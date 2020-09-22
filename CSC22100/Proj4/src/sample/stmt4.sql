SET @@GLOBAL.local_infile = 1;
INSERT INTO db1.Students
(studentID, firstName, lastName, email, sex)
VALUES (4454,'billy', 'madison', 'hoohoo@yahoo.com', 'M');
LOAD DATA INFILE '/Users/ironchefnate/Library/Mobile Documents/com~apple~CloudDocs/Documents/CityCollege/CSC22100/MySQLTest/src/com/example/mysqltest/students.csv'
INTO TABLE db1.Students
  FIELDS TERMINATED BY ',' ENCLOSED BY '"'
  LINES TERMINATED BY '\n'
  IGNORE 1 LINES
