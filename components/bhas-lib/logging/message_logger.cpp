#include "message_logger.h"
#include "message_printer.h"
#include <stdio.h>

namespace BHAS::Logging {

  void MessageLogger::handle_received_message(Communication::Message& message) {
    char buffer[128] = {};
    MessagePrinter::print(buffer, message);
    printf("Received message: %s\n", buffer);
  }

  void MessageLogger::handle_send_message(Communication::Message& message) {
    char buffer[128] = {};
    MessagePrinter::print(buffer, message);
    printf("Send message: %s\n", buffer);
  }

};