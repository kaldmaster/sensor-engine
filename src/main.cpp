#include "sensesp_app_builder.h"

#include "ds18b20_temp_sensors.h"
#include "rpm_counter.h"
#include "voltage_sensor.h"

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

    configureTempSensors();
    configureRPMCounter();
    configureVoltageSensor();

    // Start networking, SK server connections and other SensESP internals
    sensesp_app->start();
}

void loop() { app.tick(); }