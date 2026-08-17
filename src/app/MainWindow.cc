#include "app/MainWindow.h"
#include "util/OCRUtils.h"
#include <cstddef>
#include <gdk/gdk.h>
#include <glibmm/ustring.h>
#include <vector>

// private

void MainWindow::read_clipboard() {
  Glib::RefPtr<Gdk::Clipboard> clipboard = get_clipboard();
  Glib::RefPtr<Gdk::ContentFormats> formats = clipboard->get_formats();

  if (formats->contain_mime_type("text/plain")) {
    clipboard->read_text_async(
        [this](const Glib::RefPtr<Gio::AsyncResult> &result) {
          this->on_clipboard_received_text(result);
        });
  }

  if (formats->contain_gtype(GDK_TYPE_TEXTURE)) {
    clipboard->read_texture_async(
        [this](const Glib::RefPtr<Gio::AsyncResult> &result) {
          this->on_clipboard_received_img(result);
        });
  }
}

void MainWindow::on_clipboard_received_text(
    const Glib::RefPtr<Gio::AsyncResult> &result) {
  try {
    Glib::ustring text = get_clipboard()->read_text_finish(result);
    translation_view.setInputAndTranslate(text);
  } catch (const Glib::Error &e) {
    // clipboard is empty or unavailable — nothing to do
  }
}

void MainWindow::on_clipboard_received_img(
    const Glib::RefPtr<Gio::AsyncResult> &result) {
  try {
    Glib::RefPtr<Gdk::Texture> texture =
        get_clipboard()->read_texture_finish(result);
    // tansform texture to pix in leptonica
    const int width = texture->get_width();
    const int height = texture->get_height();
    const std::size_t stride = width * 4;
    std::vector<unsigned char> pixels(stride * height);
    texture->download(pixels.data(), stride);
    Pix *pix = pixCreate(width, height, 32);
    l_uint32 *data = pixGetData(pix);
    const int wpl = pixGetWpl(pix);
    for (int y = 0; y < height; ++y) {
      l_uint32 *line = data + y * wpl;
      for (int x = 0; x < width; ++x) {
        const auto *p = pixels.data() + y * stride + x * 4;

        const l_uint32 r = p[0];
        const l_uint32 g = p[1];
        const l_uint32 b = p[2];

        composeRGBPixel(r, g, b, &line[x]);
      }
    }

    Glib::ustring ocr_result = OCRUtils::getInstance().recognize(pix);
    pixDestroy(&pix);

    translation_view.setInputAndTranslate(ocr_result);
  } catch (const Glib::Error &e) {
    // do nothing
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
