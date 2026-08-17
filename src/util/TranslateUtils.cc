#include "util/TranslateUtils.h"
#include "config/Config.h"
#include <array>
#include <iomanip>
#include <iostream>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <openssl/evp.h>
#include <random>
#include <string>

// private

std::string TranslateUtils::translate_baidu(const std::string &source,
                                            const std::string &target,
                                            const std::string &query) {
  const std::string appid = config.baidu_app_id;
  const std::string secret_key = config.baidu_secret_key;
  const std::string salt = std::to_string(std::random_device{}());
  const std::string sign = appid + query + salt + secret_key;

  std::array<unsigned char, EVP_MAX_MD_SIZE> md;
  unsigned int md_size = 0;
  EVP_Digest(sign.data(), sign.size(), md.data(), &md_size, EVP_md5(), nullptr);

  std::ostringstream md5;
  md5 << std::hex << std::setfill('0');
  for (unsigned int i = 0; i < md_size; ++i)
    md5 << std::setw(2) << static_cast<int>(md[i]);

  const std::string url =
      "http://api.fanyi.baidu.com/api/trans/vip/translate?appid=" + appid +
      "&q=" + curl_handle.escape(query) + "&from=" + source + "&to=" + target +
      "&salt=" + salt + "&sign=" + md5.str();

  std::string response;
  if (!curl_handle.get(url, response))
    return "网络错误";

  std::string trans_result;
  try {
    nlohmann::json response_json = nlohmann::json::parse(response);
    int n = response_json["trans_result"].size();
    for (int i = 0; i < n - 1; i++) {
      trans_result +=
          response_json["trans_result"][i]["dst"].get<std::string>();
      trans_result += '\n';
    }
    trans_result +=
        response_json["trans_result"][n - 1]["dst"].get<std::string>();
  } catch (const nlohmann::json::exception &error) {
    std::cerr << "json parse exception " << error.what();
    return "json parse error";
  }

  return trans_result;
}

// public

TranslateUtils::TranslateUtils(const CurlHandle &curl_handle,
                               const Config &config)
    : curl_handle(curl_handle), config(config) {
  solutions.emplace("baidu", &TranslateUtils::translate_baidu);
}

TranslateUtils &TranslateUtils::getInstance(const CurlHandle &curl_handle,
                                            const Config &config) {
  static TranslateUtils instance(curl_handle, config);
  return instance;
}
