<template>
  <div class="monitor_terrarium_box">
    <div class="grid-container">
      <div class="grid-item">Sensor name</div>
      <div class="grid-item">Current reading</div>
      <div class="grid-item">1 h Avg</div>
      <div class="grid-item">24 h Avg</div>
      <div class="grid-item">Graph</div>

      <div class="grid-item">{{ sensorNames[0] }}</div>
      <div class="grid-item">2</div>
      <div class="grid-item">3</div>
      <div class="grid-item">4</div>
      <div class="grid-item">5</div>

      <div class="grid-item">{{ sensorNames[1] }}</div>
      <div class="grid-item">2</div>
      <div class="grid-item">3</div>
      <div class="grid-item">4</div>
      <div class="grid-item">5</div>

      <div class="grid-item">{{ sensorNames[2] }}</div>
      <div class="grid-item">2</div>
      <div class="grid-item">3</div>
      <div class="grid-item">4</div>
      <div class="grid-item">5</div>

      <div class="grid-item">{{ sensorNames[3] }}</div>
      <div class="grid-item">2</div>
      <div class="grid-item">3</div>
      <div class="grid-item">4</div>
      <div class="grid-item">5</div>

      <div class="grid-item">{{ sensorNames[4] }}</div>
      <div class="grid-item">2</div>
      <div class="grid-item">3</div>
      <div class="grid-item">4</div>
      <div class="grid-item">5</div>

      <div class="grid-item">{{ sensorNames[5] }}</div>
      <div class="grid-item">2</div>
      <div class="grid-item">3</div>
      <div class="grid-item">4</div>
      <div class="grid-item">5</div>

      </div>
    </div>
</template>

<script>

export default {
  name: "MonitorTerrarium",
  data: function () {
    return {
      sensorNames: ["Moisture", "Light", "Noise", "Temperature", "Humidity", "Vibration"],
    }
  },
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