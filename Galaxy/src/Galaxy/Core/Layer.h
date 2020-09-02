#pragma once

#include "Galaxy/Core/Core.h"
#include "Galaxy/Core/Timestep.h"
#include "Galaxy/Events/Event.h"

namespace Galaxy
{
	class  Layer
	{
	public:
		Layer(const std::string& name = "Layer") : m_DebugName(name) {};
		virtual ~Layer() {};

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& e) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}

