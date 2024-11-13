This project is a basic to-do list application in C++ that lets users add, view, delete, and save tasks, making it a useful tool for managing simple to-do lists. It was created to help practice core C++ concepts, including pointers, recursion, and file handling. Tasks are stored in a linked list and saved to a file called tasks.txt so they’re available each time the program runs. Main features include adding a task by entering a description, viewing tasks with their positions, deleting tasks by specifying the position, and saving tasks on exit. The program uses smart pointers to manage memory, recursion to handle linked list operations, and file streams to keep tasks saved between sessions. To compile, use g++ -std=c++11 main.cpp -o todo, and to run, enter ./todo. The program starts with a simple menu, letting players pick options to manage tasks. Error handling is included to manage things like empty lists or invalid positions. Potential future improvements could include adding due dates, task priorities, or a GUI to make it easier to use.