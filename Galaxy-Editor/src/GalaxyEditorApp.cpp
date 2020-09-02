#include <Galaxy.h>
#include "Galaxy/Core/EntryPoint.h"

#include "EditorLayer.h"

namespace Galaxy
{
	class GalaxyEditor : public Application
	{
	public:
		GalaxyEditor()
			:Application("Galaxy Editor")
		{
			PushLayer(new EditorLayer());
		}

		~GalaxyEditor() {}
	};

	Application* CreateApplication()
	{
		return new GalaxyEditor();
	}
}