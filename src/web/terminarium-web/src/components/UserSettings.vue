<template>
    <form>
    <div class="form-name">
      <label for="name" class="label-white-name">Name:</label>
      <input class="input-name" name="name" id="name" type="text">
    </div> 
 
    <div class="form">
      <label for="username" class="label-white">Username:</label>
      <input class="input" name="username" id="username" type="text">
    </div>
 
    <div class="form">
       <label for="password" class="label-white">Password:</label>
       <input class="input" name="password" id="password" type="password">
     </div>   

    <img class="avatar" src="..\assets\avatar-lizard.png" >
    </form>

    <div class="button-container">
      <button class="button" @click="handleClick">Cancel</button>
      <button class="button" @click="handleClick">Save</button>
    </div>
 </template>
 
 <script>
 export default {
   name: 'UserSettings', }
 </script>

<style>

.form {
  margin-bottom: -170px;
  margin-top: 194px;
  display: flex;
  flex-direction: column;
  align-items:center;
  
}

.form-name{
  margin-bottom: -170px;
  margin-top: 190px;
  display: flex;
  flex-direction: column;
  align-items:center;
  margin-left: 10%;
}


.label-white {
    font-family:Cantora One, Georgia;
    color: #45C059;
    text-shadow: -1px -1px 0 black, 1px -1px 0 black, -1px 1px 0 black, 1px 1px 0 black;
    margin-right: 23%
 
}

.label-white-name {
    font-family:Cantora One, Georgia;
    color: #45C059;
    text-shadow: -1px -1px 0 black, 1px -1px 0 black, -1px 1px 0 black, 1px 1px 0 black;
    margin-right: 16%;

 
}

.input{ 
  font-family:Cantora One, Georgia;  
  background-color:rgba(0, 0, 0, 0.301);
  color: white;
  width: 30%;
  padding: 12px 20px;
  font-size: 16px;
  border: 1px solid rgba(0, 0, 0, 0.301);
  border-radius: 0;
  box-sizing: border-box;
}

.input-name{ 
  font-family:Cantora One, Georgia;  
  background-color:rgba(0, 0, 0, 0.301);
  color: white;
  width: 22%;
  padding: 12px 20px;
  font-size: 16px;
  border: 1px solid rgba(0, 0, 0, 0.301);
  border-radius: 0;
  box-sizing: border-box;

}

.avatar {
  position: absolute;
  top: 38%;
  left: 39.5%;
  transform: translate(-50%, -50%);
  width: 100px;
  height: 100px;
  object-fit: cover;
  border-radius: 33%;
        
}

.button-container {
  display: flex;
  justify-content: center;
  position: fixed;
  bottom: 70px;
  width: 100%;
}

.button {
  font-family:Cantora One, Georgia;
  font-size: 100%;
  color: black;
  background-color: #45C059;
  border: #45C059;
  margin: 8px;
  width: 90px;
  height: 30px;
 
}

</style>



