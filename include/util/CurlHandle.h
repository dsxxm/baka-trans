#include <curl/curl.h>
#include <string>

class CurlHandle {
private:
  CURL *curl;
  static size_t writeCallBack(void *content, size_t size, size_t nmemb,
                              void *reponse);

public:
  CurlHandle();
  ~CurlHandle();
  bool get(const std::string &url, const std::string response);
};
