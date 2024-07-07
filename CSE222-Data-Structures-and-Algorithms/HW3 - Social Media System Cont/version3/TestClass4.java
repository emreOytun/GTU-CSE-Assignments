package version3;

import java.util.LinkedList;
import java.util.List;

/**
 * Tests the system for Scenario-4.
 */
public class TestClass4 {

    public static void main(String[] args) {
                    
        /** Keeps all the account that have been signed up. */
        List<Account> accounts = new LinkedList<>();

        System.out.println("CSE222 - HW3 \n");

        System.out.print("Step 1... ");
        System.out.println("Creating accounts...");
        Account gizemsungu = new Account("gizemsungu", "14.05.1993", "Kocaeli");
        Account sibelgulmez = new Account("sibelgulmez", "10.03.1995", "Istanbul");
        Account gokhankaya = new Account("gokhankaya", "17.05.1990", "Gebze");
        Account emreoytun = new Account("emreoytun", "16.02.2001", "Istanbul");
        Account ali = new Account("ali61", "10.09.1997", "Trabzon");
        Account simge = new Account("simge10", "02.03.1988", "Balikesir");
        Account meryem = new Account("meryem", "03.07.2000", "Sivas");
        Account can = new Account("canoz", "17.05.2001", "Bursa");
        Account ahmet = new Account("ahmet21", "08.08.2008", "Rize");
        Account veli = new Account("veli", "10.10.1990", "Antalya");

        gizemsungu.signUp(accounts);
        sibelgulmez.signUp(accounts);
        gokhankaya.signUp(accounts);
        emreoytun.signUp(accounts);
        ali.signUp(accounts);
        simge.signUp(accounts);
        meryem.signUp(accounts);
        can.signUp(accounts);
        ahmet.signUp(accounts);
        veli.signUp(accounts);
        System.out.println();

        /************* UNLIKE TEST  **************/

        System.out.print("Step 2... ");
        System.out.println("Logging into an account (username: " + "emreoytun" + ")...");
        emreoytun.login(accounts);
        System.out.println();

        System.out.print("Step 3... ");
        System.out.println("Sharing two posts...");
        emreoytun.sharePost(accounts, "First post in new app.");
        emreoytun.sharePost(accounts, "Happy to announce i got the job!");
        System.out.println();

        System.out.print("Step 4... ");
        System.out.println("Following meryem...");
        emreoytun.follow(accounts, meryem); // For history logs.
        System.out.println();

        System.out.print("Step 5... ");
        System.out.println("Blocking can... ");
        emreoytun.blockAccount(can); // For history logs.
        System.out.println();

        System.out.print("Step 5... ");
        System.out.println("Logging out from account 'emreoytun'...");
        emreoytun.logout(); 
        System.out.println();

        System.out.print("Step 6... ");
        System.out.println("Logging into an account (username: " + "gizemsungu" + ")...");
        gizemsungu.login(accounts);
        System.out.println();

        System.out.print("Step 7... ");
        System.out.println("Liking posts of emreoytun...");
        gizemsungu.likePost(accounts, 1);
        gizemsungu.likePost(accounts, 2);
        System.out.println();

        System.out.print("Step 8... ");
        System.out.println("Logging out from account 'gizemsungu'...");
        gizemsungu.logout();
        System.out.println();

        System.out.print("Step 9... ");
        System.out.println("Logging into an account (username: " + "gokhankaya" + ")...");
        gokhankaya.login(accounts);
        System.out.println();

        System.out.print("Step 10... ");
        System.out.println("Liking post of emreoytun...");
        gokhankaya.likePost(accounts, 1);
        System.out.println();

        System.out.print("Step 11... ");
        System.out.println("Viewing emreoytun's profile...");
        gokhankaya.viewAccount(emreoytun);

        System.out.print("Step 12... ");
        System.out.println("Viewing emreoytun's posts' interactions...");
        gokhankaya.viewInteractions(accounts, emreoytun);
        System.out.println();

        System.out.print("Step 13... ");
        System.out.println("Logging out from account 'gokhankaya'...");
        gokhankaya.logout();
        System.out.println();

        System.out.print("Step 14... ");
        System.out.println("Logging into an account (username: " + "gizemsungu" + ")...");
        gizemsungu.login(accounts);
        System.out.println();

        System.out.print("Step 15... ");
        System.out.println("Unliking post of emreoytun...");
        gizemsungu.unlikePost(accounts, 1);
        System.out.println();

        System.out.print("Step 16... ");
        System.out.println("Logging out from account 'gizemsungu'...");
        gizemsungu.logout();
        System.out.println();
        
        System.out.print("Step 17... ");
        System.out.println("Logging into an account (username: " + "gokhankaya" + ")...");
        gokhankaya.login(accounts);
        System.out.println();

        System.out.print("Step 18... ");
        System.out.println("Unliking post of emreoytun...");
        gokhankaya.unlikePost(accounts, 1);
        System.out.println();

        System.out.print("Step 19... ");
        System.out.println("Viewing emreoytun's profile...");
        gokhankaya.viewAccount(emreoytun);

        System.out.print("Step 20.. ");
        System.out.println("Viewing emreoytun's posts' interactions...");
        gokhankaya.viewInteractions(accounts, emreoytun);
        System.out.println();

        System.out.print("Step 21... ");
        System.out.println("Logging out from account 'gokhankaya'...");
        gokhankaya.logout();
        System.out.println();


        /************* UNBLOCK TEST **************/        

        System.out.print("Step 22... ");
        System.out.println("Logging into an account (username: " + "sibelgulmez" + ")...");
        sibelgulmez.login(accounts);
        System.out.println();

        System.out.print("Step 23... ");
        System.out.println("Following ali...");
        sibelgulmez.follow(accounts, ali);
        System.out.println();

        System.out.print("Step 24... ");
        System.out.println("Sharing a post...");
        sibelgulmez.sharePost(accounts, "GTU is the best!");
        System.out.println();

        System.out.print("Step 25... ");
        System.out.println("Logging out from account 'sibelgulmez'...");
        sibelgulmez.logout();
        System.out.println();

        // For history logs.
        System.out.print("Step 26... ");
        System.out.println("Logging into an account (username: " + "emreoytun" + ")...");
        emreoytun.login(accounts);
        System.out.println();
        
        System.out.print("Step 27... ");
        System.out.println("Following sibelgulmez...");
        emreoytun.follow(accounts, sibelgulmez);
        System.out.println();

        System.out.print("Step 28... ");
        System.out.println("Liking the post of sibelgulmez...");
        emreoytun.likePost(accounts, 3);
        System.out.println();

        System.out.print("Step 29... ");
        System.out.println("Adding a comment on a post of sibelgulmez...");
        emreoytun.makeComment(accounts, 3, "It's hard though");
        System.out.println();

        System.out.print("Step 30... ");
        System.out.println("Blocking gokhankaya... ");
        emreoytun.blockAccount(gokhankaya);
        System.out.println();

        System.out.print("Step 31... ");
        System.out.println("Unblocking can... ");
        emreoytun.unblockAccount(can);
        System.out.println();

        System.out.print("Step 32... ");
        System.out.println("Unfollowing meryem...");
        emreoytun.unfollow(accounts, meryem);
        System.out.println();;

        System.out.print("Step 33... ");
        System.out.println("Logging out from account 'emreoytun'...");
        emreoytun.logout();
        System.out.println();

        System.out.print("Step 34... ");
        System.out.println("Logging into an account (username: " + "ali" + ")...");
        ali.login(accounts);
        System.out.println();

        System.out.print("Step 35... ");
        System.out.println("Following sibelgulmez...");
        ali.follow(accounts, sibelgulmez);
        System.out.println();

        System.out.print("Step 36... ");
        System.out.println("Adding a comment on a post of sibelgulmez...");
        ali.makeComment(accounts, 3, "I think so...");
        System.out.println();

        System.out.print("Step 37... ");
        System.out.println("Logging out from account 'ali'...");
        ali.logout();
        System.out.println();

        System.out.print("Step 38... ");
        System.out.println("Logging into an account (username: " + "simge" + ")...");
        simge.login(accounts);
        System.out.println();

        System.out.print("Step 39... ");
        System.out.println("Viewing sibelgulmez's profile...");
        simge.viewAccount(sibelgulmez);

        System.out.print("Step 40... ");
        System.out.println("Viewing sibelgulmez's posts' interactions...");
        simge.viewInteractions(accounts, sibelgulmez);
        System.out.println();

        System.out.print("Step 41... ");
        System.out.println("Logging out from account 'simge'...");
        simge.logout();
        System.out.println();

        System.out.print("Step 42... ");
        System.out.println("Logging into an account (username: " + "sibelgulmez" + ")...");
        sibelgulmez.login(accounts);
        System.out.println();

        System.out.print("Step 43... ");
        System.out.println("Blocking ali... ");
        sibelgulmez.blockAccount(ali);
        System.out.println();

        System.out.print("Step 44... ");
        System.out.println("Logging out from account 'sibelgulmez'...");
        sibelgulmez.logout();
        System.out.println();

        System.out.print("Step 45... ");
        System.out.println("Logging into an account (username: " + "ali" + ")...");
        ali.login(accounts);
        System.out.println();

        System.out.print("Step 46... ");
        System.out.println("Viewing sibelgulmez's profile...");
        ali.viewAccount(sibelgulmez);

        System.out.print("Step 47... ");
        System.out.println("Viewing sibelgulmez's posts' interactions...");
        ali.viewInteractions(accounts, sibelgulmez);
        System.out.println();

        System.out.print("Step 48... ");
        System.out.println("Liking posts of emreoytun...");
        ali.likePost(accounts, 2);
        System.out.println();

        System.out.print("Step 49... ");
        System.out.println("Logging out from account 'ali'...");
        ali.logout();
        System.out.println();

        System.out.print("Step 50... ");
        System.out.println("Logging into an account (username: " + "sibelgulmez" + ")...");
        sibelgulmez.login(accounts);
        System.out.println();

        System.out.print("Step 51... ");
        System.out.println("Unblocking ali... ");
        sibelgulmez.unblockAccount(ali);
        System.out.println();

        System.out.print("Step 52... ");
        System.out.println("Logging out from account 'sibelgulmez'...");
        sibelgulmez.logout();
        System.out.println();

        System.out.print("Step 53... ");
        System.out.println("Logging into an account (username: " + "ali" + ")...");
        ali.login(accounts);
        System.out.println();

        System.out.print("Step 54... ");
        System.out.println("Viewing sibelgulmez's profile...");
        ali.viewAccount(sibelgulmez);

        System.out.print("Step 55... ");
        System.out.println("Viewing sibelgulmez's posts' interactions...");
        ali.viewInteractions(accounts, sibelgulmez);
        System.out.println();

        System.out.print("Step 56... ");
        System.out.println("Logging out from account 'ali'...");
        ali.logout();
        System.out.println();

        /************* UNCOMMENT TEST  **************/        
        System.out.print("Step 57... ");
        System.out.println("Logging into an account (username: " + "meryem" + ")...");
        meryem.login(accounts);
        System.out.println();

        System.out.print("Step 58... ");
        System.out.println("Sharing a post...");
        meryem.sharePost(accounts, "New post in new site!");
        System.out.println();

        System.out.print("Step 59... ");
        System.out.println("Logging out from account 'meryem'...");
        meryem.logout();
        System.out.println();

        System.out.print("Step 60... ");
        System.out.println("Logging into an account (username: " + "can" + ")...");
        can.login(accounts);
        System.out.println();

        System.out.print("Step 61... ");
        System.out.println("Adding a comment on a post of meryem...");
        can.makeComment(accounts, 4, "I just found this site");
        System.out.println();

        System.out.print("Step 62... ");
        System.out.println("Logging out from account 'can'...");
        can.logout();
        System.out.println();

        System.out.print("Step 63... ");
        System.out.println("Logging into an account (username: " + "ahmet" + ")...");
        ahmet.login(accounts);
        System.out.println();

        System.out.print("Step 64... ");
        System.out.println("Viewing meryem's profile...");
        ahmet.viewAccount(meryem);

        System.out.print("Step 65... ");
        System.out.println("Viewing meryem's posts' interactions...");
        ahmet.viewInteractions(accounts, meryem);
        System.out.println();

        System.out.print("Step 66... ");
        System.out.println("Logging out from account 'ahmet'...");
        ahmet.logout();
        System.out.println();

        System.out.print("Step 67... ");
        System.out.println("Logging into an account (username: " + "can" + ")...");
        can.login(accounts);
        System.out.println();

        System.out.print("Step 68... ");
        System.out.println("Uncommenting a comment on a post of meryem...");
        can.uncomment(accounts, 4, 6);
        System.out.println();

        System.out.print("Step 69... ");
        System.out.println("Logging out from account 'can'...");
        can.logout();
        System.out.println();

        System.out.print("Step 70... ");
        System.out.println("Logging into an account (username: " + "ahmet" + ")...");
        ahmet.login(accounts);
        System.out.println();

        System.out.print("Step 71... ");
        System.out.println("Viewing meryem's profile...");
        ahmet.viewAccount(meryem);

        System.out.print("Step 72... ");
        System.out.println("Viewing meryem's posts' interactions...");
        ahmet.viewInteractions(accounts, meryem);
        System.out.println();

        System.out.print("Step 73... ");
        System.out.println("Logging out from account 'ahmet'...");
        ahmet.logout();
        System.out.println();

        /************* UNFOLLOW TEST **************/    
        System.out.print("Step 74... ");
        System.out.println("Logging into an account (username: " + "emreoytun" + ")...");
        emreoytun.login(accounts);
        System.out.println();

        System.out.print("Step 75... ");
        System.out.println("Following veli...");
        emreoytun.follow(accounts, veli);
        System.out.println();

        System.out.print("Step 76... ");
        System.out.println("Viewing veli's profile...");
        emreoytun.viewAccount(veli);

        System.out.print("Step 77... ");
        System.out.println("Logging out from account 'emreoytun'...");
        emreoytun.logout();
        System.out.println();

        System.out.print("Step 78... ");
        System.out.println("Logging into an account (username: " + "veli" + ")...");
        veli.login(accounts);
        System.out.println();

        System.out.print("Step 79... ");
        System.out.println("Viewing emreoytun's profile...");
        veli.viewAccount(emreoytun);

        System.out.print("Step 80... ");
        System.out.println("Following emreoytun...");
        veli.follow(accounts, emreoytun);
        System.out.println();

        System.out.print("Step 81... ");
        System.out.println("Logging out from account 'veli'...");
        veli.logout();
        System.out.println();

        System.out.print("Step 82... ");
        System.out.println("Logging into an account (username: " + "emreoytun" + ")...");
        emreoytun.login(accounts);
        System.out.println();

        System.out.print("Step 83... ");
        System.out.println("Unfollowing veli...");
        emreoytun.unfollow(accounts, veli);
        System.out.println();

        System.out.print("Step 84... ");
        System.out.println("Logging out from account 'emreoytun'...");
        emreoytun.logout();
        System.out.println();

        System.out.print("Step 85... ");
        System.out.println("Logging into an account (username: " + "simge" + ")...");
        simge.login(accounts);
        System.out.println();

        System.out.print("Step 86... ");
        System.out.println("Viewing emreoytun's profile...");
        simge.viewAccount(emreoytun);

        System.out.print("Step 87... ");
        System.out.println("Viewing veli's profile...");
        simge.viewAccount(veli);

        System.out.print("Step 88... ");
        System.out.println("Logging out from account 'simge'...");
        simge.logout();
        System.out.println();

        /********* HISTORY TEST *******/
        System.out.print("Step 89... ");
        System.out.println("Logging into an account (username: " + "emreoytun" + ")...");
        emreoytun.login(accounts);
        System.out.println();

        System.out.print("Step 90... ");
        System.out.println("Showing history of emreoytun... ");
        emreoytun.showHistory();
        System.out.println();

    }

}
