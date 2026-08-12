#include "app/TranslationView.h"
#include "util/CurlHandle.h"
#include "util/TranslateUtils.h"
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <openssl/evp.h>
#include <string>

// private

void TranslationView::translate() {
  std::string provider = translation_control.getProvider();

  CurlHandle &curl_handle = CurlHandle::getInstance();
  TranslateUtils &translate_utils =
      TranslateUtils::getInstance(curl_handle, config);

  auto it = translate_utils.solutions.find(provider);
  if (it != translate_utils.solutions.end()) {
    const std::string source = translation_control.getSource();
    const std::string target = translation_control.getTarget();
    const std::string query = input_panel.getBuffer()->get_text();

    std::string response =
        (translate_utils.*(it->second))(source, target, query);
    output_panel.getBuffer()->set_text(response);
  }
}

// protected

// public

TranslationView::TranslationView(Config &config) : config(config) {
  // settings
  set_orientation(Gtk::Orientation::VERTICAL);
  input_panel.set_vexpand(true);
  output_panel.set_vexpand(true);

  // append items
  append(input_panel);
  append(translation_control);
  append(output_panel);

  // signals
  translation_control.signalTranslateRequest().connect(
      [this]() { this->translate(); });
}

void TranslationView::setInputAndTranslate(Glib::ustring text) {
  text.erase(0, text.find_first_not_of("\n"));
  text.erase(text.find_last_not_of("\n") + 1);
  if (input_panel.getBuffer()->get_text() != text) {
    input_panel.getBuffer()->set_text(text);
    translate();
  }
}
