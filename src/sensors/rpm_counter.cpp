#include "rpm_counter.h"
#include "log_functions.h"

void configureRPMCounter() {
    // Define the sk path this sensor use
    const char* sk_path = "propulsion.engine.revolutions";

    // Config paths for the web config
    const char* config_path = "/sensors/engine_rpm";

    // These two are necessary until a method is created to synthesize them.
    // Everything after "/sensors" in each of these ("/engine_rpm/calibrate" and
    // "/engine_rpm/sk") is simply a label to display what you're configuring in
    // the Configuration UI.
    const char* config_path_calibrate = "/sensors/engine_rpm/calibrate";
    const char* config_path_skpath = "/sensors/engine_rpm/sk";

    // Read the value every 500 ms. The alternator have 16 poles, whick makes
    // the multiplier 1/16;
    const float multiplier = 16.0;
    const unsigned int read_delay = 500;

    // Pin 8 and trigger on rising value.
    uint8_t pin = 8;
    auto* sensor = new DigitalInputCounter(pin, INPUT_PULLUP, RISING, read_delay);

    sensor
        ->connect_to(new Frequency(multiplier, config_path_calibrate))
        ->connect_to(new LambdaTransform<float, float, const char*>
            (log_function, "RPM: ", log_param_data))
        ->connect_to(new SKOutputFloat(sk_path, config_path_skpath, new SKMetadata("Hz", "Engine RPM")));
}