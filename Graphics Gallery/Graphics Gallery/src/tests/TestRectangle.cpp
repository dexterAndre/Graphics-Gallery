#include "TestRectangle.h"
#include "Renderer.h"
#include "GraphicsBuffers.h"
#include "Shader.h"
#include "GraphicsStatics.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "imgui/imgui.h"

namespace test
{
	TestRectangle::TestRectangle()
		: m_Position{ 0.0f, 0.0f, 0.0f }
		, m_Rotation{ 0.0f }
		, m_Scale{ 1.0f, 1.0f, 1.0f }
	{
	}
	TestRectangle::~TestRectangle()
	{
	}
	void TestRectangle::OnUpdate(float deltaTime)
	{
	}
	void TestRectangle::OnRender(Renderer* renderer)
	{
		/* Clearing */
		renderer->Clear(GS::m_CLEARCOLOR);

		/* Geometry content */
		float positions[] = {
			// Positions						// Colors
			 0.5f,       0.5f,      0.0f,		1.0f,	0.0f,	0.0f,	1.0f,
			-0.5f,       0.5f,      0.0f,		0.0f,   1.0f,	0.0f,	1.0f,
			-0.5f,      -0.5f,      0.0f,		0.0f,   0.0f,	1.0f,	1.0f,
			 0.5f,      -0.5f,      0.0f,		1.0f,   1.0f,	1.0f,	1.0f
		};

		unsigned int indices[] = {
			0, 1, 2,
			0, 2, 3
		};

		/* Buffer setup */
		VertexArray VAO;
		VertexBuffer VBO(positions, 4 * 7 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(4);
		VAO.AddBuffer(VBO, layout);
		IndexBuffer EBO(indices, 6);

		/* Shader setup */
		Shader shader("res/shaders/basic_unlit_color.shader");
		shader.Bind();

		/* Cleaning up */
		VAO.Unbind();
		VBO.Unbind();
		EBO.Unbind();
		shader.Unbind();

		/* Recalculating MVP matrices */
		{
			//glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::make_vec3(m_Position));
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::make_vec3(m_Position));
			model = glm::rotate(model, glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::scale(model, glm::make_vec3(m_Scale));
			glm::mat4 view = glm::mat4(1.0f);
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
			//glm::mat4 proj = glm::mat4(1.0f);
			glm::mat4 proj = glm::perspective(45.0f, (float)GS::m_SCR_WIDTH / GS::m_SCR_HEIGHT, 0.1f, 1000.0f);
			glm::mat4 mvp = proj * view * model;
			shader.Bind();
			shader.SetUniformMat4f("u_MVP", mvp);
			renderer->Draw(VAO, EBO, shader);
		}
	}
	void TestRectangle::OnImGuiRender()
	{
		ImGui::SliderFloat3("Position", m_Position, -1.0f, 1.0f);
		ImGui::SliderFloat("Rotation", &m_Rotation, 0.0f, 360.0f);
		ImGui::SliderFloat3("Scale", m_Scale, 0.0f, 1.5f);

		//ImGui::ShowDemoWindow();
	}
}