// 1. The Fully Optimized Printer
class Printer {
    public int n = 1;
    public int max = 8;
    
    public void printOdd() {
        while (n <= max) {
            
            // OPTIMIZATION: Only lock the critical section, not the whole method!
            synchronized (this) {
                // If it's even (and we haven't hit the max), go to sleep
                while (n % 2 == 0 && n <= max) {
                    try { wait(); } catch (InterruptedException e) {}
                }
                
                // Double-check that we haven't exceeded max while asleep
                if (n <= max) {
                    System.out.println("Odd Thread:  " + n);
                    n++;
                    notify(); // Wake up the even thread
                }
            }
        }
    }

    public void printEven() {
        while (n <= max) {
            
            // OPTIMIZATION: Only lock the critical section, not the whole method!
            synchronized (this) {
                // If it's odd (and we haven't hit the max), go to sleep
                while (n % 2 != 0 && n <= max) {
                    try { wait(); } catch (InterruptedException e) {}
                }
                
                // Double-check that we haven't exceeded max while asleep
                if (n <= max) {
                    System.out.println("Even Thread: " + n);
                    n++;
                    notify(); // Wake up the odd thread
                }
            }
        }
    }
}

// 2. The Threads
class OddThread extends Thread {
    Printer printer;
    public OddThread(Printer printer) { this.printer = printer; }
    
    public void run() {
        printer.printOdd();
    }
}

class EvenThread extends Thread {
    Printer printer;
    public EvenThread(Printer printer) { this.printer = printer; }
    
    public void run() {
        printer.printEven();
    }
}

// 3. Execution
public class q2 {
    public static void main(String[] args) {
        Printer printer = new Printer(); 
        
        new OddThread(printer).start();
        new EvenThread(printer).start();
    }
}