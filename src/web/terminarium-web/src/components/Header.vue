<!------------------------------------------------------------------------------------------
   Page header component containing slot for logotype, navigation bar and a Log in button.
   The Log in button is a child component meaning it is its own component nested
   within the header component.
   The navbar of the header changes based on weather the page is is logged in or not.
   Additional links appear to logged in users.
   --------------------------------------------------------------------------------------->
<template>
  <header class="terminarium_header">
    <div class="logo_container">
      <img src="/src/assets/terminarium-logo.png" alt="Terminarium logo">
    </div>
    <nav class="header_nav_bar" v-if="!isLoggedIn"> <!-- Signed out user menu -->
      <!-- TODO: Set links -->
      <a href="#" class="header_link">About</a>
      <a href="#" class="header_link">Help</a>
      <a href="#" class="header_link">Contact</a>
    </nav>
    <nav class="header_nav_bar" v-else>             <!-- Signed in user menu -->
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
      <AccessButton></AccessButton>                 <!-- The 'AccessButton' is imported component and serves as a sign in/out button -->
    </div>
  </header>
</template>

<script>
import AccessButton from "@/components/AccessButton.vue";

export default {
  name: "SiteHeader",
  components: {AccessButton}, // Access to the child component.
  data: function () {
    return{
      // TODO: actually implement logic to check if user is logged in
      // I suggest we introduce a global variable 'isLoggedIn' to the app so that all components that need it can access it from root
      isLoggedIn: true // This would then be isLoggedIn: this.$root.isLoggedIn
    }
  }
}
</script>

<style scoped>                  /* Style scoped applies css properties to HTML elements but only targets the elements of the component it is in. */

.terminarium_header {
  background-color: rgba(0, 0, 0, 0.301);
  color: #fff;
  display: flex;               /* Adapting to screen size*/
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
  transition: transform 0.3s ease-in-out;  /* Defines how the transition between two states will look.  */
}                                          /* In this case the links will move smoothly in and out between scale 1 and 1.1 when hovered  */


.header_link:hover {
  transform: scale(1.1);                  /* Makes element  10 % larger  */
}

.header_button {
  margin: 20px;
  width: 250px;
}

</style>
