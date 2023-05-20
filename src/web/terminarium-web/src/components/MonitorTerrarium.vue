<!---------------------------*COMPONENT DESCRIPTION*-------------------------------
  This component contains the monitoring board used to display current readings and
  statistical data, fetched live from the Wio Terminal and Firebase database 
  respectively. 

  The "Chart"-component is imported and used inside the grid structure. To ensure
  proper functionality without errors; refer to that component-file's description 
  when refactoring its usage here - as it requires several external props.
---------------------------------------------------------------------------------->

<script setup>
import Chart from "@/components/Chart.vue";
import { averageSensorValues } from "@/modules/averageValues.js";
import { parseVibrationData } from "@/modules/utils";
</script>

<template>
  <div class="monitor_terrarium_box">
    <div class="grid-container">
      <!-- The structure of the grid: titles for each column. -->
      <div class="grid-item">Sensor type</div>
      <div class="grid-item">Current reading</div>
      <div class="grid-item">1 hour Avg.</div>
      <div class="grid-item">24 hours Avg.</div>
      <div class="grid-item">Graph</div>

      <!-- Temperature ------------------------------->
      <div class="grid-item">{{ sensorNames[0] }}</div>
      <div
        class="grid-item"
        v-bind:class="[
          /* Logic:
           *  1. If the current sensor reading is undefined - retain the text color as the default convention (white).
           *  2. If the current sensor reading is within the user-defined ranges - set the text color to green.
           *  3. Otherwise, meaning that the current sensor reading is not within the user-defined ranges - set the text color to red.
           * The same logic is applicable for all sensor types. */
          isWithinAcceptedRange(sensorNames[0].toLowerCase()) === undefined
            ? ''
            : isWithinAcceptedRange(sensorNames[0].toLowerCase())
            ? 'apply-green-text'
            : 'apply-red-text',
        ]"
      >
        {{ this.sensorValues.value[sensorNames[0].toLowerCase()] || NaN }}°C
      </div>
      <div class="grid-item">{{ sensorAvgs.temperature.oneHourAvg }}</div>
      <div class="grid-item">
        {{ sensorAvgs.temperature.twentyFourHourAvg }}
      </div>
      <div class="grid-item">
        <Chart
          :sensorType="'temperature'"
          :range="chartRange"
          :height="chartHeight"
          :width="chartWidth"
        />
      </div>

      <!-- Humidity ---------------------------------->
      <div class="grid-item">{{ sensorNames[1] }}</div>
      <div
        class="grid-item"
        v-bind:class="[
          isWithinAcceptedRange(sensorNames[1].toLowerCase()) === undefined
            ? ''
            : isWithinAcceptedRange(sensorNames[1].toLowerCase())
            ? 'apply-green-text'
            : 'apply-red-text',
        ]"
      >
        {{ this.sensorValues.value[sensorNames[1].toLowerCase()] || NaN }}% RH
      </div>
      <div class="grid-item">{{ sensorAvgs.humidity.oneHourAvg }}</div>
      <div class="grid-item">{{ sensorAvgs.humidity.oneHourAvg }}</div>
      <div class="grid-item">
        <Chart
          :sensorType="'humidity'"
          :range="chartRange"
          :height="chartHeight"
          :width="chartWidth"
        />
      </div>

      <!-- Light ------------------------------------->
      <div class="grid-item">{{ sensorNames[2] }}</div>
      <div
        class="grid-item"
        v-bind:class="[
          isWithinAcceptedRange(sensorNames[2].toLowerCase()) === undefined
            ? ''
            : isWithinAcceptedRange(sensorNames[2].toLowerCase())
            ? 'apply-green-text'
            : 'apply-red-text',
        ]"
      >
        {{ this.sensorValues.value[sensorNames[2].toLowerCase()] || NaN }}%
      </div>
      <div class="grid-item">{{ sensorAvgs.light.oneHourAvg }}</div>
      <div class="grid-item">{{ sensorAvgs.light.twentyFourHourAvg }}</div>
      <div class="grid-item">
        <Chart
          :sensorType="'light'"
          :range="chartRange"
          :height="chartHeight"
          :width="chartWidth"
        />
      </div>

      <!-- Moisture ---------------------------------->
      <div class="grid-item">{{ sensorNames[3] }}</div>
      <div
        class="grid-item"
        v-bind:class="[
          isWithinAcceptedRange(sensorNames[3].toLowerCase()) === undefined
            ? ''
            : isWithinAcceptedRange(sensorNames[3].toLowerCase())
            ? 'apply-green-text'
            : 'apply-red-text',
        ]"
      >
        {{ this.sensorValues.value[sensorNames[3].toLowerCase()] || NaN }}% RH
      </div>
      <div class="grid-item">{{ sensorAvgs.moisture.oneHourAvg }}</div>
      <div class="grid-item">{{ sensorAvgs.moisture.twentyFourHourAvg }}</div>
      <div class="grid-item">
        <Chart
          :sensorType="'moisture'"
          :range="chartRange"
          :height="chartHeight"
          :width="chartWidth"
        />
      </div>

      <!-- Loudness ---------------------------------->
      <div class="grid-item">{{ sensorNames[4] }}</div>
      <div
        class="grid-item"
        v-bind:class="[
          isWithinAcceptedRange(sensorNames[4].toLowerCase()) === undefined
            ? ''
            : isWithinAcceptedRange(sensorNames[4].toLowerCase())
            ? 'apply-green-text'
            : 'apply-red-text',
        ]"
      >
        {{ this.sensorValues.value[sensorNames[4].toLowerCase()] || NaN }}%
      </div>
      <div class="grid-item">{{ sensorAvgs.loudness.oneHourAvg }}</div>
      <div class="grid-item">{{ sensorAvgs.loudness.twentyFourHourAvg }}</div>
      <div class="grid-item">
        <Chart
          :sensorType="'loudness'"
          :range="chartRange"
          :height="chartHeight"
          :width="chartWidth"
        />
      </div>

      <!-- Vibration --------------------------------->
      <div class="grid-item">Vibrating</div>
      <!-- This is an exception, as it's more readable than "Vibration" -->
      <div
        class="grid-item"
        v-bind:class="[
          isWithinAcceptedRange(sensorNames[5].toLowerCase()) === undefined
            ? ''
            : !isWithinAcceptedRange(sensorNames[5].toLowerCase())
            ? 'apply-green-text'
            : 'apply-red-text',
        ]"
      >
        {{
          parseVibrationData(
            this.sensorValues.value[sensorNames[5].toLowerCase()]
          ) || NaN
        }}
      </div>
      <div class="grid-item">{{ sensorAvgs.vibration.oneHourAvg }}</div>
      <div class="grid-item">{{ sensorAvgs.vibration.twentyFourHourAvg }}</div>
      <div class="grid-item">
        <Chart
          :sensorType="'vibration'"
          :range="chartRange"
          :height="chartHeight"
          :width="chartWidth"
        />
      </div>
    </div>
  </div>
  <!-- This button enables the user to change the acceptable sensor-ranges for the Wio Terminal -->
  <button type="button" class="set-ranges" @click="setRanges">
    Set acceptable ranges
  </button>
