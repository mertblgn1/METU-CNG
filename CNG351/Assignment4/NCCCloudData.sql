DROP TABLE PlaySession;
DROP TABLE Computer;
DROP TABLE LibraryGame;
DROP TABLE Library;
DROP TABLE Game;
DROP TABLE UserSubscription;
DROP TABLE Subscription;
DROP TABLE Users;

CREATE TABLE Users(
	username VARCHAR(40) NOT NULL,
	name VARCHAR(40) NOT NULL,
	surname VARCHAR(40) NOT NULL,
	email varchar(40) NOT NULL,
	dob DATE NOT NULL,
	PRIMARY KEY(username)
);

CREATE TABLE Subscription(
	subscription_id VARCHAR(40) NOT NULL,
	type VARCHAR(20) NOT NULL CHECK(type IN ('low', 'mid', 'high')),
	monthly_price VARCHAR(20) NOT NULL CHECK(monthly_price BETWEEN 100 AND 1000),
	payment_type VARCHAR(20) NOT NULL CHECK(payment_type IN ('credit-card', 'PayPal', 'bank-transfer')),
	PRIMARY KEY(subscription_id)
);

CREATE TABLE UserSubscription(
	username VARCHAR(40) NOT NULL,
	subscription_id VARCHAR(40) NOT NULL,
	start_date DATE NOT NULL,
	end_date DATE NOT NULL,
	CONSTRAINT fk_user FOREIGN KEY (username) REFERENCES Users(username),
	CONSTRAINT fk_subscription FOREIGN KEY (subscription_id) REFERENCES Subscription(subscription_id),
	PRIMARY KEY(username, subscription_id)
);

CREATE TABLE Game(
	game_id VARCHAR(40) NOT NULL,
	game_name VARCHAR(40) NOT NULL,
	game_description VARCHAR(400) NOT NULL,
	PRIMARY KEY(game_id)
);

CREATE TABLE Library(
	library_connection_token VARCHAR(40) NOT NULL,
	username VARCHAR(40) NOT NULL,
	library_name VARCHAR(20) NOT NULL CHECK(library_name IN ('Steam', 'Epic Games')),
	CONSTRAINT fk_library_user FOREIGN KEY (username) REFERENCES Users(username),
	PRIMARY KEY(library_connection_token)
);

CREATE TABLE LibraryGame(
	library_connection_token VARCHAR(40) NOT NULL,
	game_id VARCHAR(40) NOT NULL,
	CONSTRAINT fk_token FOREIGN KEY (library_connection_token) REFERENCES Library(library_connection_token),
	CONSTRAINT fk_game FOREIGN KEY (game_id) REFERENCES Game(game_id),
	PRIMARY KEY(library_connection_token, game_id)
);

CREATE TABLE Computer(
	id VARCHAR(40) NOT NULL,
	price VARCHAR(20) NOT NULL,
	cpu VARCHAR(60) NOT NULL,
	gpu VARCHAR(40) NOT NULL,
	time_bought DATE NOT NULL,
	maintenance_date DATE NOT NULL,
	PRIMARY KEY(id)
);

CREATE TABLE PlaySession(
	game_id VARCHAR(40) NOT NULL,
	computer_id VARCHAR(40) NOT NULL,
	library_connection_token VARCHAR(40) NOT NULL,
	start_date_time TIMESTAMP NOT NULL,
	end_date_time TIMESTAMP NOT NULL,
	CONSTRAINT fk_game_id FOREIGN KEY (game_id) REFERENCES Game(game_id),
	CONSTRAINT fk_computer FOREIGN KEY (computer_id) REFERENCES Computer(id),
	CONSTRAINT fk_tokens FOREIGN KEY (library_connection_token) REFERENCES Library(library_connection_token),
	PRIMARY KEY(game_id, computer_id, library_connection_token)
);

