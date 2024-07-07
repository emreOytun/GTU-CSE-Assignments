package version2;
/**
 * Represents a message.
 * @author Emre Oytun
 */
public class Message {

    /** Keeps a message's id. */
    private int messageId;
    /** Keeps the id of the account who sends the message. */
    private int senderId;
    /** Keep the id of the account who receives the message. */
    private int receiverId;
    /** Keeps the content of the message. */
    private String content;

    /**
     * Creates a message with given parameters.
     * @param messageId The message's id.
     * @param senderId The sender's id.
     * @param receiverId The receiver's id.
     * @param content The message's content.
     */
    public Message(int messageId, int senderId, int receiverId, String content) {
        this.messageId = messageId;
        this.senderId = senderId;
        this.receiverId = receiverId;
        this.content = content;
    }

    @Override
    public boolean equals(Object o) {
        if (o == null) return false;
        if (o == this) return true;
        if (o.getClass() != this.getClass()) return false;
        Message oth = (Message) o;
        if (messageId != oth.messageId) return false;
        if (senderId != oth.senderId) return false;
        if (receiverId != oth.receiverId) return false;
        if (content == null && oth.content == null) return true;
        if (content == null || oth.content == null) return false;
        return content.equals(oth.content);
    } 

    /**
     * Gets the message's id.
     * @return An integer representing the message's id.
     */
    public int getMessageId() {
        return messageId;
    }

    /**
     * Sets the message's id.
     * @param messageId The message's id.
     */
    public void setMessageId(int messageId) {
        this.messageId = messageId;
    }

    /**
     * Gets the sender's id.
     * @return An integer representing the sender id.
     */
    public int getSenderId() {
        return senderId;
    }

    /**
     * Sets the sender id.
     * @param senderId The message's sender id.
     */
    public void setSenderId(int senderId) {
        this.senderId = senderId;
    }

    /**
     * Gets the receiver id.
     * @return An integer representing the receiver id.
     */
    public int getReceiverId() {
        return receiverId;
    }

    /**
     * Sets the receiver id.
     * @param receiverId The message's receiver id.
     */
    public void setReceiverId(int receiverId) {
        this.receiverId = receiverId;
    }

    /**
     * Gets the content of the message.
     * @return A string representing the message's content.
     */
    public String getContent() {
        return content;
    }

    /**
     * Sets the content of the message.
     * @param content The message's content.
     */
    public void setContent(String content) {
        this.content = content;
    }

}