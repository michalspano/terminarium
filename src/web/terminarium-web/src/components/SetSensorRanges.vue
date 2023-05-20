<!----------------------------------------------------------------------------------
   The "SetSensorRanges" component is used to
   set the desired environment ranges for the terrarium enclosures.
   The component validates the ranges and saves them in local storage.
----------------------------------------------------------------------------------->
<template>
  <!----------------------------------------------------------------------------------
   The page uses a grid structure(defined in css).
   v-model is used to bind the input fields with their respective data properties.
   The elements are styled using css.
----------------------------------------------------------------------------------->
  <div class="Choose_ranges_box">
    <button type="button" class="set_ranges_buttons" @click="goToMonitorTerrarium">Monitor Terrarium</button>
    <div class="grid-container">
      <!-------------------------------------------------*MOISTURE*-------------------------------------------------->
      <div class="grid-item">
        <p><b>Set</b> your desired <b>minimum </b> and <b> maximum </b><b style="color: gold">Moisture %</b></p>
      </div>

      <div class="grid-item">
        <label class="set_label" for="minimum_moisture_value">Minimum:</label>
        <input class="set_field" type="number" id="minimum_moisture_value" v-model="moisture_min" min="0" max="100">
      </div>

      <div class="grid-item">
        <label class="set_label" for="maximum_moisture_value">Maximum:</label>
        <input class="set_field" type="number" id="maximum_moisture_value" v-model="moisture_max" min="0" max="100">
      </div>


      <!--------------------------------------------------*LIGHT*----------------------------------------------------->
      <div class="grid-item">
        <p><b>Set</b> your desired <b>minimum </b> and <b> maximum </b><b style="color: gold">Light level </b></p>
      </div>

      <div class="grid-item">
        <label class="set_label" for="minimum_light_value">Minimum:</label>
        <input class="set_field" type="number" id="minimum_light_value" v-model="light_min" min="0" max="100">
      </div>

      <div class="grid-item">
        <label class="set_label" for="maximum_light_value">Maximum:</label>
        <input class="set_field" type="number" id="maximum_light_value" v-model="light_max" min="0" max="100">
      </div>

      <!-------------------------------------------------*LOUDNESS*--------------------------------------------------->
      <div class="grid-item">
        <p><b>Set</b> your desired <b>minimum </b> and <b> maximum </b><b style="color: gold">Loudness level</b></p>
      </div>

      <div class="grid-item">
        <label class="set_label" for="minimum_noise_value">Minimum:</label>
        <input class="set_field" type="number" id="minimum_noise_value" v-model="loudness_min" min="0" max="100">
      </div>

      <div class="grid-item">
        <label class="set_label" for="maximum_noise_value">Maximum:</label>
        <input class="set_field" type="number" id="maximum_noise_value" v-model="loudness_max" min="0" max="100">
      </div>

      <!------------------------------------------------*TEMPERATURE*------------------------------------------------->
      <div class="grid-item">
        <p><b>Set</b> your desired <b>minimum </b> and <b> maximum </b><b style="color: gold">Temperature °C</b></p>
      </div>

      <div class="grid-item">
        <label class="set_label" for="minimum_temperature_value">Minimum:</label>
        <input class="set_field" type="number" id="minimum_temperature_value" v-model="temperature_min" min="0" max="100">
      </div>

      <div class="grid-item">
        <label class="set_label" for="maximum_temperature_value">Maximum:</label>
        <input class="set_field" type="number" id="maximum_temperature_value" v-model="temperature_max" min="0" max="100">
      </div>

      <!-------------------------------------------------*HUMIDITY*--------------------------------------------------->
      <div class="grid-item">
        <p><b>Set</b> your desired <b>minimum </b> and <b> maximum </b><b style="color: gold">Humidity %</b></p>
      </div>

      <div class="grid-item">
        <label class="set_label" for="minimum_humidity_value">Minimum:</label>
        <input class="set_field" type="number" id="minimum_humidity_value" v-model="humidity_min" min="0" max="100">
      </div>

      <div class="grid-item">
        <label class="set_label" for="maximum_humidity_value">Maximum:</label>
        <input class="set_field" type="number" id="maximum_humidity_value" v-model="humidity_max" min="0" max="100">
      </div>

    </div>

    <button class="set_ranges_buttons" @click="saveSensorRanges">Save</button> <!-- @click binds the button to a method in script -->



  </div>
  <div class="success_message" v-if="displayOnSaveMessage">           <!-- v-if is only displayed if the data property is true -->
    <p>{{ onSaveMessage }}</p>                                        <!-- Dynamic message, displayed when user clicks save button -->
  </div>
