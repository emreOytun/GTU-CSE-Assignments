package version4;

import java.util.AbstractList;
import java.util.Collection;
import java.util.Iterator;
import java.util.List;
import java.util.ListIterator;
import java.util.NoSuchElementException;

/**
 * LDLinkedList class extending AbstractList and implementing List interface.
 * It works with lazy deletion.
 * @author Emre Oytun
 */
@SuppressWarnings("unchecked")
public class LDLinkedList<E> extends AbstractList<E> implements List<E> {
    
    /**
     * Representing a node to keep the data, next node and a flag indicating it is deleted or not.
     */
    public static class Node<E> {
        private E data;
        private Node<E> next;
        private boolean deleted;

        /**
         * Initializes the node with the given data.
         * @param data The data that node is initialized.
         */
        public Node(E data) {
            this(data, null);
        } 

        /**
         * Initializes the node with the given data and the given next item.
         * @param data The data that node is initialized.
         * @param next The next node that this node points.
         */
        public Node(E data, Node<E> next) {
            this.data = data;
            this.next = next;
            this.deleted = false;
        }
    }

    /** Head of the list. */
    private Node<E> head;
    /** Size of the list. */
    private int size;
    /** Total number of lazy deleted nodes. */
    private int deletedNumber;

    /**
     * Initializes an empty list.
     */
    public LDLinkedList() {
        head = null;
        size = 0;
        deletedNumber = 0;
    }

    /**
     * Iterator implementation for LDLinkedList.
     */
    private class LDIter implements Iterator<E> {
        private Node<E> nextItem;
        private int index;
        private Node<E> lastItemReturned;

        /**
         * Initializes an iterator pointing the first element.
         */
        public LDIter() {
            if (head == null) nextItem = null;
            else if (!head.deleted) nextItem = head;
            else nextItem = findNext(head);
            index = 0;
            lastItemReturned = null;
        }

        /**
         * Checks if iterator has a next item.
         * @return A boolean indicating if iterator has next or not.
         */
        @Override
        public boolean hasNext() {
            return index != size;
        }

        /**
         * Returns the next element if there is one.
         * @throws NoSuchElementException if there is no next element.
         * @return Next element
         */
        @Override
        public E next() {
            if (!hasNext()) {
                throw new NoSuchElementException();
            }

            lastItemReturned = nextItem;
            nextItem = findNext(nextItem);
            ++index;
            return lastItemReturned.data;
        }

        /**
         * Removes the last returned item.
         * @throws IllegalStateException if there is no last returned item.
         */
        @Override
        public void remove() {
            if (lastItemReturned == null) {
                throw new IllegalStateException();
            }

            lastItemReturned.deleted = true;
            ++deletedNumber;
            checkLazyDelete();

            if (nextItem == lastItemReturned) {
                nextItem = findNext(nextItem);
            }
            else {
                --index;
            }
            lastItemReturned = null;
            --size;
        }
        
    }

    /**
     * List iterator implementation for LDLinkedList.
     */
    private class LDLinkedListIter implements ListIterator<E> {
        /** Next item's node. */
        private Node<E> nextItem;
        /** Last returned node. */
        private Node<E> lastItemReturned;
        /** Index of next item. */
        private int index;
        
        /**
         * Initializes the iterator with the given index.
         * @param index The index that iterator initializes with.
         * @throws IndexOutOfBoundsException if the given index is less than 0, or greater than size.
         */
        public LDLinkedListIter(int index) throws IndexOutOfBoundsException {
            // index can be equal to size meaning nextItem=null.
            if (index < 0 || index > size) {
                throw new IndexOutOfBoundsException();
            }
            
            // Set lastItemReturned and index here.
            this.lastItemReturned = null;
            this.index = index;
            
            if (index == size) {
                nextItem = null;
            }

            else if (index == 0 && !head.deleted) {
                nextItem = head;
            }
            
            else {
                if (head.deleted == false) nextItem = head;
                else nextItem = findNext(head);
                for (int i = 0; i < index; ++i) {
                    nextItem = findNext(nextItem);
                }
            }
        }
        
