// *** Database Functionality Module ***

import { initializeApp } from "firebase/app";                                             // import firebase application
import { getDatabase, ref, onValue, set } from "firebase/database";  // import firebase database functionality
import { firebaseConfig } from "./config.js";

const app       = initializeApp(firebaseConfig);                       // initialize firebase application via the configuration object
const database  = getDatabase();                                       // initialize database instance

/** @function isDatabaseConnected
 * When called, this function determines the connection status to the database and 
 * returns a boolean accordingly. It does this by creating a new 'promise' and passing
 * the argument 'resolve', which resolves the 'promise' with a true or false value
 * based on the result of the following onValue operation (explained above). */

const isDatabaseConnected = async () => {                                     
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
 * @param {String} nodeName - String used in reference to the db node where data should be written
 *                            Its value is a concatenation of the sensor's unique mqtt topic and timestamp */

export async function write(nodeName, value) {                               
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
