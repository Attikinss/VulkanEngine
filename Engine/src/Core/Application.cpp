#include "Application.h"
#include <iostream>

namespace VKE {
	void Application::Initialise() {
		m_Initialised = true;

		std::cout << "Application Initialised." << std::endl;
	}

	void Application::Run() {
		m_Running = true;
		std::cout << "Application Running..." << std::endl;
	}

	void Application::Shutdown() {
		m_Running = false;
		m_Initialised = false;
		std::cout << "Application Shutdown." << std::endl;
	}
}
