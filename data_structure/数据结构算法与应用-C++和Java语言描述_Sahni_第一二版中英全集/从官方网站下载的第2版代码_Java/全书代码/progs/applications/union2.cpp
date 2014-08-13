/** union/find using chains and size info
  * simulated pointers used */


package applications;

public class UnionFindSecondSolution
{
   static equivNode *node; // array of nodes
   
   /** initialize numberOfElements classes with one element each */
   static void initialize(int numberOfElements)
   {
      n = numberOfElements;
      node = new equivNode [n + 1];
      
      for (int e = 1; e <= n; e++)
         // node[e] is initialized so that its equivClass is e,
         // size is 1, and next is 0
         node[e] = new equivNode(e,1);
   }
   
   /** unite the classes i and j */
   static void union(int i, int j)
   {
      // make i smaller class
      if (node[i].size > node[j].size)
      {// swap i and j
         int t = i;
         i = j;
         j = i;
      }
   
      //  change equivClass values of smaller class
      int k;
      for (k = i; node[k].next != 0; k = node[k].next)
         node[k].equivClass = j;
      node[k].equivClass = j; // last node in chain
   
      // insert chain i after first node in chain j
      // and update new chain size
      node[j].size += node[i].size;
      node[k].next = node[j].next;
      node[j].next = i;
   }
   }
   
   /** find the class that contains element e */
   static int find(int e)
   {
      return node[e].equivClass;
   }

   private class equivNode
   {
      int equivClass;   // element class identifier
      int size;         // size of class
      int next;         // pointer to next element in class

      /** constructor */
      equivNode(int theClass, int theSize)
      {
         equivClass = theClass;
         size = theSize;
         // next has the default value 0
      }
   }

   /** test program */
   public static void main(String [] args)
   {
      initialize(10);
      union(1,2);
      union(3,4);
      union(1,3);
      for (int i = 1; i < 7; i++)
         System.out.println("Element 1 is in equivalence class " +
                             find(i));
   }
}

   
   
