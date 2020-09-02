#pragma once

#include "Galaxy/Core/Layer.h"
#include "Galaxy/Events/ApplicationEvent.h"
#include "Galaxy/Events/KeyEvent.h"
#include "Galaxy/Events/MouseEvent.h"

namespace Galaxy
{
	class  ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& e) override;

		void SetBlockEvents(bool block) { m_BlockEvents = block; }

		void Begin();
		void End();
	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};
}