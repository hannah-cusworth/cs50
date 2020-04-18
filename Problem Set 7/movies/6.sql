SELECT AVG("rating")
FROM "ratings"
JOIN "movies" ON movies.id=ratings.movie_id
WHERE "year" == 2012 AND "rating" IS NOT NULL