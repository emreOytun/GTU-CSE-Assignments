package version3;
/**
 * Represents a like which is an interaction.
 * @author Emre Oytun
 */
public class Like extends Interaction {

    /**
     * Creates a like with the given parameters.
     * @param interactionId The interaction's id.
     * @param accountId The account id who makes this interaction.
     * @param postId The post id to whom this interaction belongs.
     */
    public Like(int interactionId, int accountId, int postId) {
        super(interactionId, accountId, postId);
    }
    
    @Override
    public boolean equals(Object o) {
        if (!super.equals(o)) return false;
        if (o.getClass() != this.getClass()) return false;
        return true; 
    }
}
