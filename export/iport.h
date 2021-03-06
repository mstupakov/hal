#ifndef IPORT_H__
#define IPORT_H__

#include "common/common.h"
#include "common/port.h"

#include <memory>
#include <list>
#include <map>

namespace hal {
  class IPort {
    std::shared_ptr<GBoard> m_board;
    std::list<std::shared_ptr<port::Port>> m_ports;

    public:
      IPort(std::shared_ptr<GBoard>);

      void Subscribe(port::Notify);
      std::shared_ptr<port::Port> GetPort(unsigned);

      decltype(m_ports)::iterator begin();
      decltype(m_ports)::iterator end();
  };
}

#endif /* IPORT_H__ */
