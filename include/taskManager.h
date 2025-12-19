//taskManager public interface (logic only, no UI)

#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <set>

class taskManager {
public:

    //task item structure
    struct ToDoItem {
        int id;
        std::string description;
        bool isDone;
    };

        enum class SortType {
        ByID,
        ByStatus,
        ByCreation
    };

    //task management API
    int addTask(const std::string& description);
    bool removeTask(int id);
    bool toggleTask(int id);

    std::vector<ToDoItem> getTasks(SortType type) const;

private:

    //get available ID for task
    int getNextID();
    int nextID{1};
    std::set<int> freeIDs;

    std::unordered_map<int, ToDoItem> toDoList;
    std::vector<int> order;
};