        /**
         * Checks if the list has next item.
         * @return A boolean indicating if the LDLinkedList has next item or not.
         */
        @Override
        public boolean hasNext() {
            return index != size;
        }

        /**
         * Returns the next item if it has one.
         * @throws NoSuchElementException if there is no next item.
         * @return The next element.
         */
        @Override
        public E next() throws NoSuchElementException {
            if (!hasNext()) {
                throw new NoSuchElementException();
            }

            lastItemReturned = nextItem;
            nextItem = findNext(nextItem);
            ++index;
            return lastItemReturned.data;
        }

        /**
         * Checks if the iterator has previous item.
         * @return A boolean indicating if the iterator has previous item or not.
         */
        @Override
        public boolean hasPrevious() { 
            return index != 0;
        }

        /**
         * Finds the previous node from the given index.
         * @param index The index of the given position.
         * @return The previous node of the given position.
         */
        private Node<E> findPrevious(int index) {
            Node<E> curNode = null;
        
            if (head == null) return null;
            if (!head.deleted) curNode = head;
            else curNode = findNext(head);

            for (int i = 0; i < index-1; ++i) {
                curNode = findNext(curNode);
            }
            return curNode;
        }

        /**
         * Returns the previous item if it has one.
         * @throws NoSuchElementException if it does not have previous item.
         * @return The previous item.
         */
        @Override
        public E previous() {
            if (!hasPrevious()) {
                throw new NoSuchElementException();
            }

            nextItem = findPrevious(index);
            lastItemReturned = nextItem;
            --index;
            return lastItemReturned.data;
        }

        /**
         * @return The next index.
         */
        @Override
        public int nextIndex() {
            return index;
        }

        /**
         * @return The previous index.
         */
        @Override
        public int previousIndex() {
            return index - 1;    
        }

        /**
         * Adds the given object before the next item.
         * @param data The data that will be added.
         * @throws NullPointerException if the given object is null.
         */
        @Override
        public void add(E data) {
            if (data == null) {
                throw new NullPointerException();
            }

            Node<E> newNode = new Node<>(data);
            // If list is empty, and nextItem=null :
            if (nextItem == head) {
                newNode.next = head;
                head = newNode;
            }
            else {
                Node<E> prevNode = findPrevious(index);
                prevNode.next = newNode;
                newNode.next = nextItem;
            }
            ++index;
            ++size;
            lastItemReturned = null;
        }

        /**
         * Removes the last item returned if there is one.
         * @throws IllegalStateException if there is no last item returned.
         */
        @Override
        public void remove() {
            // If next/previous methods have not been called, or if add/remove methods have been called before remove.
            if (lastItemReturned == null) {
                throw new IllegalStateException();
            }

            // Mark lastItemReturned as deleted.
            lastItemReturned.deleted = true;
            ++deletedNumber;

            // Check lazy delete.
            checkLazyDelete();

            // If nexItem and lastItemReturned point to the same node(after previous() method), then nextItem should proceed, and index should be same.
            // Otherwise, index is decremented.
            if (nextItem == lastItemReturned) {
                nextItem = findNext(nextItem);
            }
            else {
                --index;
            }
            --size;
            lastItemReturned = null; // release the object
        }

        /**
         * Sets the last item returned with the given object.
         * @param obj The object that will be set.
         * @throws IllegalStateException if there is no last item returned.
         * @throws NullPointerException if the given object is null.
         */
        @Override
        public void set(E obj) {
            // If next/previous methods have not been called, or if add/remove methods have been called before remove.
            if (lastItemReturned == null) {
                throw new IllegalStateException();
            }
            if (obj == null) {
                throw new NullPointerException();
            }

            lastItemReturned.data = obj;
        }
    }

    /** Finds the next node coming after the given node. 
     * @param curNode The current node that the next node will be found after.
    */
    private Node<E> findNext(Node<E> curNode) {
        do {
            curNode = curNode.next;
        } while (curNode != null && curNode.deleted); 
        return curNode;
    }

