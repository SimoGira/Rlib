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
#include "../../include/Utils.hpp"

void printMessageCallback(void* data){
  if (data != nullptr) {
    Temperature* temperatureData =  reinterpret_cast<Temperature*>(&data);
    std::cout << "Temperature: " << temperatureData->temperature()
              << " with variance: " << temperatureData->variance()
              << " RECEIVED." << std::endl;
  }
}


int main(int argc, char const *argv[]) {

  std::cout << "Starting subscriber." << std::endl;
  int samples = 10;

  rlib::Subscriber* mysub = new rlib::Subscriber(new TemperaturePubSubType());

  if(mysub->init("MyTopic", "Temperature")) {
    while(mysub->listener_.samples_ < samples) {
        printMessageCallback(mysub->listener_.data_);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    //    mysub->run(static_cast<uint32_t>(samples));
  }

  delete mysub;

  return 0;
}
