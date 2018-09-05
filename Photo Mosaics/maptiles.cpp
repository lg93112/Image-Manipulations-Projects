/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> & theTiles)
{
    /**
     * @todo Implement this function!
     */

    map<HSLAPixel, int> PixelsToTiles;
    for(size_t i=0;i<theTiles.size();i++){
      pair<HSLAPixel, int> p(theTiles[i].getAverageColor(), i);
      PixelsToTiles.insert(p);
    }

    vector<Point<3>> tilesPoints;

    map<Point<3>, HSLAPixel> PointsToPixels;
    for(map<HSLAPixel, int>::iterator it=PixelsToTiles.begin();it!=PixelsToTiles.end();++it){
      double hue = ((it->first).h)/360.0;
      Point<3> pt(hue,(it->first).s, (it->first).l);
      pair<Point<3>, HSLAPixel> p(pt, it->first);
      PointsToPixels.insert(p);
      tilesPoints.push_back(pt);
    }

    KDTree<3> tilesKDTree(tilesPoints);

    MosaicCanvas* canvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());

    for(int i=0;i<theSource.getRows();i++){
      for(int j=0;j<theSource.getColumns();j++){
        HSLAPixel source_Pixel = theSource.getRegionColor(i,j);
        double s_h = (source_Pixel.h)/360.0;
        Point<3> source(s_h, source_Pixel.s, source_Pixel.l);
        Point<3> nearest = tilesKDTree.findNearestNeighbor(source);
        canvas->setTile(i, j, theTiles[PixelsToTiles[PointsToPixels[nearest]]]);
      }
    }

    return canvas;
}
