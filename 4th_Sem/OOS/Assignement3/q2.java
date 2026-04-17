import java.util.Scanner;
import java.util.Arrays;

class Main {

    public static <T extends Comparable<T>> void findFrequency(T[] array) {
        if (array.length == 0) return;

        Arrays.sort(array);

        int count = 1;
        for (int i = 0; i < array.length; i++) {
            if (i < array.length - 1 && array[i].equals(array[i + 1])) {
                count++;
            } else {
                System.out.println(array[i] + ": " + count);
                count = 1;
            }
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter number of elements: ");
        int n = sc.nextInt();

        Integer[] data = new Integer[n];
        System.out.println("Enter " + n + " integers:");
        for (int i = 0; i < n; i++) {
            data[i] = sc.nextInt();
        }

        System.out.println("Frequency of elements:");
        findFrequency(data);
        
        sc.close();
    }
}
