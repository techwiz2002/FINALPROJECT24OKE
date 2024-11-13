#include <iostream>
#include <fstream>
#include <string>
#include <memory> // For smart pointers

using namespace std;

// Structure representing each task in the list
struct Task {
    string description;
    unique_ptr<Task> next = nullptr; // Pointer to the next task
};

// Function to add a task
void addTask(unique_ptr<Task>& head, const string& description) {
    unique_ptr<Task> newTask(new Task()); // Direct allocation for compatibility
    newTask->description = description;
    newTask->next = move(head); // Insert new task at the beginning
    head = move(newTask);
}

// Recursive function to display tasks
void displayTasks(const unique_ptr<Task>& task, int index = 1) {
    if (!task) {
        if (index == 1)
            cout << "No tasks to display." << endl;
        return;
    }
    cout << index << ". " << task->description << endl;
    displayTasks(task->next, index + 1); // Recursive call to display next task
}

// Function to save tasks to a file
void saveTasks(const unique_ptr<Task>& task, ofstream& file) {
    if (!task) return;
    file << task->description << endl;
    saveTasks(task->next, file); // Recursive call to save the next task
}

// Function to load tasks from a file
void loadTasks(unique_ptr<Task>& head, ifstream& file) {
    string line;
    while (getline(file, line)) {
        addTask(head, line); // Adds each task from file to the list
    }
}

// Function to delete a task at a specific position
void deleteTask(unique_ptr<Task>& head, int position, int current = 1) {
    if (!head) {
        cout << "Position out of range." << endl;
        return;
    }
    if (position == current) {
        head = move(head->next); // Deletes the task at the current position
    } else {
        deleteTask(head->next, position, current + 1); // Recursive call to find position
    }
}

int main() {
    unique_ptr<Task> head = nullptr;
    int choice;
    string description;
    int position;

    // Load tasks from file on startup
    ifstream inputFile("tasks.txt");
    if (inputFile.is_open()) {
        loadTasks(head, inputFile);
        inputFile.close();
    }

    do {
        cout << "\nTo-Do List Menu:\n";
        cout << "1. Add Task\n2. View Tasks\n3. Delete Task\n4. Save and Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Ignore trailing newline

        switch (choice) {
            case 1:
                cout << "Enter task description: ";
                getline(cin, description);
                addTask(head, description);
                break;
            case 2:
                cout << "\nCurrent Tasks:\n";
                displayTasks(head);
                break;
            case 3:
                cout << "Enter task position to delete: ";
                cin >> position;
                deleteTask(head, position);
                break;
            case 4: {
                ofstream outputFile("tasks.txt");
                if (outputFile.is_open()) {
                    saveTasks(head, outputFile); // Save tasks to file recursively
                    outputFile.close();
                    cout << "Tasks saved. Exiting...\n";
                } else {
                    cout << "Error saving tasks to file.\n";
                }
                break;
            }
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
