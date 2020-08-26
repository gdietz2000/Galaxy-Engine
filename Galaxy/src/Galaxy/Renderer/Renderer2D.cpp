#include "gxpch.h"
#include "Renderer2D.h"

#include "RenderCommand.h"

#include "VertexArray.h"
#include "Shader.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Galaxy
{
	struct Renderer2DStorage
	{
		Ref<VertexArray> m_VertexArray;
		Ref<Shader> m_TextureShader;
		Ref<Texture> m_WhiteTexture;
	};

	static Renderer2DStorage* s_Data;

	void Renderer2D::Init()
	{
		s_Data = new Renderer2DStorage();

		s_Data->m_VertexArray = VertexArray::Create();

		float squareVertices[5 * 4] = {
			   -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
				0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
				0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			   -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		};

		Ref<VertexBuffer> m_VertexBuffer = VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		m_VertexBuffer->SetLayout({ { "a_Position", ShaderDataType::Float3 }, { "a_TexCoord", ShaderDataType::Float2 }, });

		s_Data->m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		unsigned int squareIndices[6] = { 0,1,2, 2,3,0 };
		Ref<IndexBuffer> m_IndexBuffer = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));

		s_Data->m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		s_Data->m_WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTexturedata = 0xffffffff;
		s_Data->m_WhiteTexture->SetData(&whiteTexturedata, sizeof(uint32_t));


		s_Data->m_TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		s_Data->m_TextureShader->Bind();
		s_Data->m_TextureShader->SetInt("u_Texture", 0);
	}
	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}
	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_Data->m_TextureShader->Bind();
		s_Data->m_TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}
	void Renderer2D::EndScene()
	{

	}
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		s_Data->m_TextureShader->SetFloat4("u_Color", color);
		//Bind White Texture here
		s_Data->m_WhiteTexture->Bind();


		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * //Add rotation here
			glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

		s_Data->m_TextureShader->SetMat4("u_Model", transform);

		s_Data->m_VertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->m_VertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		s_Data->m_TextureShader->SetFloat4("u_Color", glm::vec4(1.0f));
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * //Add rotation here
			glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

		s_Data->m_TextureShader->SetMat4("u_Model", transform);

		s_Data->m_VertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->m_VertexArray);
	}
}