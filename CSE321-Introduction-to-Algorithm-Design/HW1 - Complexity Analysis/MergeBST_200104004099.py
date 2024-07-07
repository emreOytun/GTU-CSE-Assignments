class Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None


def printTreeInfix(root):
    if (root == None):
        return

    printTreeInfix(root.left)
    print(root.value)
    printTreeInfix(root.right)

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

# Merge two sorted array into one.
# If there are duplicate elements, then only one of them is taken.
def mergeTwoSortedArray(arr1, arr2):
    mergedArr = []
    idx1 = 0
    idx2 = 0
    while (idx1 < len(arr1) and idx2 < len(arr2)):
        if (arr1[idx1] < arr2[idx2]):
            mergedArr.append(arr1[idx1])
            idx1 = idx1 + 1
        elif (arr2[idx2] < arr1[idx1]):
            mergedArr.append(arr2[idx2])
            idx2 = idx2 + 1
        else:
            idx2 = idx2 + 1     # Ignore duplicates


    while (idx1 < len(arr1)):
        mergedArr.append(arr1[idx1])
        idx1 = idx1 + 1

    while (idx2 < len(arr2)):
        mergedArr.append(arr2[idx2])
        idx2 = idx2 + 1
        
    return mergedArr

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

# Merge two BST whose roots are given as parameters.
# 1) Get tree elements sorted in two seperate arrays.
# 2) Merge these two sorted arrays into one.
# 3) Create BST using the merged sorted array.
def mergeTwoBST(root1, root2):
    sortedArr1 = []
    sortedArr2 = []
    getTreeElementsSorted(root1, sortedArr1)
    getTreeElementsSorted(root2, sortedArr2)
    mergedArr = mergeTwoSortedArray(sortedArr1, sortedArr2)
    return createTreeFromSortedArray(mergedArr)

def main():
    root1 = Node(10)
    node1_1 = Node(3)
    node1_2 = Node(13)

    root1.left = node1_1
    root1.right = node1_2

    root2 = Node(20)
    node2_1 = Node(10)
    node2_2 = Node(7)
    node2_3 = Node(22)

    root2.left = node2_1
    node2_1.left = node2_2
    root2.right = node2_3

    # First tree:
    #  10
    # 3  13


    # Second tree: 
    #      20
    #   10   22
    # 7

    # Merged Tree:
    #    10
    #  3    20
    #   7  13  22
    # Expected result (infix print): 3 7 10 13 20 22
    printTreeInfix(mergeTwoBST(root1, root2))

main()