#pragma once

#include <string>

/*
** Read Config from lua
*/
class Config {
private:
  class LuaLoader;

  std::string file_path;

  static std::string expandUserPath(const std::string &file_path);
  void createFileIfNotExists(const std::string &file_path);
  bool loadConfig(LuaLoader &lua_loader);

public:
  Config(std::string file_path);

  int window_height;
  int window_width;

  std::string baidu_app_id;
  std::string baidu_secret_key;
};
