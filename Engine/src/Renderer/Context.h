#pragma once
#include <vulkan/vulkan.h>

namespace VKE {
	class Context {
	public:
		Context();
		~Context();

		static VkInstance GetInstance() { return s_Instance; }

	private:
		VkDebugUtilsMessengerEXT m_DebugMessenger = VK_NULL_HANDLE;

		inline static VkInstance s_Instance;
	};
}