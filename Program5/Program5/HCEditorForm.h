// File: HCEditorForm.h
// Date: 12/2/2014
// Author: Dorian P. Yeager
// Installation: Grove City College
// Class: Comp 322, Object-Oriented and Advanced Programming
// Contents: Class definition for HCEditorForm, a class which provides initialization
//   and event handlers for a C++/CLR generated class. The purpose of the project is
//   to implement a graphics interface to the text editor project from Comp 220.

#pragma once

#include "Document.h"
#include "Change.h"
#include "DisplayManager.h"

namespace Program5 {

    using namespace System;
    using namespace System::Drawing;
    using System::Threading::Timer;
    using namespace System::Windows::Forms;
    
    ref class MyForm;
    typedef MyForm GeneratedForm;

    ref class HCEditorForm {
    public:
        HCEditorForm(MyForm^);
        ~HCEditorForm();
        void reconfigureAndFill();
        //void positionDocumentAt(int row, int col);
        void onCursorTimerTick();
        void onLoad(Object^  sender, EventArgs^  e);
        void onPaint(Object^  sender, PaintEventArgs^  e);
        void onSizeChanged(Object^  sender, EventArgs^  e);
        //void onKeyPress(Object^  sender, KeyPressEventArgs^  e);
        //void onKeyDown(Object^  sender, KeyEventArgs^  e);
        //void onMouseDown(Object^  sender, MouseEventArgs^  e);
        //void onFind(Object^  sender, System::EventArgs^  e);
        //void onReplace(Object^  sender, EventArgs^  e);
        //void onFileNew(Object^  sender, EventArgs^  e);
        //void onFileOpen(Object^  sender, EventArgs^  e);
        //void onSaveAs(Object^ sender, EventArgs^ e);
    private:
        bool loaded;
        Document &d;
        DisplayManager *dispMan;
        String^ fontName;
        Pen^ blackPen, ^backPen;
        Brush^ blackBrush;
        float dx, dy;
        Color cursorColor;
        Point textCursorPosition;
        static const float pixelsPerCharX = 9.9f;
        static const float pixelsPerCharY = 20.0f;
        static const float fontSize = 12.0f;
        static const int LEFT = 2, TCLEFT = LEFT+2, TOP = 10;
        GeneratedForm^ form;
    };
}

