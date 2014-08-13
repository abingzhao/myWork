package dataStructures;

import java.util.*;
import applications.*;
import exceptions.*;
import utilities.*;

public abstract class Graph
{
   // ADT methods
   public abstract int vertices();
   public abstract int edges();
   public abstract boolean existsEdge(int i, int j);
   public abstract void putEdge(Object theEdge);
   public abstract void removeEdge(int i, int j);
   public abstract int degree(int i);
   public abstract int inDegree(int i);
   public abstract int outDegree(int i);

   // create an iterator for vertex i
   public abstract Iterator iterator(int i);

   // class data members
   private static int [] reach;  // used to label vertices
   private static int label;     // the label to use
   private static int destination;
   private static int [] path;   // used to store a path
   private static int length;    // path length

   // implementation independent methods
   /** breadth-first search
     * reach[i] is set to label for all vertices reachable
     * from vertex v */
   public void bfs(int v, int [] reach, int label)
   {
      ArrayQueue q = new ArrayQueue(10);
      reach[v] = label;
      q.put(new Integer(v));
      while (!q.isEmpty())
      {
         // remove a labeled vertex from the queue
         int w = ((Integer) q.remove()).intValue();

         // mark all unreached vertices adjacent from w
         Iterator iw = iterator(w);
         while (iw.hasNext())
         {// visit an adjacent vertex of w
            int u = ((EdgeNode) iw.next()).vertex; 
            if (reach[u] == 0)
            {// u is an unreached vertex
               q.put(new Integer(u));
               reach[u] = label; // mark reached
            }
         }
      }
   }
   
   /** depth-first search
     * reach[i] is set to label for all vertices reachable
     * from vertex v */
   public void dfs(int v, int [] reach, int label)
   {
      Graph.reach = reach;
      Graph.label = label;
      rDfs(v);
   }
   
   /** recursive dfs method */
   private void rDfs(int v)
   {
      reach[v] = label;
      Iterator iv = iterator(v);
      while (iv.hasNext())
      {// visit an adjacent vertex of v
         int u = ((EdgeNode) iv.next()).vertex; 
         if (reach[u] == 0)  // u is an unreached vertex
            rDfs(u);
      }
   }

   /** find a path from s to d
     * @return the path in an array using positions 0 on up
     * @return null if there is no path */
   public int [] findPath(int s, int d)
   {
      // initialize for recursive path finder
      int n = vertices();
      path = new int [n];
      path[0] = s;              // first vertex is always s
      length = 0;               // current path length
      destination = d;
      reach = new int [n + 1];  // by default reach[i] = 0 initially
      
      // search for path
      if (s == d || rFindPath(s))
      {// a path was found, trim array to path size
         int [] newPath = new int [length + 1];
         // copy from old space to new space
         System.arraycopy(path, 0, newPath, 0, length + 1);
         return newPath;
      }
      else
         return null;
   }
   
   /** real path finder, performs a depth-first search
     * @param s source vertex not equal to destination
     * @return true iff a path to destination is found */
   private boolean rFindPath(int s)
   {
      reach[s] = 1;
      Iterator is = iterator(s);
      while (is.hasNext())
      {// visit an adjacent vertex of s
         int u = ((EdgeNode) is.next()).vertex; 
         if (reach[u] == 0)   // u is an unreached vertex
         {// move to vertex u
            length++;
            path[length] = u; // add u to path
            if (u == destination) return true;
            if (rFindPath(u))
               return true;
            // no path from u to destination
            length--;         // remove u from path
         }
      }
      return false;
   }

   /** verify that the graph is an undirected graph
     * @exception UndefinedMethodException if graph is directed  */
   public void verifyUndirected(String theMethodName)
   {
      Class c = getClass();   // class of this
      if (c == AdjacencyGraph.class ||
          c == AdjacencyWGraph.class ||
          c == LinkedGraph.class ||
          c == LinkedWGraph.class)
         return;

      // not an undirected graph
      throw new UndefinedMethodException
         ("Graph." + theMethodName + " is for undirected graphs only");
   }