--User
Insert into Users(username, name, surname, email, dob) VALUES ('nheinritz0', 'Nil', 'Heinritz', 'nheinritz0@gmail.com', TO_DATE ('24/06/1997', 'DD/MM/YYYY'));
Insert into Users(username, name, surname, email, dob) VALUES ('ssolan5', 'Salim', 'Sloan', 'ssolan5@gmail.com', TO_DATE ('24/06/1997', 'DD/MM/YYYY'));
Insert into Users(username, name, surname, email, dob) VALUES ('mrozenbaum1', 'Rozen', 'Baum', 'mrozenbaum1@gmail.com', TO_DATE ('06/03/1990', 'DD/MM/YYYY'));
Insert into Users(username, name, surname, email, dob) VALUES ('irevie3', 'David', 'Irevie', 'irevie3@gmail.com', TO_DATE ('22/05/1998', 'DD/MM/YYYY'));

--Subscription
Insert into Subscription(subscription_id, type, monthly_price, payment_type) VALUES ('1', 'high', '450', 'credit-card');
Insert into Subscription(subscription_id, type, monthly_price, payment_type) VALUES ('2', 'mid', '350', 'PayPal');
Insert into Subscription(subscription_id, type, monthly_price, payment_type) VALUES ('3', 'low', '150', 'bank-transfer');
Insert into Subscription(subscription_id, type, monthly_price, payment_type) VALUES ('4', 'high', '450', 'credit-card');
Insert into Subscription(subscription_id, type, monthly_price, payment_type) VALUES ('5', 'low', '450', 'credit-card');

--UserSubscription
Insert into UserSubscription(username, subscription_id, start_date, end_date) VALUES ('nheinritz0', '1',  TO_DATE ('18/02/2021', 'DD/MM/YYYY'),  TO_DATE ('18/10/2021', 'DD/MM/YYYY'));
Insert into UserSubscription(username, subscription_id, start_date, end_date) VALUES ('ssolan5', '2',  TO_DATE ('23/05/2022', 'DD/MM/YYYY'),  TO_DATE ('23/05/2022', 'DD/MM/YYYY'));
Insert into UserSubscription(username, subscription_id, start_date, end_date) VALUES ('mrozenbaum1', '3',  TO_DATE ('03/12/2022', 'DD/MM/YYYY'),  TO_DATE ('03/06/2023', 'DD/MM/YYYY'));
Insert into UserSubscription(username, subscription_id, start_date, end_date) VALUES ('irevie3', '5',  TO_DATE ('11/04/2021', 'DD/MM/YYYY'),  TO_DATE ('31/12/2023', 'DD/MM/YYYY'));
Insert into UserSubscription(username, subscription_id, start_date, end_date) VALUES ('nheinritz0', '4',  TO_DATE ('19/10/2021', 'DD/MM/YYYY'),  TO_DATE ('19/10/2022', 'DD/MM/YYYY'));

--Game
Insert into Game(game_id, game_name, game_description) VALUES ('1', 'God of War: Ragnarok', 'God of War Ragnarök is an action-adventure game developed by Santa Monica Studio and published by Sony Interactive Entertainment. It was released worldwide on November 9, 2022, for the PlayStation 4 and PlayStation 5, marking the first cross-gen release in the God of War series.');
Insert into Game(game_id, game_name, game_description) VALUES ('2', 'Cyberpunk 2077', 'Cyberpunk 2077 is an action role-playing video game developed by CD Projekt Red and published by CD Projekt. The story takes place in Night City, an open world set in the Cyberpunk universe.');
Insert into Game(game_id, game_name, game_description) VALUES ('3', 'Assassin''s Creed Valhalla', 'Assassin''s Creed Valhalla is a 2020 action role-playing video game developed by Ubisoft Montreal and published by Ubisoft. It is the twelfth major installment in the Assassin''s Creed series, and the successor to 2018''s Assassin''s Creed Odyssey.');
Insert into Game(game_id, game_name, game_description) VALUES ('4', 'The Witcher 3: Wild Hunt', 'The Witcher 3: Wild Hunt is a 2015 action role-playing game developed and published by CD Projekt. It is the sequel to the 2011 game The Witcher 2: Assassins of Kings and the third game in The Witcher video game series, played in an open world with a third-person perspective.');
Insert into Game(game_id, game_name, game_description) VALUES ('5', 'Don''t Starve Together', 'Don''t Starve Together is the standalone multiplayer expansion of the uncompromising wilderness survival game, Don''t Starve. Now including Reign of Giants; adding new characters, seasons, creatures, biomes, and Giant new challenges to Don''t Starve Together.');
Insert into Game(game_id, game_name, game_description) VALUES ('6', 'We Were Here Together', 'Embark on a puzzle solving adventure in which you and a partner must prove you can communicate and work together to escape the haunted Castle Rock.');

