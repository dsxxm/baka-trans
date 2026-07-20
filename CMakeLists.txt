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

file(GLOB_RECURSE sources CONFIGURE_DEPENDS src/*.cc)

add_executable(${PROJECT_NAME} ${sources})
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} PRIVATE
  PkgConfig::GTKMM
  PkgConfig::LUA
  PkgConfig::CURL
  OpenSSL::Crypto
  nlohmann_json::nlohmann_json
)

target_compile_definitions(
  ${PROJECT_NAME} PRIVATE PROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}"
)
