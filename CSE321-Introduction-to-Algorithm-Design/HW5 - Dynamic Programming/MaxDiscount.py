def maxDiscount(stores) :
    # Initialize DP table
    dp = []
    for i in range(0, len(stores) + 1) :
        dp.append(0)

    for i in range(1, len(stores) + 1) :
        dp[i] = max(dp[i - 1], dp[i - 1] + calc_discount(stores[i - 1]))

    return dp[len(stores) + 1]