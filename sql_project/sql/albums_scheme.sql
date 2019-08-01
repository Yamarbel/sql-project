CREATE DATABASE IF NOT EXISTS albums_scheme;

USE albums_scheme;

DROP VIEW IF EXISTS SONGS_VIEW;
DROP TABLE IF EXISTS albums;
DROP TABLE IF EXISTS technicians;
DROP TABLE IF EXISTS songs;
DROP TABLE IF EXISTS musician_instruments;
DROP TABLE IF EXISTS producers;
DROP TABLE IF EXISTS musicians;
DROP TABLE IF EXISTS instruments_song;
DROP TABLE IF EXISTS instruments;
DROP TABLE IF EXISTS albums_songs;
DROP TABLE IF EXISTS album_instruments;



CREATE TABLE producers (
  producer_id int(11) NOT NULL,
  producer_name varchar(50) DEFAULT NULL,
  producer_phone varchar(10) DEFAULT NULL,
  join_date date DEFAULT NULL,
  PRIMARY KEY (producer_id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
INSERT INTO producers VALUES (1,'Kobi Farhi','0544898877','2018-01-01'),(2,'BIBI','0544898877','2018-02-01'),(4,'Jonny Nexwil','0544898877','2018-04-06'),(5,'Gal Toren','0544898877','2018-01-07'),(6,'Tuka Yaakov','0544898877','2018-12-01'),(7,'Asaf Flotz','0544898877','2018-01-11'),(8,'Kushi Sumbo','0544898877','2018-06-01'),(9,'Rahel Emano','0544898877','2018-01-08'),(10,'Y Y','0544898877','2018-07-01');

CREATE TABLE instruments (
  instrument_id int(11) NOT NULL,
  instrument_creator varchar(50) DEFAULT NULL,
  instrument_type varchar(50) DEFAULT NULL,
  PRIMARY KEY (instrument_id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
INSERT INTO instruments VALUES (1,'Swissa','guitar'),(2,'Ori Shohat','drums'),(3,'Fishi','darbuka'),(4,'Dr dry','halilit'),(5,'Swissa','tof miriam');

CREATE TABLE musicians (
  musician_id int(11) NOT NULL,
  musician_name varchar(50) DEFAULT NULL,
  musician_address varchar(50) DEFAULT NULL,
  musician_phone varchar(10) DEFAULT NULL,
  PRIMARY KEY (musician_id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
INSERT INTO musicians VALUES (1,'Ori Kfir','hagolan 3','0545810108'),(2,'Guy Chriqui','rakevet 11','0545811008'),(3,'Orisan Santo','hatzil 8','0545410108'),(4,'Yam Arbel','tinshemet 12','0545813438'),(5,'Lev Ari','hara 23','0545453108'),(6,'Shira Star','shtand 9','0547560108'),(7,'Yaron Mintz','ben yehuda 3','0547500108'),(8,'Dekel Mor','piza 4','0547560104'),(9,'Papush Bitran','truman 3','0547500108'),(10,'Gal Levi','florentin 7','0547560104');

CREATE TABLE technicians (
  technician_id int(11) NOT NULL,
  technician_name varchar(50) DEFAULT NULL,
  PRIMARY KEY (technician_id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
INSERT INTO technicians VALUES (1,'yossi gispan'),(2,'dudu topaz'),(3,'margalit zanani'),(4,'zohar argov'),(5,'tupac shakur'),(6,'roni levy'),(7,'lionel messi'),(8,'toto tamuz'),(9,'ishay levi'),(10,'jose mourinho');








CREATE TABLE album_instruments (
  id int(11) NOT NULL,
  album_id varchar(50) DEFAULT NULL,
  instument_id varchar(10) DEFAULT NULL,
  PRIMARY KEY (id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
INSERT INTO album_instruments VALUES (1,'1','1'),(2,'1','3'),(3,'1','2'),(4,'4','1'),(5,'4','5'),(6,'3','1'),(7,'3','4'),(8,'5','1');



CREATE TABLE albums (
  album_id int(10) unsigned NOT NULL,
  album_name varchar(50) DEFAULT NULL,
  start_day date DEFAULT NULL,
  end_day date DEFAULT NULL,
  musician_id int(11) DEFAULT NULL,
  producer_id int(11) DEFAULT NULL,
  songs_count int(11) DEFAULT NULL,
  PRIMARY KEY (album_id),
  KEY producer_id (producer_id),
  KEY musician_id (musician_id),
  CONSTRAINT albums_ibfk_1 FOREIGN KEY (producer_id) REFERENCES producers (producer_id),
  CONSTRAINT albums_ibfk_2 FOREIGN KEY (musician_id) REFERENCES musicians (musician_id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
INSERT INTO albums VALUES (1,'Mabool','2012-07-01','2012-12-01',1,1,3),(2,'El nora alila','2015-01-01','2016-01-01',1,2,3),(3,'dead massieh','2013-10-15','2014-09-01',1,5,3),(4,'Hombre lobo','2018-08-01','2018-12-29',1,6,3),(5,'Tavio birot','2016-07-01','2017-07-01',7,8,3),(6,'Styles','1998-07-01','2000-07-01',8,9,2),(7,'Play','1991-02-12','1991-11-03',9,10,3),(8,'13','2013-01-06','2013-07-09',10,4,2),(9,'zohar','2014-07-01','2014-12-01',1,2,2),(10,'sababa','2017-07-01','2017-12-21',8,2,2);




CREATE TABLE albums_songs (
  id int(10) unsigned NOT NULL,
  song_id int(11) DEFAULT NULL,
  album_id int(11) DEFAULT NULL,
  musician_id int(11) DEFAULT NULL,
  PRIMARY KEY (id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
INSERT INTO albums_songs VALUES (1,1,1,1),(2,1,1,2),(3,2,1,1),(4,3,1,1),(5,4,2,2),(6,5,2,2),(7,5,2,2),(8,6,3,3),(9,6,3,1),(10,7,3,3),(11,8,4,4),(12,9,4,4),(13,9,4,7),(14,10,5,5),(15,11,5,5),(16,12,5,5),(17,12,5,5),(18,13,6,6),(19,14,6,6),(20,15,6,6),(21,16,7,7),(22,17,7,7),(23,18,8,8),(24,19,8,8),(25,20,9,9),(26,21,9,9),(27,22,9,9),(28,22,10,10),(29,23,10,10),(30,24,10,10),(31,24,7,10);





CREATE TABLE instruments_song (
  id int(11) NOT NULL,
  song_id int(11) DEFAULT NULL,
  instrument_id int(11) DEFAULT NULL,
  PRIMARY KEY (id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

INSERT INTO instruments_song VALUES (1,1,1),(2,1,3),(3,5,1),(4,5,2),(5,7,1),(6,7,4),(7,8,1),(8,9,2),(9,10,1),(10,10,5);





CREATE TABLE musician_instruments (
  id int(11) NOT NULL,
  musician_id int(11) DEFAULT NULL,
  instrument_id int(11) DEFAULT NULL,
  PRIMARY KEY (id),
  KEY musician_id (musician_id),
  KEY instrument_id (instrument_id),
  CONSTRAINT musician_instruments_ibfk_1 FOREIGN KEY (musician_id) REFERENCES musicians (musician_id),
  CONSTRAINT musician_instruments_ibfk_2 FOREIGN KEY (instrument_id) REFERENCES instruments (instrument_id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
INSERT INTO musician_instruments VALUES (1,1,2),(2,1,2),(3,1,2),(4,2,2),(5,3,2),(6,4,1),(7,1,5),(8,2,2),(9,5,1);


CREATE TABLE songs (
  song_id int(11) NOT NULL,
  song_name varchar(50) DEFAULT NULL,
  song_genre varchar(10) DEFAULT NULL,
  song_length varchar(50) DEFAULT NULL,
  song_record_date date DEFAULT NULL,
  song_writer varchar(50) DEFAULT NULL,
  song_composer varchar(50) DEFAULT NULL,
  technician_id int(11) DEFAULT NULL,
  PRIMARY KEY (song_id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

INSERT INTO songs VALUES (1,'Put your namber in my phone','Metal','3','2018-04-05','Uzi Remirez','harak',1),
						 (2,'Badad','Dikaon','3:25','2017-03-15','Uzi Remirez','harak',1),
						 (3,'Yam shel dmaot','Dikaon','2:52','2013-03-12','Avram Grant','chupchik',3),
						 (4,'Yafa Sheli','Mizrahit','3:52','2012-02-02','Uzi Remirez','harak',1),
						 (5,'Haver BeMashber','Dikaon','4:22','2015-03-05','Yossi Gipan','harak',2),
						 (6,'Blue suede shoes','Country','5:33','2013-01-05','Toto Kimoto','baby shark',1),
						 (7,'My way','classic','3:22','2012-01-05','Jojo Halastra','Hazaniuk',7),
						 (8,'The gunners dream','rock','3:53','2018-04-06','Ron Kofman','natan alterman',1),
						 (9,'Frecha bemercedes','pop','4:01','2018-05-05','Uzi Remirez','harak',5),
						 (10,'The price fron Ness ziona','Dikaon','3:12','2013-02-01','Haim Yavin','harak',8),
                         (11,'Give him chance','Dikaon','3:12','2013-02-01','Haim Yavin','harak',1),
                         (12,'Taking for a fool','Dikaon','3:12','2013-02-01','Haim Yavin','harak',2),
                         (13,'Venus in tamuz','Dikaon','3:12','2013-02-01','Haim Yavin','harak',1),
                         (14,'Yalda','Dikaon','3:12','2013-02-01','Haim Yavin','harak',1),
                         (15,'Friend in a crisis','Dikaon','3:12','2013-02-01','Haim Yavin','harak',1),
                         (16,'Tuki Yossi','Dikaon','3:12','2013-02-01','Haim Yavin','harak',2),
                         (17,'Is this it','Dikaon','3:12','2013-02-01','Haim Yavin','harak',3),
                         (18,'Howlin for you','Pop','3:12','2013-02-01','Haim Yavin','harak',1),
                         (19,'Babe im gonna leave you','Dikaon','3:12','2013-02-01','Haim Yavin','harak',3),
                         (20,'Shine on you crazy diamond','Rock','3:12','2013-02-01','Haim Yavin','harak',1),
                         (21,'Yoko homo','Rock','3:12','2013-02-01','Haim Yavin','harak',3),
                         (22,'The man who sold the world','Grunge','3:12','2013-02-01','Haim Yavin','harak',5),
                         (23,'About a girl','Grunge','3:12','2013-02-01','Haim Yavin','harak',4),
                         (24,'Magic moments','Classic','3:12','2013-02-01','Haim Yavin','harak',1);
                         
                         





CREATE VIEW SONGS_VIEW AS
SELECT songs.song_id,songs.song_name, songs.song_genre, songs.song_length, songs.song_record_date, songs.song_writer, songs.song_composer,
albums.album_id, albums.album_name, albums.start_day, albums.end_day, albums.producer_id, albums.songs_count,
musicians.musician_id, musicians.musician_name, musicians.musician_address, musicians.musician_phone,
technicians.technician_id, technicians.technician_name
FROM songs 
LEFT JOIN albums_songs on songs.song_id = albums_songs.song_id
LEFT JOIN albums on albums_songs.album_id = albums.album_id
LEFT JOIN musicians on albums_songs.musician_id = musicians.musician_id
LEFT JOIN technicians on songs.technician_id = technicians.technician_id