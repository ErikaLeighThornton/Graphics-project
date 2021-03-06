#include <iostream>
#include "../../Gateware/Interface/G_System/GWindow.h" 

#include "LetsDrawSomeStuff.h"

using namespace GW;
using namespace CORE;
using namespace SYSTEM;

// Main entry point
int main()
{
	// Handle to our new window, be sure to DecrementCount to free memory
	GWindow* myWindow = nullptr;
	// Our class that contains all D3D11 related Code
	LetsDrawSomeStuff* myDrawSystem = nullptr;
	// Create new window
	if (G_SUCCESS(CreateGWindow(100, 100, 1024, 768, GWindowStyle::WINDOWEDBORDERED, &myWindow)))
	{
		// Create our Draw system now that we have a window, this will also open our window
		myDrawSystem = new LetsDrawSomeStuff(myWindow);
		// main loop, assumes window has already been opened
		GW::SYSTEM::GWindowInputEvents lastEvent;
		while (G_SUCCESS(myWindow->GetLastEvent(lastEvent)) && 
				lastEvent != GW::SYSTEM::GWindowInputEvents::DESTROY)
		{
			// process platform specific window events
			if (G_FAIL(myWindow->ProcessWindowEvents()))
				break; // nope...

			// Before or after events are processed lets do some drawing
			myDrawSystem->Render();
		}
		// Free drawing system and all internal elements
		delete myDrawSystem; 
		myDrawSystem = nullptr;
		// free window
		myWindow->DecrementCount();
	}
    return 0;
}
