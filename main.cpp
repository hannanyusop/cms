#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <conio.h>
#include <iomanip>
#include<fstream>



using namespace std;

//declare gloabal var
static string username = "null";
FILE *fp, *ft;

struct student
{
	char first_name[50];
	char last_name[50];
	char matric_id[20];
	char password[100];
	int semester = 0;
	int credit_hour = 0;
	char course[100];
	int section;
}e;
	
void logo()
{
    cout << "\n==============================================================\n";
    cout << "||              UNIVERSITI TEKNOLOGI MALAYSIA               ||\n";
    cout << "||                      SKUDAI,JOHOR                        ||\n";
    cout << "||          UTM SUBJECT REGISTRATION SYSTEM                 ||\n";
    cout << "==============================================================\n";
    
    if(username != "null"){
		cout << endl << "welcome, " << username << "!" << endl<< endl;	
	}
}

void clearScreen()
{
	system("CLS");
    logo();
}

bool backMainMessage()
{
	char action;
	cout << "Press Y/y to back main manu or press any key to exit:";
	cin >> action;
	
	if(action == 'y' || action == 'Y'){
		return true;
	}
	
	return false;
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
	cout << "| 7 => Add student(Admin)                                  |\n";
	cout << "| 8 => View Student(Admin)                                 |\n";
	cout << "| 9 => Search Student(Admin)                               |\n";
	cout << "|==========================================================|\n";
	cout << "| Q => Quit                                                |\n";
	cout << "|==========================================================|\n";
	
	bool result = false; int num;
	do{
		cout<< "Select Menu(1-6):";
		cin >> num;
		
		if(num > 0 && num < 10){
			
			result = true;
		}else{
			cout << "invalid input! Please insert range 1-6.\n\n";
		}
		
	}while(result == false);
	
	return num;
	
}


string login()
{
    char username[100],password[100];
    bool result = false;
    
    
    logo();
	cout << "\n==============================================================\n";
    cout<< "\n\t\tPlease Login\n\n";
    cout<< "\tStudent No:";
    cin >> username;
    cout<< "\tPassword: ";
    cin >> password;
    cout << "==============================================================\n";
    
    bool auth = false;
    long int recsize;

    fp=fopen("students.txt","rb+");
	//create file if not exist
    if (fp == NULL) {fp = fopen("students.txt","wb+");}
 	recsize = sizeof(e);
 	
	
	rewind(fp);
	while (fread(&e,recsize,1,fp) == 1)
	{
		if (strcmp(e.matric_id,username) == 0 && strcmp(e.password,password) == 0){
			
			
			fseek(fp, - recsize, SEEK_CUR);
			fwrite(&e,recsize,1,fp);
			auth = true;
			break;
			
		}
	}
		
	if(auth == false){
		return "false";
	}
	   
	return username;

}

int main() {
    FILE *fp, *ft;
    char another, choice;
    bool backMain = true;

    char xfirst_name[50], xlast_name[50];
    long int recsize;

    fp=fopen("students.txt","rb+");

 	recsize = sizeof(e);
 	
 	
	string loginResult;
	int attempt = 0;
	do{
        
        if(attempt == 0){
        	//change first attempt
			attempt++;
		}else{
			attempt++;
			system("CLS");
			cout << "\nInvalid Student ID or Password! Attempt(s):"<<attempt;
		}
		
        loginResult = login();

   }while(loginResult == "false");
   
   username = loginResult;
 	
 	
	do{
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
	    		break;
	    	case 7:
	    		
	    		fseek(fp,0,SEEK_END);
	            another ='Y';
	            while(another == 'Y' || another == 'y')
	            {
	                system("cls");
	                cout << "==== View All Student ==== " << endl ;
	                cout << "Enter the First Name : ";cin >> e.first_name;
					cout << "Enter the Last Name  : ";cin >> e.last_name;
					cout << "Enter Matric No      : ";cin >> e.matric_id;
	                cout << "Enter the Course     : ";cin >> e.course;
	                cout << "Enter the Section    : ";cin >> e.section;
	                
	                e.semester  = 1;
	                e.credit_hour = 0;
	                strcpy(e.password, e.matric_id);
	                
	                fwrite(&e,recsize,1,fp);
	                cout << "\n Add Another Record (Y/N) ";
	                fflush(stdin);
	                another = getchar();
	            }
            
	    		break;
	    	case 8 :
	    		
				rewind(fp);
				cout << "==== View All Student ==== " << endl;
				while (fread(&e,recsize,1,fp) == 1){
					
					cout << "Name       : " <<e.first_name <<" "<<e.last_name <<endl;
					cout << "Matric No  : " <<e.matric_id <<endl;
					cout << "Course     : " <<e.course <<endl;
					cout << "Section    : " <<e.section <<endl;
					cout << "Semester   : " << e.semester <<endl;
					cout << "Credit Hour: " <<e.credit_hour <<endl;
					cout << "------------------------------------------------------" <<endl;
				}
				cout << "\n\n";
				system("pause");
	           
		    	break;
		    	
		    case 9 :
		    	
		    	system("cls");
				another = 'Y';
				bool result = false;
				
				while (another == 'Y'|| another == 'y')
				{
					cout << "\n Enter the last name of the student : ";
					cin >> xlast_name;
					
					rewind(fp);
					while (fread(&e,recsize,1,fp) == 1)
					{
						if (strcmp(e.last_name,xlast_name) == 0){
							
							cout << endl <<"Found!" <<endl;
							cout << "Name       : " <<e.first_name <<" "<<e.last_name <<endl;
							cout << "Matric No  : " <<e.matric_id <<endl;
							cout << "Course     : " <<e.course <<endl;
							cout << "Section    : " <<e.section <<endl;
							cout << "Semester   : " << e.semester <<endl;
							cout << "Credit Hour: " <<e.credit_hour <<endl;
							fseek(fp, - recsize, SEEK_CUR);
							fwrite(&e,recsize,1,fp);
							result = true;
							break;
							
						}
					}
					
					if(result == false){
						cout << "Student Record not found" <<endl;
					}
					cout << "Search Another Student? (Y/N) ";
					fflush(stdin);
					another = getchar();
				}
		    	break;
		}
	}while(backMain == true);

	return 0;
}

