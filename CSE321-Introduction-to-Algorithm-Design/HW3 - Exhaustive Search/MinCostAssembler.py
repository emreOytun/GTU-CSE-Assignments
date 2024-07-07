minCost = float('inf')
minSequence = None

def minCostAssembler(costMatrix):
    remainingParts = []
    sequence = []
    for i in range(0, len(costMatrix)):
        remainingParts.append(i)
        sequence.append(i)

    # Initialize minCost as infinite.
    global minCost
    global minSequence
    minCost = float('inf')
    minSequence = None

    # Assumption: From question, I understand that energy cost is between two assemble parts. Therefore, I assume there's
    # no energy cost for the first part.
    # 0-th index(first assemble part) has no cost. So, try all of the parts as first part and call the recursive method
    # for all of them so to try all possibilities.
    for i in range(0, len(costMatrix)):
        sequence[0] = remainingParts[i]
        swap(remainingParts, i, 0)
        minCostAssemblerHelper(costMatrix, 0, sequence, remainingParts, 0)
        swap(remainingParts, i, 0)
    return minCost, minSequence

def minCostAssemblerHelper(costMatrix, totalCost, sequence, remainingParts, curPart):
    if (curPart >= len(costMatrix) - 1):
        global minCost
        global minSequence
        if (totalCost < minCost) :
            minCost = totalCost
            minSequence = sequence[:]
        return

    # Try all possibilities for the next part.
    for nextPart in range (curPart + 1, len(remainingParts)):
        sequence[curPart + 1] = remainingParts[nextPart]
        swap(remainingParts, curPart + 1, nextPart)
        minCostAssemblerHelper(costMatrix, totalCost + costMatrix[sequence[curPart]][sequence[curPart+1]], sequence, remainingParts, curPart + 1)
        swap(remainingParts, curPart + 1, nextPart)
    return

def swap(arr, idx1, idx2):
    temp = arr[idx1]
    arr[idx1] = arr[idx2]
    arr[idx2] = temp

def main():
    costMatrix = [
                    [float('inf'), 7, 3],
                    [1, float('inf'), 4],
                    [5, 6, float('inf')]
                ];

    cost, sequence = minCostAssembler(costMatrix)
    print("", cost, sequence)

main()