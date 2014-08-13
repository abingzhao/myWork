
/** abstract class for linear lists */

package dataStructures;

public abstract class LinearList
{
   public abstract boolean isEmpty();
   public abstract int size();
   public abstract Object elementAt(int index);
   public abstract int indexOf(Object elem);
   public abstract void insertElementAt
                   (Object obj, int index);
   public abstract void removeElementAt(int index);
}
