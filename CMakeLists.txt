cmake_minimum_required(VERSION 3.23)
project(baka-translator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED IMPORTED_TARGET gtkmm-4.0)
pkg_check_modules(LUA REQUIRED IMPORTED_TARGET lua)
pkg_check_modules(CURL REQUIRED IMPORTED_TARGET libcurl)

find_package(OpenSSL REQUIRED)
find_package(nlohmann_json REQUIRED)

set(RAPIDOCR_ONNX_DIR
  "${CMAKE_CURRENT_SOURCE_DIR}/third_party/rapidocr_onnx"
  CACHE PATH "RapidOcrOnnx CLIB directory")

find_path(RAPIDOCR_ONNX_INCLUDE_DIR
  NAMES OcrLiteCApi.h
  PATHS "${RAPIDOCR_ONNX_DIR}/include"
  NO_DEFAULT_PATH
  REQUIRED)

find_library(RAPIDOCR_ONNX_LIBRARY
  NAMES RapidOcrOnnx
  PATHS "${RAPIDOCR_ONNX_DIR}/lib"
  NO_DEFAULT_PATH
  REQUIRED)

add_library(RapidOcrOnnx::RapidOcrOnnx SHARED IMPORTED GLOBAL)
set_target_properties(RapidOcrOnnx::RapidOcrOnnx PROPERTIES
  IMPORTED_LOCATION "${RAPIDOCR_ONNX_LIBRARY}"
  INTERFACE_INCLUDE_DIRECTORIES "${RAPIDOCR_ONNX_INCLUDE_DIR}")

file(GLOB_RECURSE sources CONFIGURE_DEPENDS src/*.cc)

add_executable(${PROJECT_NAME} ${sources})
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} PRIVATE
  PkgConfig::GTKMM
  PkgConfig::LUA
  PkgConfig::CURL
  OpenSSL::Crypto
  nlohmann_json::nlohmann_json
  RapidOcrOnnx::RapidOcrOnnx
)

set_target_properties(${PROJECT_NAME} PROPERTIES
  BUILD_RPATH "${RAPIDOCR_ONNX_DIR}/lib")

target_compile_definitions(
  ${PROJECT_NAME} PRIVATE PROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}"
)
