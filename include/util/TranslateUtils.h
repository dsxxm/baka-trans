#include "config/Config.h"
#include "util/CurlHandle.h"
#include <string>
#include <unordered_map>

class TranslateUtils {
private:
  const CurlHandle &curl_handle;
  const Config &config;
  // source源语言 target目标语言 query翻译内容 return翻译结果
  std::string translate_baidu(const std::string &source,
                              const std::string &target,
                              const std::string &query);

  TranslateUtils(const CurlHandle &curl_handle, const Config &config);

  TranslateUtils(const TranslateUtils &) = delete;
  TranslateUtils operator=(const TranslateUtils &) = delete;

public:
  using TransSol = std::string (TranslateUtils::*)(const std::string &,
                                                   const std::string &,
                                                   const std::string &);
  std::unordered_map<std::string, TransSol> solutions;

  static TranslateUtils &getInstance(const CurlHandle &, const Config &);
};
