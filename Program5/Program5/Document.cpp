// File: Document.cpp
// Author: Dorian P. Yeager
// Date: October 1, 2013
// Installation: Grove City College
// Contents:
//		Implementation code for class Document

#include "Document.h"
#include <fstream>
#include <string>
using std::string;
using std::getline;
using std::swap;
using std::ifstream;
using std::ofstream;

Document::Document(const char *fileName): fileName(fileName) {
	if (fileName != 0) load(fileName);
	else text = "\n";
	currentContext = 0;
}

void Document::clear() {
	text = "\n";
	currentContext = 0;
}

void Document::save(const char *fileName) {
    Document &d = *this;
    ofstream fout(fileName);
    Context oldContext = currentContext;
    d.goTo(begin());
    while (!d.atEnd()) {
        fout << *d;
        ++d;
    }
    fout << *d;
    fout.close();
    d.goTo(oldContext);
}

void Document::load(const char *fileName) {
	ifstream fin(fileName);
	if (fin.fail()) return;
	  // Ignore call if file is faulty.
	text = "";
	char ch;
	string line;
	fin.get(ch);
	bool first = true;
	while(fin) {
		if (ch == '\n') text += "\n";
		else {
			fin.putback(ch);
			getline(fin,line);
			if (!first) text += '\n';
			text += line;
		}
		fin.get(ch);
		first = false;
	}
	fin.close();
	text += "\n";
	currentContext = 0;
}

void Document::apply(Change &c) {
	c.apply(*this);
	Change *reverse = c.reverse();
	if (reverse != 0) history.push(reverse);
}

void Document::yank() {
    yankBuffer = getString(text.size());
}

void Document::insert(char ch) {
	text = text.insert(currentContext.offset,string("")+ch);
	currentContext.offset++;
}

void Document::insert(string s) {
	text.insert(currentContext.offset,s);
	for (int i=0; i<(int)s.size(); ++i) currentContext.offset++;
}

char Document::remove() {
	char rv = text[currentContext.offset];
	text = text.substr(0,currentContext.offset) + text.substr(currentContext.offset+1);
	if ((int)text.length() <= currentContext.offset) currentContext.offset--;
	return rv;
}

void Document::remove(int n) {
	for (int i=0; i<n; ++i) remove();
}

Context Document::getContext() {
	return currentContext;
}

void Document::undo() {
	if (!history.empty()) {
		Change * undoer = history.top();
		history.pop();
		undoer->apply(*this);
		delete undoer;
	}
}

char & Document::operator*() {
	return text[currentContext.offset];
}

void Document::operator++() {
	currentContext.offset++;
	if (text.length() == currentContext.offset)
		text = text + "\n";
}

void Document::operator +=(int n) {
	currentContext.offset += n;
	if ((int)text.length() <= currentContext.offset)
		currentContext.offset = text.length() - 1;
}

void Document::operator--() {
	currentContext.offset--;
	if (currentContext.offset < 0) currentContext.offset = 0;
}

void Document::operator -=(int n) {
	currentContext.offset -= n;
	if (currentContext.offset < 0) currentContext.offset = 0;
}

int Document::currentLineOffset() {
	int startOfThisLine = currentContext.offset;
	while (startOfThisLine != 0 && text[startOfThisLine-1] != '\n')
		--startOfThisLine;
	return currentContext.offset - startOfThisLine;
}

void Document::goTo(Context context) {
	currentContext = context;
	if (currentContext.offset < 0) currentContext.offset = 0;
	if (currentContext.offset >= (int)text.length()) 
		currentContext.offset = text.length()-1;
}

Context Document::begin() {
	return Context();
}

Context Document::end() {
	return Context(text.length()-1);
}

Context Document::lineBegin() {
	if (!atBeginning()) {
		Context oldContext = getContext();
		Context rv;
		Document &doc = *this;
		if (*doc == '\n') --doc;
		while (!doc.atBeginning() && *doc != '\n') --doc;
		if (*doc == '\n') ++doc;
		rv = getContext();
		goTo(oldContext);
		return rv;
	}
	else return getContext();
}


Context Document::lineEnd() {
	Context oldContext = getContext();
	Context rv;
	Document &doc = *this;
	while (!doc.atEnd() && *doc != '\n') ++doc;
	rv = getContext();
	goTo(oldContext);
	return rv;
}

string Document::getString(int max) {
	int remaining = end() - currentContext;
	if (remaining < max) max = remaining;
	string maxString = text.substr(currentContext.offset,max);
	int lfPos = maxString.find('\n');
	if (lfPos >= 0) 
		maxString = maxString.substr(0,lfPos+1);
	return maxString;
}

Context Document::find(string pattern) {
    ++*this;
    int place = text.find(pattern.c_str(), currentContext.offset);
    --*this;
    return Context(place);
}

void Document::placeYank() {
    goTo(lineBegin());
    insert(yankBuffer);
    if (**this == '\n') goTo(lineBegin());
    else {
        --*this;
        goTo(lineBegin());
    }
}
