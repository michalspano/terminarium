import mqtt from 'mqtt';                                        // import mqtt client library (install by using npm install mqtt --save)
import { saveData } from './dataHandler.js'                   // import function that sensor data is passed to


const options = {                                               // define the MQTT client and connect to the broker
    host: '***.***.*.***',                                      // replace with the IP address of your MQTT broker
    reconnectPeriod: 1000,                                      // default value for amount of ms between reconnect attempts
    port: 1883                                                  // replace with the port number of your MQTT broker
};
const client = mqtt.connect(options);                           // connect to the mqtt broker

export function connect() {                                     // subscribe to sensor topics and call function to handle incoming data
    client.on('connect', function () {                          // runs once connected to MQTT broker
        console.log('Connected to MQTT broker!');               // print connection message to console
        client.subscribe('/terminarium/sensor/temperature');    // subscribe to all sensor topics
        client.subscribe('/terminarium/sensor/humidity');
        client.subscribe('/terminarium/sensor/vibration');
        client.subscribe('/terminarium/sensor/moisture');
        client.subscribe('/terminarium/sensor/light');
        client.subscribe('/terminarium/sensor/loudness');
    });

    client.on('message', function (topic, message) {            // runs once a message is received
        console.log('Received message:', message.toString());   // print message received to console
        saveData(topic, message.toString());                    // pass topic and sensor data as String to be saved
    });
    client.on('reconnect', function () {                        // runs if client is reconnecting
        console.log('Trying to reconnect')
    });
    client.on('offline', function () {                          // runs if connection is lost
        console.log('Client offline')
    });

}