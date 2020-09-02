#pragma once

#include "entt.hpp"

namespace Galaxy
{
	class Scene
	{
	public:
		Scene();
		~Scene();
	private:
		entt::registry m_Registry;
	};
}