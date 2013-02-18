#ifndef INCLUDED_SCRIPTMANAGER
#define INCLUDED_SCRIPTMANAGER

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class ScriptManager{
public:
	static ScriptManager* GetInstance();
	void LoadScript(std::string filename);
private:
	ScriptManager(){};
	ScriptManager(ScriptManager const&){};
	ScriptManager& operator=(ScriptManager const&){};
	static ScriptManager *m_instance;
	int ConvertFromString(const std::string &str);
};

#endif