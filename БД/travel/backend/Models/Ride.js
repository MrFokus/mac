const base = require('./BaseModel')

class Ride extends base.BaseModel {

    constructor() {
        super();
        this.table = 'ride'
    }
    async getAll() {
        const res = await this.connection.query(
            `SELECT *
             FROM ${this.table}`
        )
        return res.rows
    }
}

module.exports = {
    Ride
}