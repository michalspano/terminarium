import {readSensorRange} from "./fetch.js";

// Calculates the average value for each sensor reading in a specific interval
export function averageSensorValues(hours) {
    return readSensorRange(hours).then((fetchData) => {             // fetches sensor readings

        const averageValues = new Map();                            // map for storing average values.
        for (const sensorType in fetchData) {                       // parses sensor readings for each sensor
        const values = fetchData[sensorType].map((entry) => parseFloat(entry.value)); 
            averageValues.set(sensorType, calculateAverage(values)); // calculates average and adds value to a map
        }
        return averageValues;
    })
}


const calculateAverage = (values) => {
    return values.reduce((a, b) => a + b, 0) / values.length;       //Calculates the average sensor reading from an array of values
}