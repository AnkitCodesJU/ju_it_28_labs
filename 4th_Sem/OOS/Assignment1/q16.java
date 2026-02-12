interface Fruit
{
        boolean hasAPeel();
}

interface Vegetable
{
        boolean hasARoot();
}

class Tomato implements Fruit, Vegetable
{
        public boolean hasAPeel()
        {
                return true;
        }

        public boolean hasARoot()
        {
                return false;
        }

        void display()
        {
                System.out.println("Tomato Details:");
                System.out.println("Has a peel: " + hasAPeel());
                System.out.println("Has a root: " + hasARoot());
        }
}

class Main16
{
        public static void main(String[] args)
        {
                Tomato t = new Tomato();
                t.display();
        }
}

