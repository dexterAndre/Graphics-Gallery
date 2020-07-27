#include "TestClearColor.h"
#include "Renderer.h"
#include "imgui/imgui.h"

namespace test
{
	TestClearColor::TestClearColor()
		: m_ClearColor{ 0.2f, 0.3f, 0.8f, 1.0f }
	{
	}
	TestClearColor::~TestClearColor()
	{
	}
	void TestClearColor::OnUpdate(float deltaTime)
	{
	}
	void TestClearColor::OnRender(Renderer* renderer)
	{
		renderer->Clear(m_ClearColor);
	}
	void TestClearColor::OnImGuiRender()
	{
		ImGui::ColorEdit4("Clear Color", m_ClearColor);
	}
}