#include "Sandbox2D.h"

#include "Platform/OpenGl/OpenGLShader.h"

#include "ImGui/imgui.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(16.0f / 9.0f)
{

}

Sandbox2D::~Sandbox2D()
{

}

void Sandbox2D::OnAttach()
{
	m_VertexArray = Galaxy::VertexArray::Create();

	float squareVertices[3 * 4] = {
		   -0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f,  0.5f, 0.0f,
		   -0.5f,  0.5f, 0.0f
	};

	Galaxy::Ref<Galaxy::VertexBuffer> m_VertexBuffer = Galaxy::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
	m_VertexBuffer->SetLayout({ { "a_Position", Galaxy::ShaderDataType::Float3 } });

	m_VertexArray->AddVertexBuffer(m_VertexBuffer);

	unsigned int squareIndices[6] = { 0,1,2, 2,3,0 };
	Galaxy::Ref<Galaxy::IndexBuffer> m_IndexBuffer = Galaxy::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));

	m_VertexArray->SetIndexBuffer(m_IndexBuffer);

	m_Shader = Galaxy::Shader::Create("assets/shaders/FlatColorShader.glsl");


}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(Galaxy::Timestep ts)
{
	//Update
	m_CameraController.OnUpdate(ts);

	//Render

	Galaxy::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Galaxy::RenderCommand::Clear();

	Galaxy::Renderer::BeginScene(m_CameraController.GetCamera());

	std::dynamic_pointer_cast<Galaxy::OpenGLShader>(m_Shader)->Bind();
	std::dynamic_pointer_cast<Galaxy::OpenGLShader>(m_Shader)->UploadUniformFloat4("u_Color", m_SquareColor);

	Galaxy::Renderer::Submit(m_VertexArray, m_Shader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Galaxy::Renderer::EndScene();
}

void Sandbox2D::OnEvent(Galaxy::Event& event)
{
	m_CameraController.OnEvent(event);
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}