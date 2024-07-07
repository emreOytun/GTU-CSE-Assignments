/**
 * Security class to keep fail message.
 * @author Emre Oytun
 */
public abstract class Security {
    protected String failMessage = null;

    /**
     * Get the fail message.
     * @return A string representing the mail message.
     */
    public String getFailMessage() {
        return failMessage;
    }
}
