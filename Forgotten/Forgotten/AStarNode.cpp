#include "AStarNode.h"

AStarNode::AStarNode(sf::Vector2f position, sf::Vector2f goal, int moveCost, AStarNode *parent)
	:m_position(position), m_goal(goal), m_parent(parent), m_moveCost(moveCost)
{
	// Set G value
	if(m_parent){
		m_G = m_parent->GetG()+moveCost;
	}else{
		m_G = moveCost;
	}

	// Set H value
	m_H = ManhattanDistance(m_position, m_goal);

}

int AStarNode::GetG(){ return m_G; }

int AStarNode::GetH(){ return m_H; }

int AStarNode::GetF() { return m_H + m_G; }

int AStarNode::GetMoveCost(){ return m_moveCost; }

AStarNode* AStarNode::GetParent(){ return m_parent; }

sf::Vector2f AStarNode::GetPosition(){ return m_position; }

void AStarNode::SetG(int g){ m_G = g; }

void AStarNode::SetH(int h){ m_H = h; }

void AStarNode::SetParent(AStarNode *parent){ m_parent = parent; }

int AStarNode::ManhattanDistance(sf::Vector2f start, sf::Vector2f goal)
{
	// Estimate distance to goal by adding X and Y coordinates
	int x_diff = (int)(abs((int)(start.x-goal.x)));
	int y_diff = (int)(abs((int)(start.y-goal.y)));

	// Multiply by straight move as of Manhattan distance 
	return STRAIGHT_MOVE*(x_diff+y_diff);
}

std::vector<AStarNode> AStarNode::GetAdjacentNodes()
{
	std::vector<AStarNode> tmpVector;

	// Straight neighbors
	const AStarNode UP(sf::Vector2f(m_position.x, m_position.y-1), m_goal, STRAIGHT_MOVE, this);
	const AStarNode RIGHT(sf::Vector2f(m_position.x+1, m_position.y), m_goal, STRAIGHT_MOVE, this);
	const AStarNode DOWN(sf::Vector2f(m_position.x, m_position.y+1), m_goal, STRAIGHT_MOVE, this);
	const AStarNode LEFT(sf::Vector2f(m_position.x-1, m_position.y), m_goal, STRAIGHT_MOVE, this);

	// Diagonal neighbors
	const AStarNode UP_LEFT(sf::Vector2f(m_position.x-1, m_position.y-1), m_goal, DIAGONAL_MOVE, this);
	const AStarNode UP_RIGHT(sf::Vector2f(m_position.x+1, m_position.y-1), m_goal, DIAGONAL_MOVE, this);
	const AStarNode DOWN_LEFT(sf::Vector2f(m_position.x-1, m_position.y+1), m_goal, DIAGONAL_MOVE, this);
	const AStarNode DOWN_RIGHT(sf::Vector2f(m_position.x+1, m_position.y+1), m_goal, DIAGONAL_MOVE, this);

	tmpVector.push_back(UP);
	tmpVector.push_back(RIGHT);
	tmpVector.push_back(DOWN);
	tmpVector.push_back(LEFT);

	tmpVector.push_back(UP_LEFT);
	tmpVector.push_back(UP_RIGHT);
	tmpVector.push_back(DOWN_LEFT);
	tmpVector.push_back(DOWN_RIGHT);

	return tmpVector;

}