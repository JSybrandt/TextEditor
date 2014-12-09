// File: Document.h
// Author: Dorian P. Yeager
// Date: October 1, 2013
// Installation: Grove City College
// Contents:
//		Definition of class Document, a representation of a text file
//		in memory. A document may be sent "apply" messages that change its
//		contents. Each apply message receives a pointer to a Change object
//		that encapsulates sufficient information to implement the change
//		requested. Some changes are reversible, and a stack of pointers to
//		the reverses of past changes is kept in the stack "history".
//		A doocument always maintains a Context object called currentContext,
//		encapsulating sufficient information to determine the current position
//		in the file where any relevant change (such as an insertion or deletion
//		of text) will be applied.

#ifndef __DOCUMENT_H
#define __DOCUMENT_H

#include <string>
#include <stack>
using std::string;
using std::stack;
#include "Change.h"
#include "Context.h"

class Document {
	Context currentContext, savedContext;
	string text;
	const char *fileName;
	stack<Change*> history;
    string yankBuffer;
public:
	Document(const char *fileName=0);
	void clear();
	void load(const char *fileName);
	void save(const char *fileName);
    int size() { return text.size(); }
	void apply(Change &c);
    void yank();
    void placeYank();
	void insert(char ch);
						 // Inserts ch before the current character.
	void insert(string s);
						 // Inserts string s before the current character.
	char remove();       // Removes the current character.
	void remove(int n);  // Removes n characters.
	int currentLineOffset();
		                 // Returns the offset of the current context within
	                     // the current line.
	void undo();
	char &operator *();  // Returns a reference to the current character.
	void operator ++();  // Moves forward one character.
	void operator --();  // Moves back one character.
	bool atEnd() { return currentContext == end(); }
	bool atBeginning() { return currentContext == begin(); }
	void goTo(Context context);
	Context begin();	  // Returns the context of the beginning of
		                  // the file.
	Context end();	      // Returns the context of the end of the file.
	Context lineBegin();  // Returns the context of the beginning of
		                  // the current line.
	Context lineEnd();	  // Returns the context of the end of the
		                  // current line.
	Context getContext(); // Returns the current context.
    Context find(string pattern); // Returns the context at which the
                          // pattern can be found. Begins its search at
                          // the current context. Returns offset -1 if not
                          // found.
	void operator -=(int n); // Moves back n characters or to beginning 
						 // of file.
	void operator +=(int n); // Moves forward n characters or to end 
						 // of file.
	string getString(int max); // Gets a substring of doc at most max
	                     // chars long, stopping at \n, including \n.
};

#endif
