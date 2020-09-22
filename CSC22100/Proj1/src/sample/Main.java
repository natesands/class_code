/*
Nathaniel J. Sands
CSc 22100
CCNY Spring 2020
Exercise 1
03/05/20
 */



package sample;

import javafx.application.Application;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.stage.Stage;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;
import java.lang.Math;


/* global vars that relate to size of canvas */
class Globals {
    final static double MAX_X = 900.0;
    final static double MAX_Y = 500.0;
    final static double CENTER_X = MAX_X / 2;
    final static double CENTER_Y = MAX_Y / 2;
}

/* abstract shape class */
abstract class MyShape {
    // center point/start point
    private double x, y;
    // fill color
    private MyColor c;

    // constructors
    MyShape() {
        c = MyColor.BLACK;
        x = Globals.CENTER_X;
        y = Globals.CENTER_Y;
    }
    MyShape(double x, double y) {
        c = MyColor.BLACK;
        this.x = x; this.y = y;
    }
    MyShape(double x, double y, MyColor c) {
        this.c = c;
        this.x = x; this.y = y;
    }

    // methods
    public double getX() { return x; }
    public double getY() { return y; }
    public MyColor getColor() { return c; }

    public void setX(double x) { this.x = x; }
    public void setY(double y) { this.y = y; }
    public void setColor(MyColor c) { this.c = c; }

    // required implementations
    public abstract String toString();
    public abstract void draw(GraphicsContext gc);
}

/* colors */
enum MyColor { 
    /* RED(255,0,0), GREEN(0,255,0), BLUE(0,0,255), */
    BLACK(0,0, 0), /*WHITE(255,255,255), YELLOW(255,255,0),*/
    PLUM(221,160,221), MAGENTA(255,0,255),
    MEDIUMTURQUOISE(72,209, 204), ORANGE(255,165,0),
    RED1 ( 255,0,0),DEEPPINK2 ( 255,0,95),DEEPPINK1 ( 255,0,135),
    MAGENTA2 ( 255,0,215),
    MAGENTA1 ( 255,0,255),ORANGERED1 ( 255,95,0),
    INDIANRED1 ( 255,95,95),
    HOTPINK ( 255,95,175),
    MEDIUMORCHID1 ( 255,95,255),DARKORANGE ( 255,135,0),
    SALMON1 ( 255,135,95),LIGHTCORAL ( 255,135,135),
    PALEVIOLETRED1 ( 255,135,175),ORCHID2 ( 255,135,215),
    ORCHID1 ( 255,135,255),ORANGE1 ( 255,175,0),
    SANDYBROWN ( 255,175,95),LIGHTSALMON1 ( 255,175,135),
    LIGHTPINK1 ( 255,175,175),PINK1 ( 255,175,215),
    PLUM1 ( 255,175,255),GOLD1 ( 255,215,0),
    LIGHTGOLDENROD2 ( 255,215,95),NAVAJOWHITE1 ( 255,215,175),
    MISTYROSE1 ( 255,215,215),THISTLE1 ( 255,215,255),
    YELLOW1 ( 255,255,0),LIGHTGOLDENROD1 ( 255,255,95),
    KHAKI1 ( 255,255,135),WHEAT1 ( 255,255,175),
    CORNSILK1 ( 255,255,215),GREY100 ( 255,255,255),
    GREY3 ( 8,8,8),GREY7 ( 18,18,18),
    GREY11 ( 28,28,28),GREY15 ( 38,38,38),
    GREY19 ( 48,48,48),GREY23 ( 58,58,58),GREY27 ( 68,68,68),
    GREY30 ( 78,78,78),GREY35 ( 88,88,88),GREY39 ( 98,98,98),
    GREY42 ( 108,108,108),GREY46 ( 118,118,118),
    GREY50 ( 128,128,128),GREY54 ( 138,138,138),
    GREY58 ( 148,148,148),GREY62 ( 158,158,158),
    GREY66 ( 168,168,168),GREY70 ( 178,178,178),
    GREY74 ( 188,188,188),GREY78 ( 198,198,198),
    GREY82 ( 208,208,208);

