// *** Utility functions ***

import Paho from 'paho-mqtt';

/**
 * Function to format date and time from the convention used in the database to the default format
 * It is needed to calculate the time difference between the current time and the time of the last 
 * entry in the database, namely in the @function read(hours) function.
 * @param {string} raw_date - date in the format dd-mm-yyyy;hh:mm fetched from the database
 * @returns {Date} a formatted date object in the default format: yyyy-mm-ddThh:mm
 */
export const formatDateTime = (raw_date) => {
    const day = raw_date.slice(0, 2);
    const month = raw_date.slice(3, 5) - 1;
    const year = raw_date.slice(6, 10);
    const hour = raw_date.slice(11, 13);
    const minute = raw_date.slice(14, 16);

    return new Date(year, month, day, hour, minute);
}

/**
 * A function that ensures that the number is always three digits long
 * @param {number} num - a number to be formatted
 * @returns {string} a string of three digits
 */
export const threeDigitFormat = (num) => {
    return num.toString().padStart(3, '0');
};

/**
 * This function is used to initialize the MQTT client based on the hiveMQ public broker
 * and the Paho library (https://www.eclipse.org/paho/clients/js/)
 * @returns {Paho.Client} a new MQTT client
 */
export const MQTTClientInit = () => {
    return new Paho.Client(
            'broker.hivemq.com',
            Number(8000),
            `client-id-${generateUniqueID()}`
    );
};

/**
 * This function is used to generate a pseudo-unique number to be used as a client ID for the MQTT client
 * A further justification of why the function is sufficient can be found here: {@link docs/generateUniqueID.md}.
 * @returns {number} a pseudo-unique number
 */
const generateUniqueID = () => {
    const randomN = Math.floor(Math.random() * 1000) + 1;
    return Math.floor(Date.now() / randomN);
};

/**
 * This function formats the current time to a string in the format yyyy-mm-ddThh:mm.
 * This is a convention used in the database to name the nodes.
 * @returns {string} a formatted timestamp in the format yyyy-mm-ddThh:mm
 */ 
export const createTimestamp = () => {                                         // function returns formatted timestamp
    const date = new Date();                                           // create new Date object with current date/time

    const options = {                                                  // define date/time formatting options
        day: '2-digit',
        month: '2-digit',
        year: 'numeric',
        hour: '2-digit',
        minute: '2-digit',
        hour12: false
    };

    let formattedDate = date.toLocaleString('en-GB', options);         // format using defined options
    formattedDate = formattedDate.replace(',', ';').replace(/\s+/g, ''); // replace ',' between time and date and remove whitespace
    formattedDate = formattedDate.replace(/\//g, '-');                 // replace '/' with '-' in string to not cause node name issues when writing to DB
    return formattedDate;                                              // return formatted timestamp
} 

/**
 * This function formats the raw vibration data received from the MQTT broker to a more readable format.
 * Namely: 'true' -> 'Yes' and 'false' -> 'No'
 * @param {String} vibrationData - the registered vibration data from MQTT
 * @returns 
 */
export const parseVibrationData = (vibrationData) => {
    return vibrationData === 'true' ? 'Yes' : 'No';
};