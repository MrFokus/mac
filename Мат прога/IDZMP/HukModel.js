const math = require('mathjs');
const parser = math.parser();

class Huk {
    input_data = {
        // //sqrt((x-y)^2+(x^2+2-y-5)^2)
        // //8x^2+4*x*y+5*y^2
        // //(x1-2)^2+(x2-5)^2+(x3+2)^4
        // function: "(x1-2)^2+(x2-5)^2+(x3+2)^4",
        // alpha: 2,
        // betta: 2,
        // eps: 0.0001,
        // //1,1,1
        // h: [1,1,1],
        // //4,-2,3
        // x0: [4,-2,3],
        // type_func: "f(x1,x2,x3)",
        // epsilant: 0.1,
    }

    resES = [
        {
            flag: 1,
        }
    ];
    export_data = {}


    valueFunc(x) {
        try {
            let arg = "f(" + x.join(",") + ")";
            parser.evaluate("f"+this.input_data.type_func + '=' + this.input_data.function)
            return (parser.evaluate(arg))
        } catch (e) {
            throw "Проверьте корректность введённых данных ( "+e+" )";
            console.log(e);
        }


    }

    reduceH(h) {
        let flag = 0, i;
        for (i = 0; i < h.length; i++) {
            if (h[i] > this.input_data.epsilant) {
                h[i] /= this.input_data.alpha;
                flag = 1;
            }
        }
        return {
            flag: flag,
            h: h,
        };
    }

    exploratory_search(x0, h) {
           let time_base_point = x0.slice(0), i, new_base_point, j, flag = 1, z_tbp, z_x0;
           let new_h = {}
           for (j = 0; flag === 1; j++) {
               console.log("h= " + h);
               for (i = 0; i < x0.length; i++) {
                   time_base_point[i] += h[i];
                   z_tbp = this.valueFunc(time_base_point);
                   z_x0 = this.valueFunc(x0);
                   if (z_tbp < z_x0) {
                       continue;
                   } else {
                       time_base_point[i] -= 2 * h[i];

                       z_tbp = this.valueFunc(time_base_point);
                       z_x0 = this.valueFunc(x0);
                       if (z_tbp < z_x0) {
                           continue;
                       } else {
                           time_base_point[i] += h[i];
                       }
                   }
               }
               if (z_tbp < z_x0) {
                   new_base_point = time_base_point.slice(0);
                   time_base_point = x0.slice(0);
                   break;
               } else {
                   new_h = this.reduceH(h.slice(0));
                   h = new_h.h;
                   if (new_h.flag === 0) {
                       flag = new_h.flag;
                       new_base_point = x0;
                       break;
                   }
               }
           }
           return {
               time_base_point,
               new_base_point,
               flag,
           }
    }

    search_obr(x1, x0, b) {
       try{
           let i, x2 = [];
           for (i = 0; i < this.input_data.x0.length; i++) {
               x2[i] = x1[i] + b * (x1[i] - x0[i]);
           }
           return x2;
       }
       catch (e){
           throw "Ошибка сервера";
       }
    }

