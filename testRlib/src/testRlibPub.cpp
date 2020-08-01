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

//#include "../../Rlib/include/Publisher.hpp"
#include "../../include/Publisher.hpp"
#include "TemperaturePubSubTypes.h"

void updateTemperature(Temperature& data){
  float newTemperature = data.temperature()+1.0;
  data.temperature(newTemperature);
}

int main(int argc, char const *argv[]) {

  // Prepare the custom message
  Temperature temperatureData;
  float temperature = 10.0;
  float variance = 0.0;   // 0 is interpreted as variance unknown
  void* data = reinterpret_cast<void*>(&temperatureData);


  // Initialize the publisher
  rlib::Publisher* mypub = new rlib::Publisher(new TemperaturePubSubType());
  std::cout << "Starting publisher." << std::endl;
  uint32_t samples = 10;


  if(mypub->init("MyTopic", "Temperature")) {
    uint32_t samples_sent = 0;

    while (samples_sent < samples) {
      // read data from a sensor and publish it
      updateTemperature(temperatureData);
      mypub->load(data);

      // publish
      if (mypub->publish()) {
          samples_sent++;
          std::cout << "Temperature: " << temperatureData.temperature()
                    << " with variance: " << temperatureData.variance()
                    << " SENT" << std::endl;
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
  }

  delete mypub;

  return 0;
}
