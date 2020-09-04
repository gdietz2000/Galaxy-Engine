#include "gxpch.h"
#include "Scene.h"

#include "Entity.h"

#include "Component.h"

#include "Galaxy/Renderer/Renderer2D.h"

#include "glm/glm.hpp"

namespace Galaxy
{

	static void OnTransformConstruct(entt::registry& registry, entt::entity entity)
	{
		
	}

	Scene::Scene()
	{
#if ENT_EXAMPLE_CODE
		struct MeshComponent 
		{
			float value;
			MeshComponent() = default;
		};
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

		m_Registry.on_construct<TransformComponent>().connect<&OnTransformConstruct>();

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
#endif
	}

	Scene::~Scene()
	{
	
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;

		return entity;
	}

	void Scene::OnUpdate(Timestep ts)
	{
		//Update Scripts
		{
			m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
				{
					if (!nsc.Instance)
					{
						nsc.InstantiateFunction();
						nsc.Instance->m_Entity = Entity{ entity, this };
						nsc.OnCreateFunction(nsc.Instance);
					}

					nsc.OnUpdateFunction(nsc.Instance, ts);
				});
		}

		//Render sprites
		Camera* mainCamera = nullptr;
		glm::mat4 tform(1.0f);
		auto view = m_Registry.view<TransformComponent, CameraComponent>();
		for (auto entity : view)
		{
			auto& [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

			if (camera.Primary)
			{
				mainCamera = &camera.Camera;
				tform = transform.Transform;
				break;
			}
		}

		if (mainCamera)
		{
			Renderer2D::BeginScene(*mainCamera, tform);

			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

				Renderer2D::DrawQuad(transform, sprite.Color);

			}

			Renderer2D::EndScene();
		}
	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		//Resize out non-Fixed Aspect Ratio Cameras
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraComp = view.get<CameraComponent>(entity);
			if (!cameraComp.FixedApsectRatio)
				cameraComp.Camera.SetViewportSize(width, height);
		}
	}
}