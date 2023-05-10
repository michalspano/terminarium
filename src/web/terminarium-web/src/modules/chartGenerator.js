import { Chart } from 'chart.js/auto';

/**
 * An immutable object that maps sensor types to colors
 * @type {Object} graphColors
 */
const graphColors = Object.freeze({
    "temperature":  "rgba(255, 99, 132, 0.75)", // red
    "humidity":     "rgba(54, 162, 235, 0.75)", // blue
    "moisture":     "rgba(75, 192, 192, 0.75)", // green
    "light":        "rgba(255, 206, 86, 0.75)", // yellow
    "loudness":     "rgba(153, 102, 255, 0.75)" // purple
});

/**
 * Function to generate a line graph using {@code Chart.js}
 * @param {Array} chartData - a sequence of values to be displayed on the chart
 * @param {String} elementID - the ID of the HTML element that will contain the chart
 * @param {String} sensorType - the type of the sensor that the chart will display 
 * @returns {Chart} a {@code Chart.js} instance
 */

export const generateLineGraph = (chartData, elementID, sensorType) => {
    const context = document.getElementById(elementID).getContext('2d');
    const graphColor = graphColors[sensorType];

    const config = {
        type: 'line',                           // type of graph: linear
        data: {
            labels: Array.from({                // generate an array of empty strings
                length: chartData.length        // with the same length as the chart data
            }, () => ''),               // the y-axis is hidden, hence the empty strings
            datasets: [{
                data: chartData,                //  the data to be displayed
                borderColor: graphColor,        //  the color of the line
                backgroundColor: graphColor,    //  the color of the area under the line
            }]
        },
        options: {
            plugins: {
                legend: {
                    display: false          // hides the legend
                }
            },
            animation: {
                duration: 0                 // removes the animation
            },
            responsive: false,              // should not resize the chart canvas when its container does
            scales: {                       // hides the x and y axis
                y: {
                    max: 100,
                    display: false,
                },
                x: {
                    display: false
                }
            },
            elements: {                    // hides the points on the line
                point: {
                    radius: 0
                }
            }
        },
    };

    // Return the chart instance
    return new Chart(context, config);
};