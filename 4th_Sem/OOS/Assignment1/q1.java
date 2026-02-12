import java.util.*;

class Room {
        double height, breadth, length;

        Room(double height, double length, double breadth) {
                this.height = height;
                this.length = length;
                this.breadth = breadth;
        }

        double volume() {
                return length * breadth * height;
        }
}

class RoomDemo {
        public static void main(String args[]) {
                Room r1 = new Room(1, 2, 3);
                System.out.println("Volume is " + r1.volume());
        }
}

