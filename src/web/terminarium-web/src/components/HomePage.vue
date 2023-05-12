<template>
  <div>
    <div class="text-wrapper">

      <h1 class="description-header">Unmatched Care</h1> 

      <p>Experience an all-in-one integrated system for monitoring your terrarium.</p>
      <p> Using our precise and high-powered sensors, the environmental conditions 
            <br>of your enclosure can be read from anywhere at any time.</p>
      <p> Never let an emergency go unnoticed. Do the best for the lives in your care.</p>
    </div>   
    
    <div class="video-wrapper">
      <vue-plyr>
        <div data-plyr-provider="youtube" data-plyr-embed-id="a_XenRF_u9Y"></div>
      </vue-plyr>
    </div>
  </div>
</template>

<script>
export default {
  name: 'Home',
  mounted() {
  }
}
</script>

<style>
.text-wrapper {
  width: 65%;
  float: left;
  margin-top: 120px;
  margin-left: 3%;
}

h1.description-header {
  
  color: rgb(219, 213, 204);
  font-family: Cantora One, Georgia;
  font-size: 3em;
  text-align: left;
  margin-bottom: 0.5em;
  display: block;
}

p {
  color: rgb(219, 213, 204);
  font-family:Cantora One, Georgia;
  font-size: 1.1rem;
  margin-top: 5%;
  display: block;
}

.video-wrapper {
  position: absolute;
  top: 180px;
  right: 5%;
  width: 35%;
  box-shadow:#437649 0px 2px 4px, #437649 0px 7px 13px -3px,#437649 0px -3px 0px inset;
  border: 1px solid rgba(13, 255, 0, 0.76);
  transform: scale(1.05);
}

</style>

