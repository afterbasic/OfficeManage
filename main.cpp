#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
struct OFFICE_EMPLOYEES_DATA {
  unsigned int PrimaryKey;
  std::string Name;
  std::string ID;
  std::string Position;
  /*1. Create the based logic tables.*/
};
/*2. checking and creating database, in this case a binary encoded file.*/
void system_check_DataBase(std::fstream &Data_Variable);
unsigned int Intro_Get_Option_User();
void AddEmployeesData(std::fstream &Data_Variable);
unsigned int System_Get_Data_Size(std::fstream &Data_Variable);
void SystemEmployeesWriteData(std::fstream &Data_Variable, unsigned int BaitPosition, OFFICE_EMPLOYEES_DATA &InputEmployeesData);
void displayEmployeesData(std::fstream &Data_Variable);
OFFICE_EMPLOYEES_DATA SystemReadEmployessData(std::fstream &Data_Variable, unsigned int Position);
 int main(int argc, char** argv) {
   std::fstream Data_Variable;
  system_check_DataBase(Data_Variable);
  unsigned int User_Choice = Intro_Get_Option_User();
  char User_Event_Continue;
  enum System_Option{ADD = 1, DISPLAY, EDIT, DELETE, QUIT};
  /*Transforming the coice onto keyword*/
  
  while(User_Choice != QUIT) {
    switch(User_Choice) {
      case ADD:
      std::cout << "•••Adding Employee's Data." << std::endl;
      AddEmployeesData(Data_Variable);
      break;
      case DISPLAY:
      std::cout << "•••Displaying Employee's Data." << std::endl;
      displayEmployeesData(Data_Variable);
      break;
      case EDIT:
      std::cout << "•••Editing Employee's Data." << std::endl;
      break;
      case DELETE:
      std::cout << "•••Deleting Employee's Data." << std::endl;
      break;
      default:
      std::cout << "Console Message: No keyword found. Choose [1-5]" << std::endl;
      break;
    }
    label_continue:
    std::cout << "Continue? (yY/nN) : " << std::endl;
    std::cin >> User_Event_Continue;
    if((User_Event_Continue == 'y') | (User_Event_Continue == 'Y'))  {
      User_Choice = Intro_Get_Option_User();
  } else if((User_Event_Continue == 'n') | (User_Event_Continue == 'N')) {
    break;
  } else {
    std::cout << "Console message: Please choose the right input." << std::endl;
    goto label_continue;
  }
  
}
std::cout << "Console message: end of a program." << std::endl;
  std::cin.get();
  return 0;
}
void system_check_DataBase(std::fstream &Data_Variable) {
  Data_Variable.open("data.bin", std::ios::out | std::ios::in | std::ios::binary);
  /*checking the database*/
  unsigned int StatusCodeCheck_Exist = rand();
  unsigned int StatusCodeCheck_NotExist = rand();
  if (Data_Variable.is_open()) {
    std::cout << "Console message: DataBase system is ready. status code: " << StatusCodeCheck_Exist << std::endl;
  } else {
    std::cout << "Console message: System Database doesn't exist, creating a new one. status code: " << StatusCodeCheck_NotExist << std::endl;
    Data_Variable.close();
    Data_Variable.open("data.bin", std::ios::trunc | std::ios::out | std::ios::in | std::ios::binary);
  }
  
}
unsigned int Intro_Get_Option_User() {
  unsigned int User_Input;
  std::system("clear");
  std::system("clear");
  std::cout << "||||||OFFICE MANAGER V. 1.0 ||||||" << std::endl;
  std::cout << "1. Add Employee's Data" << std::endl;
  std::cout << "2. Display Employee's Data" << std::endl;
  std::cout << "3. Edit Employee's Data" << std::endl;
  std::cout << "4. Delete Employee's Data" << std::endl;
  std::cout << "5. Quit Program" << std::endl;
  std::cout << "Console Message : *Your input [1-5]* >> " << std::endl;
  std::cin >> User_Input;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
	
  return User_Input;
}

void AddEmployeesData(std::fstream &Data_Variable) {
  OFFICE_EMPLOYEES_DATA InputEmployeesData;
  OFFICE_EMPLOYEES_DATA lastEmployeesData;
  unsigned int Data_Size = System_Get_Data_Size(Data_Variable);
  std::cout << "Console message: data size : " << Data_Size << std::endl;
  if (Data_Size == 0) {
    InputEmployeesData.PrimaryKey = 1;
  } else {
    lastEmployeesData = SystemReadEmployessData(Data_Variable, Data_Size);
    std::cout << "Console message: Primary key : " << lastEmployeesData.PrimaryKey << std::endl;
    InputEmployeesData.PrimaryKey = lastEmployeesData.PrimaryKey + 1;
  }
  std::cout << "•Employees Name: " << std::endl;
  std::getline(std::cin, InputEmployeesData.Name);
  std::cout << "•Employees Position: " << std::endl;
  std::getline(std::cin, InputEmployeesData.Position);
  std::cout << "•Employees ID: " << std::endl;
  std::getline(std::cin, InputEmployeesData.ID);
  SystemEmployeesWriteData(Data_Variable, Data_Size + 1, InputEmployeesData);
  return;
}
unsigned int System_Get_Data_Size(std::fstream &Data_Variable) {
  unsigned int start;
  unsigned int end;
  Data_Variable.seekg(0, std::ios::beg);
  start = Data_Variable.tellg();
  Data_Variable.seekg(0, std::ios::end);
  end = Data_Variable.tellg();
  return ( end - start)/(sizeof(OFFICE_EMPLOYEES_DATA));
}
void SystemEmployeesWriteData(std::fstream &Data_Variable, unsigned int Position, OFFICE_EMPLOYEES_DATA &InputEmployeesData) {
  Data_Variable.seekp((Position - 1) * sizeof(OFFICE_EMPLOYEES_DATA), std::ios::beg);
  Data_Variable.write(reinterpret_cast<char*>(&InputEmployeesData), sizeof(OFFICE_EMPLOYEES_DATA));
  return;
}
OFFICE_EMPLOYEES_DATA SystemReadEmployessData(std::fstream &Data_Variable, unsigned int Position) {
  OFFICE_EMPLOYEES_DATA readEmployeesData;
Data_Variable.seekg((Position - 1)*sizeof(OFFICE_EMPLOYEES_DATA),std::ios::beg);
	Data_Variable.read(reinterpret_cast<char*>(&readEmployeesData),sizeof(OFFICE_EMPLOYEES_DATA));
	return readEmployeesData;
}
void displayEmployeesData(std::fstream &Data_Variable){
	unsigned int size = System_Get_Data_Size(Data_Variable);
	OFFICE_EMPLOYEES_DATA showEmployeedData;
	std::cout << "\tNo. \tName.\tPrimary Key.\tPosition.\tID." << std::endl;
	for(unsigned int i = 1; i <= size; i++){
		showEmployeedData = SystemReadEmployessData(Data_Variable,i);
		std::cout << i << "\t";
		std::cout << showEmployeedData.Name << "\t";
		std::cout << showEmployeedData.PrimaryKey << "\t";
		std::cout << showEmployeedData.ID << "\t";
		std::cout << showEmployeedData.Position << std::endl;
	}
}