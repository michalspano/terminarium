export let sensorValues = new Map();                      // declare map to contain sensor data and make it exportable

export function handleData(topic, sensorData) {           // function handling incoming messages (parameters are mqtt topic and contents of message)

  sensorValues.set(topic, sensorData);                    // add newly received value into the map (topic as key, message contents as value)

  for (const [key, value] of sensorValues.entries()) {    // loop through each map entry
    console.log(`${key}: ${value}`);                      // print key (topic) and value (sensor data) to console
  }
}

// TODO: add timestamps to the data