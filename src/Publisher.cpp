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

#include "Publisher.hpp"
#include <iostream>

namespace rlib {

  Publisher::Publisher(eprosima::fastdds::dds::TopicDataType* topicDataType)
          : participant_(nullptr)
          , publisher_(nullptr)
          , topic_(nullptr)
          , writer_(nullptr)
          , type_(topicDataType)
  {}

  Publisher::~Publisher() {
    if (writer_ != nullptr) {
        publisher_->delete_datawriter(writer_);
    }

    if (publisher_ != nullptr) {
        participant_->delete_publisher(publisher_);
    }

    if (topic_ != nullptr) {
        participant_->delete_topic(topic_);
    }

    eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->delete_participant(participant_);
  }

  bool Publisher::init(std::string topicName, std::string topicDataTypeName) {
    //hello_.index(0);
    //hello_.message("HelloWorld");

    eprosima::fastdds::dds::DomainParticipantQos participantQos;
    participantQos.name("Participant_publisher");
    participant_ = eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->create_participant(0, participantQos);

    if (participant_ == nullptr) {
        return false;
    }

    // Register the data Type in the DomainParticipant.
    type_.register_type(participant_);

    // Create the publications Topic
    topic_ = participant_->create_topic(topicName, topicDataTypeName, eprosima::fastdds::dds::TOPIC_QOS_DEFAULT);

    if (topic_ == nullptr) {
        return false;
    }

    // Create the Publisher
    publisher_ = participant_->create_publisher(eprosima::fastdds::dds::PUBLISHER_QOS_DEFAULT, nullptr);

    if (publisher_ == nullptr) {
        return false;
    }

    // Create the DataWriter
    writer_ = publisher_->create_datawriter(topic_, eprosima::fastdds::dds::DATAWRITER_QOS_DEFAULT, &listener_);

    if (writer_ == nullptr) {
        return false;
    }
    return true;
  }

  bool Publisher::publish() {
    if (data_ == nullptr) {
      return false;
    }
    if (listener_.matched_ > 0) {
        //hello_.index(hello_.index() + 1);
        writer_->write(&data_);
        return true;
    }
    return false;
  }

  void Publisher::run(uint32_t samples) {
    uint32_t samples_sent = 0;
    while (samples_sent < samples) {
        if (publish()) {
            samples_sent++;
            //std::cout << "Message: " << hello_.message() << " with index: " << hello_.index()
            std::cout  << " SENT" << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
  }

  // TODO: Call this before publish
  void Publisher::load(void* data){
    data_ = data;
  }




} // rlib
