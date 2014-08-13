void Hanoi::TowersOfHanoi(int n, int x, int y, int z)
{// Move the top n disks from tower x to tower y.
 // Use tower z for intermediate storage.
   int d;  // disk number
   if (n > 0) {
      TowersOfHanoi(n-1, x, z, y);
      S[x]->Delete(d);  // remove a disk from x
      S[y]->Add(d);  // put this disk on tower y
   // ShowState();
   // substitute ShowState code for test run
      cout << "Move disk " << d << " from tower "
           << x << " to tower " << y << endl;
      TowersOfHanoi(n-1, z, y, x);}
}

