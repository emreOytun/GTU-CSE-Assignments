package version1;
/**
 * Represents an account.
 * @author Emre Oytun
 */
public class Account {

    /** Keeps account id of the user. */
    private int accountId;
    /** Keeps username of the user. */
    private String username;
    /** Keeps birthdate of the user. */
    private String birthDate;
    /** Keeps location of the user. */
    private String location;
    
    /** Keeps all posts of the user. */
    private Post[] posts;
    /** Keeps all messages of the user. */
    private Message[] messages;
    /** Keeps following accounts which follow the account. */
    private Account[] following;
    /** Keeps accounts that the account follows. */
    private Account[] followers;
    /** Keeps account that the account blocked. */
    private Account[] blockedAccounts;

    /** Keeps the boolean indicating if the account has logined or not. */
    private boolean isLoginned;

    /** Keeps the last viewed account to be able to make some checks. */
    private String lastViewedAccount;

    /**
     * Creates an account with the given parameters.
     * @param accountId The account id of the account.
     * @param username The username of the user.
     * @param birthdate The birthdate of the user.
     * @param location The location of the user.
     */
    public Account(int accountId, String username, String birthdate, String location) {
        this.accountId = accountId;
        this.username = username;
        this.birthDate = birthdate;
        this.location = location;
        this.isLoginned = false;  
        this.lastViewedAccount = null;  
    
        this.posts = new Post[50];
        this.messages = new Message[50];
        this.following = new Account[50];
        this.followers = new Account[50];
        this.blockedAccounts = new Account[50];
    }

    /**
     * Creates an account when id is not given.
     * @param username The username of the account.
     * @param birthdate The birthdate of the user.
     * @param location The location of the user.
     */
    public Account(String username, String birthdate, String location) {
        this(0, username, birthdate, location);
    }

    /**
     * Checks whether given object is equals to the account.
     * @param o The given object that will be compared.
     * @return A boolean indicating if the given object equals to the account or not.
     */
    @Override
    public boolean equals(Object o) {
        if (o == null) return false;
        if (o == this) return true;
        if (o.getClass() != this.getClass()) return false;
        
        Account oth = (Account) o;
        if (oth.getAccountId() != accountId) return false;
        if (!compareString(username, oth.username)) return false;
        if (!compareString(birthDate, oth.birthDate)) return false;
        if (!compareString(location, oth.location)) return false;
        return true;
    }

    /**
     * Writes the account informations inside the string.
     * @return A string representing account details.
     */
    @Override
    public String toString() {
        int followingSize = getFollowingSize();
        int followersSize = getFollowersSize();
        int postSize = getPostSize();

        System.out.println("----------------------");
        String res =  "User ID: " + accountId + "\n" +
                "Username: " + username + "\n" +
                "Location: " + location + "\n" +
                "Birth Date: " + birthDate + "\n" +
                username + " is following " + followingSize + " account(s) and has " + followersSize + " followers(s)." + "\n";

        if (followersSize != 0) {
            res += "The followers of " + username + " are: ";
            for (int i = 0; i < followersSize; ++i) {
                res += followers[i].getUsername() + ", ";
            }
            res += "\n";
        }

        if (followingSize != 0) {
            res += username + " is following: ";
            for (int i = 0; i < followingSize; ++i) {
                res += following[i].getUsername() + ", ";
            }
            res += "\n";
        }

        res += username + " has " + postSize + " posts." + "\n";
        return res;
    }

    
    /**
     * Gets account id.
     * @return An integer representing the account id.
     */
    public int getAccountId() {
        return accountId;
    }

    /**
     * Set account id.
     * @param accountId The account id of the account.
     */
    public void setAccountId(int accountId) {
        this.accountId = accountId;
    }

    /**
     * Gets username.
     * @return A string representing username.
     */
    public String getUsername() {
        return username;
    }

    /**
     * Sets username.
     * @param username The user name of the user.
     */
    public void setUsername(String username) {
        this.username = username;
    }

