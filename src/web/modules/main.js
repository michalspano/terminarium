// Module responsible for connecting to MQTT broker and writing data to database
// I.e. collects sensor data from MQTT broker and writes it to the database

import { writeToDB } from "./dataHandler.js";
import { connect } from './mqtt.js';


connect();                      // call function to start listening for incoming MQTT messages and save incoming data

setInterval(writeToDB, 60000);  // write saved data to database every minute
                              

