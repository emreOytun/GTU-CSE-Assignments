/**
 * The class that extends from the sortAbstract class and implements the sort method using
 * the quick sort algorithm.
 * @author Emre Oytun
 */
public class quickSort extends sortAbstract {
   
     /**
     * The constructor to initialize an instance of the quick sort class using the given map.
     * @param originalMap The original map that will be sorted.
     */
    public quickSort(myMap originalMap) {
        super(originalMap);
    }

    /**
     * The method that implements the sort method using the quick sort algorithm.
     */
    protected void sort() {
        sort(0, aux.length-1);
    }

    /**
     * The recursive method to sort the auxilary array using the quick sort algorithm.
     * It chooses the pivot as the middle element always.
     * @param firstIdx The first index of the current sub-array.
     * @param lastIdx The last index of the current sub-array.
     */
    private void sort(int firstIdx, int lastIdx) {
        if (firstIdx >= lastIdx) return;

        // Select the pivot as the middle item.
        int pivot = (firstIdx + lastIdx) / 2;
        swap(lastIdx, pivot);
        int pivotIdx = firstIdx;
        for (int i = firstIdx; i < lastIdx; ++i) {
            if (originalMap.get(aux[i]).getCount() <= originalMap.get(aux[lastIdx]).getCount()) {
                swap(pivotIdx, i);
                ++pivotIdx;
            }
        }
        swap(lastIdx, pivotIdx);
        sort(firstIdx, pivotIdx-1);
        sort(pivotIdx+1, lastIdx);
    }

}
