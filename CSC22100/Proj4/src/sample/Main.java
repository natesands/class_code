package sample;

import java.sql.*;

import java.nio.file.Files;
import java.nio.file.InvalidPathException;
import java.nio.file.Paths;
import java.nio.file.Path;
import java.io.IOException;

class StmtArray {
    private String s;
    private String [] stmts;
    private Path path;

    StmtArray (String p) {
        try {
            path = Paths.get(p);
        } catch (InvalidPathException ex) {
            System.out.println("Bad path.");
            System.exit(-1);
        }
        try {
            s = Files.readString(path);
        } catch (IOException ex) {
            System.out.println("I/O Error.");
            System.exit(-1);
        }
        stmts = s.split(";");
        for (String value : stmts) System.out.println(value);
    }
    String[] getStmts() {return stmts;}
}

class  MyStmt {
    private String stmt;
    private Path path;

    MyStmt (String p) {
        try {
            path = Paths.get(p);
        } catch (InvalidPathException ex) {
            System.out.println("Bad path.");
            System.exit(-1);
        }
        try {
            stmt = Files.readString(path);
        } catch (IOException ex) {
            System.out.println("I/O Error.");
            System.exit(-1);
        }
    }
    String getStmt() { return stmt;}
}

public class MySQLTest {
    public static void main(String args[]) {
        String dbURL = "jdbc:mysql://localhost:3306/db1";
        String user = "nate";
        String password = "nsbta808";
        String timeZone = "EST";
        String connectionString = dbURL + "?user=" + user + "&password=" + password
                + "&serverTimezone=" + timeZone;
        /*String stmtPath = "/Users/ironchefnate/Library/Mobile Documents/com~apple~CloudDocs/"  +
                "Documents/CityCollege/CSC22100/MySQLTest/src/com/example/mysqltest/";*/
        String stmtPath = "/Users/nathanielsands/Documents/CityCollege/CSC22100/Proj4/src/sample/";

        // read in batch of sql statements from file
        StmtArray s = new StmtArray(stmtPath + "stmt3.sql");
        StmtArray t = new StmtArray(stmtPath + "stmt4.sql");
        String[] stmts = s.getStmts();
        String[] stmts2 = t.getStmts();


        Connection conn = null;
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection(connectionString);

            if (conn != null) {
                System.out.println("Connected to database.");
                Statement stmt = conn.createStatement();
                // add statements to batch and execute
                for (String value : stmts) stmt.addBatch(value);
                for (String value : stmts2) stmt.addBatch(value);
                stmt.executeBatch();

                MySQLTest.showColumns(conn);

                Statement stmt2 = conn.createStatement(ResultSet.TYPE_FORWARD_ONLY,
                        ResultSet.CONCUR_UPDATABLE);
                ResultSet rs = stmt2.executeQuery("SELECT COUNT(*) FROM db1.Students");
                rs.next();
                int rowCount = rs.getInt(1);
                System.out.println("rows: " + rowCount);

                MySQLTest.showValues(conn);

                //  Close the database
                conn.close();
            }

        } catch (SQLException ex) {
            System.out.println("SQLException: " + ex.getMessage());
            ex.printStackTrace();

        } catch (Exception ex) {
            System.out.println("Exception: " + ex.getMessage());
            ex.printStackTrace();
        }
    }

    public static void showValues(Connection conn)
    {
        try {
            Statement stmt = conn.createStatement();
            ResultSet rset = stmt.executeQuery("SELECT * FROM Students");
            MySQLTest.showResults("Students", rset);
        } catch (SQLException ex) {
            System.out.println("SQLException: " + ex.getMessage());
            ex.printStackTrace();
        }
    }
    public static void showColumns(Connection conn)
    {
        try {
            Statement stmt = conn.createStatement();
            ResultSet rset = stmt.executeQuery("SHOW COLUMNS FROM Students");
            MySQLTest.showResults("Students", rset);
        } catch (SQLException ex) {
            System.out.println("SQLException: " + ex.getMessage());
            ex.printStackTrace();
        }
    }

    public static void showResults(String tableName, ResultSet rSet)
    {
        try {
            ResultSetMetaData rsmd = rSet.getMetaData();
            int numColumns = rsmd.getColumnCount();
            String resultString = null;
            if (numColumns > 0)
            {
                resultString = "\nTable: " + tableName + "\n" +
                        "=======================================================\n";
                for (int colNum = 1; colNum <= numColumns; colNum++)
                    resultString += rsmd.getColumnLabel(colNum) + " ";
            }
            System.out.println(resultString);
            System.out.println(
                    "=======================================================");
            while (rSet.next()) {
                resultString = "";
                for (int colNum = 1; colNum <= numColumns; colNum++)
                {
                    String column = rSet.getString(colNum);
                    if (column != null)
                        resultString += column + " ";
                }
                System.out.println(resultString + '\n' +
                        "------------------------------------------------------------");
            }
        } catch (SQLException ex) {
            System.out.println("SQLException: " + ex.getMessage());
            ex.printStackTrace();
        }
    }
}
