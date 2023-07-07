--Name: Mert Can, Surname: Bilgin, Student ID: 2453025
--I read and accept the submission rules and the extra rules. This is my own work that is done by myself only



data TernaryTree = NodeNotFound | NodeExists | NotReachable | Empty | Node String TernaryTree TernaryTree TernaryTree deriving (Show, Eq, Ord)


--Part One
charToInt::Char->Int
charToInt '0' = 0
charToInt '1' = 1
charToInt '2' = 2
charToInt '3' = 3
charToInt '4' = 4
charToInt '5' = 5
charToInt '6' = 6
charToInt '7' = 7
charToInt '8' = 8
charToInt '9' = 9
charToInt _   = 0


--Part Two
insertNode::TernaryTree->[Char]->TernaryTree

learnLevel [] = 0
learnLevel (x:xs) = if x == '.' then 1 + learnLevel xs else learnLevel xs

takeVersion [] = []
takeVersion (x:xs) = if x == '.' then [charToInt (head xs)] ++ takeVersion xs  else takeVersion xs

insertNode Empty xs = (Node xs Empty Empty Empty)
insertNode (Node t left mid right) xs = if ((takeVersion xs) !! (learnLevel t)) == 1
    then (Node t (insertNode left xs) mid right)
    else if ((takeVersion xs) !! (learnLevel t)) == 2
    then (Node t left (insertNode mid xs) right)
    else (Node t left mid (insertNode right xs))

--Part Three
totalNodes::TernaryTree->Int
totalNodes Empty = 0
totalNodes (Node t left mid right) = totalNodes left + totalNodes mid + totalNodes right + 1

--Part Four
height::TernaryTree->Int
height Empty = 0
height (Node t left mid right) = if (height left) > (height mid) && (height left) > (height right)
                                 then (height left) + 1
                                 else if (height right) > (height mid)
                                 then (height right) + 1
                                 else
                                 (height mid) + 1

--Part Five
levelcount::TernaryTree->Int->Int
learnVersion [] = 0
learnVersion (x:xs) = if x == '.' then 100 + learnVersion xs else learnVersion xs

levelcount Empty _ = 0
levelcount (Node t left mid right) x = if (learnVersion t) /= 100*x
    then levelcount left x + levelcount mid x + levelcount right x
    else
    	1 + levelcount left x + levelcount mid x + levelcount right x
{-I used 100 because it was helpful when I trace my code-}


--Part Six
findNode::TernaryTree->[Char]->TernaryTree
findNode Empty _ = NodeNotFound
findNode (Node t left mid right) xs = if xs == t then (Node t left mid right)
    else if ((takeVersion xs) !! (learnLevel t)) == 1 then findNode left xs
    else if ((takeVersion xs) !! (learnLevel t)) == 2 then findNode mid xs
    else findNode right xs