#pragma once

#include "Glacier/Core/Core.h"

#include <string>
#include <functional>

namespace Glacier 
{
	// �̺�Ʈ Ÿ���� �����ϴ� enum class.
	// �� ���� �̺�Ʈ Ŭ������ �̸��� enum�� ���� ��� EVENT_CLASS_TYPE() ��ũ�θ� ���� ���� �̺�Ʈ Ŭ������ Ÿ���� �޾ƿ� �� ����.
	enum class EventType 
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled, MouseWheelUp, MouseWheelDown
	};

	// �̺�Ʈ�� ���͸� �ϱ� ���� �̺�Ʈ ī�װ� enum. Ư�� �̺�Ʈ�� �������� ���� �� ���.
	// ���� ���� �� ���� ���͸� �� �� �ֵ��� bit ���� ���.(bitflag)
	enum EventCategory 
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput =	   BIT(1),
		EventCategoryKeyboard =    BIT(2),
		EventCategoryMouse =       BIT(3),
		EventCategoryMouseButton = BIT(4)
	};
	// Event Ŭ������ ����ϴ� ��ü���� �̺�Ʈ Ŭ�������� �Լ� �κ��� ���ϰ� �ۼ��� �� �ֵ��� ��ũ�� �ۼ�.
	// #  : �޾ƿ� ��ũ�� ������ ���ڿ��� �ٲ���.
	// ## : �� ���� ��ū�� �ٿ���.
	// �̺�Ʈ Ÿ�Ը� �������� ���� Ŭ���� �ν��Ͻ��� �ʿ� ���� ������ static �Լ��� �������.
	// ���� �Լ��� GetEventType() �Լ��� �̿�, �������� ���� Event Ŭ���� ���� �ϳ��� ��� �̺�Ʈ �ν��Ͻ��� �̺�Ʈ Ÿ���� ������ �� �ֵ��� ��.
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
							   virtual EventType GetEventType() const override { return GetStaticType(); }\
							   virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	/*
		<Event>
		�̺�Ʈ�� ������ Ŭ����. Event Ŭ������ ��� �޾� �� ���� �̺�Ʈ���� ��Ÿ���� Ŭ������ ������.
	*/
	class GLACIER_API Event
	{
		// EventDispatcher Ŭ�������� ���� �����ϵ��� ������.
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		// �̺�Ʈ�� Ư�� ī�װ��� ���ϴ��� üũ�ϴ� �Լ�.
		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}

	public:
		// �̺�Ʈ�� ó���Ǿ����� �˷��ִ� ����.
		// ���� ���̾�� ���� ���̾�� �̺�Ʈ�� �� �̻� �����ϰ� ���� �ʴٸ�, �� ���� true�� ����� ���� ���̾ �̺�Ʈ�� �������� �ʵ��� ��.
		bool Handled = false;

	};

	/*
		<EventDispatcher>
		�� �̺�Ʈ Ÿ�Կ� �ش��ϴ� �̺�Ʈ�� �ݹ� �Լ��� �����ϴ� ������ �ϴ� Ŭ����.
	*/
	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>; // ���� Ÿ���� bool, ���ڰ� ���ø� ���� Ÿ���� �Լ� ��ü.
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		template<typename T>
		bool Dispatch(EventFn<T> eventCallbackFunc)
		{
			// m_Event�� Ÿ�԰� T::GetStaticType()�� Ÿ���� ��ġ�ϴ��� �˻�. 
			// ��, EventDispatcher�� ��� �ִ� �̺�Ʈ Ÿ�԰� Dispatch() ȣ��� �Բ� �Ѱ��� ���ø� Ÿ���� ��ġ�ϴ��� �˻�.
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				// m_Event ��ü�� T Ÿ������ ĳ�����ؼ� callback �Լ��� ���ڷ� ����, callback �Լ��� ȣ��.
				// ���� Ÿ������ �̺�Ʈ ó�� ���θ� bool Ÿ������ �޾Ƽ� m_Event�� ����.
				m_Event.Handled = eventCallbackFunc(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}