#include "VKEngine.h"

int main() {
	VKE::Application app;
	app.Initialise();
	app.Run();
	app.Shutdown();

	return 0;
}