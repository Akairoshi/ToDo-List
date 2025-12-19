//Console UI only. TaskManager logic is separated in taskManager.*

#include "taskManager.h"
#include "SCF.h"
#include <iostream>

using std::cin;
using std::cout;
using std::string;

int main() {
    //safe input helper
    using scf::safeInput;
    
    //initialize taskManager
    taskManager manager;

    cout << "---- To do list ----\n";

    while (true) {
        cout << "tdl >> ";
        string cmd;
        std::getline(cin, cmd);

        //command dispatcher
        if (cmd == "add") {
            int id = manager.addTask(
                safeInput<string>("> Enter task description: ")
            );
            cout << "* Task added with ID " << id << "\n";
        }

        else if (cmd == "mark") {
            int id = safeInput<int>("> Enter task id: ");
            if (!manager.toggleTask(id))
                cout << "! Task not found\n";
        }

        else if (cmd == "remove") {
            int id = safeInput<int>("> Enter task id: ");
            if (!manager.removeTask(id))
                cout << "! Task not found\n";
        }

        else if (cmd == "list") {

            cout << "\n" << "---- Tasks ----" << "\n";

            auto tasks = manager.getTasks(taskManager::SortType::ByStatus);

            for (const auto& t : tasks) {
                cout << t.id << ": " << t.description << (t.isDone ? " [X]" : " [ ]") << "\n";
            }
            cout << "\n";
        }

        else if (cmd == "exit") break;
        else if (cmd == "help") cout << "? Availbale commands: add, mark, remove, list, help, exit" << "\n";

        else cout << "! Unknown command\n";
    }
}
