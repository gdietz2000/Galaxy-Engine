#pragma once

#include "Galaxy/Log.h"

namespace Galaxy
{
	class GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}