    private int red, green, blue;

    MyColor(int red, int green, int blue) {
        this.red = red;
        this.green = green;
        this.blue = blue;
    }
    public Color getRGB() {return Color.rgb(red, green, blue);}
}

/* auxiliary class for MyPolygon */
class Vertex {
    private double x;
    private double y;

    Vertex(double x, double y) {
        this.x = x;
        this.y = y;
    }
    public double getX() { return x; }
    public double getY() { return y; }
    // computes rotation of point (x,y) about the origin
    public double rotateXBy(int n, double radians) {
        return x * Math.cos(n*radians) - y * Math.sin(n*radians);
    }
    public double rotateYBy(int n, double radians) {
        return x * Math.sin(n*radians) + y * Math.cos(n*radians);
    }
}
/* n-gon with radius r */
class MyPolygon extends MyShape {
    private int N;
    private double r;
    private double[] xPoints;
    private double[] yPoints;
    private MyColor outlineColor; // outline color
    private double linewidth = 2.0;

    // constructors
    MyPolygon(int N, double r) {
        super();
        this.N = N;
        this.r = r;
        outlineColor = MyColor.BLACK;
        calculateVertices();
    }
    MyPolygon(double x, double y, MyColor fill,
              MyColor outline, int N, double r){
        super(x,y,fill);
        this.N = N;
        this.r = r;
        outlineColor = outline;
        calculateVertices();
    }
    // fill xPoints, yPoints w/ vertices
    public void calculateVertices() {
        double theta = 2 * Math.PI / N;
        Vertex v = new Vertex(0, r);
        xPoints = new double[N];
        yPoints = new double[N];
        for (int n = 0; n < N; n++) {
            xPoints[n] = v.rotateXBy(n, theta) + getX();
            yPoints[n] = v.rotateYBy(n, theta) + getY();
        }
    }

    // calculate area, perimeter, internal angle,
    // length of side
    public double getArea() {
        return N * Math.pow(r,2) * Math.sin( Math.PI / N) *
                Math.cos(Math.PI / N);
    }
    public double getPerimeter() {
        return 2*N*Math.sin(Math.PI/N)*r;
    }
    public double getAngle() {
        return Math.toDegrees(Math.PI * (N-2) / N);
    }
    public double getSide() {
        return 2 * r * Math.sin(Math.PI / N);
    }

    public String toString() {
        return String.format("Polygon with %d sides, length %.2f, interior angle %.2f," +
                "perimeter %.2f, area %.2f", N, getSide(), getAngle(), getPerimeter(),
                getArea());
    }


    public void draw(GraphicsContext gc) {
        gc.setFill(getColor().getRGB());
        gc.fillPolygon(xPoints, yPoints, N);
        gc.setLineWidth(linewidth);
        gc.setStroke(outlineColor.getRGB());
        gc.strokePolygon(xPoints, yPoints, N);
    }
}
/*
 Lines are treated as vectors with their 'tip' located at the (x2,y2)
 coordinate stored in MyLine, and their 'tail' at the point (x,y) stored in
 the superclass MyShape.  The method getAngle() returns the angle between the
 tip and the horizontal x-axis across the top of the frame.
 */
class MyLine extends MyShape {
    private double x2, y2;
    private double linewidth = 2.0;

    // constructors
    MyLine(double x1, double y1, double x2, double y2) {
        super(x1, y1);
        this.x2 = x2; this.y2 = y2;
    }
    MyLine(double x1, double y1, double x2, double y2, MyColor c) {
        super(x1, y1, c);
        this.x2 = x2; this.y2 = y2;
    }
    MyLine(double x1, double y1, double x2, double y2, double linewidth) {
        super(x1, y1);
        this.x2 = x2; this.y2 = y2;
        this.linewidth = linewidth;
    }
    MyLine(double x1, double y1, double x2, double y2, MyColor c, double linewidth) {
        super(x1, y1, c);
        this.x2 = x2; this.y2 = y2;
    }

