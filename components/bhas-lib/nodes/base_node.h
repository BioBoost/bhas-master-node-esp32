#pragma once

#include <stdint.h>
#include <string>

namespace BHAS::Nodes {

  class BaseNode {

    public:
      BaseNode(uint8_t id);

    // public:
    //   uint64_t last_seen();

    public:
      void indicate_active();

    public:
      uint8_t id() const;

    public:
      std::string to_string();

    private:
      uint8_t _id = 0;
      time_t _lastActiveTime = 0;
  };

};