-- Check that the Actor.id/MovieActor.aid and Movie.id/MovieActor.mid match up
-- such that it lists those actors by first and last name who acted in the
-- movie 'Die Another Day'
SELECT CONCAT(first, ' ', last) AS ActorName
FROM Actor, MovieActor
WHERE Actor.id = MovieActor.aid AND 
      (SELECT id 
      FROM Movie 
      WHERE title = 'Die Another Day') = MovieActor.mid;

-- First separate those actors who have acted in two or more movies from
-- the rest of the actors. Then count them up into one grand total.
SELECT COUNT(actormult)
FROM (SELECT aid AS actormult 
     FROM MovieActor 
     GROUP BY aid 
     HAVING COUNT(*) >= 2) AS ActorCount;

-- Find all the female actresses who act in rated PG-13 or R movies
-- Make sure the actor/movie ids match those with proper rating and with
-- proper gender before listing the actresses all by last then first name.
SELECT DISTINCT CONCAT(last, ',', first) AS ActorName
FROM Actor, MovieActor
WHERE EXISTS (SELECT id
      	     FROM Movie WHERE (rating = 'PG-13' OR rating = 'R')
	     AND MovieActor.mid = Movie.id)
	     AND Actor.id = MovieActor.aid AND Actor.sex = 'Female';
