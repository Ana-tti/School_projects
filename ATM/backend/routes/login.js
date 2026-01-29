const express = require('express');
const router = express.Router();
const bcrypt = require('bcryptjs');
const card = require('../models/card_model');
const jwt = require('jsonwebtoken');
const dotenv = require('dotenv');

router.post('/', function(request, response){
    card.checkLocked(request.body.cardnumber,function(err, result){
      if (err){
        response.json(dbError);
      return;
      }

      else if(result[0].is_locked == 1){
          console.log("Card locked");
          response.send('Card is locked');
          return;
        }
else{
    if(request.body.cardnumber && request.body.pin){
      const user = request.body.cardnumber;
      const pass = request.body.pin;
        card.checkPin(user, function(dbError, dbResult) {
          if(dbError){
            response.json(dbError);
          }
          else{
            if (dbResult.length > 0) {
              bcrypt.compare(pass,dbResult[0].pin, function(err,compareResult) {
                if(compareResult) {
                  console.log("success");
                  card.resetAttempts(user,function(dbError,dbResult){
                    if(dbError){
                      response.send(dbError);
                    }
                  })
                  const token = generateAccessToken({ cardnumber: user });
                  response.setHeader('Content-Type', 'application/json'); 
                  response.send(token);
                }
                else {
                    console.log("wrong password");
                    response.send(false);
                    card.updateAttempts(user,function(dbError,dbResult){
                      if(dbError){
                        response.send(dbError);
                      }
                    })
                    

                }			
              }
              );
            }
            else{
              console.log("user does not exist");
              response.send(false);
            }
          }
          }
        );
      }
    else{
      console.log("username or password missing");
      response.send(false);
    }
  }
  }
)});
  

function generateAccessToken(cardnumber) {
  dotenv.config();
  return jwt.sign(cardnumber, process.env.MY_TOKEN, { expiresIn: '1800s' });
}

module.exports=router; 