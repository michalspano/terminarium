<template>
  <!-- Container for the form -->
  <div class="form-entries">
    <!-- 1st row: name and avatar -->
    <div class="row-name">
      <img class="avatar" src="@/assets/avatar-lizard.png" alt="avatar" draggable="false">
      <div class="form-name">
        <label for="nameID" class="label-name">Name:</label>
        <input class="input-name" name="name" id="nameID" type="text" v-model="name">
      </div> 
    </div>
    <!-- 2nd row: username row -->
    <div class="row-form-user">
      <label for="usernameID" class="label-user-pass">Username:</label>
      <input class="input-user" name="username" id="usernameID" type="text" v-model="username">
    </div>
    <!-- 3rd row: password row -->
    <div class="row-form-user">
      <label for="passwordID" class="label-user-pass">Password:</label>
      <input class="input-user" name="password" id="passwordID" type="password" v-model="password">
    </div>
    <!-- 4th row: save changes button -->
    <div class="button-container"> 
      <button class="btn" type="button" @click="saveButton()">Save</button>
    </div>  

    <!-- confirmation text indicating changes were saved or not -->
    <div class="saved-message-container">
      <p v-if="isSaved && !isEmpty" class="saved-message">Changes saved succesfully!</p>
      <p v-if="isSaved && isEmpty" class="saved-message">No changes saved!</p>  
    </div>

    
  </div>
</template>
 
 <script>

  export default {
    name: 'UserSettings',
    data() {
      return {
        name: '',
        username: '',
        password: '',
        isSaved:false,
        isEmpty:false
      };
    },
    // populate variables with values saved in local storage
    created() {
      this.name = localStorage['name'] || '' ;
      this.username = localStorage['username'] || '' ;
      this.password = localStorage['password'] || '' ;
    },
    methods:{
      /* this method gets the values entered in the name, username, and password 
      input fields and, as long as they are not empty, updates the current value with the new value.*/
      saveButton(){
        this.isSaved = true;                  // flag for the confirmation text to print when save button is pressed

        // assign field values to new variables
        const newName = this.name;
        const newUsername = this.username;
        const newPassword = this.password;

        // isEmpty boolean is true if each field is empty
        this.isEmpty = newName === '' && 
                       newUsername === '' && 
                       newPassword  === '';

        if (!this.isEmpty){                   // if at least 1 field isn't empty
          this.saveToLocalStorage();          // save values to local storage

      }
    }, 
    // save new valid String values to local storage
    saveToLocalStorage() {
      this.name !== '' ? localStorage['name'] = this.name : '';
      this.username !== '' ? localStorage['username'] = this.username : '';
      this.password !== '' ? localStorage['password'] = this.password : '';

    }
  }
}

</script>

<style scoped>

  /* Styling for the whole container */
  .form-entries {
    width: 50%;
    margin: auto;
    margin-top: 200px;
  }

  /* Styling for the name row */
  .row-name {
    display: flex;
    gap: 15px;
    flex-direction: row;
    align-items: center;
    justify-content: center;
  }

  /* Styling for the name form */
  .form-name {
    display: flex;
    width: 50%; /* stretch the form to fill the container */
    flex-direction: column;
    justify-content: center;
    align-items: left;
  }

  /* Styling for the avatar of the user in the first row */
  .avatar {
    width: 10%;
    height: 10%;
    min-width: 50px;
    min-height: 50px;
    border-radius: 33%;
  }

  /* Styling for the row of the username and password */
  .row-form-user {
    display: flex;
    margin-top: 0.5%;
    align-items: center;
    flex-direction: column;
  }

  /* Styling for the labels */
  .label-name, .label-user-pass {
    color: #45C059;
    font-family: Cantora One, Georgia;
    text-shadow: -1px -1px 0 black, 1px -1px 0 black, -1px 1px 0 black, 1px 1px 0 black;
  }

  /* Styling for the name label */
  .label-user-pass {
      width: 60%; /* the alternative to text-align: left */
  }

  /* Styling specific to the input fields */
  .input-name, .input-user {
    color: white;
    font-size: 16px;
    padding: 12px 20px;
    box-sizing: border-box;
    font-family: Cantora One, Georgia;
    border: 1px solid rgba(0, 0, 0, 0.301);
    background-color:rgba(0, 0, 0, 0.301);
  }

  /* Spcific styling for the name input field */
  .input-user { width: 62%; }

  /* Styling for the buttons container */
  .button-container {
    display: flex;
    display: row;
    gap: 30px;
    justify-content: center;
    padding-top: 2%;
}

 /* Movement for the button */
  button:active {
   transform: translate(0em, 0.2em);
}

  /* Styling for the button */
  .btn {
    color: black;
    font-size: 2.5vh;
    border: #45C059;
    background-color: #45C059;
    font-family: Cantora One, Georgia;
    cursor: pointer;
  }

  /* Styling for the message container */
  .saved-message-container{
    display: flex;
    display: row;
    gap: 30px;
    justify-content: center;
    padding-top: 2%;
  }

  /* Styling for the message */
  .saved-message {
  color: white;
  font-family: Cantora One, Georgia;
}

</style>