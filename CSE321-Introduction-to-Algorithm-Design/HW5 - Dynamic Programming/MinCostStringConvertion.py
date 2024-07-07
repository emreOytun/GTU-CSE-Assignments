from collections import deque

def minCostAndOperationsFinder(str1, str2) :
    dp = [[0 for j in range(len(str2) + 1)] for i in range(len(str1) + 1)]

    # Initialize DP table
    for i in range(0, len(str1)) :
        dp[i][0] = 0
    for i in range(0, len(str2)) :
        dp[0][i] = 0

    # Fill DP table
    # O(m*n)
    for i in range(1, len(str1) + 1) :
        for j in range(1, len(str2) + 1) : 
            if (str1[i-1] == str2[j-1]) :
                dp[i][j] = dp[i-1][j-1] + 1
            else :
                dp[i][j] = max(dp[i-1][j], dp[i][j-1])

    # Find the common characters
    # O(max(m, n))
    i = len(str1)
    j = len(str2)
    commonCharsStack1 = []
    commonCharsStack2 = []
    while (i > 0 and j > 0) :
        if (str1[i-1] == str2[j-1]) :
            commonCharsStack1.append(str1[i-1])
            commonCharsStack2.append(str1[i-1])
            i = i - 1
            j = j - 1
        elif (dp[i-1][j] > dp[i][j-1]) :
            i = i - 1
        else :
            j = j - 1
    
    # Find the characters to delete
    commonSequenceN = dp[len(str1)][len(str2)]
    minOperations = 0

    result = "Delete:"
    if (commonSequenceN > 0) :
        for i in range(0, len(str1)) :
            if (len(commonCharsStack1) != 0 and str1[i] == commonCharsStack1[len(commonCharsStack1) - 1]) :
                commonCharsStack1.pop()
            else : 
                result = result + " " + str1[i]
                minOperations = minOperations + 1
    
    result = result + " Insert:"
    if (commonSequenceN > 0) :
       for i in range(0, len(str2)) :
            if (len(commonCharsStack2) != 0 and str2[i] == commonCharsStack2[len(commonCharsStack2) - 1]) :
                commonCharsStack2.pop()
            else : 
                result = result + " " + str2[i]
                minOperations = minOperations + 1
    
    return minOperations, result

def main() :
    str1 = "ADGGHAT"
    str2 = "AAGGHTH"

    print(minCostAndOperationsFinder(str1, str2))

main()