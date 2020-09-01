/*
 * Design a system to keep track of employee data. The system should keep track of an employee’s name, ID number and
hourly pay rate in a class called Employee. You may also store any additional data you may need, hint, you need
something extra. This data is stored in a file (user selectable) with the id number, hourly pay rate, and the employee’s
full name (example):
17 5.25 Daniel Katz
18 6.75 John F. Jones
Additionally we would like to be able to print payroll information from data in a different file. The data is the
employee’s id number and a number of hours that they worked (example):
17 40
18 20
18 20
As you see we can have the same number listed twice in which case that person should be paid the sum of the numbers
(John Jones did 40 hours work, but it’s listed as 20+20).
You should start by reading in the first file and storing the data as objects in a linked list. You will need to create
the linked list class and the Employee data class. You may choose to use the Linked List class we created, or you may
opt to create your own doubly linked list class. (Note: if you cannot get either working, you can use the STL list class
but 20% will be deducted). The Linked list could be templated or not, it’s up to you, however templating it would allow
it to be used for other projects, so it might be a good idea.
Once you have read in the information from the first file, read in the second file. Ultimately we would like to print
payroll information based on the hourly wage from the first file multiplied by the number of times an employee worked in
the second file. How you do this is entirely up to you.
The output must be in sorted (descending; so the person who gets paid most prints first) order in the form of:
*********Payroll Information********
Daniel Katz, $270
John F. Jones, $210
*********End payroll**************
* */

// 1. Create Employee Data Class*
// 2. create the linked list class.
// 3. Create 1st file: id number, hourly pay rate, and the employee’s full name*
// 4. Create 2nd file: employee’s id number and a number of hours that they worked*
// 5. start by reading in the first file and storing the data as objects in a linked list
// 6. read in the information from the first file---houly wage, store the data as objects in a linked list
// 7. read in the second file---Number of hours an employee worked,store the data as objects in a linked list
// 8. Calculate payroll information based on the hourly wage from the first file multiplied by the number of times an
// employee worked in the second file.
// 9. The output must be in sorted (descending; so the person who gets paid most prints first) order in the form of:
// *********Payroll Information********
// Daniel Katz, $270
// John F. Jones, $210
// *********End payroll**************

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

// *******Employee Data Class**********
class Employee
{

private:
    int id;
    string name;
    double hourlywage;
    vector<int> workhour;

public:
    Employee(int id, string name, double hourlywage, vector<int> workhour)
        : id{ id }
        , name{ name }
        , hourlywage{ hourlywage }
        , workhour{ workhour }
    {
    }
    Employee()
        : Employee(0, "Annonimous", 0, {}){};

    void set_id(int setid)
    {
        id = setid;
    }
    int get_id()
    {
        return id;
    }
    void set_name(string setname)
    {
        name = setname;
    }
    string get_name()
    {
        return name;
    }
    void set_hourlywage(double sethourlywage)
    {
        hourlywage = sethourlywage;
    }
    double get_hourlywage()
    {
        return hourlywage;
    }
    void set_workhour()
    {
        int setworkhour;
        cout << "Enter each day's work hour and end by entering '-1': " << endl;
        while(setworkhour > -1) {
            cin >> setworkhour;
            workhour.push_back(setworkhour);
        }
    }
    vector<int> get_workhour()
    {
        return workhour;
    }
};

// ********Linked List Object**********

namespace linkedEmployeeList
{
class EmNode
{
private:
    int EmID;
    string EmName;
    double EmHourlyWage;
    int EmWorkHour;
    double EmTotalWage;
    EmNode* Emlink;

public:
    EmNode()
        : EmID(0)
        , EmName("Annoymous")
        , EmHourlyWage(0)
        , EmWorkHour(0)
        , Emlink(NULL)
    {
        EmTotalWage = 0;
    }
    EmNode(int ID, string Name, double HourlyWage = 0, int WorkHour = 0, EmNode* Emnext = NULL)
        : EmID(ID)
        , EmName(Name)
        , EmHourlyWage(HourlyWage)
        , EmWorkHour(WorkHour)
        , Emlink(Emnext)
    {
        EmTotalWage = 0;
    }

    void setID(int ID)
    {
        EmID = ID;
    }
    int getID() const
    {
        return EmID;
    }
    void setName(string Name)
    {
        EmName = Name;
    }
    string getName() const
    {
        return EmName;
    }
    void setHourlyWage(double HourlyWage)
    {
        EmHourlyWage = HourlyWage;
    }
    double getHourlyWage() const
    {
        return EmHourlyWage;
    }
    void setWorkHour(int workhour)
    {
        EmWorkHour = workhour;
    }
    int getWorkHour() const
    {
        return EmWorkHour;
    }

