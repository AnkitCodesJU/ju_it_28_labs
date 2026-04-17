import java.util.Scanner;
import java.util.Arrays;

class GenericSorter {

    public static <T extends Comparable<T>> void sortArray(T[] array) {
        int n = array.length;
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (array[j].compareTo(array[j + 1]) > 0) {
                    T temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                }
            }
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter number of elements: ");
        int n = sc.nextInt();

        Integer[] numbers = new Integer[n];

        System.out.println("Enter " + n + " integers:");
        for (int i = 0; i < n; i++) {
            numbers[i] = sc.nextInt();
        }

        sortArray(numbers);

        System.out.println("Sorted result: " + Arrays.toString(numbers));
        sc.close();
    }
}
