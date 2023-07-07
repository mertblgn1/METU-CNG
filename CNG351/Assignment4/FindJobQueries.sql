-- Query 1
SELECT member_id, name, surname, tel FROM Member;

-- Query 2
SELECT group_name, creation_date FROM GroupInfo WHERE group_type = 'Unlisted' and created_by = '1333';

-- Query 3
SELECT name, surname, email
FROM Member
WHERE member_id IN (SELECT created_by FROM GroupInfo WHERE group_type = 'Standard' and creation_date > DATE'2022-01-01');

-- Query 4
SELECT title, content
FROM Post
WHERE posted_by IN (SELECT connection_member_id FROM ConnectionList WHERE
member_id = (SELECT member_id FROM Member WHERE name = 'Yeliz' AND surname = 'Yesilada'));

-- Query 5
SELECT M.name, M.surname, G.group_name, Mng.name, Mng.surname
FROM Member M
JOIN GroupInfo G ON M.member_id = G.created_by
JOIN Member Mng ON G.manager_id = Mng.member_id
WHERE M.company_id = (SELECT company_id FROM Company WHERE companyname = 'Curiosity');

-- Query 6
SELECT M.name, M.surname, COUNT(M.member_id)
FROM AssessmentTaken A1, Assessment A2, Member M
WHERE A2.name = 'Introduction to Phyton' AND A1.assessment_id = A2.assessment_id
AND A1.member_id = M.member_id
GROUP BY M.member_id, M.name, M.surname;