--Library
Insert into Library(library_connection_token, library_name, username) VALUES ('044e61f9d672', 'Steam', 'nheinritz0');
Insert into Library(library_connection_token, library_name, username) VALUES ('9f9d8e6173ea', 'Epic Games', 'ssolan5');
Insert into Library(library_connection_token, library_name, username) VALUES ('074a94021595', 'Steam', 'mrozenbaum1');
Insert into Library(library_connection_token, library_name, username) VALUES ('881cd083a7c2', 'Steam', 'irevie3');
Insert into Library(library_connection_token, library_name, username) VALUES ('1e89613783dd', 'Epic Games', 'irevie3');

--LibraryGame
Insert into LibraryGame(library_connection_token, game_id) VALUES ('044e61f9d672', '1');
Insert into LibraryGame(library_connection_token, game_id) VALUES ('044e61f9d672', '3');
Insert into LibraryGame(library_connection_token, game_id) VALUES ('044e61f9d672', '4');
Insert into LibraryGame(library_connection_token, game_id) VALUES ('9f9d8e6173ea', '2');
Insert into LibraryGame(library_connection_token, game_id) VALUES ('074a94021595', '5');
Insert into LibraryGame(library_connection_token, game_id) VALUES ('074a94021595', '6');
Insert into LibraryGame(library_connection_token, game_id) VALUES ('074a94021595', '4');
Insert into LibraryGame(library_connection_token, game_id) VALUES ('1e89613783dd', '2');
Insert into LibraryGame(library_connection_token, game_id) VALUES ('1e89613783dd', '3');
Insert into LibraryGame(library_connection_token, game_id) VALUES ('881cd083a7c2', '1');
Insert into LibraryGame(library_connection_token, game_id) VALUES ('881cd083a7c2', '4');

