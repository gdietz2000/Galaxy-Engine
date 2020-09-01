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

    static bool dockspaceOpen = true;
    static bool opt_fullscreen_persistant = true;
    bool opt_fullscreen = opt_fullscreen_persistant;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->GetWorkPos());
        ImGui::SetNextWindowSize(viewport->GetWorkSize());
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
    // and handle the pass-thru hole, so we ask Begin() to not render a background.
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
    ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            // Disabling fullscreen would allow the window to be moved to the front of other windows,
            // which we can't undo at the moment without finer window depth/z control.
            //ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

            if (ImGui::MenuItem("Exit"))
            {
                Galaxy::Application::Get().Close();
            }
    
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    ImGui::Begin("Settings");

    auto stats = Galaxy::Renderer2D::GetStats();
    ImGui::Text("Renderer2D Stats:");
    ImGui::Text("Draw Calls: %d", stats.DrawCalls);
    ImGui::Text("Quad Count: %d", stats.QuadCount);
    ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
    ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

    uint32_t textureID = m_CheckerboardTexture->GetRendererID();
    ImGui::Image((void*)textureID, ImVec2(256, 256));
    ImGui::End();

    ImGui::End();
}