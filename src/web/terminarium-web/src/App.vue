<script setup>
// Components 
import DefaultPageLayout from '@/components/DefaultPageLayout.vue';
import HomePage from '@/components/HomePage.vue';
import SelectTerrarium from '@/components/SelectTerrariumPage.vue';
import SetSensorRanges from '@/components/SetSensorRanges.vue';
import UserSettings from '@/components/UserSettings.vue';
import Register from '@/components/RegisterPage.vue';

// Functions
import { createTimestamp } from '@/modules/utils.js';
import { write } from "@/modules/database.js";
import { MQTTClient } from "@/modules/mqtt_config.js";

// Import the "computed()" method from Vue Composition API. 
// Used inside the "provide()" option/function.
// More info: https://vuejs.org/api/reactivity-core.html#computed
import { computed } from 'vue'
</script>

<template>
  <div id="app">
    <!-- Component containing the elements (components) that are always part of the website's layout -->
    <DefaultPageLayout @access-button-event="handleAccessButtonEvent" />

    <!-- The "KeepAlive" tag wraps the loaded components and caches them to maintain state 
      (keeps the same component instance alive). Only components that are "included" will be cached. -->
    <KeepAlive include="SelectTerrarium, SetSensorRanges">
      <component v-bind:is="currentView" @accRegisterSuccess="handleAccRegistration"/>
    </KeepAlive>
  </div>
</template>

<script>
// Decide which component to load - based on defined paths (routes) correlating to the URL hash fragment.
const routes = {
  "/": HomePage,
  "/set-sensor-ranges": SetSensorRanges,
  "/settings": UserSettings,
  "/register-account": Register,
  "/your-terrariums": SelectTerrarium,
}

