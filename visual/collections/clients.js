var Datastore = require('nedb');
var collection = new Datastore({filename : 'clients'});
collection.loadDatabase();

var ClientsCollection = () => {
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
                collection.update({_id: id}, data, {}, (err, count) => {
                    console.log('changed ' + count + ' rows');
                    resolve(count);
                })
            })
        },
        insert: data => {
            return new Promise((resolve, reject) => {
                collection.insert(data, (err, document) => {
                    resolve(document);
                })
            })
        },
        removeOne: id => {
            return new Promise((resolve, reject) => {
                collection.remove({_id: id}, {}, (err, count) => {
                    resolve(count)
                })
            })
        },
        count: query => {
            query = query ? query : {}
            return new Promise((resolve, reject) => {
                collection.count(query, function (err, count) {
                    resolve(count)
                })
            })
        }
    }
};

module.exports = ClientsCollection;
