
#include <bits/stdc++.h>

const char *menu =
    "Welcome to your task manager, here is a list of operations you can do:\n"
    "  - To insert in your list: insert | num of elements\n"
    "  - To remove a task by ID: deleteID | ID\n"
    "  - To search for a task: search | ID\n"
    "  - To remove all tasks with a certain priority: DeletePrio | priority\n"
    "  - To display all tasks ordered: exhibit\n"
    "  - To exit menu: exit\n";

struct task {
  int ID = 0;
  std::string description = "";
  int priority = 3; // default last priority
};
struct Node {
  task tasks;
  Node *prev;
  Node *next;
};

Node *build(int id, std::string descript, int priority) { // single node builder
  Node *newNode = new Node();
  newNode->tasks.ID = id;
  newNode->tasks.description = descript;
  newNode->tasks.priority = priority;
  newNode->next = nullptr;
  newNode->prev = nullptr;
  return newNode;
}

void insert(Node *&head, int id, std::string descript, int priority) { // inserts a new node on the list
  Node *newnode = build(id, descript, priority);
  if (head ==
      nullptr) { // if the current node is the first it is null, so just use it
    head = newnode;
    return;
  }

  Node *current = head;
  while (current->next != nullptr) { // if not, we will go to the end of the
                                     // list to insert the new node
    current = current->next;
  }
  // this part is just to fix the next and current nodes in the lines
  current->next = newnode;
  newnode->prev = current;
}

Node *sortnodesID(Node *start) { // sorts nodes based on priority
  if (start == nullptr) {
    std::cout << "there are no elements to exhibit\n";
    return start;
  }
  Node *correct = nullptr; // we are going to create the sorted list now

  while (start) {
    Node *current = start;
    start = start->next;
    if (correct == nullptr ||
        current->tasks.priority <
            correct->tasks
                .priority) { // if its the start or its going in the start
      current->next = correct;
      correct = current;
    } else {
      Node *temp = correct;
      while (temp->next &&
             temp->next->tasks.priority < current->tasks.priority) {
        temp = temp->next;
      }
      // when we get to the element we want to swap we just swap it
      current->next = temp->next;
      temp->next = current;
    }
  }
  return correct;
}
Node *findID(Node *start, int id) { // returns a node based on given id
  Node *current = start;
  while (current != nullptr) {
    if (current->tasks.ID == id) {
      return current; // Found the node
    }
    current = current->next;
  }
  return nullptr; // Not found
}
void printID(Node *start, int id) {
  Node *print = findID(start, id);
  if (print == nullptr) {
    std::cout << "task was not found";
    return;
  }

  std::cout << "task ID: " << print->tasks.ID << "\n"
            << "task description: " << print->tasks.description << "\n"
            << "task priority: " << print->tasks.priority;
}
void removeID(Node *&start, int id) { // removes a node based on its id
  Node *dead = findID(start, id); // dead because its going to be deleted
  if (dead == nullptr) {
    std::cout << "task was not found :(";
    return;
  }
  if (start == dead) { // first node
    Node *temp = start;
    start = start->next;
    delete temp;
    return;
  }

  Node *prev = start;
  while (prev->next != nullptr && prev->next != dead) {
    prev = prev->next;
  }

  if (prev->next == dead) {
    prev->next = dead->next;
    delete dead;
  }
}

void printList(Node *start) { // prints the entire sorted list
  Node *current = sortnodesID(start);
  while (current != nullptr) { // traverse all the nodes to print them all
    std::cout << std::string(30, '=') << std::endl;

    std::cout << "ID: " << current->tasks.ID << std::endl;
    std::cout << "description: " << current->tasks.description << std::endl;
    std::cout << "priority: " << current->tasks.priority << std::endl;

    current = current->next;
  }
  std::cout << std::string(30, '=') << std::endl;
}

void removePriority(Node *&start, int priority) { // removes nodes based on given priority
  Node *current = start;

  while (current != nullptr) {
    if (current->tasks.priority == priority) {
      removeID(*&start, current->tasks.ID);
    }

    current = current->next;
  }
}

bool checkID(Node *&head, int id) { // checks if the id is already taken
  if (findID(head, id) != nullptr) {
    return true;
  } else {
    return false;
  }
}

bool checkInterval(int num) { // checks if a int x is 1 < x < 3
  if (num < 1 || num > 3) {
    return true;
  } else {
    return false;
  }
}

int main() {
  // welcoming ascii art text
  std::cout << "  _       _____ ______             _____ _                 _   "
               "    _             \n"
            << " | |     / ____|  ____|           / ____(_)               | |  "
               "   | |            \n"
            << " | |    | (___ | |__     ______  | (___  _ _ __ ___  _   _| | "
               "__ _| |_ ___  _ __ \n"
            << " | |     \\___ \\|  __|   |______|  \\___ \\| | '_ ` _ \\| | | "
               "| |/ _` | __/ _ \\| '__|\n"
            << " | |____ ____) | |____            ____) | | | | | | | |_| | | "
               "(_| | || (_) | |   \n"
            << " |______|_____/|______|          |_____/|_|_| |_| "
               "|_|\\__,_|_|\\__,_|\\__\\___/|_|   \n"
            << "                                                               "
               "                  \n";


  Node *head = nullptr;
  std::cout << menu;
  std::string command = "";


  while (true) { // command loop
    std::cout << "Enter command(menu to see commands): ";
    std::cin >> command;

    if (command == "exit") {
      std::cout << "Exiting the program\n";
      break;
    } else if (command == "insert") { // insert command
      std::cout << "digit the ammount of elements you want to add \n";
      int num = 0;
      std::cin >> num;

      // node insertion loop (receives each new node and stores them)
      while (num--) {
        int id;
        std::string description;
        int priority;
        std::cout << "enter the tasks in the following format: ID | "
                     "Priority(1-3) | Description"
                  << std::endl;
        std::cin >> id >> priority;
        std::getline(std::cin, description);

        // reruns the input in case the id is already taken
        while (checkID(head, id)) {
          std::cout << "id is already being used, digit another one:\n";
          std::cin >> id;
        }

        //reruns the input in case the priority interval is < 1 or > 3
        while(checkInterval(priority)) {
          std::cout << "please enter a priority from 1 to 3 to task with id: "
                    << id << std::endl;
          std::cin >> priority;
        }

        insert(head, id, description, priority);
      }
    } else if (command == "deleteID") { // delete command
      std::cout << "digit the id you want to delete" << std::endl;
      int id;
      std::cin >> id;
      removeID(*&head, id);
    } else if (command == "search") { // search command
      std::cout << "digit the id you want to insert" << std::endl;
      int id;
      std::cin >> id;

      Node *target = findID(head, id);

      std::cout << target->tasks.ID << " | " << target->tasks.description
                << " | " << target->tasks.priority << " | " << std::endl;
    } else if (command == "DeletePrio") { // delete based on priority command
      std::cout << "digit the priority you want to delete" << std::endl;
      int priority;
      std::cin >> priority;

      removePriority(*&head, priority);
    } else if (command == "exhibit") { // exhibit command 
      printList(*&head);

    } else if (command == "menu") { // help command
      std::cout << menu;
    } else {
      std::cout << "Invalid command! Please try again.\n"; // invalid command error
    }
    for (int i = 0; i < 3; i++) {
      std::cout << std::endl; // command spacing
    }
  }
}
