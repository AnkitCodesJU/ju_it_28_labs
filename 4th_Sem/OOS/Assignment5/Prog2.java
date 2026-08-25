interface Shape {
    void draw();
}

class Circle implements Shape {
    public void draw() {
        System.out.println("Circle");
    }
}

class Rectangle implements Shape {
    public void draw() {
        System.out.println("Rectangle");
    }
}

abstract class ShapeDecorator implements Shape {
    protected Shape shp;

    public ShapeDecorator(Shape shp) {
        this.shp = shp;
    }

    public void draw() {
        shp.draw();
    }
}

class RedShapeDecorator extends ShapeDecorator {
    public RedShapeDecorator(Shape shp) {
        super(shp);
    }

    public void draw() {
        shp.draw();
        setRedBorder();
    }

    private void setRedBorder() {
        System.out.println("Border Color: Red");
    }
}

class Prog2 {
    public static void main(String[] arg) {
        Shape cir = new Circle();
        Shape redC = new RedShapeDecorator(new Circle());
        Shape redR = new RedShapeDecorator(new Rectangle());
        cir.draw();
        redC.draw();
        redR.draw();
    }
}