const db=require('../database.js');

const account={
    getAll(callback){
        return db.query('SELECT * FROM account',callback);
    },
    getById(id,callback,){
        return db.query('SELECT * FROM account WHERE idclient=?',[id],callback);
    },
    add(newAccount,callback){
        return db.query('INSERT INTO account(idclient, cardnumber ,balance, creditlimit, creditbalance) VALUES(?,?,?,?,?)',[newAccount.idclient,
            newAccount.cardnumber,newAccount.balance,newAccount.creditlimit,newAccount.creditbalance],callback);
    },
    update(id,newData,callback){
        return db.query('UPDATE account SET idclient=?, cardnumber=?, balance=?, creditlimit=?,creditbalance=? WHERE idaccount=?',
            [newData.idclient, newData.cardnumber, newData.balance, newData.creditlimit, newData.creditbalance, id],callback
        );

    },
    delete(id,callback){
        return db.query('DELETE FROM account WHERE idaccount=?',
            [id],callback
        );

    },
    getBalance(id,callback){
        return db.query('SELECT balance FROM account WHERE idaccount=?',
            [id],callback
        );

    },

    getCreditBalance(id,callback){
        return db.query('SELECT creditbalance FROM account WHERE idaccount=?',
            [id],callback
        );

    },

    getCreditLimit(id,callback){
        return db.query('SELECT creditlimit FROM account WHERE idaccount=?',
            [id],callback
        );

    },

    defineDebit(cardnumber, callback){
        return db.query('CALL define_debit(?)',[cardnumber],callback);
    },
    defineCredit(cardnumber, callback){
        return db.query('CALL define_credit(?)',[cardnumber],callback);
    },
 }


module.exports=account;