/**
 * The main method to test the sorting algorithm of the mergeSort class.
 * @author Emre Oytun
 */
public class Main {
    public static void main(String[] args) {
        myMap originalMap = new myMap("'Hush, hush!' whispered the rushing wind.");
        mergeSort sort = new mergeSort(originalMap);
        sort.printMaps();
    }
}