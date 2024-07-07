package version3;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

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
    private List<Like> likes;
    /** Keeps the comments of the post. */
    private List<Comment> comments;

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

        this.likes = new LinkedList<>();
        this.comments = new LinkedList<>();
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
        likes.add(like);
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
        comments.add(comment);
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
        Iterator<Like> it = likes.iterator();
        while (it.hasNext()) {
            Like l = it.next();
            if (l.getAccountId() == accountId) {
                return true;
            }
        }
        return false;
    }

    public void viewInteractions(List<Account> accounts) {
        
                System.out.println("----------------------");
                System.out.println("(PostID: " + getPostId() + "): " + getContent());
        
                int likeSize = getLikeSize();
                if (likeSize == 0) {
                    System.out.println("The post has no likes.");
                }
                else {
                    System.out.print("The post was liked by the following account(s): ");
                    Iterator<Like> likesIt = likes.iterator();
                    while(likesIt.hasNext()) {
                        System.out.print(findAccountById(accounts, likesIt.next().getAccountId()).getUsername() + ", ");
                    }
                    System.out.println();
                }
                
                int commentSize = getCommentSize();
                if (commentSize == 0) {
                    System.out.println("The post has no comments.");
                }
                else {
                    System.out.println("The post has " + commentSize + " comment(s)...");
                    Iterator<Comment> commentsIt = comments.iterator();
                    int j = 0;
                    while (commentsIt.hasNext()) {
                        Comment comment = commentsIt.next();
                        System.out.println("Comment " + (j+1) + ": " + "'" + findAccountById(accounts, comment.getAccountId()).getUsername() + "'" + 
                                " said " + "'" + comment.getContent() + "'"); 
                        ++j;
                    }
                }
    }

    public void removeLike(int accountId) {
        boolean isDone = false;
        Iterator<Like> it = likes.iterator();
        while (it.hasNext() && !isDone) {
            Like l = it.next();
            if (l.getAccountId() == accountId) {
                it.remove();
                isDone = true;
            }
        }
    }

    public void removeComment(int commentId) {
        boolean isDone = false;
        Iterator<Comment> it = comments.iterator();
        while (it.hasNext() && !isDone) {
            Comment c = it.next();
            if (c.getInteractionId() == commentId) {
                it.remove();
                isDone = true;
            }
        }
    }

    public boolean hasComment(int commentId, int accountId) {
        Iterator<Comment> it = comments.iterator();
        while (it.hasNext()) {
            Comment c = it.next();
            if (c.getInteractionId() == commentId && c.getAccountId() == accountId) {
                return true;
            }
        }
        return false;
    }

    public void removeInteractions(int accountId) {
        removeLike(accountId);
        
        Iterator<Comment> it = comments.iterator();
        while (it.hasNext()) {
            Comment c = it.next();
            if (c.getAccountId() == accountId) {
                it.remove();
            }
        }
    }


    /**
     * Gets the number of likes in the post.
     * @return An integer representing like size.
     */
    private int getLikeSize() {
        return likes.size();
    }

    /**
     * Gets the number of comments in the post.
     * @return An integer representing comment size.
     */
    private int getCommentSize() {
        return comments.size();
    }

    /**
     * Finds the account whose id is given.
     * @param accounts The registered accounts' array.
     * @param id The id of the account which will be found inside accounts.
     * @return An account that is found, or NULL if account is not found.
     */
    private Account findAccountById(List<Account> accounts, int id) {
        Account account = null;
        boolean isFound = false;

        Iterator<Account> it = accounts.iterator();
        while (it.hasNext() && !isFound) {
            Account element = it.next();
            if (id == element.getAccountId()) {
                account = element;
                isFound = true;
            } 
        }
        return account;
    }

    public int getLastInteractionId() {
        int lastId = 0;
        if (likes.size() != 0 && likes.get(likes.size()-1).getInteractionId() > lastId) {
            lastId = likes.get(likes.size()-1).getInteractionId();
        } 
        if (comments.size() != 0 && comments.get(comments.size()-1).getInteractionId() > lastId) {
            lastId = comments.get(comments.size()-1).getInteractionId();
        }
        return lastId;
    }
}
