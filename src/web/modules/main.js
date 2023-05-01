import { app } from "database";
import { connect } from "mqtt";

// use the imported modules to set up application
connect();           // call function to start listening for incoming MQTT messages

app.initializeApp(); // firebase is already initialized object? Do i have to do this?

