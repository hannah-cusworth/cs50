SELECT "name" from "people"
WHERE "id" IN (SELECT DISTINCT "person_id" FROM "stars"
WHERE "movie_id" IN (SELECT "id" FROM "movies" WHERE "year" = 2004))
ORDER BY "birth" ASC