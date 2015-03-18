#include "helloworld_DCPS.hpp"

int main(int argc, char *arv[])
{
    /* Create DomainParticipant - this connects the application to DDS */
    dds::domain::DomainParticipant dp( org::opensplice::domain::default_id() );

    /* Create a topic - this is like a db table or queue (depending on QoS). */
    dds::topic::Topic<Hello::World> topic( dp, "HelloWorld" );

    /* Create a datawriter - lets the application publish to a topic */
    dds::pub::DataWriter<Hello::World> dw( dp, topic, topic.qos() );

    /* Create and write a sample */
    dw << Hello::World(0, "Hello World");
    
    return 0;
}
