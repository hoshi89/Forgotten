#ifndef INCLUDED_FLAGMANAGER
#define INCLUDED_FLAGMANAGER

#include <vector>

class FlagManager{
public:
	static FlagManager* GetInstance();
	void CreateFlag(std::string flagname);
	void DeleteFlag(std::string flagname);
	bool IsFlagSet(std::string flagname);
private:
	FlagManager();
	FlagManager(FlagManager const&){};
	FlagManager& operator=(FlagManager const&){};
	static FlagManager* m_instance;
	std::vector<std::string> m_flags;
};

#endif