#include <iostream> 
#include <fstream> 
#include <string> 
#include <sstream> 
#include <vector> 
#include <stdexcept>
#include <cctype> 
using namespace std; 
namespace SmartUtil {
string toLower(string s) {
for (char &c : s) c = tolower(c); return 
s;
}
string trim(string s) {
size_t start = s.find_first_not_of(" "); 
size_t end = s.find_last_not_of(" "); 
if (start == string::npos) return ""; 
return s.substr(start, end - start + 1);
}
bool contains(string text, string word) { text
= toLower(text);
word = toLower(word);
return text.find(word) != string::npos;
}
int getPriority(string desc) { desc
= toLower(desc);
if (contains(desc, "urgent") || contains(desc, "critical")) 
return 1; else if (contains(desc, "repair") || 
contains(desc, "fix")) return 2;
else
return 3;
}
string suggestDeadline(int priority) {
if (priority == 1) return "1 Day (URGENT)";
else if (priority == 2) return "3 Days (MEDIUM)"; else 
return "7 Days (LOW)";
}
}
template <typename T> void 
showData(T data) {
cout << "Data: " << data << endl;
}
template <class T> 
class Report {
T value; 
public:
Report(T v) : value(v) {} void 
display() {
cout << "Report Value: " << value << endl;
}
};
void clearInput() { 
cin.clear(); 
cin.ignore(1000,
'\n');
}
bool login(string u, string p) { string 
user, pass;
cout << "Username: "; cin
>> user;
cout << "Password: "; cin
>> pass;
if (user == u && pass == p) { 
cout << "Login Successful\n"; 
return true;
}
cout << "Invalid Login\n"; return 
false;
}
void addTask(int id, string desc, string status, string role) { ofstream 
f("tasks.txt", ios::app);
if (!f) {
cout << "File Error\n"; return;
}
desc = SmartUtil::trim(desc);
status = SmartUtil::toLower(status);
int priority = SmartUtil::getPriority(desc);
string deadline = SmartUtil::suggestDeadline(priority); 
f << id << "," << desc << "," << status << "," << role
<< "," << priority << "," << deadline << endl;
cout << "Task Added with Deadline: " << deadline << endl;
}
void viewTasks() { ifstream 
f("tasks.txt");
if (!f) {
cout << "No tasks found\n"; return;
}
string line;
cout << "\n--- ALL TASKS ---\n";
while (getline(f, line)) { 
cout << line << endl;
}
}
void searchTaskByKeyword(string keyword) { ifstream 
f("tasks.txt");
if (!f) {
cout << "No tasks found\n"; return;
}
string line;
bool found = false;
cout << "\n--- SEARCH RESULTS ---\n";
while (getline(f, line)) {
if (SmartUtil::contains(line, keyword)) { cout
<< line << endl; 
found = true;
}
}
if (!found)
cout << "No matching tasks found!\n";
}
void viewTasks(int tid)
{
ifstream f("tasks.txt");
if (!f)
{
cout << "File not found\n"; return;
}
string line, desc, status, role, priority, deadline; int 
id;
cout << "\n--- SEARCH TASK ---\n";
while (getline(f, line)) { stringstream 
ss(line);
string temp; 
getline(ss, temp,
',');
try {
id = stoi(temp);
}
catch (...)
{
continue;
}
getline(ss, desc, ',');
getline(ss, status, ',');
getline(ss, role, ',');
getline(ss, priority, ','); getline(ss, 
deadline);
if (id == tid) {
cout << id << " | " << desc << " | " << status
<< " | " << role
<< " | Priority: " << priority
<< " | Deadline: " << deadline << endl; return;
}
}
cout << "Task not found!\n";
}

