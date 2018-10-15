//
// Created by Alex on 03/10/2018.
//

#ifndef XOPENGLENGINE_DISPLAYMANAGER_H
#define XOPENGLENGINE_DISPLAYMANAGER_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <memory>
#include <exception>

class DisplayManager
{
public:
    /*create and initialize the screen and glfw*/
    DisplayManager();

    /*create and initialize the screen and glfw*/
    DisplayManager(std::string title,int height=0,int width=0);

    DisplayManager& operator = (DisplayManager const &obj);

    ~DisplayManager();

    void updateDisplay();
    bool windowShouldClose();
    void closeDisplay();
    GLFWwindow* getWindow();


private:
    std::shared_ptr<GLFWwindow> window;
    GLFWmonitor* monitor=nullptr;
    const GLFWvidmode* mode=nullptr;

};

class DisplayManagerException :public std::runtime_error {
public:
    DisplayManagerException() : runtime_error("DisplayManager default exception") {}

    DisplayManagerException(std::string err) : runtime_error(err.c_str()) {}
};

#endif //XOPENGLENGINE_DISPLAYMANAGER_H