   /** verify that the graph is a directed graph
     * @exception UndefinedMethodException if graph is undirected  */
   public void verifyDirected(String theMethodName)
   {
      Class c = getClass();   // class of this
      if (c == AdjacencyDigraph.class ||
          c == AdjacencyWDigraph.class ||
          c == LinkedDigraph.class ||
          c == LinkedWDigraph.class)
         return;

      // not a digraph
      throw new UndefinedMethodException
         ("Graph." + theMethodName + " is for directed graphs only");
   }

   /** verify that the graph is a weighted undirected graph
     * @exception UndefinedMethodException if graph is not
     * weighted and undirected  */
   public void verifyWeightedUndirected(String theMethodName)
   {
      Class c = getClass();   // class of this
      if (c == AdjacencyWGraph.class ||
          c == LinkedWGraph.class)
         return;

      // not weighted and undirected
      throw new UndefinedMethodException
         ("Graph." + theMethodName + " is for weighted undirected graphs only");
   }

   /** verify that the graph is a weighted graph
     * @exception UndefinedMethodException if graph is not
     * weighted */
   public void verifyWeighted(String theMethodName)
   {
      Class c = getClass();   // class of this
      if (c == AdjacencyWGraph.class ||
          c == AdjacencyWDigraph.class ||
          c == LinkedWGraph.class ||
          c == LinkedWDigraph.class)
         return;

      // not weighted
      throw new UndefinedMethodException
         ("Graph." + theMethodName + " is for weighted graphs only");
   }

   /** @return true iff graph is connected */
   public boolean connected()
   {
      // make sure this is an undirected graph
      verifyUndirected("connected");

      int n = vertices();
   
      reach = new int [n + 1];  // by default reach[i] = 0
      
      // mark vertices reachable from vertex 1
      dfs(1, reach, 1);
      
      // check if all vertices marked
      for (int i = 1; i <= n; i++)
         if (reach[i] == 0)
            return false;
      return true;
   }

   /** label the components of an undirected graph
    *  @return the number of components
    *  set c[i] to be the component number of vertex i */
   public int labelComponents(int [] c)
   {
      // make sure this is an undirected graph
      verifyUndirected("labelComponents");

      int n = vertices();
   
      // assign all vertices to no component
      for (int i = 1; i <= n; i++)
         c[i] = 0;
   
      label = 0;  // ID of last component
      // identify components
      for (int i = 1; i <= n; i++)
         if (c[i] == 0)  // vertex i is unreached
         {// vertex i is in a new component
            label++;
            bfs(i, c, label); // mark new component
         }
   
      return label;
   }

   /** @return false iff the digraph has no topological order
     * @param theOrder[0:n-1] is set to a topological order when
     * such an order exists */
   public boolean topologicalOrder(int [] theOrder)
   {
      // make sure this is a digraph
      verifyDirected("topologicalOrder");

      int n = vertices();
      
      // compute in-degrees, default initial values are 0
      int [] inDegree = new int [n + 1];
      for (int i = 1; i <= n; i++)
      {// edges out of vertex i
         Iterator ii = iterator(i);
         while (ii.hasNext())
         {// visit an adjacent vertex of i
            int u = ((EdgeNode) ii.next()).vertex; 
            inDegree[u]++;
         }
      }
      
      // stack vertices with zero in-degree
      ArrayStack stack = new ArrayStack(10);
      for (int i = 1; i <= n; i++)
         if (inDegree[i] == 0)
            stack.push(new Integer(i));
      
      // generate topological order
      int i = 0;  // cursor for array s
      while (!stack.empty())
      {// select from stack
         int nextVertex = ((Integer) stack.pop()).intValue();
         theOrder[i++] = nextVertex;
         // update in-degrees
         Iterator iNextVertex = iterator(nextVertex);
         while (iNextVertex.hasNext())
         {// visit an adjacent vertex of nextVertex
            int u = ((EdgeNode) iNextVertex.next()).vertex; 
            inDegree[u]--;
            if (inDegree[u] == 0)
               stack.push(new Integer(u));
         }
      }
      return (i == n);
   }

   /** bipartite cover support class, data members, and methods */
   private static class NodeType
   {
      // data members
      int left,  // pointer to previous node
          right; // pointer to next node
   }
   
   // class data member of Graph
   static int [] bin;   // pointer to first node in bin
   static NodeType [] node;

