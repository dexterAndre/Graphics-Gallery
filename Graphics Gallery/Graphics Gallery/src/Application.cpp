#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "GraphicsStatics.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

#include "tests/TestClearColor.h"
#include "tests/TestRectangle.h"




int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Setting OpenGL version */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    /* Initializing OpenGL functions */
    if (glewInit() != GLEW_OK)
    {
        std::cout << "ERROR: glewInit(); not valid" << std::endl;
    }

    std::cout << "[OpenGL Version: " << glGetString(GL_VERSION) << "]" << std::endl;

    /* Setting OpenGL states */
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


    {
        /* Renderer setup */
        Renderer renderer;

        /* GUI setup */
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

        test::TestRectangle test;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            renderer.Clear(GS::m_CLEARCOLOR);

            test.OnUpdate(0.0f);
            test.OnRender(&renderer);

            /* GUI setup */
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            test.OnImGuiRender();

            /* GUI rendering */
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    /* GUI cleanup */
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    /* GLFW cleanup */
    glfwTerminate();
    return 0;
}