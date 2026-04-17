class FactGen extends Thread {
    public int p;
    private int i;
    public final Object lock;
    int[] b;
    public int turn = 0;

    public FactGen(Object lock, int[] b) {
        this.lock = lock;
        this.b = b;
        this.p = 1;
        this.i = 1;
    }

    public int nextFact() {
        p = p * i;
        i++;
        return p;
    }

    @Override
    public void run() {
        while (i <= 10) {
            synchronized (lock) {
                while (turn != 0) {
                    try {
                        lock.wait();
                    } catch (InterruptedException e) {
                        Thread.currentThread().interrupt();
                    }
                }
                b[0] = nextFact();
                System.out.println("Generated factorial: " + b[0]);
                turn = 1;
                lock.notify();
            }
        }
    }
}

class Adder extends Thread {
    public double sum;
    public final Object lock;
    FactGen fact;

    public Adder(Object lock, FactGen fact) {
        this.lock = lock;
        this.fact = fact;
        this.sum = 0;
    }

    @Override
    public void run() {
        // FIX 1: Adder must loop 10 times to match the 10 factorials
        for (int count = 1; count <= 10; count++) {
            
            // FIX 2: Spelled with a 'z'
            synchronized (lock) {
                while (fact.turn != 1) {
                    
                    // FIX 3: Wrapped wait() in a try-catch block
                    try {
                        lock.wait();
                    } catch (InterruptedException e) {
                        Thread.currentThread().interrupt();
                    }
                }
                
                sum += 1.0 / fact.b[0];
                fact.turn = 0;
                lock.notify();
            }
        }
    }
}

public class q3 { // Capitalized class names are best practice (e.g., Q3)
    public static void main(String[] args) {
        Object lock = new Object();
        int[] b = new int[1]; // The shared 'plate'
        
        FactGen factGen = new FactGen(lock, b);
        Adder adder = new Adder(lock, factGen);

        // Start both threads
        factGen.start();
        adder.start();

        // The main thread waits for both to finish before continuing
        try {
            factGen.join();
            adder.join();
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }

        // 1! + 2! + 3! + ... + 10! = 4037913
        System.out.println("Sum of factorials from 1! to 10!: " + adder.sum);
    }
}