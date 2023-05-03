import { write } from './database.js'

let sensorValues = new Map();                                        // declare map to contain sensor data

export function saveData(topic, message) {                           // function handling incoming messages (parameters are mqtt topic and contents of message)

  const sensorData = {                                               // create object containing sensor data and timestamp
    data: message,                                                   // actual sensor data
    timestamp: createTimestamp()                                     // call function to generate formatted timestamp
  };

  sensorValues.set(topic, sensorData);                               // add newly received value into the map (topic as key, message contents as value)
  printToConsole(sensorValues);                                      // call function to print map entries to console
}

export function writeToDB() {                                        // function that sends sensor data 
  for (const [key, value] of sensorValues.entries()) {               // loop through each map entry
    const nodeName = (`${ key }/${ value.timestamp }`);              // define node name as the mqtt topic plus the timestamp
    write(nodeName, value.data);                                     // call write function from database.js using given parameters
  }
  // TODO: consider adding a 'last updated' child node of sensors 
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
}