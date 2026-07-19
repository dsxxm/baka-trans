#include "app/InputPanel.h"

InputPanel::InputPanel() {
  set_child(text_view);

  buffer = text_view.get_buffer();
  buffer->set_text("input here");
}
