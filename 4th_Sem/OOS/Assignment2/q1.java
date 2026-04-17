class ChildThread extends Thread 
{
        @Override
        public void run() 
        {
                System.out.println("In child thread");
        }
}

class q1
{
        public static void main(String[] args) 
        {
                ChildThread child = new ChildThread();
                child.start();    
                System.out.println("In main thread");
        }
}