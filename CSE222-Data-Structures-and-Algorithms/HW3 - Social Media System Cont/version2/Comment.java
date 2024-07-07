package version2;
/**
 * Represents a comment which is an interaction.
 * @author Emre Oytun
 */
public class Comment extends Interaction {
    
    /** Keeps the content of the comment. */
    private String content;

    /**
     * Creates a comment with the given parameters.
     * @param interactionId The interaction id.
     * @param accountId The account id of the interaction.
     * @param postId The post id of the interaction.
     * @param content The content of the comment.
     */
    public Comment(int interactionId, int accountId, int postId, String content) {
        super(interactionId, accountId, postId);
        this.content = content;
    }

    @Override
    public boolean equals(Object o) {
        if (!super.equals(o)) return false;
        if (o.getClass() != this.getClass()) return false;
        Comment oth = (Comment) o;
        if (content == null && oth.content == null) return true;
        if (content == null || oth.content == null) return false;
        return content.equals(oth.content);
    }

    /**
     * Gets the content of the comments.
     * @return A string representing the content of the comment.
     */
    public String getContent() {
        return content;
    }

    /**
     * Sets the content of the comment.
     * @param content The comment's content.
     */
    public void setContent(String content) {
        this.content = content;
    }

    
}
