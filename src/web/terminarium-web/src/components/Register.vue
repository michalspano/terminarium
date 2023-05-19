<template> 
    <!-- Classes containing heading text -->
     <div class="heading"> 
        <h1>Register!</h1> 
     </div>
     <div class="sub-heading">
        <p>create your account now 
        <br>and start monitoring</p>
     </div> 
    <!-- Container for the form -->
     <div class="form-entries">
      <!-- 1st row: name -->
      <div class="row-form">
        <input class="input" name="name" id="nameID" type="text" v-model="name"
             placeholder="name" >
      </div>
      <!-- 2nd row: username row -->
      <div class="row-form">
        <input class="input" name="username" id="usernameID" type="text" v-model="username"
             placeholder="username" >
      </div>
      <!-- 3rd row: password row -->
      <div class="row-form">
        <input class="input" name="password" id="passwordID" type="password" v-model="password"
            placeholder="password" >
      </div>
      <!-- 4th row: save changes button -->
      <div class="button-container"> 
        <button class="btn" type="button" @click="saveButton()" :disabled="isEmpty">register</button>
      </div>  
    </div>
  </template>

<script>

export default {
  name: 'Register',
  data() {
    return {
      name: '',
      username: '',
      password: '',
    };
  },
  methods:{
    /* this method gets the values entered in the name, username, and password 
    input fields and, as long as they are not empty, updates the current value with the new value.*/
    saveButton(){
      if (!this.isEmpty) {          // user input is only saved if form fields are not empty
        this.saveToLocalStorage(); 
      }
    },

  // save new valid String values to local storage
    saveToLocalStorage() {
        localStorage['name'] = this.name;
        localStorage['username'] = this.username;
        localStorage['password'] = this.password;

    }
  },
  computed: {
    // method returns true if at least 1 field isn't complete
    isEmpty() {
        return this.name === '' || 
               this.username === '' || 
               this.password === '' ;
    }
  }
}

</script>

<style scoped>

  /* Styling for the whole container */
  .form-entries {
    width: 50%;
    margin-left: 30%;
    margin-top: -100px;
  }

   /* Styling for the row of the name, username and password */
   .row-form {
    display: flex;
    margin-top: 0.5%;
    align-items: center;
    flex-direction: column;
   
  }
   /* Styling specific to the input fields */
   .input {
    color: white;
    font-size: 16px;
    padding: 12px 20px;
    box-sizing: border-box;
    font-family: Cantora One, Georgia;
    border: 1px solid rgba(0, 0, 0, 0.301);
    background-color:rgba(0, 0, 0, 0.301);
  }

  /* Spcific styling for the name input field */
  .input{ 
    width: 62%; 
}

  /* Styling for the button container */
  .button-container {
    display: flex;
    display: row;
    gap: 30px;
    justify-content: center;
    padding-top: 2%;
}

 /* Click animation for the button */
   button:active {
   transform: translate(0em, 0.2em);
}

 /* Button click animation disabled when form is empty */
    button:active[disabled] {
    transform: none;
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

/* Styling for the button when disabled */
  .btn:disabled{
    color: #3f4440;
    font-size: 2.5vh;
    background-color: gray;
    font-family: Cantora One, Georgia;
  }

/* Styling for the top text */
  .heading {
    font-family: Cantora One, Georgia;
    font-size: 2em;
    border: black;
    color: #45C059;
    margin-top: 150px;
    margin-left: 60px;      
}

/* Styling for the bottom text */
  .sub-heading {
   font-family: Cantora One, Georgia;
   font-size: 1.5rem;
   border: #45C059;
   color: rgba(245, 245, 245, 0.692);
   margin-top: -60px;
   margin-left: 100px;
  }

  /* Adjust font and margins for smaller size screeens*/
@media (max-width: 768px) {
  .heading {
    font-size: 1.5em;
    margin-top: 100px;
    margin-left: 30px;
  }

  .sub-heading {
    font-size: 1rem;
    margin-top: -40px;
    margin-left: 50px;
  }
}

</style>

