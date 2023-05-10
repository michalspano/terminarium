<!-----------------------------*COMPONENT DESCRIPTION*---------------------------------
    This component is used to dynamically display the correct image and text set for 
    a specific terrarium Avatar.

    Takes external props from its parent component. The required ones are:
        - "image": the filename of an avatar image located in the "assets"-directory.
        - "name": the specific terrarium name set by the user.
-------------------------------------------------------------------------------------->

<template>
    <div class="avatar" >
        <img 
        v-bind:src="imageSrc" 
        alt="Avatar picture"
        v-bind:style="{width: size, height: size}"
        @click="wasClicked"
        >
        <div class="terrariumName">{{ name }}</div>
    </div>
</template>

<script>
/**Exports the "component definition object" for efficient re-use in other modules.
 * The additional in-line syntax following "export default" is automatically added by
 * the Vue-compiler for type inference / support. */
export default {
    name: "Avatar.vue",

    /**"props:" declares which external props the child component accepts from its parent.
     * Here we are using the "object-syntax" for prop validation. 
     * More info can be found in the official docs: https://vuejs.org/guide/components/props.html */
    props: {
        image: {                //Determines the URL filepath.
            type: String,
            required: true
        },

        size: {                 //Determines the size of the Avatar.
            type: String,
            default: "150px"
        },

        name: {                 //Determines the Terrarium name.
            type: String,
            required: true
        },

        index: {                //The index of an Avatar instance in the parent component array.
            type: Number,       //Passed back to the parent component when an event is triggered.
            required: true
        },

        isClickable: {          //Determines if the Avatar is interactable by clicking on it.
            type: Boolean,
            default: true       //By default the value is true; the parent component must pass a "false" value to disable it.
        }
    },

    computed: {
        imageSrc() {
            return (`src/assets/${this.image}`);
        }
    },

    methods: {
        /**Emits an event for the parent component to handle when and if the Avatar is clickable.
         * More information in official docs: https://vuejs.org/guide/components/events.html */
        wasClicked() {
            if (this.isClickable) {
                this.$emit("avatarClicked", this.index);
            }
        }
    }
}
</script>

<style>
/* Outline that applies to all component elements - helpful during development process */
/* TODO: Remove */
* {
    outline: green dashed 1px;
}

.terrariumName {
    text-align: center;
    font-weight: bold;
    cursor: default;
    color: white;
}

img {
    object-fit: contain;
    border-radius: 33%;
    cursor: pointer;
}

</style>
