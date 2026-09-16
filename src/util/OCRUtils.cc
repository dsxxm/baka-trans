#include "util/OCRUtils.h"
#include <iostream>
#include <leptonica/allheaders.h>
#include <string>
#include <tesseract/baseapi.h>

namespace {

const char *tesseract_language(const std::string &source_language) {
  if (source_language == "zh")
    return "chi_sim";
  if (source_language == "jp")
    return "jpn";
  return "eng";
}

std::string recognize_image(Pix *image, const char *language) {
  tesseract::TessBaseAPI api;
  if (api.Init(nullptr, language)) {
    std::cerr << "cannot initialize tesseract language: " << language << '\n';
    return {};
  }

  api.SetImage(image);
  char *outtext = api.GetUTF8Text();
  std::string result = outtext;
  delete[] outtext;
  return result;
}

} // namespace

// private

OCRUtils::OCRUtils() {}
OCRUtils::~OCRUtils() {}

// public

OCRUtils &OCRUtils::getInstance() {
  static OCRUtils instance;
  return instance;
}

std::string OCRUtils::recognize(const std::string &filepath,
                                const std::string &source_language) {
  Pix *image = pixRead(filepath.c_str());
  if (image == nullptr)
    return {};

  const std::string result =
      recognize_image(image, tesseract_language(source_language));
  pixDestroy(&image);
  return result;
}

std::string OCRUtils::recognize(Pix *image,
                                const std::string &source_language) {
  return recognize_image(image, tesseract_language(source_language));
}