</template>

<script>

// Imports for the MQTT functionality
import { threeDigitFormat, MQTTClientInit } from '@/modules/utils.js';

const client = MQTTClientInit(); // Initialize the MQTT client (see utils.js)

export default {
  name: "SetSensorRanges",
  data: function () {
    return {
      sensorNames: ["moisture", "light", "loudness", "temperature", "humidity"],

      /*--- Minimum and maximum values for all sensors--- */
      moisture_min: null,
      moisture_max: null,         /* The data properties are initialized as null and will be populated immediately by the created lifecycle hook that runs when the component  */
      light_min: null,            /* has been created and initialized. Read about created lifecycle here: https://vuejs.org/api/options-lifecycle.html#created                 */
      light_max: null,            /* The data properties are populated with 0's if no previous values have been saved. In the case that user have saved values previously      */
      loudness_min: null,         /* they will be retrieved from local storage and assigned to the data properties.                                                            */
      loudness_max: null,
      temperature_min: null,
      temperature_max: null,
      humidity_min: null,
      humidity_max: null,
      /*--------------------------------------------------*/

      displayOnSaveMessage: false,/* Boolean used in v-if to display successful save message if the save button has been clicked */
      onSaveMessage: "",          /* The onSaveMessage is different depending on weather the saveData() was successful or not    */
      validRange: false,
    }
  },


    // The created lifecycle hook runs when the component has been created and initialized, but prior to mounting to the DOM.
    // Created() will attempt to retrieve previously saved values from local storage and if no prior values exist set 0.
  created() {
    for (const sensorName of this.sensorNames) {                         // iterates over every sensor.
      this[`${sensorName}_min`] = localStorage[`${sensorName}_min`] || 0;// if previous ranges are saved retrieve 'sensorname'min from local storage else set 0.
      this[`${sensorName}_max`] = localStorage[`${sensorName}_max`] || 0;// if previous ranges are saved retrieve 'sensorname'max from local storage else set 0.
    }
    window.scrollTo(0,0);                                           // Takes you to the top of the screen when entering the screen.
  },

  methods: {
    goToMonitorTerrarium() {
      window.location.href = "#/your-terrariums"
    },
    // Saves the user input values to the wio terminal and handles potential error cases
    saveSensorRanges: function () {
      let rangeBuffer = new Map(); // Buffer for the sensor data to be sent to the wio terminal
      try {
        for (const sensorName of this.sensorNames) {                     // Goes through every sensor.
          const min = this[`${sensorName}_min`];                         // Immutable variable min declared and set to the current sensors min value.
          const max = this[`${sensorName}_max`];                         // immutable value max is declared and set to the current sensors Max value.

          this.validateRanges(min, max);                                 // The range is validated.

          // If an error is thrown, the entry is not added to the buffer
          // Furthermore, the consecutive entries are not added to the buffer
          if (!this.validRange) throw new Error(this.onSaveMessage);

          // Otherwise the entry is added to the buffer
          rangeBuffer.set(sensorName, { min, max });
        }
      } catch (error) {
        console.error(error);                                                       // Logs error to the console
        this.displayOnSaveMessage = true;
        this.resetSaveButton();
        return;
      }
      
      /* Displays the message to the user and resets the save button's state
       * Moreover, save the ranges to the local storage, so that they can be retrieved later */
      this.saveRangesToLocalStorage();
      this.displayOnSaveMessage = true;
      this.resetSaveButton();

      // ==================== MQTT ====================

      client.connect({
        onSuccess: () => {
          console.log(`Connected to broker @ ${client.host}:${client.port}`);

          // Iterate over the rangeBuffer and send the data to the wio terminal
          for (const [sensorName, { min, max }] of rangeBuffer) {
            const TOPIC = `/terminarium/app/range/${sensorName}`;                 // The topic the data is sent to
            const PAYLOAD = `${threeDigitFormat(min)},${threeDigitFormat(max)}`;  // The data that is sent to the wio terminal
            client.send(TOPIC, PAYLOAD);                                          // Send the data to the wio terminal
          }

          client.disconnect();  // Disconnect from the broker after the data has been sent
        },
        // If the connection fails, an error is logged to the console
        onFailure: (err) => console.error(err)
      });
    },
    // Resets isDataSaved to false so success/Error message will be displayed again on click
    resetSaveButton() {
      setTimeout(() => {                                          // The function will be executed 2,5 seconds after its called
        this.displayOnSaveMessage = false;
      }, 2500);
    },
    // Verifies that the ranges follow the following rules
    validateRanges(min, max) {
      if (min > max) {                                                   // Min can not be larger Max. If it is an error message explaining why range is invalid is set.
        this.validRange = false;
        this.onSaveMessage = "Save failed invalid range: Minimum value must be <= Maximum value";
      } else if (min < 0 || min > 100 || max < 0 || max > 100) {         // Min or max can not be smaller than zero or larger than 100. If it is an error message explaining why range is invalid is set.
        this.validRange = false;
        this.onSaveMessage = "Save failed invalid range: Values must be 0 - 100";
      } else {                                                           // Success case, range is valid. Sets success message.
        this.validRange = true;
        this.onSaveMessage = "Your desired values were saved successfully!";
      }
    },
    // Saves sensor values to local storage. Local storage is persistent meaning the values are saved between sessions.
    // The local storage us browser specific and values can not be shared between browsers or devices.
    // The data is stored as key-value pairs: key -> value.
    saveRangesToLocalStorage() {
      for (const sensorName of this.sensorNames) {                       // iterates over every sensor
        localStorage[`${sensorName}_min`] = this[`${sensorName}_min`];   // Saves min to local storage
        localStorage[`${sensorName}_max`] = this[`${sensorName}_max`];   // Saves max to local storage
      }
    }
  },
};

