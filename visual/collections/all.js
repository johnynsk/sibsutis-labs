var filmsCollection = require('./films')
var clientsCollection = require('./clients')
var tenantsCollection = require('./tenants')

var Collections = () => {
    return {
        films: filmsCollection,
        clients: clientsCollection,
        tenants: tenantsCollection
    }
}

module.exports = Collections;
