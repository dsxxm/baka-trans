#include "app/OutputPanel.h"
#include <glibmm/refptr.h>
#include <gtkmm/cssprovider.h>

OutputPanel::OutputPanel() {
  // config
  set_policy(Gtk::PolicyType::NEVER, Gtk::PolicyType::AUTOMATIC);
  text_view.set_wrap_mode(Gtk::WrapMode::WORD_CHAR);
  text_view.set_editable(false);
  Glib::RefPtr<Gtk::CssProvider> provider = Gtk::CssProvider::create();
  provider->load_from_data("#output_textview{font:22px monospace;}");
  text_view.set_name("output_textview");
  text_view.get_style_context()->add_provider(provider, 1);
  // add somthing
  set_child(text_view);

  buffer = text_view.get_buffer();
  buffer->set_text("output here");
}
