#include <gtkmm.h>

class Application : public Gtk::Application {
private:
  void foo();
  void create_window();
  Glib::RefPtr<Gtk::Builder> builder;

protected:
  Application();
  void on_startup() override;
  void on_activate() override;

public:
  static Glib::RefPtr<Application> create();
};
