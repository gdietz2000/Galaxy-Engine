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
	Galaxy::Renderer2D::ResetStats();
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
		Galaxy::Renderer2D::DrawRotatedQuad({ 1.0f,0.0f }, { 0.8f,0.8f }, glm::radians(-45.0f), { 0.2f,0.3f,0.8f,1.0f });
		Galaxy::Renderer2D::DrawQuad({ -1.0f,0.0f }, { 0.8f,0.8f }, { 0.8f,0.3f,0.2f,1.0f });
		Galaxy::Renderer2D::DrawQuad({ 0.5f,-0.5f }, { 0.5f,0.75f }, { 0.8f,0.3f,0.2f,1.0f });
		Galaxy::Renderer2D::DrawQuad({ 0.0,0.0, -0.1f }, { 10.0f,10.0f }, m_CheckerboardTexture, 10.0f);
		Galaxy::Renderer2D::DrawRotatedQuad({ -2,0, 0.0f }, { 1.0f,1.0f }, glm::radians(rotation), m_CheckerboardTexture, 20.0f);
		Galaxy::Renderer2D::EndScene();

		Galaxy::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -4.75f; y < 5.25f; y += 0.5f)
		{
			for(float x = -4.75f; x < 5.25f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5) / 10, 0.4f, (y + 5) / 10 , 0.75f};
				Galaxy::Renderer2D::DrawQuad({ x,y }, { 0.45f, 0.45f }, color);
			}
		}
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

	auto stats = Galaxy::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quad Count: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}