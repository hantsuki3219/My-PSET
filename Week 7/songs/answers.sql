-- 1.sql, ลิสต์เพลงทั้งหมด 
SELECT name FROM songs;

-- 2.sql, ลิสต์เพลงทั้งหมด โดยเรียงตาม tempo จากน้อยไปมาก
SELECT name FROM songs ORDER BY tempo;

-- 3.sql, ลิสต์ top 5 เพลงที่ยาวที่สุด จากมากไปน้อย
SELECT name FROM songs ORDER BY duration_ms DESC LIMIT 5;

-- 4.sql, ลิสต์เพลงที่มี danceability, energy, และ valence มากกว่า 0.75
SELECT name FROM songs WHERE danceability > 0.75 AND energy > 0.75 and valence > 0.75;

-- 5.sql, หาค่าเฉลี่ยของ energy ของเพลงทั้งหมด
SELECT AVG(energy) FROM songs;

-- 6.sql, ลิสต์เพลงทั้งหมดจากศิลปินคนเดียว (คนไหนก็ได้ซักคน)
SELECT name FROM songs WHERE artist_id = (SELECT id FROM artists WHERE name = 'Artist Name');

-- 7.sql, หาค่าเฉลี่ยของ energy ของเพลงจากศิลปินคนเดียว (คนไหนก็ได้ซักคน)
SELECT AVG(energy) FROM songs WHERE artist_id = (SELECT id FROM artists WHERE name = 'Artist Name');

-- 8.sql, ลิสต์เพลงทั้งหมดที่มีการ featuring ศิลปินคนอื่น
SELECT name FROM songs WHERE name LIKE '%feat.%';