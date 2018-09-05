/**
 * @file mosaiccanvas.h
 */

#include <iostream>
#include <sys/stat.h>
#include <errno.h>
#include <cstdlib>
#include <unordered_map>

#include "mosaiccanvas.h"
#include "util/util.h"

using namespace std;
using namespace util;

bool MosaicCanvas::enableOutput = false;

/**
 * Constructor.
 *
 * @param theRows Number of rows to divide the canvas into
 * @param theColumns Number of columns to divide the canvas into
 */
MosaicCanvas::MosaicCanvas(int theRows, int theColumns)
    : rows(theRows), columns(theColumns)
{
    if ((theRows < 1) || (theColumns < 1)) {
        cerr << "Error: Cannot set non-positive rows or columns" << endl;
        exit(-1);
    }

    myImages.resize(rows * columns);
}

/**
 * Retrieve the number of rows of images
 *
 * @return The number or rows in the mosaic, or -1 on error
 */
int MosaicCanvas::getRows() const
{
    return rows;
}

/**
 * Retrieve the number of columns of images
 *
 * @return The number of columns in the mosaic, or -1 or error
 */
int MosaicCanvas::getColumns() const
{
    return columns;
}

void MosaicCanvas::setTile(int row, int column, TileImage &i)
{
    if (enableOutput) {
        cerr << "\rPopulating Mosaic: setting tile ("
             << row << ", " << column
             << ")" << string(20, ' ') << "\r";
        cerr.flush();
    }
    myImages[row * columns + column] = &i;
}

const TileImage* MosaicCanvas::getTile(int row, int column) const
{
    return myImages[row * columns + column];
}

PNG MosaicCanvas::drawMosaic(int pixelsPerTile) const
{
    if (pixelsPerTile <= 0) {
        cerr << "ERROR: pixelsPerTile must be > 0" << endl;
        exit(-1);
    }

    int width = columns * pixelsPerTile;
    int height = rows * pixelsPerTile;

    // Create the image
    PNG mosaic(width, height);

    // Create list of drawable tiles

    map<TileImage*,vector<pair<size_t,size_t>>> tilesmap;

    for(int row=0;row<rows;row++){
      for(int col=0;col<columns;col++){
        tilesmap[myImages[row * columns + col]].push_back(pair<size_t,size_t> (row,col));
      }
    }

    map<TileImage*,vector<pair<size_t,size_t>>>::iterator it;

    for(it=tilesmap.begin();it!=tilesmap.end();it++){
      vector<pair<size_t,size_t>> &v = it->second;
      for(unsigned i=0; i<v.size(); i++){
        size_t row = v[i].first;
        size_t col = v[i].second;
        int startX = divide(width  * col,       getColumns());
        int endX   = divide(width  * (col + 1), getColumns());
        int startY = divide(height * row,       getRows());
        int endY   = divide(height * (row + 1), getRows());

        if (endX - startX != endY - startY)
            cerr << "Error: resolution not constant: x: " << (endX - startX)
                 << " y: " << (endY - startY) << endl;

        (it->first)->paste(mosaic, startX, startY, endX - startX);
      }
    }

    return mosaic;
}
