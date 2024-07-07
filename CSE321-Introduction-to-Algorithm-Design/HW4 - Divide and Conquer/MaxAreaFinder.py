def findMaxArea(intervalValueArr, lowerBound, upperBound):
    if (intervalValueArr == None or len(intervalValueArr) == 0) :
        return float('-inf') 

    curSum = 0;
    curSumLeftIdx = lowerBound
    curSumRightIdx = -1

    maxSum = intervalValueArr[lowerBound]
    maxSumLeftIdx = lowerBound
    maxSumRightIdx = lowerBound
    for i in range(lowerBound, upperBound + 1) :
        curSum += intervalValueArr[i];
        curSumRightIdx = i
        if (curSum > maxSum) :
            maxSum = curSum;
            maxSumLeftIdx = curSumLeftIdx
            maxSumRightIdx = curSumRightIdx
        if (curSum < 0) :
            curSum = 0;
            curSumLeftIdx = i + 1
    
    return maxSumLeftIdx, maxSumRightIdx, maxSum;

def main():
    intervalValueArr = [0, 2, 1, 2, -2, 1]
    leftBound, rightBound, max = findMaxArea(intervalValueArr, 1, 4)
    print("[" + str(leftBound) + "," + str(rightBound) + "]" + " Max Area: " + str(max))

main()