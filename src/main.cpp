#include "sensesp/sensors/analog_input.h"
#include "sensesp/sensors/digital_input.h"
#include "sensesp/sensors/sensor.h"
#include "sensesp/signalk/signalk_output.h"
#include "sensesp/system/lambda_consumer.h"
#include "sensesp_app_builder.h"

using namespace sensesp;

reactesp::ReactESP app;

// The setup function performs one-time application initialization.
void setup() {
#ifndef SERIAL_DEBUG_DISABLED
    SetupSerialDebug(115200);
#endif

    // Construct the global SensESPApp() object
    SensESPAppBuilder builder;
    sensesp_app = (&builder)
        ->set_hostname("sensor-engine")
        ->get_app();

    // Start networking, SK server connections and other SensESP internals
    sensesp_app->start();
}

void loop() { app.tick(); }