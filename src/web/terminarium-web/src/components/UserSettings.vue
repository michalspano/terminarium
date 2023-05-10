<template>
  <div class="form-entries">
    <div class="row-name">
      <img class="avatar" src="../assets/avatar-lizard.png"  alt="avatar">  
      <div class="form-name">
        <label for="name" class="label-name">Name:</label>
        <input class="input-name" name="name" id="name" type="text">
      </div> 
    </div>     
    <div class="row-user-pass">
      <div class="row-margin"></div> 
      <div class="form-user-pass">
        <label for="username" class="label-user-pass">Username:</label>
        <input class="input-user-pass" name="username" id="username" type="text">
      </div>
    </div>
    <div class="row-user-pass">
      <div class="row-margin"></div> 
      <div class="form-user-pass">
        <label for="password" class="label-user-pass">Password:</label>
        <input class="input-user-pass" name="password" id="password" type="password">
      </div>
    </div>
    <div class="button-container"> 
      <!--TODO: handleClick to be implemented -->
      <button class="button" @click="handleClick">Cancel</button>
      <button class="button" @click="handleClick">Save</button>
    </div>  
  </div>
</template>
 
 <script>
 export default {
   name: 'UserSettings', }
 </script>

<style scoped>

.form-entries {                   
  margin: auto;
  margin-top: 16%;
  width: 52%;
}

.row-name {                        
  display: flex;                  
  gap: 15px;
  flex-direction: row;
  align-items: center;
  justify-content: center;
}

.avatar {
  width: 10%;
  height: 10%;
  min-width: 50px;
  min-height: 50px;
  border-radius: 33%;
}

.form-name {
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: left;
}

.label-name {
    font-family:Cantora One, Georgia;
    color: #45C059;
    text-shadow: -1px -1px 0 black, 1px -1px 0 black, -1px 1px 0 black, 1px 1px 0 black;
    display: flex;
}

.input-name { 
  font-family:Cantora One, Georgia;  
  background-color:rgba(0, 0, 0, 0.301);
  color: white;
  padding: 12px 20px;
  font-size: 16px;
  border: 1px solid rgba(0, 0, 0, 0.301);
  border-radius: 0;
  box-sizing: border-box;
}

.row-user-pass {
  display: flex;
}

.row-margin {                /* empty element, used for positioning the form-user-pass class */
  width: 38%;
  min-width: 50px;
  min-height: 50px;
  align-items: left;
  justify-content: left;
}

.form-user-pass {
  display: flex;
  flex-direction: column;
  align-items: left;
  width: 100%; 
  flex-grow: 3;
  margin-top: 0.5%;
  
}

.label-user-pass {
    font-family:Cantora One, Georgia;
    color: #45C059;
    text-shadow: -1px -1px 0 black, 1px -1px 0 black, -1px 1px 0 black, 1px 1px 0 black;
    display: flex;
}

.input-user-pass { 
  font-family:Cantora One, Georgia;  
  background-color:rgba(0, 0, 0, 0.301);
  color: white;
  width: 62%;
  padding: 12px 20px;
  font-size: 16px;
  border: 1px solid rgba(0, 0, 0, 0.301);
  box-sizing: border-box;
}

.button-container {
  display: flex;
  justify-content: center;
  width: 100%;
}

.button {
  display: flex;
  justify-content: center;
  font-family:Cantora One, Georgia;
  font-size: 100%;
  color: black;
  background-color: #45C059;
  border: #45C059;
  margin: 2%;
}
</style>