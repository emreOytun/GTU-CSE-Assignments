/**
 * A class to make password2 controls.
 * @author Emre Oytun
 */
public class Password2Security extends Security {
    
    /**
     * Checks if the given password2 is valid according to the condition below.
     * If password2 is in between 10 and 10000, then it is valid.
     * @param password2 The password2 that will be checked.
     * @return A boolean indicating if the password2 is valid.
     */
    public boolean checkIfValidPassword2(int password2) {
        if (!(10 < password2 && password2 < 10000)) {
            failMessage = "The password2 is invalid. It should be between 10 and 10,000.";
            return false;
        }
        return true;
    }
    
    /**
     * Checks if the password2 can be obtained as the sum of denominations multiplied by arbitrary coefficients.
     * @param password2 The password2 that will be checked.
     * @param denominations The denominations list containing non-negative integers.
     * @return A boolean indicating if the password2 can be obtained or not.
     */
    public boolean isExactDivision(int password2, int[] denominations) {
        if (denominations == null) {
            failMessage = "The password2 is invalid. Denominations array is null.";
            return false;
        }
        boolean result = isExactDivision(password2, denominations, 0);
        if (!result) failMessage = "The password2 is invalid. It is not compatible with the denominations.";
        return result;
    }

    /**
     * Recursive function to check if it can make the remaining 0 using the denominations.
     * @param remaining The remaining that is formed by substracting the denominations.
     * @param denominations The denominations list.
     * @param curIndex The current index at which this recursive calls operate.
     * @return A boolean indicating if remaining can be made 0 or not.
     */
    private boolean isExactDivision(int password2, int[] denominations, int curIndex) {
        if (password2 == 0) {
            return true;
        }
        if (password2 < 0 || curIndex >= denominations.length) return false;

        boolean result1 = isExactDivision(password2 - denominations[curIndex], denominations, curIndex);
        if (result1) return true;

        return isExactDivision(password2, denominations, curIndex + 1);
    }

}