   /** create b empty bins and n nodes */
   private static void createBins(int b, int n)
   {
      bin = new int [b + 1];
      node = new NodeType [n + 1];
      for (int i = 1; i <= n; i++)
         node[i] = new NodeType();
   }
   
   /** insert v into bin b unless b is zero */
   private static void insertBins(int b, int v)
   {
      if (b == 0)
         return;   // do not insert in bin 0

      node[v].left = b; // add at left end of bin b
      if (bin[b] != 0)  // bin b is not empty
         node[bin[b]].left = v;
      node[v].right = bin[b];
      bin[b] = v;
   }
   
   /** move vertex v from its current bin to bin toBin
     * @param bMax rightmost nonempty bin */
   private static void moveBins(int bMax, int toBin, int v)
   {
      // nodes to the left and right of v
      int l = node[v].left;
      int r = node[v].right;
   
      // delete v from current bin
      if (r != 0)  // v has a node to its left
         node[r].left = node[v].left;
      if (l > bMax || bin[l] != v) // not left-most one
         node[l].right = r;
      else  // left-most in bin l
         bin[l] = r;
   
      // add to bin toBin
      insertBins(toBin, v);
   }
   
   /** @return -1 if the bipartite graph has no cover
     * @return cover size if there is a cover
     * @param theLabel is bipartite labeling, theLabel[i] = 1 iff i is in A
     * @param theCover theCover[i], i >= 0 is set to
     * the cover (if there is one) */
   public int bipartiteCover(int [] theLabel, int [] theCover)
   {
      int n = vertices();
   
      // create structures
      int sizeOfA = 0;
      for (int i = 1; i <= n; i++) // find size of set A
         if (theLabel[i] == 1) sizeOfA++;
      int sizeOfB = n - sizeOfA;
      createBins(sizeOfB, n);
      int [] newVerticesCovered = new int [n + 1];
         // vertex i covers newVerticesCovered[i] uncovered vertices of B
      boolean [] changed = new boolean [n + 1];
         // changed[i] is true iff newVerticesCovered[i] has changed
      boolean [] covered = new boolean [n + 1];
         // covered[i] is true iff vertex i is covered
      ArrayStack stack = new ArrayStack(10);
      
      // initialize
      for (int i = 1; i <= n; i++)
         if (theLabel[i] == 1)
         {// i is in A
            newVerticesCovered[i] = degree(i); // i covers this many
            insertBins(newVerticesCovered[i], i);
         }
      
      // construct cover
      int numberCovered = 0, // # of B vertices vertices
          maxBin = sizeOfB;  // max bin that may be
                             // nonempty
      int coverSize = 0;     // number of A vertices in cover
      while (maxBin > 0)     // search all bins
         if (bin[maxBin] != 0)            // bin maxBin is not empty
         {
            int v = bin[maxBin];          // first vertex
            theCover[coverSize++] = v;    // add v to cover
            // label newly covered vertices
            Iterator iv = iterator(v);
            while (iv.hasNext())
            {
               int j = ((EdgeNode) iv.next()).vertex; 
               if (!covered[j])          // j not covered yet
               {
                  covered[j] = true;
                  numberCovered++;
                  // update New
                  Iterator ij = iterator(j);
                  while (ij.hasNext())
                  {
                     int k = ((EdgeNode) ij.next()).vertex; 
                     newVerticesCovered[k]--;        // j does not count
                     if (!changed[k])
                     {
                        stack.push(new Integer(k));  // stack once only
                        changed[k] = true;
                     }
                  }
               }   
            }
            // update bins
            while (!stack.empty())
            {
               int k = ((Integer) stack.pop()).intValue();
               changed[k] = false;
               moveBins(sizeOfB, newVerticesCovered[k], k);
            }
         }
         else maxBin--; // go to next bin
      
      return (numberCovered == sizeOfB) ? coverSize : -1;
   }

