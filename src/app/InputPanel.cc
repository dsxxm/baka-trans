#include "app/InputPanel.h"

// public

InputPanel::InputPanel() {
  // config
  set_policy(Gtk::PolicyType::NEVER, Gtk::PolicyType::AUTOMATIC);
  text_view.set_wrap_mode(Gtk::WrapMode::WORD_CHAR);
  Glib::RefPtr<Gtk::CssProvider> provider = Gtk::CssProvider::create();
  provider->load_from_data("#input_textview{font:22px monospace;}");
  text_view.set_name("input_textview");
  text_view.get_style_context()->add_provider(provider, 1);
  // add something
  set_child(text_view);
  buffer = text_view.get_buffer();
}
