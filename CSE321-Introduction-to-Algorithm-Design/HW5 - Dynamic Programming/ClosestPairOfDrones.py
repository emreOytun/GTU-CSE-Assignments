import math
import random

class Coordinate :
    def __init__(self, x, y) :
        self.x = x
        self.y = y
    
    def __str__(self) :
        return f"({self.x}, {self.y})"

def xKeyExtractor(coordinate) :
    return coordinate.x

def yKeyExtractor(coordinate) :
    return coordinate.y

def findMinDistanceBetweenDrones(coordinates) :
    if coordinates == None :
        return None

    sortedXList = sorted(coordinates, key=xKeyExtractor)
    sortedYList = sorted(coordinates, key=yKeyExtractor)

    return findMinDistanceRec(sortedXList, sortedYList, 0, len(coordinates) - 1)

def findMinDistanceRec(sortedXList, sortedYList, li, ri) :
    # Base case: Number of remaining points <= 3
    # O(1)
    n = ri - li + 1
    if n <= 3 :
        return exhaustiveSearch(sortedXList, li, ri)
    
    # Divide case
    mid = (li + ri) // 2

    leftSet = set()
    for i in range(li, mid + 1) :
        leftSet.add(sortedXList[i])

    sortedYListLeft = []
    sortedYListRight = []
    for i in range(0, n) :
        if (sortedYList[i] in leftSet) :
            sortedYListLeft.append(sortedYList[i])
        else :
            sortedYListRight.append(sortedYList[i])


    pair1, pair2, deltaLeft = findMinDistanceRec(sortedXList, sortedYListLeft, li, mid)
    pair3, pair4, deltaRight = findMinDistanceRec(sortedXList, sortedYListRight, mid + 1, ri)
    delta = min(deltaLeft, deltaRight)

    # Find the points whose x coordinates are in range [mid-delta, mid+delta]
    # O(N)
    midPoint = sortedXList[mid]
    pointsInStrip = []
    for i in range(0, n) :
        if (abs(sortedYList[i].x - midPoint.x) < delta) :
            pointsInStrip.append(sortedYList[i])

    # O(N)
    pair5, pair6, deltaMid = findMinDistanceInStrip(pointsInStrip, delta)
    minDistance = min(delta, deltaMid)
    if (minDistance == deltaLeft) : return pair1, pair2, minDistance
    if (minDistance == deltaRight) : return pair3, pair4, minDistance
    return pair5, pair6, minDistance

def findMinDistanceInStrip(pointsInStrip, delta) :
    minDistance = delta;
    pair1 = None
    pair2 = None

    # O(N)
    for i in range(0, len(pointsInStrip)) :
        # It'll have a constant running time according to the theory.
        # Max 16 iterations.
        j = i + 1
        while (j < len(pointsInStrip) and (pointsInStrip[j].y - pointsInStrip[i].y < minDistance)) :
            distance = findDistance(pointsInStrip[i], pointsInStrip[j])
            if (distance < minDistance) :
                minDistance = distance
                pair1 = pointsInStrip[i]
                pair2 = pointsInStrip[j]
            j = j + 1
    
    return pair1, pair2, minDistance;

def exhaustiveSearch(sortedXList, li, ri) :
    minDistance = float('inf')
    pair1 = None
    pair2 = None
    for i in range(li, ri + 1) :
        for j in range (i + 1, ri + 1) :
            distance = findDistance(sortedXList[i], sortedXList[j])
            if (distance < minDistance) :
                minDistance = distance
                pair1 = sortedXList[i]
                pair2 = sortedXList[j]
    return pair1, pair2, minDistance


def findDistance(point1, point2) :
    xDistance = abs(point1.x - point2.x)
    yDistance = abs(point1.y - point2.y)
    return math.sqrt(math.pow(xDistance, 2) + math.pow(yDistance, 2))

def main() :
    # Generate 50 random coordinates with integer values, increased variability, and an offset
    coordinates = [Coordinate(random.randint(1, 150), random.randint(1, 150) + 10) for _ in range(50)]

    pair1, pair2, minDistance = findMinDistanceBetweenDrones(coordinates)
    print(pair1)
    print(pair2)
    print(minDistance)

main()    