    main(req) {
        this.export_data = {};
        try {
            this.export_data = {
                request_params: [
                    {
                        iteration: 0,
                        initial_data: {},
                        ES: {
                            h: [],
                            time_base_point: this.input_data.x0,
                            f_NBP: 0,
                            f_TBP: 0,
                            new_base_point: this.input_data.x0,
                        },
                        SO: {
                            new_base_point: this.input_data.x0,
                            f_NBP: 0,
                            f_TBP: 0,
                            time_base_point: this.input_data.x0,
                        },
                    }
                ]
            }
            this.input_data = req;
            this.export_data.request_params[0].initial_data.function = req.function;
            this.export_data.request_params[0].initial_data.x0 = req.x0;
            this.export_data.request_params[0].initial_data.h = req.h;
            this.export_data.request_params[0].initial_data.alpha = req.alpha;
            this.export_data.request_params[0].initial_data.betta = req.betta;
            this.export_data.request_params[0].initial_data.epsilant = req.epsilant;
            this.resES[0].time_base_point = this.input_data.x0;
            this.resES[0].new_base_point = this.input_data.x0;
            let flag = 0;
            console.log("    H = " + this.input_data.h + ", Альфа = " + this.input_data.alpha + ", Бетта = " + this.input_data.betta);
            console.log("Начальная базисная точка: " + this.input_data.x0);
            console.log("Номер итерации " + 1);
            this.export_data.request_params[1] = {
                iteration: 1,
                ES: {},
                SO: {},
            };
            this.resES[1] = this.exploratory_search(this.resES[0].time_base_point.slice(0), this.input_data.h.slice(0));
            this.export_data.request_params[1].ES.time_base_point = this.resES[0].time_base_point;
            this.export_data.request_params[1].ES.new_base_point = this.resES[1].new_base_point;
            this.export_data.request_params[1].ES.f_TBP = this.valueFunc(this.resES[0].time_base_point);
            this.export_data.request_params[1].ES.f_NBP = this.valueFunc(this.resES[1].new_base_point);
            console.log("Новая базисная точка: " + this.resES[1].new_base_point)
            if (this.resES[0].flag === 0) {
                console.log("Минимум функции =" + this.resES[i].new_base_point);
                flag = 1;
            }
            for (let i = 2; flag === 0; i++) {
                this.resES[i] = {};
                this.export_data.request_params[i] = {
                    iteration: i,
                    ES: {},
                    SO: {},
                    msg: "",
                    DES: {}
                };
                console.log("Поиск по образцу");
                this.resES[i].time_base_point = this.search_obr(this.resES[i - 1].new_base_point, this.resES[i - 2].new_base_point, this.input_data.betta);
                this.export_data.request_params[i - 1].SO.new_base_point = this.resES[1].new_base_point;
                this.export_data.request_params[i - 1].SO.time_base_point = this.resES[i].time_base_point;
                console.log("Временная базисная точка: " + this.resES[i].time_base_point)

                console.log("Номер итерации " + i);
                console.log("Исследующий поиск");
                console.log("F(" + this.resES[i].time_base_point + ") = " + this.valueFunc(this.resES[i].time_base_point));
                this.resES[i] = this.exploratory_search(this.resES[i].time_base_point.slice(0), this.input_data.h.slice(0));
                this.export_data.request_params[i].ES.time_base_point = this.resES[1].time_base_point;
                this.export_data.request_params[i].ES.new_base_point = this.resES[i].new_base_point;
                this.export_data.request_params[i].ES.f_TBP = this.valueFunc(this.resES[i].time_base_point);
                this.export_data.request_params[i].ES.f_NBP = this.valueFunc(this.resES[i].new_base_point);
                console.log("Новая базисная точка: " + this.resES[i].new_base_point)
                if (this.resES[i].flag === 0) {
                    console.log("Минимум функции =" + this.resES[i].new_base_point);
                    flag = 1;
                    break;
                }
                if (this.valueFunc(this.resES[i].new_base_point) < this.valueFunc(this.resES[i - 1].new_base_point)) {
                    continue;
                } else {
                    console.log(this.valueFunc(this.resES[i].new_base_point) + ">" + this.valueFunc(this.resES[i - 1].new_base_point))
                    console.log("Исследующий поиск вокруг этой временной базисной точки неудачен поэтому возвращаемся к старой базисной точке")
                    this.export_data.request_params[i].msg = "Исследующий поиск вокруг этой временной базисной точки неудачен поэтому возвращаемся к старой базисной точке";
                    this.resES[i].time_base_point = this.resES[i - 1].new_base_point.slice(0);
                    console.log("Исследующий поиск");
                    console.log("F(" + this.resES[i].time_base_point + ") = " + this.valueFunc(this.resES[i].time_base_point));
                    this.resES[i] = this.exploratory_search(this.resES[i].time_base_point.slice(0), this.input_data.h.slice(0));
                    this.export_data.request_params[i].DES.time_base_point = this.resES[1].time_base_point;
                    this.export_data.request_params[i].DES.new_base_point = this.resES[i].new_base_point;
                    this.export_data.request_params[i].DES.f_TBP = this.valueFunc(this.resES[i].time_base_point);
                    this.export_data.request_params[i].DES.f_NBP = this.valueFunc(this.resES[i].new_base_point);
                    console.log("Новая базисная точка: " + this.resES[i].new_base_point)
                    if (this.resES[i].flag === 0) {
                        console.log("Минимум функции =" + this.resES[i].new_base_point);
                        flag = 1;
                        break;
                    }

                }
            }
            this.export_data.request_params.forEach(rp => {
                if (Object.keys(rp.SO).length === 0) {
                    delete rp.SO
                }
            })

            return this.export_data;
        }
        catch (e){
            console.log(e)
            this.export_data.err=e;
            return this.export_data;
        }
    }
}

module.exports = Huk;

