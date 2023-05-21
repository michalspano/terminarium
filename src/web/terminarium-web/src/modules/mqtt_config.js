// *** MQTT Configuration for the Web Client - Sensor Readings ***

import { MQTTClientInit } from '@/modules/utils.js'

export const MQTTClient = MQTTClientInit();  // Initializes the MQTT client.

// Called when the connection is made
const onConnect = () => {
    console.log(`Connected to ${MQTTClient.host}:${MQTTClient.port}`) // log the connection
    MQTTClient.subscribe("/terminarium/sensor/#");                // subscribe to the topic
}

/**
 * This function is called when the connection is lost
 * @param {*} responseObject - the response object from the MQTT broker
 * @returns {void}
 * 
 * Adapted from: // Adapted from: https://www.hivemq.com/blog/mqtt-client-library-encyclopedia-paho-js/
 */
const onConnectionLost = (responseObject) => {
    if (responseObject.errorCode !== 0) {
        console.log('Lost connection: ' + responseObject.errorMessage)
    }
}

// Callbacks for the MQTT client
MQTTClient.onConnectionLost = onConnectionLost;
// Enforce SSL - a secure connection
MQTTClient.connect({ onSuccess: onConnect, useSSL: true})