<template>
  <div class="background-image" ref="background"></div>
</template>
  
  <style>
  .background-image {
    background-image: url('../assets/Background.jpg');
    background-size: cover;
    background-position: center;
    background-repeat: repeat-y;
    width: 100%;
    min-height: 100vh;
    position: absolute;
    top: 0;
    left: 0;
    z-index: -1;
  }
  </style>
  
  <script>
  export default {
    name: 'Background',
    mounted() {
      this.$refs.background.style.height = `${document.body.scrollHeight}px`;
    }
  }
</script>