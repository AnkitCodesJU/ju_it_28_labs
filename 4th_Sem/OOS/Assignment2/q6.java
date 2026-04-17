class Binary extends Thread {
    // Clever upgrade: storing the actual index instead of just true/false!
    public static volatile int found = -1; 
    
    int startIndex;
    int endIndex;
    int value;
    int[] arr;

    public Binary(int startIndex, int endIndex, int value, int[] arr) {
        this.startIndex = startIndex;
        this.endIndex = endIndex;
        this.value = value;
        this.arr = arr;
    }

    @Override
    public void run() {
        int mid;
        
        // This condition checks if we haven't found it yet AND the target actually
        // falls within this specific thread's assigned chunk of numbers.
        while (found == -1 && startIndex <= endIndex && value <= arr[endIndex] && value >= arr[startIndex]) {
            mid = (startIndex + endIndex) / 2;
            
            if (arr[mid] == value) {
                found = mid; // Broadcast the index to everyone!
                System.out.println("Value found at index: " + mid);
                return;
            } else if (arr[mid] < value) {
                startIndex = mid + 1;
            } else {
                endIndex = mid - 1;
            }
        }
    }
}
class q6 { // Capitalized class name
    
    // FIX 1: Added the main method!
    public static void main(String[] args) { 
        int n = 30; // Array size 
        
        // Create the sorted array: [0, 2, 4, 6, 8, ... 58]
        int[] array = new int[n];
        for (int i = 0; i < n; i++) {
            array[i] = i * 2; 
        }
        
        int nt = n / 10;
        Thread[] thread = new Binary[nt];
        
        for (int i = 0; i < nt; i++) {
            int start = i * 10;
            // FIX 2: Made the end index INCLUSIVE (9, 19, 29) to prevent crashing
            int end = start + 9; 
            
            thread[i] = new Binary(start, end, 44, array);
            thread[i].start();
        }
        
        for (int i = 0; i < nt; i++) {
            try {
                thread[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();    
            }
        }
        
        // FIX 4: Check the global static variable AFTER all threads have joined
        if (Binary.found == -1) {
            System.out.println("Value not found in the array.");                  
        }
    }
}