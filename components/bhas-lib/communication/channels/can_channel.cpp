#include "can_channel.h"
#include "../encoders/can_encoder.h"
#include "driver/twai.h"

namespace BHAS::Communication::Channels {

  CANChannel::CANChannel(gpio_num_t txPin, gpio_num_t rxPin)
    : _txPin(txPin), _rxPin(rxPin) {
  }

  bool CANChannel::init() {
    //Initialize configuration structures using macro initializers
    twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT(_txPin, _rxPin, TWAI_MODE_NORMAL);
    twai_timing_config_t t_config = TWAI_TIMING_CONFIG_100KBITS();
    twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

    if (twai_driver_install(&g_config, &t_config, &f_config) != ESP_OK) {
      // TODO: Error message ?
      _initialized = false;
      return false;
    }

    if (twai_start() != ESP_OK) {
      // TODO: Error message ?
      _initialized = false;
      return false;
    }

    _initialized = true;
    return true;
  }

  bool CANChannel::send(Message& message) {
    twai_message_t canMessage = Encoders::CANEncoder::message_to_can_message(message);
    esp_err_t result = twai_transmit(&canMessage, pdMS_TO_TICKS(1000));

    // TODO: Check result + what if fails ? Do we create internal buffer for messages that need to be send ?
  
    if (result == ESP_OK) call_send_handlers(message);

    return result == ESP_OK;
  }

  void CANChannel::receive() {
    twai_message_t canMessage;
    if (twai_receive(&canMessage, pdMS_TO_TICKS(10)) == ESP_OK) {
      Message message = Encoders::CANEncoder::can_message_to_message(canMessage);
      call_receive_handlers(message);
    }
  }

};
