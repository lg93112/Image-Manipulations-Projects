/* Your code here! */

#include "maze.h"
#include <iostream>
#include <unordered_map>

using std::make_pair;
using std::unordered_map;

SquareMaze::SquareMaze () {}


void SquareMaze::makeMaze (int width, int height){
  // Initialization
  width_ = width;
  height_ = height;
  size_ = width * height;
  rightwalls_.assign(size_, true);
  downwalls_.assign(size_,true);
  mazes_.addelements(size_);
  // Select random walls to delete
  int right;
  for(int i=0; i<(size_/2); i++){
    int col = rand() % (width_-1);
    int row = rand() % (height_-1);
    int index[3] = {width_*row+col, width_*row+col+1, width_*(row+1)+col};
    right = rand() % 2;
    if(right){
      if(rightwalls_[index[0]]==true && mazes_.find(index[0]) != mazes_.find(index[1]))
      {
        rightwalls_[index[0]] = false;
        mazes_.setunion(index[0],index[1]);
      }
    }
    else{
      if(downwalls_[index[0]]==true && mazes_.find(index[0]) != mazes_.find(index[2]))
      {
        downwalls_[index[0]] = false;
        mazes_.setunion(index[0],index[2]);
      }
    }
  }
  // Check if walls can be deleted starting from the first maze
  right = rand() % 2;
  for(int row = 0; row < height_-1; row++){

    for(int col = 0; col < width_-1; col++){
      int index[3] = {width_*row+col, width_*row+col+1, width_*(row+1)+col};
      if(right){
        if(rightwalls_[index[0]]==true && mazes_.find(index[0]) != mazes_.find(index[1]))
        {
          rightwalls_[index[0]] = false;
          mazes_.setunion(index[0],index[1]);
        }
        if(downwalls_[index[0]]==true && mazes_.find(index[0]) != mazes_.find(index[2]))
        {
          downwalls_[index[0]] = false;
          mazes_.setunion(index[0],index[2]);
        }
        right = 0;
      }
      else{
        if(downwalls_[index[0]]==true && mazes_.find(index[0]) != mazes_.find(index[2]))
        {
          downwalls_[index[0]] = false;
          mazes_.setunion(index[0],index[2]);
        }
        if(rightwalls_[index[0]]==true && mazes_.find(index[0]) != mazes_.find(index[1]))
        {
          rightwalls_[index[0]] = false;
          mazes_.setunion(index[0],index[1]);
        }
        right = 1;
      }
    }
    // Check if down walls can be deleted for the rightmost mazes
    int rightmost = width_ * row + width_-1;
    int rightm_down = width_ * (row+1) + width_-1;
    if(downwalls_[rightmost]==true && mazes_.find(rightmost) != mazes_.find(rightm_down))
    {
      downwalls_[rightmost] = false;
      mazes_.setunion(rightmost,rightm_down);
    }

  }
  // Check if right walls can be deleted for the downmost mazes
  for(int col=0; col<width_-1; col++){
    int downmost = width_ * (height_-1) + col;
    int downm_right = width_ * (height_-1) + col + 1;
    if(rightwalls_[downmost]==true && mazes_.find(downmost) != mazes_.find(downm_right))
    {
      rightwalls_[downmost] = false;
      mazes_.setunion(downmost,downm_right);
    }
  }

}



bool SquareMaze::canTravel (int x, int y, int dir) const {
  if(x<0 || x>width_-1 || y<0 || y>height_-1){return false;}
  int index[3] = {width_*y+x, width_*y+x-1, width_*(y-1)+x};
  if(dir==0 && x<width_-1){return !rightwalls_[index[0]];}
  if(dir==1 && y<height_-1){return !downwalls_[index[0]];}
  if(dir==2 && x>0){return !rightwalls_[index[1]];}
  if(dir==3 && y>0){return !downwalls_[index[2]];}
  return false;
}


void SquareMaze::setWall (int x, int y, int dir, bool exists){
  if(x<0 || x>width_-1 || y<0 || y>height_-1){return;}
  int index = width_*y+x;
  if(dir==0 && x<width_-1){rightwalls_[index] = exists;}
  else if(dir==1 && y<height_-1){downwalls_[index] = exists;}
}


pair<int, int> SquareMaze::get_next_maze(int x, int y, int dir){
  pair<int, int> next(0,0);
  if(dir==0){next = make_pair(x+1, y);}
  if(dir==1){next = make_pair(x, y+1);}
  if(dir==2){next = make_pair(x-1, y);}
  if(dir==3){next = make_pair(x, y-1);}
  return next;
}


pair<int, int> SquareMaze::get_prev_maze(int x, int y, int dir){
  pair<int, int> next(0,0);
  if(dir==0){next = make_pair(x-1, y);}
  if(dir==1){next = make_pair(x, y-1);}
  if(dir==2){next = make_pair(x+1, y);}
  if(dir==3){next = make_pair(x, y+1);}
  return next;
}

