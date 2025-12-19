//TaskManager logic (no UI)

#include "taskManager.h"
#include <algorithm>

//get available ID for task
int taskManager::getNextID() {
    if (!freeIDs.empty()) {
        int id = *freeIDs.begin();
        freeIDs.erase(freeIDs.begin());
        return id;
    }
    return nextID++;
}

//add task to storage and creation order
int taskManager::addTask(const std::string& description) {
    int id = getNextID();
    toDoList[id] = {id, description, false};
    order.push_back(id);
    return id;
}

//remove task to storage and creation order
bool taskManager::removeTask(int id) {
    if (!toDoList.contains(id)) return false;

    toDoList.erase(id);
    freeIDs.insert(id);
    order.erase(std::remove(order.begin(), order.end(), id), order.end());
    return true;
}

//mark task done / not done
bool taskManager::toggleTask(int id) {
    auto it = toDoList.find(id);
    if (it == toDoList.end()) return false;

    it->second.isDone = !it->second.isDone;
    return true;
}

// return tasks sorted according to selected strategy
std::vector<taskManager::ToDoItem> taskManager::getTasks(SortType type) const {
    std::vector<ToDoItem> result;

    for (const auto& [id, item] : toDoList)
        result.push_back(item);

    switch (type) {
        case SortType::ByID:
            std::sort(result.begin(), result.end(),
                [](const ToDoItem& a, const ToDoItem& b) {
                    return a.id < b.id;
                });
            break;

        case SortType::ByStatus:
            std::sort(result.begin(), result.end(),
                [](const ToDoItem& a, const ToDoItem& b) {
                    return a.isDone < b.isDone;
                });
            break;

        case SortType::ByCreation:
            result.clear();
            for (int id : order)
                result.push_back(toDoList.at(id));
            break;
    }

    return result;
}
