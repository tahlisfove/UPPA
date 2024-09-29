db.getCollection('films').find({})

/* 1 */
db.films.count()

/* 2 */
db.films.findOne({title:"Titanic"})

/* 3 */
db.films.distinct("genre")

/* 4 */
db.films.distinct("country")

/* 5 */
db.films.find({genre:"Comédie"})

/* 6 */
db.films.count({genre:"Drame", year:1988})

/* 7 */
db.films.find({genre:"Thriller", "director.last_name": "Hitchcock"})

/* 8 */
db.films.find({summary:null})

/* 9 */
db.films.find({"director.last_name": "Tarantino", summary:/mort/i})

/* 10 */
db.films.find({"director.last_name": "Tarantino", "actors.birth_date": {$lt:1940}})

/* 11 */
db.films.find({"director.last_name": "Tarantino", "actors.birth_date": {$lt:1940}, "actors.birth_date": {$not: {$gt:1968}}})

/* 12 */
db.films.aggregate([{$match: {"actors": {$elemMatch : {birth_date: {$lt:1940}, role: "Bill"}}}}])

/* 13 */
db.films.aggregate([{$match: {"actors.0.first_name": "Kevin", "actors.0.last_name": "Spacey"}}])

/* 14 */
db.films.aggregate([{$match: {genre: {$in: ["Crime", "Thriller", "Suspense"]}}}, {$group: {_id: "$director", total_films: {$sum:1}}}])

/* 15 */
db.films.aggregate([{$unwind: "$actors"}, {$group: {_id: {actors_id:"$actors._id", actors_first_name: "$actors.first_name", actors_last_name: "$actors.last_name"}, total_films: {$sum:1}}}, {$match: {"total_films": {$gte:5}}}])

/* 16 */
db.films.aggregate([{$group: {_id: {director_first_name: "$director.first_name", director_last_name: "$director.last_name"}, films: {$push: {title: "$title"}}}}])