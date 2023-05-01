import mqtt from 'mqtt';
import { handleData } from "dataHandler";

// define the MQTT client and connect to the broker
const options = {
    host: '192.168.1.148', // replace with the IP address of your MQTT broker
    port: 1883             // replace with the port number of your MQTT broker
  };

// connect to the  broker
const client = mqtt.connect(options);

// subscribe to sensor topics and call function to handle incoming data
function connect() {
    client.on('connect', function () {
      console.log('Connected to MQTT broker!');
      client.subscribe('/terminarium/sensor/temperature');
      client.subscribe('/terminarium/sensor/humidity');
      client.subscribe('/terminarium/sensor/vibration');
      client.subscribe('/terminarium/sensor/moisture');
      client.subscribe('/terminarium/sensor/light');
      client.subscribe('/terminarium/sensor/loudness');
    });
  
    client.on('message', function (topic, message) {
      console.log('Received message:', message.toString());
      handleData(message.toString());
    }); 
  }

// export the connect function for use in other modules
module.exports = {
    connect
  };
