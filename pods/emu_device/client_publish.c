/*
Implementation of mqqt client publish v5.0 from 
https://github.com/eclipse/mosquitto/blob/master/examples/publish/basic-1.c
*/

#include <mosquitto.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
    struct mosquitto *mosq;
    int rc;
    
    mosquitto_lib_init();

/*
Docs:
    Parameters:
    mosq - a valid mosquitto instance.
    mid - pointer to an int. If not NULL, the function will set this
    to the message id of this particular message. This can be then
    used with the publish callback to determine when the message
    has been sent.
    Note that although the MQTT protocol doesn't use message ids
    for messages with QoS=0, libmosquitto assigns them message ids
    so they can be tracked with this parameter.
    topic - null terminated string of the topic to publish to.
    payloadlen - the size of the payload (bytes). Valid values are between 0 and
    268,435,455.
    payload - pointer to the data to send. If payloadlen > 0 this must be a
    valid memory location.
    qos - integer value 0, 1 or 2 indicating the Quality of Service to be
    used for the message.
    retain - set to true to make the message retained.
*/
   // rc = mosquitto_publish(mosq,)
}