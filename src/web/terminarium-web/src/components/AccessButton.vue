<!----------------------------------------------------------------------------------
    The "AccessButton" component is used to dynamically display the appropriate
    "log in" or "log out" -button. Depending on the User's current login status.
----------------------------------------------------------------------------------->

<template>
    <button @click="accessButtonAction" 
    type="button" 
    class="access">{{ accessButtonDescription }}</button>
</template>


<script>
/**
 * Exports the "component definition object" for efficient re-use in other modules.
 * The additional in-line syntax following "export default" is automatically added by
 * the Vue-compiler for type inference / support.
 */
export default {
    name: "AccessButton.vue",
    data () {
        return {
            // Placeholder hard-coded value
            isLoggedIn: false
            // TODO: actually implement logic to check if user is logged in
            // (likely to be a computed value instead)
        };
    },

    computed: {
        // Return the correct button description.
        accessButtonDescription() {
            if (this.isLoggedIn) {
                return "log out";
            } else {
                return "log in";
            }
        }
    },

    methods: {
        // Either redirect to the login-page, or log the User out and redirect to the home-page
        accessButtonAction() {
            if (this.isLoggedIn) {
                // TODO: insert logic to log the user out and redirect them to login page
            } else {
                // TODO: insert logic to redirect user to login page
            }
        }
    }
}
</script>


<style scoped>
/* Outline that applies to all component elements - helpful during development process */
/* TODO: Remove */
* {
    outline: red dashed 1px;
}
</style>
