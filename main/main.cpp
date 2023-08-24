#include <stdio.h>
#include "driver/gpio.h"
#include "driver/twai.h"
#include "communication/message.h"
#include "communication/channels/local_echo_channel.h"
#include "communication/channels/can_channel.h"
#include "driver/gpio.h"

using BHAS::Communication::Message;
using BHAS::Communication::Channels::LocalEchoChannel;
using BHAS::Communication::Channels::CANChannel;

extern "C" void app_main() {

  CANChannel channel(GPIO_NUM_14, GPIO_NUM_32);
  channel.init();

  while (true) {
    channel.receive();
  }

}