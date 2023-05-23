#include "MainWindow.h"

using namespace System;
using namespace System::Windows;
using namespace System::Windows::Forms;
using namespace AudioEqWin;

[STAThreadAttribute]
int my_main(array<String^>^ args)
{
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	AudioEqWin::MainWindow window;
	Application::Run(% window);
	return 0;
}