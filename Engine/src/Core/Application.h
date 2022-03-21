#pragma once

namespace VKE {
	class Window;

	class Application {
	public:
		Application() = default;
		~Application();

		void Initialise();
		void Run();
		void Shutdown();

	private:
		bool m_Running = false;
		bool m_Initialised = false;

		Window* m_Window = nullptr;
	};
}