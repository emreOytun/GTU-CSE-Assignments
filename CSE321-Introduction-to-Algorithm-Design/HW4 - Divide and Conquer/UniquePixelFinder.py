def findUniquePixel(arr) :
    if (arr == None) :
        return None
    
    # Search through the inner elements and check unique pixel.
    for i in range(1, len(arr) - 1) :
        for j in range(1, len(arr[0]) - 1) :
            if (arr[i][j] > arr[i][j+1]) and (arr[i][j] > arr[i][j-1]) and (arr[i][j] > arr[i-1][j]) and (arr[i][j] > arr[i+1][j]) :
                return arr[i][j]
            
    # Search through the elements in the matrix sides except corners.  
    # Search through first and last row side elements.
    lastRowIdx = len(arr) - 1
    for j in range(1, len(arr[0]) - 1) :
        if (arr[0][j] > arr[0][j+1]) and (arr[0][j] > arr[0][j-1]) and (arr[0][j] > arr[1][j]) :
            return arr[0][j]
        if (arr[lastRowIdx][j] > arr[lastRowIdx][j+1]) and (arr[lastRowIdx][j] > arr[lastRowIdx][j-1]) and (arr[lastRowIdx][j] > arr[lastRowIdx-1][j]) :
            return arr[lastRowIdx][j]
        
    # Search through first and last col side elements.
    lastColIdx = len(arr[0]) - 1
    for i in range(1, len(arr) - 1) :
        if (arr[i][0] > arr[i-1][0]) and (arr[i][0] > arr[i+1][0]) and (arr[i][0] > arr[i][1]) :
            return arr[i][0]
        if (arr[i][lastColIdx] > arr[i-1][lastColIdx]) and (arr[i][lastColIdx] > arr[i+1][lastColIdx]) and (arr[i][lastColIdx] > arr[i][lastColIdx-1]) :
            return arr[i][0]
    
    # Search in corners.
    # Check top-leftmost corner.
    if (arr[0][0] > arr[0][1]) and (arr[0][0] > arr[1][0]) :
        return arr[0][0]
    
    # Check top-rightmost corner.
    if (arr[0][lastColIdx] > arr[0][lastColIdx-1]) and (arr[0][lastColIdx] > arr[1][lastColIdx]) : 
        return arr[0][lastColIdx]
    
    # Check bottom-leftmost corner.
    if (arr[lastRowIdx][0] > arr[lastRowIdx-1][0]) and (arr[lastRowIdx][0] > arr[lastRowIdx][1]) :
        return arr[lastRowIdx][0]
    
    # Check bottom-rightmost corner.
    if (arr[lastRowIdx][lastColIdx] > arr[lastRowIdx-1][lastColIdx]) and (arr[lastRowIdx][lastColIdx] > arr[lastRowIdx][lastColIdx-1]) :
        return arr[lastRowIdx][lastColIdx]
    
def main() :
    arr = [
        [1, 3, 4, 6],
        [2, 4, 10, 12],
        [3, 5, 20, 14],
        [4, 6, 8, 18] 
        ]

    print("Unique element: ", findUniquePixel(arr))

main()