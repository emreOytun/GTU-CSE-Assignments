import java.util.Stack;

/**
 * A class to make password1 controls.
 * @author Emre Oytun
 */
public class Password1Security extends Security {
    
    /**
     * Checks if the given password1 is valid according to the conditions below:
     * 1) Password1 should have at least 8 characters.
     * 2) Password1 should have letters and brackets only.
     * 3) Password1 should have at least 2 brackets.
     * 4) Password1 should at least 1 letter.
     * @param password1 The password1 that will be checked.
     * @return A boolean indicating the password1 is valid or not.
     */
    public boolean checkIfValidPassword1(String password1) {
        if (password1 == null) {
            failMessage = "The password1 is invalid. It should have at least 8 characters.";
            return false;
        }

        boolean result = true;
        int paranthesNumber = 0;
        int characterNumber = 0;
        
        for (int i = 0; i < password1.length() && result; ++i) {
            Character ch = password1.charAt(i);
            switch(ch) {
                case '(':
                case ')':
                case '[':
                case ']':
                case '{':
                case '}':
                    ++paranthesNumber;
                    break;
            
                default:
                    if (Character.isAlphabetic(ch)) {
                        ++characterNumber;
                    }
                    else {
                        result = false;
                    }
                    break;
            }
        }
        if (!result) {
            failMessage = "The password1 is invalid. It should have letters and brackets only.";
            return false;
        }
        if (paranthesNumber + characterNumber < 8) {
            failMessage = "The password1 is invalid. It should have at least 8 characters.";
            return false;
        }
        if (paranthesNumber < 2) {
            failMessage = "The password1 is invalid. It should have at least 2 brackets.";
            return false;
        }
        if (characterNumber == 0) {
            failMessage = "The password1 is invalid. It should have letters too.";
            return false;
        }
        return true;
    }

    /**
     * Checks if the password1 includes a character from the username.
     * @param username The username that will be used to control password1.
     * @param password1 The password that will be checked.
     * @return A boolean indicating if the password1 is valid or not.
     */
    public boolean containsUserNameSpirit(String username, String password1) {
        Stack<Character> stack = new Stack<>();
        for (int i = 0; i < username.length(); ++i) {
            stack.push(username.charAt(i));
        }
        boolean contains = false;
        while (!stack.isEmpty() && !contains) {
            if (password1.indexOf(stack.pop()) != -1) {
                contains = true;
            }
        }
        if (!contains) failMessage = "The password1 is invalid. It should have at least 1 character from the username.";
        return contains;
    }

    /**
     * Checks if the given password1 is balanced.
     * @param password1 The password1 that will be checked.
     * @return A boolean indicating if the password1 is valid or not.
     */
    public boolean isBalancedPassword(String password1) {
        String str = deleteCharacters(password1);
        Stack<Character> stack = new Stack<>();
        boolean isBalanced = true;
        for (int i = 0; i < str.length() && isBalanced; ++i) {
            Character ch = str.charAt(i);
            switch (ch) {

                case '(':
                case '[':
                case '{':
                    stack.push(ch);
                    break;

                case ')':
                case ']':
                case '}':
                    if (stack.isEmpty()) isBalanced = false;
                    else {
                        Character lastParanthesis = stack.pop();
                        if (getParanthesisPoint(ch) != getParanthesisPoint(lastParanthesis)) {
                            isBalanced = false;
                        }
                    }
                    break;
            }
        }
        if (!isBalanced) failMessage = "The password1 is invalid. It should be balanced.";
        return isBalanced;
    }

    /**
     * Gives numbers to each types of brackets.
     * @param ch The paranthes that will be numbered.
     * @return An integer representing the number of paranthes.
     */
    private int getParanthesisPoint(Character ch) {
        if (ch == '(' || ch == ')') return 1;
        if (ch == '[' || ch == ']') return 2;
        if (ch == '{' || ch == '}') return 3;
        return -1;
    }

    /**
     * Creates a new string by deleting characters from the given string.
     * @param str The string that will be used to create new string.
     * @return A string representing the character deleted version of the given string.
     */
    private String deleteCharacters(String str) {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < str.length(); ++i) {
            Character ch = str.charAt(i);
            if (!Character.isAlphabetic(ch)) sb.append(ch);
        }
        return sb.toString();
    }

    /** The count list of characters. */
    private int[] countList = null;
    
    /**
     * Checks if the given password1 can be rearranged so that it forms a palindrome.
     * @param password1 The password1 that will be checked if it can be form a palindrome.
     * @return A boolean indicating if the password1 is valid or not.
     */
    public boolean isPalindromePossible(String password1) {
        String str = deleteParanthesis(password1);
        countList = new int[26];
        boolean result = isPalindromePossible(str, 0);
        if (!result) failMessage = "The password1 is invalid. It should be possible to obtain a palindrome from the password1.";
        return result;
    }

    /**
     * Recursive function to check if the given string can be rearranged so that it forms a palindrome.
     * @param str The string that will be checked.
     * @param curIndex The current index at which the recursive call operates.
     * @return A boolean indicating if the given string can form a palindrome.
     */
    private boolean isPalindromePossible(String str, int curIndex) {
        // If it is at the end of the string, then check if it can be form a palindrome.
        if (curIndex >= str.length()) {
            return checkOddCharNumber();
        }

        // Increment the character count here.
        Character ch = str.charAt(curIndex);
        int charIndex = Character.toLowerCase(ch) - 'a';
        ++countList[charIndex];
        return isPalindromePossible(str, curIndex + 1);
    }

    /**
     * Check if a palindrome can be formed using the frequency list of characters according to below:
     * If there are characters more than 1 whose frequencies are odd number, then a palindrome cannot be formed.
     * Otherwise, a palindrome can be formed.
     * @return A boolean indicating if a palindrome can be formed.
     */
    private boolean checkOddCharNumber() {
        boolean oddBefore = false;
        boolean result = true;
        for (int i = 0; i < 26 && result; ++i) {
            if (countList[i] % 2 == 1) {
                if (oddBefore) result = false;
                else oddBefore = true;
            } 
        }
        return result;
    }

    /**
     * Deletes the paranthesis from the given string.
     * @param str The string that paranthesis will be removed from. 
     * @return A string created by deleting paranthesis from the given string.
     */
    private String deleteParanthesis(String str) {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < str.length(); ++i) {
            Character ch = str.charAt(i);
            if (Character.isAlphabetic(ch)) sb.append(ch);
        }
        return sb.toString();
    }
}
