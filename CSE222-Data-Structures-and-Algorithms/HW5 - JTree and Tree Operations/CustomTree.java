import java.io.File;
import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Scanner;

import javax.swing.JFrame;
import javax.swing.JTree;
import javax.swing.tree.DefaultMutableTreeNode;

/**
 * A tree class using JTree.
 * @author Emre Oytun
 */
public class CustomTree {
    private DefaultMutableTreeNode root = new DefaultMutableTreeNode("Root");
    private JFrame frame = new JFrame();
    private JTree jtree = null;

    /**
     * Shows the JTree structure by using JFrame.
     */
    public void showTree() {
        // Create and embed the JTree to the JFrame to display the JTree.
        jtree = new JTree(root);
        frame.add(jtree);
        frame.setSize(500, 500);
        frame.setVisible(true);
    }

    /**
     * Closes the JFrame.
     */
    public void closeTree() {
        frame.remove(jtree);
        frame.setVisible(false);
        frame.dispose();
    }

    /**
     * Makes breadth-first search using the given element.
     * @param element The element that will be searched in the tree.
     */
    public void bfs(Object element) {
        System.out.println("Using BFS to find '" + element + "' in the tree...");
        LinkedList<DefaultMutableTreeNode> queue = new LinkedList<>();
        queue.offer(root); // Initialize the queue with the root.

        boolean isFound = false;
        int step = 1;
        while (!queue.isEmpty() && !isFound) {
            DefaultMutableTreeNode node = queue.pop();
            if (node.getUserObject().equals(element)) { // Check if the node's object is equals to the element.
                System.out.println("Step " + step + " -> " + node.getUserObject() + "(Found!)");
                isFound = true;
            }
            else { // Otherwise, put children to the queue and continue.
                System.out.println("Step " + step + " -> " + node.getUserObject());
                for (int i = 0; i < node.getChildCount(); ++i) {
                    queue.offer((DefaultMutableTreeNode) node.getChildAt(i));
                }       
            }
            ++step;
        }
        if (!isFound) System.out.println("Not found.");
    }

    private int step; // Step number for dfs.

    /**
     * Makes depth-first search using the given element.
     * @param element The element that will be searched in the tree.
     */
    public void dfs(Object element) {
        System.out.println("Using DFS to find '" + element + "' in the tree...");
        step = 1;
        if (!dfsRec(root, element)) {
            System.out.println("Not found.");
        }
    }

    /**
     * Helper recursive method for dfs, it recursively searches the element in the tree.
     * @param node The current node in the search.
     * @param element The element that will be searched in the tree.
     * @return A boolean indicating if the element is found or not.
     */
    private boolean dfsRec(DefaultMutableTreeNode node, Object element) {
        // Check if the node's object is equals to the element.
        if (node.getUserObject().equals(element)) {
            System.out.println("Step " + step + " -> " + node.getUserObject() + "(Found!)");
            return true;
        }

        System.out.println("Step " + step + " -> " + node.getUserObject());
        ++step;
        for (int i = node.getChildCount()-1; i >= 0; --i) {     // Call next dfsRec methods for the children starting from the rightmost.
            boolean res = dfsRec((DefaultMutableTreeNode) node.getChildAt(i), element);
            if (res) return true;
        }
        return false;
    }

    /**
     * Makes post-order search in the tree.
     * @param element The element that will be searched in the tree.
     */
    public void postOrderSearch(Object element) {
        System.out.println("Using Post-Order traversal to find '" + element + "' in the tree...");
        step = 1;
        boolean isFound = false;    

        // Root is not counted in the post-order so call postOrderSearchRec for the children of the root here.
        for (int i = 0; i < root.getChildCount() && !isFound; ++i) {
            if (postOrderSearchRec((DefaultMutableTreeNode) root.getChildAt(i), element)) {
                isFound = true;
            }
        }
        if (!isFound) { 
            System.out.println("Not found.");
        }
    }

    /**
     * A helper recursive method for post-order search. It searches the element recursively.
     * @param node The current node in the search.
     * @param element The element that will be searched in the tree.
     * @return A boolean indicating if the element is found or not.
     */
    private boolean postOrderSearchRec(DefaultMutableTreeNode node, Object element) {
        // Call the next methods from starting left child to right child.
        for (int i = 0; i < node.getChildCount(); ++i) {
            boolean res = postOrderSearchRec((DefaultMutableTreeNode) node.getChildAt(i), element);
            if (res) return true;
        }
        if (node.getUserObject().equals(element)) {
            System.out.println("Step " + step + " -> " + node.getUserObject() + "(Found!)");
            return true;
        }
        System.out.println("Step " + step + " -> " + node.getUserObject());
        ++step;
        return false;
    }

