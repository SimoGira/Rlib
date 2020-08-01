#include <iostream>
#include "Subscriber.hpp"

namespace rlib {
  Subscriber::Subscriber(eprosima::fastdds::dds::TopicDataType* topicDataType)
      : participant_(nullptr)
      , subscriber_(nullptr)
      , topic_(nullptr)
      , reader_(nullptr)
      , type_(topicDataType)
  {}

  Subscriber::~Subscriber() {
      if (reader_ != nullptr) {
          subscriber_->delete_datareader(reader_);
      }

      if (topic_ != nullptr) {
          participant_->delete_topic(topic_);
      }

      if (subscriber_ != nullptr) {
          participant_->delete_subscriber(subscriber_);
      }
      eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->delete_participant(participant_);
  }


  bool Subscriber::init(std::string topicName, std::string topicDataTypeName) {
      eprosima::fastdds::dds::DomainParticipantQos participantQos;
      participantQos.name("Participant_subscriber");
      participant_ = eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->create_participant(0, participantQos);

      if (participant_ == nullptr) {
          return false;
      }

      // Register the Type
      type_.register_type(participant_);

      // Create the subscriptions Topic
      topic_ = participant_->create_topic(topicName, topicDataTypeName, eprosima::fastdds::dds::TOPIC_QOS_DEFAULT);

      if (topic_ == nullptr) {
          return false;
      }

      // Create the Subscriber
      subscriber_ = participant_->create_subscriber(eprosima::fastdds::dds::SUBSCRIBER_QOS_DEFAULT, nullptr);

      if (subscriber_ == nullptr) {
          return false;
      }

      // Create the DataReader
      reader_ = subscriber_->create_datareader(topic_, eprosima::fastdds::dds::DATAREADER_QOS_DEFAULT, &listener_);

      if (reader_ == nullptr) {
          return false;
      }

      return true;
  }


  void Subscriber::run(uint32_t samples) {
      while(listener_.samples_ < samples) {
          std::this_thread::sleep_for(std::chrono::milliseconds(100));
      }
  }


  //###########################################################################
  // SubListener
  //###########################################################################

  Subscriber::SubListener::SubListener(): samples_(0) {}

  void Subscriber::SubListener::on_subscription_matched(eprosima::fastdds::dds::DataReader*, const eprosima::fastdds::dds::SubscriptionMatchedStatus& info) {
      if (info.current_count_change == 1) {
          std::cout << "Subscriber matched." << std::endl;
      } else if (info.current_count_change == -1) {
          std::cout << "Subscriber unmatched." << std::endl;
      } else {
          std::cout << info.current_count_change
                  << " is not a valid value for SubscriptionMatchedStatus current count change" << std::endl;
      }
  }

  void Subscriber::SubListener::on_data_available(eprosima::fastdds::dds::DataReader* reader) {
      eprosima::fastdds::dds::SampleInfo info;
      if (reader->take_next_sample(&data_, &info) == ReturnCode_t::RETCODE_OK) {
        if (info.instance_state == eprosima::fastdds::dds::ALIVE) {
          samples_++;
          //std::cout << "Temperature: " << data_.temperature() << " with variance: " << data_.variance()
          //          << " RECEIVED." << std::endl;
                    std::cout <<  samples_ << " RECEIVED." << std::endl;
        }
      }
  }
}
