#pragma once

#include <curl/curl.h>
#include <string>

class CurlHandle {
private:
  CURL *curl;
  static size_t write_callback(void *content, size_t size, size_t nmemb,
                               void *reponse);

  CurlHandle();
  ~CurlHandle();

  CurlHandle(const CurlHandle &) = delete;
  CurlHandle &operator=(const CurlHandle &) = delete;

public:
  bool get(const std::string &url, std::string &response) const;
  // 将参数编码
  std::string escape(const std::string &param) const;

  static CurlHandle &getInstance();
};