    /**
     * Gets the birth date of the user.
     * @return A string representing the birth date.
     */
    public String getBirthDate() {
        return birthDate;
    }

    /**
     * Sets the birth date of the account.
     * @param birthDate The user's birthdate.
     */
    public void setBirthDate(String birthDate) {
        this.birthDate = birthDate;
    }

    /**
     * Gets the location of the user.
     * @return A string representing user's location.
     */
    public String getLocation() {
        return location;
    }

    /**
     * Sets the location of the user.
     * @param location The user's location.
     */
    public void setLocation(String location) {
        this.location = location;
    }

    /**
     * Registers the new account.
     * @param accounts The registered accounts' array.
     */
    public void signUp(Account[] accounts) {
        Account result = findAccountByUsername(accounts, getUsername());
        if (result != null) {
            System.out.println("WARNING: An account with username " + getUsername() + " has already been created.");
            return;
        }

        addAccount(accounts, this);
        System.out.println("An account with username " + username + " has been created.");
    }

     /**
     * Logins to the system.
     * Checks if the user has loginned before and makes other checks.
     * @param accounts The accounts array to check if another user has logged in before.
     */
    public void login(Account[] accounts) {        
        if (isLoginned) {
            System.out.println("WARNING: You are already logged in.");
        }
        else {
            // Check if someone has logined before.
            boolean someoneLogin = false;
            boolean signedUp = false;
            for (int i = 0; accounts[i] != null && (!someoneLogin || !signedUp); ++i) {
                if (accounts[i].isLoginned) {
                    someoneLogin = true;
                }
                if (accounts[i].getUsername().equals(username)) {
                    signedUp = true;
                }
            }
            if (!signedUp) {
                System.out.println("WARNING: You have not registered before.");
            }
            else if (someoneLogin) {
                System.out.println("WARNING: Another account has logged in before.");
            }
            else {
                isLoginned = true;        
            }
        }
    }

    /**
     * Logout from the system.
     * Checks if the user has loginned before.
     */
    public void logout() {
        if (!isLoginned) {
            System.out.println("WARNING: You are not logged in before.");
        }
        else {
            isLoginned = false;
            lastViewedAccount = null;
        }
    }

   /**
     * Shares a new post with the given content.
     * Checks if the user has loginned before.
     * @param accounts The registered accounts' array to check if another account with the same username has registered before.
     * @param content The content of the new post.
     */
    public void sharePost(Account[] accounts, String content) {
        if (!isLoginned) {
            System.out.println("WARNING: You are not logged in.");
        }
        else {
            Post newPost = new Post(getLastPostId(accounts)+1, getAccountId(), content);
            addPost(newPost);
        }
    }

     /**
     * Follows the given account.
     * Checks if the user has loginned before.
     * Checks if user is trying to follow itself.
     * Checks if the user is blocked.
     * Checks if the user has followed the account before.
     * @param accounts The registered accounts' array to check if there is such account registered to the system.
     * @param account The account that will be followed by this account.
     */
    public void follow(Account[] accounts, Account account) {
        if (account == null) {
            System.out.println("WARNING: There is no such account.");
            return;
        }
        
        Account result = findAccountByUsername(accounts, account.getUsername());
        if (result == null) {
            System.out.println("WARNING: There are no accounts registered with username " + account.getUsername() + ".");
        }
        
        else if (!isLoginned) {
            System.out.println("WARNING: You are not logged in.");
        }

        else if (account == this) {
            System.out.println("WARNING: You cannot follow yourself.");
        }

        else if (account.isBlocked(username)) {
            System.out.println("WARNING: You are blocked!");
        }

        else if (isFollowing(account.getUsername())) {
            System.out.println("WARNING: You are already following the account with username '" + account.getUsername() + "'.");
        }

        else if (isBlocked(account.getUsername())) {
            System.out.println("WARNING: You blocked this account before. You cannot follow."); 
        }

        else {
            account.addFollower(this);
            addFollowing(account);
        }

    }

