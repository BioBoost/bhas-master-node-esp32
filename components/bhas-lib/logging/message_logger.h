#pragma once

#include "../communication/i_message_handler.h"

namespace BHAS::Logging {

  class MessageLogger : public Communication::IMessageHandler {

    public:
      void handle_received_message(Communication::Message& message);
      void handle_send_message(Communication::Message& message);

  };

};