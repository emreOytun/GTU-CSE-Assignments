import java.util.LinkedHashMap;
import java.util.Set;

/**
 * The class to keep Character-info pairs constructed from the given string along with the map size information.
 * @author Emre Oytun
 */
public class myMap {
    private LinkedHashMap<Character, info> map;
    private int mapSize;
    private String str;
    
    /**
     * The no-args constructor to initialize the map without giving the string to convert.
     */
    public myMap() {
        map = new LinkedHashMap<>();
        mapSize = 0;
        str = "";
    }

    /**
     * The constructor to initialize the map using a string.
     * @param str The string that will be converted to an instance of myMap class.
     */
    public myMap(String str) {
        this();

        // Preprocess the string before building the map.
        System.out.println("Original String: \t" + str);
        str = str.toLowerCase();
        str = str.replaceAll("[^a-z\\s]", "");
        System.out.println("Preprocessed String: \t" + str);
        if (!checkValidity(str)) {
            System.out.println("WARNING: The preprocessed string does not have any characters.");
        }
        System.out.println();

        this.str = str;
        
        // Build the map using the str.
        buildMap();
    }

    /**
     * The method to check if the string has any characters.
     * @param str The string that will be checked.
     * @return A boolean indicating if the preprocesseed string is valid or not.
     */
    private boolean checkValidity(String str) {
        if (str.length() == 0) return false;
        for (int i = 0; i < str.length(); ++i) {
            if (str.charAt(i) != ' ') {
                return true;
            }
        }
        return false;
    }

    /**
     * The method to add/update new Character-info pair.
     * @param ch The key to the map.
     * @param chInfo The value of the given character key.
     */
    public void put(Character ch, info chInfo) {
        if (map.put(ch, chInfo) == null) ++mapSize;
    }

    /**
     * The method to get the value of the given character.
     * @param ch The character key whose value will be returned.
     * @return The value that is found. Null otherwise.
     */
    public info get(Character ch) {
        return map.get(ch);
    }

    /**
     * The method to return the size of the map.
     * @return An integer representing the size of the map.
     */
    public int size() {
        return mapSize;
    }

    /**
     * The method to get the key set of the map.
     * @return A set containing the keys of the map.
     */
    public Set<Character> keySet() {
        return map.keySet();
    }

    /**
     * The method to build the map using the given string by mapping each letter.
     */
    private void buildMap() {
        String[] words = str.split(" ");
        for (String word : words) {
            for (int i = 0; i < word.length(); ++i) {
                Character ch = word.charAt(i);
                info chInfo = map.get(ch);
                if (chInfo == null) {
                    chInfo = new info();
                    ++mapSize;
                }
                chInfo.push(word);
                map.put(ch, chInfo);
            }
        }
    }

    /**
     * The method to print the map properly.
     */
    public void printMap() {
        for (Character ch : map.keySet()) {
            System.out.println("Letter: " + ch + " - " + map.get(ch));
        }
    }


}
