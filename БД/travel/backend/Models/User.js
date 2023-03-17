const base = require('./BaseModel')
const crypto = require('crypto');

class User extends base.BaseModel {

    constructor() {
        super();
        this.table = 'client'
    }

    hash(pass) {
        let name = pass;
        let hash = crypto.createHash('md5').update(name).digest('hex');
        console.log(hash);
        return hash;
    }

    async checkUser(login_client, pass_client) {
        try {
            const res = await this.connection.query(
                `SELECT id_client
             FROM ${this.table}
             WHERE (login_client='${login_client}' AND pass_client='${pass_client}')`
            )
            let check_m = await this.connection.query(
                `SELECT *
             FROM manager
             WHERE (login_manager='${login_client}' AND pass_manager='${pass_client}')`
            )
            if(check_m.rowCount !== 0) {
                if(check_m.rows[0].post_manager==="младший") {
                    res.msg = "manager"
                    res.id_manager = check_m.rows[0].id_manager;
                    console.log(res)
                    return res;
                }
                else{
                    res.msg = "mainManager"
                    res.id_manager = check_m.rows[0].id_manager;
                    console.log(res)
                    return res;
                }
            }
            console.log(res.rows[0]);
            if (res.rowCount !== 0) {
                return res.rows[0]
            }
            else{
                return "No user";
            }
        } catch (e) {
            console.log(e)
            throw ("Неверный логин или пароль")

        }

    }

    async createUser(data, pass_client) {
        try {
            const check = await this.connection.query(
                `SELECT id_client
             FROM ${this.table}
             WHERE (login_client='${data.login}' OR pasport_client='${data.passport}')`
            )
            if (check.rowCount === 0) {
                const create = await this.connection.query(
                    `INSERT INTO client(
	            fio_client, number_client, gender_client, pasport_client, login_client, pass_client)
	            VALUES ('${data.name}', '${data.number_phone}', '${data.gender}', '${data.passport}', '${data.login}', '${pass_client}');`
                )
                console.log(create);
                if (create.rowCount) {
                    const res = await this.connection.query(
                        `SELECT id_client
                         FROM ${this.table}
                         WHERE (login_client='${data.login}' OR pasport_client='${data.passport}')`
                    )
                    return ({
                        id: res.rows[0],
                        msg: "Запрос выполнен успешно",
                    });
                }
                return ("Ошибка");
            } else {
                return ("Такой пользователь существует");
            }


        } catch (e) {
            console.log(e)
            return ("Ошибка");

        }

    }
    async addManager(data) {
        try {
            const check = await this.connection.query(
                `SELECT id_manager
             FROM manager
             WHERE login_manager='${data.login_manager}'`
            )
            console.log(check)
            if (check.rowCount === 0) {
                const create = await this.connection.query(
                    `INSERT INTO manager(
                    fio_manager, number_manager, gender_manager, login_manager, pass_manager)
                    SELECT fio_client, number_client, gender_client, login_client, pass_client FROM client WHERE login_client='${data.login_manager}';
                    UPDATE public.manager
                    SET post_manager='младший'
                    WHERE login_manager='${data.login_manager}';`
                )
                console.log(create);
                if (create.rowCount!==0) {
                    return (
                        "Запрос выполнен успешно"
                );
                }
                else return ("Пользователь не найден");
            } else {
                return ("Такой менеджер существует");
            }


        } catch (e) {
            console.log(e)
            return ("Ошибка");

        }

    }

    async TRU(data) {
        try {
            const check = await this.connection.query(
                `SELECT id_client
             FROM ${this.table}
             WHERE (fio_client='${data.name}' AND pasport_client='${data.passport}')`
            )
            if (check.rowCount === 0) {
                const create = await this.connection.query(
                    `INSERT INTO client(
	            fio_client,pasport_client)
	            VALUES ('${data.name}','${data.passport}');`
                )
                console.log(create);
                if (create.rowCount) {
                    const res = await this.connection.query(
                        `SELECT id_client
                         FROM ${this.table}
                         WHERE (fio_client='${data.name}' AND pasport_client='${data.passport}')`
                    )
                    return ({
                        id: res.rows[0],
                        fio_client: data.name,
                        pasport_client:data.passport,
                        number_client:'',
                        msg: "Запрос выполнен успешно",
                    });
                }
                return ("Ошибка");
            } else {
                return check.rows[0];
            }


        } catch (e) {
            console.log(e)
            return ("Ошибка");

        }

    }

    async getUser(data) {
        try {
            console.log(data)
            const get = await this.connection.query(
                `SELECT *
             FROM ${this.table}
             WHERE id_client=${+data.user}`
            )
            console.log(get.rows[0]);
            return get.rows[0];
        } catch (e) {
            console.log(e)
            return ("Ошибка");

        }

    }
}

module.exports = {
    User
}