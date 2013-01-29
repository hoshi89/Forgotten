#ifndef INCLUDED_ASTARNODE
#define INCLUDED_ASTARNODE

#define DIAGONAL_MOVE 14
#define STRAIGHT_MOVE 10

#include <vector>
#include <SFML/Graphics.hpp>

class AStarNode{
public:
	AStarNode(sf::Vector2f position, sf::Vector2f goal, int moveCost, AStarNode *parent=NULL);
	int GetG();
	int GetH();
	int GetF();
	int GetMoveCost();
	AStarNode* GetParent();
	sf::Vector2f GetPosition();
	void SetG(int g);
	void SetH(int h);
	void SetParent(AStarNode *parent);
	std::vector<AStarNode> GetAdjacentNodes();
private:
	int m_G;
	int m_H;
	int m_moveCost;
	sf::Vector2f m_position;
	sf::Vector2f m_goal;
	AStarNode *m_parent;

	int ManhattanDistance(sf::Vector2f start, sf::Vector2f goal);
	
};

#endif