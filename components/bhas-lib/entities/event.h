#pragma once

namespace BHAS {

  class Event {

    public:
      enum class Type {
        BOOT =          0x00,
        ALIVE =         0x01,
        BUTTON =        0x02,
        TEMPERATURE =   0x03
      };

  };

};
