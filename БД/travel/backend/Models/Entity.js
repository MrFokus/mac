const base = require('./BaseModel')

class Entity extends base.BaseModel {

    constructor() {
        super();
        this.table = 'tour'
    }

    async addTour(data) {
        try {
            if(data.name_country===''||data.name_city==='' ||data.name_hotel==='' || data.class_hotel===''||data.type_transport||data.name_tour===''||data.date_start_tour===''||data.date_end_tour===''||data.price_tour===''||data.description_tour===''){
                console.log("Не все данные введены")
                return "Не все данные введены";

            }
            console.log(data)
            let queryTour = {
                id_hotel: 0,
                id_city: 0,
                id_transport: 0,
                price_tour: data.price_tour,
                name_tour: data.name_tour,
                description_tour: data.description_tour,
                date_start_tour: data.date_start_tour,
                date_end_tour: data.date_end_tour,
            }

            let country;
            let checkCountry = await this.connection.query(
                `SELECT id_country
                FROM country
                WHERE name_country='${data.name_country}'`
            )
            let checkCity = await this.connection.query(
                `SELECT id_city
                FROM city
                WHERE name_city='${data.name_city}'`
            )
            let checkTransport=await this.connection.query(
                `SELECT id_transport
                FROM transport
                WHERE type_transport='${data.type_transport}'`)
            let checkHotel=await this.connection.query(
                `SELECT id_hotel
                FROM hotels
                WHERE name_hotel='${data.name_hotel}'`)
            if (checkCountry.rowCount=== 0) {
                checkCountry = await  this.connection.query(
                    `INSERT INTO country(
                    name_country)
                    VALUES ('${data.name_country}')
                    RETURNING id_country`
                )
            }
            country=checkCountry.rows[0].id_country;
            console.log(country);
            if(checkCity.rowCount===0){
                checkCity = await  this.connection.query(
                    `INSERT INTO city(
                    name_city,id_country)
                    VALUES ('${data.name_city}',${country})
                    RETURNING id_city`
                )
            }
            queryTour.id_city=checkCity.rows[0].id_city;
            if(checkTransport.rowCount===0){
                checkTransport = await  this.connection.query(
                    `INSERT INTO transport(
                    type_transport)
                    VALUES ('${data.type_transport}')
                    RETURNING id_transport`
                )
            }
            queryTour.id_transport=checkTransport.rows[0].id_transport;
            if(checkHotel.rowCount===0){
                checkTransport = await  this.connection.query(
                    `INSERT INTO hotels(
                    name_hotel,class_hotel,id_city)
                    VALUES ('${data.name_hotel}',${data.class_hotel},${queryTour.id_city})
                    RETURNING id_hotel`
                )
            }
            queryTour.id_hotel=checkHotel.rows[0].id_hotel;

            console.log(queryTour);
            const create =await this.connection.query(
                `
                INSERT INTO public.tour(
                id_hotel, id_city, id_transport, price_tour, name_tour, description_tour, date_start_tour, date_end_tour)
                VALUES (${queryTour.id_hotel}, ${queryTour.id_city}, ${queryTour.id_transport}, ${queryTour.price_tour}, '${queryTour.name_tour}', '${queryTour.description_tour}', '${queryTour.date_start_tour}', '${queryTour.date_end_tour}');
                `
            )
            if (create.rowCount !== 0) {
                return (
                    "Запрос выполнен успешно"
                );
            } else return ("Пользователь не найден");


        } catch (e) {
            console.log(e)
            return ("Ошибка");

        }

    }

    async reportType1() {
        try {
            let res = await this.connection.query(
                `SELECT cl.fio_client, r.id_ride, m.fio_manager, r.date_order from ride r
                JOIN client cl ON r.id_client=cl.id_client
                JOIN manager m ON r.id_manager=m.id_manager
                where date_order > CURRENT_DATE - INTERVAL '1 months' `
            )
            console.log(res.rows)
            res.rows.forEach(r => {
                let [month, day, year] = [
                    r.date_order.getMonth() + 1,
                    r.date_order.getDate(),
                    r.date_order.getFullYear(),
                ];
                r.date_order = day + '.' + month + '.' + year;
            })
            return res;
        } catch (e) {
            return "Error"
        }
    }
    async reportType2() {
        try {
            let res = await this.connection.query(
                `SELECT Count(m.fio_manager),m.fio_manager,t.name_tour from ride r
                JOIN tour t ON r.id_tour=t.id_tour
                JOIN manager m ON r.id_manager=m.id_manager
                GROUP BY t.name_tour, m.fio_manager
                Order by count desc `
            )
            console.log(res.rows)
            return res;
        } catch (e) {
            return "Error"
        }
    }
    async reportType3() {
        try {
            let res = await this.connection.query(
                `SELECT cl.fio_client, Count(r.id_client),SUM(t.price_tour) from ride r
                JOIN tour t ON r.id_tour=t.id_tour
                JOIN client cl ON r.id_client=cl.id_client
                Group by cl.fio_client
                Order by count,sum desc`
                            )
            console.log(res.rows)
            return res;
        } catch (e) {
            return "Error"
        }
    }
    async addRide(data) {
        try {
            let now = new Date()
            console.log(now.toISOString());
            let [month, day, year] = [
                now.getMonth() + 1,
                now.getDate(),
                now.getFullYear(),
            ];
            const res = await this.connection.query(
                `INSERT INTO ride(
                id_client, id_tour, date_order)
                VALUES (${+data.id_client}, ${+data.id_tour}, '${year+'-'+month+'-'+day}'); `
            )
            return "OK";
        } catch (e) {

        }
    }
    async delTour(data) {
        try {
            const res = await this.connection.query(
                `DELETE FROM tour
	            WHERE id_tour=${data.id_tour}`
            )
            return "OK";
        } catch (e) {
            return "Ошибка";
        }
    }

