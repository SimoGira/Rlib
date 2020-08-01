// Subscriber.hpp
#ifndef SUBSCRIBER_HPP
#define SUBSCRIBER_HPP

#pragma once

#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>
#include <fastdds/dds/subscriber/SampleInfo.hpp>

namespace rlib {
  class Subscriber {
  private:

    eprosima::fastdds::dds::DomainParticipant* participant_;
    eprosima::fastdds::dds::Subscriber* subscriber_;
    eprosima::fastdds::dds::DataReader* reader_;
    eprosima::fastdds::dds::Topic* topic_;
    eprosima::fastdds::dds::TypeSupport type_;

    //static void* dataSub_;

    class SubListener : public eprosima::fastdds::dds::DataReaderListener {
    public:

        SubListener();

        ~SubListener() override {}

        void on_subscription_matched(eprosima::fastdds::dds::DataReader*, const eprosima::fastdds::dds::SubscriptionMatchedStatus& info) override;

        void on_data_available(eprosima::fastdds::dds::DataReader* reader) override;

        void* data_;

        std::atomic_int samples_;

    } listener_;

  public:

    Subscriber(eprosima::fastdds::dds::TopicDataType* topicDataType);

    virtual ~Subscriber();

    //!Initialize the subscriber
    bool init(std::string topicName, std::string topicDataTypeName);

    //!Run the Subscriber
    void run(uint32_t samples);
  };
} // rlib

#endif
