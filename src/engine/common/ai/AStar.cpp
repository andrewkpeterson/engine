#include "AStar.h"

AStar::AStar(std::shared_ptr<MapSegment> segment) :
    m_segment(segment)
{

}

AStar::~AStar()
{

}

std::vector<std::pair<int, int>> AStar::AStarAlgorithm(std::shared_ptr<AStarState> start, std::shared_ptr<AStarState> goal) {
    std::set<std::shared_ptr<AStarState>, StateComparator> open_set;
    std::map<std::pair<int, int>, std::shared_ptr<AStarState>> pair2state;
    start->gcost = 0.0f;
    start->fcost = float(std::sqrt(std::pow(start->x - goal->x, 2) + std::pow(start->z - goal->z, 2)));
    open_set.insert(start);
    pair2state[std::pair<int, int>(start->x, start->z)] = start;
    std::map<std::pair<int, int>, std::pair<int, int>> came_from;

    while (open_set.size() > 0) {
        std::shared_ptr<AStarState> current = *open_set.begin();
        if (current->x == goal->x && current->z == goal->z) {
            return reconstructPath(std::pair<int, int>(current->x, current->z), came_from);
        }

        open_set.erase(current);
        std::vector<std::pair<int, int>> neighbors = getNeighbors(current);
        for (int i = 0; i < neighbors.size(); i++) {
            std::pair<int, int> n_pair = neighbors[i];
            float tentative_gcost = current->gcost + 1;
            bool visited = pair2state.find(n_pair) != pair2state.end();
            std::shared_ptr<AStarState> n_ptr;
            if (visited) {
                n_ptr = pair2state[n_pair];
            } else {
                n_ptr = std::make_shared<AStarState>();
                n_ptr->x = n_pair.first;
                n_ptr->z = n_pair.second;
            }
            if (!visited || tentative_gcost < n_ptr->gcost) {
                came_from[std::pair<int, int>(n_ptr->x, n_ptr->z)] = std::pair<int, int>(current->x, current->z);
                n_ptr->gcost = tentative_gcost;
                n_ptr->fcost = tentative_gcost + float(std::sqrt(std::pow(n_ptr->x - goal->x, 2) + std::pow(n_ptr->z - goal->z, 2)));
                open_set.insert(n_ptr);
            }
        }
    }


    // return failure
    return std::vector<std::pair<int, int>>({});
}

std::vector<std::pair<int, int>> AStar::getNeighbors(std::shared_ptr<AStarState> node) {
    std::vector<std::pair<int, int>> retvec;
    if (m_segment->data[(node->x + 1) * MapGenerator::MAP_WIDTH + node->z] == MapElement::OPEN) {
        retvec.push_back(std::pair<int, int>(node->x + 1, node->z));
    }
    if (m_segment->data[(node->x - 1) * MapGenerator::MAP_WIDTH + node->z] == MapElement::OPEN) {
        retvec.push_back(std::pair<int, int>(node->x - 1, node->z));
    }
    if (m_segment->data[(node->x) * MapGenerator::MAP_WIDTH + node->z + 1] == MapElement::OPEN) {
        retvec.push_back(std::pair<int, int>(node->x, node->z + 1));
    }
    if (m_segment->data[(node->x) * MapGenerator::MAP_WIDTH + node->z - 1] == MapElement::OPEN) {
        retvec.push_back(std::pair<int, int>(node->x, node->z - 1));
    }

    return retvec;
}

std::vector<std::pair<int, int>> AStar::reconstructPath(std::pair<int, int> current,
                                                        std::map<std::pair<int, int>, std::pair<int, int>> &came_from) {
    std::vector<std::pair<int, int>> path;
    path.insert(path.begin(), current);
    auto it = came_from.begin();
    while (it != came_from.end()) {
        current = came_from[current];
        path.insert(path.begin(), current);
        it++;
    }

    return path;
}