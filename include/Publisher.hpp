// Publisher.hpp
#ifndef PUBLISHER_HPP
#define PUBLISHER_HPP

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

  namespace efdds = eprosima::fastdds::dds;

  class Publisher {
  private:

    //CustomDataType data_;

    efdds::DomainParticipant* participant_;
    efdds::Publisher* publisher_;
    efdds::Topic* topic_;
    efdds::DataWriter* writer_;
    efdds::TypeSupport type_;

    void* data_;

    class PubListener : public efdds::DataWriterListener {
    public:

      PubListener(): matched_(0) {}

      ~PubListener() override {}

      // DataWriter’s listener callback
      void on_publication_matched(efdds::DataWriter*, const efdds::PublicationMatchedStatus& info) override {
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

    Publisher(efdds::TopicDataType* topicDataType);

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
