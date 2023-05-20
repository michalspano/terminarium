<!---------------------------*COMPONENT DESCRIPTION*------------------------------------
    This component defines the contents for the "terrarium menu"-page.
    Lets the user manage their terrariums, displayed as a list of avatars, and 
    provides access to detailed information for each terrarium on a separate page.

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
                    v-on:avatarClicked="handleAvatarClicked"
                />   
                <div class="add-terrarium" v-if="!isFull">
                    <div class="add-button">
                        <img    
                        src="/src/assets/add-button.png" 
                        alt="Add Terrarium button" 
                        class="add-button" 
                        @click="addTerrarium"   
                        >
                    </div>
                    <figcaption id="add-button-text">Add Terrarium</figcaption>
                </div>
            </div>
            <div class="manage-terrariums">
                <button class="button" @click="manageTerrariums">manage terrariums</button>
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

    data() {
        return {
            /**These values are hard-coded for now - later on they will instead be fetched.
             * The user will eventually be able to add, delete, and modify their list of terrariums freely.
             */
            terrariumList: [
                {
                    avatarImage: "avatar-plant.png",
                    avatarName: "Peter Planta"
                },

                {
                    avatarImage: "avatar-lizard.png",
                    avatarName: "Örjan Ödla"
                }
            ]
            
        }
    },

    computed: {
        isFull() {
            return (this.terrariumList.length >= 5);
        }
    },

    methods: {
        /**Adds a new terrarium with a default name and image.
         * The cardinality is computed on demand so that it corresponds 
         * to how many terrariums the user already has.
         */
        addTerrarium() {
            if (this.terrariumList.length < 5) {
                const terrariumCardinality = this.terrariumList.length + 1;
                this.terrariumList.push({ 
                    avatarImage: "avatar-default.png",
                    avatarName: `terrarium #${terrariumCardinality}`
                })
            }
        },

        deleteTerrarium(index) {
            this.terrariumList.splice(index, 1);
        },

        moveTerrarium(oldIndex, newIndex) {
            /**Eventually the user will be able to just drag-and-drop the avatars on-screen to change the terrarium order.
             * This check is somewhat redundant - but is left in, in case of future functionality changes.
             */
            if (newIndex < this.terrariumList.length && newIndex >= 0) {
                this.terrariumList.splice(newIndex, 0, this.terrariumList.splice(oldIndex, 1)[0]);
            }
        },

        /**This method will be re-factored to take the user to the specific terrarium page.
         * Right now it is just moving whichever terrarium was clicked to the first index.
         */
        handleAvatarClicked(oldIndex) {
            this.moveTerrarium(oldIndex, 0);
        },

        manageTerrariums() {
            this.terrariumList.pop();
        }
    }
}
</script>


<style scoped>
/* TODO: supply this section with proper code commenting in a follow-up commit. */

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
}

#add-button-text {
    text-align: center;
    font-weight: bold;
    color: white;
    cursor: default;
    white-space: nowrap;
}

img {
    height: 100px;
    width: 100px;
}

.monitoring-board {
    width: 100%;
}

</style>
