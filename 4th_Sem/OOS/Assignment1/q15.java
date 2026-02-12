class Tollbooth
{
        private int totalCars;
        private int unpaidCars;
        private int totalCash;

        Tollbooth()
        {
                totalCars = 0;
                unpaidCars = 0;
                totalCash = 0;
        }

        void payingCar()
        {
                totalCars++;
                totalCash = totalCash + 50;
        }

        void nonPayingCar()
        {
                totalCars++;
                unpaidCars++;
        }

        void display()
        {
                System.out.println("Total number of cars passed without paying: " + unpaidCars);
                System.out.println("Total number of cars passed by: " + totalCars);
                System.out.println("Total cash collected: Rs. " + totalCash);
        }
}

class Main15
{
        public static void main(String[] args)
        {
                Tollbooth tb = new Tollbooth();

                tb.payingCar();
                tb.payingCar();
                tb.nonPayingCar();
                tb.payingCar();
                tb.nonPayingCar();
                tb.payingCar();

                tb.display();
        }
}

