package version1;
/**
 * Represents a post.
 * @author Emre Oytun
 */
public class Post {

    /** Keeps the post id. */
    private int postId;
    /** Keeps the account id. */
    private int accountId;
    /** Keeps the content of the post. */
    private String content;
    
    /** Keeps the likes of the post. */
    private Like[] likes;
    /** Keeps the comments of the post. */
    private Comment[] comments;

    /**
     * Creates a post with the given parameters.
     * @param postId The post id.
     * @param accountId The account id which belongs to the account who shares the post.
     * @param content The content of the post.
     */
    public Post(int postId, int accountId, String content) {
        this.postId = postId;
        this.accountId = accountId;
        this.content = content;

        this.likes = new Like[50];
        this.comments = new Comment[50];
    }

    @Override
    public boolean equals(Object o) {
        if (o == null) return false;
        if (o == this) return true;
        if (o.getClass() != this.getClass()) return false;
        Post oth = (Post) o;
        if (postId != oth.postId) return false;
        if (accountId != oth.accountId) return false;
        if (content == null && oth.content == null) return true;
        if (content == null || oth.content == null) return false;
        return content.equals(oth.content);
    }
    
    /**
     * Gets the post id.
     * @return An integer representing the post id.
     */
    public int getPostId() {
        return postId;
    }

    /**
     * Sets the post id.
     * @param postId The post id.
     */
    public void setPostId(int postId) {
        this.postId = postId;
    }

    /**
     * Gets the account id belonging to who shares this post.
     * @return An integer representing the account id.
     */
    public int getAccountId() {
        return accountId;
    }

    /**
     * Sets the account id belonging to who shares this post.
     * @param accountId The account id.
     */
    public void setAccountId(int accountId) {
        this.accountId = accountId;
    }

    /**
     * Gets the content of the post.
     * @return A string representing the content.
     */
    public String getContent() {
        return content;
    }

    /**
     * Sets the content of the post.
     * @param content The content of the post.
     */
    public void setContent(String content) {
        this.content = content;
    }

    /**
     * Adds a like to the post.
     * @param like The like that will be added to the post.
     * @throws RuntimeException If the given like is null.
     */
    public void addLike(Like like) throws RuntimeException {
        if (like == null) {
            System.out.println("Given like is null.");
        }

        int i = 0;
        for (; likes[i] != null; ++i) {}
        likes[i] = like;
    }    
    
    /**
     * Adds a comment to the post.
     * @param comment The comment that will be added to the post.
     * @throws RuntimeException If the given comment is null.
     */
    public void addComment(Comment comment) throws RuntimeException {
        if (comment == null) {
            System.out.println("Given comment is null.");
        }
        
        int i = 0;
        for (; comments[i] != null; ++i) {}
        comments[i] = comment;
    }

    /**
     * Gets the total inteaction number.
     * @return An integer representing the interaction size.
     */
    public int getInteractionSize() {
        return getCommentSize() + getLikeSize();
    }

    /**
     * Checks if the given account liked the post before.
     * @param accountId The id of the account who will be checked for previous like.
     * @return A boolean indicating if the given account liked the post before.
     */
    public boolean userLiked(int accountId) {
        for (int i = 0; likes[i] != null; ++i) {
            Like l = likes[i];
            if (l.getAccountId() == accountId) {
                return true;
            }
        }
        return false;
    }

    public void viewInteractions(Account[] accounts) {
        
                System.out.println("----------------------");
                System.out.println("(PostID: " + getPostId() + "): " + getContent());
        
                int likeSize = getLikeSize();
                if (likeSize == 0) {
                    System.out.println("The post has no likes.");
                }
                else {
                    System.out.print("The post was liked by the following account(s): ");
                    for (int j = 0; j < likeSize; ++j) {
                        System.out.print(findAccountById(accounts, likes[j].getAccountId()).getUsername() + ", ");
                    }
                    System.out.println();
                }
                
                int commentSize = getCommentSize();
                if (commentSize == 0) {
                    System.out.println("The post has no comments.");
                }
                else {
                    System.out.println("The post has " + commentSize + " comment(s)...");
                    for (int j = 0; j < commentSize; ++j) {
                        System.out.println("Comment " + (j+1) + ": " + "'" + findAccountById(accounts, comments[j].getAccountId()).getUsername() + "'" + 
                                " said " + "'" + comments[j].getContent() + "'"); 
                    }
                }
    }

    public void removeInteractions(int accountId) {
        removeLike(accountId);
        removeComments(accountId);
    }

    private void removeLike(int accountId) {
        boolean isDone = false;
        for (int i = 0; likes[i] != null && !isDone; ++i) {
            if (likes[i].getAccountId() == accountId) {
                int j = i+1;
                for (; likes[j] != null; ++j) {
                    likes[j-1] = likes[j];
                }
                likes[j-1] = null;
                isDone = true;
            }
        } 
    }

    private void removeComments(int accountId) {
        boolean isDone = false;
        for (int i = 0; comments[i] != null && !isDone; ++i) {
            if (comments[i].getAccountId() == accountId) {
                int j = i+1;
                for (; comments[j] != null; ++j) {
                    comments[j-1] = comments[j];
                }
                comments[j-1] = null;
                isDone = true;
            }
        }
    } 

    /**
     * Gets the number of likes in the post.
     * @return An integer representing like size.
     */
    private int getLikeSize() {
        int i = 0;
        for (; likes[i] != null && i < likes.length ; ++i) {}
        return i;
    }

    /**
     * Gets the number of comments in the post.
     * @return An integer representing comment size.
     */
    private int getCommentSize() {
        int i = 0;
        for (; comments[i] != null && i < comments.length ; ++i) {}
        return i;
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

    public int getLastInteractionId() {
        int lastId = 0;
        int likesSize = getLikeSize();
        int commentSize = getCommentSize();
        if (likesSize != 0 && likes[likesSize-1].getInteractionId() > lastId) {
            lastId = likes[likesSize-1].getInteractionId();
        }
        if (commentSize != 0 && comments[commentSize-1].getInteractionId() > lastId) {
            lastId = comments[commentSize-1].getInteractionId();
        }
        return lastId;
    }

}
