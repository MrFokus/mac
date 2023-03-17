const base = require('./BaseController')
const model = require('../models/Ride')

class RideController extends base.BaseController {

    model;
    routes = [
        {
            path: '/ride',
            type: 'get',
            handler: this.getAll
        },
        {
            path: '/room/:id',
            type: 'get',
            handler: this.getOne
        },
        {
            path: '/room',
            type: 'post',
            handler: this.create
        },

    ];

    constructor(app) {
        super(app);
        this.model = new model.Ride()
        this.attachRoutes()
    }

    async getAll(request, response) {
        response
            .status(200)
            .json(await this.model.getAll())
    }

    async getOne(request, response) {
        const result = await this.model.getById(request.params.id)
        if (result) {
            response
                .status(200)
                .json(result)
        } else {
            response
                .status(404)
                .json({
                    error: 'Not found'
                })
        }
    }

    async create(request, response) {
        const result = await this.model.create(request.body)
        if (result.rowCount) {
            response
                .status(201)
                .json({
                    status: "Success"
                })
        } else {
            response
                .status(400)
                .json({
                    error: "Bad request"
                })
        }
    }

}

module.exports = {
    RideController
}