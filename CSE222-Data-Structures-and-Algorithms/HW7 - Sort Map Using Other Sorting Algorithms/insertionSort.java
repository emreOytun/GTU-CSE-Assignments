/**
 * The class that extends from the sortAbstract class and implements the sort method using
 * the insertion sort algorithm.
 * @author Emre Oytun
 */
public class insertionSort extends sortAbstract {
    
     /**
     * The constructor to initialize an instance of the insertion sort class using the given map.
     * @param originalMap The original map that will be sorted.
     */
    public insertionSort(myMap originalMap) {
        super(originalMap);
    }

    /**
     * The method that implements the sort method using the insertion sort algorithm.
     */
    protected void sort() {
        for (int i = 1; i < aux.length; ++i) {
            for (int j = i-1; j >= 0 && originalMap.get(aux[j+1]).getCount() < originalMap.get(aux[j]).getCount(); --j) {
                swap(j+1, j);
            }
        }
    }

}
