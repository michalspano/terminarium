#!/usr/bin/env node

import { initializeApp } from "firebase/app";                   // import firebase application
import { getDatabase, ref, onValue } from "firebase/database";  // import firebase database functionality
import { config as dotEnvConfig } from "dotenv";                // import dotenv configuration (aliased)

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

const app       = initializeApp(firebaseConfig);    // initialize firebase application via the configuration object
const database  = getDatabase();                    // initialize database instance

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
 * NOTE: The function is used for debugging purposes only. */

onValue(ref(database, ".info/connected"), (snapshot) => {
    if (snapshot.val() === true) {
        console.log("Database connection established.");
    } else {
        console.log("Database connection lost.");
    }
});

// export the firebase object for use in other modules
module.exports = {
    app
  };
