/* Your code here! */
#include "dsets.h"
#include <vector>

using namespace std;

void DisjointSets::addelements (int num){
  vector<int> newvec(num, -1);
  v_.insert(v_.end(),newvec.begin(),newvec.end());
}

int DisjointSets::find (int elem){
  if(v_[elem]<0){return elem;}
  else {return v_[elem] = find(v_[elem]);}
}

void DisjointSets::setunion (int a, int b){
  int tree1 = find(a);
  int tree2 = find(b);
  if(tree1==tree2){return;}
  int newsize = v_[tree1]+v_[tree2];
  if(v_[tree1]>v_[tree2]){
    v_[tree1] = tree2;
    v_[tree2] = newsize;
  }
  else{
    v_[tree2] = tree1;
    v_[tree1] = newsize;
  }
}

int DisjointSets::size (int elem){
  int root = find(elem);
  return -v_[root];
}
