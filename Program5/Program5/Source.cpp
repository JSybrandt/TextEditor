
#include "MyForm.h"
using namespace Program5;

#pragma comment(linker,"/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

[STAThreadAttribute]
int main()
{
	MyForm ^ f = gcnew MyForm();
	Application::Run(f);
	
	return 0;
}