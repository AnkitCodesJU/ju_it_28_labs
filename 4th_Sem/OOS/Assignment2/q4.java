import java.io.*;
import java.util.Scanner;

class DataVault 
{
        private int currentValue;
        private boolean isLoaded = false;
        private boolean isFinished = false;

        public synchronized void storeValue(int val) 
        {
                while (isLoaded) 
                {
                        try 
                        {
                                wait();
                        } 
                        catch (InterruptedException ex) 
                        {
                                Thread.currentThread().interrupt();
                        }
                }
                this.currentValue = val;
                this.isLoaded = true;
                notify();
        }

        public synchronized Integer fetchValue() 
        {
                while (!isLoaded && !isFinished) 
                {
                        try 
                        {
                                wait();
                        } 
                        catch (InterruptedException ex) 
                        {
                                Thread.currentThread().interrupt();
                        }
                }

                if (!isLoaded && isFinished) 
                {
                        return null;
                }

                int temp = currentValue;
                isLoaded = false;
                notify();
                return temp;
        }

        public synchronized void markComplete() 
        {
                this.isFinished = true;
                notifyAll();
        }
}

class FileReaderTask extends Thread 
{
        private DataVault vault;
        private String targetPath;

        public FileReaderTask(DataVault vault, String targetPath) 
        {
                this.vault = vault;
                this.targetPath = targetPath;
        }

        @Override
        public void run() 
        {
                try (Scanner scan = new Scanner(new File(targetPath))) 
                {
                        System.out.println("Reading started...");
                        
                        while (scan.hasNextInt()) 
                        {
                                int fetchedNum = scan.nextInt();
                                System.out.println("Read: " + fetchedNum);
                                vault.storeValue(fetchedNum);
                        }
                        
                        System.out.println("Reading completed.");
                } 
                catch (FileNotFoundException ex) 
                {
                        System.out.println("File missing.");
                } 
                finally 
                {
                        vault.markComplete(); 
                }
        }
}

class AccumulatorTask extends Thread 
{
        private DataVault vault;

        public AccumulatorTask(DataVault vault) 
        {
                this.vault = vault;
        }

        @Override
        public void run() 
        {
                long totalAmount = 0;
                System.out.println("Accumulation started...");
                
                while (true) 
                {
                        Integer extracted = vault.fetchValue();
                        
                        if (extracted == null) 
                        {
                                break;
                        }
                        
                        System.out.println("Processed: " + extracted);
                        totalAmount += extracted;
                }
                
                System.out.println("\n----------------------------");
                System.out.println("Calculated Total: " + totalAmount);
                System.out.println("----------------------------");
        }
}

class q4
{
        public static void main(String[] args) 
        {
                String sourceFile = "data_input.txt";
                
                generateTestData(sourceFile);

                DataVault syncVault = new DataVault();
                
                FileReaderTask reader = new FileReaderTask(syncVault, sourceFile);
                AccumulatorTask calculator = new AccumulatorTask(syncVault);

                reader.start();
                calculator.start();
        }

        private static void generateTestData(String filePath) 
        {
                try (PrintWriter out = new PrintWriter(filePath)) 
                {
                        out.println("10 20 30");
                        out.println("40 50");
                        out.println("100");
                        System.out.println("Test file initialized.\n");
                } 
                catch (FileNotFoundException ex) 
                {
                        System.out.println("Error initializing file.");
                }
        }
}