    /**
     * Likes a post with the given post id.
     * Check if the user has loginned before.
     * Checks if the user is blocked.
     * Check if the user has liked the post before.
     * @param accounts The registered accounts' array to find the last interaction id.
     * @param postId The id of the post that will be liked.
     */
    public void likePost(Account[] accounts, int postId) {
        if (!isLoginned) {
            System.out.println("WARNING: You are not logged in.");
        }
        
        else {
            Post post = findPostById(accounts, postId);
            if (post == null) {
                System.out.println("WARNING: There is no such post.");
            }

            else {
                Account account = findAccountById(accounts, post.getAccountId());
                if (account.isBlocked(getUsername())) {
                    System.out.println("WARNING: You are blocked!");
                }
                
                else if (post.userLiked(getAccountId())) {
                    System.out.println("WARNING: You liked this post before.");
                }

                else if (isBlocked(account.getUsername())) {
                    System.out.println("WARNING: You blocked the owner of the post. You cannot like the post.");
                }
                
                else {
                    post.addLike(new Like(getLastInteractionId(accounts)+1, getAccountId(), post.getPostId()));
                }
            }
        }

        
    }

    /**
     * Makes a new comment to the post whose id is given.
     * Check if the user has loginned before.
     * Checks if the user is blocked.
     * @param accounts The registered accounts' array to find the last comment's id.
     * @param postId The post's id.
     * @param comment The comment that will be made to the post.
     */
    public void makeComment(Account[] accounts, int postId, String comment) {
        if (!isLoginned) {
            System.out.println("WARNING: You are not logged in.");
        }
        
        else {
            Post post = findPostById(accounts, postId);
            if (post == null) {
                System.out.println("WARNING: There is no such post.");
            }

            else {
                Account account = findAccountById(accounts, post.getAccountId());
                if (account.isBlocked(getUsername())) {
                    System.out.println("WARNING: You are blocked!");
                }

                else if (isBlocked(account.getUsername())) {
                    System.out.println("WARNING: You blocked the owner of the post. You cannot comment.");
                }

                else {
                    post.addComment(new Comment(getLastInteractionId(accounts)+1, getAccountId(), post.getPostId(), comment));
                }
            }
        }
            
    }

    /**
     * Sends a message to the given account.
     * Check if the user has loginned before.
     * Checks if the user is following the receiver account.
     * Checks if the user is blocked to find the last message's id.
     * @param accounts The registered accounts' array.
     * @param receiverAccount The account of the receiver user.
     * @param content The message's content.
     */
    public void sendMessage(Account[] accounts, Account receiverAccount, String content) {
        if (receiverAccount == null) {
            System.out.println("WARNING: There is no such account.");
            return;
        }
        
        Account result = findAccountByUsername(accounts, receiverAccount.getUsername());
        if (result == null) {
            System.out.println("WARNING: There are no accounts registered with username " + receiverAccount.getUsername() + ".");
        }
        
        else if (!isLoginned) {
            System.out.println("WARNING: You are not logged in.");
        }
       
        else if (receiverAccount.isBlocked(getUsername())) {
            System.out.println("WARNING: You are blocked!");
        }

        else if (!isFollowing(receiverAccount.getUsername())) {
            System.out.println("WARNING: You are not following the user that the message will be sent.");
        }

        else if (isBlocked(receiverAccount.getUsername())) {
            System.out.println("WARNING: You blocked the receiver. You cannot send message.");
        }

        else {
            Message message = new Message(getLastMessageId(accounts), getAccountId(), receiverAccount.getAccountId(), content);
            receiverAccount.addMessage(message);
            addMessage(message);
        }
    }

