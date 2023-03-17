const base = require('./BaseController')
const model = require('../models/Entity')

class EntityController extends base.BaseController {

    model;
    routes = [

        {
            path: '/collections',
            type: 'post',
            handler: this.getCollections,
        },
        {
            path: '/tour',
            type: 'post',
            handler: this.getTour,
        },
        {
            path: '/addRide',
            type: 'post',
            handler: this.addRide,
        },
        {
            path: '/giveUnfRide',
            type: 'post',
            handler: this.takeUnfRide,
        },
        {
            path: '/takeRide',
            type: 'post',
            handler: this.takeRide,
        },
        {
            path: '/sucRide',
            type: 'post',
            handler: this.sucRide,
        },
        {
            path: '/addTour',
            type: 'post',
            handler: this.addTour,
        },
        {
            path: '/delTour',
            type: 'post',
            handler: this.delTour,
        },
        {
            path: '/reportType1',
            type: 'post',
            handler: this.reportType1,
        },
        {
            path: '/reportType2',
            type: 'post',
            handler: this.reportType2,
        },
        {
            path: '/reportType3',
            type: 'post',
            handler: this.reportType3,
        },
    ];

    constructor(app) {
        super(app);
        this.model = new model.Entity()
        this.attachRoutes()
    }

    async reportType1(request, response) {
        try {
            console.log(request.body);
            let res = await this.model.reportType1()
            response
                .status(200)
                .json(res)
        } catch (e) {
            response.status(404).json(e);
        }
    }
    async reportType2(request, response) {
        try {
            console.log(request.body);
            let res = await this.model.reportType2()
            response
                .status(200)
                .json(res)
        } catch (e) {
            response.status(404).json(e);
        }
    }
    async reportType3(request, response) {
        try {
            console.log(request.body);
            let res = await this.model.reportType3()
            response
                .status(200)
                .json(res)
        } catch (e) {
            response.status(404).json(e);
        }
    }

    async delTour(request, response) {
        try {
            console.log(request.body);
            let res = await this.model.delTour(request.body)
            response
                .status(200)
                .json(res)
        } catch (e) {
            response.status(404).json(e);
        }
    }

    async getCollections(request, response) {
        try {
            console.log(request.body);
            let res = await this.model.getCollections()
            response
                .status(200)
                .json(res)
        } catch (e) {
            response.status(404).json(e);
        }
    }

    async sucRide(request, response) {
        try {
            console.log(request.body);
            let res = await this.model.sucRide(request.body)
            response
                .status(200)
                .json(res)
        } catch (e) {
            response.status(404).json(e);
        }
    }

    async getTour(request, response) {
        try {
            console.log(request.body);
            let res = await this.model.getTour(request.body)
            response
                .status(200)
                .json(res)
        } catch (e) {
            response.status(404).json(e);
        }
    }

    async addTour(request, response) {
        try {
            let res = await this.model.addTour(request.body)
            response
                .status(200)
                .json(res)
        } catch (e) {
            response.status(404).json(e);
        }
    }

    async takeUnfRide(request, response) {
        try {
            console.log(request.body);
            let res = await this.model.takeUnfRide(request.body)
            response
                .status(200)
                .json(res)
        } catch (e) {
            response.status(404).json(e);
        }
    }

    async takeRide(request, response) {
        try {
            console.log(request.body);
            let res = await this.model.takeRide(request.body)
            response
                .status(200)
                .json(res)
        } catch (e) {
            response.status(404).json(e);
        }
    }

    async addRide(request, response) {
        try {
            console.log(request.body);
            let res = await this.model.addRide(request.body)
            response
                .status(200)
                .json(res)
        } catch (e) {
            response.status(404).json(e);
        }
    }
}

module.exports = {
    EntityController
}