#include "SCF.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::unordered_map;
using std::vector;

// класс для управления задачами
class taskManager
{
private:
    int nextID{1};
    std::set<int> freeIDs;

    // получение доступного ID
    int getNextID()
    {
        int id;
        if (!freeIDs.empty())
        {
            id = *freeIDs.begin();
            freeIDs.erase(freeIDs.begin());
        }
        else
        {
            id = nextID++;
        }
        return id;
    }

public:
    // Структура задачи
    struct ToDoItem
    {
        int id{};
        string description{};
        bool isDone{};
    };

    // Добавление задачи
    void addTask(const string &descruption, vector<int> &order, unordered_map<int, ToDoItem> &toDoList)
    {
        int newID = getNextID();
        ToDoItem newItem{newID, descruption, false};
        toDoList[newID] = newItem;
        order.push_back(newID);
        cout << "* Task added" << "\n";
    }

    // Удаление задачи
    void removeTask(const int &ID, vector<int> &order, unordered_map<int, ToDoItem> &toDoList)
    {
        auto it = toDoList.find(ID);
        if (it == toDoList.end())
        {
            cout << "! Task with ID " << ID << " not found" << endl;
            return;
        }

        toDoList.erase(it);
        freeIDs.insert(ID);

        order.erase(std::remove(order.begin(), order.end(), ID), order.end());
        cout << "* Task " << ID << " removed" << endl;
    }

    // Отметка задачи как выполненая / не выполненая
    void markTask(const int &ID, vector<int> &order, unordered_map<int, ToDoItem> &toDoList)
    {
        auto it = toDoList.find(ID);

        if (it == toDoList.end())
        {
            cout << "! Task with ID " << ID << " not found" << endl;
            return;
        }

        auto &item = it->second;
        item.isDone = !item.isDone;
        cout << item.id << ": " << item.description << (item.isDone ? " [X]" : " []") << endl;
    }
    

    // Вывод списка задач
    void listTasks(vector<int> &order, unordered_map<int, ToDoItem> &toDoList)
    {
        std::sort(order.begin(), order.end());
        if (order.empty())
        {
            cout << "! To do list is empty" << endl;
            return;
        }
        cout << "\n" << "---- Task list ----" << "\n";
        for (int id : order)
        {
            const auto &item = toDoList.at(id);
            string status = item.isDone ? " [X]" : " []";
            cout << id << ": " << item.description << status << endl;
        }
        cout << endl;
    }
};

int main()
{
    using scf::safeInput;

    vector<int> order{};
    unordered_map<int, taskManager::ToDoItem> toDoList;

    // объявление менеджера задач
    taskManager manager;

    cout << "---- To do list ----" << "\n";
    cout << "Get command list - enter help" << "\n";
    while (true)
    {

        string operation{};
        cout << "tdl >> ";
        std::getline(cin, operation);

        if (operation == "add")
        {

            manager.addTask(safeInput<string>("> Enter task description: "), order, toDoList);
        }

        else if (operation == "mark")
        {
            manager.markTask(safeInput<int>("> Enter task id: "), order, toDoList);
        }
        else if (operation == "remove")
        {
            manager.removeTask(safeInput<int>("> Enter task id: "), order, toDoList);
        }
        else if (operation == "list")
        {
            manager.listTasks(order, toDoList);
        }
        else if (operation == "exit")
        {
            break;
        }
        else if (operation == "help")
        {
            cout << "? Availbale commands: add, mark, remove, list, help, exit" << "\n";
        }
        else
        {
            cout << "! Unknown operation" << "\n";
        }
    }
    cout << "---- To Do list closed ----" << "\n";
    return 0;
}