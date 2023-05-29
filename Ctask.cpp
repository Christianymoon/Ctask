#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <limits>
#include <time.h>

using std::string;

struct Tasks {
	string task;
	string date;
	Tasks *follow;
};

class TaskManager {

private:

	Tasks *front = NULL;
	Tasks *end = NULL;

public:
	static bool isVoid(Tasks *front) {
		return (front == NULL)? true : false;
	}

	void insertTask(string task, string date) {
		Tasks *new_task = new Tasks();
		new_task->task = task;
		new_task->date = date;
		new_task->follow = NULL;
		if (TaskManager::isVoid(front)) {
			front = new_task;
		} else {
			end->follow = new_task;
		}
		end = new_task;

		setTaskToFile(&new_task->task, &new_task->date);
	}

	void deleteTasks() {
		Tasks *aux = front;
		if (front == end) {
			front = NULL;
			end = NULL;
		} else {
			front = front->follow;
		}
		delete aux;
	}

	void extractData() {
		while (front != NULL) {
			if (front != NULL) {
				deleteTasks();
			} else {
				std::cout<<"\n\nFinished\n\n"<<std::endl;
			}
		}
		getTaskToFile();
		std::cout<<"\n";
		system("pause");
		system("cls");
	}

	void setTaskToFile(string *task, string *date) {
	    time_t rawtime;
	    time (&rawtime);
		std::ofstream file("tasks.txt", std::ios::app);
		string current_task = *task;
		file<<current_task<<" at "<<*date<<" created "<< ctime (&rawtime);
	}

	void getTaskToFile() {
		std::ifstream file("tasks.txt");
		if (file.is_open()) {
			std::string line;
			while(std::getline(file, line)) {
				std::cout<<"\n";
				std::cout<<"-----------------------------------------------------"<<std::endl;
				std::cout<<"Task * "<< line <<"                                  "<<std::endl;
				std::cout<<std::endl;

			}
			file.close();
		} else {
                std::cout<<"[!] Error: File not opened"<<std::endl;
		}
	}

	void deleteAllTasks() {
		std::ofstream file("tasks.txt", std::ofstream::out | std::ofstream::trunc);
		file.close();
	}
};


int main_menu(); // prototype of function
void banner();
void insertTaskMenu(TaskManager &);

int main() {
	int selection = 0;
	TaskManager tasking = TaskManager();
	do {
		banner();
    	selection = main_menu();
    	switch (selection) {
    		case 1:
    			tasking.extractData(); break;
    		case 2:
    			insertTaskMenu(tasking); break;
    		case 3:
    			tasking.deleteAllTasks(); break;
		}

	} while(selection != 0);


    return 0;
}

void banner() {
    std::cout<<"----------------------------------------------------------------"<<std::endl;
    std::cout<<"|      Ctask by Christian written in C++                        |"<<std::endl;
    std::cout<<"|                                                               |"<<std::endl;
    std::cout<<"----------------------------------------------------------------"<<std::endl;
    std::cout<<"\nSelect a option:\n"<<std::endl;
	std::cout<<"\t 1 - View current tasks"<<std::endl;
	std::cout<<"\t 2 - Enter a new task"<<std::endl;
	std::cout<<"\t 3 - Delete all tasks"<<std::endl;
	std::cout<<"\t 0 - Exit"<<std::endl;
}


int main_menu() {
    int option = 0;
    std::cout<<"\n\nEnter a option: ";
    std::cin>>option;

	if (option != 0 && option < 4) {
		return option;
	} else {
		std::cout<<"\ngoodbye"<<std::endl;
		return option;
	}
}

void insertTaskMenu(TaskManager &task_manager) {
	string task;
	string time;
	int option;
	do {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "[*] Set a task: ";
        std::getline(std::cin, task);
        std::cout << "[*] Set a finish time: ";
        std::getline(std::cin, time);
        task_manager.insertTask(task, time);
        std::cout << "\n\n[!] Set more tasks? 1 = yes, 2 = no: ";
        std::cin >> option;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	} while (option == 1);

}


