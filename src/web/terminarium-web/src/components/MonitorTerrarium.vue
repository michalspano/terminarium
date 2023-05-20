<!---------------------------*COMPONENT DESCRIPTION*-------------------------------
  This component contains the monitoring board used to display current readings and
  statistical data, fetched live from the Wio Terminal and Firebase database 
  respectively. 

  The "Chart"-component is imported and used inside the grid structure. To ensure
  proper functionality without errors; refer to that component-file's description 
  when refactoring its usage here - as it requires several external props.
---------------------------------------------------------------------------------->

<script setup>
import Chart from '@/components/Chart.vue';
import { averageSensorValues } from '@/modules/averageValues.js';
import { parseVibrationData } from '@/modules/utils';
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
      <div class="grid-item">{{ this.sensorValues.value.temperature || 0 }}°C</div>
      <div class="grid-item">{{ sensorAvgs.temperature.oneHourAvg }}</div>
      <div class="grid-item">{{ sensorAvgs.temperature.twentyFourHourAvg }}</div>
      <div class="grid-item">
        <Chart :sensorType="'temperature'" :range="chartRange" :height="chartHeight" :width="chartWidth" />
      </div>

      <!-- Humidity ---------------------------------->
      <div class="grid-item">{{ sensorNames[1] }}</div>
      <div class="grid-item">{{ this.sensorValues.value.humidity || 0 }}% RH</div>
      <div class="grid-item">{{ sensorAvgs.humidity.oneHourAvg }}</div>
      <div class="grid-item">{{ sensorAvgs.humidity.oneHourAvg }}</div>
      <div class="grid-item">
        <Chart :sensorType="'humidity'" :range="chartRange" :height="chartHeight" :width="chartWidth" />
      </div>

      <!-- Light ------------------------------------->
      <div class="grid-item">{{ sensorNames[2] }}</div>
      <div class="grid-item">{{ this.sensorValues.value.light || 0 }}%</div>
      <div class="grid-item">{{ sensorAvgs.light.oneHourAvg }}</div>
      <div class="grid-item">{{ sensorAvgs.light.twentyFourHourAvg }}</div>
      <div class="grid-item">
        <Chart :sensorType="'light'" :range="chartRange" :height="chartHeight" :width="chartWidth" />
      </div>

      <!-- Moisture ---------------------------------->
      <div class="grid-item">{{ sensorNames[3] }}</div>
      <div class="grid-item">{{ this.sensorValues.value.moisture || 0 }}%</div>
      <div class="grid-item">{{ sensorAvgs.moisture.oneHourAvg }}</div>
      <div class="grid-item">{{ sensorAvgs.moisture.twentyFourHourAvg }}</div>
      <div class="grid-item">
        <Chart :sensorType="'moisture'" :range="chartRange" :height="chartHeight" :width="chartWidth" />
      </div>

      <!-- Loudness ---------------------------------->
      <div class="grid-item">{{ sensorNames[4] }}</div>
      <div class="grid-item">{{ this.sensorValues.value.loudness || 0 }}%</div>
      <div class="grid-item">{{ sensorAvgs.loudness.oneHourAvg }}</div>
      <div class="grid-item">{{ sensorAvgs.loudness.twentyFourHourAvg }}</div>
      <div class="grid-item">
        <Chart :sensorType="'loudness'" :range="chartRange" :height="chartHeight" :width="chartWidth" />
      </div>

      <!-- Vibration --------------------------------->
      <div class="grid-item">Vibrating</div> <!-- This is an exception, as it's more readable than "Vibration" -->
      <div class="grid-item">{{ parseVibrationData(this.sensorValues.value.vibration) || 0 }}</div>
      <div class="grid-item">{{ sensorAvgs.vibration.oneHourAvg }}</div>
      <div class="grid-item">{{ sensorAvgs.vibration.twentyFourHourAvg }}</div>
      <div class="grid-item">
        <Chart :sensorType="'vibration'" :range="chartRange" :height="chartHeight" :width="chartWidth" />
      </div>

    </div>

  </div>
  <!-- This button enables the user to change the acceptable sensor-ranges for the Wio Terminal -->
  <button type="button" class="set-ranges" @click="setRanges">Set acceptable ranges</button>
</template>

<script>
export default {
  name: "MonitorTerrarium",
  components: { Chart },
  inject: ['sensorValues'],

  data() {
    return {
      sensorNames: ["Temperature", "Humidity", "Light", "Moisture", "Loudness", "Vibration"],

      // How many hours the average should be calculated for. 
      // There are two different values displayed for each sensor.
      shorterRange: "1",      // The shorter time-span.
      longerRange: "24",      // The longer time-span.
      chartRange: "24",

      chartHeight: "50",    // Used as external prop for each Chart component - defines their height.
      chartWidth: "100",     // Used as external prop for each Chart component - defines their width.

      // The initial states of the average values; similarly, placeholder values used to store the averages.
      sensorAvgs: {
        temperature:  { oneHourAvg: 0, twentyFourHourAvg: 0 },
        humidity:     { oneHourAvg: 0, twentyFourHourAvg: 0 },
        light:        { oneHourAvg: 0, twentyFourHourAvg: 0 },
        moisture:     { oneHourAvg: 0, twentyFourHourAvg: 0 },
        loudness:     { oneHourAvg: 0, twentyFourHourAvg: 0 },
        vibration:    { oneHourAvg: 0, twentyFourHourAvg: 0 }
      },
    };
  },
  // Hook: 'created' - responsibility: update the average values.
  created() { this.updateAverageValues(); },

  // Hook: 'mounted': TODO
  mounted() {},

  methods: {
    // Tells the router in App.vue to switch to the SetSensorRanges-component.
    setRanges() { window.location.href = "#/set-sensor-ranges" },

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
        sensorState.oneHourAvg        = shortAvgMap.get(sensor) || NaN;
        sensorState.twentyFourHourAvg = longAvgMap.get(sensor)  || NaN;
      }
    },
  }
}
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
  background-color: #ffffff;
  padding: 5px;
  border-radius: 5px;
  color: white;

  /* Centers the contents of each grid-item */
  display: flex;
  justify-content: center;
  align-items: center;
}

.grid-item:nth-child(n+1):nth-child(-n+5) {
  background-color: rgba(80, 80, 80, 0.2);
}

.grid-item:nth-child(n+6):nth-child(-n+35) {
  background-color: rgba(0, 255, 0, 0.2);
}

.set-ranges {
  /* TODO: finalise this button's styling */
  margin-top: 1vh;
  width: 100%;
  height: 22px;
  border-radius: 10px;
  background-color: #45C059;
  cursor: pointer;
  color: white;
}
</style>
