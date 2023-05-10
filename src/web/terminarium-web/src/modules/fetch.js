import { initializeApp } from "firebase/app";                   // import firebase application
import { getDatabase, ref, onValue } from "firebase/database";  // import firebase database functionality
import { firebaseConfig } from "@/modules/config.js";
import { formatDateTime } from "@/modules/utils.js";

const app       = initializeApp(firebaseConfig);    // initialize firebase application via the configuration object
const database  = getDatabase();                    // initialize database instance

/**
 * Fetch data entries from the database for the last specified number of hours
 * It is used to populate the chart with range-based data
 * @param {number} hours - number of hours to go back in time
 * @returns {Promise} a promise that resolves to an array of objects with the following structure:
 * @example [{sensor: "sensor1", timestamp: "01-01-2021;00:00", value: "10"}, ...]
 */
export const readSensorRange = (hours) => {
  let result = {};                                                  // array to store the results
  const now = new Date();                                           // get the current time

  return new Promise((resolve) => {
    const reference = ref(database, "/terminarium/sensor/");        // get the access to all the sensors' timestamps
    onValue(reference, (DBnode) => {
      DBnode.forEach((sensor) => {                            // iterate through all the sensors
        sensor.forEach((timestamp) => {                       // iterate through all the timestamps of each sensor

          const time = formatDateTime(timestamp.key);               // format the timestamp from the database
          const diff = now.getTime() - time.getTime();              // get the diff. between timestamp and current time
          const hourDiff = diff / (1000 * 3600);                    // convert the diff. to hours
          
          // if the difference is less than the specified number of hours, add the entry to the result array
          if (hourDiff < hours) {
            const sensorName = sensor.key;
            const timestampVal = timestamp.key;
            const value = timestamp.val().value;
            
            // Check if an entry for the sensor already exists in the result array
            if (result[sensorName] === undefined) result[sensorName] = [];
            
            // Add the entry to the result array
            result[sensorName].push({
              timestamp: timestampVal,
              value: value
            });
          }
        });
      });
      // populate the promise with the result
      resolve(result);
    });
  });
}