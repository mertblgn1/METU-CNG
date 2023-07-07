-- Query 1
SELECT username, name, surname, email FROM Users;

-- Query 2
SELECT price, cpu, gpu FROM Computer
WHERE price > '15000' AND time_bought > TO_DATE('30/01/2022', 'DD/MM/YYYY') AND maintenance_date > TO_DATE('10/06/2022', 'DD/MM/YYYY');

-- Query 3
SELECT name, surname FROM Users, UserSubscription
WHERE Users.username = UserSubscription.username AND start_date > TO_DATE('01/01/2022', 'DD/MM/YYYY');

-- Query 4
SELECT name, surname, Game.game_id
FROM Users, Library, LibraryGame, Game
WHERE Users.username = Library.username
AND Library.library_connection_token = LibraryGame.library_connection_token
AND LibraryGame.game_id = Game.game_id;

-- Query 5
SELECT name, surname
FROM Users, PlaySession, Game, Library
WHERE Library.library_connection_token = PlaySession.library_connection_token
AND PlaySession.game_id = Game.game_id
AND Users.username = Library.username
AND Game.game_name = 'Assassin''s Creed Valhalla'
AND PlaySession.start_date_time > TO_DATE('17/10/2022', 'DD/MM/YYYY');

-- Query 6
SELECT name, surname, SUM((CAST(end_date_time as date) - CAST(start_date_time as date)) * 1440)
AS TotalPlayTimeinMinutes
FROM Users LEFT JOIN Library
ON Library.username = Users.username
LEFT JOIN PlaySession
ON Library.library_connection_token = PlaySession.library_connection_token
LEFT JOIN Game
ON PlaySession.game_id = Game.game_id
WHERE Game.game_name = 'Assassin''s Creed Valhalla'
GROUP BY name, surname;