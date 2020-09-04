#pragma once

#include <Galaxy.h>

#include "Panels/SceneHierarchy.h"

namespace Galaxy
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(Timestep ts) override;
		virtual void OnEvent(Event& event) override;
		virtual void OnImGuiRender() override;
	private:
		OrthographicCameraController m_CameraController;

		//Temporary
		Ref<VertexArray> m_VertexArray;
		Ref<Shader> m_Shader;
		Ref<Framebuffer> m_FrameBuffer;

		Ref<Texture2D> m_CheckerboardTexture;

		Ref<Scene> m_ActiveScene;
		Entity m_SquareEntity;
		Entity m_CameraEntity;
		Entity m_ClipSpaceCamera;

		bool m_PrimaryCamera = true;

		bool m_ViewportFocused = false;
		bool m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = {0.0f, 0.0f};

		//Panels
		SceneHierarchyPanel m_SceneHierarchyPanel;
	};
}