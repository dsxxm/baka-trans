#pragma once

#include "app/InputPanel.h"
#include "app/OutputPanel.h"
#include "app/TranslationControl.h"
#include "config/Config.h"
#include <gtkmm.h>

class TranslationView : public Gtk::Box {
private:
  Config &config;

  InputPanel input_panel;
  TranslationControl translation_control;
  OutputPanel output_panel;

  void translate();
  std::string translate_baidu();

protected:
public:
  TranslationView(Config &);
  void setInputAndTranslate(Glib::ustring text);
};
