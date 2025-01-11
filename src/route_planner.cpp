#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
    // Convert inputs to percentage:
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

    start_node = &(m_Model.FindClosestNode(start_x, start_y));
    end_node = &(m_Model.FindClosestNode(end_x, end_y));
}


// TODO 3: Implement the CalculateHValue method.
// Tips:
// - You can use the distance to the end_node for the h value.
// - Node objects have a distance method to determine the distance to another node.

float RoutePlanner::CalculateHValue(const RouteModel::Node *node) {
    return std::sqrt(std::pow((x - other.x), 2) + std::pow((y - other.y), 2));
}


// TODO 4: Complete the AddNeighbors method to expand the current node by adding all unvisited neighbors to the open list.
// Tips:
// - Use the FindNeighbors() method of the current_node to populate current_node.neighbors vector with all the neighbors.
// - For each node in current_node.neighbors, set the parent, the h_value, the g_value. 
// - Use CalculateHValue below to implement the h-Value calculation.
// - For each node in current_node.neighbors, add the neighbor to open_list and set the node's visited attribute to true.

void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {
    // Collecting the neighbours
    current_node->FindNeighbors();
    
    for(auto neighbor: current_node->neighbors) {
        neighbor->parent = current_node;
        neighbor->g_value += current_node->g_value + current_node->distance(*neighbor);
        neighbor->h_value = this->CalculateHValue(neighbor);
        neighbor->visited = true;
        this->open_list.push_back(neighbor);
    }
}


// TODO 5: Complete the NextNode method to sort the open list and return the next node.
// Tips:
// - Sort the open_list according to the sum of the h value and g value.
// - Create a pointer to the node in the list with the lowest sum.
// - Remove that node from the open_list.
// - Return the pointer.

RouteModel::Node *RoutePlanner::NextNode() {
    sort(this->open_list.begin(),
         this->open_list.end(),
         [](const RouteModel::Node* a, const RouteModel::Node* b){ return a->g_value + a->h_value > b->g_value + b->h_value;});
    RouteModel::Node* next = this->open_list.back();
    this->open_list.pop_back();
    return next;
}


// TODO 6: Complete the ConstructFinalPath method to return the final path found from your A* search.
// Tips:
// - This method should take the current (final) node as an argument and iteratively follow the 
//   chain of parents of nodes until the starting node is found.
// - For each node in the chain, add the distance from the node to its parent to the distance variable.
// - The returned vector should be in the correct order: the start node should be the first element
//   of the vector, the end node should be the last element.

std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
    // Create path_found vector
    distance = current_node->g_value;
    std::vector<RouteModel::Node> path_found;
    auto cur_node = current_node;

    while(true) {
        path_found.push_back(*cur_node);
        if(cur_node == this->start_node)
            break;
        cur_node = cur_node->parent;
    }
    
    // Reversing so that the start_node was at the beginning of the vector
    reverse(path_found.begin(), path_found.end());
    std::cout << "path_found length: " << path_found.size() << std::endl;

    // Multiply the distance by the scale of the map to get meters.
    distance *= m_Model.MetricScale();
    return path_found;
}


// TODO 7: Write the A* Search algorithm here.
// Tips:
// - Use the AddNeighbors method to add all of the neighbors of the current node to the open_list.
// - Use the NextNode() method to sort the open_list and return the next node.
// - When the search has reached the end_node, use the ConstructFinalPath method to return the final path that was found.
// - Store the final path in the m_Model.path attribute before the method exits. This path will then be displayed on the map tile.

void RoutePlanner::AStarSearch() {
    RouteModel::Node *current_node = nullptr;
    this->open_list.push_back(this->start_node);
    this->start_node->visited = true;
    
    while(open_list.size() > 0) {
        current_node = this->NextNode();
        if(current_node == this->end_node) {
            this->m_Model.path = this->ConstructFinalPath(current_node);
            return;
        }
        this->AddNeighbors(current_node);
    }
}