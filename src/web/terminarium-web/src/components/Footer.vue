<template>
    <footer>
        <div class="terminarium_footer">
            <h1>Terrminarium</h1>
        </div>
        <div class="footer-bottom">
            <p> &copy;2023 Copyright: <Terrminarium class="com"></Terrminarium></p>
        </div>
    </footer>
</template>

<script>

export default {
  name: 'Footer.vue'
}
</script>

<style scoped>                

* {
  outline: red dashed 1px;    
}

.terrminarium_footer {
  background-color: #5A5A5A;
  color: #fff;
  display: flex;              
  align-items: center;
  height: 100px;
  position: fixed;
  top: 0;
  left: 0;
  width: 100%;
  padding: 20px;
}
</style>