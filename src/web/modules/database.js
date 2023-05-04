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

const printConnectionStatus = (connected) => {                         // function that prints message based on connection status
  if (connected) {
    console.log("Database connection established.");
  } else {
    console.log("Database connection lost.");
  }
};

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
 * 
 * * NOTE: The function is used for debugging purposes only. */

onValue(ref(database, ".info/connected"), (snapshot) => {             
  printConnectionStatus(snapshot.val());                               
});

/** @function isDatabaseConnected
 * When called, this function determines the connection status to the database and 
 * returns a boolean accordingly. It does this by creating a new 'promise' and passing
 * the arguement 'resolve', which resolves the 'promise' with a true or false value
 * based on the result of the following onValue operation (explained above). */

const isDatabaseConnected = () => {                                     
  return new Promise((resolve) => {                                    
    onValue(ref(database, ".info/connected"), (snapshot) => {          
      resolve(snapshot.val() == true)                                  
    });
  });
};

/** @function write
 * This function writes data to the database. First it calls isDatabaseConnected 
 * function and, when its 'promise' is resolved, it passes 'connected' argument
 * as the resulting boolean value. If connected, the function will proceed to
 * write to database using the parameters passed to it:
 * 
 * @param {boolean} connected - value indicating whether client is connected to Firebase Realtime Database 
 * @param {String} value - sensor data to be written to the database (received as a String)
 * @param {String} nodeName - String uased in reference to the db node where data should be written
 *                            Its value is a concatenation of the sensor's unique mqtt topic and timestamp */

export function write(nodeName, value) {                               
  isDatabaseConnected().then((connected) => {                          
    if (connected) {                                                   
      const reference = ref(database, nodeName);                       
      set(reference, {value: value});                                  
      console.log(`Database entry updated: '${nodeName}'`)             
    } else {                                                           
      console.log(`Could not write entry to database: '${nodeName}'`); 
    }
  });
}