    /**
     * Views the given account.
     * Checks if the user has loginned before.
     * Checks if the user is blocked.
     * @param account The account that will be viewed.
     */
    public void viewAccount(Account account) {
        if (!isLoginned) {
            System.out.println("WARNING: You are not logged in.");
        }
        
        else if (account == null) {
            System.out.println("WARNING: There is no such account.");
        }

        else if (account.isBlocked(getUsername())) {
            System.out.println("WARNING: You are blocked!");
        }

        else if (isBlocked(account.getUsername())) {
            System.out.println("WARNING: You blocked the account. You cannot view.");
        }
        
        else {
            System.out.println(account);
            lastViewedAccount = account.getUsername();
        }
    }

    /**
     * Views the given account's posts.
     * Checks if the user has loginned before.
     * Checks if the user is blocked.
     * Checks if the user is viewed the account before.
     * @param account The account whose posts will be viewed.
     */
    public void viewPosts(Account account) {
        if (!isLoginned) {
            System.out.println("WARNING: You are not logged in.");
        }

        else if (account == null) {
            System.out.println("WARNING: There is no such account.");
        }

        else if (account.isBlocked(getUsername())) {
            System.out.println("WARNING: You are blocked!");
        }

        else if (lastViewedAccount == null || !lastViewedAccount.equals(account.getUsername())) {
            System.out.println("WARNING: You cannot view the posts before viewing the account.");
        }

        else if (isBlocked(account.getUsername())) {
            System.out.println("WARNING: You blocked the account. You cannot view posts.");
        }

        else {
            System.out.println(account.postsToString());
        }
    }

    /**
     * Views the interactions of the user whose account is given.
     * Checks if the user has loginned before.
     * Checks if the user is blocked.
     * Checks if the user is viewed the account before.
     * @param accounts The registered accounts' array to find the usernames needed to view.
     * @param account The account whose interactions will be viewed.
     */
    public void viewInteractions(Account[] accounts, Account account) {
        if (!isLoginned) {
            System.out.println("WARNING: You are not logged in.");
        }
        
        else if (account == null) {
            System.out.println("WARNING: There is no such account.");
        }

        else if (account.isBlocked(getUsername())) {
            System.out.println("WARNING: You are blocked!");
        }

        else if (lastViewedAccount == null || !lastViewedAccount.equals(account.getUsername())) {
            System.out.println("WARNING: You cannot view the interactions before viewing the account.");
        }

        else if (isBlocked(account.getUsername())) {
            System.out.println("WARNING: You blocked the account. You cannot view interactions.");
        }

        else {
            account.viewInteractions(accounts);
        }
    }

    /**
     * Checks inbox of the account.
     * Checks if the user has loginned before.
     */
    public void checkInbox() {
        if (!isLoginned) {
            System.out.println("WARNING: You are not logged in.");
            return;
        }
        int totalInbox = getInboxSize();
        System.out.println("There is/are " + totalInbox + " message(s) in the inbox.");
    }

    /**
     * Checks outbox of the account.
     * Checks if the user has loginned before.
     */
    public void checkOutbox() {
        if (!isLoginned) {
            System.out.println("WARNING: You are not logged in.");
            return;
        }
        int totalOutbox = getOutboxSize();
        System.out.println("There is/are " + totalOutbox + " message(s) in the outbox.");
    }

 
    /**
     * Views inbox of the account.
     * Checks if the user has loginned before.
     * @param accounts The registered accounts' array to find the usernames of the receiver and sender's accounts.
     */
    public void viewInbox(Account[] accounts) {
        if (!isLoginned) {
            System.out.println("WARNING: You are not logged in.");
            return;
        }

        System.out.println("Viewing inbox...");
        Message[] inbox = getInbox();
        for (int i = 0; inbox[i] != null; ++i) {
            System.out.println("----------------------");
            System.out.println("Message ID: " + inbox[i].getMessageId());
            System.out.println("From: " + findAccountById(accounts, inbox[i].getSenderId()).getUsername());
            System.out.println("To: " + findAccountById(accounts, inbox[i].getReceiverId()).getUsername());
            System.out.println("Message: " + inbox[i].getContent());
        }
    }