    // draws a line between (x, y) and (x2, y2)
    public void draw(GraphicsContext gc) {
        gc.setLineWidth(linewidth);
        gc.setStroke(getColor().getRGB());
        gc.beginPath();
        gc.moveTo(getX(), getY());
        gc.appendSVGPath("L " + x2 + "," + y2);
        gc.closePath();
        gc.stroke();
    }
    public double getLength() {
        double dx = getX() - x2;
        double dy = getY() - y2;
        return Math.sqrt( Math.pow(dx,2) + Math.pow(dy,2));
    }
    public double getAngle() {
        double dx = x2 - getX();
        double dy = y2 - getY();
        double angleInRads = Math.atan2( dy, dx);
        return Math.toDegrees(angleInRads);
    }
    public String toString() {
        return String.format("Line of length %.2f  making angle %.2f " +
                "with horizontal axis.", getLength(), getAngle());
    }
}
/* circles with radius r */
class MyCircle extends MyShape {
    private double r;
    private MyColor outlineColor; // outline color
    private double linewidth = 2.0;
    //constructors
    MyCircle() {
        super();
        r = Globals.MAX_Y / 4;
        outlineColor = MyColor.BLACK;
    }
    MyCircle(double r) {
        super();
        this.r = r;
        outlineColor = MyColor.BLACK;
    }
    MyCircle(double x, double y, double r) {
        super(x,y);
        this.r = r;
        outlineColor = MyColor.BLACK;
    }
    MyCircle(double x, double y, MyColor fill,
             MyColor outline, double r) {
        super(x, y, fill);
        this.r = r;
        outlineColor = outline;
    }
    // required draw and toString implementations
    public void draw(GraphicsContext gc) {
        gc.setFill(getColor().getRGB());
        gc.fillOval(getX()-r, getY()-r, 2*r, 2*r);
        gc.setLineWidth(linewidth);
        gc.setStroke(outlineColor.getRGB());
        gc.strokeOval(getX()-r, getY()-r, 2*r, 2*r);
    }
    public String toString() {
        return String.format("Circle with radius %.2f, circumference %.2f, and" +
                "area %.2f.", r, getPerimeter(), getArea());
    }

    // calculate area and circumference
    public double getArea() {
        return Math.PI * Math.pow(r,2);
    }
    public double getPerimeter(){
        return 2 * Math.PI * r;
    }


}
public class Main extends Application {

    @Override
    public void start(Stage stage) {

        stage.setTitle("CSc 221 Exercise 1");
        Group root = new Group();
        Canvas canvas = new Canvas(Globals.MAX_X, Globals.MAX_Y);
        GraphicsContext gc = canvas.getGraphicsContext2D();

        // Draw sequence of circles and inscribed hexagons
        double radius = Globals.MAX_Y / 2.5;
        int index = 1;
        for (MyColor color : MyColor.values()) {
            if (index % 2 == 0) {
                radius = radius * Math.cos(Math.PI / 6.0);
                MyCircle circle = new MyCircle(Globals.CENTER_X,
                    Globals.CENTER_Y, color, MyColor.BLACK, radius);
                circle.draw(gc);
            }
            else {
                MyPolygon poly = new MyPolygon(Globals.CENTER_X, Globals.CENTER_Y,
                        color, MyColor.BLACK, 6, radius);
                poly.draw(gc);
            }
            index++;
        }

        // Draw lines connecting the corners of the canvas.
        MyLine cross1 = new MyLine(0.0, 0.0,Globals.MAX_X,Globals.MAX_Y, 3.0);
        cross1.draw(gc);
        MyLine cross2 = new MyLine(Globals.MAX_X,0.0, 0.0, Globals.MAX_Y, 3);
        cross2.draw(gc);

        root.getChildren().add(canvas);
        stage.setScene(new Scene(root));
        stage.show();

    }


    public static void main(String[] args) {
        launch(args);
    }
}
