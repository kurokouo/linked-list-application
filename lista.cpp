
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

Node *build(int id, std::string descript, int priority) {
  Node *newNode = new Node();
  newNode->tasks.ID = id;
  newNode->tasks.description = descript;
  newNode->tasks.priority = priority;
  newNode->next = nullptr;
  newNode->prev = nullptr;
  return newNode;
}

void insert(Node *&head, int id, std::string descript, int priority) {
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

Node *sortnodesID(Node *start) {
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
Node *findID(Node *start, int id) {
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
void removeID(Node *&start, int id) {
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

void printList(Node *start) {
  Node *current = sortnodesID(start);
  while (current != nullptr) { // traverse all the nodes to print them all
    std::cout << "ID: " << current->tasks.ID << " | ";
    std::cout << "description: " << current->tasks.description << " | ";
    std::cout << "priority: " << current->tasks.priority << " | ";
    std::cout << std::endl;
    current = current->next;
  }
  std::cout << std::endl;
}

void removePriority(Node *&start, int priority){
  Node *current = start;

  while(current != nullptr){
    if(current->tasks.priority == priority){
      removeID(*&start, current->tasks.ID);
    }

    current = current->next;
  }
}

int main() {
  Node *head = nullptr;
  std::cout << menu;
  std::string command = "";
  while (true) {
    std::cout << "Enter command: ";
    std::cin >> command;
    if (command == "exit") {
      std::cout << "Exiting the program\n";
      break;
    } else if (command == "insert") {
      std::cout << "digit the ammount of elements you want to add\n";
      int num = 0;
      std::cin >> num;
      while (num--) {
        int id;
        std::string description;
        int priority;
        std::cout << "enter the node tasks in the following format: ID  Priority  Description" << std::endl;
        std::cin >> id >> priority;
        std::getline(std::cin, description);
        insert(head, id, description, priority);
      }
    } else if (command == "deleteID") {
      std::cout << "digit the id you want to delete" << std::endl;
      int id;
      std::cin >> id;
      removeID(*&head, id);
    } else if (command == "search") {
      std::cout << "digit the id you want to insert" << std:: endl;
      int id;
      std::cin >> id;

      Node *target = findID(head, id);

      std::cout << target->tasks.ID << " | " << target->tasks.description << " | " << target->tasks.priority << " | " << std::endl;
    } else if (command == "DeletePrio") {
      std::cout << "digit the priority you want to delete" << std::endl;
      int priority;
      std::cin >> priority;
      
      removePriority(*&head, priority);
    } else if (command == "exhibit") {
      printList(*&head);

    } else {
      std::cout << "Invalid command! Please try again.\n";
    }
    std::cout << std::endl;
  }
}
