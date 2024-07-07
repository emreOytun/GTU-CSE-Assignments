import java.util.Set;

/**
 * The abstract class to keep the common members and methods together.
 * @author Emre Oytun
 */
public abstract class sortAbstract {
    protected myMap originalMap;
    protected myMap sortedMap;
    protected Character[] aux;

     /**
     * The constructor to initialize the members with the given original map by sorting the given map using the abstract sort method.
     * @param originalMap The original map that will be sorted.
     */
    public sortAbstract(myMap originalMap) {
        this.originalMap = originalMap;
        sortedMap = new myMap();
        // initialize the aux array as the key set.
        initializeAux();

        // sort the aux using selection sort.
        long start = System.nanoTime();
        sort();
        long end = System.nanoTime();
        long diff = end - start;
        System.out.println("Sorting time: " + diff + " ns.");

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
     * The abstract method that will be implemented by the children of this class such that
     * it will sort the auxilary array.
     */
    protected abstract void sort();

    /**
     * The method to swap the elements of the auxilary array using the given indexes.
     * @param fi The first element's index.
     * @param li The second element's index.
     */
    protected void swap(int fi, int li) {
        Character temp = aux[fi];
        aux[fi] = aux[li];
        aux[li] = temp;
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
