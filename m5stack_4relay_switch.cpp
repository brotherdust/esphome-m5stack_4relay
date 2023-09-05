#include "m5stack_4relay_switch.h"

#include "esphome/core/helpers.h"
#include "esphome/core/log.h"

namespace esphome {
namespace m5stack_4relay {

static const char *const TAG = "m5stack_4relay";

void M5STACK4RELAYComponent::setup() {
  ESP_LOGCONFIG(TAG, "Setting up M5STACK4RELAY (0x%02X)...", this->address_);
  auto err = this->write(nullptr, 0);
  if (err != i2c::ERROR_OK) {
    this->mark_failed();
    return;
  }
  uint8_t component_status = 0;
  get_status(&component_status);
}

M5STACK4RELAYSwitch *M5STACK4RELAYComponent::create_switch(uint8_t switch_num) {
  return new M5STACK4RELAYSwitch(this, switch_num);
}

void M5STACK4RELAYComponent::loop() {
  if (this->update_) {
    // this->set_component_value_();

    this->update_ = false;
  }
}

void M5STACK4RELAYComponent::get_status(uint8_t *state) {
  this->read_byte(M5STACK4RELAY_RELAY_CONTROL_REGISTER);
}

bool M5STACK4RELAYComponent::set_component_value_(uint8_t switch_num,
                                                  uint8_t value) {
  get_status(&component_status);
  ESP_LOGD(TAG, "Current status 0x%02X", component_status);
  ESP_LOGD(TAG, "Desired switch: %1u", switch_num);
  ESP_LOGD(TAG, "Desired state: %1u", value);
  switch_num = 3 - switch_num;
  if (value) {
    this->component_status |= (1u << switch_num);
  } else {
    this->component_status &= ~(1u << switch_num);
  }
  this->update_ = true;
  return this->write_byte(M5STACK4RELAY_RELAY_CONTROL_REGISTER, component_status);
  
}

void M5STACK4RELAYSwitch::write_state(bool state) {
  if (!this->parent_->set_component_value_(this->switch_num_, state)) {
    publish_state(false);
  } else {
    publish_state(state);
  }
}

}  // namespace m5stack_4relay
}  // namespace esphome
