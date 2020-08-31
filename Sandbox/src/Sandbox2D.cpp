#include "Sandbox2D.h"

#include "Platform/OpenGl/OpenGLShader.h"

#include "ImGui/imgui.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Galaxy/Debug/Instrumentor.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(16.0f / 9.0f)
{

}

Sandbox2D::~Sandbox2D()
{

}

void Sandbox2D::OnAttach()
{
	m_CheckerboardTexture = Galaxy::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(Galaxy::Timestep ts)
{
	GX_PROFILE_FUNCTION();

	//Update
	{
		GX_PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}

	//Render
	{
		GX_PROFILE_SCOPE("Renderer Prep");
		Galaxy::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Galaxy::RenderCommand::Clear();
	}

	{
		static float rotation = 0.0f;
		rotation += ts * 50.0;

		GX_PROFILE_SCOPE("Renderer Draw");
		Galaxy::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Galaxy::Renderer2D::DrawRotatedQuad({ 1.0f,0.0f }, { 0.8f,0.8f }, rotation, { 0.8f,0.3f,0.2f,1.0f });
		Galaxy::Renderer2D::DrawQuad({ -1.0f,0.0f }, { 0.8f,0.8f }, { 0.2f,0.3f,0.8f,1.0f });
		Galaxy::Renderer2D::DrawQuad({ 0.5f,-0.5f }, { 0.5f,0.75f }, { 0.8f,0.3f,0.2f,1.0f });
		Galaxy::Renderer2D::DrawQuad({ 0.0,-0.0, -0.1f }, { 10.0f,10.0f }, m_CheckerboardTexture, 10.0f);
		Galaxy::Renderer2D::DrawRotatedQuad({ 0,0, 0.0f }, { 1.0f,1.0f }, 45, m_CheckerboardTexture, 20.0f);
		Galaxy::Renderer2D::EndScene(); 
	}
}

void Sandbox2D::OnEvent(Galaxy::Event& event)
{
	m_CameraController.OnEvent(event);
}

void Sandbox2D::OnImGuiRender()
{
	GX_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}