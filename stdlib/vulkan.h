// EDEN ENGINE Standard Library - Vulkan Bindings
// This file is automatically included in generated C++ code

#ifndef EDEN_VULKAN_H
#define EDEN_VULKAN_H

#include <vulkan/vulkan.h>
#include <stdint.h>

// Vulkan types (C-compatible wrappers)
typedef VkInstance VkInstance;
typedef VkPhysicalDevice VkPhysicalDevice;
typedef VkDevice VkDevice;
typedef VkQueue VkQueue;
typedef VkCommandPool VkCommandPool;
typedef VkCommandBuffer VkCommandBuffer;
typedef VkSwapchainKHR VkSwapchainKHR;
typedef VkSurfaceKHR VkSurfaceKHR;
typedef VkRenderPass VkRenderPass;
typedef VkPipeline VkPipeline;
typedef VkFramebuffer VkFramebuffer;
typedef VkBuffer VkBuffer;
typedef VkImage VkImage;
typedef VkImageView VkImageView;
typedef VkSemaphore VkSemaphore;
typedef VkFence VkFence;
typedef VkResult VkResult;

// Common Vulkan constants
#define VK_SUCCESS 0
#define VK_NOT_READY 1
#define VK_TIMEOUT 2
#define VK_EVENT_SET 3
#define VK_EVENT_RESET 4
#define VK_INCOMPLETE 5
#define VK_ERROR_OUT_OF_HOST_MEMORY -1
#define VK_ERROR_OUT_OF_DEVICE_MEMORY -2
#define VK_ERROR_INITIALIZATION_FAILED -3
#define VK_ERROR_DEVICE_LOST -4
#define VK_ERROR_MEMORY_MAP_FAILED -5
#define VK_ERROR_LAYER_NOT_PRESENT -6
#define VK_ERROR_EXTENSION_NOT_PRESENT -7
#define VK_ERROR_FEATURE_NOT_PRESENT -8
#define VK_ERROR_INCOMPATIBLE_DRIVER -9
#define VK_ERROR_TOO_MANY_OBJECTS -10
#define VK_ERROR_FORMAT_NOT_SUPPORTED -11
#define VK_ERROR_FRAGMENTED_POOL -12
#define VK_ERROR_UNKNOWN -13

// Common Vulkan function declarations
extern "C" {
    // Instance creation
    VkResult vkCreateInstance(const VkInstanceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkInstance* pInstance);
    void vkDestroyInstance(VkInstance instance, const VkAllocationCallbacks* pAllocator);
    
    // Physical device
    VkResult vkEnumeratePhysicalDevices(VkInstance instance, uint32_t* pPhysicalDeviceCount, VkPhysicalDevice* pPhysicalDevices);
    void vkGetPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties* pQueueFamilyProperties);
    VkResult vkGetPhysicalDeviceSurfaceSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, VkSurfaceKHR surface, VkBool32* pSupported);
    VkResult vkGetPhysicalDeviceSurfaceCapabilitiesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkSurfaceCapabilitiesKHR* pSurfaceCapabilities);
    VkResult vkGetPhysicalDeviceSurfaceFormatsKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pSurfaceFormatCount, VkSurfaceFormatKHR* pSurfaceFormats);
    
    // Device creation
    VkResult vkCreateDevice(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDevice* pDevice);
    void vkDestroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator);
    
    // Queue
    void vkGetDeviceQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue* pQueue);
    
    // Command pool
    VkResult vkCreateCommandPool(VkDevice device, const VkCommandPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCommandPool* pCommandPool);
    void vkDestroyCommandPool(VkDevice device, VkCommandPool commandPool, const VkAllocationCallbacks* pAllocator);
    
    // Command buffer
    VkResult vkAllocateCommandBuffers(VkDevice device, const VkCommandBufferAllocateInfo* pAllocateInfo, VkCommandBuffer* pCommandBuffers);
    void vkFreeCommandBuffers(VkDevice device, VkCommandPool commandPool, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers);
    
    // Swapchain
    VkResult vkCreateSwapchainKHR(VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain);
    void vkDestroySwapchainKHR(VkDevice device, VkSwapchainKHR swapchain, const VkAllocationCallbacks* pAllocator);
    VkResult vkGetSwapchainImagesKHR(VkDevice device, VkSwapchainKHR swapchain, uint32_t* pSwapchainImageCount, VkImage* pSwapchainImages);
    VkResult vkAcquireNextImageKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t timeout, VkSemaphore semaphore, VkFence fence, uint32_t* pImageIndex);
    
    // Render pass
    VkResult vkCreateRenderPass(VkDevice device, const VkRenderPassCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass);
    void vkDestroyRenderPass(VkDevice device, VkRenderPass renderPass, const VkAllocationCallbacks* pAllocator);
    
    // Image view
    VkResult vkCreateImageView(VkDevice device, const VkImageViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImageView* pView);
    void vkDestroyImageView(VkDevice device, VkImageView imageView, const VkAllocationCallbacks* pAllocator);
    
    // Synchronization
    VkResult vkCreateSemaphore(VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore);
    void vkDestroySemaphore(VkDevice device, VkSemaphore semaphore, const VkAllocationCallbacks* pAllocator);
    VkResult vkCreateFence(VkDevice device, const VkFenceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence);
    void vkDestroyFence(VkDevice device, VkFence fence, const VkAllocationCallbacks* pAllocator);
    VkResult vkWaitForFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences, VkBool32 waitAll, uint64_t timeout);
    VkResult vkResetFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences);
    
    // Device wait
    VkResult vkDeviceWaitIdle(VkDevice device);
}

#endif // EDEN_VULKAN_H