    /**
     * Moves the node from the given source to the destination.
     * @param source The path to the source node that will be moved.
     * @param destination The destination year that source node will be moved into.
     */
    public void moveNode(String source, String destination) {
        // Try to find and delete the source node in the deleteNode method.
        String[] sourcePath = source.split(",");
        DefaultMutableTreeNode sourceNode = deleteNode(root, sourcePath, 0);
        if (sourceNode == null) {
            source = source.replaceAll(",", "->");
            System.out.println("Cannot move " + source + " because it doesn't exist in the tree.");
        }
        else {
            // Continue to moving the found sourceNode.
            String[] destinationPath = Arrays.copyOf(sourcePath, sourcePath.length);
            destinationPath[0] = destination;

            DefaultMutableTreeNode curNode = root;
            // Go until the source node, if there is no such path then create it; continue to the next path otherwise.
            for (int i = 0; i < destinationPath.length-1; ++i) {
                int childIndex = indexOfChild(curNode, destinationPath[i]);
                if (childIndex == -1) {
                    DefaultMutableTreeNode newNode = new DefaultMutableTreeNode(destinationPath[i]);
                    curNode.add(newNode);
                    curNode = newNode;
                }
                else {
                    curNode = (DefaultMutableTreeNode) curNode.getChildAt(childIndex);
                }
            }
            int childIndex = indexOfChild(curNode, destinationPath[destinationPath.length-1]);
            if (childIndex == -1) curNode.add(sourceNode); // Add the source node directly to the parent, if the parent does not have this child.
            else { // Overwrite otherwise.
                curNode.remove(childIndex);
                LinkedList<DefaultMutableTreeNode> childQueue = new LinkedList<>();
                for (int i = childIndex; i < curNode.getChildCount(); ++i) {
                    childQueue.offer((DefaultMutableTreeNode) curNode.getChildAt(i));
                    curNode.remove(i);
                }
                curNode.add(sourceNode);
                while (!childQueue.isEmpty()) {
                    curNode.add(childQueue.pop());
                }

                source = source.replaceAll(",", "->");
                System.out.println("Moved " + source + " to " + destination + ".");
             
                int firstComma = source.indexOf("-");
                String printDestinationPath = destination + "->" +source.substring(firstComma+2, source.length());
                System.out.println(printDestinationPath + " has been overwritten.");
            }
        }
    }

    // 
    /**
     * Deletes the source node given in the source path.
     * Starting from root, tries to find the child in the path and remove when it reaches at the source node given in the path.
     * @param curNode The parent node that the current path will be searched in its children.
     * @param sourcePath The array containing the node names in the source path.
     * @param index The current index of the current path that will be searched.
     * @return The deleted source node, or null if there is no such node.
     */
    private DefaultMutableTreeNode deleteNode(DefaultMutableTreeNode curNode, String[] sourcePath, int index) {
        int childIndex = indexOfChild(curNode, sourcePath[index]);
        if (childIndex == -1) return null; // Return null if there are no such path.
        // Check if it reaches at the source node.
        if (sourcePath.length == index+1) {
            DefaultMutableTreeNode sourceNode = (DefaultMutableTreeNode) curNode.getChildAt(childIndex);
            curNode.remove(childIndex);
            return sourceNode;
        }
        // If it doesn't reach at the source node, then continue for the next path.
        DefaultMutableTreeNode sourceNode = deleteNode((DefaultMutableTreeNode) curNode.getChildAt(childIndex), sourcePath, index+1);
        if (sourceNode == null) return null;
        DefaultMutableTreeNode childNode = (DefaultMutableTreeNode) curNode.getChildAt(childIndex);
        if (childNode.getChildCount() == 0) curNode.remove(childIndex);
        return sourceNode;
    }

    /**
     * Constructs tree from the .txt file.
     * @throws FileNotFoundException when the file is not found in the folder.
     */
    public void constructTreeFromFile() throws FileNotFoundException {
        try {
            // Initialize the file.
            File file = new File("tree.txt");
            Scanner scanner = new Scanner(file); // Open connection

            // Calculate the total row number.
            int totalRow = 0;
            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();               
                if (line != null && !isBlank(line)) ++totalRow;
            }
            scanner.close(); // Close the file connection
            
            // Read the file again and 
            String[][] arr = new String[totalRow][];
            scanner = new Scanner(file);
            int i = 0;
            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                if (line != null && !isBlank(line)) {
		           arr[i] = line.split(";");
		           ++i;
                }
            }
            scanner.close(); // close the file connection.

            constructTreeHelper(arr);
        } catch(FileNotFoundException e) {
            System.out.println("Try again... File name should be: tree.txt.");
        }
    }

    /**
     * A helper function to construct the tree from .txt file.
     * It constructs the tree using the 2D String array containing the paths in each line.
     * @param arr The 2D String array that contains the paths.
     */
    private void constructTreeHelper(String[][] arr) {
        // Iterate over each line, and add the nodes to the tree.
        // For each line, starting from the root:
        // 1) Try to find the child index of the current path.
        // 2) If there is no such path, then create it. Otherwise, continue with this path.
        for (int i = 0; i < arr.length; ++i) {
            DefaultMutableTreeNode curNode = root;
            for (int j = 0; j < arr[i].length; ++j) {
                int idx = indexOfChild(curNode, arr[i][j]);
                if (idx == -1) {
                    DefaultMutableTreeNode newNode = new DefaultMutableTreeNode(arr[i][j]);
                    curNode.add(newNode);
                    curNode = newNode;
                }
                else {
                    // Since the tree has only DefaultMutableTreeNode type nodes, cast safely.
                    curNode = (DefaultMutableTreeNode) curNode.getChildAt(idx); 
                }
            }
        }
    }

    /**
     * A helper method to find the given element inside the children of the given node.
     * Returns -1 if the given element is not found.
     * @param node The node that element will be searched in its children.
     * @param element The element that will be searched.
     * @return An integer of the element's index. -1, if element is not found.
     */
    private int indexOfChild(DefaultMutableTreeNode node, Object element) {
        for (int i = 0; i < node.getChildCount(); ++i) {
            DefaultMutableTreeNode child = (DefaultMutableTreeNode) node.getChildAt(i);
            if (child.getUserObject().equals(element)) return i;
        }
        return -1;
    }

    private boolean isBlank(String str) {
        if (str.length() == 0) return true;
        for (int i = 0; i < str.length(); ++i) {
            if (str.charAt(i) != ' ') return false;
        }
        return true;
    }
}