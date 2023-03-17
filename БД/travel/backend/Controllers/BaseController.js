class BaseController {

    routes = [];
    app;

    constructor(app) {
        this.app = app
    }

    attachRoutes() {
        this.routes.forEach((route) => {
            this.app[route.type](route.path, route.handler.bind(this))
            console.log(`${route.type.toUpperCase()}: ${route.path}`)
        })
    }
}

module.exports = {
    BaseController
}