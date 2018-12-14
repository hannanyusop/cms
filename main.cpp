#include<iostream>
#include<string>
#include<stdlib.h>
#include<fstream>

using namespace std;

void logo()
{
    cout << "======================================\n";
    cout << "|| UTHM SUBJECT REGISTRATION SYSTEM ||\n";
    cout << "======================================\n\n";
}
bool login()
{
    string username,password;
	cout<< "\n------------------------------------------------\n";
    cout<< "\n\t\tPlease Login\n\n";
    cout<< "\tStudent No:";
    cin >> username;
    cout<< "\tPassword: ";
    cin >> password;
    cout<< "\n------------------------------------------------\n";
    
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

    std::fstream fs;
    fs.open ("data/students/test.txt", std::fstream::in | std::fstream::out | std::fstream::app);
    fs << " more lorem ipsum";
    fs.close();

   return 0;
}
