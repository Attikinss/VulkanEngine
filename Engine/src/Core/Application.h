#pragma once

namespace VKE {
	class Application {
	public:
		void Initialise();
		void Run();
		void Shutdown();

	private:
		bool m_Running = false;
		bool m_Initialised = false;
	};
}