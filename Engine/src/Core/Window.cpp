#include "Window.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace VKE {
	static GLFWwindow* CreateWindow(int32_t width, int32_t height, const std::string& title) {
		// Initialize glfw if not already initialized
		glfwInit();

		// For now do not create glfw context as vulkan does not need it
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		// For now do not allow window resizing via glfw
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		return glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	}

	Window::Window(int32_t width, int32_t height, const std::string& title)
		: m_Width(width), m_Height(height), m_Title(title), m_WindowHandle(CreateWindow(width, height, title)) {
	}

	Window::~Window() {
		// Only destroy if it actally exists
		if (m_WindowHandle) {
			glfwDestroyWindow(m_WindowHandle);
			m_WindowHandle = nullptr;
		}

		// TODO: Move somewhere that makes sense
		glfwTerminate();
	}

	void Window::PollEvents() {
		glfwPollEvents();
	}

	void Window::SwapBuffers() {
		glfwSwapBuffers(m_WindowHandle);
	}

	bool Window::ShouldClose() const {
		return glfwWindowShouldClose(m_WindowHandle);
	}
}