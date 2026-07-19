#pragma once

#include <gtkmm.h>

class InputPanel : public Gtk::ScrolledWindow {
private:
  Glib::RefPtr<Gtk::TextBuffer> buffer;
  Gtk::TextView text_view;

protected:
public:
  InputPanel();
  Glib::RefPtr<Gtk::TextBuffer> get_buffer() { return buffer; }
};
