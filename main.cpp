#include<iostream>
#include<string>
#include<stdlib.h>
#include<fstream>

using namespace std;


void logo()
{
    cout << "\n==============================================================\n";
    cout << "||              UNIVERSITI TEKNOLOGI MALAYSIA               ||\n";
    cout << "||                      SKUDAI,JOHOR                        ||\n";
    cout << "||          UTM SUBJECT REGISTRATION SYSTEM                 ||\n";
    cout << "==============================================================\n";
}

void clearScreen()
{
	system("CLS");
    logo();
}

bool login()
{
    string username,password;
    
	cout << "\n==============================================================\n";
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

void searchSubject()
{
	char again = 'y';
    		
	do{
		
		clearScreen();
		cout << "       ---------------------------------------------------    \n";
		cout << "       |             SEARCH SUBJECT ID                   |    \n";
		cout << "       ---------------------------------------------------    \n";
		
	string code; 
	cout << "Insert Subject ID:";
	cin >> code;
	
	string parameter = "["+code+"]";
	string line;
	bool result = false;
	
	  ifstream subject ("data/subjects.txt");
	  subject.is_open();
	    size_t pos;
		while(subject.good())
		{
		      getline(subject,line);
		      pos=line.find(parameter); 
		      if(pos!=string::npos) 
		        {
		            cout << "Found:"+line;
		            result = true;
		            break;
		        }
		}
		  
		if(result == false){
			cout << "\n\nSorry! No Code found for:"+code+"\n";
		}
		
	    subject.close();	  
	  
	  	cout << "\n\nDo you want to search another code?\nclick Y for yes or enter any key to stop\n";
	  	cin >> again;
	  	
	  
	  
	}while(again == 'y' || again == 'Y');
	
}

int main() {
   clearScreen();
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
    clearScreen();
    int selected = displayMenu();
    
    clearScreen();
    switch(selected){
    	case 1 :
    		break;
    		
    	case 2 :
    		break;
    		
    	case 3 :
    		break;
    	case 4 :
    		break;
    	case 5 :
    		break;
    	case 6 :
    		searchSubject();
    		break;
	}
    

   return 0;
}
