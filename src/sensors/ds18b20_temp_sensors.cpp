#include "ds18b20_temp_sensors.h"

void configureTempSensors() {
    uint8_t temp_pin = 5;
    uint temp_read_delay = 500;

    DallasTemperatureSensors* dts = new DallasTemperatureSensors(temp_pin);

    auto* alternator_temp =
        new OneWireTemperature(dts, temp_read_delay, "/alternatorTemperature/oneWire");
    alternator_temp->connect_to(new Linear(1.0, 0.0, "/alternatorTemperature/linear"))
        ->connect_to(new SKOutputFloat("propulsion.engine.alternatorTemperature",
                                     "/alternatorTemperature/skPath"));

    auto* exhaust_temp =
        new OneWireTemperature(dts, temp_read_delay, "/exhaustTemperature/oneWire");
    exhaust_temp->connect_to(new Linear(1.0, 0.0, "/exhaustTemperature/linear"))
        ->connect_to(new SKOutputFloat("propulsion.engine.exhaustTemperature",
                                     "/alternatorTemperature/skPath"));

    auto* engine_room_temp =
        new OneWireTemperature(dts, temp_read_delay, "/engineRoomTemperature/oneWire");
    engine_room_temp->connect_to(new Linear(1.0, 0.0, "/engineRoomTemperature/linear"))
        ->connect_to(new SKOutputFloat("propulsion.engine.roomTemperature",
                                     "/engineRoomTemperature/skPath"));
}