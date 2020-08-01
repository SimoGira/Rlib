/*
 * Tasks:
 *  - Create custom messages
 *  - Stream messages between separate processes
 *  - Send a single message / response between separate processes
 *  - Display published messages in the terminal (A simple tool would read one specific topic/message, a more generic would read any topic/message)
 *  - Display what processes are publishing messages
 *  - Stress test system
 *  - Measure rate of sent messages
 *  - Measure latency of sent messages
 */


#include <iostream>

//#include "../../Rlib/include/Subscriber.hpp"
#include "../../include/Subscriber.hpp"
#include "TemperaturePubSubTypes.h"

int main(int argc, char const *argv[]) {

  std::cout << "Starting subscriber." << std::endl;
  int samples = 10;

  rlib::Subscriber* mysub = new rlib::Subscriber(new TemperaturePubSubType());

  if(mysub->init("MyTopic", "Temperature")) {
        mysub->run(static_cast<uint32_t>(samples));
  }

  delete mysub;

  return 0;
}
