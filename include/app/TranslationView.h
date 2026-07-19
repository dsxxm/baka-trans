#pragma once

#include "app/InputPanel.h"
#include "app/OutputPanel.h"
#include "app/TranslationControl.h"
#include <gtkmm.h>

class TranslationView : public Gtk::Box {
private:
  InputPanel input_panel;
  TranslationControl translation_control;
  OutputPanel output_panel;

protected:
public:
  TranslationView();
};
