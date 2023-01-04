#include "coolant_temp_sensor.h"
#include "log_functions.h"

void configureCoolantTempSensor() {
    // Define the sk path this sensor use
    const char* sk_path = "propulsion.engine.coolantTemperature";

    // Config paths for the web config
    const char* analog_in_config_path = "/sensors/engine_coolant_temperature/analog_in";
    const char* linear_config_path = "/sensors/engine_coolant_temperature/linear";

    uint8_t pin = 9;
    unsigned int read_delay = 500;

    // Use a special version of the AnalogInput class that supports the ESP32C3 board.
    // The class is modified so that the pins used by C3 for the analog read is allowed.
    auto* analog_input = new AnalogInputC3(pin, read_delay, analog_in_config_path);

    const float multiplier = 0.00137;
    const float offset = -0.1644;

    analog_input
        ->connect_to(new Linear(multiplier, offset, linear_config_path))
        ->connect_to(new LambdaTransform<float, float, const char*>
            (log_function, "Coolant temp: ", log_param_data))
        ->connect_to(new SKOutputFloat(sk_path, "", new SKMetadata("K", "Engine coolant temperature")));
}