export default {
  components: {
    DefaultPageLayout,
    HomePage,
    SelectTerrarium,
    SetSensorRanges,
    UserSettings,
    Register
  },

  data() {
    return {
      currentPath: window.location.hash,    // Initialise currentPath as the current URL hash fragment.
      isLoggedIn: false,                    // Initialise the User's login status to false.
      isDisplayingRealTimeData: false,      // Initialise the display of real-time data to false.

      /** @sensorValues
       * Sensor data is stored in a object with 6 entries corresponding to 6 sensor types.
       * For each entry, the key is the mqtt topic and the value is an object containing the
       * sensor data and a timestamp of when the data is received.
       * Having the unique sensor topics as keys allows both retrieval of specific sensor 
       * data and overwriting it when new incoming data is received. */
      sensorValues: {},

      /**@vibrationCount
     * Vibration data is a boolean value, useful for real-time monitoring but not
     * for data analysis. Therefore we separately store the number of vibration 
     * occurrences (i.e. 'true' values) during each interval and write this number 
     * to the database instead of the boolean value stored in the sensorValues object.*/
      vibrationCount: 0
    }
  },

  mounted() {
    // Add an eventListener to the "hashchange" event.
    // The event is triggered anytime the URL hash fragment changes.
    // Automatically updates currentPath to the new hash value.
    window.addEventListener("hashchange", () => this.currentPath = window.location.hash);

    // ======================== MQTT ========================

    /**
     * The current analysis is, that the App.vue will continuously be connected to the MQTT broker,
     * hence, the data will be collected (and saved) even when the user is on different sub-pages. 
     * This is an event handler for when a message is received
     * @param {Object} message - the message object with the data from the MQTT broker
     * @returns {void}
     */
    MQTTClient.onMessageArrived = (message) => {
      this.saveData(message.destinationName, message.payloadString); // call function to save the data
    }

    // ======================== Database ========================

    // The read data entries are transmitted to the database every DELAY milliseconds.
    const DELAY = 5 * 60_000; // 5 minutes
    this.writeToDB(); setInterval(this.writeToDB, DELAY);
  },

  provide() {
    return {
      // This prop is "injected" by components further down in the component hierarchy.
      // Using the imported "computed()" API from Vue ensures that the prop is reactive, meaning:
      // when the boolean changes, the change is reflected in any sub-component injecting it.
      // This applies both for the "isLoggedIn" and "sensorValues" props.

      isLoggedIn: computed(() => this.isLoggedIn),

      // The "sensorValues" that propagates down the component hierarchy is a computed property.
      // However, its structure must be changed to be compatible with the "MonitorTerrariumPage.vue" component.
      // Example: { "/terminarium/sensor/temperature": { data: 25, timestamp: dd-mm-yyyy;hh:mm } } -> { temperature: 25 }
      // Reason: the topic and the timestamp are not needed in the MonitorTerrariumPage.vue component. However, here, they are
      // needed to keep track of the latest values for each sensor type, and similarly append the timestamp with the data
      // to the database.
      sensorValues: computed(() => {
        const sensorValuesTmp = { ...this.sensorValues }    // copy the sensorValues object
        for (const key in sensorValuesTmp) {                // iterate over the keys in the object
          const value = sensorValuesTmp[key];               // obtain the value for the key
          const newKey = key.split("/").pop();              // transform the key to only contain the sensor type

          delete sensorValuesTmp[key];                      // delete the old key-value pair
          sensorValuesTmp[newKey] = value.data;             // add the new key-value pair
        }
        return sensorValuesTmp;
      })
    }
  },

  computed: {
    currentView() {
      // Slice "currentPath" at index 1 to remove the "#" and compare it to the defined "routes".
      // If slice() results in a falsy value (empty String) - display the HomePage. (First OR-condition)
      // If the component retrieved from routes is "undefined", due to the String not being formatted correctly,
      // we - again, display the HomePage instead. (Second OR-condition)
      const componentToLoad = routes[this.currentPath.slice(1) || "/"] || HomePage  // If desired; replace "HomePage" with a "404 not found"-component. 

      // Validate that the User has access (is logged in) for certain components to be displayed.
      // Otherwise the HomePage is displayed.
      if (!this.isLoggedIn && (componentToLoad === SelectTerrarium || componentToLoad === SetSensorRanges || componentToLoad === UserSettings)) {
        return HomePage   // TODO: replace HomePage with "401 unauthorized"-component
      } else {
        return componentToLoad
      }
    }
  },

  methods: {
    toggleLoginStatus() {
      this.isLoggedIn = !this.isLoggedIn
    },

    // Method for when the AccessButton-component has been clicked (login/logout button).
    // This event propagates through: AccessButton --> Header --> DefaultPageLayout --> App (this file). 
    // In both of the intermediary components the event is re-emitted.
    handleAccessButtonEvent() {
      if (this.isLoggedIn) {
        window.location.href = "#/"   // Returns the User to the HomePage when they log out.
        this.toggleLoginStatus()
      } else if (localStorage.getItem("username") && localStorage.getItem("password")) {
        this.toggleLoginStatus()
      } else {
        window.location.href="#/register-account"     // TODO: replace this line with a "window.location.href" redirecting to the login page, IF it's added.
      }
    },
    /**
     * This function saves the sensor data to the sensorValues object
     * @param {String} topic - topic of the message
     * @param {String} message - payload of the message
     */
    saveData(topic, message) {                            // function handling incoming messages (parameters are mqtt topic and contents of message)
      const sensorData = {                                                // create object containing sensor data and timestamp
        data: message,                                                    // actual sensor data
        timestamp: createTimestamp()                                      // call function to generate formatted timestamp
      };

      if (topic.endsWith('vibration') && message == 'true') {             // check if incoming message is from vibration sensor and message indicates vibration is occurring 
        this.vibrationCount++;                                            // if so, increment the vibration counter by 1
      }
      this.sensorValues[topic] = sensorData;                              // add newly received value into the object (topic + { sensor data })
    },

    /**
     * This function writes the sensor data to the database
     * @returns {void}
     */
    async writeToDB() {                                                  // function that sends sensor data (called once every interval)
      for (const key in this.sensorValues) {                     // loop through each entry in the object
        const value = this.sensorValues[key];                   // obtain the value for the key
        const nodeName = (`${key}/${value.timestamp}`);                   // define node name as the mqtt topic plus the timestamp
        if (!(key.endsWith('vibration'))) {                               // check if loop is on the vibration data entry
          write(nodeName, value.data);                                    // if not, call write to DB function using data value from the object
        } else write(nodeName, this.vibrationCount);                           // if so, call write to DB function using vibrationCount data instead
      }
      this.vibrationCount = 0;                                            // reset the vibration counter for the next interval
    },

    // Returns the User to the Home page and changes the login status to "true".
    // Called by the event listener for "accRegisterSuccess" - an event emitted by the "RegisterPage"-component.
    handleAccRegistration() {
      window.location.href="#/"
      this.toggleLoginStatus()
    }
  }
}
</script>
