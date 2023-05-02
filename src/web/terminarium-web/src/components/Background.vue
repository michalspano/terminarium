<template>
    <div class="background-image"></div>
  </template>
  
  <style>
  .background-image {
    background-image: url('../assets/Background.jpg');
    background-size: cover;
  background-position: center;
  width: 100%;
  height: 100%;
  position: absolute;
  top: 0;
  left: 0;
  z-index: -1;
  }
  </style>
  
  <script>
  export default {
    name: 'Background'
  }
  </script>