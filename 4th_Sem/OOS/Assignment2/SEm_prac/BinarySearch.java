class BinarySearch<T extends Comparable<T>> {
    int len;
    T[] arr;
    public BinarySearch(T[] arr){
        this.arr = arr;
        len = arr.length;
    }
    public void BinSearch(T item){
        int  mid,low = 0,high = len - 1;
        while(low <= high){
            mid = (low + high) / 2;
            if(arr[mid].compareTo(item) == 0){
                System.out.println("Element found at index: " + mid);
                return;
            }
            else if(arr[mid].compareTo(item) < 0){
                low = mid + 1;
            }
            else{
                high = mid - 1;
            }
        }
        System.out.println("Element not found");
    }
    public static void main(String[] args) {
        Integer[] arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        BinarySearch<Integer> bs = new BinarySearch<>(arr);
        bs.BinSearch(5); // Should print index of element
        bs.BinSearch(11); // Should print "Element not found"
    }
}