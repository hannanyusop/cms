#include<iostream>
#include<string>
#include<stdlib.h>
#include<fstream>
#include <string.h>


using namespace std;

//declare gloabal var
int max_subject = 100;
string subjectFile = "data/subjects.data";
static string username = "null";

typedef struct subject
{
    char code[10] = "null";
    char name[100] = "null";
    int credit_hour = 0;
    int semester = 0;
    int capacity = 0;
}subject_t;


typedef struct students
{
	char matric_id[20] = "null";
	char password[100];
	char name[100];
	int semester = 0;
	int credit_hour = 0;
}student_t;

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

string login()
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
	
	
	if(auth == false){
		return "false";
	}
	   
	return username;

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
	cout << "|==========================================================|\n";
	cout << "| Q => Quit                                                |\n";
	cout << "|==========================================================|\n";
	
	bool result = false; int num;
	do{
		cout<< "Select Menu(1-6):";
		cin >> num;
		
		if(num > 0 && num < 9){
			
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
		bool result = false;
		clearScreen();
		cout << "       ---------------------------------------------------    \n";
		cout << "       |             SEARCH SUBJECT ID                   |    \n";
		cout << "       ---------------------------------------------------    \n";
		
	string code; 
	cout << "Insert Subject ID:";
	cin >> code;
	
		// Reading from it
    ifstream input_file("subjects.data", ios::binary);
    subject_t data[10];
    input_file.read((char*)&data, sizeof(data));
	         

    for (size_t i = 0; i < 10; i++)
    {
		if(data[i].credit_hour != 0){
			
			if(data[i].code == code){
				cout << "Record Found! "<<endl;
				cout << "Record #" << i << endl;
		        cout << "Code: " << data[i].code << endl;
		        cout << "Name: " << data[i].name << endl;
		        cout << "Credit Hour: " << data[i].credit_hour << endl;
		        cout << "Semester: " << data[i].semester << endl;
		        cout << "Capacity: " << data[i].capacity << endl;
		        cout << "-------------------------------------------" << endl;
		        
		        result = true;
			}
		}
		
    }	

		if(result == false){
			cout << "Sorry! No code match! (" << code << ")" <<endl; 
		}  
	  	cout << "\n\nDo you want to search another code?\nclick Y for yes or enter any key to stop\n";
	  	cin >> again;
	  
	}while(again == 'y' || again == 'Y');
	
}

bool addSubject()
{
	clearScreen();
	cout << "       ---------------------------------------------------    \n";
	cout << "       |                    ADD SUBJECT                  |    \n";
	cout << "       ---------------------------------------------------    \n";
	
	subject_t data[10];  
	
    strcpy(data[0].code, "DUA1002");
    strcpy(data[0].name, "Pengajian AM");
    data[0].credit_hour = 2;
	data[0].semester = 1;
	data[0].capacity = 30;
	
	strcpy(data[1].code, "DUE1202");
    strcpy(data[1].name, "Communicative English");
    data[1].credit_hour = 2;
	data[1].semester = 1;
	data[1].capacity = 30;
	
	strcpy(data[2].code, "NET1103");
    strcpy(data[2].name, "Operating System");
    data[2].credit_hour = 3;
	data[2].semester = 1;
	data[2].capacity = 30;
	
    // Serializing struct to student.data
    ofstream output_file("subjects.data", ios::binary);
    output_file.write((char*)&data, sizeof(data));
    output_file.close();
    
    return backMainMessage();
	
}

bool viewAllSubject()
{	
	clearScreen();
	cout << "       ---------------------------------------------------    \n";
	cout << "       |                 VIEW ALL SUBJECT                |    \n";
	cout << "       ---------------------------------------------------    \n";
	
    ifstream input_file("subjects.data", ios::binary);
    subject_t data[10];
    input_file.read((char*)&data, sizeof(data));
	         

    for (size_t i = 0; i < 10; i++)
    {


		if(data[i].credit_hour != 0){
			
			cout << "Record #" << i << endl;
	        cout << "Code: " << data[i].code << endl;
	        cout << "Name: " << data[i].name << endl;
	        cout << "Credit Hour: " << data[i].credit_hour << endl;
	        cout << "Semester: " << data[i].semester << endl;
	        cout << "Capacity: " << data[i].capacity << endl;
	        cout << "-------------------------------------------" << endl;
	        
		}else{
			cout << "End of Records. Total: " << i <<" record(s)" << endl;
			break;
		}

        
    }
    
	string action;
	cout << "\nPress any key to back main menu....";
	cin >> action;
	return true;
		
}


