#pragma once

#include "Galaxy/Layer.h"
#include "Galaxy/Events/ApplicationEvent.h"
#include "Galaxy/Events/KeyEvent.h"
#include "Galaxy/Events/MouseEvent.h"

namespace Galaxy
{
	class GALAXY_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}