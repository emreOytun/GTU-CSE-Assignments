from functools import cmp_to_key

# Checks whether the point is above or below the line a - b.
def pointsArrangement(a, b, c) :
    result = (b[1] - a[1]) * (c[0] - b[0]) - (c[1] - b[1]) * (b[0] - a[0])
    if (result < 0) : return -1
    if (result > 0) : return 1
    return 0

centerPoint = [0, 0]

# Compare points and return -1 if point1 is clockwise side of point2.
def comparePoint(point1, point2) :
    points1 = [point1[0] - centerPoint[0], point1[1] - centerPoint[1]]
    points2 = [point2[0] - centerPoint[0], point2[1] - centerPoint[1]]
    if (points1[1] * points2[0] - points2[1] * points1[0] < 0) :
        return -1
    return 1

def sortPointsAntiClockWise(result) :
    # Sorting the points in the anti-clockwise order
    global centerPoint
    centerPoint = [0, 0]
    size = len(result)
    for i in range(0, size) :
        centerPoint[0] += result[i][0]
        centerPoint[1] += result[i][1]
    centerPoint[0] /= size
    centerPoint[1] /= size
    result = sorted(result, key=cmp_to_key(comparePoint))
    return result

# Exhasutive search algorithm to find the points on convex hull's segments.
# Find all pair of points and check if all remaining points are in one side of the line constructed by these two points.
def findConvexPointsExhaustive(points) :
    unique_points = set()
    for i in range(0, len(points)) :
        for j in range(i + 1, len(points)) :
            x1 = points[i][0] 
            x2 = points[j][0]
            
            y1 = points[i][1]
            y2 = points[j][1]
            
            a1 = y1 - y2
            b1 = x2 - x1
            c1 = x1 * y2 - y1 * x2
            
            positive = 0
            negative = 0
            for k in range(0, len(points)):
                if (k == i) or (k == j) :
                    negative += 1
                    positive += 1
                elif (a1 * points[k][0] + b1 * points[k][1] + c1 <= 0) :
                    negative += 1
                elif (a1 * points[k][0] + b1 * points[k][1] + c1 >= 0) :
                    positive += 1
                    
            if (positive == len(points)) or (negative == len(points)) :
                unique_points.add(tuple(points[j]))
                unique_points.add(tuple(points[i]))

    result = []
    for unique_point in unique_points :
        result.append(list(unique_point))

    result.sort()
    return sortPointsAntiClockWise(result)

# Find upper tangent points on the given points of left and right convexes.
def findUpperTangent(indexLeft, indexRight, leftConvexPoints, rightConvexPoints) :
    leftSize, rightSize = len(leftConvexPoints), len(rightConvexPoints)
    done = False
    while (not done) :
        done = True
        while (pointsArrangement(leftConvexPoints[indexLeft], rightConvexPoints[indexRight], rightConvexPoints[(indexRight + rightSize - 1) % rightSize]) <= 0) :
            indexRight = (indexRight + rightSize - 1) % rightSize
        while (pointsArrangement(rightConvexPoints[indexRight], leftConvexPoints[indexLeft], leftConvexPoints[(indexLeft + 1) % leftSize]) >= 0) :
            indexLeft = (indexLeft + 1) % leftSize
            done = False
    return indexLeft, indexRight

# Find lower tangent points on the given points of left and right convexes.
def findLowerTangent(indexLeft, indexRight, leftConvexPoints, rightConvexPoints) :
    leftSize, rightSize = len(leftConvexPoints), len(rightConvexPoints)
    done = False
    while (not done) :
        done = True
        while (pointsArrangement(leftConvexPoints[indexLeft], rightConvexPoints[indexRight], rightConvexPoints[(indexRight + 1) % rightSize]) >= 0) :
            indexRight = (indexRight + 1) % rightSize
        while (pointsArrangement(rightConvexPoints[indexRight], leftConvexPoints[indexLeft], leftConvexPoints[(indexLeft + leftSize - 1) % leftSize]) <= 0) :
            indexLeft = (indexLeft - 1) % leftSize
            done = False
    return indexLeft, indexRight

# Finds upper and lower tangent points and merges the left and right convexes.
def mergeTwoConvex(leftConvexPoints, rightConvexPoints) :
    sizeLeft, sizeRight = len(leftConvexPoints), len(rightConvexPoints)
    right_most_index_leftConvex, left_most_index_rightConvex = 0, 0

    for i in range(1, sizeLeft) :
        if (leftConvexPoints[i][0] > leftConvexPoints[right_most_index_leftConvex][0]) :
            right_most_index_leftConvex = i

    for i in range(1, sizeRight) :
        if (rightConvexPoints[i][0] < rightConvexPoints[left_most_index_rightConvex][0]) :
            left_most_index_rightConvex = i

    topLeft, topRight = findUpperTangent(right_most_index_leftConvex, left_most_index_rightConvex, leftConvexPoints, rightConvexPoints)    
    bottomLeft, bottomRight = findLowerTangent(right_most_index_leftConvex, left_most_index_rightConvex, leftConvexPoints, rightConvexPoints)

    result = []    
    leftIndex = topLeft
    result.append(leftConvexPoints[topLeft])
    while (leftIndex != bottomLeft) :
        leftIndex = (leftIndex + 1) % sizeLeft
        result.append(leftConvexPoints[leftIndex])

    rightIndex = bottomRight
    result.append(rightConvexPoints[bottomRight])
    while (rightIndex != topRight) :
        rightIndex = (rightIndex + 1) % sizeRight
        result.append(rightConvexPoints[rightIndex])
    return result

def findConvexPointsRec(points) :
    if (len(points) <= 5) :
        return findConvexPointsExhaustive(points)

    start = len(points) // 2
    left_hull = findConvexPointsRec(points[0:start])
    right_hull = findConvexPointsRec(points[start:len(points)])
    return mergeTwoConvex(left_hull, right_hull)

# First sort the points according to x and pass them to recursive function.
def findMinWrappingSensors(points) :
    points.sort()
    return len(findConvexPointsRec(points))

def main() :
    input_points = []
    input_points.append([0, 0])
    input_points.append([3, -4])
    input_points.append([1, -5])
    input_points.append([7, -3])
    input_points.append([2, -1])
    input_points.append([-5, -5])
    input_points.append([6, 4])
    input_points.append([-2, -1])
    input_points.append([-1, 1])
    input_points.append([3, 7])
    input_points.append([0, 7])

    print(findMinWrappingSensors(input_points))

main()