<template>
  <div class="users">
    <ul v-for="user of users" :key="user.id">
      <li>
        <a href="" @click.prevent="toUser(user)">{{user.name}}</a>
      </li>
    </ul>
  </div>
</template>
<script>
export default {
  data(){
    return{
      users:[],
    }
  },
  async mounted(){
    this.users=await this.$axios.$get('https://jsonplaceholder.typicode.com/users');
    console.log(this.users)
  },
  methods:{
    toUser(user){
      this.$router.push('/users/'+user.id)
    }
  }
}
</script>
