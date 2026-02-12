class Automobile {
        private String make;
        private String type;
        private int maxSpeed;
        private double price;
        private double mileage;
        private String registrationNumber;

        public void setMake(String make) {
                this.make = make;
        }

        public void setType(String type) {
                this.type = type;
        }

        public void setMaxSpeed(int maxSpeed) {
                this.maxSpeed = maxSpeed;
        }

        public void setPrice(double price) {
                this.price = price;
        }

        public void setMileage(double mileage) {
                this.mileage = mileage;
        }

        public void setRegistrationNumber(String registrationNumber) {
                this.registrationNumber = registrationNumber;
        }

        public String getMake() {
                return make;
        }

        public String getType() {
                return type;
        }

        public int getMaxSpeed() {
                return maxSpeed;
        }

        public double getPrice() {
                return price;
        }

        public double getMileage() {
                return mileage;
        }

        public String getRegistrationNumber() {
                return registrationNumber;
        }
}

class Track extends Automobile {
        private int capacity;
        private String hoodType;
        private int noOfWheels;

        public void setCapacity(int capacity) {
                this.capacity = capacity;
        }

        public void setHoodType(String hoodType) {
                this.hoodType = hoodType;
        }

        public void setNoOfWheels(int noOfWheels) {
                this.noOfWheels = noOfWheels;
        }

        public int getCapacity() {
                return capacity;
        }

        public String getHoodType() {
                return hoodType;
        }

        public int getNoOfWheels() {
                return noOfWheels;
        }
}

class Car extends Automobile {
        private int noOfDoors;
        private int seatingCapacity;

        public void setNoOfDoors(int noOfDoors) {
                this.noOfDoors = noOfDoors;
        }

        public void setSeatingCapacity(int seatingCapacity) {
                this.seatingCapacity = seatingCapacity;
        }

        public int getNoOfDoors() {
                return noOfDoors;
        }

        public int getSeatingCapacity() {
                return seatingCapacity;
        }
}
class Main13 {
        public static void main(String[] args) {

                Car car = new Car();
                car.setMake("Honda");
                car.setType("Sedan");
                car.setMaxSpeed(180);
                car.setPrice(1200000);
                car.setMileage(17.5);
                car.setRegistrationNumber("ABC123");
                car.setNoOfDoors(4);
                car.setSeatingCapacity(5);

                System.out.println("Car Details");
                System.out.println(car.getMake());
                System.out.println(car.getType());
                System.out.println(car.getMaxSpeed());
                System.out.println(car.getPrice());
                System.out.println(car.getMileage());
                System.out.println(car.getRegistrationNumber());
                System.out.println(car.getNoOfDoors());
                System.out.println(car.getSeatingCapacity());

                System.out.println();

                Track track = new Track();
                track.setMake("Tata");
                track.setType("Transport");
                track.setMaxSpeed(120);
                track.setPrice(2500000);
                track.setMileage(8.0);
                track.setRegistrationNumber("XYZ789");
                track.setCapacity(25);
                track.setHoodType("Open");
                track.setNoOfWheels(10);

                System.out.println("Track Details");
                System.out.println(track.getMake());
                System.out.println(track.getType());
                System.out.println(track.getMaxSpeed());
                System.out.println(track.getPrice());
                System.out.println(track.getMileage());
                System.out.println(track.getRegistrationNumber());
                System.out.println(track.getCapacity());
                System.out.println(track.getHoodType());
                System.out.println(track.getNoOfWheels());
        }
}

