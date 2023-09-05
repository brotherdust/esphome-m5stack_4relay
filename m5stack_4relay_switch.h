#pragma once

#include "esphome/components/i2c/i2c.h"
#include "esphome/components/switch/switch.h"
#include "esphome/core/component.h"

namespace esphome {
namespace m5stack_4relay {

class M5STACK4RELAYSwitch;

class M5STACK4RELAYComponent : public Component, public i2c::I2CDevice {
 public:
  M5STACK4RELAYComponent(bool store_in_eeprom,
                         uint8_t mode = M5STACK4RELAY_MODES::SYNC)
      : store_in_eeprom_(store_in_eeprom), mode_(mode) {}

  // M5STACK4RELAYSwitch *create_channel(uint8_t channel);

  const uint8_t M5STACK4RELAY_MODE_CONTROL_REGISTER = 0x10;
  const uint8_t M5STACK4RELAY_RELAY_CONTROL_REGISTER = 0x11;
  enum M5STACK4RELAY_MODES {

    ASYNC = 0x0,
    SYNC = 0x1,
  };

  M5STACK4RELAYSwitch *create_switch(uint8_t switch_num);

  void setup() override;
  float get_setup_priority() const override { return setup_priority::HARDWARE; }
  void loop() override;

 protected:
  friend M5STACK4RELAYSwitch;
  bool set_component_value_(uint8_t channel, uint8_t value);
  void get_status(uint8_t *state);

  uint8_t mode_ = M5STACK4RELAY_MODES::SYNC;
  uint8_t component_status = 0;
  bool store_in_eeprom_ = false;
  bool update_ = false;
};

class M5STACK4RELAYSwitch : public switch_::Switch {
 public:
  M5STACK4RELAYSwitch(M5STACK4RELAYComponent *parent, uint8_t switch_num)
      : parent_(parent), switch_num_(switch_num) {}

 protected:
  void write_state(bool state) override;

  M5STACK4RELAYComponent *parent_;
  uint8_t switch_num_;
};

}  // namespace m5stack_4relay
}  // namespace esphome
