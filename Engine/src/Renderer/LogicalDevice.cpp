#include "LogicalDevice.h"

namespace VKE {
	std::shared_ptr<LogicalDevice> LogicalDevice::Create(const std::shared_ptr<PhysicalDevice>& device) {
		return std::make_shared<LogicalDevice>(device);
	}

	LogicalDevice::LogicalDevice(const std::shared_ptr<PhysicalDevice>& device) {
		m_Device = CreateDevice(device);
		m_GraphicsQueue = GetDeviceQueue(device->GetQueueFamilyIndices().Graphics);
	}

	LogicalDevice::~LogicalDevice() {
		vkDestroyDevice(m_Device, nullptr);
	}

	VkDevice LogicalDevice::CreateDevice(const std::shared_ptr<PhysicalDevice>& device) {
		auto indices = device->GetQueueFamilyIndices();

		// Define infornation for device queue
		float queuePriority = 1.0f;
		VkDeviceQueueCreateInfo queueInfo{};
		queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueInfo.queueFamilyIndex = (uint32_t)indices.Graphics;
		queueInfo.queueCount = 1;
		queueInfo.pQueuePriorities = &queuePriority;

		// Define information about desired device features
		VkPhysicalDeviceFeatures deviceFeatures{};

		// Define information about the device
		VkDeviceCreateInfo deviceInfo{};
		deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		deviceInfo.pQueueCreateInfos = &queueInfo;
		deviceInfo.queueCreateInfoCount = 1;
		deviceInfo.pEnabledFeatures = &deviceFeatures;

		// TODO: Include validation layers for the device

		// TODO: Error handling
		VkDevice logicalDevice;
		vkCreateDevice(device->GetDeviceHandle(), &deviceInfo, nullptr, &logicalDevice);
		return logicalDevice;
	}

	VkQueue LogicalDevice::GetDeviceQueue(int32_t queueFamilyIndex) {
		VkQueue queue;
		vkGetDeviceQueue(m_Device, queueFamilyIndex, 0, &queue);
		return queue;
	}
}
