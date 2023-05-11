<template>
  <!-- Container for the form -->
  <div class="form-entries">
    <!-- 1st row: name and avatar -->
    <div class="row-name">
      <img class="avatar" src="@/assets/avatar-lizard.png" alt="avatar">
      <div class="form-name">
        <label for="name" class="label-name">Name:</label>
        <input class="input-name" name="name" id="name" type="text">
      </div> 
    </div>
    <!-- 2nd row: username row -->
    <div class="row-form-user">
      <label for="username" class="label-user-pass">Username:</label>
      <input class="input-user" name="username" id="username" type="text">
    </div>
    <!-- 3rd row: password row -->
    <div class="row-form-user">
      <label for="password" class="label-user-pass">Password:</label>
      <input class="input-user" name="password" id="password" type="password">
    </div>
    <!-- 4th row: buttons -->
    <div class="button-container"> 
      <!--TODO: handleClick to be implemented -->
      <button class="btn" @click="handleClick">Cancel</button>
      <button class="btn" @click="handleClick">Save</button>
    </div>  
  </div>
</template>
 
 <script>
  // TODO: handleClick to be implemented
  export default {
    name: 'UserSettings'
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

  /* Styling for the buttons */
  .btn {
    color: black;
    font-size: 2.5vh;
    border: #45C059;
    background-color: #45C059;
    font-family: Cantora One, Georgia;
  }
</style>