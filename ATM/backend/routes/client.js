const express = require('express');
const router = express.Router();
const client = require('../models/client_model');

router.get('/',function(request, response){
    client.getAll(function(err, result){
        if(err){
            response.json(err);
        }
        else{
            response.json(result);
        }
    })
});

router.get('/:id',function(request, response){
    client.getById(request.params.id,function(err, result){
        if(err){
            response.json(err);
        }
        else{
            response.json(result[0]);
        }
    })
});

router.post('/',function(request, response){
    client.add(request.body, function(err, result){
        if(err){
            response.json(err);
        }
        else{
            response.json(result.affectedRows);
        }
    })
});

router.put('/:id',function(request, response){
    client.update(request.params.id, request.body, function(err, result){
        if(err){
            response.json(err);
        }
        else{
            response.json(result.affectedRows);
        }
    })
});

router.delete('/:id',function(request, response){
    client.delete(request.params.id, function(err, result){
        if(err){
            response.json(err);
        }
        else{
            response.json(result.affectedRows);
        }
    })
});
module.exports=router