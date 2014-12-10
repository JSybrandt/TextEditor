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
#include "findForm.h"

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
            int x = LEFT, y = TOP+20;
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
        int height = rect.Height-20;
        int cols = (width - 2*TCLEFT) / pixelsPerCharX;
        int rows = (height - TOP)/ pixelsPerCharY;
        dispMan->configure(rows,cols);
        dispMan->fillDisplay();
    }
      
    void HCEditorForm::onCursorTimerTick() {
        int ci, cj;
        dispMan->getContextCoords(ci,cj);
        float y = TOP + dy*ci+20;
        float x = LEFT + dx*cj;
        Graphics^ g = form->CreateGraphics();
        Pen^ pen = gcnew Pen(cursorColor);
        g->DrawLine(pen,x,y,x,y+dy);
        if (cursorColor == Color::Black) cursorColor = form->BackColor;
        else cursorColor = Color::Black;
    }
        
	void HCEditorForm::onMouseDown(Object^  sender, MouseEventArgs^  e)
	{
		
	}


	void HCEditorForm::onKeyPress(Object^  sender, KeyPressEventArgs^  e)
	{
	}
    void HCEditorForm::onKeyDown(Object^  sender, KeyEventArgs^  e)
	{
		Change *ch = nullptr;
		switch (e->KeyCode)
		{
		case Keys::Right: ch = new MoveRight(dispMan); break;
		case Keys::Left: ch = new MoveLeft(dispMan); break;
		case Keys::Up: ch = new MoveUp(dispMan); break;
		case Keys::Down: ch = new MoveDown(dispMan); break;
		case Keys::End: if(e->Control) ch = new EndOfDocument();
						else ch = new EndOfLine(dispMan);
						break;
		case Keys::Delete: ch = new Deletion(d.getContext(),' ',dispMan); break;
		case Keys::Back: ch = new BackSpace(d.getContext(),dispMan); break;
		case Keys::PageDown: ch = new PageForward(dispMan); break;
		case Keys::PageUp: ch = new PageBackward(dispMan); break;
		case Keys::Home: if(e->Control) ch = new StartOfDocument();
						 else ch = new StartOfLine(dispMan); 
						 break;
		case Keys::Return: ch =  new Insertion(d.getContext(),'\n',dispMan);break;
		default:
			if(e->KeyValue == 'Z' && e->Control) ch = new Undo();
			else if(e->KeyValue == 'W' && e->Control) ch = new NextWord();
			else if(isPrintable(e->KeyValue))
			{
				if(e->Shift)
					ch = new Insertion(d.getContext(),e->KeyValue,dispMan);		
				else
					ch = new Insertion(d.getContext(),tolower(e->KeyValue),dispMan);	
			}
			break;
		}
		if(ch!=nullptr) 
		{
			d.apply(*ch);
			dispMan->fillDisplay();
			form->Invalidate();
		}
		delete ch;
	}

	bool HCEditorForm::isPrintable(wchar_t c)
	{
		//space is first printable, only unprintable after is DEL
		return(c >= ' ' && c!= 127);
	}


	void HCEditorForm::MarshalString ( String ^ s, string& os ) {
	   using namespace Runtime::InteropServices;
	   const char* chars = 
		  (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	   os = chars;
	   Marshal::FreeHGlobal(IntPtr((void*)chars));
	}

	void HCEditorForm::onFind(Object^  sender, System::EventArgs^  e)
	{
		findForm ^f = gcnew findForm();
		f->setFind();
		if(f->ShowDialog() == DialogResult::OK)
		{
			string find;
			MarshalString(f->getFindText(),find);
			d.apply(FindChange(find,dispMan));
			form->Invalidate();
		}
	}
	void HCEditorForm::onReplace(Object^  sender, EventArgs^  e)
	{
		findForm ^f = gcnew findForm();
		f->setReplace();
		if(f->ShowDialog() == DialogResult::OK)
		{
			string find,replace;
			MarshalString(f->getFindText(),find);
			MarshalString(f->getReplaceText(),replace);
			d.apply(ReplaceChange(find,replace, d.getContext(),dispMan));
			form->Invalidate();
		}
	}
	void HCEditorForm::onFileNew(Object^  sender, EventArgs^  e)
	{
		d.clear();
		form->Invalidate();
	}
	void HCEditorForm::onFileOpen(Object^  sender, EventArgs^  e)
	{
		OpenFileDialog^ load = gcnew OpenFileDialog();

		if(load->ShowDialog() == DialogResult::OK)
		{
			string path;
			MarshalString(load->FileName,path);
			d.load(path.c_str());
			form->Invalidate();
		}
	}
	void HCEditorForm::onSaveAs(Object^ sender, EventArgs^ e)
	{
		SaveFileDialog^ save = gcnew SaveFileDialog();

		if(save->ShowDialog() == DialogResult::OK)
		{
			string path;
			MarshalString(save->FileName,path);
			d.save(path.c_str());
		}
	}

	
};
