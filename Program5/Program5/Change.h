// File: Change.h
// Author: Dorian P. Yeager
// Date: October 1, 2013
// Installation: Grove City College
// Contents:
//		Definition of class Change. An object of this type is a representation
//		of a change to be applied to a Document object.

#ifndef __CHANGE_H
#define __CHANGE_H

#include "context.h"
#include "DisplayManager.h"

class Document;
class DisplayManager;

class Change {
public:
	virtual Change * reverse() {return 0;}
	virtual void apply(Document&) {};
	virtual bool isExit() { return true; };
};

typedef Change Exit;

class NontrivialChange: public Change {
	virtual bool isExit() { return false; }
};

class Insertion: public NontrivialChange {
public:
	Insertion(Context context, char ch, DisplayManager *dispMan): 
	  context(context), ch(ch), dispMan(dispMan) {}
	virtual Change * reverse();
	virtual void apply(Document &d);
private:
	Context context; 
	char ch;
	DisplayManager *dispMan;
};

class DeleteUndoer: public Insertion {
public:
	DeleteUndoer(Context context, char ch, DisplayManager *dispMan): 
	  Insertion(context, ch, dispMan) {}
	virtual void apply(Document &d);
};

class Deletion: public NontrivialChange {
public:
	Deletion(Context context, char ch, DisplayManager *dispMan): 
      context(context), ch(ch), dispMan(dispMan) {}
	virtual Change * reverse();
	virtual void apply(Document &d);
protected:
	Context context; 
	char ch;
	DisplayManager *dispMan;
};

class InsertionUndoer: public Deletion {
public:
	InsertionUndoer(Context context, char ch, DisplayManager *dispMan): 
      Deletion(context, ch, dispMan) {}
	virtual void apply(Document &d);
};

class BackSpace: public NontrivialChange {
public:
	BackSpace(Context context, DisplayManager *dispMan): 
      context(context), dispMan(dispMan) {}
	virtual Change * reverse();
	virtual void apply(Document &d);
private:
	Context context; 
	char ch;
	DisplayManager *dispMan;
};

class Undo: public NontrivialChange {
public:
	virtual void apply(Document &d);
};

class MoveLeft: public NontrivialChange {
public:
    MoveLeft(DisplayManager *dispMan): dispMan(dispMan) {}
	virtual void apply(Document &d);
private:
    DisplayManager *dispMan;
};

class MoveRight: public NontrivialChange {
public:
    MoveRight(DisplayManager *dispMan): dispMan(dispMan) {}
	virtual void apply(Document &d);
private:
	DisplayManager *dispMan;
};

class MoveDown: public NontrivialChange {
public:
	MoveDown(DisplayManager *dispMan): dispMan(dispMan) {}
	virtual void apply(Document &d);
private:
	DisplayManager *dispMan;
};

class MoveUp: public NontrivialChange {
public:
	MoveUp(DisplayManager *dispMan): dispMan(dispMan) {}
	virtual void apply(Document &d);
private:
	DisplayManager *dispMan;
};

class EndOfLine: public NontrivialChange {
public:
	EndOfLine(DisplayManager *dispMan): dispMan(dispMan) {}
	virtual void apply(Document &d);
private:
	DisplayManager *dispMan;
};

class StartOfLine: public NontrivialChange {
public:
	StartOfLine(DisplayManager *dispMan): dispMan(dispMan) {}
	virtual void apply(Document &d);
private:
	DisplayManager *dispMan;
};

class EndOfDocument: public NontrivialChange {
public:
    EndOfDocument() {}
    virtual void apply(Document &d);
};

class StartOfDocument: public NontrivialChange {
public:
    StartOfDocument() {}
    virtual void apply(Document &d);
};

class PositionToLine: public NontrivialChange {
public:
	PositionToLine(int lineNo): lineNo(lineNo) {}
	virtual void apply(Document &d);
private:
	int lineNo;
};

class PageForward: public NontrivialChange {
public:
    PageForward(DisplayManager *dispMan): dispMan(dispMan) {}
    virtual void apply(Document &d);
private:
    DisplayManager *dispMan;
};

class PageBackward: public NontrivialChange {
public:
    PageBackward(DisplayManager *dispMan): dispMan(dispMan) {}
    virtual void apply(Document &d);
private:
    DisplayManager *dispMan;
};

class NextWord: public NontrivialChange {
public:
    virtual void apply(Document &d);
};

class SaveChange: public NontrivialChange {
public:
    SaveChange(string filename): filename(filename) {}
    virtual void apply(Document &d);
private:
    string filename;
};

class LoadChange: public NontrivialChange {
public:
    LoadChange(string filename): filename(filename) {}
    virtual void apply(Document &d);
private:
    string filename;
};

class FindChange: public NontrivialChange {
public:
    FindChange(string pattern, DisplayManager *dispMan): 
      pattern(pattern), dispMan(dispMan) {
    }
    virtual void apply(Document &d);
private:
    DisplayManager *dispMan;
    string pattern;
};

class ReplaceChange: public NontrivialChange {
public:
    ReplaceChange(string pattern, string replacement, 
            Context context, DisplayManager *dispMan):
        pattern(pattern), replacement(replacement), context(context), dispMan(dispMan) {
    }
    virtual void apply(Document &d);
    virtual Change * reverse();
private:
    DisplayManager *dispMan;
    string pattern, replacement;
    Context context, oldContext;
};

class YankChange: public NontrivialChange {
public:
    virtual void apply(Document &d);
};

class PlaceYank: public NontrivialChange {
public:
    virtual void apply(Document &d);
    virtual Change * reverse();
};

class DeleteLine: public NontrivialChange {
public:
    virtual void apply(Document &d);
};

class YellChange: public NontrivialChange {
public:
	YellChange(Context c): context(c) {}
	virtual void apply(Document &d);
	virtual Change * reverse();
private:
	Context context;
};

class DeleteChars: public NontrivialChange {
public:
	DeleteChars(Context c, int n): context(c), n(n) {}
	virtual void apply(Document &d);
private:
	Context context;
	int n;
};

#endif
