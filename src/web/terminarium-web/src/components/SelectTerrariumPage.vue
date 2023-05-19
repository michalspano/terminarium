<!---------------------------*COMPONENT DESCRIPTION*------------------------------------
    This component defines the contents for the "select terrarium"-page.
    Lets the user manage their terrariums, displayed as a list of avatars, and 
    provides access to detailed information for a specific enclosure.

    Official documentation, explaining the 'v-for'-directive and 'keys':
    List rendering: https://vuejs.org/guide/essentials/list.html#v-for
    Keys: https://vuejs.org/api/built-in-special-attributes.html#key
--------------------------------------------------------------------------------------->

<script setup>
import Avatar from './Avatar.vue';
import MonitorTerrarium from './MonitorTerrarium.vue';
</script>

<template>
    <div class="page-content">
        <div class="terrariums">
            <div class="avatar-container">
                <!--------------------------------------------------------------------------------------------------------------
                    "v-for" renders a list of items based on an array. Here it does so for all the Avatar-components.
                    Each unique instance will automatically be assigned a key using the index of its position in the array,
                    this is needed for each element to be rendered properly.
                    When the ordering inside the array changes, the keys will automatically be updated to to ensure consistency.

                    For further explanation: refer to the links provided in the component description*.
                --------------------------------------------------------------------------------------------------------------->
                <Avatar
                    v-for="(terrarium, index) in terrariumList"
                    v-bind:key="index"
                    v-bind:image="terrarium.avatarImage"
                    v-bind:name="terrarium.avatarName"
                    v-bind:size="'100px'"
                    v-bind:index="index"
                    v-bind:isEditable="this.isManaging"
                    v-on:avatarClicked="handleAvatarClicked"
                    v-on:deleteButtonEvent="deleteTerrarium"
                    v-on:updateName="updateTerrariumName"
                />   
                <div class="add-terrarium" v-if="!isFull">
                    <div class="add-button-img">
                        <img
                        src="/src/assets/button-add.png" 
                        alt="Add Terrarium button" 
                        class="add-button" 
                        draggable="false"
                        @click="addTerrarium"   
                        >
                    </div>
                    <figcaption id="add-button-text">Add Terrarium</figcaption>
                </div>
            </div>
            <div class="manage-terrariums">
                <button type="button" class="button" @click="manageTerrariums">{{ isManaging ? "submit" : "manage terrariums" }}</button>
            </div>
            <div class="monitoring-board">
                <MonitorTerrarium/>
            </div>
        </div>
    </div>
</template>

<script>
export default {
    name: "SelectTerrarium",
    components: {
        Avatar
    },

    // Triggers certain actions when the component is removed from the DOM (but the instance is cached).
    // https://vuejs.org/api/options-lifecycle.html#deactivated
    deactivated() {
        this.isManaging = false;
    },

    data() {
        return {
            /**These values are hard-coded for now - later on they will instead be fetched.
             * The user will eventually be able to add, delete, and modify their list of terrariums freely.
             */
            terrariumList: [
                {
                    avatarImage: "plant",
                    avatarName: "Peter Planta"
                },

                {
                    avatarImage: "lizard",
                    avatarName: "Örjan Ödla"
                }
            ],

            // List of avatar image-assets. Iterated through when setting the image of a terrarium Avatar.
            imageAssetsList: [
                "default",
                "lizard",
                "plant",
            ],

            // Determine if the user is managing their list of terrariums. 
            // If set to true; enables them to edit the name and image, or delete terrariums.
            isManaging: false
        }
    },

    computed: {
        // Check if the list of terrariums is full.
        isFull() {
            return (this.terrariumList.length >= 5);
        }
    },

    methods: {
        // Add a new terrarium with a default name and image.
        // The cardinality is computed on demand so that it corresponds to how many terrariums the user has in the list.
        addTerrarium() {
            this.isManaging = true;     // Set value to true so that new component passes if-condition inside mounted().
            if (this.terrariumList.length < 5) {
                const terrariumCardinality = this.terrariumList.length + 1;
                this.terrariumList.push({ 
                    avatarImage: this.imageAssetsList[0],
                    avatarName: `terrarium #${terrariumCardinality}`
                });
            }
        },

        // Delete terrarium from list.
        deleteTerrarium(index) {
            this.terrariumList.splice(index, 1);
        },

        // ****** CURRENTLY UNUSED ******   -However, left in for future update(s).
        // Move terrarium to new index in the terrarium list.
        moveTerrarium(oldIndex, newIndex) {
            if (newIndex < this.terrariumList.length && newIndex >= 0) {
                this.terrariumList.splice(newIndex, 0, this.terrariumList.splice(oldIndex, 1)[0]);
            }
        },


        // Handles the actions triggered when an Avatar has been interacted with.
        // For now it only changes the 
        handleAvatarClicked(index, oldImage) {
            if (this.isManaging) {
                this.terrariumList[index].avatarImage = this.cycleAvatarImage(oldImage);
            } else {
                // TODO: Display monitoring info for specific terrarium instance clicked.
            }
        },
       
        // Change an Avatar instance's displayed image by cycling through the array of available avatar image-assets.
        cycleAvatarImage(oldImage) {
            const newImageIndex = (this.imageAssetsList.indexOf(oldImage) + 1) % this.imageAssetsList.length;
            return (this.imageAssetsList[newImageIndex]);
        },

        // Update name of terrarium (Avatar-component instance).
        updateTerrariumName(index, newName) {
            this.terrariumList[index].avatarName = newName;
        },

        // Toggle boolean to enable/disable managing the terrariums.
        manageTerrariums() {
            this.isManaging = !this.isManaging;
        }
    }
}
</script>


<style scoped>

.page-content {
    display: flex;
    flex-direction: column;
    justify-content: flex-end;
    align-items: center;
    margin-top: 150px;
}

.terrariums {
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
    width: 50%;
}

.avatar-container {
    display: flex;
    justify-content: center;
    align-items: flex-end;
    gap: calc(7vw);
}

.manage-terrariums {
    margin-top: 1vh;
    margin-bottom: 2vh;
}

.add-button {
    cursor: pointer;
    border-radius: 50%;
}

#add-button-text {
    text-align: center;
    font-weight: bold;
    color: white;
    cursor: default;
    white-space: nowrap;
}

.button {
    border-radius: 20px;
    background-color: #45C059;
    color: black;
    text-align: center;
    cursor: pointer;

    /* TODO: placeholder: decide on the final value. 
    Currently; same width as the longest possible button text.
    Likely to change with font styling alterations.*/
    min-width: 127px; 
}

img {
    height: 100px;
    width: 100px;
}

.monitoring-board {
    width: 100%;
}

</style>
