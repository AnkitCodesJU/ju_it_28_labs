class Adder{
        int n;
        int oddsum;
        int evenSum;
        public Adder(){
                n=0;
                oddsum=0;
                evenSum=0;
        }
        static final int max  = 100;
        // public Adder(){}
        
                void OddSum(){
                        synchronized(this){
                        while(n<max){
                        while(n%2 == 0){
                                try{this.wait();}catch(InterruptedException e){}
                        }
                        oddsum+=n;
                        n++;
                        this.notify();
                        }
                }
        }
       
                void EvenSum(){
                        synchronized(this){
                        while(n<max){
                        while(n%2 != 0){
                                try{this.wait();}catch(InterruptedException e){}
                        }
                        evenSum+=n;
                        n++;
                        this.notify();
                        }
                }
        }
        
}
class OddThread extends Thread{
        Adder adder;
        public OddThread(Adder adder){
                this.adder = adder;
        }
        public void run(){
                adder.OddSum();
        }
}
class EvenThread extends Thread{
        Adder adder;
        public EvenThread(Adder adder){
                this.adder = adder;
        }
        public void run(){
                adder.EvenSum();
        }
}
class q5{
        public static void main(String[] args){
                Adder adder = new Adder();
                OddThread oddThread = new OddThread(adder);
                EvenThread evenThread = new EvenThread(adder);
                oddThread.start();
                evenThread.start();
                try{
                        oddThread.join();
                        evenThread.join();
                }catch(InterruptedException e){
                        e.printStackTrace();
                }
                System.out.println("Sum of odd numbers: " + adder.oddsum);
                System.out.println("Sum of even numbers: " + adder.evenSum);    
        }
}
