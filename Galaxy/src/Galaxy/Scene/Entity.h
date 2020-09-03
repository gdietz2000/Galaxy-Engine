#pragma once
#include "Galaxy/Core/Log.h"

#include "Scene.h"

#include "entt.hpp"

namespace Galaxy
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;

		template<typename T, typename ... Args>
		T& AddComponent(Args&&... args)
		{
			GX_CORE_ASSERT(!HasComponent<T>(), "Entity already has this component!");

			return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			GX_CORE_ASSERT(HasComponent<T>(), "Entity does not have this component!");

			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.has<T>(m_EntityHandle);
		}

		template<typename T>
		void RemoveComponent()
		{
			GX_CORE_ASSERT(HasComponent<T>(), "Entity does not have this component!");

			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}
		
		operator bool() const { return m_EntityHandle != entt::null; }
		operator uint32_t() const { return (uint32_t)m_EntityHandle; }

	private:
		entt::entity m_EntityHandle{entt::null};
		Scene* m_Scene = nullptr;
	};
}