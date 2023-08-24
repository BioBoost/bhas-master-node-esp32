#pragma once

#include <stdint.h>
#include "../communication/i_message_handler.h"
#include "../communication/message.h"
#include "../logging/message_logger.h"
#include "../communication/channels/channel.h"

namespace BHAS::Nodes {

  class MasterNode : public Communication::IMessageHandler {

    public:
      MasterNode(uint8_t id, Communication::Channel& channel);

    public:
      uint8_t id() const;

    public:
      void dispatch_forever();

    protected:
      Communication::Channel& channel();

    protected:
      void handle_received_message(Communication::Message& message);
      void handle_send_message(Communication::Message& message);

    private:
      void setup_channel_logging();

    private:
      static const uint8_t BROADCAST_ID = 255;

    private:
      uint8_t _id = 0;
      Communication::Channel& _channel;
      Logging::MessageLogger _messageLogger;
  };

};