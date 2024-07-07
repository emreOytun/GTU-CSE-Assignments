package homework1;

/**
 * Tests the system for Scenario-3.
 */
public class TestClass3 {
   
    public static void main(String[] args) {
       
        /** Keeps all the account that have been signed up. */
        Account[] accounts = new Account[500];

        System.out.println("CSE222 - HW1 \n");

        Account gizemsungu = new Account("gizemsungu", "14.05.1993", "Kocaeli");
        Account sibelgulmez = new Account("sibelgulmez", "10.03.1995", "Istanbul");
        Account gokhankaya = new Account("gokhankaya", "17.05.1990", "Gebze");
        gizemsungu.signUp(accounts);
        sibelgulmez.signUp(accounts);
        gokhankaya.signUp(accounts);
        System.out.println();


        /* SCENARIO-1/2 ACTIONS BEFORE SCENARIO-3 TO BE CONSISTENT: */
        sibelgulmez.login(accounts);
        sibelgulmez.sharePost(accounts, "I like Java.");
        sibelgulmez.sharePost(accounts, "Java the coffee...");
        sibelgulmez.follow(accounts, gizemsungu);
        sibelgulmez.follow(accounts, gokhankaya);
        sibelgulmez.logout();
        
        gokhankaya.login(accounts);
        gokhankaya.likePost(accounts, 1);
        gokhankaya.makeComment(accounts, 1, "me too!");
        gokhankaya.follow(accounts, sibelgulmez);
        gokhankaya.follow(accounts, gizemsungu);
        gokhankaya.sendMessage(accounts, gizemsungu, "This homework is too easy!");
        gokhankaya.logout();
        
        gizemsungu.login(accounts);
        gizemsungu.likePost(accounts, 1);
        gizemsungu.likePost(accounts, 2);
        gizemsungu.logout();

        gizemsungu.login(accounts);
        gizemsungu.sharePost(accounts, "Post1.");
        gizemsungu.sharePost(accounts, "Post2");
        gizemsungu.logout();

        sibelgulmez.login(accounts);
        sibelgulmez.likePost(accounts, 3);
        sibelgulmez.logout();

        gokhankaya.login(accounts);
        gokhankaya.makeComment(accounts, 4, "Nice!");
        gokhankaya.sendMessage(accounts, gizemsungu, "Hello!");
        gokhankaya.logout();



        System.out.print("Step 1...");
        System.out.println("Logging into another account (username: gizemsungu)...");
        gizemsungu.login(accounts);
        System.out.println();

        System.out.print("Step 1-a...");
        System.out.println("Blocking sibelgulmez...");
        gizemsungu.blockAccount(sibelgulmez);
        System.out.println();

        System.out.print("Step 1-b...");
        System.out.println("Logging out from account 'gizemsungu'..");
        gizemsungu.logout();
        System.out.println();

        System.out.print("Step 2...");
        System.out.println("Logging into another account (username: sibelgulmez)...");
        sibelgulmez.login(accounts);
        System.out.println();

        System.out.print("Step 2-a...");
        System.out.println("Viewing gizemsungu's profile...");
        sibelgulmez.viewAccount(gizemsungu);
        System.out.println();

        System.out.print("Step 2-b...");
        System.out.println("Trying to send message to gizemsungu");
        sibelgulmez.sendMessage(accounts, gizemsungu, "Hey there!");
        System.out.println();
        
    }
}
