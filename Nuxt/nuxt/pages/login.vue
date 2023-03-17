<template>
  <div class="login">
    <NuxtLink to="/">Homepage</NuxtLink>
    <h1>Login</h1>
    <input type="text" v-model="message">
    <button @click="checkLogin(message)">Next</button>
    <p v-if="invalidLogin">CHEK LOGIN</p>
  </div>
</template>
<script>
  export default {
    data(){
      return {
        message:"",
        invalidLogin: false
      }
    },
    methods:{
      checkLogin(message){
        let login="test@gmail.ru"
        if(message!==login){
          this.invalidLogin=true
        }
        else{
          this.$router.push('/')
        }
      }
    }
  }
</script>
