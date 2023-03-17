require('dotenv').config()
const express = require('express')
const bodyParser = require('body-parser')

const room = require('./controllers/RoomController')

const app = express()
const port = process.env.PORT

app.use(bodyParser.json())
app.use(
    bodyParser.urlencoded({
        extended: true,
    })
)

new room.RoomController(app)

app.listen(port, () => {
    console.log(`App running on port ${port}.`)
})