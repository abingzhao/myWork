


/** Chain extended to include methods
  * makeEmpty and append.  */

package dataStructures;

import java.util.*;
import wrappers.*;

public class ExtendedChain extends Chain
{
   // data member
   protected ChainNode lastNode;

   // methods
   /** Remove the element with specified index.
     * All elements with higher index have their
     * index reduced by 1.
     * @exception ArrayIndexOutOfBoundsException thrown
     * if index is not between 0 and size - 1 */
   public void removeElementAt(int index)
   {// overrides Chain.removeElementAt
      if (index < 0 || index >= size)
         // invalid list position
         throw new ArrayIndexOutOfBoundsException
            ("Chain.elementAt: " +
             "index must be between 0 and size - 1");

      if (index == 0) // remove first node
         firstNode = firstNode.next;
      else 
      {  // use q to get to index-1'th
         ChainNode q = firstNode;
         for (int i = 0; i < index - 1; i++)
            q = q.next;

         q.next = q.next.next; // remove p from chain
         if (q.next == null) lastNode = q;
      }
      size--;
   }
   
   /** Insert an element with specified index.
     * All elements with equal or higher index
     * have their index increased by 1.
     * @exception ArrayIndexOutOfBoundsException thrown
     * if index is not between 0 and size */

   public void insertElementAt(Object obj, int index)
   {// overrides Chain.insertElementAt
      if (index < 0 || index > size)
         // invalid list position
         throw new ArrayIndexOutOfBoundsException
            ("FormulaBasedLinearList.insertElementAt: " +
             "index must be between 0 and size");

      if (index == 0)
      {   // insert at front
          firstNode = new ChainNode(obj, firstNode);
          if (firstNode.next == null) lastNode = firstNode;
      }
      else
      {   // find index - 1'th node
          ChainNode p = firstNode;
          for (int i = 0; i < index - 1; i++)
             p = p.next;

          // insert after p
          p.next = new ChainNode(obj, p.next);
          if (p.next.next == null) lastNode = p.next;
      }
      size++;
   }
   
   /** Make the chain empty. */
   public void makeEmpty()
   {
      firstNode = null;
      size = 0;
   }

   /** Add obj to the right end of the chain. */
   public void append(Object obj)
   {
      ChainNode y = new ChainNode(obj, null);
      if (firstNode == null)
         // chain is empty
         firstNode = lastNode = y;
      else
      {   // attach y next to lastNode
          lastNode.next = y;
          lastNode = y;
      }
      size++;
   }

   /** test program */
   public static void main(String [] args)
   {
      // test default constructor
      ExtendedChain x = new ExtendedChain();

      // test size
      System.out.println("Initial size is " +
                         x.size());

      // test isEmpty
      if (x.isEmpty())
         System.out.println("The list is empty");
      else System.out.println("The list is not empty");

      // test insertElementAt
      x.insertElementAt(new MyInteger(2), 0);
      x.insertElementAt(new MyInteger(6), 1);
      x.insertElementAt(new MyInteger(1), 0);
      x.insertElementAt(new MyInteger(4), 2);
      System.out.println("List size is " +
                         x.size());

      // test toString
      System.out.println("The list is " + x);

      // test indexOf
      int index = x.indexOf(new MyInteger(4));
      if (index < 0)
         System.out.println("4 not found");
      else System.out.println("The index of 4 is "
                              + index);

      index = x.indexOf(new MyInteger(3));
      if (index < 0)
         System.out.println("3 not found");
      else System.out.println("The index of 3 is "
                              + index);

      // test elementAt
      System.out.println("Element at 0 is " +
                         x.elementAt(0));
      System.out.println("Element at 3 is " +
                         x.elementAt(3));

      // test removeElementAt
      x.removeElementAt(1);
      System.out.println("The list is " + x);
      x.removeElementAt(2);
      System.out.println("The list is " + x);

      if (x.isEmpty())
         System.out.println("The list is empty");
      else System.out.println("The list is not empty");

      System.out.println("List size is " +
                         x.size());

      // test makeEmpty
      x.makeEmpty();
      if (x.isEmpty())
         System.out.println("The list is empty");
      else System.out.println("The list is not empty");

      System.out.println("List size is " +
                         x.size());

      // test append
      x.append(new MyInteger(5));
      x.append(new MyInteger(6));
      x.append(new MyInteger(7));
      System.out.println("The list is " + x);

      x.removeElementAt(2);
      x.append(new MyInteger(8));
      System.out.println("The list is " + x);
   }
}
