#include "app/MainWindow.h"

// private
// protected
// public

MainWindow::MainWindow(const std::string title, int width, int height,
                       Config &config)
    : title(title), width(width), height(height), config(config),
      translation_view(config) {
  set_title(title);
  set_default_size(width, height);

  set_child(translation_view);
}
