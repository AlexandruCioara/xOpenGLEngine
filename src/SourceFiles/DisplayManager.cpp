//
// Created by Alex on 03/10/2018.
//

#include "../HeaderFiles/DisplayManager.h"


DisplayManager::DisplayManager() {
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

DisplayManager::DisplayManager(std::string title,int height,int width) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    monitor = glfwGetPrimaryMonitor();
    mode = glfwGetVideoMode(monitor);

    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
    glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_FALSE);
    window.reset();
    if (width==0 || height==0) {
        window = std::shared_ptr<GLFWwindow>(glfwCreateWindow(mode->width, mode->height, title.c_str(), monitor, NULL),
                                             [](GLFWwindow *window) {
                                                 glfwDestroyWindow(window);
                                                 window = nullptr;
                                             });
    }
    else {
        window = std::shared_ptr<GLFWwindow>(glfwCreateWindow(width, height, title.c_str(), NULL, NULL),
                                             [](GLFWwindow *window) {
                                                 glfwDestroyWindow(window);
                                                 window = nullptr;
                                             });
    }
    //GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, SCREEN_TITLE.c_str(), glfwGetPrimaryMonitor(), NULL);
    if (window == nullptr) {
        std::string err = "Failed to create GLFW window\n";
        throw DisplayManagerException(err);
    }
    glfwMakeContextCurrent(window.get());
    glfwSetFramebufferSizeCallback(window.get(), framebuffer_size_callback); // the function framebuffer_size_callback can be found in DisplayManager.cpp
}

DisplayManager & DisplayManager::operator=(DisplayManager const & obj)
{
    if (this != &obj) {
        this->monitor = obj.monitor;
        this->window = obj.window;
        this->mode = obj.mode;
    }
    return *this;
}

void DisplayManager::updateDisplay()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(this->window.get());
}

bool DisplayManager::windowShouldClose()
{
    if (glfwGetKey(window.get(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window.get(), true);
    return !glfwWindowShouldClose(window.get());
}

void DisplayManager::closeDisplay()
{
    if (window != nullptr) {
        window.reset();
        window = nullptr;
    }
}

GLFWwindow * DisplayManager::getWindow()
{
    return this->window.get();
}

DisplayManager::~DisplayManager() {
    if (window.get() != nullptr) {
        window.reset();
    }
}