</script>
<style scoped>

.Choose_ranges_box {                    /* This box defines the space for the grid_container */
  padding: 0;
  display: flex;                        /* Adapting to screen size */
  flex-direction: column;               /* Flex items stack vertically */
  justify-content: center;              /* Align flex items centered vertically */
  align-items: center;                  /* Align flex items centered horizontally */
  width: 100%;
  margin-top: 20vh;
}

p {
  margin: 0;
  font-size: 14px;

}

.set_label {
  font-size: 20px;
  font-weight: bold;
}

.set_field {
  font-size: 15px;
  padding: 10px;
  border-radius: 20px;                    /* Rounds edges */

}

.grid-container {
  display: grid;
  grid-template-rows: repeat(5, 1fr);     /* Creates a grid with 5 rows Guides to learn more: https://css-tricks.com/snippets/css/complete-guide-grid/ */
  grid-template-columns: repeat(3, 1fr);  /* 3 columns                                        https://www.w3schools.com/cssref/pr_grid-template.php    */
  gap: 10px;
  width: 60%;
  margin: 10px;
}

.grid-item {
  background-color: rgba(80, 80, 80, 0.7); /* rgba's first three arguments take red, green and blue 0 - 255. */
  padding: 10px;                           /* The fourth lets you set transparency 0 - 1. Guide to learn: https://www.webfx.com/blog/web-design/rgba/ */
  border-radius: 20px;                     /* Rounds edges */
}

.set_ranges_buttons {
  width: 60%;
  height: 20px;
  border-radius: 20px;
  color: #ffffff;
  background-color: rgba(80, 80, 80, 0.7); /* rgba's first three arguments take red, green and blue 0 - 255. */
  border: none;                            /* The fourth lets you set transparency 0 - 1. Guide to learn: https://www.webfx.com/blog/web-design/rgba/ */
  text-align: center;
  font-size: 16px;
  cursor: pointer;
}

.set_ranges_buttons:hover {
  background-color: #437649;
  transition: background-color 1.0s ease;  /* Fades in the background-color on hover. */
}

.success_message {
  margin-top: 5px;
  width: 100%;
  height: 20px;
  text-align: center;
}
</style>
