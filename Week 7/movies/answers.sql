-- 1.sql, ลิสต์ชื่อหนังทั้งหมดที่ฉายในปี 2008
SELECT title FROM movies WHERE year = 2008;

-- 2.sql, หาปีเกิดของใครซักคนจากชื่อ
SELECT birth FROM people WHERE name = 'Name';

-- 3.sql, ลิสต์ชื่อหนังทั้งหมดที่ฉายตั้งแต่ปี 2008 เป็นต้นมา เรียงตามตัวอักษร
SELECT title FROM movies WHERE year >= 2018 ORDER BY title ASC;

-- 4.sql, หาเลขจำนวนของหนังทั้งหมดที่ได้ rating 10.0
SELECT COUNT(rating) FROM ratings WHERE rating = 10.0;

-- 5.sql, ลิสต์ชื่อหนังและปีที่ฉายทั้งหมดที่เป็น Harry Potter เรียงตามปีที่ฉาย
SELECT title, year FROM movies WHERE title LIKE 'Harry Potter%' ORDER BY year ASC;

-- 6.sql, หาค่าเฉลี่ยของ rating ของหนังทั้งหมดในปี 2012
SELECT AVG(rating)
FROM movies
JOIN ratings ON movies.id = ratings.movie_id
WHERE year = 2012;

-- 7.sql, ลิสต์ชื่อหนังและ rating ทั้งหมดที่ฉายในปี 2010 เรียงตาม rating จากมากไปน้อย ถ้า rating เท่ากัน ให้เรียงตามตัวอักษรแทน
SELECT title, rating
FROM movies
JOIN ratings ON movies.id = ratings.movie_id
WHERE year = 2010
ORDER BY rating DESC, title ASC;

-- 8.sql, ลิสต์ชื่อคนที่ร่วมแสดง (starred) ใน Toy Story ทั้งหมด
SELECT name
FROM people
JOIN stars ON stars.person_id = people.id
JOIN movies ON movies.id = stars.movie_id
WHERE movies.title = 'Toy Story';

-- 9.sql, ลิสต์ชื่อคนที่ร่วมแสดง (starred) หนังทั้งหมดในปี 2004 เรียงตามปีเกิด
SELECT DISTINCT name
FROM people
JOIN stars ON stars.person_id = people.id
JOIN movies ON movies.id = stars.movie_id
WHERE movies.year = 2004
ORDER BY people.birth ASC;

-- 10.sql, ลิสต์ชื่อผู้กำกับหนังทั้งหมดที่มีผลงานหนังที่ได้ rating อย่างน้อย 9.0
SELECT DISTINCT name
FROM people
JOIN directors ON directors.person_id = people.id
JOIN ratings ON ratings.movie_id = directors.movie_id
WHERE rating >= 9.0

-- 11.sql, ลิสต์ 5 ชื่อหนังที่มี rating สูงที่สุดที่มี Chadwick Boseman ร่วมแสดงด้วย เรียงตาม rating จากมากไปน้อย
SELECT title
FROM movies
JOIN ratings ON movies.id = ratings.movie_id
JOIN stars ON stars.movie_id = movies.id
JOIN people ON stars.person_id = people.id
WHERE people.name = 'Chadwick Boseman'
ORDER BY ratings.rating DESC
LIMIT 5;

-- 12.sql, ลิสต์ชื่อหนังทั้งหมดที่มี Johnny Depp และ Helena Bonham Carter ร่วมแสดงด้วยกัน
-- version 1
SELECT title
FROM movies
JOIN stars ON stars.movie_id = movies.id
JOIN people ON people.id = stars.person_id
WHERE people.name = 'Johnny Depp'
AND title IN
(
    SELECT title
    FROM movies
    JOIN stars ON stars.movie_id = movies.id
    JOIN people ON people.id = stars.person_id
    WHERE people.name = 'Helena Bonham Carter'
);

-- version 2
SELECT movies.title
FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE people.name = "Johnny Depp"
INTERSECT
SELECT movies.title
FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE people.name = "Helena Bonham Carter";

-- version 3
SELECT title
FROM movies
JOIN stars ON stars.movie_id = movies.id
JOIN people ON people.id = stars.person_id
WHERE people.name IN ('Johnny Depp', 'Helena Bonham Carter')
GROUP BY title
HAVING COUNT(DISTINCT people.name) = 2;

--  13.sql, ลิสต์ชื่อคนทั้งหมดที่ร่วมแสดงในหนังที่มี Kevin Bacon ร่วมแสดงด้วย
SELECT DISTINCT(name) FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE movies.id IN
(
    SELECT DISTINCT(movies.id) FROM movies
    JOIN stars ON movies.id = stars.movie_id
    JOIN people ON people.id = stars.person_id
    WHERE people.name = "Kevin Bacon"
    AND people.birth = 1958
) 
AND people.name != "Kevin Bacon";
