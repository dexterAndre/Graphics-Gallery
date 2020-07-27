#pragma once

#include "Test.h"

namespace test
{
	class TestRectangle : public Test
	{
	public:
		TestRectangle();
		~TestRectangle();

		void OnUpdate(float deltaTime) override;
		void OnRender(Renderer* renderer) override;
		void OnImGuiRender();

	private:
		float m_Position[3];
		float m_Rotation;
		float m_Scale[3];
	};
}