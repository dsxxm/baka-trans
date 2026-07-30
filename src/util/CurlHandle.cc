#include "util/CurlHandle.h"

// private
size_t CurlHandle::writeCallBack(void *content, size_t size, size_t nmemb,
                                 void *reponse) {
  size_t realsize = size * nmemb;
  std::string *str = static_cast<std::string *>(reponse);
}

// public
CurlHandle::CurlHandle() {
  curl = NULL;
  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();
}
CurlHandle::~CurlHandle() { curl_easy_cleanup(curl); }
