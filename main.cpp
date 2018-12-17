#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <conio.h>
#include <iomanip>
#include<fstream>



using namespace std;

//declare gloabal var
static string username = "null", s_role = "none", s_name = "null", s_course = "null", s_section = "null";
static bool result = false;
static int s_semester = 0, s_credit_hour = 0;
FILE *fp, *ft, *fshs;


struct student_has_subject
{
	string matric_id;
	string subject_code;
}s_has_sub;


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
	char role[20] = "user";
}e;

struct subjects
{
	char name[100];
	char code[100];
	int credit_hour;
	int semester;
	int capacity;
}subject;

void logo()
{
    cout << "\n==============================================================\n";
    cout << "||              UNIVERSITI TEKNOLOGI MALAYSIA               ||\n";
    cout << "||                      SKUDAI,JOHOR                        ||\n";
    cout << "||          UTM SUBJECT REGISTRATION SYSTEM                 ||\n";
    cout << "==============================================================\n";

    if(s_name != "null"){
		cout << endl << "welcome, " << s_name << "!Role:" << s_role << endl<< endl;
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
	cout << "| 4 => Delete Suject(Admin)                                |\n";
	cout << "| 5 => View All Subject(Admin)                             |\n";
	cout << "| 6 => Add Subject(Admin)                                  |\n";
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
    long int recsize, subRecsize, shsRec;

    fp = fopen("students.txt","rb+");
    ft = fopen("subjects.txt","rb+");
    fshs = fopen("student_has_subject.txt","rb+");
	//create file if not exist
    if (fp == NULL) {fp = fopen("students.txt","wb+");}
    if (ft == NULL) {ft = fopen("subjects.txt","wb+");}
    if (fshs == NULL) {fshs = fopen("student_has_subject.txt","wb+");}

 	recsize = sizeof(e);
 	subRecsize = sizeof(subject);
 	shsRec = sizeof(s_has_sub);


	rewind(fp);
	while (fread(&e,recsize,1,fp) == 1)
	{
		if (strcmp(e.matric_id,username) == 0 && strcmp(e.password,password) == 0){


			fseek(fp, - recsize, SEEK_CUR);
			fwrite(&e,recsize,1,fp);
			auth = true;

			s_role = e.role;
			s_name = e.first_name;
			s_course = e.course;
			s_section = e.section;
			s_semester = e.semester;
			s_credit_hour = e.credit_hour;
			break;

		}
	}

	if(auth == false){
		return "false";
	}

	return username;

}


//user functions
int userMainMenu()
{
	cout << "\n############################################################\n";
	cout << "#                       WELOCOME TO UTM CMS                #\n";
	cout << "#                use number(1-6) to make selection         #\n";
	cout << "############################################################\n";
	cout << "| 1 => Register Subject                                    |\n";
	cout << "| 2 => View Registered Subject                             |\n";
	cout << "| 3 => Search Subject                                      |\n";
	cout << "| 4 => Remove Registered Subject                           |\n";
	cout << "|==========================================================|\n";
	cout << "| Q => Quit                                                |\n";
	cout << "|==========================================================|\n";

	bool result = false; int num;
	do{
		cout<< "Select Menu(1-6):";
		cin >> num;

		if(num > 0 && num < 6){

			result = true;
		}else{
			cout << "invalid input! Please insert range 1-6.\n\n";
		}

	}while(result == false);

	return num;
}

//end user functions
int main() {

    char another, choice;
    bool backMain = true;

    char xfirst_name[50], xlast_name[50], getInput[100];
    long int recsize, subRecsize, shsRec;

    fp=fopen("students.txt","rb+");
    ft=fopen("subjects.txt","rb+");
    fshs = fopen("student_has_subject.txt","rb+");


 	recsize = sizeof(e);
 	subRecsize = sizeof(subject);
 	shsRec = sizeof(s_has_sub);

	string loginResult;
	int attempt = 0;

//	bool testing = true;
//
//	if(testing == true){
//		username = "test";
//		fp=fopen("students.txt","rb+");
//	    ft=fopen("subjects.txt","rb+");
//		//create file if not exist
//	    if (fp == NULL) {fp = fopen("students.txt","wb+");}
//	    if (ft == NULL) {ft = fopen("subjects.txt","wb+");}
//	}

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



   if(s_role == "user"){
   	// student


	do{
		clearScreen();
		int selected = userMainMenu();

		switch(selected){
			case 1 :

				rewind(ft);

				cout << "==== View All Subject For Semester " <<s_semester << "==== " << endl;
				while (fread(&subject,subRecsize,1,ft) == 1){

					if(subject.semester == s_semester){
						cout << "Subject              : "<< subject.code << " "<< subject.name << endl;
						cout << "Credit Hour          : "<< subject.credit_hour<< endl;
		                cout << "Semeseter            : "<< subject.semester<< endl;
		                cout << "Left                 : "<< subject.capacity<< endl;
						cout << "------------------------------------------------------" <<endl;
					}
				}
				result = false;

				do{
					string code;

					cout << "Insert subject code:"; cin>>code;

					//checking
					rewind(ft);
					while (fread(&subject,subRecsize,1,ft) == 1){

						if(subject.semester == s_semester && subject.code == code){

								fseek(fshs,0,SEEK_END);
				                s_has_sub.matric_id = username;
					            s_has_sub.subject_code = subject.code;

				                fwrite(&s_has_sub,shsRec,1,fshs);
				                fflush(stdin);

								result = true;
								cout << "Successfully Registered!" << endl;
								break;
						}

					}

					if(result == false){
						cout << "Invalid Selection!" <<endl << endl;
					}

				}while(result == false);

				system("pause");
				break;

				case 2 :

					rewind(fshs);
					cout << "==== View Registered Subject ======" << endl;
					while (fread(&s_has_sub,shsRec,1,fshs) == 1){

						if(s_has_sub.matric_id == username){
							cout << "CODE              : "<< s_has_sub.subject_code <<endl;
						}

					}
					cout << "====================================" << endl;
					system("pause");
					break;

                case 3 :

                    clearScreen();
					another = 'Y';

					while (another == 'Y'|| another == 'y')
					{
                        clearScreen();
                        cout << "======== Search Subject  ======== " << endl;
						cout << "\n Enter Subject Code/Name : ";
						cin >> getInput;

						while (fread(&subject,subRecsize,1,ft) == 1){

                            if (strcmp(subject.code,getInput) == 1 || strcmp(subject.name,getInput) == 1){

                                cout << "Name                 : "<< subject.name << endl;
                                cout << "Code                 : "<< subject.code<< endl;
                                cout << "Credit Hour          : "<< subject.credit_hour<< endl;
                                cout << "Semeseter            : "<< subject.semester<< endl;
                                cout << "Capacity             : "<< subject.capacity<< endl;
                                cout << "------------------------------------------------------" <<endl;

                                result = true;
                                break;
                            }
                        }

						if(result == false){
							cout << "No Record not found" <<endl;
						}

						cout << "Search Another Subject? (Y/N) ";
						fflush(stdin);
						another = getchar();
					}
                    break;
                case 4 :
                    break;


		}


	}while(backMain == true);

   	cout << "You're student" << endl;

   }else if(s_role == "admin"){

   	//access

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

		    		system("cls");
		        	another = 'Y';
		        	char code[20];
		        	FILE *ftt;

		        	while (another == 'Y'|| another == 'y')
		          	{
		          		bool deleted = false;

						cout << "\n Enter subject code to delete : ";
						cin >> code;

						//ftt: temp file ft:current users file

						ftt = fopen("temp.dat", "wb");

						rewind(ft);
						while (fread (&subject, subRecsize,1,ft) == 1)

		                if (strcmp(subject.code,code) != 0){
		                    fwrite(&subject,subRecsize,1,ftt);
		                }else{
		                	//subject found!
		                	deleted = true;
						}


		                if(deleted == true){

		        			fclose(ft);fclose(ftt);
			                remove("subjects.txt");
			                rename("temp.dat","subjects.txt");
							ft = fopen("subjects.txt","rb+");
							cout <<endl << "Successfully deleted the subject" <<endl;

						}else{

							cout << "No subject found!" <<endl;
							fclose(ftt); remove("temp.dat");
						}


						cout << "\n Delete another subject?(Y/N) ";
						fflush(stdin);
						another = getchar();
		            }
		    		break;
		    	case 5 :

		    		rewind(ft);
					cout << "==== View All Subject ==== " << endl;
					while (fread(&subject,subRecsize,1,ft) == 1){

						cout << "Name                 : "<< subject.name << endl;
						cout << "Code                 : "<< subject.code<< endl;
						cout << "Credit Hour          : "<< subject.credit_hour<< endl;
		                cout << "Semeseter            : "<< subject.semester<< endl;
		                cout << "Capacity             : "<< subject.capacity<< endl;
						cout << "------------------------------------------------------" <<endl;
					}
					cout << "\n\n";
					system("pause");

		    		break;
		    	case 6 :
		    		fseek(ft,0,SEEK_END);
		            another ='Y';

		            while(another == 'Y' || another == 'y')
		            {
		                system("cls");
		                cout << "==== Add Sbuject ==== " << endl ;
		                cout << "Name                 : ";cin >> subject.name;
						cout << "Code                 : ";cin >> subject.code;
						cout << "Credit Hour          : ";cin >> subject.credit_hour;
		                cout << "Semeseter            : ";cin >> subject.semester;
		                cout << "Capacity             : ";cin >> subject.capacity;

		                fwrite(&subject,subRecsize,1,ft);
		                cout << "\n Add Another Record (Y/N) ";
		                fflush(stdin);
		                another = getchar();
		            }
		    		break;
		    	case 7:

		    		fseek(fp,0,SEEK_END);
		            another ='Y';
		            while(another == 'Y' || another == 'y')
		            {
		                system("cls");
		                cout << "==== Add Student ==== " << endl ;
		                cout << "Enter the First Name : ";cin >> e.first_name;
						cout << "Enter the Last Name  : ";cin >> e.last_name;
						cout << "Enter Matric No      : ";cin >> e.matric_id;
		                cout << "Enter the Course     : ";cin >> e.course;
		                cout << "Enter the Section    : ";cin >> e.section;
		                cout << "Role(admin/user)     : ";cin >> e.role;

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
						cout << "Role       : " <<e.role <<endl;
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

   }
	return 0;
}