</template>

<script>
export default {
  name: "MonitorTerrarium",
  components: { Chart },
  inject: ["sensorValues"],

  data() {
    return {
      sensorNames: [
        "Temperature",
        "Humidity",
        "Light",
        "Moisture",
        "Loudness",
        "Vibration",
      ],

      // How many hours the average should be calculated for.
      // There are two different values displayed for each sensor.
      shorterRange: "1", // The shorter time-span.
      longerRange: "24", // The longer time-span.
      chartRange: "24",

      chartHeight: "50", // Used as external prop for each Chart component - defines their height.
      chartWidth: "100", // Used as external prop for each Chart component - defines their width.

      // The initial states of the average values; similarly, placeholder values used to store the averages.
      sensorAvgs: {
        temperature:  { oneHourAvg: 0, twentyFourHourAvg: 0 },
        humidity:     { oneHourAvg: 0, twentyFourHourAvg: 0 },
        light:        { oneHourAvg: 0, twentyFourHourAvg: 0 },
        moisture:     { oneHourAvg: 0, twentyFourHourAvg: 0 },
        loudness:     { oneHourAvg: 0, twentyFourHourAvg: 0 },
        vibration:    { oneHourAvg: 0, twentyFourHourAvg: 0 },
      },

      sensorRanges: {
        temperature:  { min: 21, max: 28 },
        humidity:     { min: 10, max: 40 },
        light:        { min: 20, max: 65 },
        moisture:     { min: 10, max: 85 },
        loudness:     { min: 0,  max: 65 },
        vibration:    { min: 0,  max: 1  },
      },
    };
  },

  activated() {
    this.updateAverageValues();   // Compute the average sensor values
    this.getSavedSensorRanges();  // Compute the latest saved ranges (if any exist)
  },

  methods: {
    // Tells the router in App.vue to switch to the SetSensorRanges-component.
    setRanges() {
      window.location.href = "#/set-sensor-ranges";
    },

    /**
     * This method is responsible for displaying the average values of each sensor.
     * It calls the averageSensorValues() method from the averageValues.js module.
     * It fetches the data entries directly from the database. So, it obtains the
     * real-time average values.
     */
    async updateAverageValues() {
      // Fetch the data entries from the database and calculate the average values.
      const shortAvgMap = await averageSensorValues(this.shorterRange);
      const longAvgMap  = await averageSensorValues(this.longerRange);

      // Iterate over all the sensors and update their average values. If an acceptable
      // value is not retrieved, display 'NaN' instead.
      for (const [sensor, sensorState] of Object.entries(this.sensorAvgs)) {
        sensorState.oneHourAvg = shortAvgMap.get(sensor)        || NaN;
        sensorState.twentyFourHourAvg = longAvgMap.get(sensor)  || NaN;
      }
    },

    /**
     * This function stores assigns each sensor reading a particular state with the respect
     * to the defined sensor ranges. This way, we're able to store 3 states, namely:
     * (i) the value is not provided, (ii) the value is not within the range, (iii)
     * the value is within the range.
     * @param {String} - the sensor type to be mapped based on the value
     * @return {boolean | undefined} - the three states for each sensor reading
     */
    isWithinAcceptedRange(sensorType) {
      const currentMin      = this.sensorRanges[sensorType].min;
      const currentMax      = this.sensorRanges[sensorType].max;
      const currentReading  = this.sensorValues.value[sensorType];

      // Special case: vibration sensor
      if (sensorType === "vibration") {
        if (currentReading === 'true') return true;
                
        return false;
      }

      // If the current value is undefined, simply return undefined, because
      // we need to be able to store 3 states.
      if (currentReading === undefined) return undefined;

      // If the value is not within the desired ranges, return false
      if (currentReading < currentMin || currentReading > currentMax) return false;

      // Otherwise, return true
      return true;
    },
    /**
     * This method is responsible for obtaining the saved sensor ranges from the
     * local storage. If there are no saved values, the default values are used.
     */
     getSavedSensorRanges() {
      // Iterate over all the sensors and obtain their saved values from the local storage.
      for (const sensor of this.sensorNames) {
        const savedMin = localStorage.getItem(`${sensor.toLowerCase()}_min`);
        const savedMax = localStorage.getItem(`${sensor.toLowerCase()}_max`);

        // Check against null, if the values are not null, update the sensorRanges object
        // with the parsed values as an integer.
        if (savedMin !== null) {
          this.sensorRanges[sensor.toLowerCase()].min = parseInt(savedMin);
        } else if (savedMax !== null) {
          this.sensorRanges[sensor.toLowerCase()].max = parseInt(savedMax);
        }
      }
    }
  },
};
</script>

