/*
Nathaniel J. Sands
CSc 22100
CCNY Spring 2020
Exercise 2
03/26/20
*/

package Proj2;

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


/* MYPOINT */
interface MyPoint {
  /* methods implemented in MyShape */
  double getX();
  double getY();
  void setX(double x);
  void setY(double y);
  /* Static Methods */
  /* return (x,y) coordinates of shape */
  static double X(MyShape shape) {
    return shape.getX();
  }
  static double Y(MyShape shape) {
    return shape.getY();
  }
  /* set (x,y) coordinates of shape */ 
  static void setPoint(MyShape shape,double x, double y) { 
    shape.setX(x);
    shape.setY(y);
  }
  /* shift shape's center to new (x,y) */
  static void moveTo(MyShape shape, double new_x, double new_y) {
    setPoint(shape, new_x, new_y);
  }
  /* determine distance from center of shape to point
     (x,y) */
  static double distanceTo(MyShape shape, double x, double y) {
    return Math.sqrt(Math.pow(shape.getX() - x ,2) +
                     Math.pow(shape.getY() - y ,2));
  }
  /* determine distance between centers of two shapes.
     Used in MyShapePosition. */
  static double distance(MyShape shape1, MyShape shape2) {
    return distanceTo(shape1, shape2.getX(), shape2.getY());
  }
}

/* MYSHAPEPOSITION */
interface MyShapePosition extends MyPoint {
  /* all shape classes must implement */
  MyRectangle getMyBoundingBox();
  /* static method to detect overlap of shape bounding boxes */
  static boolean doOverlap(MyShape shape1, MyShape shape2){
    MyRectangle box1 = shape1.getMyBoundingBox();
    MyRectangle box2 = shape2.getMyBoundingBox();
    dx = Math.abs(box1.getX()-box2.getX());
    dy = Math.abs(box2.getY()-box2.getY());
    if (dx <= (.5*(box1.getW()+box2.getW())) &&
        dy <= (.5*(box1.getH()+box2.getH())))
      return true;
    else return false;  
  }
}

/* MYSHAPE */
abstract class MyShape implements MyShapePosition {
  private double x, y;
  private MyColor c;
  
  MyShape(double x, double y, MyColor c) {
    this.x = x;
    this.y = y;
    this.c = c;
  }

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

/* MYRECTANGLE */
class MyRectangle extends MyShape {
  private double w, h;
  
  MyRectangle(double centerX, double centerY, double w, double h) {
    super(centerX, centerY);
    this.w = w;
    this.h = h;
  }
    public double area() { return w * h; }
    public MyRectangle getMyBoundingBox() {
      MyRectangle rec = new MyRectangle(getX(), getY(), w, h);
      return rec;
    }
    public double getW() { return w; }
    public double getH() { return h; }
}

/* MYLINE */
class MyLine extends MyShape {
  private double x2, y2;
  private double linewidth = 2.0;
  
  MyLine(double x1, double y1, double x2, double y2) {
    super(x1,y1);
    this.x2 = x2; this.y2 = y2;
  }

  public MyRectangle getMyBoundingBox() {
    return new MyRectangle(.5 * (getX() + x2), .5 * (getY() + y2), x2 - getX(), y2 - getY());
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

/* VERTEX  */
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
/* MYPOLYGON */
class MyPolygon extends MyShape {
    private int N; // number of sides
    private double r;
    private double[] xPoints;
    private double[] yPoints;
    private MyColor outlineColor = BLACK;
    private double linewidth = 2.0;

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
    public MyRectangle getMyBoundingBox() {
      return MyRectangle(getX(), getY(), 2*r, 2*r);
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

/* MYOVAL */
class MyOval extends MyShape {
  private double w;
  private double h;
  private MyColor outlineColor = BLACK;
  private double linewidth = 2.0;

  MyOval(double x, double y, double w, 
         double h, MyColor fill) {
    super(x, y, fill);
    this.w = w;
    this.h = h;
  }
  public void draw(GraphicsContext gc) {
      gc.setFill(getColor().getRGB());
      gc.fillOval(getX()-.5*w, getY()-.5*h, w, h);
      gc.setLineWidth(linewidth);
      gc.setStroke(outlineColor.getRGB());
      gc.strokeOval(getX()-.5*w, getY()-.5*h, w, h );
  }
  public String toString() {
      return String.format("Oval with width %.2f, height %.2f, perimeter %.2f, and" +
              "area %.2f.", w, h, getPerimeter(), getArea());
  }
  public double getArea() {
      return Math.PI*.5*w*.5*h;
  }
  public double getPerimeter(){
    // uses Ramanujan's approximation
    double a = .5*w;
    double b = .5*h;
      return Math.PI*(3*(a+b)-Math.sqrt((3*a+b)*(a+3*b)))
  }
  public MyRectangle getMyBoundingBox() {
    return MyRectangle(getX(), getY(), w, h);
  }
  
}

/* MYCIRCLE */
class MyCircle extends MyOval {
  private double r;
  private MyColor outlineColor = BLACK;
  private double linewidth = 2.0;
  
  MyCircle(double x, double y, double r, MyColor fill) {
      super(x, y, 2*r, 2*r, fill);
      this.r = r;
  }

  public String toString() {
      return String.format("Circle with radius %.2f, circumference %.2f, and" +
              "area %.2f.", r, getPerimeter(), getArea());
  }
  public double getArea() {
      return Math.PI * Math.pow(r,2);
  }
  public double getPerimeter(){
      return 2 * Math.PI * r;
  }
}

class intTest {
  public static void main(String [] args) {
    var r1 = new MyRectangle(80,90,7,8);
    var r2 = new MyRectangle(10,10,9,10);
    if (MyShapePosition.doOverlap(r1, r2)) 
      System.out.println("YES!");
    else System.out.println("NO!");
    System.out.println(r1.area());
    System.out.println("x: " + r1.getX() + ", y: " + r1.getY());
    MyPoint.setPoint(r1,50,10);
    MyPoint.moveTo(r1, 10, 0);
    System.out.println("x: " + r1.getX() + ", y: " + r1.getY());
    var l = new MyLine(1, 2, 3, 4);
    MyRectangle lbb = l.getMyBoundingBox();
    String s = String.format("x: %.2f, y: %.2f, w: %.2f, h: %.2f",
        lbb.getX(), lbb.getY(), lbb.getH(), lbb.getW());
    System.out.println(s);
    System.out.println("r1's center is: (" + MyPoint.X(r1) + ", " 
      + MyPoint.Y(r1) + ")");
    System.out.println("r2's center is: (" + MyPoint.X(r2) + ", " 
      + MyPoint.Y(r2) + ")");
    System.out.println("d(r1,r2)= " + MyPoint.distance(r1,r2));
  }
}


