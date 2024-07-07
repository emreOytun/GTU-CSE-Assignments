package homework1;
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

        this.likes = new Like[0];
        this.comments = new Comment[0];
    }
    
    /**
     * Gets the likes of the post.
     * @return A like array containing the likes.
     */
    public Like[] getLikes() {
        return likes;
    }

    /**
     * Gets the number of likes in the post.
     * @return An integer representing like size.
     */
    public int getLikeSize() {
        return likes.length;
    }

    /**
     * Gets the comments of the post.
     * @return A comment array containing the comments.
     */
    public Comment[] getComments() {
        return comments;
    }

    /**
     * Gets the number of comments in the post.
     * @return An integer representing comment size.
     */
    public int getCommentSize() {
        return comments.length;
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
            throw new RuntimeException("Given like is null.");
        }

        Like[] newArray = new Like[likes.length + 1];
        for (int i = 0; i < likes.length; ++i) {
            newArray[i] = likes[i];
        }
        likes = null;
        likes = newArray;

        likes[likes.length-1] = like;
    }    
    
    /**
     * Adds a comment to the post.
     * @param comment The comment that will be added to the post.
     * @throws RuntimeException If the given comment is null.
     */
    public void addComment(Comment comment) throws RuntimeException {
        if (comment == null) {
            throw new RuntimeException("Given comment is null.");
        }
        
        Comment[] newArray = new Comment[comments.length + 1];
        for (int i = 0; i < comments.length; ++i) {
            newArray[i] = comments[i];
        }
        comments = null;
        comments = newArray;

        comments[comments.length-1] = comment;
    }

    /**
     * Gets the total inteaction number.
     * @return An integer representing the interaction size.
     */
    public int getInteractionSize() {
        return comments.length + likes.length;
    }

    /**
     * Checks if the given account liked the post before.
     * @param accountId The id of the account who will be checked for previous like.
     * @return A boolean indicating if the given account liked the post before.
     */
    public boolean userLiked(int accountId) {
        for (int i = 0; i < likes.length; ++i) {
            Like l = likes[i];
            if (l.getAccountId() == accountId) {
                return true;
            }
        }
        return false;
    }

}