    async getTour(data) {
        try {
            const res = await this.connection.query(
                `SELECT t.id_tour, t.price_tour, t.name_tour,c.name_city, tr.type_transport,h.name_hotel,h.class_hotel, t.description_tour, t.date_start_tour, t.date_end_tour
                FROM ${this.table} t
                JOIN city c ON t.id_city=c.id_city
                JOIN transport tr ON t.id_transport=tr.id_transport
                JOIN hotels h ON t.id_hotel=h.id_hotel 
                WHERE t.id_tour=${+data.id_tour} `
            )
            return res.rows[0];
        } catch (e) {

        }
    }

    async sucRide(data) {
        try {
            console.log(data);
            const res = await this.connection.query(
                `UPDATE ride
                SET id_manager=${data.id_manager}
                WHERE id_ride=${data.id_ride}; `
            )
            return res.rows[0];
        } catch (e) {

        }
    }

    async takeRide(id_manager) {
        try {
            console.log(id_manager);
            let res = await this.connection.query(
                `SELECT t.date_start_tour,t.date_end_tour,t.name_tour,cy.name_city,h.name_hotel,c.fio_client,c.number_client,c.pasport_client,t.price_tour from ride r
                JOIN client c ON r.id_client=c.id_client
                JOIN tour t ON r.id_tour=t.id_tour
                JOIN hotels h ON t.id_hotel=h.id_hotel
                JOIN city cy ON t.id_city=cy.id_city
                where r.id_manager=` + id_manager.id_manager
            )
            console.log(res);
            res.rows.forEach(r => {
                let [month, day, year] = [
                    r.date_start_tour.getMonth() + 1,
                    r.date_start_tour.getDate(),
                    r.date_start_tour.getFullYear(),
                ];
                r.date_start_tour = day + '.' + month + '.' + year;
                [month, day, year] = [
                    r.date_end_tour.getMonth() + 1,
                    r.date_end_tour.getDate(),
                    r.date_end_tour.getFullYear(),
                ];
                r.date_end_tour = day + '.' + month + '.' + year;
            })
            return res.rows;
        } catch (e) {
            console.log(e)
            return e
        }
    }

    async takeUnfRide() {
        try {
            let res = await this.connection.query(
                `SELECT r.id_ride, t.date_start_tour,t.date_end_tour,t.name_tour,cy.name_city,h.name_hotel,c.fio_client,c.number_client,c.pasport_client,t.price_tour from ride r
                JOIN client c ON r.id_client=c.id_client
                JOIN tour t ON r.id_tour=t.id_tour
                JOIN hotels h ON t.id_hotel=h.id_hotel
                JOIN city cy ON t.id_city=cy.id_city
                where r.id_manager is NULL;`
            )
            res.rows.forEach(r => {
                let [month, day, year] = [
                    r.date_start_tour.getMonth() + 1,
                    r.date_start_tour.getDate(),
                    r.date_start_tour.getFullYear(),
                ];
                r.date_start_tour = day + '.' + month + '.' + year;
                [month, day, year] = [
                    r.date_end_tour.getMonth() + 1,
                    r.date_end_tour.getDate(),
                    r.date_end_tour.getFullYear(),
                ];
                r.date_end_tour = day + '.' + month + '.' + year;
            })
            return res.rows;
        } catch (e) {
            return e
        }
    }

    async getCollections() {
        try {
            const res = await this.connection.query(
                `SELECT t.id_tour, t.price_tour, t.name_tour,c.name_city, tr.type_transport,h.name_hotel,h.class_hotel, t.description_tour, t.date_start_tour, t.date_end_tour
                FROM ${this.table} t
                JOIN city c ON t.id_city=c.id_city
                JOIN transport tr ON t.id_transport=tr.id_transport
                JOIN hotels h ON t.id_hotel=h.id_hotel`
            )

            if (res.rowCount !== 0) {
                res.rows.forEach(r => {
                    let [month, day, year] = [
                        r.date_start_tour.getMonth() + 1,
                        r.date_start_tour.getDate(),
                        r.date_start_tour.getFullYear(),
                    ];
                    r.date_start_tour = day + '/' + month + '/' + year;
                    [month, day, year] = [
                        r.date_end_tour.getMonth() + 1,
                        r.date_end_tour.getDate(),
                        r.date_end_tour.getFullYear(),
                    ];
                    r.date_end_tour = day + '/' + month + '/' + year;
                })
                console.log(res.rows);
                return res.rows
            } else {
                return ("No data");
            }

        } catch (e) {
            console.log("Error")
            throw ("Error")

        }

    }

}

module.exports = {
    Entity
}