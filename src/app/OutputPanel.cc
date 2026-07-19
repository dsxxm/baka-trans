#include "app/OutputPanel.h"

OutputPanel::OutputPanel() {
  set_child(text_view);

  text_view.set_editable(false);
  buffer = text_view.get_buffer();
  buffer->set_text("output here");
}
