#pragma once
#include <vulkan/vulkan.h>
#include <memory>
#include <string>
#include <unordered_set>

namespace VKE {
	class PhysicalDevice {
	public:
		struct QueueFamilyIndices {
			int32_t Graphics = -1;
		};

	public:
		static std::shared_ptr<PhysicalDevice> Create(VkInstance instance);
		PhysicalDevice(VkInstance instance);
		~PhysicalDevice() = default;

		bool IsExtensionSupported(const std::string& extensionName) const;

		VkPhysicalDevice GetDeviceHandle() const { return m_Device; }
		const QueueFamilyIndices& GetQueueFamilyIndices() const { return m_QueueFamilyIndices; }
		const VkPhysicalDeviceProperties& GetProperties() const { return m_Properties; }
		const VkPhysicalDeviceFeatures& GetFeatures() const { return m_Features; }

	private:
		VkPhysicalDevice CreateDevice(VkInstance instance);
		QueueFamilyIndices CreateQueueFamilyIndices();
		bool IsDeviceSuitable(VkPhysicalDevice device, VkPhysicalDeviceProperties* properties, VkPhysicalDeviceFeatures* features);

	private:
		VkPhysicalDevice m_Device = VK_NULL_HANDLE;

		VkPhysicalDeviceProperties m_Properties;
		VkPhysicalDeviceFeatures m_Features;
		QueueFamilyIndices m_QueueFamilyIndices;
		std::unordered_set<std::string> m_SupportedExtensions;
	};
}