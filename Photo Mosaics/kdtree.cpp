/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */


template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if(curDim<Dim && curDim>=0){
      if(first[curDim]!=second[curDim]){return first[curDim]<second[curDim];}
      return first<second;
    }
    return false;
}

template <int Dim>
double KDTree<Dim>::distance(const Point<Dim> &p1, const Point<Dim> &p2) const
{
  double distance = 0;
  for(int i=0;i<Dim;i++){
    distance+=(p1[i]-p2[i])*(p1[i]-p2[i]);
  }
  return distance;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     double sumsq_c = distance(target,currentBest);
     double sumsq_p = distance(target,potential);
     if(sumsq_c==sumsq_p){return potential<currentBest;}
     else if(sumsq_c>sumsq_p){return true;}
     return false;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    points = newPoints;
    construct(0,points.size()-1,0);
}


template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */

    return findNN(0, points.size()-1, 0, query, points[(points.size()-1)/2]);

}


template <int Dim>
int KDTree<Dim>::partition(int left, int right, int dim){
  int mid = (left+right)/2;
  Point<Dim> midValue = points[mid];
  std::swap(points[right],points[mid]);
  int storeIndex = left;
  for(int i=left;i<=right-1;i++){
    if(smallerDimVal(points[i],midValue,dim)){
      std::swap(points[i],points[storeIndex]);
      storeIndex++;
    }
  }
  std::swap(points[storeIndex],points[right]);
  return storeIndex;
}

template <int Dim>
void KDTree<Dim>::select(int left, int right, int dim, int index){
  if(left>=right){return;}
  int pivotIndex = partition(left,right,dim);
  if(index == pivotIndex){return;}
  else if(index<pivotIndex){select(left,pivotIndex-1,dim,index);}
  else{select(pivotIndex+1,right,dim,index);}
}

template <int Dim>
void KDTree<Dim>::construct(int left, int right, int dim){
  if(left==right){return;}
  int mid = (left+right)/2;
  select(left,right,dim,mid);
  if(mid-1>left){construct(left,mid-1,(dim+1)%Dim);}
  if(mid+1<right){construct(mid+1,right,(dim+1)%Dim);}
}


template <int Dim>
Point<Dim> KDTree<Dim>::findNN(int left, int right, int d, const Point<Dim> &query, const Point<Dim> &best) const{
  Point<Dim> currBest = best;
  if(left==right){
    if(shouldReplace(query,best,points[left])){
      currBest = points[left];
      return currBest;
    }
    currBest = best;
    return currBest;
  }
  int L = 1;
  int subRoot = (left+right)/2;
  if(smallerDimVal(query,points[subRoot],d) && left<subRoot){
    currBest = findNN(left,subRoot-1,(d+1)%Dim,query,currBest);
    L = 1;
  }
  if(smallerDimVal(points[subRoot],query,d) && subRoot<right) {
    currBest = findNN(subRoot+1,right,(d+1)%Dim,query,currBest);
    L = 0;
  }

  if(shouldReplace(query,currBest,points[subRoot])){currBest = points[subRoot];}
  if((query[d]-points[subRoot][d])*(query[d]-points[subRoot][d])<=distance(query,currBest)){
    if(L==1 && subRoot<right){
      currBest = findNN(subRoot+1,right,(d+1)%Dim,query,currBest);
    }
    if(L==0 && left<subRoot){
      currBest = findNN(left,subRoot-1,(d+1)%Dim,query,currBest);
    }
  }
  return currBest;
}
