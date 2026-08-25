import java.io.*;
import java.util.Scanner;

public class NumeralWordFilter {

    private boolean containsNumeral(String word) {
        for (int i = 0; i < word.length(); i++) {
            if (Character.isDigit(word.charAt(i))) {
                return true;
            }
        }
        return false;
    }

    public int filterAndCountNumeralWords(String sourceFilePath, String destFilePath) {
        int numeralWordCount = 0;

        try (Scanner scanner = new Scanner(new FileInputStream(sourceFilePath));
             PrintWriter writer = new PrintWriter(new FileOutputStream(destFilePath))) {

            while (scanner.hasNext()) {
                String word = scanner.next();

                if (containsNumeral(word)) {
                    writer.println(word);
                    numeralWordCount++;
                }
            }
            
            System.out.println("File processing successful.");

        } catch (FileNotFoundException e) {
            System.out.println("Error: One of the files could not be found or created.");
        } catch (IOException e) {
            System.out.println("Exception caught during I/O operations: " + e.getMessage());
        }

        return numeralWordCount;
    }

    public static void main(String[] args) {
        NumeralWordFilter filter = new NumeralWordFilter();
        
        String sourceFile = "source.txt"; 
        String destinationFile = "dest.txt"; 
        
        int count = filter.filterAndCountNumeralWords(sourceFile, destinationFile);
        
        System.out.println("Total number of words containing at least one numeral: " + count);
    }
}