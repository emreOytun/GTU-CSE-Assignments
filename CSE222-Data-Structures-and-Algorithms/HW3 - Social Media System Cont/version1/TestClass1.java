package version1;

/**
 * Tests the system for Scenario-1.
 */
public class TestClass1 {
   
    public static void main(String[] args) {
        
        /** Keeps all the account that have been signed up. */
        Account[] accounts = new Account[500];

        System.out.println("CSE222 - HW3 \n");

        System.out.print("Step 1... ");
        System.out.println("Creating accounts...");
        Account gizemsungu = new Account("gizemsungu", "14.05.1993", "Kocaeli");
        Account sibelgulmez = new Account("sibelgulmez", "10.03.1995", "Istanbul");
        Account gokhankaya = new Account("gokhankaya", "17.05.1990", "Gebze");
        gizemsungu.signUp(accounts);
        sibelgulmez.signUp(accounts);
        gokhankaya.signUp(accounts);
        System.out.println();

        System.out.print("Step 2... ");
        System.out.println("Logging into an account (username: " + "sibelgulmez" + ")...");
        sibelgulmez.login(accounts);
        System.out.println();

        System.out.print("Step 3... ");
        System.out.println("Sharing two posts...");
        sibelgulmez.sharePost(accounts, "I like Java.");
        sibelgulmez.sharePost(accounts, "Java the coffee...");
        System.out.println();

        System.out.print("Step 4... ");
        System.out.println("Following gizemsungu and gokhankaya...");
        sibelgulmez.follow(accounts, gizemsungu);
        sibelgulmez.follow(accounts, gokhankaya);
        System.out.println();
        
        System.out.print("Step 5... ");
        System.out.println("Logging out from account 'sibelgulmez'...");
        sibelgulmez.logout();
        System.out.println();

        System.out.print("Step 6... ");
        System.out.println("Logging into another account (username: gokhankaya)...");
        gokhankaya.login(accounts);
        System.out.println();

        System.out.print("Step 7... ");
        System.out.println("Viewing sibelgulmez's profile...");
        gokhankaya.viewAccount(sibelgulmez);

        System.out.print("Step 8... ");
        System.out.println("Viewing sibulgulmez's posts...");
        gokhankaya.viewPosts(sibelgulmez);

        System.out.print("Step 9... ");
        System.out.println("Liking a post of sibelgulmez...");
        gokhankaya.likePost(accounts, 1);
        System.out.println();

        System.out.print("Step 10... ");
        System.out.println("Adding a comment on a post of sibelgulmez...");
        gokhankaya.makeComment(accounts, 1, "me too!");
        System.out.println();

        System.out.print("Step 11... ");
        System.out.println("Following sibelgulmez and gizemsungu...");
        gokhankaya.follow(accounts, sibelgulmez);
        gokhankaya.follow(accounts, gizemsungu);
        System.out.println();

        System.out.print("Step 12... ");
        System.out.println("Sending a message to gizemsungu...");
        gokhankaya.sendMessage(accounts, gizemsungu, "This homework is too easy!");
        System.out.println();

        System.out.print("Step 13... ");
        System.out.println("Logging out from account 'gokhankaya'..");
        gokhankaya.logout();
        System.out.println();

        System.out.print("Step 14... ");
        System.out.println("Logging into another account (username: gizemsungu)...");
        gizemsungu.login(accounts);
        System.out.println();

        System.out.print("Step 15... ");
        System.out.println("Checking outbox...");
        gizemsungu.checkOutbox();
        System.out.println();

        System.out.print("Step 16... ");
        System.out.println("Checking inbox...");
        gizemsungu.checkInbox();
        System.out.println();

        System.out.print("Step 17... ");
        System.out.println("Viewing inbox...");
        gizemsungu.viewInbox(accounts);
        System.out.println();

        System.out.print("Step 18... ");
        System.out.println("Viewing sibelgulmez's profile...");
        gizemsungu.viewAccount(sibelgulmez);

        System.out.print("Step 19... ");
        System.out.println("Viewing sibelgulmez's posts...");
        gizemsungu.viewPosts(sibelgulmez);

        System.out.print("Step 20... ");
        System.out.println("Viewing sibelgulmez's posts' interactions...");
        gizemsungu.viewInteractions(accounts, sibelgulmez);
        System.out.println();
        
        System.out.print("Step 21... ");
        System.out.println("Liking sibelgulmez's posts...");
        gizemsungu.likePost(accounts, 1);
        gizemsungu.likePost(accounts, 2);
        System.out.println();

        System.out.print("Step 22... ");
        System.out.println("Viewing sibelgulmez's posts' interactions...");
        gizemsungu.viewInteractions(accounts, sibelgulmez);
        System.out.println();   
    
    }

}
