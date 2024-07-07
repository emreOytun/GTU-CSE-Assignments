import java.io.FileNotFoundException;
import java.util.Scanner;

/**
 * Main class containing the main method to test the CustomTree class.
 * @author Emre Oytun
 */
public class Main {
    /**
     * A helper function to check if the given string can be converteed to an integer.
     * @param str The string that will be checked if it can be converted to an integer.
     * @return A boolean indicating if the given string can be converted to an integer.
     */
    public static boolean isNumber(String str) {
        try {
            Integer.valueOf(str);
            return true;
        } catch (Exception e) {
        }
        return false;
    }

    public static void main(String[] args) {
        try {
            CustomTree tree = new CustomTree();
            
            // Part-A:
            tree.constructTreeFromFile();
            Scanner scanner = new Scanner(System.in);
            tree.showTree();
            System.out.print("Press enter to close the frame...");
            scanner.nextLine();
            tree.closeTree();

            // Input for parts B,C,D:
            System.out.print("Enter the input to search: ");
            String input = scanner.nextLine();
            System.out.print(input);     
            
            // Part-B:
            tree.bfs(input);
            System.out.println();

            // Part-C:
            tree.dfs(input);
            System.out.println();

            // Part-D:
            tree.postOrderSearch(input);
            System.out.println();

            // Part-E:
            boolean isDone = true;
            String sourcePath = null;
            int sourceYear = -1;
            do {
                isDone = true;
                System.out.print("Enter the source path to move: ");
                sourcePath = scanner.nextLine();
                sourcePath = sourcePath.replaceAll(" ", ""); // remove all whitespaces
                String[] nodes = sourcePath.split(","); // split the given source

                // Check if there are at least 2 nodes.
                if (nodes.length < 2) {
                    System.out.println("Invalid input! There should be at least 2 nodes one for year and one for source node.");
                    isDone = false;
                }
                // Check if the first node is a year.
                else if (!isNumber(nodes[0])) {
                    System.out.println("Invalid input! The first node should be year.");
                    isDone = false;
                }
                else {
                    sourceYear = Integer.valueOf(nodes[0]);
                }
            } while (!isDone);

            String destination = null;
            do {
                isDone = true;
                System.out.print("Enter the destination: ");
                destination = scanner.nextLine();
                if (!isNumber(destination)) {
                    System.out.println("Invalid input! Destination should be year.");
                    isDone = false;
                }
                else if (Integer.valueOf(destination) == sourceYear) {
                    System.out.println("Invalid input! Source year and destination year cannot be the same.");
                    isDone = false;
                }
            } while (!isDone);
            
            tree.moveNode(sourcePath, destination);
            tree.showTree();
            System.out.print("Press enter to close the frame...");
            scanner.nextLine();
            tree.closeTree();
            scanner.close(); // close the scanner connection.

        } catch (FileNotFoundException e) {
            System.out.println(e.getMessage());
        }
    }
}
