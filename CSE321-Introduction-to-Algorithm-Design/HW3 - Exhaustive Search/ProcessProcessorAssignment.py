minCost = float('inf')
minCostAssignment = None

# costMatrix is n*n matrix. Rows indicate processors, columns indicate processes. 
# Intersection of a row-column indicates cost of this column(process) for this row(processor).
def minCostAssignment(costMatrix):
    if (costMatrix == None):
        return None
    
    # Initialize the array which contains assignment of processes to processors. (i-th index of assignments array means i-th process.)
    assignments = []
    for i in range(0, len(costMatrix)):
        assignments.append(-1)

    # Initialize the array which contains the remaining processes.    
    remainingProcesses = []
    for i in range(0, len(costMatrix)):
        remainingProcesses.append(i)
    
    # Initialize the minCost as infinite.
    global minCost
    global minCostAssignment
    minCost = float('inf')
    minCostAssignment = None
    minCostAssignmentHelper(costMatrix, assignments, remainingProcesses, 0)
    return minCost, minCostAssignment

def minCostAssignmentHelper(costMatrix, assignments, remainingProcesses, curJob):
    if (curJob == len(costMatrix)):
        cost = calculateCost(costMatrix, assignments)

        global minCost
        global minCostAssignment
        if (cost < minCost):
            minCost = cost
            minCostAssignment = assignments[:]
        return
    
    # Generate all possible combinations for current job.
    # curJob = curProcessIdx
    for i in range(curJob, len(remainingProcesses)):
        processIdx = remainingProcesses[i]
        assignments[processIdx] = curJob
        swap(remainingProcesses, curJob, i)
        minCostAssignmentHelper(costMatrix, assignments, remainingProcesses, curJob + 1)
        swap(remainingProcesses, curJob, i)

def calculateCost(costMatrix, assignments):
    cost = 0
    for i in range(len(assignments)):
        cost = cost + costMatrix[assignments[i]][i]
    return cost

def swap(arr, idx1, idx2):
    temp = arr[idx1]
    arr[idx1] = arr[idx2]
    arr[idx2] = temp
    

def main():
    matrix = [
        [1, 10, 20],
        [4, 5, 3],
        [8, 2, 9]
    ]

    # assignment array contains the processor indexes matched with each process.
    # assignment = [0, 2, 1] means 0.process-0.processor, 1.process-2.processor, 2.process-1.processor
    cost, assignment = minCostAssignment(matrix)
    print("", cost, assignment) 
    
main()
    