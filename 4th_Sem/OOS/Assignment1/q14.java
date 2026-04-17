interface Shape
{
        double area();
        void draw();
        void rotate();
        void move(int dx, int dy);
        void printDetails();
}

class Circle implements Shape
{
        private int x;
        private int y;
        private int radius;

        Circle(int x, int y, int radius)
        {
                this.x = x;
                this.y = y;
                this.radius = radius;
        }

        public double area()
        {
                return Math.PI * radius * radius;
        }

        public void draw()
        {
                System.out.println("Draw implemented for draw");
        }

        public void rotate()
        {
                System.out.println("Rotated");
        }

        public void move(int dx, int dy)
        {
                x += dx;
                y += dy;
        }

        public void printDetails()
        {
                System.out.println("Circle -> Center: (" + x + ", " + y + "), Radius: " + radius + ", Area: " + area());
        }
}

class Rectangle implements Shape
{
        private int x;
        private int y;
        private int length;
        private int width;

        Rectangle(int x, int y, int length, int width)
        {
                this.x = x;
                this.y = y;
                this.length = length;
                this.width = width;
        }

        public double area()
        {
                return length * width;
        }

        public void draw()
        {
                System.out.println("Draw implemented for draw");
        }

        public void rotate()
        {
                System.out.println("Rotated");
        }

        public void move(int dx, int dy)
        {
                x += dx;
                y += dy;
        }

        public void printDetails()
        {
                System.out.println("Rectangle -> Position: (" + x + ", " + y + "), Length: " + length + ", Width: " + width + ", Area: " + area());
        }
}
class Main14
{
        public static void main(String[] args)
        {
                Circle c1 = new Circle(0, 0, 5);
                Circle c2 = new Circle(10, 10, 3);

                Rectangle r1 = new Rectangle(0, 0, 4, 6);
                Rectangle r2 = new Rectangle(5, 5, 3, 7);
                Rectangle r3 = new Rectangle(2, 8, 6, 2);

                System.out.println("Before Moving:");
                c1.printDetails();
                c2.printDetails();
                r1.printDetails();
                r2.printDetails();
                r3.printDetails();

                c1.move(2, 3);
                c2.move(-1, 4);
                r1.move(5, 5);
                r2.move(1, 1);
                r3.move(-2, -2);

                System.out.println("After Moving:");
                c1.printDetails();
                c2.printDetails();
                r1.printDetails();
                r2.printDetails();
                r3.printDetails();
        }
}
		
