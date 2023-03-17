const base = require('./BaseController')
const model = require('../models/User')

class UserController extends base.BaseController {

    model;
    routes = [

        {
            path: '/auth',
            type: 'post',
            handler: this.checkUser,
        },
        {
            path: '/registration',
            type: 'post',
            handler: this.createUser,
        },
        {
            path: '/client',
            type: 'post',
            handler: this.getUser,
        },
        {
            path: '/timeRegClient',
            type: 'post',
            handler: this.TRU,
        },
        {
            path: '/addManager',
            type: 'post',
            handler: this.addManager,
        },

    ];

    constructor(app) {
        super(app);
        this.model = new model.User()
        this.attachRoutes()
    }

    async addManager(request, response) {
        try {
            console.log(request.body);
            let res=await this.model.addManager(request.body)
            response
                .status(200)
                .json(res)
        }
        catch (e){
            response.status(404).json(e);
        }
    }

    async checkUser(request, response) {
       try {
           console.log(request.body);
           let hash=this.model.hash(request.body.password)
           let res=await this.model.checkUser(request.body.login, hash)
           response
               .status(200)
               .json(res)
       }
       catch (e){
           response.status(404).json(e);
       }
    }
    async createUser(request, response) {
        try {
            console.log(request.body);
            let hash=this.model.hash(request.body.password)
            let res=await this.model.createUser(request.body, hash)
            response
                .status(200)
                .json(res)
        }
        catch (e){
            response.status(404).json(e);
        }
    }
    async TRU(request, response) {
        try {
            console.log(request.body);
            let res=await this.model.TRU(request.body)
            response
                .status(200)
                .json(res)
        }
        catch (e){
            response.status(404).json(e);
        }
    }
    async getUser(request, response) {
        try {
            console.log(request.body.user);
            let res=await this.model.getUser(request.body)
            response
                .status(200)
                .json(res)
        }
        catch (e){
            response.status(404).json(e);
        }
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
    UserController
}