#ifndef CONFIG_H
#define CONFIG_H

#include <string>

/*
** Read Config from lua
*/
class Config {
private:
  class LuaLoader;

  const std::string file_path;
  std::string api_key;

  static std::string expandUserPath(const std::string &file_path);
  void createFileIfNotExists(const std::string &file_path);
  bool loadConfig(LuaLoader &lua_loader);

public:
  Config(std::string file_path = "~/.config/baka/trans.config.lua");
  ~Config() {}
};

#endif
