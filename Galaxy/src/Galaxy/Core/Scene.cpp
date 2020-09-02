#include "gxpch.h"
#include "Scene.h"

#include "glm/glm.hpp"

namespace Galaxy
{

	static void DoMaths(const glm::mat4& transform)
	{
	
	}

	Scene::Scene()
	{
		struct MeshComponent {};
		struct TransformComponent
		{
			glm::mat4 Transform;

			TransformComponent() = default;
			TransformComponent(const TransformComponent&) = default;
			TransformComponent(const glm::mat4& transform)
				: Transform(transform) {}

			operator const glm::mat4& () const { return Transform; }

		};

		entt::entity entity = m_Registry.create();

		auto& transform = m_Registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));

		if (m_Registry.has<TransformComponent>(entity))
			TransformComponent& ent = m_Registry.get<TransformComponent>(entity);

		auto view = m_Registry.view<TransformComponent>();

		for (auto entity : view)
		{
			TransformComponent& transform = view.get<TransformComponent>(entity);
		}

		auto group = m_Registry.group<TransformComponent>(entt::get<MeshComponent>);
		for (auto entity : group)
		{
			auto& [transform, mesh] = group.get<TransformComponent, MeshComponent>(entity);

		}
	}

	Scene::~Scene()
	{
	
	}
}