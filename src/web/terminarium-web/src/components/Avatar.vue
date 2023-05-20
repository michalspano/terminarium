<!-----------------------------*COMPONENT DESCRIPTION*------------------------------------------
    This component is used to dynamically display the correct image and text set for a specific 
    terrarium Avatar. It also enables the user to edit the name and image, and delete unwanted 
    instances, of the component, by emitting events that can be handled by the parent component.

    Takes external props from its parent component. The required ones are:
        - "image": the (partial) filename of an avatar image located in the "assets"-directory.
        - "name": the specific terrarium name set by the user.
----------------------------------------------------------------------------------------------->

<template>
    <div class="avatar" >
        <img 
            src="/src/assets/button-delete-avatar.png" 
            alt="delete button"
            id="delete-button"
            v-if="isEditable"
            @click="$emit('deleteButtonEvent', this.index)"
        >
        <div class="avatar-container">
            <img 
                v-bind:src="imageSrc" 
                alt="Avatar picture"
                v-bind:class="{ 'interactable-avatar': isEditable || isClickable }"
                v-bind:style="{width: size, height: size}"
                draggable="false"
                @click="handleAvatarClicked"
            >
            <input 
                type="text" 
                class="input-box"
                ref="inputBox"
                maxlength="20"
                v-model.trim.lazy="localName"
                @keydown.enter="handleEnterKeyPress"
                @blur="handleNameChange"
                v-if="isEditable"
            >
            <div class="terrariumName" v-else>{{ this.name }}</div>
        </div>
    </div>
</template>


<script>
/**Exports the "component definition object" for efficient re-use in other modules.
 * The additional in-line syntax following "export default" is automatically added by
 * the Vue-compiler for type inference / support. */
export default {
    name: "Avatar",
    mounted() {
        if (this.isEditable) {                  // Only equates to 'true' when a new Avatar-component instance gets added to the "SelectTerrariumPage" list.
            this.$nextTick(() => {              // Delay to ensure that everything is properly initialised and rendered, before:
                this.highlightSelectTextbox();  // Calls function to focus and select name input field for the new Avatar.
            })
        }
    },

    data() {
        return {
            localName: ""       // Needed to correctly render the terrariums name inside the input text field, and termporarily store new values.
        }                       // The "inputBox" element v-models this prop to both display and update it.
    },


    watch: {
        name: {                             // Watches the external prop "name", triggers when it changes.
            handler(newName) {              // handler() is a method that let's us attach an "immediate" option.
                this.localName = newName;   // Sets the "localName" prop to mirror "name". 
            },
            immediate: true                 // Makes the watcher fetch initial data - otherwise, watchers are "lazy" by default.
        }                                   // https://vuejs.org/guide/essentials/watchers.html#eager-watchers
    },

    /**"props:" declares which external props the child component accepts from its parent.
     * Here we are using the "object-syntax" for prop validation. 
     * More info can be found in the official docs: https://vuejs.org/guide/components/props.html */
    props: {
        image: {                // Determines the URL filepath.
            type: String,
            required: true
        },

        size: {                 // Determines the size of the Avatar.
            type: String,
            default: "150px"
        },

        name: {                 // Determines the Terrarium name.
            type: String,
            required: true
        },

        index: {                // The index of an Avatar instance in the parent component array when rendered in v-for loop.
            type: Number,       // Passed back to the parent component when an event is triggered.
            default: -1
        },

        isClickable: {          // Determines if the Avatar is interactable by clicking on it.
            type: Boolean,
            default: true       // By default the value is true; the parent component must pass a "false" value to disable it.
        },

        isEditable: {           // Determines if the Avatar (external props) can be edited (to change its appearance).
            type: Boolean,
            default: false
        }
    },

    computed: {
        // Return full file-path for image asset.
        imageSrc() {
            return (`/src/assets/avatar-${this.image}.png`);
        }
    },

    methods: {
        /**Emits an event for the parent component to handle when and if the Avatar is clickable/editable.
         * More information in official docs: https://vuejs.org/guide/components/events.html */
        handleAvatarClicked() {
            if (this.isClickable || this.isEditable) {    // Can be separated into if-else if extended to provide different functionalities.
                this.$emit("avatarClicked", this.index, this.image);    // Such as emitting multiple different events.
            }
        },

        // Emits the (local) name-change to the Parent component so that it can change the value of the external prop.
        // It is then passed back to the child-component in order to update its "real" name.
        handleNameChange() {
            this.$emit('updateName', this.index, this.localName);
        },

        // Handles event triggered by the user pressing "Enter"-key inside text input field.
        handleEnterKeyPress() {
            this.$refs.inputBox.blur();     // Because of the @blur event listener this will trigger handleNameChange().
        },                                  // Therefore we don't need to explicitly call it.

        // Focuses the text input field and selects all its contents. 
        highlightSelectTextbox() {
            this.$refs.inputBox.focus();
            this.$refs.inputBox.select();
        }
    }
}
</script>


<style scoped>
.avatar {
    position: relative;
}

.interactable-avatar {
    cursor: pointer;
}

.avatar-container {
    max-width: 100px;    
}

#delete-button {
    position: absolute;
    left: 73px;
    bottom: 95px;
    border-radius: 50%;
    height: 30px;
    width: 30px;
    cursor: pointer;
}

.input-box {
    display: block;
    flex-direction: column;
    width: 100%;
    height: 12px;
    text-align: center;
    color: white;
    background-color: rgba(255, 255, 255, 0.2);
    border-color: rgba(69, 192, 89, 1)
}

.terrariumName {
    display: flex;
    justify-content: center;
    font-weight: bold;
    cursor: default;
    color: white;
    white-space: nowrap;
}

img {
    object-fit: contain;
    border-radius: 33%;
}
</style>
