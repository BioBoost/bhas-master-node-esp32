#pragma once

#include "channel.h"
#include "driver/gpio.h"

namespace BHAS::Communication::Channels {

  class CANChannel : public Channel {

    public:
      CANChannel(gpio_num_t txPin, gpio_num_t rxPin);
    
    public:
      bool init();
      // TODO - Add de-init

    public:
      bool send(Message& message);
      void receive();   // Need to call this method periodically to receive messages; handlers will be called if registered
    
    private:
      gpio_num_t _txPin;
      gpio_num_t _rxPin;
      bool _initialized = false;

  };

};
