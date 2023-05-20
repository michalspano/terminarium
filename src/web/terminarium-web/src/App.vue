<script setup>
import DefaultPageLayout from './components/DefaultPageLayout.vue';
import HomePage from './components/HomePage.vue';
import SelectTerrarium from './components/SelectTerrariumPage.vue';
import SetSensorRanges from './components/SetSensorRanges.vue';
import UserSettings from './components/UserSettings.vue';
import '@/css/global.css';

// Import the "computed()" method from Vue Composition API. 
// Used inside the "provide()" option/function.
// More info: https://vuejs.org/api/reactivity-core.html#computed
import { computed } from 'vue'
</script>

<template>
  <div id="app">
    <!-- Component containing the elements (components) that are always part of the website's layout -->
    <DefaultPageLayout @access-button-event="handleAccessButtonEvent" />

    <!-- The "KeepAlive" tag wraps the loaded components and caches them to maintain state 
      (keeps the same component instance alive). Only components that are "included" will be cached. -->
    <KeepAlive include="SelectTerrarium, SetSensorRanges">
      <component v-bind:is="currentView" />
    </KeepAlive>
  </div>
</template>

<script>
// Decide which component to load - based on defined paths (routes) correlating to the URL hash fragment.
const routes = {
  "/": HomePage,
  "/set-sensor-ranges": SetSensorRanges,
  "/settings": UserSettings,
  "/your-terrariums": SelectTerrarium,
}

export default {
  components: {
    DefaultPageLayout,
    HomePage,
    SelectTerrarium,
    SetSensorRanges,
    UserSettings
  },

  data() {
    return {
      currentPath: window.location.hash,    // Initialise currentPath as the current URL hash fragment.
      isLoggedIn: false             // Initialise the User's login status to false.
    }
  },

  mounted() {
    // Add an eventListener to the "hashchange" event.
    // The event is triggered anytime the URL hash fragment changes.
    // Automatically updates currentPath to the new hash value.
    window.addEventListener("hashchange", () => {
      this.currentPath = window.location.hash
    })
  },

  provide() {
    return {
      // This prop is "injected" by components further down in the component hierarchy.
      // Using the imported "computed()" API from Vue ensures that the prop is reactive, meaning:
      // when the boolean changes, the change is reflected in any sub-component injecting it.
      isLoggedIn: computed(() => this.isLoggedIn)
    }
  },

  computed: {
    currentView() {
      // Slice "currentPath" at index 1 to remove the "#" and compare it to the defined "routes".
      // If slice() results in a falsy value (empty String) - display the HomePage. (First OR-condition)
      // If the component retrieved from routes is "undefined", due to the String not being formatted correctly,
      // we - again, display the HomePage instead. (Second OR-condition)
      const componentToLoad = routes[this.currentPath.slice(1) || "/"] || HomePage  // If desired; replace "HomePage" with a "404 not found"-component. 

      // Validate that the User has access (is logged in) for certain components to be displayed.
      // Otherwise the HomePage is displayed.
      if (!this.isLoggedIn && (componentToLoad === SelectTerrarium || componentToLoad === SetSensorRanges || componentToLoad === UserSettings)) {
        return HomePage   // TODO: replace HomePage with "401 unauthorized"-component
      } else {
        return componentToLoad
      }
    }
  },

  methods: {
    // Method for when the AccessButton-component has been clicked (login/logout button).
    // This event propagates through: AccessButton --> Header --> DefaultPageLayout --> App (this file). 
    // In both of the intermediary components the event is re-emitted.
    handleAccessButtonEvent() {
      if (this.isLoggedIn) {
        window.location.href="#/"   // Returns the User to the HomePage when they log out.
        this.isLoggedIn = false
      } else {
        this.isLoggedIn = true     // TODO: replace this line with a "window.location.href" redirecting to the login page, IF it's added.
      }
    }
  }
}
</script>
