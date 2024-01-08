// Q1) Create a Student Record in a file and Provide Option of addition / deletion / Modification of Data.
// Hint: write/read the data in File .
// Note : Use read() / write() function of C++.

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;
struct Student{
    int rollno;
    char name[50];
};
std::vector<double> uniqueNumbers;

void displaymenu(){
    cout << "\n1. Add Student Record";
    cout << "\n2. Delete Student Record";
    cout << "\n3. Modify Student Record";
    cout << "\n4. Display Records";
    cout << "\n5. Exit";
    cout << "\nEnter your choice: ";
}

bool findRecord(fstream& file, int rollNumberToFind) {
Student student;
    while (!file.eof()) {
        file >> student.rollno >> student.name;

        if (!file.eof() && student.rollno == rollNumberToFind) {
            return true; // Record found
        }
    }

    return false; // Record not found
}


void add(fstream& file){

    Student student;
    int rollno;
    cout << "\nEnter Roll Number: ";
    cin >> rollno;
    int newNumber = rollno;
    


    if (uniqueNumbers.empty()) {
        cout << "Vector is empty." <<endl;
        uniqueNumbers.push_back(newNumber);
    } 
    else{

        for (int i = 0; i < uniqueNumbers.size(); i++) {
            if (newNumber == uniqueNumbers[i]) {
                cout << "Enter a unique roll number." <<endl;
                return;
            }
        }
        cout << "Roll Number is unique and has been registered." << endl;
        uniqueNumbers.push_back(newNumber);
    }


    student.rollno = rollno;
    cout << "Enter Name: ";
    cin.ignore();
    cin.getline(student.name, sizeof(student.name));

    file << student.rollno << " " << student.name << endl;

    cout << "Record added successfully.";
}

void deleteRecord(fstream& inputFile, fstream& tempFile, int rollNumberToDelete){
    if (!findRecord(inputFile, rollNumberToDelete)) {
        cout << "Record with Roll Number " << rollNumberToDelete << " not found.";
        inputFile.close();
        tempFile.close();
        return;
    }
    // inputFile.clear();  //Clear EOF flag to rewind the file
    inputFile.seekg(0, ios::beg); // Move file pointer to the beginning    
    
    Student student;
    while (!inputFile.eof())
    {   
        inputFile >> student.rollno >> student.name;
         if (!inputFile.eof() && student.rollno!= rollNumberToDelete) {
            tempFile << student.rollno << " " << student.name<< endl;
        }
        else{
            break;
        }
        
    }
    inputFile.close();
    tempFile.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");
    cout << "Record deleted successfully.";
    
}

void modifyRecord(fstream& inputFile, fstream& tempFile, int rollNumberToModify) {
    if (!findRecord(inputFile, rollNumberToModify)) {
        cout << "Record with Roll Number " << rollNumberToModify << " not found.";
        inputFile.close();
        tempFile.close();
        return;
    }

    inputFile.clear(); // Clear EOF flag to rewind the file
    inputFile.seekg(0, ios::beg); // Move file pointer to the beginning

    Student student;
    while (!inputFile.eof()) {
        inputFile >> student.rollno >> student.name;
        if (!inputFile.eof()) {
            if (student.rollno == rollNumberToModify) {
                cout << "Current Record:\n";
                cout << "Roll Number: " << student.rollno << "\tName: " << student.name << endl;

                cout << "Enter new Roll Number: ";
                cin >> student.rollno;
                cout << "Enter new Name: ";
                cin.ignore();
                cin.getline(student.name, sizeof(student.name));
            }
             tempFile << student.rollno<< " " << student.name<<endl;
        }
        
    }

    // Continue copying the rest of the records
    while (!inputFile.eof()) {
        inputFile >> student.rollno >> student.name;
        tempFile << student.rollno << " " << student.name << endl;
    }

    inputFile.close();
    tempFile.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");
}


void displayRecords(fstream& inputFile) {
    Student student;

    cout << "\nStudent Records:\n";
    while (!inputFile.eof()) {
        inputFile >> student.rollno >> student.name;
        
        // Check if we have reached the end of the file before displaying the record
        if (!inputFile.eof()) {
            cout << "Roll Number: " << student.rollno << "\tName: " << student.name << endl;
        }
    }
}

int main()
{
    int choice;
    fstream inputFile;
    fstream tempFile;

    do
    {
        displaymenu();
        cin>>choice;

        switch (choice){
            case 1: //add record
                {
                    inputFile.open("students.txt" ,ios::binary|ios::app);
                    if (!inputFile)
                    {
                        cerr<<"Error in opening file"<<endl;
                        return 0;
                    }
                    add(inputFile);
                    inputFile.close();
                    
                }
                break;
            case 2: //delete record
                {
                    int rollNumberToDelete;
                    cout<<"Enter the Roll Number to Delete"<<endl;
                    cin>>rollNumberToDelete;
                    inputFile.open("students.txt");
                    tempFile.open("temp.txt" ,ios::binary | ios::app);

                    if (!inputFile || !tempFile) {
                            cerr << "Error opening file.";
                            return 0;
                        }
                    deleteRecord(inputFile, tempFile, rollNumberToDelete);
                }
                break;
            case 3: //modify record
                {
                    int rollNumberToModify;
                    cout<<"Enter the Roll Number to Modify its Data"<<endl;
                    cin >> rollNumberToModify;

                    inputFile.open("students.txt");
                    tempFile.open("temp.txt" , ios::app);
                    if (!inputFile || !tempFile) {
                            cerr << "Error opening file.";
                            return 0;
                        }
                    modifyRecord(inputFile, tempFile, rollNumberToModify);
                    
                }
                break;
            case 4: // Display Records
                {
                    inputFile.open("students.txt");
                    cout<<"sssssssssssssss";
                    if (!inputFile) {
                        cerr << "Error opening file for reading.";
                        return 0;
                    }
                    displayRecords(inputFile);
                    inputFile.close();
                }
                break;

            case 5: // Exit
                cout << "Exiting program.";
                break;
                
            default:
                cout << "Invalid choice. Please try again.";
        }
    } while (choice != 5);
    cin.ignore();
    return 0;
}