-- This violates the id PRIMARY KEY for the Actor table because I try to insert an actor with the same id
-- Output: ERROR 1062 (23000): Duplicate entry '68625' for key 'PRIMARY'
INSERT INTO Actor
VALUES (68625, 'Lucero', 'Alfred', 'Male', '1995-01-17', NULL);

-- This violates the id PRIMARY KEY for the Movie table because I try to insert a movie with the same id
-- Output: ERROR 1062 (23000): Duplicate entry '12' for key 'PRIMARY'
INSERT INTO Movie
VALUES (12, 'Rush Hour', 2005, 'PG-13', 'Warner');

-- This violates the id PRIMARY KEY for the Director table because I try to insert a director with the same id
-- Output: ERROR 1062 (23000): Duplicate entry '16' for key 'PRIMARY'
INSERT INTO Director
VALUES (16, 'Boss', 'Master', '1995-01-17', NULL);

-- This violates the aid FOREIGN KEY for the MovieActor table because it attempts to insert a tuple with an aid not present already in its referenced Actor table
-- Output: ERROR 1452 (23000): Cannot add or update a child row: a foreign key constraint fails ('CS143', 'MovieActor', CONSTRAINT 'MovieActor_ibfk_2' FOREIGN KEY ('aid') REFERENCES 'Actor' ('id'))
INSERT INTO MovieActor VALUES (12, 70000, 'Taxi Driver');

-- This violates the mid FOREIGN KEY for the MovieActor table because it attempts to insert a tuple with a mid not present already in its referenced Movie table
-- Output: ERROR 1452 (23000): Cannot add or update a child row: a foreign key constraint fails ('CS143', 'MovieActor', CONSTRAINT 'MovieActor_ibfk_1' FOREIGN KEY ('mid') REFERENCES 'Movie' ('id'))
INSERT INTO MovieActor VALUES (70000, 12, 'Bus Driver');

-- This violates the mid FOREIGN KEY for the Review table because it attempts to insert a tuple with a mid not present already in its referenced Movie table
-- Output: ERROR 1452 (23000): Cannot add or update a child row: a foreign key constraint fails ('CS143', 'Review', CONSTRAINT 'Review_ibfk_1' FOREIGN KEY ('mid') REFERENCES 'Movie' ('id'))
INSERT INTO Review VALUES ('Alfred', '1970-01-02 00:00:01', 70000, 5, 'Not great at all');

-- This violates the mid FOREIGN KEY for the MovieDirector table because it attempts to insert a tuple with a mid not present already in its referenced Movie table
-- Output: ERROR 1452 (23000): Cannot add or update a child row: a foreign key constraint fails ('CS143', 'MovieDirector', CONSTRAINT 'MovieDirector_ibfk_1' FOREIGN KEY ('mid') REFERENCES 'Movie' ('id'))
INSERT INTO MovieDirector VALUES (70000, 12);

-- This violates the did FOREIGN KEY for the MovieDirector table because it attempts to insert a tuple with a did not present already in its referenced Director table
-- Output: ERROR 1452 (23000): Cannot add or update a child row: a foreign key constraint fails ('CS143', 'MovieDirector', CONSTRAINT 'MovieDirector_ibfk_2' FOREIGN KEY ('did') REFERENCES 'Director' ('id'))
INSERT INTO MovieDirector VALUES (12, 70000);

-- This violates the mid FOREIGN KEY for the MovieGenre table because it attempts to insert a tuple with a mid not present already in its referenced Movie table
-- Output: ERROR 1452 (23000): Cannot add or update a child row: a foreign key constraint fails ('CS143', 'MovieGenre', CONSTRAINT 'MovieGenre_ibfk_1' FOREIGN KEY ('mid') REFERENCES 'Movie' ('id'))
INSERT INTO MovieGenre VALUES (70000, 'Comedy');

-- This breaks the year >= 0 CHECK constraint within the Movie table
-- As one can see, inserting a negative year doesn't logically make sense and breaks the constraint
INSERT INTO Movie
VALUES (10, 'Rush Hour', -1240, 'PG-13', 'Warner');

-- This breaks the rating >= 0 and rating <= 5 CHECK constraint within the Review table
-- As one can see, the rating is 25, which is above the 0-5 star rating range
INSERT INTO Review
VALUES ('Alfred', '1970-01-01 00:00:01', 10, 25, 'This is bad');

-- This breaks the dob < '2015-10-18' CHECK constraint within the Actor table
-- As one can see, the date of birth occurs beyond the present day, so the birth date should be earlier
INSERT INTO Actor
VALUES (12000, 'Tucker', 'Chris', 'Male', '2017-10-20', '2012-08-12');