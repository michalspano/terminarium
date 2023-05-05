import { generateLineGraph } from '/src/charts/chartGenerator.js';

//generates random data for testing purposes,
function generateDummyData(amount, interval) {
  const data = [];
  for (let i = 0; i < amount; i++) {
    data.push(Math.floor(Math.random() * interval));
  }
  return data;
}

function chartTest() {
  const tempDummyData = generateDummyData(100,30);
  const humiDummyData = generateDummyData(100,40);
  const moistDummyData = generateDummyData(100,25);
  const lightDummyData = generateDummyData(100,20);
  const loudDummyData = generateDummyData(100,10);
  const chartTitle = 'Sensor Ranges';
  const numOfXLabels = 100;
  const canvasID = 'lineGraphTest';



generateLineGraph(tempDummyData, humiDummyData, moistDummyData, lightDummyData, loudDummyData, canvasID, chartTitle, numOfXLabels);
}

chartTest();
