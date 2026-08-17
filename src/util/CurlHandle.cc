#include "util/CurlHandle.h"
#include <cstddef>
#include <curl/curl.h>
#include <curl/easy.h>

// private
size_t CurlHandle::write_callback(void *content, size_t size, size_t nmemb,
                                  void *reponse) {
  size_t realsize = size * nmemb;
  std::string *str = static_cast<std::string *>(reponse);
  str->append(static_cast<char *>(content), realsize);
  return realsize;
}

CurlHandle::CurlHandle() {
  curl = NULL;
  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();
}
CurlHandle::~CurlHandle() {
  curl_easy_cleanup(curl);
  curl_global_cleanup();
}

// public

bool CurlHandle::get(const std::string &url, std::string &response) const {
  if (!curl)
    return false;

  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_POST, 0);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &CurlHandle::write_callback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

  CURLcode res = curl_easy_perform(curl);
  return res == CURLE_OK;
}

std::string CurlHandle::escape(const std::string &param) const {
  if (!curl)
    return "";
  return curl_easy_escape(curl, param.c_str(), param.size());
}

CurlHandle &CurlHandle::getInstance() {
  static CurlHandle instance;
  return instance;
}
