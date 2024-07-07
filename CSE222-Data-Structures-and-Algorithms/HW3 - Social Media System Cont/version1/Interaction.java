package version1;
/**
 * An abstract class for an interaction.
 * @author Emre Oytun
 */
public abstract class Interaction {

    /** Keeps the interaction id. */
    private int interactionId;
    /** Keeps the account id. */
    private int accountId;
    /** Keeps the post id. */
    private int postId;
    
    /**
     * Creates an interaction with given parameters.
     * @param interactionId The interaction's id.
     * @param accountId The account id who makes this interaction.
     * @param postId The post id to whom this interaction belongs.
     */
    public Interaction(int interactionId, int accountId, int postId) {
        this.interactionId = interactionId;
        this.accountId = accountId;
        this.postId = postId;
    }

    @Override
    public boolean equals(Object o) {
        if (o == null) return false;
        if (o == this) return true;
        if (!(o instanceof Interaction)) return false;
        Interaction oth = (Interaction) o;
        if (interactionId != oth.interactionId) return false;
        if (accountId != oth.accountId) return false;
        if (postId != oth.postId) return false;
        return true;
    }

    /**
     * Gets the interaction id.
     * @return An integer representing interaction id.
     */
    public int getInteractionId() {
        return interactionId;
    }

    /**
     * Sets the interaction id.
     * @param interactionId The interaction's id.
     */
    public void setInteractionId(int interactionId) {
        this.interactionId = interactionId;
    }

    /**
     * Gets the account id.
     * @return An integer representing the account id.
     */
    public int getAccountId() {
        return accountId;
    }

    /**
     * Sets the account id.
     * @param accountId The account id of the interaction.
     */
    public void setAccountId(int accountId) {
        this.accountId = accountId;
    }

    /**
     * Gets the account id.
     * @return An integer representing the post id.
     */
    public int getPostId() {
        return postId;
    }

    /**
     * Sets the post id.
     * @param postId The post id of the interaction.
     */
    public void setPostId(int postId) {
        this.postId = postId;
    }

    

}