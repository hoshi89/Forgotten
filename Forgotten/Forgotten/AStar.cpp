#include "AStar.h"

AStar::AStar(GenericMap &map)
	:m_goalFound(false), m_nodeMap(map)
{
}

void AStar::FindPath(){
	
	while(true){ // To process entire path
	// Process the path bit by bit to avoid lag
	//for(int i = 0; i < 100; i++){
		if(m_openList.empty() || PathComplete()){
			break;
		}else{
			ProcessPath();
		}
	}

}

void AStar::SetPath(sf::Vector2f start, sf::Vector2f goal){

	// Set start and goal
	m_start = start;
	m_goal = goal;

	// Clear current lists
	for(unsigned int i = 0; i < m_openList.size(); i++){
		delete m_openList[i];
	}
	m_openList.clear();

	for(unsigned int i = 0; i < m_closedList.size(); i++){
		delete m_closedList[i];
	}
	m_closedList.clear();

	m_path.clear();

	// Insert first value into the openList
	m_openList.push_back(new AStarNode(m_start, m_goal, 0));

	m_goalFound = false;

}

void AStar::ProcessPath(){

	// If the list is empty, there is no path so don't do anything
	if(m_openList.empty() || m_goalFound){
		return;
	}

	// Get the node with lowest F from the openList
	AStarNode *currentNode = GetNextNode();

	// Are we finished? Was the goal found?
	if(currentNode->GetPosition() == m_goal){
		// We're home! Fill the pathqueue

		AStarNode *getPath;

		for(getPath = currentNode; getPath != NULL; getPath = getPath->GetParent())
		{
			m_path.push_back(sf::Vector2f(getPath->GetPosition()));
		}

		// We don't want to target the starting node so delete it
		m_path.pop_back();

		m_goalFound = true;
		return;

	}else{
		// Not finished yet, continue the search

		// Get adjacent nodes to the currentNode
		std::vector<AStarNode> nodeAdjacent = currentNode->GetAdjacentNodes();

		// Process every adjacent node
		for(unsigned int i = 0; i < nodeAdjacent.size(); i++){
			ExamineNode(nodeAdjacent[i]);
		}
	}

}

void AStar::ExamineNode(AStarNode &node){

	// Check if node should be ignored, updated or pushed into openList
	
	// Is the node walkable?
	if(!(m_nodeMap.isWalkable(node.GetPosition().x, node.GetPosition().y))){
		return;
	}

	// Check the closedList
	for(unsigned int i = 0; i < m_closedList.size(); i++){
		if(m_closedList[i]->GetPosition() == node.GetPosition()){
			// Found in the closed list so abort operation
			return;
		}
	}

	// Check the openList
	for(unsigned int i = 0; i< m_openList.size(); i++){
		if(m_openList[i]->GetPosition() == node.GetPosition()){
			// Found in the openList, check values if it is to be updated
			if(m_openList[i]->GetG() > node.GetG()){
				// The G value will be shorter via the current node so update
				m_openList[i]->SetG(node.GetG());
				// Change the node to point to our current node
				m_openList[i]->SetParent(node.GetParent());
			}
			// It was found and the operation was complete
			return;
		}
	}

	// If it has come to this point the node was not found in the list so push it into the openList
	m_openList.push_back(new AStarNode(node));

}

bool AStar::PathComplete(){ return m_goalFound; }

AStarNode* AStar::GetNextNode(){

		// Set some default values to make search easy
		int lowest_F = 99999999;
		int nodeIndex = -1;
		AStarNode *nextNode = NULL;

		// Find node with the lowest value
		for(unsigned int i = 0; i < m_openList.size(); i++){

			if(m_openList[i]->GetF() < lowest_F){
				// Set new lowest F and index to keep track
				lowest_F = m_openList[i]->GetF();
				nodeIndex = i;
			}

		}

		// If a node was found in the openList, return the one with lowest F
		if(nodeIndex >= 0){
			nextNode = m_openList[nodeIndex];
			// Push it into the closedList
			m_closedList.push_back(nextNode);
			// Remove it from the openList
			m_openList.erase(m_openList.begin() + nodeIndex);
		}

		return nextNode;

}

std::vector<sf::Vector2f> AStar::GetPath(){ return m_path; }

sf::Vector2f& AStar::GetNextMove(){

	sf::Vector2f nextMove(m_goal.x, m_goal.y);

	if(!m_path.empty()){
		
		nextMove = m_path[m_path.size()-1];
		m_path.pop_back();

	}

	return nextMove;

}