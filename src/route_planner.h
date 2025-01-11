#ifndef ROUTE_PLANNER_H
#define ROUTE_PLANNER_H

#include <iostream>
#include <vector>
#include <string>

#include "SDL.h"


class Node {
  public:
    float h_value = std::numeric_limits<float>::max();
    float g_value = 0.0;
    bool visited = false;
    std::vector<Node *> neighbors;

    Node();
    void FindNeighbors();
    float distance(Node other) const {
        return std::sqrt(std::pow((x - other.x), 2) + std::pow((y - other.y), 2));
    }

    Node(){}
    Node(int idx, RouteModel * search_model, Model::Node node) : Model::Node(node), parent_model(search_model), index(idx) {}

  private:
    int x;
    int y;
    int index;
    Node * FindNeighbor(std::vector<int> node_indices);
    RouteModel * parent_model = nullptr;
};


class RoutePlanner {
  public:
    RoutePlanner(std::vector<SDL_Point> bot_snake, float bot_snake_speed, std::vector<SDL_Point> user_snake, int end_x, int end_y);
    void AStarSearch();

    // The following methods have been made public so we can test them individually.
    void AddNeighbors(RouteModel::Node *current_node);
    float CalculateHValue(int end_x, int end_y);
    RouteModel::Node *NextNode();

  private:
    // Add private variables or methods declarations here.
    std::vector<RouteModel::Node*> open_list;
    RouteModel::Node *start_node;
    RouteModel::Node *end_node;

    float distance = 0.0f;
    RouteModel &m_Model;
};

#endif