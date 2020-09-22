LOAD DATA INFILE '/Users/ironchefnate/Library/Mobile Documents/com~apple~CloudDocs/Documents/CityCollege/CSC22100/MySQLTest/src/com/example/mysqltest/students.csv'
INTO TABLE db1.Students
  FIELDS TERMINATED BY ',' ENCLOSED BY '"'
  LINES TERMINATED BY '\n'
  IGNORE 1 LINES;
  Error Code: 1290. The MySQL server is running with the --secure-file-priv option so it cannot execute this statement
