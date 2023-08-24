#include "master_node.h"
#include <stdio.h>

namespace BHAS::Nodes {

  MasterNode::MasterNode(uint8_t id, Communication::Channel& channel)
    : _id(id), _channel(channel) {

    setup_channel_logging();
  }

  uint8_t MasterNode::id() const {
    return _id;
  }

  Communication::Channel& MasterNode::channel() {
    return _channel;
  }
  void MasterNode::setup_channel_logging() {
    _channel.register_receive_handler(&_messageLogger);
    _channel.register_receive_handler(this);

    _channel.register_send_handler(&_messageLogger);
    _channel.register_send_handler(this);
  }

  void MasterNode::dispatch_forever() {
    while(true) {
      _channel.receive();
    }
  }

  void MasterNode::handle_received_message(Communication::Message& message) {
    if (message.destination_id() != id() && message.destination_id() != MasterNode::BROADCAST_ID) {
      return;
    }

    printf("Received a CAN message\n");
  }

  void MasterNode::handle_send_message(Communication::Message& message) {
    // Ignore send messages
  }

};