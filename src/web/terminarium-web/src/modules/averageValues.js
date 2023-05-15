import {readSensorRange} from "./fetch.js";


/**
 * Calculate the average value for all sensors given a specific interval in hours.
 * @param {number} hours - number of hours to go back in time
 * @returns {Promise.Map<string,number>} a promise which resolves to a Map with the following structure
 * @example (Key: Sensor name, Value: Average sensor reading)
 */

export async function averageSensorValues(hours) {
    return readSensorRange(hours).then((fetchData) => {             // fetches sensor readings

        const averageValues = new Map();                            // map for storing average values.
        for (const sensorType in fetchData) {                       // parses sensor readings for each sensor
            const values = fetchData[sensorType].map((entry) => parseFloat(entry.value)); 
            averageValues.set(sensorType, calculateAverage(values)); // calculates average and adds value to a map
        }
        return averageValues;
    })
}

/**
 * Calculate the average value of an array of numbers
 * @param {Array} values - array of numbers
 * @returns The average of all numbers in values as a number
 */
const calculateAverage = (values) => {
    return values.reduce((a, b) => a + b, 0) / values.length;       //The reduce function sums all values in the values array
}