vector<int> SquareMaze::solveMaze(){
  // Solutions map to store every maze coordinates as key and vector of {# of steps from start,
  // direction of this step} as value
  vector<vector<vector<int>>> solutions(width_, vector<vector<int>>(height_));
  // Using queue to do BFS
  queue<pair<int,int>> q;
  solutions[0][0] = {0};
  q.push(make_pair(0,0));
  // BFS traversal
  while(!q.empty()){
    pair<int, int> curr = q.front();
    q.pop();
    for(int dir=0; dir<4; dir++){
      if(canTravel(curr.first, curr.second, dir)){
        pair<int, int> next = get_next_maze(curr.first, curr.second, dir);
        if(solutions[next.first][next.second].size()==0){
          solutions[next.first][next.second].push_back(solutions[curr.first][curr.second][0]+1);
          solutions[next.first][next.second].push_back(dir);
          q.push(next);
        }
      }
    }
  }
  // Find longest path index
  int longest = solutions[0][height_-1][0];
  int idx = 0;
  for(int x=0; x<width_; x++){
    if(solutions[x][height_-1][0]>longest){
      longest = solutions[x][height_-1][0];
      idx = x;
    }
  }
  // Retrieve the vector of longest path reversely
  vector<int> path;
  pair<int, int> curr = make_pair(idx,height_-1);
  while(solutions[curr.first][curr.second].size()==2){
    path.insert(path.begin(), solutions[curr.first][curr.second][1]);
    curr = get_prev_maze(curr.first, curr.second, solutions[curr.first][curr.second][1]);
  }

  return path;
}


PNG* SquareMaze::drawMaze () const{
  PNG* maze = new PNG(width_*10+1, height_*10+1);
  // blacken the leftmost pixels
  for(int row=0; row<height_*10+1; row++){
    HSLAPixel* pixel= maze->getPixel(0,row);
    pixel->h = 0.0; pixel->s = 0.0; pixel->l = 0.0; pixel->a = 1.0;
  }
  // blackent he topmost pixels except for x=1-9
  HSLAPixel* origin = maze->getPixel(0,0);
  origin->h = 0.0; origin->s = 0.0; origin->l = 0.0; origin->a = 1.0;
  for(int col=10; col<width_*10+1; col++){
    HSLAPixel* pixel = maze->getPixel(col,0);
    pixel->h = 0.0; pixel->s = 0.0; pixel->l = 0.0; pixel->a = 1.0;
  }
  // traverse each square
  for(int row=0; row<height_; row++){
    for(int col=0; col<width_; col++){
      int index = width_*row+col;
      // if right wall exists
      if(rightwalls_[index]){
        for(int i=0; i<11; i++){
          HSLAPixel* pixel = maze->getPixel((col+1)*10, row*10+i);
          pixel->h = 0.0; pixel->s = 0.0; pixel->l = 0.0; pixel->a = 1.0;
        }
      }
      // if down wall exists
      if(downwalls_[index]){
        for(int i=0; i<11; i++){
          HSLAPixel* pixel = maze->getPixel(col*10+i, (row+1)*10);
          pixel->h = 0.0; pixel->s = 0.0; pixel->l = 0.0; pixel->a = 1.0;
        }
      }
    }
  }
  return maze;
}


PNG* SquareMaze::drawMazeWithSolution (){
  PNG* maze = drawMaze();
  vector<int> solution = solveMaze();
  // starting from (5,5), use solution vector to draw the path from origin
  // to destination
  int x = 5; int y = 5;
  for(auto &step : solution){
    if(step==0){
      for(int i=0; i<11; i++){
        HSLAPixel* pixel = maze->getPixel(x+i,y);
        pixel->h = 0.0; pixel->s = 1.0; pixel->l = 0.5; pixel->a = 1.0;
      }
      x += 10;
    }
    else if(step==1){
      for(int i=0; i<11; i++){
        HSLAPixel* pixel = maze->getPixel(x,y+i);
        pixel->h = 0.0; pixel->s = 1.0; pixel->l = 0.5; pixel->a = 1.0;
      }
      y += 10;
    }
    else if(step==2){
      for(int i=0; i<11; i++){
        HSLAPixel* pixel = maze->getPixel(x-i,y);
        pixel->h = 0.0; pixel->s = 1.0; pixel->l = 0.5; pixel->a = 1.0;
      }
      x -= 10;
    }
    else {
      for(int i=0; i<11; i++){
        HSLAPixel* pixel = maze->getPixel(x,y-i);
        pixel->h = 0.0; pixel->s = 1.0; pixel->l = 0.5; pixel->a = 1.0;
      }
      y -= 10;
    }
  }
  // make the exit
  int mazex = x/10;
  int mazey = height_ - 1;
  for(int i=1; i<10; i++){
    HSLAPixel* pixel = maze->getPixel(mazex*10+i,(mazey+1)*10);
    pixel->h = 0.0; pixel->s = 0.0; pixel->l = 1.0; pixel->a = 1.0;
  }
  return maze;
}
