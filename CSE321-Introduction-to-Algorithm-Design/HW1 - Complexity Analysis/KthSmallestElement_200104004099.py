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

# K should be equal or greater than 1.
# 1) Check the k's value.
# 2) Get the tree elements in a sorted array.
# 3) Find the k-th element if it is available, otherwise return None.
def findKthSmallestElement(root, k):
    if (k <= 0):
        return None

    sortedArr = []
    getTreeElementsSorted(root, sortedArr)

    if (k > len(sortedArr)):
        return None
    return sortedArr[k - 1]

def main():
    root1 = Node(10)
    node1_1 = Node(3)
    node1_2 = Node(13)
    node1_3 = Node(25)

    root1.left = node1_1
    root1.right = node1_2
    node1_2.right = node1_3

    print(findKthSmallestElement(root1, 2))

main()