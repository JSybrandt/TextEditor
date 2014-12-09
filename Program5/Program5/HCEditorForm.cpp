// File: HCEditorForm.cpp
// Date: 12/2/2014
// Author: Dorian P. Yeager
// Installation: Grove City College
// Class: Comp 322, Object-Oriented and Advanced Programming
// Contents: Member function definitions for HCEditorForm, a class which provides 
//   initialization and event handlers for a C++/CLR generated class. The purpose
//   of the project is to implement a graphics interface to the text editor project
//   from Comp 220.


#include "HCEditorForm.h"
#include "DisplayManager.h"
#include "MyForm.h"

namespace Program5 {

    HCEditorForm::HCEditorForm(MyForm^ form): d(*new Document), form(form) {
        d.load("kjv.txt");
        dispMan = new DisplayManager(d);
        loaded = false;
        fontName = gcnew String("Courier New");
        blackBrush = gcnew SolidBrush(Color::Black);
        blackPen = gcnew Pen(Color::Black);
        backPen = gcnew Pen(form->BackColor);
        form->Font = gcnew Font(fontName,12);
        dx = pixelsPerCharX;
        dy = pixelsPerCharY;
    }

    HCEditorForm::~HCEditorForm() {
        delete &d;
    }

    void HCEditorForm::onLoad(Object^  sender, EventArgs^  e) {
        loaded = true;
        cursorColor = Color::Black;
    }

    void HCEditorForm::onPaint(Object^  sender, PaintEventArgs^  e) {
        if (loaded) {
            reconfigureAndFill();
            Graphics ^g = e->Graphics;
            int rows = dispMan->getRows();
            int x = LEFT, y = TOP;
            for (int i=0; i<rows; ++i) {
                string source = dispMan->at(i);
                String^ s = gcnew String(source.c_str());
                g->DrawString(s,form->Font,blackBrush,Point(x,y));
                y += pixelsPerCharY;
            }
        }
    }
     
    void HCEditorForm::onSizeChanged(Object^  sender, EventArgs^  e) {
        if (loaded) {
            reconfigureAndFill();
            form->Refresh();
        }
    }

    void HCEditorForm::reconfigureAndFill() {
        Rectangle rect = form->ClientRectangle;
        int width = rect.Width;
        int height = rect.Height;
        int cols = (width - 2*TCLEFT) / pixelsPerCharX;
        int rows = (height - TOP)/ pixelsPerCharY;
        dispMan->configure(rows,cols);
        dispMan->fillDisplay();
    }
      
    void HCEditorForm::onCursorTimerTick() {
        int ci, cj;
        dispMan->getContextCoords(ci,cj);
        float y = TOP + dy*ci;
        float x = LEFT + dx*cj;
        Graphics^ g = form->CreateGraphics();
        Pen^ pen = gcnew Pen(cursorColor);
        g->DrawLine(pen,x,y,x,y+dy);
        if (cursorColor == Color::Black) cursorColor = form->BackColor;
        else cursorColor = Color::Black;
    }
        
};