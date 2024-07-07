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

# The range: [a,b] (included)
# Returns empty list if there is none.
# 1) Get tree elements sorted in a sorted array by iterating over the tree.
# 2) Select the elements by iterating the sorted array.
def findElementsInRange(root, a, b):
    if (a > b):
        return []

    sortedArr = []
    getTreeElementsSorted(root, sortedArr)

    resultArr = []
    isDone = False
    idx = 0
    while (not isDone and idx < len(sortedArr)):
        if (sortedArr[idx] > b):
            isDone = True
        elif (a <= sortedArr[idx]):
            resultArr.append(sortedArr[idx])
        idx = idx + 1
    
    return resultArr

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

    print(findElementsInRange(root1, 5, 19))

main()