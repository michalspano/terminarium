<!------------------------*COMPONENT DESCRIPTION*-----------------------------------
    The "AccessButton" component is used to dynamically display the appropriate
    "log in" or "log out" -button. Depending on the User's current login status.
----------------------------------------------------------------------------------->

<template>
    <button @click="$emit('accessButtonEvent')" type="button" class="access">
        {{ accessButtonDescription }}
    </button>
</template>


<script>
/**Exports the "component definition object" for efficient re-use in other modules.
 * The additional in-line syntax following "export default" is automatically added by
 * the Vue-compiler for type inference / support. */
export default {
    name: "AccessButton",
    inject: ['isLoggedIn'],

    computed: {
        // Return the correct button description.
        accessButtonDescription() {
            if (this.isLoggedIn.value) {
                return "log out";
            } else {
                return "log in";
            }
        }
    },
}
</script>


<style scoped>
.access {
  border-radius: 20px;       /* Rounding the edges */
  background-color: green;
  border-color: gold;
  font-size: 16px;
  color: white;
  display: flex;            /* Adapting to screen size */
}
</style>
