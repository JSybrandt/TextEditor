// File: DisplayManager.h
// Author: Dorian P. Yeager
// Date: October 1, 2013
// Installation: Grove City College
// Contents:
//        Class definition for the DisplayManager class, which has the responsibility
//        of placing on the screen a representation of some portion of a document.

#ifndef __DISPLAYMANAGER_H
#define __DISPLAYMANAGER_H

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
using std::ostream;
#include <string>
using std::string;
#include <vector>
using std::vector; 
#include <fstream>
using std::ifstream;
#include "Document.h"

class DisplayManager: public vector<string> {
    // A display is a vector of strings called "rows". Each line of the document
    // may occupy one or more rows.
public:
    DisplayManager::DisplayManager(Document &doc, int rows=23, int cols=79): 
        dm(*this), doc(doc), rows(rows), cols(cols), ci(0), cj(0), contextRow(0) {
        return; // Constructor.
    }
    void fillDisplay(); // Initializes the vector of strings, attempting to place
      // the current document context on "contextRow". contextRow must be between
      // 0 and rows-1, inclusively.
    void configure(int rows, int columns); // Sets values for rows and cols.
    string getRow(int i) { // Return the i-th row of the display.
        if (i >= 0 && i < rows) return dm[i];
        else return "";
    }
    void getContextCoords(int &ci, int &cj); // Access function informs client
      // of precise location of document context on the screen.
    int getRows() { return rows; }
    int getColumns() { return cols; }
    void operator ++(); // Advance doc and (ci,cj) forward one character.
    void operator --(); // Move doc and (ci,cj) back one character.
    void setContextRow(int contextRow); // Sometimes called before fillDisplay()
      // to set a target row for the context.
private:
    void backUpOneRow();  // Back document up to beginning of previous row. 
    void advanceOneRow(); // Advance document to beginning of next row.
    Document &doc;  // The display manager keeps a reference to the document.
    int rows, cols; // Display is a rectangular array of chars with "rows"
                    // and "cols" columns.
    int ci, cj;     // Current document context is at row ci and column cj.
    int contextRow; // Desired context row which guides filling of display
                    // vector.
    DisplayManager &dm;
};

#endif
