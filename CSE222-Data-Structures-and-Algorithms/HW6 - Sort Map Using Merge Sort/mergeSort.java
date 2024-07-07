import java.util.Set;

/**
 * The class to sort the given map using mergesort algorithm.
 * @author Emre Oytun
 */
public class mergeSort {
    private myMap originalMap;
    private myMap sortedMap;
    private Character[] aux;

    /**
     * The constructor to initialize an instance with the given original map by sorting the given map.
     * @param originalMap The original map that will be sorted.
     */
    public mergeSort(myMap originalMap) {
        this.originalMap = originalMap;
        sortedMap = new myMap();
        
        // initialize the aux array as the key set.
        initializeAux();

        // sort the aux using merge sort.
        sort(0, aux.length-1);

        // put the entries to the sorted map according to the sorted keys.
        setSortedMap();
    }

    /**
     * The method to initialize the auxilary array with the size of the key set.
     */
    private void initializeAux() {
        Set<Character> keySet = originalMap.keySet();
        aux = new Character[keySet.size()];
        int i = 0;
        for (Character ch : keySet) {
            aux[i++] = ch; 
        }
    }

    /**
     * The method to print the original and the sorted maps.
     */
    public void printMaps() {
        System.out.println("The original(unsorted map): ");
        originalMap.printMap();
        
        System.out.println();
        
        System.out.println("The sorted map: ");
        sortedMap.printMap();
    }

    /**
     * The recursive method to sort the map using mergesort by splitting the array into two sub-arrays.
     * @param firstIdx The first index of the current sub-array.
     * @param lastIdx The last index of the current sub-array.
     */
    private void sort(int firstIdx, int lastIdx) {
        if (firstIdx >= lastIdx) return;

        int midIdx = firstIdx + (lastIdx - firstIdx) / 2;
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
                mergedArr[curIdx++] = aux[leftIdx++];
            }
            else {
                mergedArr[curIdx++] = aux[rightIdx++];
            }
        }
        while (leftIdx <= midIdx) {
            mergedArr[curIdx++] = aux[leftIdx++];
        }
        while (rightIdx <= lastIdx) {
            mergedArr[curIdx++] = aux[rightIdx++];
        }
        for (int i = 0; i < totalLen; ++i) {
            aux[firstIdx + i] = mergedArr[i];
        }
    }

    /**
     * The method to set the sorted map using the auxilary array.
     */
    private void setSortedMap() {
        for (Character ch : aux) {
            sortedMap.put(ch, originalMap.get(ch));
        }
    }

}
