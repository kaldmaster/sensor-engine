#include "voltage_sensor.h"
#include "log_functions.h"

void configureVoltageSensor() {
    // Define the sk path this sensor use
    const char* sk_path = "propulsion.engine.alternatorVoltage";

    // Config paths for the web config
    const char* analog_in_config_path = "/sensors/engine_alternator_voltage/analog_in";
    const char* linear_config_path = "/sensors/engine_alternator_voltage/linear";

    uint8_t pin = 8;
    unsigned int read_delay = 500;

    // Use a special version of the AnalogInput class that supports the ESP32C3 board.
    // The class is modified so that the pins used by C3 for the analog read is allowed.
    auto* analog_input = new AnalogInputC3(pin, read_delay, analog_in_config_path);

    // A voltage divider senses this value, with R1 = 100000 ohm and R2 = 27000 ohm.
    // This makes a scale of 15.52 between input value and actual, measured voltage.
    // Calculations available at https://docs.google.com/spreadsheets/d/1HJ_5kxFobu_9aqS2uCWbvzM1abmkm9GddhXVNrw4OBc/edit#gid=52356573
    const float multiplier = 15.52222222;
    const float offset = 0;

    // Connect the output of the analog input to the Linear transform,
    // and then output the results to the Signal K server. As part of
    // that output, send some metadata to indicate that the "units"
    // to be used to display this value is "ratio". Also specify that
    // the display name for this value, to be used by any Signal K
    // consumer that displays it, is "Indoor light".
    analog_input
        ->connect_to(new Linear(multiplier, offset, linear_config_path))
        ->connect_to(new LambdaTransform<float, float, const char*>
            (log_function, "Alternator voltage: ", log_param_data))
        ->connect_to(new SKOutputFloat(sk_path, "", new SKMetadata("V", "Engine alternator voltage")));
}