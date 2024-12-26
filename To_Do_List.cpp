#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Task
{
    string description;
    bool completed;

    Task(string desc) : description(desc), completed(false) {}
};

void displayMenu();
void addTask(vector<Task> &tasks);
void viewTasks(const vector<Task> &tasks);
void markTaskCompleted(vector<Task> &tasks);
void removeTask(vector<Task> &tasks);

int main()
{
    vector<Task> tasks;
    int choice;

    cout << "Welcome to the Console-Based To-Do List Manager!" << endl;

    do
    {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        cin.ignore();

        switch (choice)
        {
        case 1:
            addTask(tasks);
            break;
        case 2:
            viewTasks(tasks);
            break;
        case 3:
            markTaskCompleted(tasks);
            break;
        case 4:
            removeTask(tasks);
            break;
        case 5:
            cout << "Exiting the program. Have a productive day!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}

void displayMenu()
{
    cout << "\n===== To-Do List Menu =====" << endl;
    cout << "1. Add Task" << endl;
    cout << "2. View Tasks" << endl;
    cout << "3. Mark Task as Completed" << endl;
    cout << "4. Remove Task" << endl;
    cout << "5. Exit" << endl;
}

void addTask(vector<Task> &tasks)
{
    string taskDescription;
    cout << "Enter the task description: ";
    getline(cin, taskDescription);

    tasks.push_back(Task(taskDescription));
    cout << "Task added successfully!" << endl;
}

void viewTasks(const vector<Task> &tasks)
{
    if (tasks.empty())
    {
        cout << "No tasks available. Add some tasks first!" << endl;
        return;
    }

    cout << "\n===== To-Do List =====" << endl;
    for (size_t i = 0; i < tasks.size(); ++i)
    {
        cout << i + 1 << ". [" << (tasks[i].completed ? "Completed" : "Pending") << "] "
             << tasks[i].description << endl;
    }
}

void markTaskCompleted(vector<Task> &tasks)
{
    if (tasks.empty())
    {
        cout << "No tasks to mark as completed. Add tasks first!" << endl;
        return;
    }

    int taskNumber;
    viewTasks(tasks);
    cout << "Enter the task number to mark as completed: ";
    cin >> taskNumber;

    if (taskNumber >= 1 && taskNumber <= tasks.size())
    {
        tasks[taskNumber - 1].completed = true;
        cout << "Task marked as completed!" << endl;
    }
    else
    {
        cout << "Invalid task number. Please try again." << endl;
    }
}

void removeTask(vector<Task> &tasks)
{
    if (tasks.empty())
    {
        cout << "No tasks to remove. Add tasks first!" << endl;
        return;
    }

    int taskNumber;
    viewTasks(tasks);
    cout << "Enter the task number to remove: ";
    cin >> taskNumber;

    if (taskNumber >= 1 && taskNumber <= tasks.size())
    {
        tasks.erase(tasks.begin() + (taskNumber - 1));
        cout << "Task removed successfully!" << endl;
    }
    else
    {
        cout << "Invalid task number. Please try again." << endl;
    }
}
