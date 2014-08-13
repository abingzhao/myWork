
template<class T>
void SparseMatrix<T>::Append(const Term<T>& t)
{// Append a nonzero term t to *this.
   if (terms >= MaxTerms) throw NoMem();
   a[terms] = t;
   terms++;
}

template<class T>
void SparseMatrix<T>::Add(const SparseMatrix<T> &b,
                            SparseMatrix<T> &c) const
{// Compute c = (*this) + b.

   // verify compatibility
   if (rows != b.rows || cols != b.cols)
     throw SizeMismatch(); // incompatible matrices

   // set characteristics of result c
   c.rows = rows;
   c.cols = cols;
   c.terms = 0; // initial value

   // define cursors to move through *this and b
   int ct = 0, cb = 0;

   // move through *this and b adding like terms
   while (ct < terms && cb < b.terms) {

     // Row-major index plus cols of each term
     int indt = a[ct].row * cols + a[ct].col;
     int indb = b.a[cb].row * cols + b.a[cb].col;

     if (indt < indb) {// b term comes later
   	 c.Append(a[ct]);
         ct++;} // next term of *this
     else {if (indt == indb) {// both in same position

              // append to c only if sum not zero
              if (a[ct].value + b.a[cb].value) {
                 Term<T> t;
                 t.row = a[ct].row;
                 t.col = a[ct].col;
                 t.value = a[ct].value + b.a[cb].value;
                 c.Append(t);}

              ct++; cb++;}  // next terms of *this and b
           else {c.Append(b.a[cb]);
                 cb++;} // next term of b
          }
     }

   // copy over remaining terms
   for (; ct < terms; ct++)
      c.Append(a[ct]);
   for (; cb < b.terms; cb++)
      c.Append(b.a[cb]);
}

#endif
