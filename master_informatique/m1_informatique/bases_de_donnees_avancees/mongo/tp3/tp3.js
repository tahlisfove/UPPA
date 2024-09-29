db.getCollection('films').find({})

/* 1 */
var mapFunction = function () {emit(this.genre, 1);};
var reduceFunction = function (key, values) {return Array.sum(values);};
var queryParam = {query : {}, out : "result_set"}
db.films.mapReduce(mapFunction, reduceFunction, queryParam);
db.result_set.find();

/* 2 */
var mapFunction = function () {emit(this.genre, 1);};
var reduceFunction = function (key, values) {return Array.sum(values);};
var queryParam = {query : {country : "FR"}, out : "result_set"}
db.films.mapReduce(mapFunction, reduceFunction, queryParam);
db.result_set.find();

/* 3a */
var mapFunction = function () {emit({genre: this.genre, country: this.country},1);};
var reduceFunction = function (key, values) {return Array.sum(values);};
var queryParam = {query : {"year": {$gte:2000}}, out : "result_set"}
db.films.mapReduce(mapFunction, reduceFunction, queryParam);
db.result_set.find();

/* 3b */
var mapFunction = function () {
    for (var i = 0; i < this.actors.length; i++) {
        var actor = this.actors[i];
        var age = this.year - actor.birth_date;
        emit(this.genre, age);
    }
};

var reduceFunction = function (key, values) {
    var sum = 0;
    var count = 0;
    for (var i = 0; i < values.length; i++) {
        sum += values[i];
        count++;
    }
    return sum / count;
};

var queryParam = {
    query: {
        "actors.birth_date": { $exists: true, $ne: null },
        "genre": { $exists: true, $ne: null }
    },
    out: "result_set"
};

db.films.mapReduce(mapFunction, reduceFunction, queryParam);
db.result_set.find();