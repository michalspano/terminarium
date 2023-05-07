<!-- Page header containing slot for logotype, navigation bar and a button -->
<template>
  <header class="terrminarium_header">
    <div class="logo_container">
      <img src="src/assets/terminarium-logo.png" alt="terminarium-logo">
    </div>
    <nav class="header_nav_bar" v-if="!isLoggedIn">
      <!-- TODO: Set links -->
      <a href="#" class="header_link">About</a>
      <a href="#" class="header_link">Help</a>
      <a href="#" class="header_link">Contact</a>
    </nav>
    <nav class="header_nav_bar" v-if="isLoggedIn">
      <!-- TODO: Set links -->
      <a href="#" class="header_link">Home</a>
      <a href="#" class="header_link">About</a>
      <a href="#" class="header_link">Help</a>
      <a href="#" class="header_link">Contact</a>
      <a href="#" class="header_link">Your Terrariums</a>
      <a href="#" class="header_link">Monitor Terrarium</a>
      <a href="#" class="header_link">Settings</a>
    </nav>
    <div class="header_button">
      <!-- TODO: Implement button sign in / sign out button component -->
      <button class="placeholder_button">Sign out</button>
    </div>
  </header>
</template>


<script>
  //Only used during development to export and view component
  export default {
    name: "Header.vue",
    data: function () {
      return{

        // Placeholder hard-coded value
        isLoggedIn: true
        // TODO: actually implement logic to check if user is logged in
        // (likely to be a computed value instead)
      }
    }
  }
</script>

<style scoped>                  /* Style scoped applies css properties to HTML elements but only targets the elements of the component it is in. */
* {

  font-family: Cantora One, Georgia;
}


.terrminarium_header {
  background-color: rgba(0, 0, 0, 0.301);
  color: #fff;
  display: flex;               /* Adapting to screen size rgba(0, 0, 0, 0.301)#437649*/
  align-items: center;
  height: 100px;
  position: fixed;
  top: 0;
  left: 0;
  width: 100%;
  padding: 20px;
}

.logo_container {
  margin-right: 5px;
}

.header_nav_bar {
  display: flex;              /* Adapting to screen size */
  flex: 1;                    /* Resizes when growing and shrinking */
  justify-content: center;    /* Centers the flex items horizontally within the container. (The links are always centered )  */
}

.header_link {
  margin: 10px;
  color: #fff;
  text-decoration: none;
}

.header_link:hover {
  transition: transform 0.3s ease-in-out;
  transform: scale(1.1);
}

.header_button {
  margin: 20px;
  width: 250px;
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
