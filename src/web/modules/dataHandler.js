import { write } from './database.js'

/** @sensorValues
 * Sensor data is stored in a map with 6 entries corresponding to 6 sensor types.
 * For each entry, the key is the mqtt topic and the value is an object containing the
 * sensor data and a timestamp of when the data is received.
 * Having the unique sensor topics as keys allows both retrieval of specific sensor 
 * data and overwriting it when new incoming data is received. */
var sensorValues = new Map();                                        // declare map to contain sensor data

/**@vibrationCount
 * Vibration data is a boolean value, useful for real-time monitoring but not
 * for data analysis. Therefore we separately store the number of vibration 
 * occurrences (i.e. 'true' values) during each interval and write this number 
 * to the database instead of the boolean value stored in the sensorValues map.*/
var vibrationCount = 0;

export function saveData(topic, message) {                           // function handling incoming messages (parameters are mqtt topic and contents of message)

  const sensorData = {                                               // create object containing sensor data and timestamp
    data: message,                                                   // actual sensor data
    timestamp: createTimestamp()                                     // call function to generate formatted timestamp
  };

  if (topic.endsWith('vibration') && message == 'true') {            // check if incoming message is from vibration sensor and message indicates vibration is occurring 
    vibrationCount++;                                                // if so, increment the vibration counter by 1
  }

  sensorValues.set(topic, sensorData);                               // add newly received value into the map (topic as key, message contents as value)
  printToConsole();                                                  // call function to print map entries to console
} 

export function writeToDB() {                                        // function that sends sensor data (called once every interval)
  for (const [key, value] of sensorValues.entries()) {               // loop through each map entry
    const nodeName = (`${ key }/${ value.timestamp }`);              // define node name as the mqtt topic plus the timestamp
    if(!(key.endsWith('vibration'))) {                               // check if loop is on the vibration data entry
      write(nodeName, value.data);                                   // if not, call write to DB function using data value from the map
    } else {                                                         
      write(nodeName, vibrationCount);                               // if so, call write to DB function using vibrationCount data instead
    }
  }
  vibrationCount = 0;                                                // reset the vibration counter for the next interval
}

function createTimestamp() {                                         // function returns formatted timestamp
  const date = new Date();                                           // create new Date object with current date/time
  
  const options = {                                                  // define date/time formatting options
    day: '2-digit',
    month: '2-digit',
    year: 'numeric',
    hour: '2-digit',
    minute: '2-digit',
    hour12: false
  };
                                      
  let formattedDate = date.toLocaleString('en-GB', options);         // format using defined options
  formattedDate = formattedDate.replace(',',';').replace(/\s+/g,''); // replace ',' between time and date and remove whitespace
  formattedDate = formattedDate.replace(/\//g, '-');                 // replace '/' with '-' in string to not cause node name issues when writing to DB
  return formattedDate;                                              // return formatted timestamp
} 

function printToConsole() {                                          // function to print map entries to console
  console.log('Current sensor values:');                             // print heading to console
  for (const [key, value] of sensorValues.entries()) {               // loop through each map entry
    console.log(`${ key }: ${ value.data } at ${ value.timestamp}`); // print key (topic) and value (sensor data) of entry to console
  }
  console.log("Vibration count: " + vibrationCount);                 // print number of vibration occurrences so far
}