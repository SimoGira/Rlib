// Publisher.hpp
#ifndef PUBLISHER_HPP
#define PUBLISHER_HPP

#pragma once

#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>


namespace rlib {

  // static struct CustomDataType {
  //   void* data;
  //   eprosima::fastdds::dds::TopicDataType* pubSubType;
  // } customData_;

  class Publisher {
  private:

    //CustomDataType data_;

    eprosima::fastdds::dds::DomainParticipant* participant_;
    eprosima::fastdds::dds::Publisher* publisher_;
    eprosima::fastdds::dds::Topic* topic_;
    eprosima::fastdds::dds::DataWriter* writer_;
    eprosima::fastdds::dds::TypeSupport type_;

    void* data_;

    class PubListener : public eprosima::fastdds::dds::DataWriterListener {
    public:

      PubListener(): matched_(0) {}

      ~PubListener() override {}

      // DataWriter’s listener callback
      void on_publication_matched(eprosima::fastdds::dds::DataWriter*, const eprosima::fastdds::dds::PublicationMatchedStatus& info) override {
        if (info.current_count_change == 1) {
            matched_ = info.total_count;
            std::cout << "Publisher matched." << std::endl;
        }
        else if (info.current_count_change == -1) {
            matched_ = info.total_count;
            std::cout << "Publisher unmatched." << std::endl;
        }
        else {
            std::cout << info.current_count_change
                    << " is not a valid value for PublicationMatchedStatus current count change." << std::endl;
        }
      }

      // the number of DataReaders discovered
      std::atomic_int matched_;

    } listener_;

  public:

    Publisher(eprosima::fastdds::dds::TopicDataType* topicDataType);

    virtual ~Publisher();

    //!Initialize the publisher
    bool init(std::string topicName, std::string topicDataTypeName);

    //!Send a publication
    bool publish();

    //!Run the Publisher
    void run(uint32_t samples);

    //!Load your custom message
    void load(void* data);
};



} // rlib

#endif
