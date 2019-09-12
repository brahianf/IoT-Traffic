'use strict'

const mongoose = require ('mongoose');
const agentSchema = require('./agent');

//Libreria para PROMISES personalizadas
mongoose.Promise = require('bluebird');

//Hacer conexion y plasmar Schemas 
module.exports = async function connect(dbUrl = 'mongodb://localhost:27017//iot')
{
    let conn = await mongoose.createConnection(dbUrl, {useMongoClient: true})
    return{
        Agent: conn.model('Agent', agentSchema)
    }
}