require('dotenv').config()
const express = require('express')
const bodyParser = require('body-parser')
const ride = require('./Controllers/RideController.js')
const user = require('./Controllers/UserController.js')
const entity = require('./Controllers/EntityController')

const app = express()
const port = process.env.PORT



const cors = require('cors');
app.use(cors());
app.use(bodyParser.json())
app.use(
    bodyParser.urlencoded({
        extended: true,
    })
)
new ride.RideController(app);
new user.UserController(app);
new entity.EntityController(app)
app.listen(port, () => {
    console.log(`App running on port ${port}.`)
})