   /** find a min cost spanning tree using Kruskal's method
     * @return false iff the weighted undirected graph is not connected
     * @param spanningTreeEdges[0:n-2] has the min-cost-tree edges when done */
   public boolean kruskal(WeightedEdge [] spanningTreeEdges)
   {
      verifyWeightedUndirected("kruskal");

      int n = vertices();
      int e = edges();
      // set up array of graph edges
      ComparableEdge [] edge = new ComparableEdge [e + 1];
      int k = 0;        // cursor for edge[]
      for (int i = 1; i <= n; i++)
      {// get all edges incident to i
         Iterator ii = iterator(i);
         while (ii.hasNext())
         {
            WeightedEdgeNode w = (WeightedEdgeNode) ii.next();
            if (i < w.vertex)  // add w to edge array
               edge[++k] = new ComparableEdge(i, w.vertex,
                                         (Comparable) w.weight);
         }
      }
      // put edges in min heap
      MinHeap minHeap = new MinHeap(1);
      minHeap.initialize(edge, e);
      
      FastUnionFind uf = new FastUnionFind(n); // union/find structure
      
      // extract edges in cost order and select/reject
      k = 0;  // use as cursor for t now
      while (e > 0  && k < n - 1)
      {// spanning tree not complete & edges remain
         ComparableEdge x = (ComparableEdge) minHeap.removeMin();
         e--;
         int a = uf.find(x.vertex1);
         int b = uf.find(x.vertex2);
         if (a != b)
         {// select edge x
            spanningTreeEdges[k++] = new WeightedEdge
                                     (x.vertex1, x.vertex2, x.weight);
            uf.union(a,b);
         }
      }
      return (k == n - 1);
   }

   /** Bellman and Ford algorithm to find the shortest paths from vertex s.
     * Graph may have edges with negative cost but should
     * not have a cycle with negative cost.
     * @param theZero equals zero weight
     * @return shortest distances from s are returned in d
     * @return predecessor info in returned p */
   public void bellmanFord(int s, Operable [] d, int [] p,
                           Operable theZero)
   {
      verifyWeighted("bellmanFord");
   
      int n = vertices();
      if (s < 1 || s > n)
         throw new IllegalArgumentException
                   ("illegal source vertex" + s);
   
      // define two lists for vertices whose d has changed
      ArrayLinearList list1 = new ArrayLinearList();
      ArrayLinearList list2 = new ArrayLinearList();
      // define an array to record vertices that are in List2
      boolean [] inList2 = new boolean [n+1];
   
      // initialize p[1:n] = 0; inList2[1:n] = false by default
      for (int i = 0; i <= n; i++)
         p[i] = 0;
   
      // set d[s] = d^0(s) = 0
      d[s] = (Operable) theZero.zero();
      p[s] = s;  // p[i] != 0 means vertex i has been reached
                 // will later reset p[s] = 0
   
      // initialize list1
      list1.add(0, new Integer(s));
      
      // do n - 1 rounds of updating d
      for (int k = 1; k < n; k++)
      {
         if (list1.isEmpty())
            break;  // no more changes possible
         // process vertices on list1
         Iterator ilist1 = list1.iterator();
         while (ilist1.hasNext())
         {
            // get a vertex u whose d value has changed
            int u = ((Integer) ilist1.next()).intValue();
   
            // update d for the neighbors v of u
            Iterator iu = iterator(u);
            while (iu.hasNext())
            {
               WeightedEdgeNode vEdge = (WeightedEdgeNode) iu.next();
               if (p[vEdge.vertex] == 0 ||
                  ((Operable) d[u].add(vEdge.weight)).
                    compareTo(d[vEdge.vertex]) < 0)
               {
                  // this is either the first path to vEdge.vertex
                  // or is a shorter path than earlier ones
                  d[vEdge.vertex] = (Operable) d[u].add(vEdge.weight);
                  p[vEdge.vertex] = u;
                  // put vEdge.vertex into list2 unless it is already there
                  if (!inList2[vEdge.vertex])
                  {// put at end of list
                     list2.add(list2.size(), new Integer(vEdge.vertex));
                     inList2[vEdge.vertex] = true;
                  }
               }
            }
         }
   
         // set list1 and list2 for next update round
         list1 = list2;
         list2 = new ArrayLinearList();
   
         // reset inList2[1:n] to false
         ilist1 = list1.iterator();
         while (ilist1.hasNext())
            inList2[((Integer) ilist1.next()).intValue()] = false;
      }
      p[s] = 0;  // s has no predecessor
   }
}