    /**
     * Views outbox of the account.
     * Checks if the user has loginned before.
     * @param accounts The registered accounts' array to find the usernames of the receiver and sender's accounts.
     */
    public void viewOutbox(Account[] accounts) {
        if (!isLoginned) {
            System.out.println("WARNING: You are not logged in.");
            return;
        }

        System.out.println("Viewing outbox...");
        Message[] outbox = getOutbox();
        for (int i = 0; outbox[i] != null; ++i) {
            System.out.println("----------------------");
            System.out.println("Message ID: " + outbox[i].getMessageId());
            System.out.println("From: " + findAccountById(accounts, outbox[i].getSenderId()).getUsername());
            System.out.println("To: " + findAccountById(accounts, outbox[i].getReceiverId()).getUsername());
            System.out.println("Message: " + outbox[i].getContent());
        }
    }

    /**
     * Blocks the given account.
     * Checks if user has loginned.
     * @param account The account that will be blocked.
     */
    public void blockAccount(Account account) {
        if (!isLoginned) {
            System.out.println("WARNING: You are not logged in.");
        }

        else if (account == null) {
            System.out.println("WARNING: There is no such account.");
        }
        
        else if (account == this) {
            System.out.println("WARNING: You cannot block yourself");
        }

        else if (isBlocked(account.getUsername())) {
            System.out.println("WARNING: You blocked " + account.getUsername() + " already.");
        }

        else {
            int i = 0;
            for (; blockedAccounts[i] != null; ++i) {}
            blockedAccounts[i] = account;            
            
            removeFollower(account);
            removeFollowing(account);
            account.removeFollowing(this);
            account.removeFollower(this);  

            for (int j = 0; posts[j] != null; ++j) {
                posts[j].removeInteractions(account.getAccountId());
            }
        }
    }

    /**
     * Removes the account from following list.
     * @param account The account that will be removed from the following list if it is found.
     */
    private void removeFollowing(Account account) {
        boolean isDone = false;
        for (int i = 0; following[i] != null && !isDone; ++i) {
            if (following[i].getUsername().equals(account.getUsername())) {
                int j = i+1;
                for (; following[j] != null; ++j) {
                    following[j-1] = following[j];
                }
                following[j-1] = null;
                isDone = true;
            }
        }
    }

    /**
     * Removes the account from follower list.
     * @param account The account that will be removed from the follower list if it is found.
     */
    private void removeFollower(Account account) {
        boolean isDone = false;
        for (int i = 0; followers[i] != null && !isDone; ++i) {
            if (followers[i].getUsername().equals(account.getUsername())) {
                int j = i+1;
                for (; followers[j] != null; ++j) {
                    followers[j-1] = followers[j];
                }
                followers[j-1] = null;
                isDone = true;
            }
        }
    }

    /**
     * Checks if the given username is blocked by the user.
     * @param username The username that will be checked if it's blocked.
     * @return A boolean indicating if the username is blocked.
     */
    private boolean isBlocked(String username) {
        if (username == null) {
            return false;
        }
        
        boolean res = false;
        for (int i = 0; blockedAccounts[i] != null && !res; ++i) {
            if (blockedAccounts[i].getUsername().equals(username)) {
                res = true;
            }
        }
        return res;
    }

    private void viewInteractions(Account[] accounts) {
        for (int i = 0; posts[i] != null; ++i) {
            posts[i].viewInteractions(accounts);
        }
    }

    /**
     * Checks if the given user with username is following this account.
     * @param username The username of the user that will be checked if it follows this account.
     * @return A boolean indicating if the user follows this account.
     */
    private boolean isFollowing(String username) {
        if (username == null) {
            return false;
        }
        
        for (int i = 0; following[i] != null; ++i) {
            Account a = following[i];
            if (a.getUsername().equals(username)) {
                return true;
            }
        }
        return false;
    }

