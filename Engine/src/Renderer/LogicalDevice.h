#pragma once
#include "PhysicalDevice.h"

#include <vulkan/vulkan.h>
#include <memory>

namespace VKE {
	class LogicalDevice {
	public:
		static std::shared_ptr<LogicalDevice> Create(const std::shared_ptr<PhysicalDevice>& device);
		
		LogicalDevice(const std::shared_ptr<PhysicalDevice>& device);
		~LogicalDevice();

		const std::shared_ptr<PhysicalDevice>& GetPhysicalDevice() const { return m_PhysicalDevice; }

	private:
		VkDevice CreateDevice(const std::shared_ptr<PhysicalDevice>& device);
		VkQueue GetDeviceQueue(int32_t queueFamilyIndex);

	private:
		VkDevice m_Device = VK_NULL_HANDLE;
		std::shared_ptr<PhysicalDevice> m_PhysicalDevice;

		VkQueue m_GraphicsQueue = VK_NULL_HANDLE;
	};
}