void viewTasksByRole(string role)
{
ifstream f("tasks.txt");
if (!f)
{
cout << "File not found\n"; 
return;
}
string line, desc,status, r, priority, deadline; int 
id;
cout << "\n--- YOUR TASKS ---\n";
while (getline(f, line))
{
stringstream ss(line);
string temp; 
getline(ss, temp,
',');
try
{
id = stoi(temp);
}
catch (...) { 
continue;
}
getline(ss, desc, ',');
getline(ss, status, ',');
getline(ss, r, ','); getline(ss,
priority, ','); getline(ss, 
deadline);
if (r == role)
{
cout << id << " | " << desc << " | " << status
<< " | Priority: " << priority
<< " | Deadline: " << deadline << endl;
}
}
}
void updateTask(int tid,string newStatus) { ifstream 
fin("tasks.txt");
if (!fin)
{
cout << "File not found\n"; return;
}
vector<string> tasks;
string line, desc, status, role, priority, deadline; int 
id;
while (getline(fin, line))
{
stringstream ss(line); string temp; 
getline(ss, temp, ',');
try
{
id = stoi(temp);
}
catch (...)
{
continue;
}
getline(ss, desc, ',');
getline(ss, status, ',');
getline(ss, role, ',');
getline(ss, priority, ','); getline(ss, 
deadline);
if (id == tid)
tasks.push_back(to_string(id) + "," + desc + "," + 
SmartUtil::toLower(newStatus) + "," + 
role + "," + priority + "," + deadline);
else
tasks.push_back(line);
}
fin.close(); 
ofstream
fout("tasks.txt"); for (auto 
t : tasks) fout << t << 
endl;
cout << "Task Updated!\n";
}
class Person
{
protected: 
int id;
string name; 
public:
Person(int i=0, string n="") : id(i), name(n) {}
virtual void display()
{
cout << "ID: " << id << " Name: " << name << endl;
}
virtual void projectOperation(string role, int floors, int units, double area) {}
};
class Worker : public Person
{
double
fees; int 
hours; 
string role;
public:
Worker(int i, string n, double f, int h, string r)
: Person(i,n), fees(f), hours(h), role(r) {} 
void display() override {
cout << "Worker: " << name << " Role: " << role << endl; Person* 
p = this;
p->projectOperation(role,10,40,20000);
}
void projectOperation(string role, int floors, int units, double area) override
{
cout << "\n[Worker Role Action]\n"; if (role=="Electrician") cout << "Wiring  for " << floors << " floors\n"; else if (role=="Plumber") cout << "Pipes for "
<< units << " units\n"; else if (role=="Carpenter") cout << "Wood work area:  " << area*0.3 << endl; else cout << "Cable setup: " << area*2 << endl;
}
string getRole()
{
return role;
}
void checkIn()
{
ofstream f("attendance.txt", ios::app); f
<< name << " (" << role << ") IN\n"; 
cout << "Checked IN\n";
}
void checkOut() {
ofstream f("attendance.txt", ios::app);
f << name << " (" << role << ") OUT\n"; cout
<< "Checked OUT\n";
}
void earnings()
{
cout << "Earnings: " << fees * hours << endl;
}
friend void showWorkerDetails(Worker w);
};
void showWorkerDetails(Worker w) { cout << "\n--- Worker Details ---\n"; cout << "Name: " <<
w.name << endl; cout << "Role: " << w.role << 
endl; cout << "Earnings: " << w.fees * w.hours << 
endl;
}
class Manager : public Person
{
double budget,spent; 
public:
Manager(int i, string n, double b): Person(i,n), budget(b), spent(0) {}
void display() override
{
cout << "Manager: " << name << endl; Person* 
p = this;
p->projectOperation("Manager",10,40,20000);
}
void projectOperation(string role, int floors, int units, double area) override { cout
<< "\n[Manager Planning]\n";
cout << "Estimated Cost: " << area * 1500 << endl;
}
void addExpense(double amt) { if 
(spent + amt > budget) cout << 
"Budget exceeded\n"; else {
spent += amt;
cout << "Remaining: " << budget - spent << endl;
}
}
};
class Customer : public Person
{
double total, paid; 
public:
Customer(int i, string n, double t)
: Person(i,n), total(t), paid(0) {}
void display() override
{
cout << "Customer: " << name << endl; Person* 
p = this;
p->projectOperation("Customer",10,40,20000);
}
void projectOperation(string role, int floors, int units, double area) override { cout
<< "\n[Customer View]\n";
cout << "Unit Price: " << (area/units)*2000 << endl;
}
void pay(double amt)
{
try {
if (amt <= 0) throw invalid_argument("Invalid amount");
int method;
cout << "1.UPI 2.Card 3.Cash\nEnter choice: "; cin
>> method;
if (method < 1 || method > 3)
throw runtime_error("Invalid method");
paid += amt;
cout << "Payment Done. Remaining: " << total - paid << endl;
}
catch (exception &e)
{
cout << e.what() << endl;
}
}
};
int main() { 
showData(100);
Report<string> r("Project"); 
r.display();
int choice;
while (true) {
cout << "\n===== MAIN MENU =====\n";
cout << "1.Manager\n2.Worker\n3.Customer\n4.Exit\n"; cout
<< "Enter choice: "; 
cin >> choice;
if (choice == 4) break; 
switch (choice)
{
case 1:
{
if (!login("manager","newpass123")) break; 
int id; string name; double budget;
cout << "Enter ID: "; cin >> id; clearInput(); 
cout << "Enter Name: "; getline(cin,name); 
cout << "Enter Budget: "; cin >> budget;
Manager m(id,name,budget); 
m.display();
int ch; do { cout << "\n1.Add Expense\n2.Add Task\n3.View Tasks\n4.Search  Task\n5.Search by Keyword\n6.Back\n";
cout << "Enter choice: "; cin
>> ch;
if (ch==1) { double amt; 
cout << "Enter amount: "; 
cin >> amt; 
m.addExpense(amt);
}
else if (ch==2)
{
int tid; string desc,status,role;
cout << "Task ID: "; cin >> tid; clearInput(); 
cout << "Description: "; getline(cin,desc); 
cout << "Status: "; getline(cin,status); cout
<< "Assign Role: "; getline(cin,role); 
addTask(tid,desc,status,role);
}
else if (ch==3) viewTasks(); else 
if (ch==4) {
int tid;
cout << "Enter Task ID: "; 
cin >> tid; 
viewTasks(tid);
}
else if (ch==5) { 
string key; 
clearInput(); 
getline(cin,
key);
searchTaskByKeyword(key);
}
} while (ch!=6); break;
}
case 2: {
if (!login("worker","worker@123")) break; 
int id; string name; cout << "Enter ID: "; cin
>> id; clearInput(); cout << "Enter Name: "; 
getline(cin,name);
int rc;
cout << "1.Electrician 2.Plumber 3.Carpenter 4.Wiring\n"; 
cout << "Enter choice: "; cin
>> rc; 
string role;
if (rc==1) role="Electrician"; 
else if (rc==2) role="Plumber"; 
else if (rc==3) 
role="Carpenter"; else 
role="Wiring";
double fees; int hrs;
cout << "Enter fees/hour: "; cin >> fees; cout
<< "Enter hours: "; cin >> hrs; 
Worker w(id,name,fees,hrs,role); 
w.display();
int ch; do
{
cout << "\n1.CheckIn\n2.CheckOut\n3.View My Tasks\n4.Update  Task\n5.Earnings\n6.Show Details\n7.Back\n";
cout << "Enter choice: "; cin
>> ch;
if (ch==1) w.checkIn();
else if (ch==2) w.checkOut();
else if (ch==3) viewTasksByRole(w.getRole()); else 
if (ch==4) {
int tid; string st;
cout << "Enter Task ID: "; cin >> tid; clearInput(); cout << 
"New Status: "; getline(cin,st); updateTask(tid,st);
}
else if (ch==5) w.earnings();
else if (ch==6) showWorkerDetails(w);
} while (ch!=7); break;
}
case 3: {
if (!login("customer","cust@123")) break; 
int id; string name; double total;
cout << "Enter ID: "; cin >> id; clearInput(); 
cout << "Enter Name: "; getline(cin,name); 
cout << "Enter Total Amount: "; cin >> total;
Customer c(id,name,total); 
c.display();
int ch; do { cout << "\n1.Make Payment\n2.View Tasks\n3.Back\n"; cout << "Enter choice: ";
cin >> ch;
if (ch==1) { double amt; 
cout << "Enter amount: "; 
cin >> amt;
c.pay(amt);
}
else if (ch==2) viewTasks();
} while (ch!=3);
}
}
}
}
