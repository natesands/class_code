DROP TABLE `db1`.`Students`;

DROP TABLE db1.Courses;

DROP TABLE db1.Classes;

CREATE TABLE db1.Students
(studentID INT UNSIGNED,
PRIMARY KEY (studentID),
firstName varchar (255),
lastName varchar (255),
email varchar (255),
sex ENUM ('M', 'F'));

CREATE TABLE db1.Courses (courseID INT UNSIGNED NOT NULL,
PRIMARY KEY (courseID),
courseTitle varchar(255),
department varchar(255));

CREATE TABLE db1.Classes (courseID INT UNSIGNED NOT NULL,
studentID INT UNSIGNED NOT NULL,
section INT UNSIGNED NOT NULL,
year INT UNSIGNED,
semester ENUM('FALL','SPRING','SUMMER'),
grade ENUM('A','B','C','D','F', 'W'),
PRIMARY KEY (courseID, studentID, section))
