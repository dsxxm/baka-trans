#pragma once

/*
Main Window
*/
#include <gtkmm.h>

class MainWindow : public Gtk::ApplicationWindow {
private:
  const std::string title;
  const int width;
  const int height;

protected:
public:
  MainWindow(std::string, int, int);
};
