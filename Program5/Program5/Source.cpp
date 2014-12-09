
#include "MyForm.h"
using namespace Program5;

#pragma comment(linker,"/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

int main()
{
	Application::Run(gcnew MyForm());
	
	return 0;
}