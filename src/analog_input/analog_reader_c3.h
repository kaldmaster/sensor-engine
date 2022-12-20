#ifndef _analog_reader_H_
#define _analog_reader_H_

#include "Arduino.h"
#include "sensesp.h"
#if defined(ESP32)
#include "esp_adc_cal.h"
#endif

namespace sensesp {

/**
 * @brief Used by AnalogInput as a hardware abstraction layer.
 * 
 * This is a modified version to support ESP32C3 boards. digitalPinToAnalogChannelC3 is a
 * modified version of digitalPinToAnalogChannel that returns correct channels for C3 boards,
 * which always returns -1 otherwise.
 **/
class BaseAnalogReader {
 private:
  int output_scale_;

 public:
  virtual bool configure() = 0;
  virtual float read() = 0;
};

class ESP32C3AnalogReader : public BaseAnalogReader {
 private:
  int pin_;
  adc_atten_t attenuation_ = ADC_ATTEN_DB_11;
   // This should work with ESP32 and newer variants, ADCs are different
  adc_bits_width_t  bit_width_ = (adc_bits_width_t)  ADC_WIDTH_BIT_DEFAULT;
  // maximum voltage readout for 3.3V VDDA when attenuation_ is set to 11 dB
  const float kVmax_ = 3300;
  int8_t adc_channel_;
  esp_adc_cal_characteristics_t adc_characteristics_;
  const int kVref_ = 1100;  // voltage reference, in mV

 public:
  ESP32C3AnalogReader(int pin) : pin_{pin} {
    if (!(4 <= pin && pin <= 9)) {
      debugE("Only ADC1 is supported at the moment");
      adc_channel_ = -1;
      return;
    }
    adc_channel_ = digitalPinToAnalogChannelC3(pin);
  }

  int8_t digitalPinToAnalogChannelC3(int pin) {
    switch (pin)
    {
    case 4:
      return 0;
    case 5:
      return 1;
    case 8:
      return 3;
    case 9:
      return 4;
    
    default:
      return -1;
    }
  }

  bool configure() {
    if (adc_channel_ == -1) {
      return false;
    }
    adc1_config_width(bit_width_);
    adc1_config_channel_atten((adc1_channel_t)adc_channel_, attenuation_);
    esp_adc_cal_characterize(ADC_UNIT_1, attenuation_, bit_width_, kVref_,
                             &adc_characteristics_);
    return true;
  }

  float read() {
    uint32_t voltage;
    esp_adc_cal_get_voltage((adc_channel_t)adc_channel_, &adc_characteristics_,
                            &voltage);
    return voltage / kVmax_;
  }
};
typedef ESP32C3AnalogReader AnalogReaderC3;

}  // namespace sensesp

#endif
