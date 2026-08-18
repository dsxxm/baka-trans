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
- ocr图片翻译 ✅  TOOD:加入ocr根据provirder切换识别语言类型 目前配置为只支持英文ocr(只需要更改tesseract init配置即可更换)
- 语音翻译
- 界面优化,更多的lua配置,通过菜单栏配置程序

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
