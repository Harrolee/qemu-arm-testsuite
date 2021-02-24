# improve with decorators

import paho.mqtt.client as mqtt

topics = {
    # run code with default argument
    'run all' : 'run/#',
    # run the code with speed as an argument
    'speed' : 'run/speed',
}


def on_connect(client, userdata,flags,rc):
    print("Connected with result code "+str(rc))
    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe("$SYS/#")

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    # blindly pritn payload
    print(msg.topic+" "+str(msg.payload))

def connect_to_broker(address='127.0.0.1',port=1883,ttl=60):
    
    # create client object
    client = mqtt.Client(client_id="0")
    client.on_connect = on_connect
    client.on_message = on_message

    client.connect(address, port, ttl)

    client.loop_forever()

def publish(topic):
    message_info = publish(topics[topic], payload=None)
    if message_info.rc != 'MQTT_ERR_SUCCESS':
        return f'failed with {str(message_info.rc)}'
    return 'see directory ____ for test metadata'