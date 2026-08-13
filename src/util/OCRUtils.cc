#include "util/OCRUtils.h"

// private

OCRUtils::OCRUtils() {}
OCRUtils::~OCRUtils() {}

// public

OCRUtils &OCRUtils::getInstance() {
  static OCRUtils instance;
  return instance;
}
