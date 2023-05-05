#!/usr/bin/env node

import { initializeApp } from "firebase/app";                   // import firebase application
import { getDatabase, ref, onValue } from "firebase/database";  // import firebase database functionality
import { firebaseConfig } from "./utils.js";

const app       = initializeApp(firebaseConfig);    // initialize firebase application via the configuration object
const database  = getDatabase();                    // initialize database instance

// Note: testing purposes only
const HOURS = 24;                                   // number of hours to go back in time when fetching data from the database

/**
 * Function to format date and time from the convention used in the database to the default format
 * It is needed to calculate the time difference between the current time and the time of the last 
 * entry in the database, namely in the @function read(hours) function.
 * @param {string} raw_date - date in the format dd-mm-yyyy;hh:mm fetched from the database
 * @returns {Date} a formatted date object in the default format: yyyy-mm-ddThh:mm
 */
const formatDateTime = (raw_date) => {
  const day     = raw_date.slice(0, 2);
  const month   = raw_date.slice(3, 5) - 1;
  const year    = raw_date.slice(6, 10);
  const hour    = raw_date.slice(11, 13);
  const minute  = raw_date.slice(14, 16);

  return new Date(year, month, day, hour, minute);
}

/**
 * Fetch data entries from the database for the last specified number of hours
 * It is used to populate the chart with range-based data
 * @param {number} hours - number of hours to go back in time
 * @returns {Promise} a promise that resolves to an array of objects with the following structure:
 * @example [{sensor: "sensor1", timestamp: "01-01-2021;00:00", value: "10"}, ...]
 */
export const readSensorRange = (hours) => {
  let result = [];                                                  // array to store the results
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
            result.push({
              sensor: sensor.key,
              timestamp: timestamp.key,
              value: timestamp.val().value
            });
          }

        });
      });
      // populate the promise with the result
      resolve(result);
    });
  });
}

/**
 * Format the fetched data and print it to the console in a human-readable format
 * @param {Array} snapshot - an array of objects
 */
const printToConsole = (snapshot) => {
    for (const entry of snapshot) {
        console.log(`${entry.sensor}: ${entry.value} at ${entry.timestamp}`);
    }
}

// Example usage: fetch data for the last 24 hours
readSensorRange(HOURS).then((snapshot) => {
    printToConsole(snapshot);
});