<style scoped>
.grid-container {
  display: grid;
  grid-template-rows: repeat(7, 1fr);
  /* Creates a grid with 7 rows Guides to learn more: https://css-tricks.com/snippets/css/complete-guide-grid/ */
  grid-template-columns: repeat(5, 1fr);
  /* 5 columns                                        https://www.w3schools.com/cssref/pr_grid-template.php    */
  gap: 10px;
}

.grid-item {
  padding: 5px;
  border-radius: 5px;

  /* Centers the contents of each grid-item */
  display: flex;
  justify-content: center;
  align-items: center;
}
.grid-item:nth-child(n + 1):nth-child(-n + 5) {
  background-color: rgba(80, 80, 80, 0.2);
}

.grid-item:nth-child(n + 6):nth-child(-n + 35) {
  background-color: rgba(0, 255, 0, 0.2);
}

.set-ranges {
  /* TODO: finalise this button's styling */
  margin-top: 1vh;
  width: 100%;
  margin-bottom: 10vh;
}

.apply-red-text {
  color: #ff2d2d;
  text-shadow: -0.5px -0.5px 0 rgb(156, 0, 0), 0.5px -0.5px 0 rgb(156, 0, 0), -0.5px 0.5px 0 rgb(156, 0, 0), 0.5px 0.5px 0 rgb(156, 0, 0);
}

.apply-green-text {
  color: #10e734;
  text-shadow: -0.5px -0.5px 0 rgb(26, 110, 0), 0.5px -0.5px 0 rgb(26, 110, 0), -0.5px 0.5px 0 rgb(26, 110, 0), 0.5px 0.5px 0 rgb(26, 110, 0);
}
</style>