    /**
     * Finds the total following size.
     * @return An integer representing the total following number.
     */
    private int getFollowingSize() {
        int i = 0;
        for (; following[i] != null; ++i) {}
        return i;
    }

    /**
     * Finds the total follower size.
     * @return An integer representing the total follower number.
     */
    private int getFollowersSize() {
        int i = 0;
        for (; followers[i] != null; ++i) {}
        return i;
    }

    /**
     * Gets number of posts.
     * @return An integer representing the post size.
     */
    private int getPostSize() {
        int i = 0;
        for (; posts[i] != null; ++i) {}
        return i;
    }

    /**
     * Gets the total number of messages.
     * @return An integer representing the message size.
     */
    private int getMessageSize() {
        int i = 0;
        for (; messages[i] != null; ++i) {}
        return i;
    }

    /**
     * Gets the total number of inbox messages.
     * @return An integer representing the inbox size.
     */
    private int getInboxSize() {
        int totalInbox = 0;
        for (int i = 0; messages[i] != null; ++i) {
            if (messages[i].getReceiverId() == accountId) {
                ++totalInbox;
            }
        }
        return totalInbox;
    }

    /**
     * Gets the total number of outbox messages.
     * @return An integer representing the outbox size.
     */
    private int getOutboxSize() {
        int totalOutbox = 0;
        for (int i = 0; messages[i] != null; ++i) {
            if (messages[i].getSenderId() == accountId) {
                ++totalOutbox;
            }
        }
        return totalOutbox;
    }

    /**
     * Finds the account whose username is given.
     * @param accounts The registered accounts' array.
     * @param username The username of the account which will be found inside accounts.
     * @return An account that is found, or NULL if account is not found.
     */
    private Account findAccountByUsername(Account[] accounts, String username) {
        if (username == null) return null;
       
        Account account = null;
        boolean isFound = false;
        for (int i = 0; accounts[i] != null && !isFound; ++i) {
            if (username.equals(accounts[i].getUsername())) {
                account = accounts[i];
                isFound = true;
            } 
        }
        return account;
    }

    /**
     * Finds the account whose id is given.
     * @param accounts The registered accounts' array.
     * @param id The id of the account which will be found inside accounts.
     * @return An account that is found, or NULL if account is not found.
     */
    private Account findAccountById(Account[] accounts, int id) {
        Account account = null;
        boolean isFound = false;

        for (int i = 0; accounts[i] != null && !isFound; ++i) {
            if (id == accounts[i].getAccountId()) {
                account = accounts[i];
                isFound = true;
            } 
        }
        return account;
    }

    /**
     * Finds the post whose id is given.
     * @param accounts The registered accounts' array.
     * @param postId The id of the post which will be found inside posts.
     * @return A post that is found, or NULL if post is not found.
     */
    private Post findPostById(Account[] accounts, int postId) {
        Post post = null;
        boolean isFound = false;
        for (int i = 0; accounts[i] != null && !isFound; ++i) {
            Post[] posts = accounts[i].posts;
            for (int j = 0; posts[j] != null && !isFound; ++j) {
                if (posts[j].getPostId() == postId) {
                    post = posts[j];
                    isFound = true;
                }
            }
        }
        return post;
    }

    /**
     * Gets the last post's id.
     * @param accounts The registered accounts' array.
     * @return An integer representing the last post id.
     */
    private int getLastPostId(Account[] accounts) {
        int total = 0;
        for (int i = 0; accounts[i] != null; ++i) {
            Account a = accounts[i];
            total += a.getPostSize();
        }
        return total;
    }

    /**
     * Gets the last interaction's id.
     * @param accounts The registered accounts' array.
     * @return An integer representing the last interaction's id.
     */
    private int getLastInteractionId(Account[] accounts) {
        int lastId = 0;
        for (int i = 0; accounts[i] != null; ++i) {
            Account a = accounts[i];
            Post[] posts = a.posts;
            for (int j = 0; posts[j] != null; ++j) {
                int lastInteractionId = posts[j].getLastInteractionId();
                if (lastInteractionId > lastId) lastId = lastInteractionId;
            }
        }
        return lastId;
    }