--Computer
Insert into Computer(id, price, cpu, gpu, time_bought, maintenance_date) VALUES ('1', '12000', 'AMD Ryzen 3 4100 Processor', 'Nvdia GTX 1650', TO_DATE ('15/03/2021', 'DD/MM/YYYY'), TO_DATE ('21/12/2021', 'DD/MM/YYYY'));
Insert into Computer(id, price, cpu, gpu, time_bought, maintenance_date) VALUES ('2', '36000', 'Intel® Core™ i7-12700F Processor', 'Nvdia RTX 3080', TO_DATE ('27/01/2022', 'DD/MM/YYYY'), TO_DATE ('30/06/2022', 'DD/MM/YYYY'));
Insert into Computer(id, price, cpu, gpu, time_bought, maintenance_date) VALUES ('3', '66000', 'Intel® Core™ i9-12900K Processor', 'Nvdia RTX 3090', TO_DATE ('06/05/2022', 'DD/MM/YYYY'), TO_DATE ('06/11/2022', 'DD/MM/YYYY'));
Insert into Computer(id, price, cpu, gpu, time_bought, maintenance_date) VALUES ('4', '12000', 'AMD Ryzen 3 4100 Processor', 'Nvdia GTX 1650', TO_DATE ('15/03/2021', 'DD/MM/YYYY'), TO_DATE ('21/12/2021', 'DD/MM/YYYY'));
Insert into Computer(id, price, cpu, gpu, time_bought, maintenance_date) VALUES ('5', '36000', 'Intel® Core™ i7-12700F Processor', 'Nvdia RTX 3080', TO_DATE ('27/01/2022', 'DD/MM/YYYY'), TO_DATE ('30/06/2022', 'DD/MM/YYYY'));
Insert into Computer(id, price, cpu, gpu, time_bought, maintenance_date) VALUES ('6', '66000', 'Intel® Core™ i9-12900K Processor', 'Nvdia RTX 3090', TO_DATE ('06/05/2022', 'DD/MM/YYYY'), TO_DATE ('06/11/2022', 'DD/MM/YYYY'));
Insert into Computer(id, price, cpu, gpu, time_bought, maintenance_date) VALUES ('7', '12000', 'AMD Ryzen 3 4100 Processor', 'Nvdia GTX 1650', TO_DATE ('15/03/2021', 'DD/MM/YYYY'), TO_DATE ('21/12/2021', 'DD/MM/YYYY'));
Insert into Computer(id, price, cpu, gpu, time_bought, maintenance_date) VALUES ('8', '66000', 'Intel® Core™ i9-12900K Processor', 'Nvdia RTX 3090', TO_DATE ('06/05/2022', 'DD/MM/YYYY'), TO_DATE ('06/11/2022', 'DD/MM/YYYY'));
Insert into Computer(id, price, cpu, gpu, time_bought, maintenance_date) VALUES ('9', '36000', 'Intel® Core™ i7-12700F Processor', 'Nvdia RTX 3080', TO_DATE ('27/01/2022', 'DD/MM/YYYY'), TO_DATE ('30/06/2022', 'DD/MM/YYYY'));
Insert into Computer(id, price, cpu, gpu, time_bought, maintenance_date) VALUES ('10', '12000', 'AMD Ryzen 3 4100 Processor', 'Nvdia GTX 1650', TO_DATE ('15/03/2021', 'DD/MM/YYYY'), TO_DATE ('21/12/2021', 'DD/MM/YYYY'));
Insert into Computer(id, price, cpu, gpu, time_bought, maintenance_date) VALUES ('11', '66000', 'Intel® Core™ i9-12900K Processor', 'Nvdia RTX 3090', TO_DATE ('06/05/2022', 'DD/MM/YYYY'), TO_DATE ('06/11/2022', 'DD/MM/YYYY'));
Insert into Computer(id, price, cpu, gpu, time_bought, maintenance_date) VALUES ('12', '36000', 'Intel® Core™ i7-12700F Processor', 'Nvdia RTX 3080', TO_DATE ('27/01/2022', 'DD/MM/YYYY'), TO_DATE ('30/06/2022', 'DD/MM/YYYY'));
Insert into Computer(id, price, cpu, gpu, time_bought, maintenance_date) VALUES ('13', '66000', 'Intel® Core™ i9-12900K Processor', 'Nvdia RTX 3090', TO_DATE ('06/05/2022', 'DD/MM/YYYY'), TO_DATE ('06/11/2022', 'DD/MM/YYYY'));
Insert into Computer(id, price, cpu, gpu, time_bought, maintenance_date) VALUES ('14', '66000', 'Intel® Core™ i9-12900K Processor', 'Nvdia RTX 3090', TO_DATE ('06/05/2022', 'DD/MM/YYYY'), TO_DATE ('06/11/2022', 'DD/MM/YYYY'));
Insert into Computer(id, price, cpu, gpu, time_bought, maintenance_date) VALUES ('15', '36000', 'Intel® Core™ i7-12700F Processor', 'Nvdia RTX 3080', TO_DATE ('27/01/2022', 'DD/MM/YYYY'), TO_DATE ('30/06/2022', 'DD/MM/YYYY'));
Insert into Computer(id, price, cpu, gpu, time_bought, maintenance_date) VALUES ('16', '66000', 'Intel® Core™ i9-12900K Processor', 'Nvdia RTX 3090', TO_DATE ('06/05/2022', 'DD/MM/YYYY'), TO_DATE ('06/11/2022', 'DD/MM/YYYY'));
Insert into Computer(id, price, cpu, gpu, time_bought, maintenance_date) VALUES ('17', '36000', 'Intel® Core™ i7-12700F Processor', 'Nvdia RTX 3080', TO_DATE ('27/01/2022', 'DD/MM/YYYY'), TO_DATE ('30/06/2022', 'DD/MM/YYYY'));
Insert into Computer(id, price, cpu, gpu, time_bought, maintenance_date) VALUES ('18', '36000', 'Intel® Core™ i7-12700F Processor', 'Nvdia RTX 3080', TO_DATE ('27/01/2022', 'DD/MM/YYYY'), TO_DATE ('30/06/2022', 'DD/MM/YYYY'));
Insert into Computer(id, price, cpu, gpu, time_bought, maintenance_date) VALUES ('19', '12000', 'AMD Ryzen 3 4100 Processor', 'Nvdia GTX 1650', TO_DATE ('15/03/2021', 'DD/MM/YYYY'), TO_DATE ('21/12/2021', 'DD/MM/YYYY'));

