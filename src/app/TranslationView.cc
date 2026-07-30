#include "app/TranslationView.h"
#include <array>
#include <curl/curl.h>
#include <iomanip>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <openssl/evp.h>
#include <random>
#include <sstream>

// private

void TranslationView::translate() {
  std::string provider = translation_control.get_provider();
  // TODO: add a map
  const std::string response = translate_baidu();
  output_panel.get_buffer()->set_text(response);
}

std::string TranslationView::translate_baidu() {
  const std::string appid = config.baidu_app_id;
  const std::string secret_key = config.baidu_secret_key;
  const std::string salt = std::to_string(std::random_device{}());
  const std::string query = input_panel.get_buffer()->get_text();
  const std::string sign = appid + query + salt + secret_key;

  std::array<unsigned char, EVP_MAX_MD_SIZE> md;
  unsigned int md_size = 0;
  EVP_Digest(sign.data(), sign.size(), md.data(), &md_size, EVP_md5(), nullptr);

  std::ostringstream md5;
  md5 << std::hex << std::setfill('0');
  for (unsigned int i = 0; i < md_size; ++i)
    md5 << std::setw(2) << static_cast<int>(md[i]);

  std::unique_ptr<CURL, decltype(&curl_easy_cleanup)> curl(curl_easy_init(),
                                                           curl_easy_cleanup);
  if (!curl)
    return "create curl failed";

  const auto escape = [&](const std::string &text) {
    char *escaped = curl_easy_escape(curl.get(), text.c_str(), text.size());
    std::string result = escaped ? escaped : "";
    curl_free(escaped);
    return result;
  };

  const std::string source = translation_control.get_source();
  const std::string target = translation_control.get_target();
  const std::string url =
      "http://api.fanyi.baidu.com/api/trans/vip/translate?appid=" + appid +
      "&q=" + escape(query) + "&from=" + source + "&to=" + target +
      "&salt=" + salt + "&sign=" + md5.str();

  curl_easy_setopt(curl.get(), CURLOPT_URL, url.c_str());

  std::string response_str;
  curl_easy_setopt(
      curl.get(), CURLOPT_WRITEFUNCTION,
      +[](char *ptr, size_t size, size_t nmemb, void *userdata) {
        auto *response = static_cast<std::string *>(userdata);
        response->append(ptr, size * nmemb);
        return size * nmemb;
      });
  curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA, &response_str);

  const CURLcode result = curl_easy_perform(curl.get());
  if (result != CURLE_OK) {
    std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(result)
              << '\n';
    return "curl_easy_perform() failed";
  }
  std::string trans_result;
  try {
    nlohmann::json response = nlohmann::json::parse(response_str);
    trans_result = response["trans_result"][0]["dst"];
  } catch (const nlohmann::json::exception &error) {
    std::cerr << "json parse exception " << error.what();
    return "json parse error";
  }
  return trans_result;
}

// protected

// public

TranslationView::TranslationView(Config &config) : config(config) {
  // settings
  set_orientation(Gtk::Orientation::VERTICAL);

  // append items
  append(input_panel);
  append(translation_control);
  append(output_panel);

  // signals
  translation_control.signal_translate_request().connect(
      [this]() { this->translate(); });
}

void TranslationView::setInputAndTranslate(Glib::ustring text) {
  input_panel.get_buffer()->set_text(text);
  translate();
}
