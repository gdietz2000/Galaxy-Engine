#include <Galaxy.h>

#include "Platform/OpenGl/OpenGLShader.h"

#include "ImGui/imgui.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class ExampleLayer : public Galaxy::Layer
{
public:
	ExampleLayer() : Layer("Example"),
		m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Galaxy::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f,-0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		};

		Galaxy::Ref<Galaxy::VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(Galaxy::VertexBuffer::Create(vertices, sizeof(vertices)));
		Galaxy::BufferLayout layout =
		{
			{"a_Position", Galaxy::ShaderDataType::Float3},
			{"a_Color", Galaxy::ShaderDataType::Float4},
		};

		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		unsigned int indices[3] = { 0,1,2 };
		Galaxy::Ref<Galaxy::IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(Galaxy::IndexBuffer::Create(indices, 3));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		//SQUARE

		m_SquareVA.reset(Galaxy::VertexArray::Create());

		float squareVertices[3 * 4] = {
		   -0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f,  0.5f, 0.0f,
		   -0.5f,  0.5f, 0.0f,
		};

		Galaxy::Ref<Galaxy::VertexBuffer> squareVB;
		squareVB.reset(Galaxy::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({ {"a_Position", Galaxy::ShaderDataType::Float3} });
		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned int squareIndices[6] = { 0,1,2, 2,3,0 };
		Galaxy::Ref<Galaxy::IndexBuffer> squareIB;
		squareIB.reset(Galaxy::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
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

		m_Shader.reset(Galaxy::Shader::Create(vertexSrc, fragSrc));

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

		m_FlatColorShader.reset(Galaxy::Shader::Create(flatColorVertexSrc, flatColorFragSrc));
	}

	void OnUpdate(Galaxy::Timestep ts) override 
	{
		GX_TRACE("Delta time {0}s, ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());

		if (Galaxy::Input::IsKeyPressed(GX_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;

		if (Galaxy::Input::IsKeyPressed(GX_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Galaxy::Input::IsKeyPressed(GX_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;

		if (Galaxy::Input::IsKeyPressed(GX_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Galaxy::Input::IsKeyPressed(GX_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		
		if (Galaxy::Input::IsKeyPressed(GX_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		Galaxy::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Galaxy::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Galaxy::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		glm::vec4 redColor(0.8, 0.2, 0.3f, 1.0f);
		glm::vec4 blueColor(0.3, 0.2, 0.8f, 1.0f);

		//Galaxy::MaterialRef material = new Galaxy::Material(m_FlatColorShader);

		std::dynamic_pointer_cast<Galaxy::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Galaxy::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; ++y)
		{
			for (int x = 0; x < 20; ++x)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Galaxy::Renderer::Submit(m_SquareVA, m_FlatColorShader, transform);
			}
		}
	
		Galaxy::Renderer::Submit(m_VertexArray, m_Shader);

		Galaxy::Renderer::EndScene();
	}

	void OnEvent(Galaxy::Event& event) override
	{

	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

private:
	Galaxy::Ref<Galaxy::Shader> m_Shader;
	Galaxy::Ref<Galaxy::Shader> m_FlatColorShader;

	Galaxy::Ref<Galaxy::VertexArray> m_VertexArray;
	Galaxy::Ref<Galaxy::VertexArray> m_SquareVA;

	Galaxy::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation = 0;
	float m_CameraMoveSpeed = 5.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_SquareColor = { 0.2f,0.3f,0.8f };
};

class Sandbox : public Galaxy::Application
{
public:
	Sandbox() 
	{ 
		PushLayer(new ExampleLayer());
	}

	~Sandbox(){}
};

Galaxy::Application* Galaxy::CreateApplication()
{
	return new Sandbox();
}