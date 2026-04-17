import java.util.Scanner;

class DuplicateFinder<T extends Comparable<T>> {

    public void printDuplicates(T[] array) {
        boolean foundAny = false;
        boolean[] counted = new boolean[array.length];

        for (int i = 0; i < array.length; i++) {
            if (counted[i]) continue;

            boolean isDuplicate = false;
            for (int j = i + 1; j < array.length; j++) {
                if (array[i].equals(array[j])) {
                    isDuplicate = true;
                    counted[j] = true; 
                }
            }

            if (isDuplicate) {
                System.out.println("Duplicate found: " + array[i]);
                foundAny = true;
            }
        }

        if (!foundAny) {
            System.out.println("No duplicates found.");
        }
    }
}

class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter number of elements: ");
        int n = sc.nextInt();

        Integer[] numbers = new Integer[n];
        System.out.println("Enter " + n + " integers:");
        for (int i = 0; i < n; i++) {
            numbers[i] = sc.nextInt();
        }

        DuplicateFinder<Integer> finder = new DuplicateFinder<>();
        finder.printDuplicates(numbers);

        sc.close();
    }
}
