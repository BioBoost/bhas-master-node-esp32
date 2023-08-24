#pragma once

#include <stdint.h>
#include <stddef.h>
#include <cstring>
#include "../message.h"
#include "driver/twai.h"

namespace BHAS::Communication::Encoders {

  class CANEncoder {

    public:
      static const size_t MAX_CAN_PACKET_SIZE = 8;

    // CAN Message format:
    // | CAN ID (11 bits = DST) | SRC ID (8 bits) | ENT ID (8 bits) | BASE TYPE (4 bits) + SUBTYPE (4 bits) | DATA (max 5 bytes) |

    public:
      static twai_message_t message_to_can_message(const Message& message) {
        twai_message_t canMessage;
        canMessage.identifier = message.destination_id();
        canMessage.extd = 0;
        canMessage.data_length_code = message.payload_size() + 3;      // +3 for Sid, Eid and type
        canMessage.data[0] = message.source_id();
        canMessage.data[1] = message.entity_id();
        canMessage.data[2] = (static_cast<char>(message.base_type())  << 4) | (message.sub_type() & 0x0F);
        memcpy(canMessage.data+3, message.payload(), message.payload_size());

        return canMessage;
      }

      static Message can_message_to_message(const twai_message_t& canMessage) {
        Message message;
        
        message.source_id(canMessage.identifier);
        message.destination_id(canMessage.data[0]);
        message.entity_id(canMessage.data[1]);
        message.base_type(static_cast<Message::BaseType>((canMessage.data[2] >> 4) & 0x0F));
        message.sub_type(canMessage.data[2] & 0x0F);
        message.payload(canMessage.data+3, canMessage.data_length_code-3);

        return message;
      }

  };

};