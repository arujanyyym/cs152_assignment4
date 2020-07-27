
#include "set.h"


void print( std::ostream& out, const treenode* n, size_t indent )
{

   for( size_t i = 0; i != indent; ++ i )
      out << "|  ";
   if(n)
   {
      out << ( n -> val ) << "\n";
      print( out, n -> left, indent + 1 );
      print( out, n -> right, indent + 1 );
   }
   else
      out << "#\n";
}


// both the upperbound and the lowerbound are strict,
// we use pointers, so that they can be absent.

void checkbetween( const treenode* n,
                   const int* lowerbound, const int* upperbound )
{
   while(n)
   {
      if( lowerbound && *lowerbound >= n -> val )
      {
         std::cout << "value " << ( n -> val );
         std::cout << " is not above lower bound " << *lowerbound << "\n";
         std::abort( );
      }

      if( upperbound && n -> val >= *upperbound )
      {
         std::cout << "value " << ( n -> val );
         std::cout << "is not below upperbound " << *upperbound << "\n";
         std::abort( );
      }

      checkbetween( n -> left, lowerbound, &( n -> val ));
      lowerbound = & ( n -> val );
      n = n -> right;
   }
}


void deallocate( treenode* n )
{
   while(n)
   {
      deallocate( n -> left );
      treenode* bye = n;
      n = n -> right;
      delete bye;
   }
}


void writecopy( treenode** to, treenode* from )
{
   while( from )
   {
      *to = new treenode{ from -> val };

      writecopy( & (*to) -> left, from -> left );
      to = & (*to) -> right;
      from = from -> right;
   }
   *to = nullptr;
}


void set::checksorted( ) const
{
   ::checkbetween( tr, nullptr, nullptr );
}


std::ostream& set::print( size_t indent, std::ostream& out ) const
{
   ::print( out, tr, indent );
   return out;
}


const treenode* find( const treenode* n, int i ) {
    if(!n) {
        return nullptr;
    }
    if(n -> val != i){
      if( n -> val > i){
        const treenode* ptr = find(n -> left, i);
                return ptr;
        } else {
          const treenode* ptr = find(n -> right, i);
          return ptr;
        }

      }else {
        return n;
      }

}

treenode** find( treenode** n, int i ){
  if((*n) -> val != i){

      if( (*n) -> val > i){
          if(!(*n) -> left){
              return n;
          }
          treenode** ptr = find( &(*n) -> left, i);
          return ptr;
      } else {
          if(!(*n) -> right){
              return n;
          }
          treenode** ptr = find( &(*n) -> right, i);
          return ptr;
      }
  }else {
      return n;
  }
}

bool set::insert( int i ){

  if(tr == nullptr){
    treenode* newvalue= new treenode(i);
    tr = newvalue;
    return true;
  }else{
    treenode** a = ::find(&tr, i);

    if((*a)->val == i){
        return false;
    }else{
      treenode* newvalue= new treenode(i);
      if((*a)->val < i){
          (*a)-> right = newvalue;
      } else{
          (*a)-> left = newvalue;
      }
    }
    return true;
  }
}



bool set::contains( int i ) const{
    return ((bool)find (tr, i));

}


bool set::remove( int i ){
    treenode** deletenode = ::find(&tr, i);

    if((*deletenode) -> val != i){
        return false;
    }
    treenode* a = *deletenode;
    if(!(a -> right) && !(a -> left)){
        *(deletenode) = nullptr;
    } else if(!(a -> right)){
        *(deletenode) = a -> left;

    }else if(!(a -> left)){
        *(deletenode) = a -> right;
    } else{

        *(deletenode) = ::removerightmost(&(*deletenode) -> left);
        (*deletenode)-> left = a -> left;
        (*deletenode)-> right = a -> right;
    }

    delete a;

    return true;
}


treenode* removerightmost( treenode** from ){
    while((*from) -> right){
      from = &((*from) -> right);

    }

        treenode* removenode = *from;
        if((*from) -> left){
            *from = (*from) -> left;
        } else{
            *from = nullptr;
        }

    return removenode;

}
size_t size( const treenode* n ){
  if (!n){
    return 0;
  }
  return 1 + size(n -> left) + size(n -> right);


}
   // Returns the total size of tree.

size_t height( const treenode* n ) {
  if (!n){
    return 0;
  } else if (n -> left == nullptr && n -> right == nullptr) {
    return 1;
  } else {
    size_t left = height (n -> left);
    size_t right = height (n -> right);

    if (left > right){
      return 1 + left;
    } else {
      return 1 + right;
    }
  }
}
   // Returns the height of the tree starting at n.

size_t log_base2( size_t s ) {
  size_t i = 0;
  while ((s / 2) >= 1){
    s = s / 2;
    ++i;
  }

  return i;
}
