const base = require('./BaseModel')

class Room extends base.BaseModel {

    constructor() {
        super();
        this.table = 'rooms'
    }
}

module.exports = {
    Room
}