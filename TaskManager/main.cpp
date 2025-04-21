#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct Task {
    string description;
    int priority;

    Task(string desc, int prio) : description(desc), priority(prio) {}

    bool operator<(const Task& other) const {
        return priority < other.priority;
    }
};

class TaskManager {
private:
    priority_queue<Task> taskQueue;

public:
    void addTask(const string& description, int priority) {
        taskQueue.push(Task(description, priority));
        cout << "Task added: " << description << " with priority " << priority << endl;
    }

    void executeTask() {
        if (!taskQueue.empty()) {
            Task task = taskQueue.top();
            taskQueue.pop();
            cout << "Task completed: " << task.description << " with priority " << task.priority << endl;
        }
        else {
            cout << "There are no tasks to complete!" << endl;
        }
    }

    void showTasks() {
        if (taskQueue.empty()) {
            cout << "No tasks in the queue!" << endl;
            return;
        }

        priority_queue<Task> tempQueue = taskQueue;
        cout << "Tasks in the queue:" << endl;
        while (!tempQueue.empty()) {
            Task task = tempQueue.top();
            cout << "Task: " << task.description << ", Priority: " << task.priority << endl;
            tempQueue.pop();
        }
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "No existing task file found. Starting fresh." << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string desc;
            int prio;
            ss >> desc >> prio;
            if (!desc.empty()) {
                taskQueue.push(Task(desc, prio));
            }
        }

        file.close();
    }

    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Error saving tasks to file." << endl;
            return;
        }

        priority_queue<Task> tempQueue = taskQueue;
        while (!tempQueue.empty()) {
            Task task = tempQueue.top();
            file << task.description << " " << task.priority << endl;
            tempQueue.pop();
        }

        file.close();
    }
};

int main() {
    TaskManager manager;
    string tasks = "tasks.txt";

    manager.loadFromFile(tasks);

    int choice;
    do {
        cout << "\n--- Task Manager ---\n";
        cout << "1. Add task\n";
        cout << "2. Execute task\n";
        cout << "3. Show all tasks\n";
        cout << "4. Save to file\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string description;
            int priority;
            cout << "Enter task description (1 word): ";
            cin >> description;
            cout << "Enter task priority: ";
            cin >> priority;
            manager.addTask(description, priority);
            break;
        }
        case 2:
            manager.executeTask();
            break;

        case 3:
            manager.showTasks();
            break;

        case 4:
            manager.saveToFile(tasks);
            cout << "Tasks saved to file." << endl;
            break;

        case 0:
            cout << "Goodbye!" << endl;
            break;

        default:
            cout << "Invalid choice. Try again." << endl;
            break;
        }

    } while (choice != 0);


    return 0;
}
