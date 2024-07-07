/**
 * Test the security functions.
 * @author Emre Oytun
 */
public class Main {

    public static void secure(String username1, String password1, int password2) {
        int[] DENOMINATION_LIST = new int[] {4, 17, 29};
        UsernameSecurity usernameSecurity = new UsernameSecurity();
        Password1Security password1Security = new Password1Security();
        Password2Security password2Security = new Password2Security();

        if (!usernameSecurity.checkIfValidUsername(username1)) {
            System.out.println(usernameSecurity.getFailMessage());
        }
        else if (!password1Security.checkIfValidPassword1(password1)) {
            System.out.println(password1Security.getFailMessage());
        }
        else if (!password1Security.containsUserNameSpirit(username1, password1)) {
            System.out.println(password1Security.getFailMessage());
        }
        else if (!password1Security.isBalancedPassword(password1)) {
            System.out.println(password1Security.getFailMessage());
        }
        else if (!password1Security.isPalindromePossible(password1)) {
            System.out.println(password1Security.getFailMessage());
        }
        else if (!password2Security.checkIfValidPassword2(password2)) {
            System.out.println(password2Security.getFailMessage());
        }
        else if (!password2Security.isExactDivision(password2, DENOMINATION_LIST)) {
            System.out.println(password2Security.getFailMessage());
        }
        else {
            System.out.println("The username and passwords are valid. The door is opening, please wait.");
        }
    }

    public static void main(String[] args) {
        String username = null;
        String password1 = null;
        int password2;

        System.out.println("Test1... Inputs:");
        System.out.println("username:'sibelgulmez' - password1:'[rac()ecar]' - password2:'74' ");
        username = "sibelgulmez";
        password1 = "[rac()ecar]";
        password2 = 74;
        secure(username, password1, password2);
        System.out.println();

        System.out.println("Test2... Inputs:");
        System.out.println("username:'' - password1:'[rac()ecar]' - password2:'74' ");
        username = "";
        password1 = "[rac()ecar]";
        password2 = 74;
        secure(username, password1, password2);
        System.out.println();

        System.out.println("Test3... Inputs:");
        System.out.println("username:'sibel1' - password1:'[rac()ecar]' - password2:'74' ");
        username = "sibel1";
        password1 = "[rac()ecar]";
        password2 = 74;
        secure(username, password1, password2);
        System.out.println();

        System.out.println("Test4... Inputs:");
        System.out.println("username:'sibel' - password1:'pass[]' - password2:'74' ");
        username = "sibel";
        password1 = "pass[]";
        password2 = 74;
        secure(username, password1, password2);
        System.out.println();

        System.out.println("Test5... Inputs:");
        System.out.println("username:'sibel' - password1:'abcdabcd' - password2:'74' ");
        username = "sibel";
        password1 = "abcdabcd";
        password2 = 74;
        secure(username, password1, password2);
        System.out.println();

        System.out.println("Test6... Inputs:");
        System.out.println("username:'sibel' - password1:'[[[[]]]]' - password2:'74' ");        
        username = "sibel";
        password1 = "[[[[]]]]";
        password2 = 74;
        secure(username, password1, password2);
        System.out.println();

        System.out.println("Test7... Inputs:");
        System.out.println("username:'sibel' - password1:'[no](no)' - password2:'74' ");
        username = "sibel";
        password1 = "[no](no)";
        password2 = 74;
        secure(username, password1, password2);
        System.out.println();
        
        System.out.println("Test8... Inputs:");
        System.out.println("username:'sibel' - password1:'[rac()ecar]]' - password2:'74' ");
        username = "sibel";
        password1 = "[rac()ecar]]";
        password2 = 74;
        secure(username, password1, password2);
        System.out.println();

        System.out.println("Test9... Inputs:");
        System.out.println("username:'sibel' - password1:'[rac()ecars]' - password2:'74' ");
        username = "sibel";
        password1 = "[rac()ecars]";
        password2 = 74;
        secure(username, password1, password2);
        System.out.println();

        System.out.println("Test10... Inputs:");
        System.out.println("username:'sibel' - password1:'[rac()ecar]' - password2:'5' ");
        username = "sibel";
        password1 = "[rac()ecar]";
        password2 = 5;
        secure(username, password1, password2);
        System.out.println();

        System.out.println("Test11... Inputs:");
        System.out.println("username:'sibel' - password1:'[rac()ecar]' - password2:'35' ");
        username = "sibel";
        password1 = "[rac()ecar]";
        password2 = 35;
        secure(username, password1, password2);
        System.out.println();

        System.out.println("Test12... Inputs:");
        System.out.println("username:'sibel' - password1:'[rac()ecar]' - password2:'74' ");
        username = "sibel";
        password1 = "[rac()ecar]";
        password2 = 74;
        secure(username, password1, password2);
        System.out.println();

    }
}
