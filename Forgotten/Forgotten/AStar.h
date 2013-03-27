#ifndef INCLUDED_ASTAR
#define INCLUDED_ASTAR

#include "AStarNode.h"
#include "GenericMap.h"

class AStar{
public:
	AStar(GenericMap &map);
	void SetPath(sf::Vector2f start, sf::Vector2f goal);
	void FindPath();
	void ProcessPath();
	
	void ExamineNode(AStarNode &node);
	bool PathComplete();
	std::vector<sf::Vector2f> GetPath();
	sf::Vector2f& GetNextMove();

private:
	GenericMap &m_nodeMap;
	sf::Vector2f m_start;
	sf::Vector2f m_goal;
	std::vector<sf::Vector2f> m_path;
	std::vector<AStarNode*> m_openList;
	std::vector<AStarNode*> m_closedList;
	bool m_goalFound;
	bool m_initialized;

	AStarNode* GetNextNode();
};

#endif