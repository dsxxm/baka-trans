#include "util/OCRUtils.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <leptonica/allheaders.h>
#include <string>
#include <tesseract/baseapi.h>

// private

OCRUtils::OCRUtils() {}
OCRUtils::~OCRUtils() {}

// public

OCRUtils &OCRUtils::getInstance() {
  static OCRUtils instance;
  return instance;
}

std::string OCRUtils::recognize(std::string filepath) {
  tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
  if (api->Init(NULL, "eng")) {
    std::cerr << "cannot initialize tesseract";
    exit(1);
  }
  Pix *image = pixRead(filepath.c_str());
  api->SetImage(image);
  char *outtext = api->GetUTF8Text();
  std::string result = outtext;

  api->End();
  delete api;
  delete[] outtext;
  pixDestroy(&image);

  return result;
}

std::string OCRUtils::recognize(Pix *image) {
  tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
  if (api->Init(NULL, "eng")) {
    std::cerr << "cannot initialize tesseract";
    exit(1);
  }
  api->SetImage(image);
  char *outtext = api->GetUTF8Text();
  std::string result = outtext;

  api->End();
  delete api;
  delete[] outtext;

  return result;
}
