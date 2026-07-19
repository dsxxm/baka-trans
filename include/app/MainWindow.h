#pragma once

/*
Main Window
*/
#include "app/TranslationView.h"
#include "config/Config.h"
#include <gtkmm.h>

class MainWindow : public Gtk::ApplicationWindow {
private:
  const std::string title;
  const int width;
  const int height;
  Config &config;

  TranslationView translation_view;

protected:
public:
  MainWindow(const std::string, int, int, Config &);
};
