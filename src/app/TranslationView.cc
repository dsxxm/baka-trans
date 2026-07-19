#include "app/TranslationView.h"

// private
// protected

// public

TranslationView::TranslationView() {
  // append items
  set_orientation(Gtk::Orientation::VERTICAL);
  append(input_panel);
  append(translation_control);
  append(output_panel);

  // signals
  translation_control.signal_translate_request().connect(
      [this]() { output_panel.get_buffer()->set_text("baka!"); });
}