    /**
     * Checks the lazy deletion.
     * If there are 2 nodes marked as deleted, makes the physical deletion.
     */
    private void checkLazyDelete() {
        if (deletedNumber == 2) {
            Node<E> curNode = head;
            Node<E> prevNode = null;
            while (deletedNumber != 0) {
                if (curNode.deleted) {
                    Node<E> nextNode = curNode.next;
                    if (prevNode == null) head = nextNode;
                    else prevNode.next = nextNode;
                    --deletedNumber;
                    curNode = nextNode;
                }
                else {
                    prevNode = curNode;
                    curNode = curNode.next;
                }
            }
        }
    }

    /**
     * Adds the given object at the end of the list.
     * @param obj The object that will be added to the list.
     * @throws NullPointerException if the given object is null.
     * @return Boolean indicating the list is changed.
     */
    @Override
    public boolean add(E obj) {
        if (obj == null) {
            throw new NullPointerException();
        }

        Node<E> newNode = new Node<E>(obj);
        if (head == null) {
            head = newNode;
        }
        else {
            Node<E> curNode = head;
            while (curNode.next != null) {
                curNode = curNode.next;
            }
            curNode.next = newNode;
        }
        ++size;
        return true;
    }

    /**
     * @return A list iterator pointing the beginning of the list.
     */
    @Override
    public ListIterator<E> listIterator() {
        return new LDLinkedListIter(0);
    }

    /**
     * @param index The index that list iterator starts with.
     * @return A list iterator pointing the given index.
     */
    @Override
    public ListIterator<E> listIterator(int index) {
        return new LDLinkedListIter(index);
    }

    /**
     * @return An integer representing the size of the list.
     */
    @Override
    public int size() {
        return size;
    }

    /**
     * @return A boolean indicating if the list is empty.
     */
    @Override
    public boolean isEmpty() {
        return size == 0;
    }

    /**
     * Checks if the list contains the given object.
     * @param o The object which will be checked if it is inside the list.
     * @return A boolean indicating if the list has the given object.
     */
    @Override
    public boolean contains(Object o) {
       ListIterator<E> it = listIterator();
       boolean isFound = false;
       while (it.hasNext() && !isFound) {
            if (it.next().equals(o)) {
                isFound = true;
            }
       }
       return isFound;
    }

    /**
     * Converts the list into an array of object.
     * @return An object array containing the elements of the list.
     */
    @Override
    public Object[] toArray() {
        Object[] arr = new Object[size];
        ListIterator<E> it = new LDLinkedListIter(0);
        
        for (int i = 0; it.hasNext(); ++i) {
            arr[i] = it.next();
        }
        return arr;
    }

    /**
     * Adds the given item into the given index.
     * @param index The index that given element will be added into.
     * @param element The element that will be added.
     * @throws IndexOutOfBoundsException if the given index is not valid.
     * @throws NullPointerException if the given element is null.
     */
    @Override
    public void add(int index, E element) {
        if (index < 0 || index > size) {
            throw new IndexOutOfBoundsException();
        }
        if (element == null) {
            throw new NullPointerException();
        }
        
        Node<E> newNode = new Node<E>(element);
        // List is empty, or it ll be added at the beginning.
        if (index == 0) {
            newNode.next = head;
            head = newNode;
        }
        else {
            Node<E> curNode = head;
            int i = -1;
            if (!head.deleted) i = 0;
            while (i != index-1) {
                curNode = curNode.next;
                if (!curNode.deleted) ++i;
            }
            newNode.next = curNode.next;
            curNode.next = newNode;
        }
        ++size;
    }

    /**
     * Removes the item from the given index.
     * @param index The index from which the element is removed.
     */
    @Override
    public E remove(int index) {
        if (index < 0 || index >= size) {
            throw new IndexOutOfBoundsException();
        }

        E result = null;
        if (index == 0 && !head.deleted) {
            head.deleted = true;
            result = head.data;
        }
        else {
            Node<E> curNode = null;
            if (head.deleted == false) curNode = head;
            else curNode = findNext(head);
            for (int i = 0; i < index; ++i) {
                curNode = findNext(curNode);
            }
            curNode.deleted = true;
            result = curNode.data;
        }
        ++deletedNumber;
        --size;
        checkLazyDelete();
        return result;
    }
    
