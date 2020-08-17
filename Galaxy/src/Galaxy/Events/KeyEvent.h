#pragma once
#include "Event.h"

#include <sstream>

namespace Galaxy
{
	class GALAXY_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_Key; }

		EVENT_CLASS_CATEGORY(CategoryInput | CategoryKeyboard)
	protected:
		KeyEvent(int keycode)
			: m_Key(keycode) {}

		int m_Key;
	};

	class GALAXY_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_Key << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	class GALAXY_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_Key;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}