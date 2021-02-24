/*
Implementation of mqqt client v5.0 from 
https://github.com/eclipse/mosquitto/blob/master/examples/subscribe/basic-1.c
*/

#include <mosquitto.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

// callback for when the client receives a CONNACK message from the broker
void on_connect(struct mosquitto *mosq, void *obj, int reason_code) 
{
    int rc;
    /* Print out the connection result. mosquitto_connack_string() produces an
    * appropriate string for MQTT v3.x clients, the equivalent for MQTT v5.0
    * clients is mosquitto_reason_string().
    */
    printf("on_connect: %s\n", mosquitto_reason_string(reason_code));
    if(reason_code != 0){
        // if the connection fails for any reason, disconnect.
        // without mosquitto_disconnect(m), mosquitto will try to reconnect forever
        mosquitto_disconnect(mosq);
    }

    /* Making subscriptions in the on_connect() callback means that if the
    * connection drops and is automatically resumed by the client, then the
    * subscriptions will be recreated when the client reconnects. */
    rc = mosquitto_subscribe(mosq, NULL, "example/temperature", 1);
    if(rc != MOSQ_ERR_SUCCESS){
        fprint(stderr, "Error subscribing: %s\n", mosquitto_strerror(rc));
        // d/c if we can't subscribe, I guess
        mosquitto_disconnect(mosq);
    }
}


void on_subscribe(struct mosquitto *mosq, void *obj, int mid, int qos_count, const int *granted_qos)
{
    int i;
    bool have_subscription = false;

    /* In this example we only subscribe to a single topic at once, but a
	 * SUBSCRIBE can contain many topics at once, so this is one way to check
	 * them all. */
    for(i=0; i<qos_count; i++){
        printf("on_subscribe: %d:granted qos = %d\n", i, granted_qos[i]);
        if(granted_qos[i] <= 2){
            have_subscription = true;
        }
    }
    if(have_subscription == false){
    /* The broker rejected all of our subscriptions, we know we only sent
        * the one SUBSCRIBE, so there is no point remaining connected. */
    fprintf(stderr, "Error: All subscriptions rejected.\n");
    mosquitto_disconnect(mosq);     
    }
}

// this is where the magic happens:
    // get a message
void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg)
{ // perform an action according to the message
    // print the payload
    printf("\n\nTopic: %s\n QoS: %d\n Payload: %s\n\n", msg->topic, msg->qos, (char *)msg->payload);
        // from the struct msg, print the values stored in topic, qos, and payload
}



int main(int arc, char *arv[])
{
    const char hostname[] = "172.0.0.1"; 
    struct mosquitto *mosq;
    int rc;

    mosquitto_lib_init();

	/* Create a new client instance.
	 * id = NULL -> ask the broker to generate a client id for us
	 * clean session = true -> the broker should remove old sessions when we connect
	 * obj = NULL -> we aren't passing any of our private data for callbacks
	 */
    mosq = mosquitto_new(NULL, true, NULL);
    if(mosq == NULL){
        fprintf(stderr, "Error: Out of memory.\n");
    }

    // Configure callbacks
    mosquitto_connect_callback_set(mosq, on_connect);
    mosquitto_subscribe_callback_set(mosq, on_subscribe);
    mosquitto_message_callback_set(mosq, on_message);

    // this the magic right here:
    /* Connect to a broker, the second argument of mosquitto_connect()
        This call makes the socket connection but it does not complete the Connect/CONNACK flow.
        We need to use mosquitto_loop_start() or mosquitto_loop_forever() to process net traffic 
        
     docs:
        port - the network port to connect to. Usually 1883.
        keepalive - the number of seconds after which the broker should send a PING
        message to the client if no other messages have been exchanged in that time.   
    */

    rc = mosquitto_connect(mosq, hostname, 1883, 60);
    if(rc != MOSQ_ERR_SUCCESS){
        mosquitto_destroy(mosq);
        fprintf(stderr, "Error: %s\n", mosquitto_strerror(rc));
        return 1;
    }

    // diversion from example. loop_start creates a new thread where _loop_forever calls the connection again forever
    mosquitto_loop_start(mosq);

    mosquitto_lib_cleanup();
    return 0;
}


// general pattern in C: import library. Instantiate object. Construct reactions to events that occur via the object.
        // --> "Callback structure"