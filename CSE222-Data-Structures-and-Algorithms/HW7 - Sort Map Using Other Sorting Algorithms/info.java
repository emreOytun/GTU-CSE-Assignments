import java.util.ArrayList;

/**
 * The class to keep the informations related to a letter in the map.
 * @author Emre Oytun
 */
public class info {
    private int count;
    private ArrayList<String> words;

    /**
     * No-args constructor to initialize an instance of info class.
     */
    public info() {
        count = 0;
        words = new ArrayList<>();
    }

    /**
     * The method to add a new word into the words array.
     * @param word The new word that will be added.
     */
    public void push(String word) {
        words.add(word);
        ++count;
    }

    /**
     * The method to get the count of words.
     * @return An integer representing the count of words.
     */
    public int getCount() {
        return count;
    }

    /**
     * The method to convert the count and words into a String object properly.
     * @return A String representing the count and words.
     */
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Count: " + count + " - Words: [");
        for (int i = 0; i < count; ++i) {
            sb.append(words.get(i) + ", ");
        }
        if (count != 0) {
            sb.replace(sb.length()-2, sb.length(), "]");
        }
        return sb.toString();
    }
}
