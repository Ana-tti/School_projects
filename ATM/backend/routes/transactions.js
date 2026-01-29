const express = require('express');
const router = express.Router();
const transactions = require('../models/transactions_model');

router.get('/',function(request, response){
    transactions.getAll(function(err, result){
        if(err){
            response.json(err);
        }
        else{
            response.json(result);
        }
    })
});

router.get('/:id',function(request, response){
    transactions.getById(request.params.id,function(err, result){
        if(err){
            response.json(err);
        }
        else{
            response.json(result);
        }
    })
});

router.post('/',function(request, response){
    transactions.add(request.body, function(err, result){
        if(err){
            response.json(err);
        }
        else{
            response.json(result.affectedRows);
        }
    })
});

router.post('/deposit',function(request,response){
    const {account_id, amount} = request.body;

    transactions.deposit(account_id, amount, function(err,result){
        if (err){
            response.json(err);
        }
        else{
            response.json(result.affectedRows);
        }
    });
});

router.post('/withdraw',function(request,response){
    const {account_id, amount} = request.body;

    transactions.withdraw(account_id, amount, function(err,result){
        if (err){
            response.json(err);
        }
        else{
            response.json(result.affectedRows);
        }
    });
});

router.post('/transfer',function(request,response){
    const {first_id, second_id, amount} = request.body;

    transactions.transfer(first_id,second_id, amount, function(err,result){
        if (err){
            response.json(err);
        }
        else{
            response.json(result.affectedRows);
        }
    });
});

router.post('/creditWithdraw',function(request,response){
    const {account_id, amount} = request.body;

    transactions.creditWithdraw(account_id, amount, function(err,result){
        if (err){
            response.json(err);
        }
        else{
            response.json(result.affectedRows);
        }
    });
});

router.post('/creditPayment',function(request,response){
    const {account_id, amount} = request.body;

    transactions.creditPayment(account_id, amount, function(err,result){
        if (err){
            response.json(err);
        }
        else{
            response.json(result.affectedRows);
        }
    });
});

router.put('/:id',function(request, response){
    transactions.update(request.params.id, request.body, function(err, result){
        if(err){
            response.json(err);
        }
        else{
            response.json(result.affectedRows);
        }
    })
});

router.delete('/:id',function(request, response){
    transactions.delete(request.params.id, function(err, result){
        if(err){
            response.json(err);
        }
        else{
            response.json(result.affectedRows);
        }
    })
});
module.exports=router