    void setTotalWage(double HourlyWage, int workhour)
    {
        EmTotalWage = HourlyWage * workhour;
    }

    double getTotalWage() const
    {
        return EmTotalWage;
    }

    void setLink(EmNode* next)
    {
        Emlink = next;
    }
    EmNode* getLink() const
    {
        return Emlink;
    }
};
typedef EmNode* EmNodePtr;
}

using namespace linkedEmployeeList;
// insert a new EmNode onto the head of the list
void Emhead_insert(EmNodePtr& Emhead, int ID, string Name, double HourlyWage, int WorkHour)
{
    EmNodePtr tempPtr = new EmNode(ID, Name, HourlyWage, WorkHour, Emhead);
    Emhead = tempPtr;
}

// Seach a specific employee by ID in the linked list
EmNodePtr search(EmNodePtr Emhead, int targetID)
{
    EmNodePtr here = Emhead;
    if(here == NULL) {
        return NULL;
    } else {
        while(here->getID() != targetID && here->getLink() != NULL) {
            here = here->getLink();
            if(here->getID() == targetID) {
                return here;
            } else {
                return NULL;
            }
        }
    }
}

// ************Create file for Employee Personal Information**************
void EmployeeInfo(ofstream& EmployeeInfoFile, Employee EmployeeData)
{
    EmployeeInfoFile << EmployeeData.get_id() << ' ' << EmployeeData.get_hourlywage() << ' ' << EmployeeData.get_name()
                     << endl;
}

void open_EmployeeInfo(ofstream& EmployeeInfoFile)
{
    string EmDataFName;
    cout << "Please enter the Employee Data File Name (.txt file) you want to create/add data on:: "
         << endl; // input the name of the employee data file
    cin >> EmDataFName;
    cout << "Opening " << EmDataFName << " for appending.\n";
    EmployeeInfoFile.open(
        EmDataFName, ios::app); // opening the employee data file. If not already exist, will create a new one
    if(EmployeeInfoFile.fail()) {
        cout << "Employee Data File openning failed.\n";
        exit(1);
    }
}

// ***********Create file for Employee Payroll Information************
// Add Employee Payroll Function
void EmployeePayroll(ofstream& EmployeePayrollFile, Employee EmployeeData)
{
    vector<int> EmWorkHour = EmployeeData.get_workhour();

    for(auto v : EmWorkHour) {
        EmployeePayrollFile << EmployeeData.get_id() << ' ' << v << endl;
    }
}
// Create or open employee payroll function
void open_EmployeePayroll(ofstream& EmployeePayrollFile)
{
    string EmPayrollFile;
    cout << "Please enter the Employee Payroll File Name (.txt file) you want to create/add data on: "
         << endl; // input the name of the employee data file
    cin >> EmPayrollFile;
    cout << "Opening " << EmPayrollFile << " for appending.\n";
    EmployeePayrollFile.open(
        EmPayrollFile, ios::app); // opening the employee data file. If not already exist, will create a new one
    if(EmployeePayrollFile.fail()) {
        cout << "Employee Payroll File openning failed.\n";
        exit(1);
    }
}

// *******Open File***********
void openEmDataFile(ifstream& File)
{
    string filename;
    cout << "Please enter the Employee Data Filename for openning:" << endl;
    cin >> filename;
    File.open(filename);
    while(!File) {
        cout << "File Failed to Open." << endl;
        cout << "Please enter the Employee Data Filename for openning:";
        cin >> filename;
        File.clear();
        File.open(filename);
    }
}

void openEmPayrollFile(ifstream& File)
{
    string filename;
    cout << "Please enter the Employee Payroll Filename for openning:" << endl;
    cin >> filename;
    File.open(filename);
    while(!File) {
        cout << "File Failed to Open." << endl;
        cout << "Please enter the Employee Payroll Filename for openning:";
        cin >> filename;
        File.clear();
        File.open(filename);
    }
}

// *********Read in File Information as Listed Link
void readEmDataFile(ifstream& File, EmNodePtr& EmHead)
{
    bool firstEmNode = true;
    int nextdata;

    while(File >> nextdata) {
        int id = nextdata;
        double hourlywage;
        string name;

        File >> hourlywage;
        getline(File, name);

        if(firstEmNode == true) {
            EmHead = new EmNode(id, name, hourlywage, 0, NULL);
            firstEmNode = false;
        } else {
            Emhead_insert(EmHead, id, name, hourlywage, 0);
        }
    }
    cout << "End of the Employee Info Data file." << endl;
}
// Need to have already run readEmInfoDatafile() for this to run smoothly.
void readEmPayrollFile(ifstream& File, EmNodePtr& EmHead)
{
    int nextid;
    // bool firstEmNode = true;
    while(File >> nextid) {
        int id = nextid;
        int workhour;
        int tempWorkHour;
        File >> workhour;

        for(EmNodePtr i = EmHead; i != NULL; i = i->getLink()) {
            if(i->getID() == id) {
                tempWorkHour = i->getWorkHour();
                tempWorkHour += workhour;
                i->setWorkHour(tempWorkHour);
            }
        }
    }
    cout << "End of the Employee Payroll Data file." << endl;
}

