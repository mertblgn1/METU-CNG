CREATE DATABASE IF NOT EXISTS cocktail_maker;
USE cocktail_maker;

DROP TABLE IF EXISTS AddToFavorites;
DROP TABLE IF EXISTS CategoryHasCocktail;
DROP TABLE IF EXISTS CocktailHasIngredient;
DROP TABLE IF EXISTS CocktailImage;
DROP TABLE IF EXISTS MakeCocktail;
DROP TABLE IF EXISTS UserRecipe;
DROP TABLE IF EXISTS PredefinedRecipe;
DROP TABLE IF EXISTS Ingredient;
DROP TABLE IF EXISTS Category;
DROP TABLE IF EXISTS User;

CREATE TABLE IF NOT EXISTS User (
    id INTEGER PRIMARY KEY AUTO_INCREMENT,
    email VARCHAR(255) UNIQUE NOT NULL,
    name VARCHAR(255) NOT NULL,
    password VARCHAR(255) NOT NULL,
    dob DATE NOT NULL,
    bar VARCHAR(1024),
    shoppingList VARCHAR(1024)
);

CREATE TABLE IF NOT EXISTS Category (
    id INTEGER PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(255) NOT NULL
);

CREATE TABLE IF NOT EXISTS PredefinedRecipe (
    id INTEGER PRIMARY KEY AUTO_INCREMENT,
    description TEXT NOT NULL,
    name TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS Ingredient (
    id INTEGER PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(255) NOT NULL,
    type VARCHAR(255),
    alcoholPercentage REAL CHECK (alcoholPercentage >= 0 AND alcoholPercentage <= 100)
);

CREATE TABLE IF NOT EXISTS UserRecipe (
    id INTEGER PRIMARY KEY AUTO_INCREMENT,
    description TEXT,
    userId INTEGER NOT NULL,
    FOREIGN KEY (userId) REFERENCES User(id)
);

CREATE TABLE IF NOT EXISTS AddToFavorites (
    userId INTEGER NOT NULL,
    cocktailId INTEGER NOT NULL,
    PRIMARY KEY (userId, cocktailId),
    FOREIGN KEY (userId) REFERENCES User(id),
    FOREIGN KEY (cocktailId) REFERENCES PredefinedRecipe(id)
);

CREATE TABLE IF NOT EXISTS MakeCocktail (
    userId INTEGER NOT NULL,
    cocktailId INTEGER NOT NULL,
    PRIMARY KEY (userId, cocktailId),
    FOREIGN KEY (userId) REFERENCES User(id),
    FOREIGN KEY (cocktailId) REFERENCES PredefinedRecipe(id)
);

CREATE TABLE IF NOT EXISTS CategoryHasCocktail (
    categoryId INTEGER NOT NULL,
    cocktailId INTEGER NOT NULL,
    PRIMARY KEY (categoryId, cocktailId),
    FOREIGN KEY (categoryId) REFERENCES Category(id),
    FOREIGN KEY (cocktailId) REFERENCES PredefinedRecipe(id)
);

CREATE TABLE IF NOT EXISTS CocktailHasIngredient (
    cocktailId INTEGER NOT NULL,
    ingredientId INTEGER NOT NULL,
    quantity VARCHAR(255),
    PRIMARY KEY (cocktailId, ingredientId),
    FOREIGN KEY (cocktailId) REFERENCES PredefinedRecipe(id),
    FOREIGN KEY (ingredientId) REFERENCES Ingredient(id)
);

CREATE TABLE IF NOT EXISTS CocktailImage (
    cocktailId INTEGER,
    cocktailImage VARCHAR(255) NOT NULL,
    PRIMARY KEY (cocktailId, cocktailImage(255)),
    FOREIGN KEY (cocktailId) REFERENCES PredefinedRecipe(id)
);

-- Insert data into tables
SET FOREIGN_KEY_CHECKS=0;

INSERT INTO `cocktail_maker`.`User`
(`email`, `name`, `password`, `dob`, `bar`, `shoppingList`)
VALUES
('mert.can.bilgin01@gmail.com', 'Mert', 'password123', '2001-07-10', '1', '1,2,3');

INSERT INTO `cocktail_maker`.`Category`
(`name`)
VALUES
('Top 100'),
('Classic');

INSERT INTO `cocktail_maker`.`PredefinedRecipe`
(`id`, `description`, `name`)
VALUES
(1, 'The Margarita is a classic cocktail that originated in Mexico and has become a beloved drink all over the world. It is a simple yet delicious combination of tequila, triple sec, lime juice, and a pinch of salt. The history of the Margarita is a bit murky, with several stories claiming to be the origin. Some say it was created in the 1930s by a bartender named Don Carlos Orozco, while others credit socialite Margaret Sames for inventing the drink in the 1940s. Regardless of its exact origins, the Margarita has stood the test of time and remains a popular choice among cocktail enthusiasts. The flavour profile of this drink is a perfect balance of sweet and tart, with the tequila providing a smooth and slightly smoky kick. The salt on the rim of the glass adds a touch of savouriness and enhances the overall flavour experience. Whether you prefer it frozen, on the rocks, or straight up, the Margarita is a must-try for any cocktail lover.', 'Margarita'),
(2, 'First seen in Hugo Ensslins 1915 book "Recipes for Mixed Drinks", this classic cocktail can now be seen the world over.', 'Alexander'),
(3, 'The drink was invented and named by fictional secret agent James Bond in the 1953 novel Casino Royale. "A dry martini," [Bond] said. "One. In a deep champagne goblet.""Oui, monsieur.""Just a moment. Three measures of Gordon''s, one of vodka, half a measure of Kina Lillet. Shake it very well until it''s ice-cold, then add a large thin slice of lemon peel. Got it?"', 'Vesper'),
(4, 'The Long Island Ice Tea is a classic cocktail characterized by its deceptive potency and refreshing taste, despite a hefty mix of spirits. A medley of white rum, gin, tequila, vodka, and a hint of Cointreau, it is balanced with the tang of lemon juice and the sweetness of sugar syrup. The inclusion of cola not only contributes to the drink''s iconic appearance—resembling a non-alcoholic iced tea—but also adds a familiar, effervescent flavor that complements the complexity of the spirits. Traditionally served in a highball glass, the Long Island Ice Tea is a favorite for those who enjoy a cocktail that packs a punch while remaining pleasantly palatable.', 'Long Island Iced Tea'),
(5, 'The Mint Julep is a classic Southern cocktail that has been enjoyed for centuries. It is believed to have originated in the late 1700s or early 1800s, with its roots traced back to Virginia. The drink is traditionally made with fresh mint leaves, bourbon whiskey, and a touch of sugar. The mint leaves are commonly muddled in the bottom of a glass to release their aromatic oils and then combined with bourbon, creating a refreshing and slightly sweet flavor profile. The Mint Julep is often served in a silver or pewter cup, filled with crushed ice, and garnished with a sprig of mint. This cocktail is a staple at the Kentucky Derby and is known for its ability to cool and refresh on a hot summer day. With its simple yet delightful combination of ingredients, the Mint Julep remains a timeless and beloved drink by many.', 'Mint Julep');

INSERT INTO `cocktail_maker`.`Ingredient`
(`name`, `type`, `alcoholPercentage`)
VALUES
('Cointreau', 'Drink', 40),
('Lime juice', 'Drink', 0),
('Pineapple juice', 'Drink', 0),
('Gin', 'Drink', 40),
('Grenadine', 'Drink', 0),
('Angostura Bitters', 'Drink', 0),
('Cherry liqueur', 'Drink', 0),
('DOM Benedictine', 'Drink', 40),
('Triple Sec', 'Drink', 40),
('Tequila', 'Drink', 40),
('Salt', 'Food', NULL),
('Cream', 'Food', NULL),
('Creme De Cacao', 'Drink', 15),
('Vodka', 'Drink', 40),
('Lillet Blanc', 'Drink', 17),
('Cola', 'Drink', 0),
('White Rum', 'Drink', 40),
('Sugar Syrup', 'Drink', 0),
('Mint Leaf', 'Food', NULL),
('Bourbon', 'Drink', 40);

INSERT INTO `cocktail_maker`.`UserRecipe`
(`description`, `userId`)
VALUES
('Fresh summer cocktail', 1),
('Winter cocktail to get warm', 1);

INSERT INTO `cocktail_maker`.`AddToFavorites`
(`userId`, `cocktailId`)
VALUES
(1, 1),
(1, 2);

INSERT INTO `cocktail_maker`.`MakeCocktail`
(`userId`, `cocktailId`)
VALUES
(1, 1),
(1, 2);

INSERT INTO `cocktail_maker`.`CategoryHasCocktail`
(`categoryId`, `cocktailId`)
VALUES
(1, 1),
(1, 2),
(2, 3),
(2, 4),
(2, 5);

INSERT INTO `cocktail_maker`.`CocktailHasIngredient`
(`cocktailId`, `ingredientId`, `quantity`)
VALUES
(1, 1, '7.5 ml'),
(1, 2, '15 ml'),
(1, 3, '120 ml'),
(1, 4, '30 ml'),
(1, 5, '10 ml'),
(1, 6, '1 dash'),
(1, 7, '15 ml'),
(1, 8, '7.5 ml'),
(2, 9, '20 ml'),
(2, 2, '15 ml'),
(2, 10, '50 ml'),
(2, 11, 'Pinch'),
(3, 4, '30 ml'),
(3, 12, '30 ml'),
(3, 13, '30 ml'),
(4, 14, '15 ml'),
(4, 4, '45 ml'),
(4, 15, '7.5 ml'),
(5, 1, '15 ml'),
(5, 16, 'Top up'),
(5, 17, '15 ml'),
(5, 2, '30 ml'),
(5, 4, '15 ml'),
(5, 10, '15 ml'),
(5, 18, '20 ml'),
(5, 14, '15 ml'),
(6, 19, '12 leaves'),
(6, 20, '60 ml'),
(6, 18, '1 teaspoon');

INSERT INTO `cocktail_maker`.`CocktailImage`
(`cocktailId`, `cocktailImage`)
VALUES
(6, 'singaporeSling.jpg'),
(6, 'singaporeSling2.jpg'),
(1, 'margarita.jpg'),
(2, 'alexander.jpg'),
(3, 'vesper.jpg'),
(4, 'longIslandIceTea.jpg'),
(4, 'longIslandIceTea2.jpg'),
(5, 'mintJulep.jpg'),
(5, 'mintJulep2.jpg');

SET FOREIGN_KEY_CHECKS=1;
