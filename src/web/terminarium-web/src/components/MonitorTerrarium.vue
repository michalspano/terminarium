<script setup>
import Chart from './Chart.vue';
</script>

<template>
  <div class="monitor_terrarium_box">
    <div class="grid-container">
      <!-- The structure of the grid: titles for each column. -->
      <div class="grid-item">Sensor type</div>
      <div class="grid-item">Current reading</div>  <!-- TODO: replace the placeholders (2's) with live data -->
      <div class="grid-item">1 hour Avg.</div>      <!-- TODO: replace the placeholders (3's) with live data -->
      <div class="grid-item">24 hours Avg.</div>    <!-- TODO: replace the placeholders (4's) with live data -->
      <div class="grid-item">Graph</div>

      <!-- Temperature ------------------------------->
      <div class="grid-item">{{ sensorNames[0] }}</div>
      <div class="grid-item">2</div>
      <div class="grid-item">3</div>
      <div class="grid-item">4</div>
      <div class="grid-item"> <Chart :sensorType="'temperature'" :range="chartRange" :height="chartHeight" :width="chartWidth"/></div>

      <!-- Humidity ---------------------------------->
      <div class="grid-item">{{ sensorNames[1] }}</div>
      <div class="grid-item">2</div>
      <div class="grid-item">3</div>
      <div class="grid-item">4</div>
      <div class="grid-item"> <Chart :sensorType="'humidity'" :range="chartRange" :height="chartHeight" :width="chartWidth"/></div>

      <!-- Light ------------------------------------->
      <div class="grid-item">{{ sensorNames[2] }}</div>
      <div class="grid-item">2</div>
      <div class="grid-item">3</div>
      <div class="grid-item">4</div>
      <div class="grid-item"> <Chart :sensorType="'light'" :range="chartRange" :height="chartHeight" :width="chartWidth"/></div>

      <!-- Moisture ---------------------------------->
      <div class="grid-item">{{ sensorNames[3] }}</div>
      <div class="grid-item">2</div>
      <div class="grid-item">3</div>
      <div class="grid-item">4</div>
      <div class="grid-item"> <Chart :sensorType="'moisture'" :range="chartRange" :height="chartHeight" :width="chartWidth"/></div>

      <!-- Loudness ---------------------------------->
      <div class="grid-item">{{ sensorNames[4] }}</div>
      <div class="grid-item">2</div>
      <div class="grid-item">3</div>
      <div class="grid-item">4</div>
      <div class="grid-item"> <Chart :sensorType="'loudness'" :range="chartRange" :height="chartHeight" :width="chartWidth"/></div>

      <!-- Vibration --------------------------------->
      <div class="grid-item">{{ sensorNames[5] }}</div>
      <div class="grid-item">2</div>
      <div class="grid-item">3</div>
      <div class="grid-item">4</div>
      <div class="grid-item"> <Chart :sensorType="'vibration'" :range="chartRange" :height="chartHeight" :width="chartWidth"/></div>

      </div>
    </div>
</template>

<script>
export default {
  name: "MonitorTerrarium",
  components: { Chart },
  data() {
    return {
      sensorNames: ["Temperature", "Humidity", "Light", "Moisture", "Loudness", "Vibration"],

      // How many hours the average should be calculated for. 
      // There are two different values displayed for each sensor.
      shorterRange: "1",    // The shorter time-span.
      longerRange: "24",    // The longer time-span.
        
      // TODO: Decide on the final values: Should the user be able to choose chart range? If not, what should the hardcoded value be?
      chartRange: "1600",
      chartHeight: "50",    // Used as external prop for each Chart component - defines their height.
      chartWidth: "100"     // Used as external prop for each Chart component - defines their width.
    }; 
  }
}
</script>

<style scoped>
.grid-container {
  display: grid;
  grid-template-rows: repeat(7, 1fr);     /* Creates a grid with 7 rows Guides to learn more: https://css-tricks.com/snippets/css/complete-guide-grid/ */
  grid-template-columns: repeat(5, 1fr);  /* 5 columns                                        https://www.w3schools.com/cssref/pr_grid-template.php    */
  gap: 10px;
}

.grid-item {
  background-color: #ffffff;
  padding: 10px;
  border-radius: 5px;
  color: white;
}

.grid-item:nth-child(n+1):nth-child(-n+5) {
  background-color: rgba(80, 80, 80, 0.2);
}
.grid-item:nth-child(n+6):nth-child(-n+35) {
  background-color: rgba(0, 255, 0, 0.2);
}
</style>
