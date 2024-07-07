class Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None

def is_balanced(bst) :
    result = is_balanced_helper(bst)
    if (result != -1) :
        return True
    return False

# Return -1 if it is not balanced.
# Otherwise, return the number of nodes.
def is_balanced_helper(bst) :
    if (bst == None) :
        return 0
    
    left_result = is_balanced_helper(bst.left)
    right_result = is_balanced_helper(bst.right)
    
    if (left_result == -1 or right_result == -1) :
        return -1
    
    absDifference = abs(left_result - right_result)
    if (absDifference > 1) :
        return -1
    
    return left_result + right_result + 1

def main() :

    # Second tree: 
    #        20
    #     10   22
    #   7
    #   25

    root2 = Node(20)
    node2_1 = Node(10)
    node2_2 = Node(7)
    node2_3 = Node(22)
    node2_4 = Node(25)

    root2.left = node2_1
    node2_1.left = node2_2
    node2_2.right = node2_4
    root2.right = node2_3

    print("Isbalanced result: ", is_balanced(root2))

main()