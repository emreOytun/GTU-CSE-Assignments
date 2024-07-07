package version2;

import java.util.ArrayList;
import java.util.List;

/**
 * Tests the system for Scenario-2.
 */
public class TestClass2 {
   
    public static void main(String[] args) {
    
        /** Keeps all the account that have been signed up. */
        List<Account> accounts = new ArrayList<>();

        System.out.println("CSE222 - HW3 \n");

        /* SCENARIO-1 ACTIONS BEFORE SCENARIO-2 TO BE CONSISTENT: */
        Account gizemsungu = new Account("gizemsungu", "14.05.1993", "Kocaeli");
        Account sibelgulmez = new Account("sibelgulmez", "10.03.1995", "Istanbul");
        Account gokhankaya = new Account("gokhankaya", "17.05.1990", "Gebze");
        gizemsungu.signUp(accounts);
        sibelgulmez.signUp(accounts);
        gokhankaya.signUp(accounts);
        System.out.println();
        
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

    

        System.out.print("Step 1... ");
        System.out.println("Logging into another account (username: gizemsungu)...");
        gizemsungu.login(accounts);
        System.out.println();
        
        System.out.print("Step 1-a... ");
        System.out.println("Sharing a post...");
        gizemsungu.sharePost(accounts, "Post1.");
        System.out.println();
        
        System.out.print("Step 1-b... ");
        System.out.println("Sharing another post...");
        gizemsungu.sharePost(accounts, "Post2");
        System.out.println();

        System.out.print("Step 1-c... ");
        System.out.println("Logging out from account 'gizemsungu'..");
        gizemsungu.logout();
        System.out.println();

        System.out.print("Step 2... ");
        System.out.println("Logging into another account (username: sibelgulmez)...");
        sibelgulmez.login(accounts);
        System.out.println();
        
        System.out.print("Step 2-a... ");
        System.out.println("Viewing gizemsungu's profile...");
        sibelgulmez.viewAccount(gizemsungu);

        System.out.print("Step 2-b... ");
        System.out.println("Liking Post1...");
        sibelgulmez.likePost(accounts, 3);
        System.out.println();
        
        System.out.print("Step 2-c... ");
        System.out.println("Logging out from account 'sibelgulmez'..");
        sibelgulmez.logout();
        System.out.println();

        System.out.print("Step 3... ");
        System.out.println("Logging into another account (username: gokhankaya)...");
        gokhankaya.login(accounts);
        System.out.println();
        
        System.out.print("Step 3-a... ");
        System.out.println("Viewing gizemsungu's account...");
        gokhankaya.viewAccount(gizemsungu);

        System.out.print("Step 3-b... ");
        System.out.println("Commenting on Post2...");
        gokhankaya.makeComment(accounts, 4, "Nice!");
        System.out.println();

        System.out.print("Step 3-c... ");
        System.out.println("Sending a message to gizemsungu...");
        gokhankaya.sendMessage(accounts, gizemsungu, "Hello!");
        System.out.println();
        
        System.out.print("Step 3-d... ");
        System.out.println("Logging out from account 'gokhankaya'..");
        gokhankaya.logout();
        System.out.println();

        System.out.print("Step 4...");
        System.out.println("Logging into another account (username: gizemsungu)...");
        gizemsungu.login(accounts);
        System.out.println();

        System.out.print("Step 4-a...");
        System.out.println("Viewing gizemsungu's profile...");
        gizemsungu.viewAccount(gizemsungu);
        
        System.out.print("Step 4-b...");
        System.out.println("Viewing inbox...");
        gizemsungu.viewInbox(accounts);
        System.out.println();

    }
}