//

// ******Output******
// Sorting: ID and Total Wage List size needs to be the same and the ID and their according wage needs to be
// in the same position in differnet vector
int findIndexOfMax(vector<double> v, int low, int high)
{
    int Max, MaxInd, i;
    Max = v[low];
    MaxInd = low;
    for(i = low + 1; i <= high; i++) {
        if(v[i] > Max) {
            // cout<<v[i];
            // cout<<Max;
            Max = v[i];
            MaxInd = i;
        }
    }
    return MaxInd;
}

void swap(int& i, int& j)
{
    int temp = i;
    i = j;
    j = temp;
}

void selectionSort(vector<double>& v1, vector<int>& v2)
{
    int MaxInd;
    for(int x = 0; x < v1.size(); x++) {
        MaxInd = findIndexOfMax(v1, x, v1.size() - 1);
        swap(v1[x], v1[MaxInd]);
        swap(v2[x], v2[MaxInd]);
    }
}
void CalculateEmTotalWage(vector<double>& EmTotalWagelist, vector<int>& EmIDlist, EmNodePtr EmListHead)
{
    for(EmNodePtr i = EmListHead; i != NULL; i = i->getLink()) {
        // Calculate total wage for each employee, store in the linked node list
        i->setTotalWage(i->getHourlyWage(), i->getWorkHour());
        int id = i->getID();
        double totalwage = i->getTotalWage();
        // store ID in one vector
        EmIDlist.push_back(id);
        // store their coresponding total wage in another vector
        EmTotalWagelist.push_back(totalwage);
    }
}

// sort Employee total wage in decending order and arrange their ID as well
void SortEmTotalWage(vector<double> EmTotalWagelist,
    vector<int> EmIDlist,
    vector<string>& EmNameList,
    EmNodePtr EmListHead)
{

    selectionSort(EmTotalWagelist, EmIDlist);
    
    for(auto v : EmIDlist) {
        for(EmNodePtr i = EmListHead; i != NULL; i = i->getLink()) {
            if(i->getID() == v) {
                string name = i->getName();
                EmNameList.push_back(name);
            }
        }
    }
}

// Print

// print money:
// out_stream.setf(ios::fixed); //floating number are not written in e-notification
// out_stream.setf(ios::showpoint); //show decimal point and trailing zeros for floating point numbers
// out_stream.precision(2); //significant digit is 2

int main()
{
    /*
    ofstream EmployeeInfoFile, EmployeePayrollFile;

    // *******Creating Employee Data Class**************
    vector<Employee> EmData{ Employee(17, "Daniel Katz", 5.25, { 40 }),
        Employee(18, "John F. Jones", 6.75, { 20, 20 }) };

    // *******Creating Employee Data Files**************
    open_EmployeeInfo(EmployeeInfoFile);
    open_EmployeePayroll(EmployeePayrollFile);

    // *******Entering Employee Data********************
    for(auto v : EmData) {
        EmployeeInfo(EmployeeInfoFile, v);
        EmployeePayroll(EmployeePayrollFile, v);
    }
    // *******Closing Employee Data Files***************
    EmployeeInfoFile.close();
    EmployeePayrollFile.close();
     */

    // *********Inputing Employee Data File*********
    ifstream EmInfoData, EmPayroll;
    EmNodePtr EmListHead;

    // Read and Link Employee Info Data
    openEmDataFile(EmInfoData);
    readEmDataFile(EmInfoData, EmListHead);

    // Read and Link Employee Payroll Data
    openEmPayrollFile(EmPayroll);
    readEmPayrollFile(EmPayroll, EmListHead);

    vector<int> EmIDlist;
    vector<double> EmTotalWagelist;
    vector<string> EmNameList;

    //calculate total wage and store in their linked list
    CalculateEmTotalWage(EmTotalWagelist, EmIDlist, EmListHead);
    // sort Employee total wage in decending order and arrange their ID as well
    SortEmTotalWage(EmTotalWagelist, EmIDlist, EmNameList,EmListHead);
    


    // Print Payroll Information
    cout << "*********Payroll Information********" << endl;
    for(int i = 0; i < EmNameList.size(); i++) {
        cout << EmNameList[i] << ", $" << EmTotalWagelist[i] << endl;
    }
    cout << "*********End payroll**************" << endl;

    return 0;
}
