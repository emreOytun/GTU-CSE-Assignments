class Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None


# Put the tree elements into the sortedArr in a sorted way.
# 1) Make a recursive call with left subtree to fill sorted array with the left subtree's elements.
# 2) Put the root's value into the sorted array's end.
# 3) Make the same thing as 1st step but this time for right subtree.
def getTreeElementsSorted(root, sortedArr):
    if (root == None):
        return
    
    getTreeElementsSorted(root.left, sortedArr)
    sortedArr.append(root.value)
    getTreeElementsSorted(root.right, sortedArr)
    return sortedArr

# Create BST using the given sorted array arr.
def createTreeFromSortedArray(arr):
    return createTreeFromSortedArrayRec(arr, 0, len(arr) - 1)

# Create BST using the given sorted array arr in a recursive manner.
# 1) Check the length first. If there are no elements then return None, if there are only one elements then return this element in a node.
# 2) Otherwise, continue. Make two recursive calls for left and right part of the array and get the left and right subtrees.
# 3) Combine the results and return the tree.
def createTreeFromSortedArrayRec(arr, li, ri):
    length = ri - li + 1
    
    if (length <= 0):
        return None
    if (length == 1):
        return Node(arr[li])
    
    # Find mid using floor divison
    midIdx = (ri + li) // 2
    leftTree = createTreeFromSortedArrayRec(arr, li, midIdx - 1)
    rightTree = createTreeFromSortedArrayRec(arr, midIdx + 1, ri)
    
    resultTree = Node(arr[midIdx])
    resultTree.left = leftTree
    resultTree.right = rightTree
    return resultTree

# 1) Get the tree elements in a sorted array.
# 2) Create tree using this sorted array in a balanced way.
def balanceBST(root):
    sortedArr = []
    getTreeElementsSorted(root, sortedArr)
    return createTreeFromSortedArray(sortedArr)

# Print the three using BFS. (from-left-to-right in each level)
def printTreeBFS(root):
    if (root == None):
        return
    
    queue = []
    queue.append(root)
    while (len(queue) != 0):
        node = queue.pop(0)
        print(node.value)
        if (node.left):
            print(f"{node.value}'s left child: {node.left.value}")
            queue.append(node.left)
        if (node.right):
            print(f"{node.value}'s right child: {node.right.value}")
            queue.append(node.right) 

def main():
    root1 = Node(10)
    node1_1 = Node(3)
    node1_2 = Node(13)

    node1_3 = Node(17)
    node1_4 = Node(20)

    node1_2.right = node1_3
    node1_3.right = node1_4

    root1.left = node1_1
    root1.right = node1_2

    # Print tree before.
    print("Before balance: \n")
    printTreeBFS(root1)
    
    # Print tree after.
    print("\nAfter balance: \n")
    printTreeBFS(balanceBST(root1))

main()
