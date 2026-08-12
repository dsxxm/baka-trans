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

  Glib::RefPtr<Gtk::EventControllerFocus> foucus_controller;

  TranslationView translation_view;

  void read_clipboard();
  void on_clipboard_received(const Glib::RefPtr<Gio::AsyncResult> &result);

protected:
public:
  MainWindow(const std::string, int, int, Config &);
};
