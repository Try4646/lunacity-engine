#include "../Engine/Engine.h"  
#include "Windows.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
   LPSTR lpCmdLine, int nCmdShow) {  
   Engine engine;  
   if (engine.Init(800, 600, "Lunacity")) {  
       engine.Run();  
   }  
   engine.Shutdown();  
   return 0;  
}