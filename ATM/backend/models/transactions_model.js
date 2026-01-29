const db=require('../database.js');

const transactions={
    getAll(callback){
        return db.query('SELECT * FROM transactions',callback);
    },
    getById(id,callback,){
        return db.query('SELECT * FROM transactions WHERE idaccount=? order by occurdate desc',[id],callback);
    },
    add(newTransactions,callback){
        return db.query('INSERT INTO transactions(idaccount, cardnumber,occurdate, withdraw, transfer, deposit) VALUES(?,?,?,?,?,?)',
            [newTransactions.idaccount,newTransactions.cardnumber,newTransactions.occurdate,newTransactions.withdraw,newTransactions.transfer,newTransactions.deposit
            ],callback);
    },
    update(id,newData,callback){
        return db.query('UPDATE transactions SET occurdate=?, withdraw=?, transfer=?, deposit=? WHERE idtransactions=?',
            [newData.occurdate, newData.withdraw,newData.transfer,newData.deposit, id],callback
        );

    },
    delete(id,callback){
        return db.query('DELETE FROM transactions WHERE idtransactions=?',
            [id],callback
        );
    },

    deposit(account_id, amount, callback){
        return db.query('CALL deposit(?,?)',[account_id,amount],callback);
    },
    withdraw(account_id, amount, callback){
        return db.query('CALL withdraw(?,?)',[account_id,amount],callback);
    },
    transfer(first_id, second_id, amount, callback){
        return db.query('CALL transfer(?,?,?)',[first_id,second_id,amount],callback);
    },
    creditWithdraw(account_id,amount, callback){
        return db.query('CALL credit_withdraw(?,?)',[account_id,amount],callback);
    },
    creditPayment(account_id, amount, callback){
        return db.query('CALL credit_payment(?,?)',[account_id,amount],callback);
    }
}

module.exports=transactions;