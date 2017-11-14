var Datastore = require('nedb');
var collection = new Datastore({filename : 'tenants'});
collection.loadDatabase();

var TenantsCollection = () => {
    return {
        getAll: () => {
            return new Promise((resolve, reject) => {
                collection.find({}, (err, all) => {
                    resolve(all);
                })
            })
        },
        getOne: (id) => {
            return new Promise((resolve, reject) => {
                collection.findOne({_id: id}, (err, record) => {
                    resolve(record);
                })
            })
        },
        update: (id, data) => {
            return new Promise((resolve, reject) => {
                collection.update({_id: id}, {$set:{data}}, {}, function (err, count) {
                    resolve(count);
                })
            })
        },
        count: (query) => {
            query = query ? query : {}
            return new Promise((resolve, reject) => {
                collection.count(query, function (err, count) {
                    resolve(count)
                })
            })
        }
    }
};

module.exports = TenantsCollection;
