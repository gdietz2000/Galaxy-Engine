#pragma once

#include <Galaxy.h>

class Sandbox2D : public Galaxy::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D();

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Galaxy::Timestep ts) override;
	virtual void OnEvent(Galaxy::Event& event) override;
	virtual void OnImGuiRender() override;
private:
	Galaxy::OrthographicCameraController m_CameraController;

	//Temporary
	Galaxy::Ref<Galaxy::VertexArray> m_VertexArray;
	Galaxy::Ref<Galaxy::Shader> m_Shader;
	
	glm::vec4 m_SquareColor = { 0.2f,0.3f,0.8f,1.0f };
};