#include "app/Application.h"
#include "app/MainWindow.h"
#include "config/Config.h"
#include <iostream>

// private

void Application::foo() { std::cout << "foo" << std::endl; }

void Application::create_window() {
  auto window = Gtk::make_managed<MainWindow>("baka-trans", config.window_width,
                                              config.window_height, config);
  add_window(*window);
  window->set_show_menubar();
  window->present();
}

// protected

Application::Application() : config(PROJECT_SOURCE_DIR "/config/config.lua") {}

void Application::on_startup() {
  Gtk::Application::on_startup();

  add_action("foo", [this]() { this->foo(); });

  Glib::RefPtr<Gtk::Builder> builder;
  try {
    builder = Gtk::Builder::create_from_file(PROJECT_SOURCE_DIR "/ui/menu.ui");
  } catch (const Glib::Error &error) {
    std::cerr << "some thing wrong,maybe check menu.ui " << error.what();
  }

  auto menu = builder->get_object<Gio::Menu>("menu");
  if (menu)
    set_menubar(menu);
}

void Application::on_activate() { create_window(); }

// public

Glib::RefPtr<Application> Application::create() {
  return Glib::make_refptr_for_instance(new Application());
}
