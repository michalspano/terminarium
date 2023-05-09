import { Chart } from 'chart.js/auto';

/**
 * A dictionary of colors for each sensor type
 * @type {Object} graphColors
 */
const graphColors = {
    "temperature":  "#TODO",
    "humidity":     "#TODO",
    "moisture":     "#TODO",
    "light":        "#TODO",
    "loudness":     "#TODO"
};

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