--PlaySession
Insert into PlaySession(game_id, library_connection_token, computer_id, start_date_time, end_date_time) VALUES ('1', '044e61f9d672', '4', TO_TIMESTAMP('2022-10-10 13:50', 'YYYY-MM-DD HH24:MI'), TO_TIMESTAMP('2022-10-10 15:50', 'YYYY-MM-DD HH24:MI'));
Insert into PlaySession(game_id, library_connection_token, computer_id, start_date_time, end_date_time) VALUES ('2', '9f9d8e6173ea', '2', TO_TIMESTAMP('2022-11-08 18:36', 'YYYY-MM-DD HH24:MI'), TO_TIMESTAMP('2022-11-08 23:06', 'YYYY-MM-DD HH24:MI'));
Insert into PlaySession(game_id, library_connection_token, computer_id, start_date_time, end_date_time) VALUES ('6', '074a94021595', '6', TO_TIMESTAMP('2022-04-23 09:50', 'YYYY-MM-DD HH24:MI'), TO_TIMESTAMP('2022-11-08 12:53', 'YYYY-MM-DD HH24:MI'));
Insert into PlaySession(game_id, library_connection_token, computer_id, start_date_time, end_date_time) VALUES ('3', '1e89613783dd', '3', TO_TIMESTAMP('2022-10-18 21:38', 'YYYY-MM-DD HH24:MI'), TO_TIMESTAMP('2022-10-18 22:01', 'YYYY-MM-DD HH24:MI'));
Insert into PlaySession(game_id, library_connection_token, computer_id, start_date_time, end_date_time) VALUES ('3', '044e61f9d672', '1', TO_TIMESTAMP('2022-10-14 13:50', 'YYYY-MM-DD HH24:MI'), TO_TIMESTAMP('2022-10-14 15:50', 'YYYY-MM-DD HH24:MI'));
Insert into PlaySession(game_id, library_connection_token, computer_id, start_date_time, end_date_time) VALUES ('2', '9f9d8e6173ea', '10', TO_TIMESTAMP('2022-04-23 09:50', 'YYYY-MM-DD HH24:MI'), TO_TIMESTAMP('2022-04-23 13:53', 'YYYY-MM-DD HH24:MI'));
Insert into PlaySession(game_id, library_connection_token, computer_id, start_date_time, end_date_time) VALUES ('5', '074a94021595', '12', TO_TIMESTAMP('2022-10-16 13:58', 'YYYY-MM-DD HH24:MI'), TO_TIMESTAMP('2022-10-16 15:47', 'YYYY-MM-DD HH24:MI'));
Insert into PlaySession(game_id, library_connection_token, computer_id, start_date_time, end_date_time) VALUES ('4', '881cd083a7c2', '8', TO_TIMESTAMP('2022-11-13 22:10', 'YYYY-MM-DD HH24:MI'), TO_TIMESTAMP('2022-11-14 00:26', 'YYYY-MM-DD HH24:MI'));
Insert into PlaySession(game_id, library_connection_token, computer_id, start_date_time, end_date_time) VALUES ('4', '044e61f9d672', '19', TO_TIMESTAMP('2022-11-13 22:10', 'YYYY-MM-DD HH24:MI'), TO_TIMESTAMP('2022-11-14 00:26', 'YYYY-MM-DD HH24:MI'));
