// Subscriber.hpp
#ifndef SUBSCRIBER_HPP
#define SUBSCRIBER_HPP

#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>
#include <fastdds/dds/subscriber/SampleInfo.hpp>

#include "Utils.hpp"

namespace rlib {

  namespace efdds = eprosima::fastdds::dds;

  class Subscriber {

  private:

    efdds::DomainParticipant* participant_;
    efdds::Subscriber* subscriber_;
    efdds::DataReader* reader_;
    efdds::Topic* topic_;
    efdds::TypeSupport type_;





  public:

    //static Observer<void*> observer_;

    Subscriber(efdds::TopicDataType* topicDataType);

    virtual ~Subscriber();

    //!Initialize the subscriber
    bool init(std::string topicName, std::string topicDataTypeName);

    //!Run the Subscriber
    void run(uint32_t samples);

    class SubListener : public efdds::DataReaderListener {
    public:

        SubListener();

        ~SubListener() override {}

        void on_subscription_matched(efdds::DataReader*, const efdds::SubscriptionMatchedStatus& info) override;

        void on_data_available(efdds::DataReader* reader) override;

        void* data_;

        std::atomic_int samples_;

    } listener_;


  };


} // rlib

#endif
