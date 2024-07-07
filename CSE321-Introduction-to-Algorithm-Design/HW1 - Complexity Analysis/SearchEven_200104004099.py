# Returns None if there are no even elements.
def searchEven(arr) :
    for num in arr :
        if num % 2 == 0 :
            return num
    return None

def main() :
    arr = [1, 3, 2, 9, 8]
    print(searchEven(arr))

    arr2 = [1, 3, 5, 7]
    print(searchEven(arr2))
     
main()