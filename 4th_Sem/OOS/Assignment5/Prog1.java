interface Shape {
    void draw();
}

class Circle implements Shape {
    public void draw() {
        System.out.println("Circle");
    }
}

class Square implements Shape {
    public void draw() {
        System.out.println("Square");
    }
}

class Rectangle implements Shape {
    public void draw() {
        System.out.println("Rectangle");
    }
}

class ShapeFactory {
    public Shape getShape(String typ) {
        if (typ == null) {
            return null;
        }

        if (typ.equalsIgnoreCase("CIRCLE")) {
            return new Circle();
        } else if (typ.equalsIgnoreCase("RECTANGLE")) {
            return new Rectangle();
        } else if (typ.equalsIgnoreCase("SQUARE")) {
            return new Square();
        }

        return null;
    }
}
class Prog1 {
    public static void main(String[] arg) {
        ShapeFactory fac = new ShapeFactory();

        Shape s1 = fac.getShape("CIRCLE");
        if (s1 != null)
            s1.draw();

        Shape s2 = fac.getShape("RECTANGLE");
        if (s2 != null)
            s2.draw();

        Shape s3 = fac.getShape("SQUARE");
        if (s3 != null)
            s3.draw();
    }
}