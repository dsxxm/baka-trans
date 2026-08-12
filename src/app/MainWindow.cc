#include "app/MainWindow.h"

// private

void MainWindow::read_clipboard() {
  get_clipboard()->read_text_async(
      [this](const Glib::RefPtr<Gio::AsyncResult> &result) {
        this->on_clipboard_received(result);
      });
}

void MainWindow::on_clipboard_received(
    const Glib::RefPtr<Gio::AsyncResult> &result) {
  try {
    Glib::ustring text = get_clipboard()->read_text_finish(result);
    translation_view.setInputAndTranslate(text);
  } catch (const Glib::Error &e) {
    // clipboard is empty or unavailable — nothing to do
  }
}

// protected
// public

MainWindow::MainWindow(const std::string title, int width, int height,
                       Config &config)
    : title(title), width(width), height(height), config(config),
      translation_view(config) {
  // init pointer
  foucus_controller = Gtk::EventControllerFocus::create();

  // settings
  set_title(title);
  set_default_size(width, height);

  // append items
  set_child(translation_view);
  add_controller(foucus_controller);

  // signals
  foucus_controller->signal_enter().connect(
      [this]() { this->read_clipboard(); });
}
