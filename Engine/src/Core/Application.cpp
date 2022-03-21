#include "Application.h"
#include "Window.h"

#include <iostream>

namespace VKE {
	Application::~Application() {
		Shutdown();
	}

	void Application::Initialise() {
		if (m_Initialised) {
			// TODO: Notify user
			return;
		}

		m_Window = new Window(1280, 720, "Vulkan Engine");
		m_Initialised = true;

		std::cout << "Application Initialised." << std::endl;
	}

	void Application::Run() {
		m_Running = true;
		std::cout << "Application Running..." << std::endl;

		while (m_Running) {
			m_Window->PollEvents();
			m_Window->SwapBuffers();

			if (m_Window->ShouldClose()) {
				m_Running = false;
			}
		}
	}

	void Application::Shutdown() {
		if (!m_Initialised) {
			// TODO: Notify user
			return;
		}

		delete m_Window;

		m_Running = false;
		m_Initialised = false;
		std::cout << "Application Shutdown." << std::endl;
	}
}
