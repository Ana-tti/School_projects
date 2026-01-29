const db=require('../database.js');

const client={
    getAll(callback){
        return db.query('SELECT * FROM client',callback);
    },
    getById(id,callback,){
        return db.query('SELECT * FROM client WHERE idclient=?',[id],callback);
    },
    add(newClient,callback){
        return db.query('INSERT INTO client(fname, lname, address, phone) VALUES(?,?,?,?)',[newClient.fname,newClient.lname,
            newClient.address, newClient.phone],callback);
    },
    update(id,newData,callback){
        return db.query('UPDATE client SET fname=?, lname=?, address=?, phone=? WHERE idclient=?',
            [newData.fname, newData.lname, newData.address, newData.phone, id],callback
        );

    },
    delete(id,callback){
        return db.query('DELETE FROM client WHERE idclient=?',
            [id],callback
        );
    }
}

module.exports=client;