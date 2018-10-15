#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "src/HeaderFiles/DisplayManager.h"
#include <glm/glm.hpp>
#include <vector>


void processInput(GLFWwindow *window,DisplayManager &display);

float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
};
// settings
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 600;
const std::string SCREEN_TITLE = "OpenGL Engine";

int main() {
    glfwInit();
    {
        DisplayManager display;

        try {
            display = DisplayManager(SCREEN_TITLE,400,400);
        }
        catch (DisplayManagerException &e) {
            std::cout << e.what();
            glfwTerminate();
            return -1;
        }

        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            glfwTerminate();
            return -1;
        }
        while (display.windowShouldClose()) {

            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            // -------------------------------------------------------------------------------

            // input
            // -----
            processInput(display.getWindow(),display);

            // render
            // ------
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glfwSwapBuffers(display.getWindow());

            glfwPollEvents();
        }
        display.closeDisplay();
    }
    glfwTerminate();
    return 0;
}
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window,DisplayManager & display)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window,GLFW_KEY_K)==GLFW_PRESS) {
        display=DisplayManager(SCREEN_TITLE,400,600);
        std::cout << "viewport\n";
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}





