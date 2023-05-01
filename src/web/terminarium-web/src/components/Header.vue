// Page header containing slot for logotype, navigation bar and a button
<template>
  <header class="terrminarium_header">
    <div class="logotype">
      // TODO: implement logo
      <img src="" alt="Terrminarium logo">
    </div>
    <nav class="header_nav_bar">
      // TODO: Set links
      <a href="#" class="header_link">About</a>
      <a href="#" class="header_link">Help</a>
      <a href="#" class="header_link">Contact</a>
    </nav>
    <div class="header_button">
      // TODO: Implement button sign in / sign out button component
      <button class="placeholder_button">Sign in / sign out</button>
    </div>
  </header>
</template>


<script>
//Only used during development to export and view component
export default {
  name: "Header.vue"
}
 
</script>

<style scoped>                 /* Style scoped applies css properties to HTML elements but only targets the elements of the component it is in. */

* {
  outline: red dashed 1px;    /* SUPER GOOD TIP!!! This outlines all your elements which makes it way easier to see effects and catch bugs.
                               Will be removed when doing final styling */
}
.terrminarium_header {
  background-color: #5A5A5A;
  color: #fff;
  display: flex;              /* Adapting to screen size */
  align-items: center;
  height: 100px;
  position: fixed;
  top: 0;
  left: 0;
  width: 100%;
  padding: 20px;
}


.logotype {
  margin: 20px;
}


.header_nav_bar {
  display: flex;              /* Adapting to screen size */
  flex: 1;                    /* Resizes when growing and shrinking */
  justify-content: center;    /* Centers the flex items horizontally within the container. (The links are always centered )  */
}


.header_link {
  margin: 10px;
  color: #fff;
}


.header_button {
  margin: 20px;
}


.placeholder_button {        /* This will be replaced */
  margin: 10px;
  background-color: #000;
  border: none;
  color: #fff;
  padding: 10px;
  border-radius: 5px;
  cursor: pointer;
}
</style>
