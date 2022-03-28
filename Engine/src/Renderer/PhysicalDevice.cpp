#include "PhysicalDevice.h"

#include <vector>

namespace VKE {
	std::shared_ptr<PhysicalDevice> PhysicalDevice::Create(VkInstance instance) {
		return std::make_shared<PhysicalDevice>(instance);
	}

	PhysicalDevice::PhysicalDevice(VkInstance instance) {
		m_Device = CreateDevice(instance);
		m_QueueFamilyIndices = CreateQueueFamilyIndices();
		
		// Query number of available extensions
		uint32_t extensionCount = 0;
		vkEnumerateDeviceExtensionProperties(m_Device, nullptr, &extensionCount, nullptr);
		
		if (extensionCount > 0) {
			// Get all available extensions
			std::vector<VkExtensionProperties> extensions(extensionCount);
			vkEnumerateDeviceExtensionProperties(m_Device, nullptr, &extensionCount, &extensions.front());

			// Write all extensions names to supported set
			for (const auto& ext : extensions) {
				m_SupportedExtensions.emplace(ext.extensionName);
			}
		}
	}

	bool PhysicalDevice::IsExtensionSupported(const std::string& extensionName) const {
		return m_SupportedExtensions.find(extensionName) != m_SupportedExtensions.end();
	}

	VkPhysicalDevice PhysicalDevice::CreateDevice(VkInstance instance) {
		// Query number of GPUs available
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

		if (deviceCount == 0) {
			// TODO: Freak out
		}

		// Retrieve available GPUs
		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

		// For now, pick the first supported device
		for (auto& device : devices) {
			if (IsDeviceSuitable(device, &m_Properties, &m_Features)) {
				return device;
			}
		}

		// TODO: Throw exception or something instead
		return devices.back();
	}

	PhysicalDevice::QueueFamilyIndices PhysicalDevice::CreateQueueFamilyIndices() {
		QueueFamilyIndices indices;

		// Query how many queue family properties are available
		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(m_Device, &queueFamilyCount, nullptr);

		// Get queue family properties
		std::vector<VkQueueFamilyProperties> queueFamilyProps(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(m_Device, &queueFamilyCount, queueFamilyProps.data());

		// Find queue family that supports VK_QUEUE_GRAPHICS_BIT
		for (uint32_t i = 0; i < queueFamilyCount; i++) {
			if (queueFamilyProps[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
				indices.Graphics = i;
				break;
			}
		}

		return indices;
	}

	bool PhysicalDevice::IsDeviceSuitable(VkPhysicalDevice device, VkPhysicalDeviceProperties* properties, VkPhysicalDeviceFeatures* features) {
		// Retrieve device properties
		vkGetPhysicalDeviceProperties(device, properties);

		// Retrieve device features
		vkGetPhysicalDeviceFeatures(device, features);

		// Ensure GPU is not an integrated graphics unit and supports graphics queue family
		return properties->deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU;
	}
}
