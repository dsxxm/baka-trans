#include "app/TranslationControl.h"
#include <iostream>

// private
// protected

// public

TranslationControl::TranslationControl() {
  // build from .ui
  Glib::RefPtr<Gtk::Builder> builder;
  try {
    builder = Gtk::Builder::create_from_file(PROJECT_SOURCE_DIR
                                             "/ui/translationcontrol.ui");
  } catch (const Glib::Error &error) {
    std::cerr << "something wrong check translationcontrol.ui " << error.what();
  }
  translate_button = builder->get_object<Gtk::Button>("translate_button");
  provider = builder->get_object<Gtk::ComboBoxText>("provider");
  provider->set_active_id("baidu");
  source = builder->get_object<Gtk::ComboBoxText>("source_lang");
  source->set_active_id("auto");
  separator = builder->get_object<Gtk::Label>("separator");
  target = builder->get_object<Gtk::ComboBoxText>("target_lang");
  target->set_active_id("zh");

  // append items
  set_orientation(Gtk::Orientation::HORIZONTAL);
  append(*provider);
  append(*source);
  append(*separator);
  append(*target);
  append(*translate_button);
}

Glib::SignalProxy<void()> TranslationControl::signal_translate_request() {
  return translate_button->signal_clicked();
}
