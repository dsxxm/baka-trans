#include "Config.h"
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <lua.hpp>

class Config::LuaLoader {
public:
  lua_State *lua_state;

public:
  LuaLoader() {
    lua_state = luaL_newstate();
    luaL_openlibs(lua_state);
  }
  ~LuaLoader() { lua_close(lua_state); }

  bool loadLua(const std::string &file_path) {
    if (luaL_dofile(lua_state, file_path.c_str()) != LUA_OK) {
      std::cerr << "无法加载配置文件: " << lua_tostring(lua_state, -1) << '\n';
      lua_pop(lua_state, 1);
      return false;
    }
    return true;
  }
};

Config::Config(std::string file_path) : file_path(expandUserPath(file_path)) {
  this->createFileIfNotExists(this->file_path);
  LuaLoader lua_loader;
  if (!lua_loader.loadLua(this->file_path)) {
    return;
  }
  loadConfig(lua_loader);
}

std::string Config::expandUserPath(const std::string &file_path) {
  if (file_path.size() < 2 || file_path[0] != '~' || file_path[1] != '/') {
    return file_path;
  }

  const char *home = std::getenv("HOME");
  if (home == nullptr) {
    return file_path;
  }

  return std::string(home) + file_path.substr(1);
}

void Config::createFileIfNotExists(const std::string &file_path) {
  try {
    std::filesystem::path path = std::filesystem::path(file_path);
    std::filesystem::path parent_path = path.parent_path();
    if (!parent_path.empty() && !std::filesystem::exists(parent_path)) {
      std::filesystem::create_directories(parent_path);
    }
    if (!std::filesystem::exists(path)) {
      std::ofstream ofs(path);
      if (!ofs)
        throw std::runtime_error("无法创建配置文件");
    }
  } catch (const std::exception &e) {
    std::cerr << "文件系统错误: " << e.what() << '\n';
  }
}

bool Config::loadConfig(LuaLoader &lua_loader) {
  if (!lua_istable(lua_loader.lua_state, -1)) {
    std::cerr << "配置文件必须返回 table" << '\n';
    return false;
  }

  lua_getfield(lua_loader.lua_state, -1, "api_key");
  if (!lua_isstring(lua_loader.lua_state, -1)) {
    std::cerr << "配置项 api_key 必须是字符串" << '\n';
    lua_pop(lua_loader.lua_state, 1);
    return false;
  }

  this->api_key = lua_tostring(lua_loader.lua_state, -1);
  lua_pop(lua_loader.lua_state, 1);
  return true;
}
