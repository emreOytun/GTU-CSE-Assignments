def findFlawFuse(fuseArr):
    i = min(10, len(fuseArr) - 1)
    while (i < (len(fuseArr) - 1) and fuseArr[i] == 1) :
        i = min(i + 10, len(fuseArr) - 1)

    while (i >= 0 and fuseArr[i] == 0) : 
        i = i - 1
    
    return i + 1

def main():
    fuseArr = [1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0]
    print(findFlawFuse(fuseArr))

main()   