    /**
     * Get the last message's id.
     * @param accounts The registered accounts' array.
     * @return An integer representing the last message's id.
     */
    private int getLastMessageId(Account[] accounts) {
        int total = 0;
        for (int i = 0; accounts[i] != null; ++i) {
            Account a = accounts[i];
            total += a.getMessageSize();
        }
        return total/2;
    }

    /**
     * Gets all messages in the inbox.
     * @return A message array containing inbox messages.
     */
    private Message[] getInbox() {
        Message[] inbox = new Message[50];
        int inboxIndex = 0;
       
        for (int i = 0; messages[i] != null; ++i) {
            if (messages[i].getReceiverId() == accountId) {
                inbox[inboxIndex++] = messages[i];
            }
        }
        return inbox;
    }

    /**
     * Gets all messages in the outbox.
     * @return A message array containing outbox messages.
     */
    private Message[] getOutbox() {
        Message[] outbox = new Message[50];
        int outboxIndex = 0;
       
        for (int i = 0; messages[i] != null; ++i) {
            if (messages[i].getSenderId() == accountId) {
                outbox[outboxIndex++] = messages[i];
            }
        }
        return outbox;
    }

    /**
     * Adds a new account to the system.
     * @param accounts The registered accounts' array.
     * @param account The new account that will be added.
     */
    private void addAccount(Account[] accounts, Account account) {
        if (account == null) {
            System.out.println("Given account is null");
        }

        int i = 0;
        for (; accounts[i] != null; ++i) {}
        account.setAccountId(i+1);
        accounts[i] = account;
    }

    /**
     * Adds a new post to the account's posts.
     * @param post The new post that will be added to the account's posts.
     * @throws RuntimeException If the given post is null.
     */
    private void addPost(Post post) {
        if (post == null) {
            System.out.println("Given post is null.");
            return;
        }
        int i = 0;
        for (; posts[i] != null; ++i) {}
        posts[i] = post;
    }

    /**
     * Adds a new message to the messages of the account.
     * @param message The new message that will be added.
     * @throws RuntimeException If the given message is null.
     */
    private void addMessage(Message message) {
        if (message == null) {
            System.out.println("Given message is null.");
            return;
        }
        int i = 0;
        for (; messages[i] != null; ++i) {}
        messages[i] = message;
    }

    /**
     * Adds a new following account.
     * @param account The new account that will be followed by this account.
     * @throws RuntimeException If the given account is null.
     */
    private void addFollowing(Account account) {
        if (account == null) {
            System.out.println("Given account is null.");
            return;        
        }
        int i = 0;
        for (; following[i] != null; ++i) {}
        following[i] = account;
    }

    /**
     * Adds a new follower.
     * @param account The new follower account that will be added.
     * @throws RuntimeException If the given account is null.
     */
    private void addFollower(Account account) {
        if (account == null) {
            System.out.println("Given account is null.");
            return;
        }
        int i = 0;
        for (; followers[i] != null; ++i) {}
        followers[i] = account;
    }

    /**
     * Writes the informations of all the posts into the string.
     * @return A string representing the details of all posts.
     */
    private String postsToString() {
        String res = "";
        for (int i = 0; i < getPostSize(); ++i) {
            res += "(PostID: " + posts[i].getPostId() + ") " + username + ": " + posts[i].getContent() + "\n"; 
        }
        return res;
    }  

    /**
     * Compares two strings. 
     * @param s1 First string to be compared.
     * @param s2 Second string to be compared.
     * @return A boolean indicating the if they are equal or not. True if they are equal, false otherwise.
     */
    private boolean compareString(String s1, String s2) {
        if (s1 == null && s2 == null) return true;
        if (s1 == null || s2 == null) return false;
        return s1.equals(s2);
    }
}
