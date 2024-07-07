/**
 * The class that extends from the sortAbstract class and implements the sort method using
 * the mergesort algorithm.
 * @author Emre Oytun
 */
public class mergeSort extends sortAbstract {
  
     /**
     * The constructor to initialize an instance of the mergesort class using the given map.
     * @param originalMap The original map that will be sorted.
     */
    public mergeSort(myMap originalMap) {
        super(originalMap);
    }

    /**
     * The method that implements the sort method using the merge sort algorithm.
     */
    protected void sort() {
        sort(0, aux.length-1);
    }

    /**
     * The recursive method to sort the auxilary array using the mergesort algorithm.
     * It always splits the array into two sub-arrays.
     * @param firstIdx The first index of the current sub-array.
     * @param lastIdx The last index of the current sub-array.
     */
    private void sort(int firstIdx, int lastIdx) {
        if (firstIdx >= lastIdx) return;

        int midIdx = (firstIdx + lastIdx) / 2;
        sort(firstIdx, midIdx);
        sort(midIdx+1, lastIdx);
        merge(firstIdx, midIdx, lastIdx);
    }

    /**
     * The method to merge two sub-arrays into one sorted array using the given indexes.
     * @param firstIdx The first index of the first sub-array.
     * @param midIdx The middle index that is the last index of the first sub-array.
     * @param lastIdx The last index of the second sub-array.
     */
    private void merge(int firstIdx, int midIdx, int lastIdx) {
        int totalLen = lastIdx - firstIdx + 1;
        Character[] mergedArr = new Character[totalLen];

        int leftIdx = firstIdx;
        int rightIdx = midIdx + 1;
        int curIdx = 0;
        while (leftIdx <= midIdx && rightIdx <= lastIdx) {
            if (originalMap.get(aux[leftIdx]).getCount() <=  originalMap.get(aux[rightIdx]).getCount()) {
                mergedArr[curIdx] = aux[leftIdx];
                ++curIdx;
                ++leftIdx;
            }
            else {
                mergedArr[curIdx] = aux[rightIdx];
                ++curIdx;
                ++rightIdx;
            }
        }
        while (leftIdx <= midIdx) {
            mergedArr[curIdx] = aux[leftIdx];
            ++curIdx;
            ++leftIdx;
        }
        while (rightIdx <= lastIdx) {
            mergedArr[curIdx] = aux[rightIdx];
            ++curIdx;
            ++rightIdx;
        }
        for (int i = 0; i < totalLen; ++i, ++firstIdx) {
            aux[firstIdx] = mergedArr[i];
        }
    }
}
