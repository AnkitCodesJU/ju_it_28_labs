class SegmentScanner extends Thread 
{
        private int workerId;
        private int[] dataset;
        private int searchKey;
        private int boundLower;
        private int boundUpper;

        public SegmentScanner(int workerId, int[] dataset, int searchKey, int boundLower, int boundUpper) 
        {
                this.workerId = workerId;
                this.dataset = dataset;
                this.searchKey = searchKey;
                this.boundLower = boundLower;
                this.boundUpper = boundUpper;
        }

        @Override
        public void run() 
        {
                int leftPtr = boundLower;
                int rightPtr = boundUpper - 1;
                boolean isLocated = false;

                while (leftPtr <= rightPtr) 
                {
                        int center = leftPtr + (rightPtr - leftPtr) / 2;

                        if (dataset[center] == searchKey) 
                        {
                                synchronized (System.out) 
                                {
                                        System.out.println("Match identified.");
                                        System.out.println("Worker ID : " + workerId);
                                        System.out.println("Position  : " + center);
                                }
                                isLocated = true;
                                return;
                        } 
                        else if (dataset[center] < searchKey) 
                        {
                                leftPtr = center + 1;
                        } 
                        else 
                        {
                                rightPtr = center - 1;
                        }
                }
                
                if (!isLocated) 
                {
                        synchronized (System.out) 
                        {
                                System.out.println("Worker " + workerId + ": Key absent in assigned segment.");
                        }
                }
        }
}

class q7
{
        public static void main(String[] args) 
        {
                int totalElements = 50;
                int[] dataCollection = new int[totalElements];

                for (int idx = 0; idx < totalElements; idx++) 
                {
                        dataCollection[idx] = idx * 3; 
                }

                int keyToFind = 81; 
                
                System.out.println("Initiating distributed search for value: " + keyToFind + "\n");

                int threadCount = 5;
                int segmentSize = totalElements / threadCount;
                
                SegmentScanner[] workerPool = new SegmentScanner[threadCount];

                for (int idx = 0; idx < threadCount; idx++) 
                {
                        int rangeStart = idx * segmentSize;
                        int rangeEnd = rangeStart + segmentSize;

                        workerPool[idx] = new SegmentScanner(idx, dataCollection, keyToFind, rangeStart, rangeEnd);
                        workerPool[idx].start();
                }

                try 
                {
                        for (int idx = 0; idx < threadCount; idx++) 
                        {
                                workerPool[idx].join();
                        }
                } 
                catch (InterruptedException ex) 
                {
                        System.out.println("Execution was interrupted.");
                }
                
                System.out.println("\nSearch execution finished.");
        }
}