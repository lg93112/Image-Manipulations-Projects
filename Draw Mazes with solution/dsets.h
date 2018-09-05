/* Your code here! */
#ifndef DSETS_H
#define DSETS_H

#include <string>
#include <vector>

class DisjointSets{
  private:
    std::vector<int> v_;
  public:
    void addelements (int num);
    int find (int elem);
    void setunion (int a, int b);
    int size (int elem);
};

#endif
