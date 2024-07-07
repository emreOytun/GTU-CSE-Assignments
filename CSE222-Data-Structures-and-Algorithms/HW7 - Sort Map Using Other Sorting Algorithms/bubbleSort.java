/**
 * The class that extends from the sortAbstract class and implements the sort method using
 * the bubble sort algorithm.
 * @author Emre Oytun
 */
public class bubbleSort extends sortAbstract {
    
     /**
     * The constructor to initialize an instance of the bubble sort class using the given map.
     * @param originalMap The original map that will be sorted.
     */
    public bubbleSort(myMap originalMap) {
        super(originalMap);
    }

    /**
     * The method that implements the sort method using the bubble sort algorithm.
     */
    protected void sort() {
        boolean exchange = true;
        for (int i = 0; i < aux.length && exchange; ++i) {
            exchange = false;
            for (int j = 0; j < aux.length-1; ++j) {
                if (originalMap.get(aux[j+1]).getCount() < originalMap.get(aux[j]).getCount()) {
                    swap(j, j+1);
                    exchange = true;
                }
            }
        }
    }
}
