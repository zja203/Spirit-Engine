#pragma once

#include "Spirit/core/base.hpp"
#include <string>
#include <functional>

namespace Spirit {
	// Events in Spirit are currently blocking, meaning when an event occurs it
	// immediately gets dispatched and must be dealt with right then an there.
	// For the future, a better strategy might be to buffer events in an event
	// bus and process them during the "event" part of the update stage.

	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved
	};

	enum EventCategory {
		None = 0,
		EventCategoryApplication    = BIT(0)
	};
#define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::type; }\
	virtual EventType getEventType() const override { return getStaticType(); }\
	virtual const char* getName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }

	class Event {
		public:
			bool Handled = false;
			virtual EventType getEventType() const = 0;
			virtual const char* getName() const = 0;
			virtual int getCategoryFlags() const = 0;
			virtual std::string toString() const { return getName(); }

			inline bool isInCategory(EventCategory category) {
				return getCategoryFlags() & category;
			}
	};

	class EventDispatcher {
		template<typename T>
			using EventFn = std::function<bool(T&)>;
		public:
		EventDispatcher(Event& event) : m_Event(event) { }

		template<typename T>
			bool Dispatch(EventFn<T> func) {
				if (m_Event.getEventType() == T::getStaticType()) {
					m_Event.Handled = func(*(T*)&m_Event);
					return true;
				}
				return false;
			}
		private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os << e.toString();
	}
}
