const Pool = require('pg').Pool

class BaseModel {

    connection;
    table;

    constructor() {
        this.connection = new Pool({
            user: process.env.DB_USER,
            host: process.env.DB_HOST,
            database: process.env.DB_NAME,
            password: process.env.DB_PASSWORD,
            port: process.env.DB_PORT,
        })
    }

    async getAll() {
        const res = await this.connection.query(
            `SELECT *
             FROM ${this.table}
             ORDER BY id ASC`
        )
        return res.rows
    }

    async getById(id) {
        const res = await this.connection.query(
            `SELECT *
             FROM ${this.table}
             WHERE id = ${id}
             ORDER BY id ASC LIMIT 1`
        )
        return res.rows.length ? res.rows[0] : null
    }

    async create(body) {
        const fieldsString = Object.keys(body).join(', ')
        const valuesString = Object.values(body).map(value => `'${value}'`).join(', ')

        try {
            const res = await this.connection.query(
                `INSERT INTO ${this.table} (${fieldsString})
                 VALUES (${valuesString})`
            )
            return res
        } catch (e) {
            console.error(e)
            return {}
        }
    }
}

module.exports = {
    BaseModel
}