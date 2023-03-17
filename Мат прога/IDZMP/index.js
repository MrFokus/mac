const express = require('express')
const bodyParser = require('body-parser')
const cors = require('cors')
const fileUpload = require('express-fileupload')
fs = require('fs');

const Huk = require('./HukModel')

const app = express()
const port = process.env.PORT

app.use(fileUpload({
    createParentPath:true,
}));
app.use(cors());
app.use(bodyParser.json())
app.use(
    bodyParser.urlencoded({
        extended: true,
    })
)
const huk=new Huk();

// huk.main();
app.post('/',(req, res) => {
    console.log(req.body);
    let result=huk.main(req.body);
    res.json(result);
});

app.post('/download',(req, res) => {
    console.log(req.body)
    try {
        let request =JSON.parse(req.body.json);
        if(request.function==="") request.function="nullfunc";
        let file =request.function+'.json';
        fs.writeFileSync(file, JSON.stringify(request), (err) => {
            if(err) throw err;
            console.log('Data has been replaced!');

        });
        res.setHeader('Content-disposition', 'attachment; filename='+file);
        res.setHeader('Content-Type', 'text/json');
        res.download(file,file);
        setTimeout( ()=>{
            fs.unlinkSync(file)
        },1000);
    }
    catch (e){

    }

});
app.post('/downloadResult',(req, res) => {
    console.log(req.body.str);
    let request =req.body.str;
    console.log(request);
    let file ='res.txt';
    fs.writeFileSync('res.txt',request.toString(), (err) => {
        if(err) throw err;
        console.log('Data has been replaced!');

    });
    res.setHeader('Content-disposition', 'attachment; filename='+file);
    res.setHeader('Content-Type', 'text');
    res.download(file,file);
    setTimeout( ()=>{
        fs.unlinkSync(file)
    },1000);
});

app.listen(3001, () => {
    console.log(`App running on port 3001`)
})