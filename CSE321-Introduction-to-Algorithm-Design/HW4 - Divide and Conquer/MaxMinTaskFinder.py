def findMaxMinTasks(taskResourcesArr) :
    if (taskResourcesArr == None) :
        return float('inf')
    
    return findMaxMinTasksHelper(taskResourcesArr, 0, len(taskResourcesArr) - 1)

# Recursive helper method to divide the array and combine the results.
def findMaxMinTasksHelper(taskResourcesArr, li, hi) :
    if (li >= hi) :
        return taskResourcesArr[li], taskResourcesArr[li]
    
    mid = (li + hi) // 2
    leftMin, leftMax = findMaxMinTasksHelper(taskResourcesArr, li, mid)
    rightMin, rightMax = findMaxMinTasksHelper(taskResourcesArr, mid+1, hi)
    return min(leftMin, rightMin), max(leftMax, rightMax)

def main() :
    taskResourcesArr = [3, 5, 1, 2, 4, 5, 2, 2, 10, 1000]
    print("Max-Min Task Resource: ", findMaxMinTasks(taskResourcesArr))


main()