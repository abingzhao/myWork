


/** singly linked circular list with head node */

package dataStructures;

import wrappers.*;

public class CircularWithHead
{
   // data members
   protected ChainNode headNode;

   // constructor
   /** create a circlar list that is empty */
   public CircularWithHead()
   {
       headNode = new ChainNode();
       headNode.next = headNode;
   }

   // methods
   /** @return index of first occurrence of elem,
     * return -1 if elem not in list */
   public int indexOf(Object elem)
   {
      // put elem in head node
      headNode.element = elem;

      // search the list for elem
      ChainNode currentNode = headNode.next;
      int index = 0;  // index of currentNode
      while (!currentNode.element.equals(elem))
      {
         // move to next node
         currentNode = currentNode.next;
         index++;
      }

      // make sure we found matching element
      if (currentNode == headNode) return -1;
      else return index;
   }
   
   /** test program */
   public static void main(String [] args)
   {
      // create a circluar list
      CircularWithHead x = new CircularWithHead();
      for (int i = 0; i <= 4; i++)
      {   // insert i at front
          ChainNode y = new ChainNode(new MyInteger(i),
                            x.headNode.next);
          x.headNode.next = y;
      }

      // search
      for (int i = 0; i <=5; i++)
          System.out.println(i + " is element " +
                 x.indexOf(new MyInteger(i)));
   }
}
