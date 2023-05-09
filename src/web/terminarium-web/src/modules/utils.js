// *** Utility functions ***

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