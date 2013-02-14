#ifndef INCLUDED_EVENTHANDLER
#define INCLUDED_EVENTHANDLER

#include <queue>
#include <iostream>

class EventHandler{
public:
	static EventHandler* GetInstance();
	void AddEvent(ScriptEvent scriptEvent);
	void Remove();
private:
	EventHandler(){};
	EventHandler(EventHandler const&){};
	EventHandler& operator=(EventHandler const&){};
	static EventHandler* m_instance;
	typedef std::queue<ScriptEvent>EventQueue;
	EventQueue m_eventQueue;
};

#endif