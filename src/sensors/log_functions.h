#include "sensesp/transforms/lambda_transform.h"

using namespace sensesp;

//
// Defininng the log param data object
//
const ParamInfo* log_param_data = new ParamInfo[1]{
    {"prefix", "Prefix"}
};

auto log_function = [](float value, const char* prefix) -> float {
    Serial.print("Alternator voltage: ");
    Serial.println(value);
    return value;
};