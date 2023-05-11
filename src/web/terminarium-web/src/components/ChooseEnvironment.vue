<!----------------------------------------------------------------------------------
   The "ChooseEnvironment" component is used to
   set the desired environment ranges for the terrarium enclosures.
----------------------------------------------------------------------------------->
<template>
  <!----------------------------------------------------------------------------------
   The page uses a grid structure(defined in css).
   v-model is used to bind the input fields with their respective data properties.
   The elements are styled in the using css.
----------------------------------------------------------------------------------->
  <div class="Choose_ranges_box">
    <div class="grid-container">

      <!-------------------------------------------------*MOISTURE*-------------------------------------------------->
      <div class="grid-item">
        <p><b>Set</b> your desired <b>minimum </b> and <b> maximum </b><b style="color: gold">Moisture %</b></p>
      </div>

      <div class="grid-item">
        <label class="set_label" for="min">Minimum:</label>
        <input class="set_field" type="number" id="moisture_min" v-model="moisture_min" min="0" max="100">
      </div>

      <div class="grid-item">
        <label class="set_label" for="max">Maximum:</label>
        <input class="set_field" type="number" id="moisture_max" v-model="moisture_max" min="0" max="100">
      </div>


      <!--------------------------------------------------*LIGHT*----------------------------------------------------->
      <div class="grid-item">
        <p><b>Set</b> your desired <b>minimum </b> and <b> maximum </b><b style="color: gold">Light level </b></p>
      </div>

      <div class="grid-item">
        <label class="set_label" for="min">Minimum:</label>
        <input class="set_field" type="number" id="light_min" v-model="light_min" min="0" max="100">
      </div>

      <div class="grid-item">
        <label class="set_label" for="max">Maximum:</label>
        <input class="set_field" type="number" id="light_max" v-model="light_max" min="0" max="100">
      </div>

      <!-------------------------------------------------*LOUDNESS*--------------------------------------------------->
      <div class="grid-item">
        <p><b>Set</b> your desired <b>minimum </b> and <b> maximum </b><b style="color: gold">Noise level </b></p>
      </div>

      <div class="grid-item">
        <label class="set_label" for="min">Minimum:</label>
        <input class="set_field" type="number" id="noise_min" v-model="noise_min" min="0" max="100">
      </div>

      <div class="grid-item">
        <label class="set_label" for="max">Maximum:</label>
        <input class="set_field" type="number" id="noise_max" v-model="noise_max" min="0" max="100">
      </div>

      <!------------------------------------------------*TEMPERATURE*------------------------------------------------->
      <div class="grid-item">
        <p><b>Set</b> your desired <b>minimum </b> and <b> maximum </b><b style="color: gold">Temperature °C</b></p>
      </div>

      <div class="grid-item">
        <label class="set_label" for="min">Minimum:</label>
        <input class="set_field" type="number" id="temperature_min" v-model="temperature_min" min="0" max="100">
      </div>

      <div class="grid-item">
        <label class="set_label" for="max">Maximum:</label>
        <input class="set_field" type="number" id="temperature_max" v-model="temperature_max" min="0" max="100">
      </div>

      <!-------------------------------------------------*HUMIDITY*--------------------------------------------------->
      <div class="grid-item">
        <p><b>Set</b> your desired <b>minimum </b> and <b> maximum </b><b style="color: gold">Humidity %</b></p>
      </div>

      <div class="grid-item">
        <label class="set_label" for="min">Minimum:</label>
        <input class="set_field" type="number" id="humidity_min" v-model="humidity_min" min="0" max="100">
      </div>

      <div class="grid-item">
        <label class="set_label" for="max">Maximum:</label>
        <input class="set_field" type="number" id="humidity_max" v-model="humidity_max" min="0" max="100">
      </div>

    </div>

    <button class="save_button" @click="saveSensorRanges">Save</button> <!-- @click binds the button to a method in script -->

    <div class="success_message" v-if="displayOnSaveMessage">           <!-- v-if is only displayed if the data property is true -->
      <p>{{ onSaveMessage }}</p>
    </div>

  </div>
