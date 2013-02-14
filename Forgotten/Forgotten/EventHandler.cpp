#include "EventHandler.h"

EventHandler* EventHandler::GetInstance(){
	if(m_instance == 0){
		m_instance = new EventHandler;
	}
	return m_instance;
}

EventHandler* EventHandler::m_instance = 0;

void EventHandler::AddEvent(ScriptEvent scriptEvent){
	m_eventQueue.push(scriptEvent);
}

void EventHandler::Remove(){
	m_eventQueue.pop();
}