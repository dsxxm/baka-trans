#pragma once

/*
 * inherit from Gtk::Application to implete menu
 */
#include "config/Config.h"
#include <gtkmm.h>

class Application : public Gtk::Application {
private:
  void foo();
  void create_window();
  Config config;

protected:
  Application();
  void on_startup() override;
  void on_activate() override;

public:
  static Glib::RefPtr<Application> create();
};