</template>

<script>
export default {
  name: "ChooseEnvironment",
  data: function () {
    return {
      minValue: 0,                /* Minimum allowed input value */
      maxValue: 100,              /* Maximum allowed input value */

      sensorNames: ["moisture", "light", "noise", "temperature", "humidity"],

      moisture_min: 0,            /* Minimum and maximum values for all sensors */
      moisture_max: 0,
      light_min: 0,
      light_max: 0,
      noise_min: 0,
      noise_max: 0,
      temperature_min: 0,
      temperature_max: 0,
      humidity_min: 0,
      humidity_max: 0,            /*-------------------------------------------- */

      displayOnSaveMessage: false,/* Boolean used in v-if to display successful save message if the save button has been clicked */
      onSaveMessage: "",          /* The onSaveMessage is different depending on weather the saveData() was successful or not */
      validRange: false,
    }
  },

  mounted() {
    // TODO: Implement "cookies" so the users last saved values are start values in input fields
  },

  methods: {
    // Saves the user input values to the wio terminal and handles potential error cases
    saveSensorRanges: function () {
      try {
        for (const sensorName of this.sensorNames) {// Looks at every sensor and gets the min and max values
          const min = this[`${sensorName}_min`];
          const max = this[`${sensorName}_max`];

          this.validateRanges(min, max);

          if (!this.validRange) {
            throw new Error(this.onSaveMessage);
          }
        }
        // TODO: Send data to wio terminal here
        this.displayOnSaveMessage = true;
        this.resetSaveButton();
      }
      catch (error) {
        console.error(error);                        // Logs error to the console
        this.displayOnSaveMessage = true;            // Error message is displayed to the user
        this.resetSaveButton();
      }
    },
    // Resets isDataSaved to false so success/Error message will be displayed again on click
    resetSaveButton() {
      setTimeout(() => {                      // The function will be executed 2,5 seconds after its called
        this.displayOnSaveMessage = false;
      }, 2500);
    },

    validateRanges(min, max) {
      if (min > max) {                               // Checks if min is larger than max and sets helpful Error message if true
        this.validRange = false;
        this.onSaveMessage = "Save failed invalid range: Minimum value must be <= Maximum value";
      } else if (min > 100 || max > 100) {           // Checks if values are larger than 100 and sets helpful Error message if true
        this.validRange = false;
        this.onSaveMessage = "Save failed invalid range: Values must be <= 100";
      } else {                                       // Success case, range is valid. Sets success message
        this.validRange = true;
        this.onSaveMessage = "Your desired values were saved successfully!";
      }
    }
  },
};

</script>
<style scoped>

.Choose_ranges_box {                    /* This box defines the space for the grid_container */
  width: 800px;
  height: 400px;
  margin: 0;
  padding: 0;
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
}

.grid-item {
  background-color: rgba(80, 80, 80, 0.7); /* rgba's first three arguments take red, green and blue 0 - 255. */
  padding: 10px;                           /* The fourth lets you set transparency 0 - 1. Guide to learn: https://www.webfx.com/blog/web-design/rgba/ */
  border-radius: 20px;                     /* Rounds edges */
}

.save_button {
  margin-top: 10px;
  width: 100%;
  height: 20px;
  border-radius: 20px;
  color: #ffffff;
  background-color: rgba(80, 80, 80, 0.7); /* rgba's first three arguments take red, green and blue 0 - 255. */
  border: none;                            /* The fourth lets you set transparency 0 - 1. Guide to learn: https://www.webfx.com/blog/web-design/rgba/ */
  text-align: center;
  font-size: 16px;
  cursor: pointer;

}

.save_button:hover {
  background-color: #437649;
  transition: background-color 1.0s ease;  /* Fades in the background-color on hover, can be removed later if a global standard is introduced */
}

.success_message {
  margin-top: 5px;
  width: 100%;
  height: 20px;
  border-radius: 20px;                     /* Rounds edges */
  color: #ffffff;
  text-align: center;
  transition: background-color 3.0s ease;
  opacity: 1;
}
</style>
