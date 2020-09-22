CREATE TABLE db1.Students (student_ID INT UNSIGNED NOT NULL AUTO_INCREMENT,
PRIMARY KEY (student_ID),
firstName varchar (255),
lastName varchar (255),
email varchar (255),
sex ENUM ('M', 'F'));
