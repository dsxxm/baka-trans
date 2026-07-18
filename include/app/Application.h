#include <gtkmm.h>

class Application : public Gtk::Application {
private:
protected:
  Application();
  void on_startup() override;
  void on_activate() override;

public:
  static Glib::RefPtr<Application> create();
};
