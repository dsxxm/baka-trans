#pragma once

#include <gtkmm.h>

class OutputPanel : public Gtk::ScrolledWindow {
private:
  Glib::RefPtr<Gtk::TextBuffer> buffer;
  Gtk::TextView text_view;

protected:
public:
  OutputPanel();
  Glib::RefPtr<Gtk::TextBuffer> get_buffer() { return buffer; }
};
