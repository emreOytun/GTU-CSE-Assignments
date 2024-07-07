/**
 * A class to make username controls.
 * @author Emre Oytun
 */
public class UsernameSecurity extends Security {
    
    /**
     * Checks if the given username is valid according to condisitons below:
     * 1) Username should have at least 1 character.
     * 2) Username should have letters only.
     * @param username The username that will be checked.
     * @return A boolean indacating if the username is valid.
     */
    public boolean checkIfValidUsername(String username) { 
        if (username == null || username.length() < 1) {
            failMessage = "The username is invalid. It should have at least 1 character.";
            return false;
        }
        boolean result = checkIfValidUsername(username, 0);
        if (!result) failMessage = "The username is invalid. It should have letters only.";
        return result;
    }

    /**
     * Checks if the given username only contains letters.
     * @param username The username that will be checked.
     * @param curIndex The current index that indicates at which index this recursive call operates.
     * @return A boolean indicating if the username is valid or not.
     */
    private boolean checkIfValidUsername(String username, int curIndex) {
        if (curIndex >= username.length()) return true;
        Character ch = username.charAt(curIndex);
        if (!Character.isAlphabetic(ch)) return false;
        return checkIfValidUsername(username, curIndex + 1);
    }

}
