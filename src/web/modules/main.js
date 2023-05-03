import { writeToDB } from "./dataHandler.js";
import { connect } from './mqtt.js';


connect();                      // call function to start listening for incoming MQTT messages and save incoming data

setInterval(writeToDB, 60000);  // write saved data to database every minute
                              

