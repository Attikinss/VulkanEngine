#pragma once
#include "Utils/NonCopyable.h"

#include <string>

struct GLFWwindow;

namespace VKE {
	class Window : private NonCopyable {
	public:
		Window(int32_t width, int32_t height, const std::string& title);
		~Window();

		void PollEvents();
		void SwapBuffers();

		// TODO: Move functionality into events
		bool ShouldClose() const;

	private:
		std::string m_Title;
		int32_t m_Width;
		int32_t m_Height;
		GLFWwindow* m_WindowHandle;
	};
}