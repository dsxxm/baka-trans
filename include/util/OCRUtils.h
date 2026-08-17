#pragma once

#include <leptonica/allheaders.h>
#include <string>

class OCRUtils {
private:
  OCRUtils();
  ~OCRUtils();
  OCRUtils(const OCRUtils &) = delete;
  OCRUtils &operator=(const OCRUtils &) = delete;

public:
  static OCRUtils &getInstance();

  std::string recognize(std::string);
  std::string recognize(Pix *);
};
