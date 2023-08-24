#include <stdio.h>
#include "driver/gpio.h"
#include "communication/channels/can_channel.h"
#include "nodes/master_node.h"

using BHAS::Communication::Channels::CANChannel;
using BHAS::Nodes::MasterNode;

extern "C" void app_main() {

  CANChannel channel(GPIO_NUM_14, GPIO_NUM_32);
  channel.init();

  MasterNode node(250, channel);
  node.dispatch_forever();      // Forever loop !

}