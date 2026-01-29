const { response } = require('express');
const db=require('../database.js');
const bcrypt = require('bcryptjs');

const card={
    getAll(callback){
        return db.query('SELECT * FROM card',callback);
    },
    getByCardNum(cardNum,callback,){
        return db.query('SELECT * FROM card WHERE cardnumber=?',[cardNum],callback);
    },
    add(newCard,callback){
       bcrypt.hash(newCard.pin,10,function(err, hashed_pin){
            return db.query(`INSERT INTO card(cardnumber, idaccount, idclient, pin, is_locked) VALUES(?,?,?,?,?)`,
                [newCard.cardnumber, newCard.idaccount, newCard.idclient, hashed_pin, is_locked],callback)
       });
    },
    update(cardNum,newData,callback){
        bcrypt.hash(newData.pin,10,function(err,hashed_pin){
            return db.query('UPDATE card SET idaccount=?, idclient=?, pin=?, is_locked=? WHERE cardnumber=?',
            [newData.idaccount, newData.idclient, hashed_pin, newData.is_locked, cardNum],callback
            );
    })
    },
    delete(cardNum,callback){
        return db.query('DELETE FROM card WHERE cardnumber=?',
            [cardNum],callback
        );
    },
    checkPin(cardNum,callback){
        return db.query('SELECT pin FROM card WHERE cardnumber=?',[cardNum],callback);
    },

    checkLocked(cardNum,callback){
        return db.query('SELECT is_locked FROM card WHERE cardnumber=?',[cardNum],callback);
    },

    updateAttempts(cardNum, callback){
        return db.query('UPDATE card SET login_attempts = login_attempts +1 WHERE cardnumber =?',
            [cardNum],callback);
    },

    resetAttempts(cardNum, callback){
        return db.query('UPDATE card SET login_attempts = 0 WHERE cardnumber =?',
            [cardNum],callback);
    },

}

module.exports=card;