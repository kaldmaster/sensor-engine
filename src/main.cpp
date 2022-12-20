
#include "sensesp_app_builder.h"

// #include "sensors/ds18b20_temp_sensors.h"
#include "sensors/rpm_counter.h"
#include "sensors/voltage_sensor.h"
#include "sensors/coolant_temp_sensor.h"

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
#ifndef SERIAL_DEBUG_DISABLED // If debuging is enabled, try to connect to local debug server
        ->set_sk_server("192.168.10.196", 3000)
#endif
        ->get_app();

    // configureTempSensors();
    configureRPMCounter();
    configureVoltageSensor();
    configureCoolantTempSensor();

    // Start networking, SK server connections and other SensESP internals
    sensesp_app->start();
}

void loop() { app.tick(); }