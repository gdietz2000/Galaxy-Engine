#pragma once

#include "Galaxy/Core/Log.h"

namespace Galaxy
{
	class GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}