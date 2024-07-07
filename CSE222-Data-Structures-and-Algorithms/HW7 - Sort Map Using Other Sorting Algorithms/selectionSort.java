/**
 * The class that extends from the sortAbstract class and implements the sort method using
 * the selection sort algorithm.
 * @author Emre Oytun
 */
public class selectionSort extends sortAbstract {
    
    /**
     * The constructor to initialize an instance of the selection sort class using the given map.
     * @param originalMap The original map that will be sorted.
     */
    public selectionSort(myMap originalMap) {
        super(originalMap);
    }

    /**
     * The method that implements the sort method using the selection sort algorithm.
     */
    protected void sort() {
        for (int i = 0; i < aux.length-1; ++i) {
            int min_i = i;
            for (int j = i+1; j < aux.length; ++j) {
                if (originalMap.get(aux[j]).getCount() < originalMap.get(aux[min_i]).getCount()) {
                    min_i = j;
                }
            }
            swap(i, min_i);
        }
    }
}
