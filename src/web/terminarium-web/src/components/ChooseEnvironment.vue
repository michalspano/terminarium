<!----------------------------------------------------------------------------------
   The "ChooseEnvironment" component is used to
   set the desired environment values for the terrarium enclosures
----------------------------------------------------------------------------------->
<template>
  <!----------------------------------------------------------------------------------
   The page uses a grid structure(defined in css).
   v-model is used to bind the input fields with their respective data properties.
   The elements are styled in the using css.
----------------------------------------------------------------------------------->
  <div class="Choose_ranges_box">
    <div class="grid-container">

      <div class="grid-item">
        <p><b>Set</b> your desired <b>minimum </b> and <b> maximum </b><b style="color: gold">Moisture %</b></p>
      </div>

      <div class="grid-item">
        <label class="set_label" for="min">Minimum:</label>
        <input class="set_field" type="number" id="moisture_min" v-model="moisture_min" min="0" max="100"></div>

      <div class="grid-item">
        <label class="set_label" for="max">Maximum:</label>
        <input class="set_field" type="number" id="moisture_max" v-model="moisture_max" min="0" max="100"></div>

      <div class="grid-item">
        <p><b>Set</b> your desired <b>minimum </b> and <b> maximum </b><b style="color: gold">Light level </b></p>
      </div>

      <div class="grid-item">
        <label class="set_label" for="min">Minimum:</label>
        <input class="set_field" type="number" id="light_min" v-model="light_min" min="0" max="100"></div>

      <div class="grid-item">
        <label class="set_label" for="max">Maximum:</label>
        <input class="set_field" type="number" id="light_max" v-model="light_max" min="0" max="100"></div>

      <div class="grid-item">
        <p><b>Set</b> your desired <b>minimum </b> and <b> maximum </b><b style="color: gold">Noise level </b></p>
      </div>

      <div class="grid-item">
        <label class="set_label" for="min">Minimum:</label>
        <input class="set_field" type="number" id="noise_min" v-model="noise_min" min="0" max="100"></div>

      <div class="grid-item">
        <label class="set_label" for="max">Maximum:</label>
        <input class="set_field" type="number" id="noise_max" v-model="noise_max" min="0" max="100"></div>

      <div class="grid-item">
        <p><b>Set</b> your desired <b>minimum </b> and <b> maximum </b><b style="color: gold">Temperature C</b></p>
      </div>

      <div class="grid-item">
        <label class="set_label" for="min">Minimum:</label>
        <input class="set_field" type="number" id="temperature_min" v-model="temperature_min" min="0" max="100"></div>

      <div class="grid-item">
        <label class="set_label" for="max">Maximum:</label>
        <input class="set_field" type="number" id="temperature_max" v-model="temperature_max" min="0" max="100"></div>

      <div class="grid-item">
        <p><b>Set</b> your desired <b>minimum </b> and <b> maximum </b><b style="color: gold">Humidity %</b></p>
      </div>

      <div class="grid-item">
        <label class="set_label" for="min">Minimum:</label>
        <input class="set_field" type="number" id="humidity_min" v-model="humidity_min" min="0" max="100"></div>

      <div class="grid-item">
        <label class="set_label" for="max">Maximum:</label>
        <input class="set_field" type="number" id="humidity_max" v-model="humidity_max" min="0" max="100"></div>
    </div>

    <button class="save_button" @click="saveData">Save</button> <!-- @click binds the button to a method in script -->

    <div class="success_message" v-if="displayOnSaveMessage">   <!-- v-if is only displayed if the data property is true -->
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
      displayOnSaveMessage: false,/* Boolean used in v-if to display successful save message if the save button has been clicked  */
      onSaveMessage: "",          /* The onSaveMessage is different depending on weather the saveData() was successful or not */
    }
  },

  mounted() {
    // TODO: Fetch data from database to have the users last saved values as start values in input fields
  },

  methods: {
    // Saves/sets the values from the inputs to the data object and handles potential error cases
    saveData: function () {
      const sensorNames = ["moisture", "light", "noise", "temperature", "humidity"];

      for (const sensorName of sensorNames) {   // Looks at every sensor and gets the min and max values
        const min = this[`${sensorName}_min`];
        const max = this[`${sensorName}_max`];

        if (min > max) {                        // Checks that min is not larger than max and sets helpful exception if true
          this.displayOnSaveMessage = true;
          this.onSaveMessage = "Save failed: Minimum value must be <= Maximum value";
          this.resetSaveButton()
          return;
        }
        if (min > 100 || max > 100) {           // Checks that no value is larger than 100 and sets helpful exception if true
          this.displayOnSaveMessage = true;     // The fields arrow buttons are constricted to 0 - 100 however manually entering a large number worked previously
                                                // This can be refactored later if there is a better way.
          this.onSaveMessage = "Save failed: Values must be <= 100";
          this.resetSaveButton()
          return;
        }

      }

      // TODO: Send data to database here

      this.displayOnSaveMessage = true;
      this.onSaveMessage = "Your desired values were saved successfully!";
      this.resetSaveButton();

      /* Only used during development to check the values in the "Console"
      console.log("moisture_min:", this.moisture_min);
      console.log("moisture_max:", this.moisture_max);
      console.log("light_min:", this.light_min);
      console.log("light_max:", this.light_max);
      console.log("noise_min:", this.noise_min);
      console.log("noise_max:", this.noise_max);
      console.log("temperature_min:", this.temperature_min);
      console.log("temperature_max:", this.temperature_max);
      console.log("humidity_min:", this.humidity_min);
      console.log("humidity_max:", this.humidity_max);
      */
    },
    // Resets isDataSaved to false so success message will be displayed again on click
    resetSaveButton() {
      setTimeout(() => {
        this.displayOnSaveMessage = false;
      }, 2500); // Delay, message is displayed for 2,5 second
    }
  },
};

</script>
<style scoped>

.Choose_ranges_box {                            /* This box defines the space for the grid_container */
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
  border-radius: 20px;                           /* Rounds edges */

}

.grid-container {
  display: grid;
  grid-template-rows: repeat(5, 1fr);            /* Creates a grid with 5 rows Guides to learn more: https://css-tricks.com/snippets/css/complete-guide-grid/ */
  grid-template-columns: repeat(3, 1fr);         /* 3 columns                                        https://www.w3schools.com/cssref/pr_grid-template.php */
  gap: 10px;
}

.grid-item {
  background-color: rgba(80, 80, 80, 0.7);      /* rgba's first three arguments take red, green and blue 0 - 255. */
  padding: 10px;                                /* The fourth lets you set transparency 0 - 1. Guide to learn: https://www.webfx.com/blog/web-design/rgba/ */
  border-radius: 20px;                          /* Rounds edges */
}

.save_button {
  margin-top: 10px;
  width: 100%;
  height: 20px;
  border-radius: 20px;
  color: #ffffff;
  background-color: rgba(80, 80, 80, 0.7);    /* rgba's first three arguments take red, green and blue 0 - 255. */
  border: none;                               /* The fourth lets you set transparency 0 - 1. Guide to learn: https://www.webfx.com/blog/web-design/rgba/ */
  text-align: center;
  font-size: 16px;
  cursor: pointer;

}

.save_button:hover {
  background-color: #437649;
  transition: background-color 1.0s ease;     /* Fades in the background-color on hover, can be removed later if a global standard is introduced */
}

.success_message {
  margin-top: 5px;
  width: 100%;
  height: 20px;
  border-radius: 20px;
  color: #ffffff;
  text-align: center;
  transition: background-color 3.0s ease;
  opacity: 1;
}
</style>
