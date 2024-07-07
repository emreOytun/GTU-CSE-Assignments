/**
 * The main method to test the sorting algorithms.
 * @author Emre Oytun
 */
public class Main {
    public static void main(String[] args) {
        myMap sortedMap = new myMap("a bb ccc dddd eeeee ffffff ggggggg hhhhhhhh iiiiiiiii jjjjjjjjjj kkkkkkkkkkk llllllllllll mmmmmmmmmmmmm nnnnnnnnnnnnnn ooooooooooooooo pppppppppppppppp qqqqqqqqqqqqqqqqq rrrrrrrrrrrrrrrrrr sssssssssssssssssss tttttttttttttttttttt uuuuuuuuuuuuuuuuuuuuu vvvvvvvvvvvvvvvvvvvvvv wwwwwwwwwwwwwwwwwwwwwww xxxxxxxxxxxxxxxxxxxxxxxx yyyyyyyyyyyyyyyyyyyyyyyyy zzzzzzzzzzzzzzzzzzzzzzzzzz");
        myMap reversedSortedMap = new myMap("zzzzzzzzzzzzzzzzzzzzzzzzzz yyyyyyyyyyyyyyyyyyyyyyyyy xxxxxxxxxxxxxxxxxxxxxxxx wwwwwwwwwwwwwwwwwwwwwww vvvvvvvvvvvvvvvvvvvvvv uuuuuuuuuuuuuuuuuuuuu tttttttttttttttttttt sssssssssssssssssss rrrrrrrrrrrrrrrrrr qqqqqqqqqqqqqqqqq pppppppppppppppp ooooooooooooooo nnnnnnnnnnnnnn mmmmmmmmmmmmm llllllllllll kkkkkkkkkkk jjjjjjjjjj iiiiiiiii hhhhhhhh ggggggg ffffff eeeee dddd ccc bb a");
        myMap sameCountsMap = new myMap("a b c d e f g h i j k l m n o p q r s t u v w x y z");
        myMap mixedMap = new myMap("tttttttttttttttttttt iiiiiiiii ooooooooooooooo hhhhhhhh vvvvvvvvvvvvvvvvvvvvvv bb pppppppppppppppp ccc qqqqqqqqqqqqqqqqq rrrrrrrrrrrrrrrrrr nnnnnnnnnnnnnn uuuuuuuuuuuuuuuuuuuuu llllllllllll mmmmmmmmmmmmm ggggggg zzzzzzzzzzzzzzzzzzzzzzzzzz a ffffff sssssssssssssssssss jjjjjjjjjj dddd xxxxxxxxxxxxxxxxxxxxxxxx kkkkkkkkkkk eeeee wwwwwwwwwwwwwwwwwwwwwww yyyyyyyyyyyyyyyyyyyyyyyyy");
    
        System.out.println("\n------------------");
        System.out.println("Selection sort best:");
        selectionSort selectionSortBest = new selectionSort(sortedMap);
        selectionSortBest.printMaps();

        System.out.println("\n------------------");
        System.out.println("Selection sort average:");
        selectionSort selectionSortAverage = new selectionSort(mixedMap);
        selectionSortAverage.printMaps();

        System.out.println("\n------------------");
        System.out.println("Selection sort worst:");
        selectionSort selectionSortWorst = new selectionSort(reversedSortedMap);
        selectionSortWorst.printMaps();


        System.out.println("\n------------------");
        System.out.println("Insertion sort best:");
        insertionSort insertionSortBest = new insertionSort(sortedMap);
        insertionSortBest.printMaps();

        System.out.println("\n------------------");
        System.out.println("Insertion sort average:");
        insertionSort insertionSortAverage = new insertionSort(mixedMap);
        insertionSortAverage.printMaps();

        System.out.println("\n------------------");
        System.out.println("Insertion sort worst:");
        insertionSort insertionSortWorst = new insertionSort(reversedSortedMap);
        insertionSortWorst.printMaps();



        System.out.println("Merge sort best:");
        mergeSort mergeSortBest = new mergeSort(sortedMap);
        mergeSortBest.printMaps();

        System.out.println("\n------------------");
        System.out.println("Merge sort average:");
        mergeSort mergeSortAverage = new mergeSort(mixedMap);
        mergeSortAverage.printMaps();

        System.out.println("\n------------------");
        System.out.println("Merge sort worst:");
        mergeSort mergeSortWorst = new mergeSort(reversedSortedMap);
        mergeSortWorst.printMaps();

        
            
        System.out.println("\n------------------");
        System.out.println("Bubble sort best:");
        bubbleSort bubbleSortBest = new bubbleSort(sortedMap);
        bubbleSortBest.printMaps();

        System.out.println("\n------------------");
        System.out.println("Bubble sort average:");
        bubbleSort bubbleSortAverage = new bubbleSort(mixedMap);
        bubbleSortAverage.printMaps();

        System.out.println("\n------------------");
        System.out.println("Bubble sort worst:");
        bubbleSort bubbleSortWorst = new bubbleSort(reversedSortedMap);
        bubbleSortWorst.printMaps();

        

        System.out.println("\n------------------");
        System.out.println("Quick sort best:");
        quickSort quickSortBest = new quickSort(sortedMap);
        quickSortBest.printMaps();

        System.out.println("\n------------------");
        System.out.println("Quick sort average:");
        quickSort quickSortAverage = new quickSort(mixedMap);
        quickSortAverage.printMaps();

        System.out.println("\n------------------");
        System.out.println("Quick sort worst:");
        quickSort quickSortWorst = new quickSort(sameCountsMap);
        quickSortWorst.printMaps();

    }
}