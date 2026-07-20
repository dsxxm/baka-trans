#pragma once

#include <gtkmm.h>

class TranslationControl : public Gtk::Box {
private:
  Glib::RefPtr<Gtk::Button> translate_button;
  Glib::RefPtr<Gtk::ComboBoxText> provider;
  Glib::RefPtr<Gtk::ComboBoxText> source;
  Glib::RefPtr<Gtk::Label> separator;
  Glib::RefPtr<Gtk::ComboBoxText> target;

protected:
public:
  TranslationControl();
  Glib::SignalProxy<void()> signal_translate_request();
  std::string get_provider();
  std::string get_source();
  std::string get_target();
};
