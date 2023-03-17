<template>
  <div class="user">
    <h1>{{ chekUser(user) }}</h1>
  </div>
</template>
<script>
export default {
  data() {
    return {
      user: ''
    }
  },

  async asyncData({$axios, params}) {
    const user = await $axios.$get('https://jsonplaceholder.typicode.com/users/' + params.id)
    console.log({user})
    return {user}
  },
  methods: {
    chekUser(user) {

      if (user === {}) {
        this.$router.push('/users')
      } else {
        return user.name
      }
    }
  }


}
</script>
