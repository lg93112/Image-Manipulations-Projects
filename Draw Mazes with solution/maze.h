/* Your code here! */

#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <queue>
#include "cs225/PNG.h"
#include "dsets.h"

using namespace std;
using namespace cs225;
using std::pair;

class SquareMaze{

  public:
    SquareMaze ();
    void makeMaze (int width, int height);
    bool canTravel (int x, int y, int dir) const;
    void setWall (int x, int y, int dir, bool exists);
    vector<int> solveMaze ();
    PNG* drawMaze () const;
    PNG* drawMazeWithSolution ();


  private:
    int width_;
    int height_;
    int size_;
    vector<bool> rightwalls_;
    vector<bool> downwalls_;
    DisjointSets mazes_;
    pair<int, int> get_next_maze(int x, int y, int dir);
    pair<int, int> get_prev_maze(int x, int y, int dir);

};

#endif