//ADMIN FUNCTION START

bool adminAddStudent()
{
	clearScreen();
	cout << "       ---------------------------------------------------    \n";
	cout << "       |                    ADD STUDENT                  |    \n";
	cout << "       ---------------------------------------------------    \n";
	
	char name[100],matric_id[20];
	int semester;
	
	cout << endl << "Name:"; cin >> name;
	
	cout << endl << "Matric No:"; cin >> matric_id;
	
	cout << endl << "Semeseter:"; cin >> semester;
	
	ifstream input_file("new_students.data", ios::binary);
    student_t oldData[10];
    input_file.read((char*)&oldData, sizeof(oldData));
	         
	student_t data[10]; 
    for (int i = 0; i < 10; i++)
    {
		if(data[i].semester != 0){
			
			strcpy(data[i].name, oldData[i].name);
		    strcpy(data[i].matric_id, oldData[i].matric_id);
		    strcpy(data[i].password, oldData[i].password); //use matric no as default password 
		    data[i].credit_hour = oldData[i].credit_hour;
			data[i].semester = oldData[i].semester;
	        
		}else{
			strcpy(data[i].name, name);
		    strcpy(data[i].matric_id, matric_id);
		    strcpy(data[i].password, matric_id); //use matric no as default password 
		    data[i].credit_hour = 0;
			data[i].semester = semester;
			break;
		}

        
    }
    
    ofstream output_file("new_students.data", ios::binary);
    output_file.write((char*)&data, sizeof(data));
    output_file.close();
    
    return backMainMessage();
	
	
}

bool viewAllStudent()
{	
	clearScreen();
	cout << "       ---------------------------------------------------    \n";
	cout << "       |                 VIEW ALL STUDENT                |    \n";
	cout << "       ---------------------------------------------------    \n";
	
    ifstream input_file("new_students.data", ios::binary);
    student_t data[10];
    input_file.read((char*)&data, sizeof(data));
	         

    for (size_t i = 0; i < 10; i++)
    {


		if(data[i].semester != 0){
			
			cout << "Record #" << i << endl;
	        cout << "Matric ID: " << data[i].matric_id << endl;
	        cout << "Name: " << data[i].name << endl;
	        cout << "Password: " << data[i].password << endl;
	        cout << "Semester: " << data[i].semester << endl;
	        cout << "Total Credit Hour: " << data[i].credit_hour << endl;
	        cout << "-------------------------------------------" << endl;
	        
		}else{
			cout << "End of Records. Total: " << i <<" record(s)" << endl;
			break;
		}

        
    }
    
	string action;
	cout << "\nPress any key to back main menu....";
	cin >> action;
	return true;
		
}

	
//ADMIN FUNCTION END
int main()
{
   clearScreen();
   string loginResult;
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

   }while(loginResult == "false");
   
   username = loginResult;

	bool backMain = true;
    do{
    	//logged in
	    clearScreen();
	    int selected = displayMenu();
	    
	    clearScreen();
	    switch(selected){
	    	case 1 :
	    		backMain = addSubject();
	    		break;
	    	case 2 :
	    		break;
	    		
	    	case 3 :
	    		break;
	    	case 4 :
	    		break;
	    	case 5 :
	    		backMain = viewAllSubject();
	    		break;
	    	case 6 :
	    		searchSubject();
	    		break;
	    	case 7:
	    		adminAddStudent();
	    		break;
	    	case 8 :
	    		viewAllStudent();
	    		break;
		}
	}while(backMain == true);
    

   return 0;
}
