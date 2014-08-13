
/** linked implementation of LinearList
  * using simulated pointers */

package dataStructures;

import wrappers.*;

public class SimulatedChain extends LinearList
{
   // data members
   protected int firstNode;
   protected int size;
   public static SimulatedSpace2 S;

   // constructor
   /** create a list that is empty */
   public SimulatedChain()
   {
       firstNode = -1;
       size = 0;
   }

   // methods
   /** @return true iff list is empty */
   public boolean isEmpty()
   {
       return size == 0;
   }

   /** @return current number of elements in list */
   public int size()
   {
      return size;
   }

   /** @return element with specified index
     * @exception ArrayIndexOutOfBoundsException thrown
     * if index is not between 0 and size - 1 */

   public Object elementAt(int index)
   {
      if (index < 0 || index >= size)
         // invalid list position
         throw new ArrayIndexOutOfBoundsException
            ("Chain.elementAt: " +
             "index must be between 0 and size - 1");

      // move to desired node
      int currentNode = firstNode;
      for (int i = 0; i < index; i++)
         currentNode = S.node[currentNode].next;

      return S.node[currentNode].element;
   }
   
   /** @return index of first occurrence of elem,
     * return -1 if elem not in list */
   public int indexOf(Object elem)
   {
      // search the chain for elem
      int currentNode = firstNode;
      int index = 0;  // index of currentNode
      while (currentNode != -1 &&
             !S.node[currentNode].element.equals(elem))
      {
         // move to next node
         currentNode = S.node[currentNode].next;
         index++;
      }

      // make sure we found matching element
      if (currentNode == -1) return -1;
      else return index;
   }
   
   /** Remove the element with specified index.
     * All elements with higher index have their
     * index reduced by 1.
     * @exception ArrayIndexOutOfBoundsException thrown
     * if index is not between 0 and size - 1 */
   public void removeElementAt(int index)
   {
      if (index < 0 || index >= size)
         // invalid list position
         throw new ArrayIndexOutOfBoundsException
            ("Chain.removeElementAt: " +
             "index must be between 0 and size - 1");

      if (index == 0) // remove first node
         firstNode = S.node[firstNode].next;
      else 
      {  // use q to get to index-1'th
         int q = firstNode;
         for (int i = 0; i < index - 1; i++)
            q = S.node[q].next;

         // remove p from chain
         S.node[q].next = S.node[S.node[q].next].next;
      }
      size--;
   }
   
   /** Insert an element with specified index.
     * All elements with equal or higher index
     * have their index increased by 1.
     * @exception ArrayIndexOutOfBoundsException thrown
     * if index is not between 0 and size */

   public void insertElementAt(Object obj, int index)
   {
      if (index < 0 || index > size)
         // invalid list position
         throw new ArrayIndexOutOfBoundsException
            ("FormulaBasedLinearList.insertElementAt: " +
             "index must be between 0 and size");

      if (index == 0)
         // insert at front
         firstNode = S.allocateNode(obj, firstNode);
      else
      {   // find index - 1'th node
          int p = firstNode;
          for (int i = 0; i < index - 1; i++)
             p = S.node[p].next;

          // insert after p
          S.node[p].next = S.allocateNode(obj,
                              S.node[p].next);
      }
      size++;
   }
   
   /** convert to a string */
   public String toString()
   {
      StringBuffer s = new StringBuffer("["); 
      int currentNode = firstNode;
      while(currentNode != -1)
      {
         if (currentNode != firstNode)
            // not first element
            s.append(", ");
         s.append(S.node[currentNode].element.
                  toString());
         currentNode = S.node[currentNode].next;
      }
      s.append("]");

      // create equivalent String
      return new String(s);
   }

   /** test program */
   public static void main(String [] args)
   {
      // create simulated space with 100 nodes
      SimulatedChain.S = new SimulatedSpace2(100);

      // test default constructor
      SimulatedChain x = new SimulatedChain();

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
   }
}
