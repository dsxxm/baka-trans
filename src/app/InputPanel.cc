#include "app/InputPanel.h"

// public

InputPanel::InputPanel() {
  // add something
  set_child(text_view);
  buffer = text_view.get_buffer();
}
