'use strict';

class Vertex{
    constructor (number, cost) {
        this._number = number;
        
        if (typeof cost !== 'undefined') {
            this._cost = cost;
        } else {
            this._cost = Infinity;
        }

        this._path = [];
        this._visited = false;
    }

    getNumber() {
        return this._number;
    }

    getCost() {
        return this._cost;
    }

    getPath() {
        return this._path;
    }

    setCost(cost) {
        this._cost = cost;
        return this;
    }

    setPath(path) {
        this._path = path;
        return this;
    }

    isVisited() {
        return this._visited;
    }

    setVisited(visited) {
        this._visited = visited;
        return this;
    }
};


Vertex.prototype._number = null;
Vertex.prototype._cost = Infinity;
Vertex.prototype._visited = false;
/**
 * @var Vertex[]
 */
Vertex.prototype._path = [];

module.exports = Vertex
