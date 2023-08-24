#pragma once

namespace BHAS {

  class Action {

    public:
      enum class Type {
        ENTITY_ACTION = 0x00,
        // For base class Entity
        RESET         = 0x01,
        ENABLE        = 0x02,
        DISABLE       = 0x03
      };

  };

};