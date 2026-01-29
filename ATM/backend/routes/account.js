const express = require('express');
const router = express.Router();
const account = require('../models/account_model');

router.get('/',function(request, response){
    account.getAll(function(err, result){
        if(err){
            response.json(err);
        }
        else{
            response.json(result);
        }
    })
});

router.get('/:id',function(request, response){
    account.getById(request.params.id,function(err, result){
        if(err){
            response.json(err);
        }
        else{
            response.json(result);
        }
    })
});

router.post('/',function(request, response){
    account.add(request.body, function(err, result){
        if(err){
            response.json(err);
        }
        else{
            response.json(result.affectedRows);
        }
    })
});

router.put('/:id',function(request, response){
    account.update(request.params.id, request.body, function(err, result){
        if(err){
            response.json(err);
        }
        else{
            response.json(result.affectedRows);
        }
    })
});

router.delete('/:id',function(request, response){
    account.delete(request.params.id, function(err, result){
        if(err){
            response.json(err);
        }
        else{
            response.json(result.affectedRows);
        }
    })
});

router.get('/balance/:id', function(request, response) {
    account.getBalance(request.params.id, function(err, result) {
        if (err) {
            response.status(500).json({ error: err });
        } else {
            if (result.length > 0) {
                response.json({ balance: result[0].balance });
            } else {
                response.status(404).json({ error: "Account not found" });
            }
        }
    });
});

router.get('/creditbalance/:id', function(request, response) {
    account.getCreditBalance(request.params.id, function(err, result) {
        if (err) {
            response.status(500).json({ error: err });
        } else {
            if (result.length > 0) {
                response.json({ creditbalance: result[0].creditbalance });
            } else {
                response.json('Account not found');
            }
        }
    });
});

router.get('/creditlimit/:id', function(request, response) {
    account.getCreditLimit(request.params.id, function(err, result) {
        if (err) {
            response.status(500).json({ error: err });
        } else {
            if (result.length > 0) {
                response.json({ creditlimit: result[0].creditlimit });
            } else {
                response.status(404).json({ error: "Account not found" });
            }
        }
    });
});

router.post('/defineDebit', function(request,response){
    const {card_number} = request.body;
    account.defineDebit(card_number, function(err,result){
        if (err){
            response.json(err);
        }
        else{
            response.json(result[0]);
        }
    })
});

router.post('/defineCredit', function(request,response){
    const {card_number} = request.body;
    account.defineCredit(card_number, function(err,result){
        if (err){
            response.json(err);
        }
        else{
            response.json(result[0]);
        }
    })
});

module.exports=router