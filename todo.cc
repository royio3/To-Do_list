#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class todolist{
  public:
    todolist(){};
    void addTask(std::string task);
    void readList();
    void deleteTask(int n);
    void deleteList();
    void markComplete(int n);
    void markAll();
    void unmark(int n);
    void unmarkAll();
    void loadTasks();
    void save();
    void loadCustomList();

  private:
    std::vector<std::string> list;
    std::vector<bool> mark;
};

int main(){
  todolist todo;
  todo.loadTasks();
  std::string input;
  std::string task;
  bool isNumber = true;
  do{
    std::cout << "=====================================" << std::endl;
    std::cout << "To-Do List Application by Roy Timman" << std::endl;
    todo.readList();
    std::cout << "1) Add task." << std::endl;
    std::cout << "2) Delete task." << std::endl;
    std::cout << "3) Mark task as complete." << std::endl;
    std::cout << "4) Unmark task as complete." << std::endl;
    std::cout << "5) Save list" << std::endl;
    std::cout << "6) Load custom list" << std::endl; 
    std::cout << "q) Quit program." << std::endl;
    std::cout << std::endl << "> ";
    std::getline(std::cin, input);

    if(input == "add" || input == "1"){
      do{
        std::cout << "====================================" <<std::endl;
        todo.readList();
        std::cout << "Which tasks would you like to add? Press enter again to go back to menu" << std::endl;
        std::cout << "> ";
        task.clear();
        std::getline(std::cin, task);
        todo.addTask(task);
      }while(!task.empty());
    }

    else if(input == "delete" || input == "2"){
      do{
        std::cout << "====================================" <<std::endl;
        todo.readList();
        std::cout << "Enter the number of the task you want removed.Press enter again to go back to the menu."<< std::endl;
        std::cout << "If you want to delete all tasks, enter \"all\"."<< std::endl;
        std::cout << "> ";
        task.clear();
        isNumber = true;
        std::getline(std::cin, task);
        if(task == "all"){
          todo.deleteList();
          break;
        }
        for(unsigned int i = 0; i < task.length(); i++){
          if(task[i] < '0' || task[i] > '9'){
            isNumber = false;
            break;
          }
        }
        if(task.empty())
          isNumber = false;

        if(isNumber)
          todo.deleteTask(std::stoi(task));
        }while(!task.empty());
    }

    else if(input == "mark" || input == "3"){
      do{
        std::cout << "====================================" <<std::endl;
        todo.readList();
        std::cout << "Enter the number of the task you want to mark as complete. Press enter again to go back to the menu."<< std::endl;
        std::cout << "If you want to mark all tasks as complete, enter \"all\"."<< std::endl;
        std::cout << "> ";
        task.clear();
        isNumber = true;
        std::getline(std::cin, task);
        if(task == "all"){
          todo.markAll();
          break;
        }
        for(unsigned int i = 0; i < task.length(); i++){
          if(task[i] < '0' || task[i] > '9'){
            isNumber = false;
            break;
          }
        }
        if(task.empty())
          isNumber = false;

        if(isNumber)
          todo.markComplete(std::stoi(task));
      }while(!task.empty());
    }
    
    else if(input == "unmark" || input == "4"){
      do{
        std::cout << "====================================" <<std::endl;
        todo.readList();
        std::cout << "Enter the number of the task you want to umark. Press enter again to go back to the menu."<< std::endl;
        std::cout << "If you want to unmark all tasks, enter \"all\"."<< std::endl;
        std::cout << "> ";
        task.clear();
        isNumber = true;
        std::getline(std::cin, task);
        if(task == "all"){
          todo.unmarkAll();
          break;
        }
        for(unsigned int i = 0; i < task.length(); i++){
          if(task[i] < '0' || task[i] > '9'){
            isNumber = false;
            break;
          }
        }
        if(task.empty())
          isNumber = false;

        if(isNumber)
          todo.unmark(std::stoi(task));
      }while(!task.empty());
    }

    else if(input == "save" || input == "5")
      todo.save();

    else if(input == "load" || input == "6"){
      std::cout << "filename: ";
      todo.loadCustomList();
    }
  }while(input != "q");
  todo.save();
}

//adds task
void todolist::addTask(std::string task){
  if(task.empty())
    return;
  list.push_back(task);
  mark.push_back(false);
}

//prints TODO list from vector
void todolist::readList(){
  if(list.empty())
    return;
  for(unsigned int i = 0; i < list.size(); i++){
    std::cout << i+1 <<", " << list[i];
    if(mark[i])
      std::cout <<"\t DONE";
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

//deletes given task
void todolist::deleteTask(int n){
  if(list.empty() || n > int(list.size()) || n == 0)
    return;
  list.erase(list.begin()+n-1);
  mark.erase(mark.begin()+n-1);
}

//Delete whole TODO list
void todolist::deleteList(){
  list.clear();
  mark.clear();
}


//marks given task as complete
void todolist::markComplete(int n){
  if(mark.empty() || n > int(mark.size()) || n == 0)
    return;

  mark[n-1] = true;
}

//Marks all tasks as complete
void todolist::markAll(){
  if(mark.empty())
    return;

  for(unsigned int i = 0; i < mark.size(); i++)
    mark[i] = true;
}
//marks given task as complete
void todolist::unmark(int n){
  if(list.empty() || n > int(list.size()) || n == 0)
    return;

  mark[n-1] = false;
}

void todolist::unmarkAll(){
  if(mark.empty())
    return;

  for(unsigned int i = 0; i < mark.size(); i++)
    mark[i] = false;
}

//Loads tasks from txt file
void todolist::loadTasks(){
  std::string line;
  std::ifstream file("todolist.txt");
  if(file.is_open()){
    while(getline(file,line)){
      this->addTask(line);
    }
    std::cout << line.length() << std::endl;
    this->deleteTask(int(list.size()));
    for(unsigned int i = 0; i < line.size(); i++){
      if(i >= list.size())
        return;
      if(line[i] == '1')
        markComplete(i+1);
    }
    file.close();
  }
}

//Saves tasks in txt file
void todolist::save(){
  std::ofstream file ("todolist.txt"); 
  if(file.is_open()){
    for(unsigned int i = 0; i < list.size(); i++){
      file << list[i] << "\n";  //saves tasks in file
    }
    for(unsigned int i = 0; i < mark.size(); i++){
      file << mark[i]; //saves mark status in file
    }
    file.close();
  }
}

//Add your own list functionality
void todolist::loadCustomList(){
  std::string fileName;
  std::string line;
  getline(std::cin, fileName);
  std::ifstream file(fileName);
  if(file.fail()){
    std::cout << "File doesn't exist" << std::endl;
    return;
  }
  this->deleteList();
  while(getline(file,line)){
      this->addTask(line);
  }
  std::cout << line.length() << std::endl;
  line = list[list.size()-1]; // This command is to retrieve the intended last line otherwise there is a chance the last line is an EOF with length 0
  for(unsigned int i = 0; i < line.length(); i++){
    if(line[i] != '0' && line[i] != '1')
      return;
  }
  this->deleteTask(int(list.size()));
  for(unsigned int j = 0; j < line.length(); j++){
    if(j >= list.size())
      return;
    if(line[j] == '1')
      markComplete(j+1);
  }
}