# baka-translator 一个基于gtkmm的linux翻译器

## 目前功能

- 基础翻译界面
- 通过lua脚本配置程序 通过~/.config/baka-trans/config.lua 来配置程序 可支持配置内容如下

``` lua
return {
 -- window config
 window_height = 480,
 window_width = 640,

 -- translate api
 baidu_appid = "",
 baidu_secret_key = "",
}
```

## 未来计划加入

- 更多翻译服务商兼容
- 语音翻译
- 界面优化,更多的lua配置,通过菜单栏配置程序

## OCR 识别语言

OCR 使用翻译界面的源语言：`zh` 使用 Tesseract `chi_sim`，`jp` 使用
`jpn`，`en` 和 `auto` 使用 `eng`。请为所选语言安装对应的 Tesseract
训练数据。

## 编译程序

在项目根路径使用

``` cmake
cmake -S . -B ./cmake-build/ -G Ninja
cmake --build ./cmake-build
```

之后就可以通过

```bash
./cmake-build/baka-translator
```

运行程序
