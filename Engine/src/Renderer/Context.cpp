#include "Context.h"

#include <iostream>
#include <vector>
#include <GLFW/glfw3.h>

namespace VKE {
#ifdef _DEBUG
	static bool s_Validation = true;
#else
	static bool s_Validation = false;
#endif

	static std::vector<const char*> GetExtensions() {
		std::vector<const char*> extensions = { VK_KHR_SURFACE_EXTENSION_NAME, "VK_KHR_win32_surface" };

		// Add debug extensions
		if (s_Validation) {
			extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
			extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
			extensions.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
		}

		return extensions;
	}

	static VKAPI_ATTR VkBool32 VKAPI_CALL VulkanDebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* callbackData, void* userData) {
		// TODO: Switch on severity
		std::cerr << "Validation Layer: " << callbackData->pMessage << std::endl;
		return VK_FALSE;
	}

	Context::Context() {
		if (!glfwVulkanSupported()) {
			// TODO: Freak out
		}

		// Define information about the application
		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "VK Engine";
		appInfo.pEngineName = "VK Engine";
		appInfo.apiVersion = VK_API_VERSION_1_2;

		// Define information about the Vulkan instance
		VkInstanceCreateInfo instanceInfo = {};
		instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instanceInfo.pApplicationInfo = &appInfo;

		// Define extensions for instance
		std::vector<const char*> instanceExtensions = GetExtensions();
		instanceInfo.enabledExtensionCount = (uint32_t)instanceExtensions.size();
		instanceInfo.ppEnabledExtensionNames = instanceExtensions.data();

		if (s_Validation) {
			// Query how many extension properties are available
			uint32_t layerCount = 0;
			vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

			// Get extension properties
			std::vector<VkLayerProperties> layerProperties(layerCount);
			vkEnumerateInstanceLayerProperties(&layerCount, layerProperties.data());

			// Check if validation layer extension is present
			const char* validationLayerName = "VK_LAYER_KHRONOS_validation";
			bool validationLayerPresent = false;
			for (const auto& layer : layerProperties) {
				if (strcmp(validationLayerName, layer.layerName) == 0) {
					validationLayerPresent = true;
					break;
				}
			}

			if (validationLayerPresent) {
				// Assign validation layer to instance
				instanceInfo.ppEnabledLayerNames = &validationLayerName;
				instanceInfo.enabledLayerCount = 1;
			}
			else {
				//TODO: Freak out
			}
		}

		// Assert on this if it fails
		if (vkCreateInstance(&instanceInfo, nullptr, &s_Instance) != VkResult::VK_SUCCESS) {
			// TODO: Freak out
		}

		if (s_Validation) {
			// Define information about the debug messenger
			VkDebugUtilsMessengerCreateInfoEXT debugInfo = {};
			debugInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
			debugInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
			debugInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
			debugInfo.pfnUserCallback = VulkanDebugCallback;
			instanceInfo.pNext = &debugInfo;

			// Create messenger
			auto vkCreateDebugUtilsMessengerEXT = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(s_Instance, "vkCreateDebugUtilsMessengerEXT");
			if (vkCreateDebugUtilsMessengerEXT(s_Instance, &debugInfo, nullptr, &m_DebugMessenger) != VkResult::VK_SUCCESS) {
				//TODO: Freak out
			}
		}
	}

	Context::~Context() {
		if (s_Validation) {
			// Destroy messenger
			auto vkDestroyDebugUtilsMessengerEXT = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(s_Instance, "vkDestroyDebugUtilsMessengerEXT");
			vkDestroyDebugUtilsMessengerEXT(s_Instance, m_DebugMessenger, nullptr);
		}

		// Destroy Vulkan instance
		if (s_Instance) {
			vkDestroyInstance(s_Instance, nullptr);
			s_Instance = nullptr;
		}
	}
}