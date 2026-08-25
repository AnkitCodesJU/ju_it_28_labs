public class GenericFreq<T extends Comparable<T>> {

    private T[] arr;
    int[] freq;
    int[] vis;
    int len;

    public GenericFreq(T[] arr) {
        this.arr = arr;
        this.len = arr.length;
        this.freq = new int[len];
        this.vis = new int[len];
    }

    public void getFrequency() {

        for (int i = 0; i < len; i++) {

            if (vis[i] == 1)
                continue;

            freq[i] = 1;
            vis[i] = 1;

            for (int j = i + 1; j < len; j++) {

                if (arr[i].compareTo(arr[j]) == 0) {
                    freq[i]++;
                    vis[j] = 1;
                }
            }
        }
    }

    public void printFreq() {

        getFrequency();

        for (int i = 0; i < len; i++) {

            if (vis[i] == 1 && freq[i] > 0) {
                System.out.println("Freq[" + arr[i] + "] = " + freq[i]);
            }
        }
    }
}
class Main1 {
    public static void main(String[] args) {
        Integer[] arr = {1, 2, 3, 2, 1, 4, 5, 3};
        GenericFreq<Integer> gf = new GenericFreq<>(arr);
        gf.printFreq();
    }
}