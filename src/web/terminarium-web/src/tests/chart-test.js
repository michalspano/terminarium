import { generateLineGraph } from '@/modules/chartGenerator.js';
import { readSensorRange } from '@/modules/fetch.js';

/**
 * NOTE: this is not an automated test, but a manual one!
 * This is just a test function to check if the chart generator works
 * It is not used anywhere in the project; it generates a chart for each sensor
 * in the database for the last 72 hours. The embed is put to the body of the 
 * charts.html file.
 * TODO: the removal of this function is pending
 */
const chartTest = () => {
  const HOURS = 72;

  readSensorRange(HOURS).then((data) => {
    for (const sensor in data) {
      const values = data[sensor].map((entry) => entry.value);

      // Just some testing code
      const canvas = document.createElement('canvas');
      const ID = `${sensor}-simple-graph`;
      canvas.id = ID;

      canvas.width = 200; canvas.height = 200;
      document.body.appendChild(canvas);

      // generate the chart
      const chart = generateLineGraph(values, ID, sensor);

      // TODO: do something with the chart (store, modify, etc.)
    }
  });
}

chartTest();
