#pragma once

#include "Galaxy/Core/Timestep.h"
#include "Galaxy/Renderer/OrthographicCamera.h"

#include "Galaxy/Events/Event.h"
#include "Galaxy/Events/ApplicationEvent.h"
#include "Galaxy/Events/MouseEvent.h"

namespace Galaxy
{
	struct OrthographicCameraBounds
	{
		float Left, Right;
		float Bottom, Top;

		float GetWidth() { return Right - Left; }
		float GetHeight() { return Top - Bottom; }
	};

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float apectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		inline float GetZoomLevel() { return m_ZoomLevel; }
		inline void SetZoomLevel(float level) { m_ZoomLevel = level; }

		const OrthographicCameraBounds& GetBounds() { return m_Bounds; }
	private:
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);


		bool m_Rotation;
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCameraBounds m_Bounds;
		OrthographicCamera m_Camera;


		glm::vec3 m_CameraPosition = { 0,0,0 };
		float m_CameraRotation = 0.0f;

		float m_CameraMoveSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
	};
}