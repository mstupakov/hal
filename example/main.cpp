#include <iostream>
#include <string>
#include <map>

#include "iboard.h"
#include "iport.h"

int main(int argc, char *argv[]) {
  try {
    hal::BoardId id = hal::BoardId::E_DUMMY;

    std::map<std::string, hal::BoardId> map = {
      { "dummy", hal::BoardId::E_DUMMY }
    };

    if (argc > 1) {
      id = map.at(argv[1]);
    }

    hal::UIBoard board = hal::IBoard::GetBoard(id);
    hal::UIPort ports = board->GetIPort();

    ports->Subscribe([](hal::port::Event, hal::port::Ids){});

    for (auto p : *ports) {
      std::cerr << __PRETTY_FUNCTION__ << ": " << static_cast<int> (*p) << '\n';
    }

    auto p0 = ports->GetPort(1);
    std::cerr << __PRETTY_FUNCTION__ << ": " << p0->GetLogicPort() << '\n';

    auto p1 = ports->GetPort(2);
    std::cerr << __PRETTY_FUNCTION__ << ": " << p1->GetLogicPort() << '\n';

    auto p2 = ports->GetPort(3);
    std::cerr << __PRETTY_FUNCTION__ << ": " << p2->GetLogicPort() << '\n';

    p0->Add({p1, p2});
    p0->Sub({p1, p2});

    auto [speed, duplex, state] = p0->GetStatus();

    auto p10 = ports->GetPort(10);
  } catch (hal::Exception &e) {
    std::cerr << "Error: " << e.what() << '\n';
    std::cerr << " - RC: " << e.GetReason() << '\n';
  }

  return 0;
}