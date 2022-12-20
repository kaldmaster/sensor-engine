#include "analog_input_c3.h"

#include "Arduino.h"
#include "sensesp/sensors/sensor.h"

namespace sensesp {

AnalogInputC3::AnalogInputC3(uint8_t pin, unsigned int read_delay, String config_path,
                         float output_scale)
    : FloatSensor(config_path),
      pin{pin},
      read_delay{read_delay},
      output_scale{output_scale} {
  analog_reader = new AnalogReaderC3(pin);
  load_configuration();
}

void AnalogInputC3::update() { this->emit(output_scale * analog_reader->read()); }

void AnalogInputC3::start() {
  if (this->analog_reader->configure()) {
    ReactESP::app->onRepeat(read_delay, [this]() { this->update(); });
  }
}

void AnalogInputC3::get_configuration(JsonObject& root) {
  root["read_delay"] = read_delay;
};

static const char SCHEMA[] PROGMEM = R"###({
    "type": "object",
    "properties": {
        "read_delay": { "title": "Read delay", "type": "number", "description": "Number of milliseconds between each analogRead(A0)" }
    }
  })###";

String AnalogInputC3::get_config_schema() { return FPSTR(SCHEMA); }

bool AnalogInputC3::set_configuration(const JsonObject& config) {
  String expected[] = {"read_delay"};
  for (auto str : expected) {
    if (!config.containsKey(str)) {
      return false;
    }
  }
  read_delay = config["read_delay"];
  return true;
}

}  // namespace sensesp
