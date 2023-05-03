#!/usr/bin/env node

import { initializeApp } from "firebase/app";                                             // import firebase application
import { getDatabase, ref, onValue, set, goOnline, goOffline } from "firebase/database";  // import firebase database functionality
import { config as dotEnvConfig } from "dotenv";                                          // import dotenv configuration (aliased)

dotEnvConfig();        // initialize dotenv configuration

/** @const {Object} firebaseConfig
 * The firebase configuration object is represtented by secrets obtained from the 
 * .env file; thus, integrity of the firebase configuration is maintained. The configuration
 * values are shared with the team members via a secure channel and/or obtained from the Google
 * Firebase Console. */

const firebaseConfig = {
  apiKey:             process.env.API_KEY,
  authDomain:         process.env.AUTH_DOMAIN,
  databaseURL:        process.env.DATABASE_URL,
  projectId:          process.env.PROJECT_ID,
  storageBucket:      process.env.STOREAGE_BUCKET,
  messagingSenderId:  process.env.MESSAGING_SENDER_ID,
  appId:              process.env.APP_ID,
  measurementId:      process.env.MEASUREMENT_ID,
};

const app       = initializeApp(firebaseConfig);                       // initialize firebase application via the configuration object
const database  = getDatabase();                                       // initialize database instance

/** @function onValue
 * The onValue function is a listener that is triggered when the value of the database
 * reference changes. The function is used to determine whether the application is connected
 * to the database or not. The function is used to log the status of the database connection
 * to the console. The path '.info/connected' is a special path that is provided by the
 * firebase database. The path is used to determine whether the application is connected to
 * the database or not.
 * 
 * @param {Object} ref - the ref parameter is a reference to the database instance
 * @param {snapshot} snapshot - the snapshot parameter is a snapshot of the database instance
 */

const printConnectionStatus = (connected) => {                           // function that prints message based on connection status
  if (connected) {
    console.log("Database connection established.");
  } else {
    console.log("Database connection lost.");
  }
};

onValue(ref(database, ".info/connected"), (snapshot) => {              // use the onValue function to listen for changes to the database connection state
  printConnectionStatus(snapshot.val());                               // call the printConnectionStatus function with the current connection status
});

const isDatabaseConnected = () => {                                    // function that returns a boolean based on connection status
  return new Promise((resolve) => {                                    // create new promise and pass a function that takes a 'resolve' argument
    onValue(ref(database, ".info/connected"), (snapshot) => {          // use onValue function to listen for changes to the database connection state
      resolve(snapshot.val() == true)                                  // resolve the promise with a boolean based on connection status
    });
  });
};

export function write(nodeName, value) {                               // function for writing to database
  isDatabaseConnected().then((connected) => {                          // check if database is connected
    if (connected) {                                                   // if connected to database, proceed
      const reference = ref(database, nodeName);                       // create reference with given node name parameter  
      set(reference, {value: value});                                  // write values to database under referenced node name
      console.log(`Database entry updated: '${nodeName}'`)             // print confirmation message to console
    } else {                                                           // if not connected to database
      console.log(`Could not write entry to database: '${nodeName}'`); // print error message
    }
  });
}

