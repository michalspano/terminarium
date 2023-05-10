<!-- Create the HTML template: an empty canvas element with unique ID, width and height
    The id, if not given, will be generated automatically: lineGraph-<index>. Otherwise,
    if the id is provided, it will be used instead (instead of the generated one).
-->
<template>
    <canvas :id="canvasID" :width="width" :height="height"></canvas>
</template>

<script>
    // Import the required JS modules
    import { generateLineGraph } from '@/modules/chartGenerator.js';
    import { readSensorRange } from '@/modules/fetch.js';

    /* Set the graph index to 0; this value is used to track how many graphs are
     * instantiated on the page; hence the unique ID (which is handled automatically
     * upon instantiation) */
    window.graphIdx = 0;

    export default {
        name: 'Chart',
        props: {
            // The id is optional; if not provided, it will be generated automatically
            id: {
                type: String,
                default: undefined
            },
            // The sensor type is required to fetch the correct data from the database
            sensorType: {
                type: String,
                default: true
            },
            // The width and height are optional, but can be used to change the size of the graph
            // The default values are 200x200
            width: {
                type: String,
                default: '200'
            },
            height: {
                type: String,
                default: '200'
            },
            // The range is optional, it is used to change the time range of the entries
            range: {
                type: String,
                default: 24
            }
        },
        mounted() {
            readSensorRange(this.range).then((data) => {
                // Ensure that the data object is not empty
                if (data[this.sensorType] === undefined) return;

                // Extract the values from the object given the sensor type
                // and generate the line graph
                const values = data[this.sensorType].map((entry) => entry.value);
                generateLineGraph(values, this.canvasID, this.sensorType);
            });
        },
        beforeCreate() {
            // If the id is not provided, generate a unique id
            if (this.id === undefined) {
                this.canvasID = 'lineGraph-' + (window.graphIdx + 1);
                window.graphIdx++;

            } else this.canvasID = this.id; // otherwise, use the provided id
        }
    }
</script>