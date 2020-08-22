#include "gxpch.h"

#include "Galaxy/Input.h"
#include "Galaxy/Keycodes.h"

#include "OrthographicCameraController.h"

namespace Galaxy
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{	
	}
	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		if (Input::IsKeyPressed(GX_KEY_A))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;

		if (Input::IsKeyPressed(GX_KEY_D))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Input::IsKeyPressed(GX_KEY_W))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;

		if (Input::IsKeyPressed(GX_KEY_S))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(GX_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * ts;

			if (Input::IsKeyPressed(GX_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * ts;
		}

		m_CameraMoveSpeed = m_ZoomLevel * 1.5f;

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);
	}
	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(GX_BIND(OrthographicCameraController::OnMouseScrolledEvent));
		dispatcher.Dispatch<WindowResizeEvent>(GX_BIND(OrthographicCameraController::OnWindowResize));
	}
	bool OrthographicCameraController::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
	bool OrthographicCameraController::OnWindowResize(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
}