// File: Context.h
// Author: Dorian P. Yeager
// Date: October 1, 2013
// Installation: Grove City College
// Contents:
//		Class definition for class Context, which encapsulates sufficient information
//		to determine a location in a document. The implementation of this class
//		depends on the representation used for the Document class.

#ifndef __CONTEXT_H
#define __CONTEXT_H

class Context {
public:
	friend class Document;
	Context(int offset=0): offset(offset) {}
	int operator - (const Context &context) {
		return offset - context.offset;
	}
	int operator + (const Context &context) {
		return offset + context.offset;
	}
	bool operator == (const Context &context) {
		return offset == context.offset;
	}
	bool operator < (const Context &context) {
		return offset < context.offset;
	}
	bool operator > (const Context &context) {
		return offset > context.offset;
	}
	bool operator <= (const Context &context) {
		return offset <= context.offset;
	}
	bool operator >= (const Context &context) {
		return offset >= context.offset;
	}
	bool operator != (const Context &context) {
		return offset != context.offset;
	}
private:
	int offset;
};

#endif
