#pragma once

#include <Galaxy.h>
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

		glm::vec4 m_SquareColor = { 0.2f,0.3f,0.8f,1.0f };
	};
}