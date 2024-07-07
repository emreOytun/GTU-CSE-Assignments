maxSequence = None
maxDiscount = float('inf')

# Assumption: set_of_stores is not None.
def findMaxDiscountStoreSequence(setOfAllStores):
    if (setOfAllStores == None) :
        return None
    
    # Initialize the sequence array
    setOfStores = []

    global maxSequence
    global maxDiscount
    maxSequence = None
    maxDiscount = float('-inf')
    maxDiscountSequenceHelper(setOfAllStores, setOfStores, 0);
    return maxSequence

def maxDiscountSequenceHelper(setOfAllStores, setOfStores, curIdx):
    # Check if it is done
    if (curIdx == len(setOfAllStores)) :
        if (not (len(setOfStores) == 0)) and (calc_discount(setOfStores) > maxDiscount):
            global maxSequence
            maxSequence = setOfStores[:]
        return
    
    # Firstly, try by putting the current element to the setOfStores array.
    setOfStores.append(setOfAllStores[curIdx])
    maxDiscountSequenceHelper(setOfAllStores, setOfStores, curIdx + 1)

    # Secondly, try without putting the current element to the setOfStores array.
    setOfStores.pop()
    maxDiscountSequenceHelper(setOfStores, setOfStores, curIdx + 1)    