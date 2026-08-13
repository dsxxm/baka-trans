#pragma once

class OCRUtils {
private:
  OCRUtils();
  ~OCRUtils();
  OCRUtils(const OCRUtils &) = delete;
  OCRUtils &operator=(const OCRUtils &) = delete;

public:
  static OCRUtils &getInstance();
};
