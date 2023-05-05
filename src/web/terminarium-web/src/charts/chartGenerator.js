import {Chart} from 'chart.js/auto';
//Array for storing label names and arbitrary chosen colors
const lineLabel = [
    {label: 'Temperature', color: '#EDDFB3'},
    {label: 'Humidity', color: '#6e7c4e'},
    {label: 'Moisture', color: '#B09B71'},
    {label: 'Light', color: '#bdd514'},
    {label: 'Loudness', color: '#af511f'}
];

export function generateLineGraph(tempData, humiData, moistData, lightData, loudData, canvas, chartTitle, numOfXLabels) {
    const context = document.getElementById(canvas).getContext('2d');

    //Generates an array of integers from 1 to numOfXLabels value
    const xLabels = [];
    for (let i = 1; i <= numOfXLabels; i++) {
        xLabels.push(i);
    }
    //Array consisting of all data-points
    const data = [tempData, humiData, moistData, lightData, loudData];

    //Generating datasets containing data values and related configurations
    const datasets = [];
    for (let i = 0; i < lineLabel.length; i++) {
        datasets.push({
            label: lineLabel[i].label,
            data: data[i],
            borderColor: lineLabel[i].color,
            backgroundColor: lineLabel[i].color,
            axis: 'y',
        })
    }
    const config = {
    type: 'line',                       //type of graph - e.g. logarithmic, linear
        data: {
            labels: xLabels,
            datasets: datasets
        },
        options: {
            responsive: true,           //Resizes the chart canvas when its container does - see documentation
            interaction: {
                mode: 'index',
                intersect: true,
            },
            plugins: {
                title: {
                    display: true,
                    text: chartTitle,
                }
            },
            scales: {
                y: {
                    type: 'linear',
                    display: true,
                max: 100,               //Changes scale of y axis, if omitted it will adjust automatically
                }
            },
        },
    };
    new Chart(context, config);
}