    /**
     * Removes the given object if the list contains it.
     * @param o The object that will be removed.
     * @return A boolean indicating if the object is found and removed or not.
     */
    @Override
    public boolean remove(Object o) {
        boolean isFound = false;

        if (size == 0) return false;

        else if (!head.deleted && head.data.equals(o)) {
            isFound = true;
            head.deleted = true;
        }

        else {
            Node<E> curNode = head;
            if (head.deleted) curNode = findNext(head);
            while (curNode != null && !isFound) {
                if (curNode.data.equals(o)) {
                    isFound = true;
                    curNode.deleted = true;
                }
                else {
                    curNode = findNext(curNode);
                }
            }
        }

        if (isFound) {
            ++deletedNumber;
            --size;
            checkLazyDelete();
        }
        return isFound;
    }

    /**
     * Gets the element from the given index.
     * @param index The index of the element that will be returned.
     * @throws IndexOutOfBoundsException if the given index is invalid.
     */
    @Override
    public E get(int index) {
        if (index < 0 || index >= size) {
            throw new IndexOutOfBoundsException();
        }
        ListIterator<E> listIterator = new LDLinkedListIter(index);
        return listIterator.next();
    }

    /**
     * Updates the element whose index is given.
     * @param index The index of the element that will be updated.
     * @param element The element that replaces the old element.
     * @throws IndexOutOfBoundsException if the given index is invalid.
     */
    @Override
    public E set(int index, E element) {
        if (index < 0 || index >= size) {
            throw new IndexOutOfBoundsException();
        }

        if (element == null) {
            throw new NullPointerException();
        }

        Node<E> curNode = null;
        if (head.deleted == false) curNode = head;
        else curNode = findNext(head);
        for (int i = 0; i < index; ++i) {
            curNode = findNext(curNode);
        }
        E result = curNode.data;
        curNode.data = element;
        return result;
    }

    /**
     * Gets the index of the given object.
     * @param o The object whose index will be found and returned.
     * @return An integer representing the index of the object.
     */
    @Override
    public int indexOf(Object o) {
        int idx = -1;
        Node<E> curNode = null;
        if (head.deleted == false) curNode = head;
        else curNode = findNext(head);
        for (int i = 0; i < size && idx == -1; ++i) {
            if (curNode.data.equals(o)) {
                idx = i;
            }
            else {
                curNode = findNext(curNode);
            }
        }
        return idx;
    }

    /**
     * Gets the last index of the given object.
     * @param o The object whose last index will be found and returned.
     * @return An integer representing the last index of the object.
     */
    @Override
    public int lastIndexOf(Object o) {
        if (head == null) return -1;
        Node<E> curNode = head;
        if (head.deleted) curNode = findNext(head);
        int lastIndex = -1;
        int idx = 0;
        while (curNode != null) {
            if (!curNode.deleted) {
                if (curNode.data.equals(o)) {
                    lastIndex = idx;
                }
                ++idx;
            }
            curNode = curNode.next;
        }
        return lastIndex;
    }

    /**
     * Checks if this list contains all of the elements of the specified collection.
     * If types are not matched doesn't matter, returns false.
     * @throws NullPointerException if the given collection is null.
     */
    @Override
    public boolean containsAll(Collection<?> c) {
        if (c == null) {
            throw new NullPointerException();
        }

        Iterator<?> it = c.iterator();
        
        boolean contains = true;
        while (it.hasNext() && contains) {
            if (indexOf(it.next()) == -1) {
                contains = false;
            }
        }
        return contains;
    }

