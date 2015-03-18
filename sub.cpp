#include "helloworld_DCPS.hpp"

class DataHandler {
public:
    DataHandler() { } ;
    void operator() (dds::sub::DataReader<Hello::World>& dr) {
        /* Take all received samples from reader */
        dds::sub::LoanedSamples<Hello::World> samples = dr.take();

        /* Loop through the received samples */
        for (dds::sub::LoanedSamples<Hello::World>::const_iterator
            sample = samples.begin(); sample < samples.end(); ++sample)
        {
            std::cout << "Sample received: id=" 
                      << sample->data().id() 
                      << ", value='" 
                      << sample->data().value() << "'" << std::endl;
        }
    } 
};

int main(int argc, char *arv[])
{
    /* Create DomainParticipant - this connects the application to DDS */
    dds::domain::DomainParticipant dp( 0 );

    /* Create a topic - this is like a db table or queue (depending on QoS). */
    dds::topic::Topic<Hello::World> topic( dp, "HelloWorld" );

    /* Create a datareader - lets the application subscribe to a topic */
    dds::sub::DataReader<Hello::World> dr( dp, topic, topic.qos() );

    /* Create a readcondition which triggers on all samples */
    dds::sub::cond::ReadCondition rc(dr, dds::sub::status::DataState(), DataHandler()) ;

    /* Create a waitset that will block until data is received */
    dds::core::cond::WaitSet ws;

    /* Add the readcondition to a waitset */
    ws += rc;

    /* Start blocking until data is received */
    ws.dispatch();
    
    return 0;
}
