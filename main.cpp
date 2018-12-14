#include<iostream>
#include<string>
#include<stdlib.h>
#include<fstream>

using namespace std;

void logo()
{
    cout << "==============================================================\n";
    cout << "||              UNIVERSITI TEKNOLOGI MALAYSIA               ||\n";
    cout << "||                      SKUDAI,JOHOR                        ||\n";
    cout << "||          UTM SUBJECT REGISTRATION SYSTEM                 ||\n";
    cout << "==============================================================\n";
}
bool login()
{
    string username,password;
    
	cout << "==============================================================\n";
    cout<< "\n\t\tPlease Login\n\n";
    cout<< "\tStudent No:";
    cin >> username;
    cout<< "\tPassword: ";
    cin >> password;
    cout << "==============================================================\n";
    
    bool auth = false;
    string parameter = username+"=>"+password;

	string line;
	  ifstream student ("data/students.txt");
	  if (student.is_open())
	  {
	    size_t pos;
		while(student.good())
		  {
		      getline(student,line);
		      pos=line.find(parameter); 
		      if(pos!=string::npos) 
		        {
		            auth = true;
		            break;
		        }
		  }
	    student.close();
	  }else cout << "Unable to open file";
	
	
	   
	return auth;

}

int displayMenu()
{
	cout << "\n############################################################\n";
	cout << "#                       WELOCOME TO UTM CMS                #\n";
	cout << "#                use number(1-6) to make selection         #\n";
	cout << "############################################################\n";
	cout << "| 1 => Add Subject                                         |\n";
	cout << "| 2 => Delete Subject                                      |\n";
	cout << "| 3 => Submit Subject                                      |\n";
	cout << "| 4 => View Reqistered Subject                             |\n";
	cout << "| 5 => View All Subject                                    |\n";
	cout << "| 6 => Search Subject ID                                   |\n";
	cout << "|==========================================================|\n";
	cout << "| Q => Quit                                                |\n";
	cout << "|==========================================================|\n";
	
	bool result = false; int num;
	do{
		cout<< "Select Menu(1-6):";
		cin >> num;
		
		if(num > 0 && num < 7){
			
			result = true;
		}else{
			cout << "invalid input! Please insert range 1-6.\n\n";
		}
		
	}while(result == false);
	
	return num;
	
}
int main() {
   logo();
   bool loginResult;
   int attempt = 0;
   do{
        
        if(attempt == 0){
        	//change first attempt
			attempt++;
		}else{
			attempt++;
			system("CLS");
			logo();
			cout << "\nInvalid Student ID or Password! Attempt(s):"<<attempt;
		}
		
        loginResult = login();

   }while(loginResult == 0);

    //logged in
    system("CLS");
    logo();
    int selected = displayMenu();
    cout << selected;
    

   return 0;
}
