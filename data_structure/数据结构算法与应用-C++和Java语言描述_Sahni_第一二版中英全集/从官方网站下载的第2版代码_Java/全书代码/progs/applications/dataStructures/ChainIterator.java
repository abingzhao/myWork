


/** iterator for Chain */

package dataStructures;

import java.util.*;

public class ChainIterator implements Enumeration
{
   // data member
   private ChainNode nextNode;

   // constructor
   public ChainIterator(Chain theChain)
   {
      nextNode = theChain.firstNode;
   }

   // methods
   /** @return true iff list has more elements */
   public boolean hasMoreElements()
   {
      return nextNode != null;
   }

   /** @return next element in list
     * @exception ArrayIndexOutOfBoundsException
     * thrown if there is no next element */

   public Object nextElement()
   {
      if (nextNode != null)
      {
         Object obj = nextNode.element;
         nextNode = nextNode.next;
         return obj;
      }
      else throw new ArrayIndexOutOfBoundsException
              ("FormualBasedLinearListIterator."
                + "nextElement: No next element");
   }

   /** test program */
   public static void main(String [] args)
   {
      // create the list [0, 1, 2, 3, 4]
      Chain x = new Chain();
      x.insertElementAt(new Integer(4), 0);
      x.insertElementAt(new Integer(3), 0);
      x.insertElementAt(new Integer(2), 0);
      x.insertElementAt(new Integer(1), 0);
      x.insertElementAt(new Integer(0), 0);

      // output using an iterator
      Enumeration y = x.elements();
      while (y.hasMoreElements())
         System.out.print(y.nextElement() + " ");
      System.out.println();
   }
}