    /**
     * Convers the list to an array of the given type.
     * If size of the given array is big enough, then elements are put into this array.
     * Otherwise, the new array will be returned.
     * @param a The array that indicates the return type.
     * @throws NullPointerException if the given array is null.
     * @return An array containing all of the elements in the list.
     */
    @Override
    public <T> T[] toArray(T[] a) {
        if (a == null) {
            throw new NullPointerException();
        }

        T[] resultArray = null;
        if (a.length == size) resultArray = a;
        else resultArray = (T[]) new Object[size];

        ListIterator<E> it = new LDLinkedListIter(0);
        for (int i = 0; i < size; ++i) {
            Object element = it.next();
            if (!a.getClass().getComponentType().isInstance(element)) {
                throw new ArrayStoreException();
            }
            else {
                resultArray[i] = (T) element;
            }
        }
        return resultArray;
    }

    /**
     * Adds all of the elements in the collection to the list.
     * @throws NullPointerException if the given array is null.
     * @return A boolean indicating if the list is changed.
     */
    @Override
    public boolean addAll(Collection<? extends E> c) {
        if (c == null) {
            throw new NullPointerException();
        }
        
        Iterator<?> it = c.iterator();
        ListIterator<E> listIterator = new LDLinkedListIter(size);
        while (it.hasNext()) {
            listIterator.add((E) it.next());
        }
        return true;
    }

     /**
     * Adds all of the elements in the collection to the list.
     * @throws IndexOutOfBoundsException if the given index is invalid.
     * @throws NullPointerException if the given array is null.
     * @return A boolean indicating if the list is changed.
     */
    @Override
    public boolean addAll(int index, Collection<? extends E> c) {
        if (index < 0 || index > size) {
            throw new IndexOutOfBoundsException();
        }
        if (c == null) {
            throw new NullPointerException();
        }

        ListIterator<E> listIterator = new LDLinkedListIter(index);
        Iterator<?> it = c.iterator();
        while (it.hasNext()) {
            E obj = (E) it.next();
            listIterator.add(obj);
        }
        return true;
    }

    /**
     * Returns an iterator pointing the first element.
     */
    @Override
    public Iterator<E> iterator() {
        return new LDIter();
    }

    /**
     * Removes all elements of the given collection from the list.
     * @throws NullPointerException if the given array is null.
     * @return A boolean indicating if the list is changed.
     */
    @Override
    public boolean removeAll(Collection<?> c) {
        if (c == null) {
            throw new NullPointerException();
        }

        Iterator<E> it = (Iterator<E>) c.iterator();
        while (it.hasNext()) {
            E obj = it.next();
            while (contains(obj)) {
                remove(obj);
            }
        }
        return true;
    }

    /**
     * Retains all of the elements of the collection.
     * @throws NullPointerException if the given array is null.
     * @return A boolean indicating if the list is changed.
     */
    @Override
    public boolean retainAll(Collection<?> c) {
        if (c == null) {
            throw new NullPointerException();
        }

        ListIterator<E> listIterator = new LDLinkedListIter(0);
        while (listIterator.hasNext()) {
            if (!c.contains(listIterator.next())) {
                listIterator.remove();
            }
        } 
        return true;
    }

    /**
     * Creates a sublist from the given indexes.
     * @param fromIndex The starting index inclusive.
     * @param toIndex The last index exclusive.
     * @throws IndexOutOfBoundsException if the given indexes are not valid.
     */
    public List<E> subList(int fromIndex, int toIndex) {
        if (fromIndex < 0 || toIndex > size || fromIndex > toIndex) {
            throw new IndexOutOfBoundsException();
        }

        List<E> list = new LDLinkedList<E>();
        ListIterator<E> curIt = new LDLinkedListIter(fromIndex);
        while (curIt.nextIndex() != toIndex) {
            list.add(curIt.next());
        }
        return list;
    }

    /**
     * Clears the list.
     */
    @Override
    public void clear() {
        if ((size + deletedNumber) % 2 == 0) {
            head = null;
        }
        else {
            head.next = null;
        }
        size = 0;
    }

    /**
     * Returns the list to string as name indicates.
     * @return A string representing the elements of the list.
     */
    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder();
        builder.append("[");
        Node<E> curNode = head;
        while (curNode != null) {
            builder.append(curNode.data + ",");
            curNode = curNode.next;
        }
        if (size + deletedNumber != 0) builder.setCharAt(builder.length()-1, ']');
        else builder.append("]");
        return builder.toString();
    }

}