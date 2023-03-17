const Pool = require('pg').Pool

class BaseModel {

    connection;
    table;

    constructor() {
        this.connection = new Pool({
            user: 'german',
            host: 'localhost',
            database: 'tour',
            password: '',
            port: 5432,
        })

    }

}

module.exports = {
    BaseModel
}