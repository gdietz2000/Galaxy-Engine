#include <Galaxy.h>

#include "Platform/OpenGl/OpenGLShader.h"

#include "ImGui/imgui.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Sandbox2D.h"

#include "Galaxy/Core/EntryPoint.h"

class ExampleLayer : public Galaxy::Layer
{
public:
	ExampleLayer() : Layer("Example"),
		m_CameraController(16.0f / 9.0f, true)
	{
		m_VertexArray = Galaxy::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f,-0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		};

		Galaxy::Ref<Galaxy::VertexBuffer> m_VertexBuffer;
		m_VertexBuffer = Galaxy::VertexBuffer::Create(vertices, sizeof(vertices));
		Galaxy::BufferLayout layout =
		{
			{"a_Position", Galaxy::ShaderDataType::Float3},
			{"a_Color", Galaxy::ShaderDataType::Float4},
		};

		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		unsigned int indices[3] = { 0,1,2 };
		Galaxy::Ref<Galaxy::IndexBuffer> m_IndexBuffer;
		m_IndexBuffer = Galaxy::IndexBuffer::Create(indices, 3);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		//SQUARE

		m_SquareVA = Galaxy::VertexArray::Create();

		float squareVertices[5 * 4] = {
		   -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		   -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		};

		Galaxy::Ref<Galaxy::VertexBuffer> squareVB;
		squareVB = Galaxy::VertexBuffer::Create(squareVertices, sizeof(squareVertices));

		squareVB->SetLayout({ 
			{"a_Position", Galaxy::ShaderDataType::Float3},
			{"a_TexCoord", Galaxy::ShaderDataType::Float2},
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned int squareIndices[6] = { 0,1,2, 2,3,0 };
		Galaxy::Ref<Galaxy::IndexBuffer> squareIB;
		squareIB = Galaxy::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_Model;
			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0f);
			}
		)";

		std::string fragSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = v_Color;
			}
	
		)";

		m_Shader = Galaxy::Shader::Create("TriangleShader", vertexSrc, fragSrc);

		std::string flatColorVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			uniform mat4 u_Model;
			uniform mat4 u_ViewProjection;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0f);
			}
		)";

		std::string flatColorFragSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0f);
			}
	
		)";

		m_FlatColorShader = Galaxy::Shader::Create("FlatColorShader", flatColorVertexSrc, flatColorFragSrc);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Galaxy::Texture2D::Create("assets/textures/Missing.png");
		m_Transparent = Galaxy::Texture2D::Create("assets/textures/Transparent.png");

		std::dynamic_pointer_cast<Galaxy::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Galaxy::OpenGLShader>(textureShader)->SetInt("u_Texture", 0);
	}

	void OnUpdate(Galaxy::Timestep ts) override
	{
		m_CameraController.OnUpdate(ts);

		GX_TRACE("Delta time {0}s, ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());

		Galaxy::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Galaxy::RenderCommand::Clear();

		Galaxy::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Galaxy::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Galaxy::OpenGLShader>(m_FlatColorShader)->SetFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; ++y)
		{
			for (int x = 0; x < 20; ++x)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Galaxy::Renderer::Submit(m_SquareVA, m_FlatColorShader, transform);
			}
		}
		
		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		Galaxy::Renderer::Submit(m_SquareVA, textureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_Transparent->Bind();
		Galaxy::Renderer::Submit(m_SquareVA, textureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		Galaxy::Renderer::EndScene();
	}

	void OnEvent(Galaxy::Event& event) override
	{
		m_CameraController.OnEvent(event);
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

private:
	Galaxy::ShaderLibrary m_ShaderLibrary;
	Galaxy::Ref<Galaxy::Shader> m_Shader;
	Galaxy::Ref<Galaxy::Shader> m_FlatColorShader;

	Galaxy::Ref<Galaxy::Texture2D> m_Texture, m_Transparent;

	Galaxy::Ref<Galaxy::VertexArray> m_VertexArray;
	Galaxy::Ref<Galaxy::VertexArray> m_SquareVA;

	Galaxy::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f,0.3f,0.8f };
};

class Sandbox : public Galaxy::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox() {}
};

Galaxy::Application* Galaxy::CreateApplication()
{
	return new Sandbox();
}