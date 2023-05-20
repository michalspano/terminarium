<template>
  <div class="background-image" ref="background"></div>
</template>

  <style>
  .background-image {
    background-image: url('../assets/Background.jpg');
    background-size: cover;
    background-position: center;
    background-repeat: no-repeat;
    position: fixed;
    top: 0;
    left: 0;
    width: 100%;
    height: 100%;
    z-index: -1;
  }
  </style>

  <script>
  export default {
    name: 'Background',
    mounted() {// runs after the component has been put to the DOM
      this.dynamicBackgroundHeight();                                       // Sets the initial page height when every component is on the DOM.
      window.addEventListener('resize', this.dynamicBackgroundHeight); // when a resize event happens dynamicBackgroundHeight is called.
    },                                                                      // (A resize event is by default triggered by resizing the browser window)
    methods: {
      dynamicBackgroundHeight() {
        this.$refs.background.style.height = `${window.innerHeight}px`;     // sets css height property dynamically based the height of screen.
                                                                            // height is set to 100 % in .background-image so background will fill all screens.
      }
    }
  }
  </script>