#include <vulkan/vulkan.hpp>
#include <iostream>
#include <vector>

int main() {
    try {
        vk::ApplicationInfo appInfo("VulkanTest", 1, "NoEngine", 1, VK_API_VERSION_1_0);

        // Required for MoltenVK on macOS
        std::vector<const char*> extensions = {
            VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME
        };

        vk::InstanceCreateInfo createInfo(
            vk::InstanceCreateFlagBits::eEnumeratePortabilityKHR,
            &appInfo,
            0, nullptr, // layers
            static_cast<uint32_t>(extensions.size()), extensions.data()
        );

        vk::Instance instance = vk::createInstance(createInfo);

        std::vector<vk::PhysicalDevice> devices = instance.enumeratePhysicalDevices();
        std::cout << "Success! MoltenVK found " << devices.size() << " GPU(s):\n";

        for (const auto& device : devices) {
            std::cout << " - " << device.getProperties().deviceName << "\n";
        }

        instance.destroy();
    } catch (const vk::SystemError& err) {
        std::cerr << "Vulkan Error: " << err.what() << "\n";
        return 1;
    }

    return 0;
}
