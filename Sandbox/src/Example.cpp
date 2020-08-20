#include <Galaxy.h>

#include "ImGui/imgui.h"

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

		std::shared_ptr<Galaxy::VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(Galaxy::VertexBuffer::Create(vertices, sizeof(vertices)));
		Galaxy::BufferLayout layout =
		{
			{"a_Position", Galaxy::ShaderDataType::Float3},
			{"a_Color", Galaxy::ShaderDataType::Float4},
		};

		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		unsigned int indices[3] = { 0,1,2 };
		std::shared_ptr<Galaxy::IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(Galaxy::IndexBuffer::Create(indices, 3));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		//SQUARE

		m_SquareVA.reset(Galaxy::VertexArray::Create());

		float squareVertices[3 * 4] = {
		   -0.75f, -0.75f, 0.0f,
			0.75f, -0.75f, 0.0f,
			0.75f,  0.75f, 0.0f,
		   -0.75f,  0.75f, 0.0f,
		};

		std::shared_ptr<Galaxy::VertexBuffer> squareVB;
		squareVB.reset(Galaxy::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({ {"a_Position", Galaxy::ShaderDataType::Float3} });
		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned int squareIndices[6] = { 0,1,2, 2,3,0 };
		std::shared_ptr<Galaxy::IndexBuffer> squareIB;
		squareIB.reset(Galaxy::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0f);
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

		m_Shader.reset(new Galaxy::Shader(vertexSrc, fragSrc));

		std::string blueVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			uniform mat4 u_ViewProjection;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0f);
			}
		)";

		std::string blueFragSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2,0.3,0.8,1.0);
			}
	
		)";

		m_BlueShader.reset(new Galaxy::Shader(blueVertexSrc, blueFragSrc));
	}

	void OnUpdate() override 
	{
		if (Galaxy::Input::IsKeyPressed(GX_KEY_LEFT))
			m_CameraPosition.x += m_CameraMoveSpeed;

		if (Galaxy::Input::IsKeyPressed(GX_KEY_RIGHT))
			m_CameraPosition.x -= m_CameraMoveSpeed;

		if (Galaxy::Input::IsKeyPressed(GX_KEY_UP))
			m_CameraPosition.y -= m_CameraMoveSpeed;

		if (Galaxy::Input::IsKeyPressed(GX_KEY_DOWN))
			m_CameraPosition.y += m_CameraMoveSpeed;

		if (Galaxy::Input::IsKeyPressed(GX_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed;
		
		if (Galaxy::Input::IsKeyPressed(GX_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed;


		Galaxy::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Galaxy::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Galaxy::Renderer::BeginScene(m_Camera);

		Galaxy::Renderer::Submit(m_SquareVA, m_BlueShader);

		Galaxy::Renderer::Submit(m_VertexArray, m_Shader);

		Galaxy::Renderer::EndScene();
	}

	void OnEvent(Galaxy::Event& event) override
	{

	}

	void OnImGuiRender() override
	{

	}

private:
	std::shared_ptr<Galaxy::Shader> m_Shader;
	std::shared_ptr<Galaxy::Shader> m_BlueShader;

	std::shared_ptr<Galaxy::VertexArray> m_VertexArray;
	std::shared_ptr<Galaxy::VertexArray> m_SquareVA;

	Galaxy::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation = 0;
	float m_CameraMoveSpeed = 0.1f;
	float m_CameraRotationSpeed = 2;
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