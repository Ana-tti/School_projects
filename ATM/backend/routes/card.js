const express = require('express');
const router = express.Router();
const card = require('../models/card_model');

router.get('/',function(request, response){
    card.getAll(function(err, result){
        if(err){
            response.json(err);
        }
        else{
            response.json(result);
        }
    })
});

router.get('/:cardnumber',function(request, response){
    card.getByCardNum(request.params.cardnumber,function(err, result){
        if(err){
            response.json(err);
        }
        else{
            response.json(result[0]);
        }
    })
});

router.post('/',function(request, response){
    card.add(request.body, function(err, result){
        if(err){
            response.json(err);
        }
        else{
            response.json(result.affectedRows);
        }
    })
});

router.put('/:cardnumber',function(request, response){
    card.update(request.params.id, request.body, function(err, result){
        if(err){
            response.json(err);
        }
        else{
            response.json(result.affectedRows);
        }
    })
});

router.delete('/:cardnumber',function(request, response){
    card.delete(request.params.id, function(err, result){
        if(err){
            response.json(err);
        }
        else{
            response.json(result.affectedRows);
        }
    })
});

    router.post('/checkLocked',function(request, response){
        const {cardnumber} = request.body;
        card.checkLocked(cardnumber,function(err, result){
            if(err){
                response.json(err);
            }
            else{
                response.json(result[0]);
            }
        })
    });

    router.put('/updateAttempts', function(request,response){
        card.updateAttempts(request.params.cardnumber, request.body, function(err,result){
            if(err){
                response.json(err);
            }

            else{
                response.json(result.affectedRows)
            }
        })
    });

    router.put('/resetAttempts', function(request,response){
        card.resetAttempts(request.params.cardnumber, request.body, function(err,result){
            if(err){
                response.json(err);
            }

            else{
                response.json(result.affectedRows)
            }
        })
    });


module.exports=router