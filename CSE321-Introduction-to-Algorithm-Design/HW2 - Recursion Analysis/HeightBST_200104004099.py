class Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None

def height_of_tree(bst) :
    result = height_of_tree_helper(bst)
    if (result == -1) :
        return 0
    return result

def height_of_tree_helper(bst) :
    if (bst == None) :
        return -1

    left_height = height_of_tree_helper(bst.left)
    right_height = height_of_tree_helper(bst.right)
    return max(left_height, right_height) + 1

def main() :

    root1 = None
    print("Height_of_tree result: ", height_of_tree(root1))
    
    # Second tree: 
    #        20
    #     10   22
    #   7
    #    25

    root2 = Node(20)
    node2_1 = Node(10)
    node2_2 = Node(7)
    node2_3 = Node(22)
    node2_4 = Node(25)

    root2.left = node2_1
    node2_1.left = node2_2
    node2_2.right = node2_4
    root2.right = node2_3

    print("Height_of_tree result: ", height_of_tree(root2))

main()
    