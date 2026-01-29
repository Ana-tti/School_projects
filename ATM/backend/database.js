const mysql=require('mysql2');
const dotenv=require('dotenv');
dotenv.config();
const ConnectionString='mysql://dbuser:dbpassword@127.0.0.1:3306/bankaccount_db';
//const connection=mysql.createPool(ConnectionString);
const connection=mysql.createPool(process.env.MYSQL_SERVER);

module.exports=connection;
