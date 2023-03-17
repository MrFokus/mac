const {Client} = require('pg');
const client = new Client({
    user: 'german',
    host: 'localhost',
    database: 'german',
    password: 'root',
    port: 5432,
});
client.connect();
const query = ` 
 CREATE TABLE users ( 
 email varchar, 
 firstName varchar, 
 lastName varchar, 
 age int 
 ); 
 `;
client.query(query, (err, res) => {
    if (err) {
        console.error(err);
        return;
    }
    console.log('Table is successfully created');
    client.end();
}); 