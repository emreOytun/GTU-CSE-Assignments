# Returns -1 if reaching the target amount is not possible.
def minCoinsChange(coins, targetAmount):
    if targetAmount == 0:
        return 0
    
    # Try each coin as much as possible such that if it is possible to use a coin then use it and make a recursive call.
    minChange = float('inf')
    for i in range(0, len(coins)):
        if (coins[i] <= targetAmount):
            result = minCoinsChange(coins, targetAmount - coins[i])
            if ((result != -1) and (result + 1 < minChange)) :
                minChange = result + 1
    if (minChange != float('inf') and minChange != -1):
        return minChange
    return -1


def main():
    arr = [5, 10, 25] # sum=90, result=5 (25, 25, 25, 10, 5)
    # arr = [1,2,6,7,9] # sum=13, result=2 (9, 2)
    # arr = [2,4,6] # sum=7, result=-1
    print("result: ", minCoinsChange(arr, 90))

main()