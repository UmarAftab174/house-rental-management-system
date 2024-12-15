#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<filesystem>
using namespace std;
struct adminData {
	string fullName;
	string CNIC;
	string cellNumber;
	string username;
	string password;
};
struct userData {
	string fullName;
	string CNIC;
	string cellNumber;
	string password;
};
struct houseData {
	string ID;
	string houseNumber;
	string location;
	string size;
	string price;
	string availability;
};
void admin();
void adminOps();
void user();
void searchHouse(const string& CNIC);
void rentHouse(const string& filepath, const string& oldstatus, const string&
	newstatus, const string& CNIC, const string& period);
void returnHouse(const string& CNIC);
void cancelHouse(const string& filepath, const string& oldstatus, const string&
	newstatus, const string& CNIC, const string& period);
string seq_id_gen();
int main()
{
	cout << "\n";
	cout << "\n\tWelcome to House Rental System" << endl;
	cout << "\nEnter your choice (1: Admin, 2: User, 3: Exit): ";
	int option;
	cin >> option;
	switch (option)
	{
	case 1:
		admin();
		break;
	case 2:
		user();
		break;
	case 3:
		break;
	default:
		cout << "\n\tWrong Choice!";
		break;
	}
	return 0;
}
string seq_id_gen() {
	const string idFilePath = "./Data/fileid.txt";
	int lastAssignedId = 000;
	ifstream lastID(idFilePath);
	if (lastID.is_open()) {
		lastID >> lastAssignedId;
		lastID.close();
	}
	int Id = lastAssignedId + 1;
	ofstream newID(idFilePath, ios::out | ios::trunc);
	if (newID.is_open()) {
		newID << Id;
		newID.close();
	}
	else {
		cout << "\n\tError updating new ID!!!";
	}
	return to_string(Id);
}
void admin() {
	ifstream fileCheck("./Data/AdminData.txt");
	if (fileCheck.is_open()) {
		string line, file_data, uname, pass;
		cout << "Enter username: ";
		cin >> uname;
		for (int i = 0; i < uname.length(); i++) {
			uname[i] = tolower(uname[i]);
		}
		cout << "Enter Password: ";
		cin >> pass;
		for (int i = 0; i < pass.length(); i++) {
			pass[i] = tolower(pass[i]);
		}
		while (getline(fileCheck, line)) {
			file_data += line + "\n";
		}
		size_t check_name = file_data.find(uname);
		size_t check_pass = file_data.find(pass);
		if (check_name != string::npos && check_pass != string::npos) {
			if (file_data.substr(check_name, uname.size()) == uname &&
				file_data.substr(check_pass, pass.size()) == pass) {
				//system("cls");
				cout << "\n\tWelcome Back" << endl;
				adminOps();
			}
		}
		else {
			cout << "\n\tInvalid Username or Password" << endl;
		}
	}
	else {
		adminData adminInfo;
		cout << "Enter Data for Registration" << endl;
		string firstname, lastname;
		cout << "Enter First Name: ";
		cin >> firstname;
		cout << "Enter Last Name: ";
		cin >> lastname;
		adminInfo.fullName = firstname.append(lastname);
		adminInfo.fullName.insert(adminInfo.fullName.find(lastname), " ");
		for (int i = 0; i < adminInfo.fullName.length(); i++) {
			adminInfo.fullName[i] = toupper(adminInfo.fullName[i]);
		}
		cout << "Enter CNIC Number: ";
		cin >> adminInfo.CNIC;
		for (int i = 0; i < 13; i++) {
			if (adminInfo.CNIC.length() != 13 ||
				!isdigit(adminInfo.CNIC[i])) {
				cout << "\n\tWrong Input\n";
				cout << "Enter your CNIC number again: ";
				getline(cin, adminInfo.CNIC);
				i = -1;
			}
		}
		adminInfo.CNIC.insert(5, "-");
		adminInfo.CNIC.insert(13, "-");
		cout << "Enter your cell number: ";
		cin >> adminInfo.cellNumber;
		for (int i = 0; i < 11; i++) {
			if (adminInfo.cellNumber.length() != 11 ||
				!isdigit(adminInfo.cellNumber[i])) {
				cout << "\n\tWrong Input\n";
				cout << "Enter your number again: ";
				cin >> adminInfo.cellNumber;
				i = -1;
			}
		}
		cout << "Enter Username: ";
		cin >> adminInfo.username;
		for (int i = 0; i < adminInfo.username.length(); i++) {
			adminInfo.username[i] = tolower(adminInfo.username[i]);
		}
		cout << "Enter Password: ";
		cin >> adminInfo.password;
		for (int i = 0; i < adminInfo.password.length(); i++) {
			adminInfo.password[i] = tolower(adminInfo.password[i]);
		}
		filesystem::create_directories("./Data");
		ofstream AdminData;
		AdminData.open("./Data/AdminData.txt", ios::out);
		if (!AdminData.is_open()) {
			cout << "\n\tError!!!" << endl;
		}
		else {
			AdminData << adminInfo.fullName << endl;
			AdminData << adminInfo.CNIC << endl;
			AdminData << adminInfo.cellNumber << endl;
			AdminData << adminInfo.username << endl;
			AdminData << adminInfo.password << endl;
			cout << "\n\tRegisteration Successful" << endl;
			AdminData.close();
		}
		adminOps();
	}
}
void adminOps() {
	cout << "Choose operation do you want to perform" << endl;
	cout << "1: Add House in Inventory, 2: View Houses Inventory, 3: Delete from Inventory" << endl;
		cout << "Choice: ";
	int choice;
	cin >> choice;
	do {
		houseData houseInfo;
		if (choice == 1) {
			houseInfo.ID = seq_id_gen();
			cout << "Enter house number: ";
			cin >> houseInfo.houseNumber;
			cin.ignore();
			for (int i = 0; i < houseInfo.houseNumber.length(); i++) {
				houseInfo.houseNumber[i] =
					toupper(houseInfo.houseNumber[i]);
			}
			cout << "Enter location of house: ";
			getline(cin, houseInfo.location);
			for (int i = 0; i < houseInfo.location.length(); i++) {
				houseInfo.location[i] = toupper(houseInfo.location[i]);
			}
			cout << "Enter size of house in letters: ";
			getline(cin, houseInfo.size);
			houseInfo.size = houseInfo.size + " Sqr yards";
			for (int i = 0; i < houseInfo.size.length(); i++) {
				houseInfo.size[i] = toupper(houseInfo.size[i]);
			}
			cout << "Enter price of rent per month: ";
			cin >> houseInfo.price;
			houseInfo.price = "Rs. " + houseInfo.price + " Per Month";
			houseInfo.availability = "Available";
			ofstream HouseData;
			string fileName = houseInfo.ID + "_" + houseInfo.houseNumber +
				".txt";
			string filePath = "./Data/House/";
			string fullPath = filePath + fileName;
			filesystem::create_directories(filePath);
			HouseData.open(fullPath, ios::out);
			if (!HouseData.is_open()) {
				cout << "\n\tError" << endl;
			}
			else {
				HouseData << houseInfo.ID << " | ";
				HouseData << houseInfo.houseNumber << " | ";
				HouseData << houseInfo.location << " | ";
				HouseData << houseInfo.size << " | ";
				HouseData << houseInfo.price << " | ";
				HouseData << houseInfo.availability;
				cout << "\n\tSuccessfully added house in inventory" <<
					endl;
				HouseData.close();
			}
		}
		else if (choice == 2) {
			vector<string>filepath;
			vector<string>filedata;
			string path = "./Data/House/";
			string housedata;
			if (filesystem::exists(path) && filesystem::is_directory(path))
			{
				for (const auto& entry :
					filesystem::directory_iterator(path)) {
					string fpath = path +
						entry.path().filename().string();
					filepath.push_back(fpath);
					ifstream read(fpath);
					if (read.is_open()) {
						getline(read, housedata);
						filedata.push_back(housedata);
					}
				}
			}
			else {
				cout << "\n\tOops System Down!";
			}
			cout << "\t\tHouses in Inventory" << endl;
			for (const auto& file : filedata) {
				cout << file << endl;
			}
		}
		else if (choice == 3) {
			vector<string>filepath;
			vector<string>filedata;
			string path = "./Data/House/";
			string housedata;
			if (filesystem::exists(path) && filesystem::is_directory(path))
			{
				for (const auto& entry :
					filesystem::directory_iterator(path)) {
					string fpath = path +
						entry.path().filename().string();
					filepath.push_back(fpath);
					ifstream read(fpath);
					if (read.is_open()) {
						getline(read, housedata);
						filedata.push_back(housedata);
					}
				}
			}
			else {
				cout << "\n\tOops System Down!";
			}
			cout << "\nList of Houses" << endl;
			string id, address;
			cout << "Enter ID of house to delete: ";
			cin >> id;
			cout << "Enter address of house to delete: ";
			cin >> address;
			string fname = id + "_" + address;
			for (int i = 0; i < fname.length(); i++) {
				fname[i] = toupper(fname[i]);
			}
			for (const auto& file : filepath) {
				size_t check_name = file.find(fname);
				if (check_name != string::npos) {
					if (file.substr(check_name, fname.size()) == fname)
					{
						string fullFilename = "./Data/House/" + fname
							+ ".txt";
						if (filesystem::exists(fullFilename)) {
							if (filesystem::remove(fullFilename))
							{
								cout << "\n\t" << address << " deleted from inventory successfully." << std::endl;
							}
							else {
								cout << "\n\tError in record!!!" << endl;
							}
						}
						else {
							cout << "\n\tData of house does exist!!!" << endl;
						}
					}
				}
			}
		}
		else {
			cout << "\n\tWrong Choice" << endl;
		}
		//system("cls");
		cout << "Choose operation do you want to perform again" << endl;
		cout << "1: Add House in Inventory, 2: View Houses Inventory, 3: House from Inventory, 4: Exit" << endl;
			cout << "Choice: ";
		cin >> choice;
		system("cls");
	} while (choice == 1 || choice == 2 || choice == 3);
}
void user() {
	vector<string>filepath;
	vector<string>filedata;
	string path = "./Data/User/";
	string userdata;
	if (filesystem::exists(path) && filesystem::is_directory(path)) {
		for (const auto& entry : filesystem::directory_iterator(path)) {
			string fpath = path + entry.path().filename().string();
			filepath.push_back(fpath);
			ifstream read(fpath);
			if (read.is_open()) {
				getline(read, userdata);
				filedata.push_back(userdata);
			}
		}
	}
	cout << "Do you have an account (Y/N): ";
	char choice;
	cin >> choice;
	if (choice == 'Y' || choice == 'y') {
		cout << "Enter CNIC: ";
		string CNIC, pass;
		cin >> CNIC;
		cin.ignore();
		for (int i = 0; i < 13; i++) {
			if (CNIC.length() != 13 || !isdigit(CNIC[i])) {
				cout << "\n\tWrong Input\n";
				cout << "\tEnter your CNIC number again: ";
				getline(cin, CNIC);
				i = -1;
			}
		}
		CNIC.insert(5, "-");
		CNIC.insert(13, "-");
		for (const auto& path : filepath) {
			size_t check_cnic = path.find(CNIC);
			if (check_cnic != string::npos) {
				if (path.substr(check_cnic, CNIC.size()) == CNIC) {
					ifstream read(path);
					string userfiledata;
					getline(read, userfiledata);
					cout << "Enter Password: ";
					cin >> pass;
					for (int i = 0; i < pass.length(); i++) {
						pass[i] = tolower(pass[i]);
					}
					cin.ignore();
					size_t check_pass = userfiledata.find(pass);
					if (check_pass != string::npos) {
						if (userfiledata.substr(check_pass,
							pass.size()) == pass) {
							system("cls");
							cout << "\n\tWelcome Back" << endl;
							cout << "Do you want to (1: Rent house, 2: Cancel reservation, 3 : Exit): ";
								int option;
							cin >> option;
							switch (option)
							{
							case 1:
								searchHouse(CNIC);
								break;
							case 2:
								returnHouse(CNIC);
								break;
							default:
								break;
							}
						}
					}
				}
			}
		}
	}
	else if (choice == 'N' || choice == 'n') {
		userData userInfo;
		cout << "Enter Data for Registration" << endl;
		string firstname, lastname;
		cout << "Enter First Name: ";
		cin >> firstname;
		cin.ignore();
		cout << "Enter Last Name: ";
		cin >> lastname;
		cin.ignore();
		userInfo.fullName = firstname.append(lastname);
		userInfo.fullName.insert(userInfo.fullName.find(lastname), " ");
		for (int i = 0; i < userInfo.fullName.length(); i++) {
			userInfo.fullName[i] = toupper(userInfo.fullName[i]);
		}
		cout << "Enter CNIC Number: ";
		cin >> userInfo.CNIC;
		for (int i = 0; i < 13; i++) {
			if (userInfo.CNIC.length() != 13 || !isdigit(userInfo.CNIC[i]))
			{
				cout << "\n\tWrong Input\n";
				cout << "\tEnter your CNIC number again: ";
				getline(cin, userInfo.CNIC);
				i = -1;
			}
		}
		userInfo.CNIC.insert(5, "-");
		userInfo.CNIC.insert(13, "-");
		cout << "Enter your cell number: ";
		cin >> userInfo.cellNumber;
		for (int i = 0; i < 11; i++) {
			if (userInfo.cellNumber.length() != 11 ||
				!isdigit(userInfo.cellNumber[i])) {
				cout << "\n\tWrong Input\n";
				cout << "Enter your number again: ";
				cin >> userInfo.cellNumber;
				i = -1;
			}
		}
		cout << "Enter Password: ";
		cin >> userInfo.password;
		for (int i = 0; i < userInfo.password.length(); i++) {
			userInfo.password[i] = tolower(userInfo.password[i]);
		}
		ofstream UserData;
		string fileName = userInfo.CNIC + ".txt";
		string filePath = "./Data/User/";
		string fullPath = filePath + fileName;
		filesystem::create_directories(filePath);
		UserData.open(fullPath, ios::out);
		if (!UserData.is_open()) {
			cout << "\n\tError!!!" << endl;
		}
		else {
			UserData << userInfo.fullName << " | ";
			UserData << userInfo.CNIC << " | ";
			UserData << userInfo.cellNumber << " | ";
			UserData << userInfo.password;
			cout << "\n\tRegisteration Successful" << endl;
			UserData.close();
		}
		searchHouse(userInfo.CNIC);
}
	else {
		cout << "\n\tWrong Choice!!!";
}
}
void searchHouse(const string& CNIC) {
	vector<string>filepath;
	vector<string>filedata;
	string path = "./Data/House/";
	string userdata;
	if (filesystem::exists(path) && filesystem::is_directory(path)) {
		for (const auto& entry : filesystem::directory_iterator(path)) {
			string fpath = path + entry.path().filename().string();
			filepath.push_back(fpath);
			ifstream read(fpath);
			if (read.is_open()) {
				getline(read, userdata);
				filedata.push_back(userdata);
			}
		}
	}
	else {
		cout << "\n\tOops System Down!";
	}
	cout << "Do you want to search houses using filters? (Y/N): ";
	char choice;
	cin >> choice;
	cin.ignore();
	if (choice == 'Y' || choice == 'y') {
		cout << "Apply filters using (1: Location, 2: Size): ";
		int option;
		cin >> option;
		cin.ignore();
		if (option == 1) {
			string location;
			cout << "Enter Location: ";
			getline(cin, location);
			for (int i = 0; i < location.length(); i++) {
				location[i] = toupper(location[i]);
			}
			cout << "\n\tHouses List" << endl;
			for (const auto& data : filedata) {
				size_t check_location = data.find(location);
				if (check_location != string::npos) {
					cout << data << endl;
				}
			}
		}
		else if (option == 2) {
			string size;
			cout << "Enter Size: ";
			getline(cin, size);
			size = size + "-sqr-yards";
			for (int i = 0; i < size.length(); i++) {
				size[i] = toupper(size[i]);
			}
			cout << "\n\tHouses List" << endl;
			for (const auto& data : filedata) {
				size_t check_size = data.find(size);
				if (check_size != string::npos) {
					cout << data << endl;
				}
			}
		}
		else {
			cout << "\n\tWrong Choice";
		}
	}
	else if (choice == 'N' || choice == 'n') {
		cout << "Houses List" << endl;
		for (const auto& data : filedata) {
			cout << data << endl;
		}
	}
	else {
		cout << "\n\tWrong Choice!!!";
	}
	string ID, houseNumber;
	cout << "Enter ID of house you want to rent: ";
	cin >> ID;
	cin.ignore();
	cout << "Enter House Number: ";
	cin >> houseNumber;
	cin.ignore();
	for (int i = 0; i < houseNumber.length(); i++) {
		houseNumber[i] = toupper(houseNumber[i]);
	}
	string filename = "./Data/House/" + ID + "_" + houseNumber + ".txt";
	ifstream read(filename);
	string fdata;
	if (read.is_open()) {
		getline(read, fdata);
		cout << fdata << endl;
		read.close();
		cout << "For how many months(in letters) you want to book house: ";
		string period;
		cin >> period;
		period = period + " months";
		cout << "\nDo you want conform booking? (Y/N): ";
		char ch;
		cin >> ch;
		cin.ignore();
		if (ch == 'Y' || ch == 'y') {
			string oldstatus = "Available";
			string newstatus = "Rented";
			rentHouse(filename, oldstatus, newstatus, CNIC, period);
		}
		else {
			cout << "See you next time!!!";
		}
	}
	else {
		cout << "\n\tUnable to open file!!!";
	}
}
void rentHouse(const string& filepath, const string& oldstatus, const string&
	newstatus, const string& CNIC, const string& period) {
	ifstream read(filepath);
	string fileread;
	if (read.is_open()) {
		getline(read, fileread);
		cout << "File content: " << fileread << endl;
		read.close();
	}
	else {
		cout << "\n\tError in renting house!!!";
	}
	size_t check_newstatus = fileread.find(newstatus);
	if (check_newstatus != string::npos) {
		if (fileread.substr(check_newstatus, newstatus.size()) == newstatus) {
			cout << "\n\tHouse already rented!!!";
		}
	}
	else {
		size_t check_oldstatus = fileread.find(oldstatus);
		fileread.replace(check_oldstatus, 9, newstatus);
		fileread = fileread + " | " + CNIC + " | " + period;
		ofstream write(filepath, ios::out);
		if (write.is_open()) {
			write << fileread << endl;
			cout << "\n\tHouse rented successfully";
		}
		else {
			cout << "\n\tError in renting house!!!";
		}
	}
}
void returnHouse(const string& CNIC) {
	vector<string>filepath;
	vector<string>filedata;
	string path = "./Data/House/";
	string userdata;
	if (filesystem::exists(path) && filesystem::is_directory(path)) {
		for (const auto& entry : filesystem::directory_iterator(path)) {
			string fpath = path + entry.path().filename().string();
			filepath.push_back(fpath);
			ifstream read(fpath);
			if (read.is_open()) {
				getline(read, userdata);
				filedata.push_back(userdata);
			}
		}
	}
	else {
		cout << "\n\tOops System Down!";
	}
	system("cls");
	string ID, houseNumber;
	cout << "Enter ID of house you want to cancel reservation: ";
	cin >> ID;
	cin.ignore();
	cout << "Enter House Number: ";
	cin >> houseNumber;
	cin.ignore();
	for (int i = 0; i < houseNumber.length(); i++) {
		houseNumber[i] = toupper(houseNumber[i]);
	}
	string filename = "./Data/House/" + ID + "_" + houseNumber + ".txt";
	ifstream read(filename);
	string fdata;
	if (read.is_open()) {
		getline(read, fdata);
		cout << fdata << endl;
		read.close();
		cout << "For how many months(in letters) you had been rented house: ";
		string period;
		cin >> period;
		period = period + " months";
		cout << "\nDo you want cancle reservation? (Y/N): ";
		char ch;
		cin >> ch;
		cin.ignore();
		if (ch == 'Y' || ch == 'y') {
			string oldstatus = "Rented";
			string newstatus = "Available";
			cancelHouse(filename, oldstatus, newstatus, CNIC, period);
		}
		else {
			cout << "See you next time!!!";
		}
	}
	else {
		cout << "\n\tUnable to open file!!!";
	}
}
void cancelHouse(const string& filepath, const string& oldstatus, const string&
	newstatus, const string& CNIC, const string& period) {
	ifstream read(filepath);
	string fileread;
	if (read.is_open()) {
		getline(read, fileread);
		cout << "File content: " << fileread << endl;
		read.close();
	}
	else {
		cout << "\n\tError in renting house!!!";
	}
	size_t check_newstatus = fileread.find(newstatus);
	if (check_newstatus != string::npos) {
		if (fileread.substr(check_newstatus, newstatus.size()) == newstatus) {
			cout << "\n\tHouse is not rented!!!";
		}
	}
	else {
		size_t check_oldstatus = fileread.find(oldstatus);
		fileread.replace(check_oldstatus, oldstatus.size(), newstatus);
		string temp1 = "| " + CNIC;
		string temp2 = " | " + period;
		size_t check_cnic = fileread.find(temp1);
		if (check_cnic != string::npos) {
			fileread.replace(check_cnic, temp1.size(), "");
		}
		size_t check_period = fileread.find(temp2);
		if (check_period != string::npos) {
			fileread.replace(check_period, temp2.size(), "");
		}
		ofstream write(filepath, ios::out);
		if (write.is_open()) {
			write << fileread << endl;
			cout << "\n\tHouse reservation cancelled successfully";
		}
		else {
			cout << "\n\tError in renting house!!!";
		}
	}
}