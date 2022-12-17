#include <string>
#include <iostream>
#include <filesystem>
#include <vector>

using namespace std;
namespace fs = std::filesystem;




int loginfunction() {

	bool login = true;
	string users[] = { "ahmed", "youssef", "omar", "mazen" };
	string passwords[] = { "pass1", "pass2", "pass3", "pass4" };
	string passenter;
	string userenter;
	int attempts = 0;

	while (login)
	{
		if (attempts >= 5) {
			cout << "\nYou have made too many attempts!\n";
			exit(0);
		}


		int locationuser = -1;
		int locationpass = -1;

		attempts++;

		cout << "\nenter username" << endl;
		cin >> userenter;
		cout << "enter password" << endl;
		cin >> passenter;


		for (int i = 0; i < 4; i++) {

			if (userenter == users[i]) {
				locationuser = i;
			}
		}


		if (locationuser == -1) {
			cout << "username or password incorrect." << endl;
			continue;
		}

		for (int i = 0; i < 4; i++) {

			if (passenter == passwords[i]) {
				locationpass = i;
			}
		}


		if (locationpass == -1) {
			cout << "username or password incorrect." << endl;
			continue;
		}

		if (locationuser == locationpass) {

			cout << "welcome!";
			return locationuser;
			break;

		}
		else {
			cout << "username or password incorrect." << endl;

		}



	}

}

void listsongs(vector <string>& songs) {

	string path;
	cout << "\n\nselect your music folder using path: ";
	cin >> path;
	char dot = '.';


	for (const auto& entry : fs::directory_iterator(path)) {
		string item = entry.path().string();
		item = item.substr(item.find_last_of("/\\") + 1);

		size_t found = item.find(dot);
		if (found > 1000000) {
			continue;
		}

		string ext = item.substr(item.find_last_of(".\\"));
		if (ext == ".zip" || ext == ".7z" || ext == ".rar") {
			cout << endl << item << endl;
			songs.push_back(entry.path().string());
		}

	}
}



int main() {
	vector<string> songs;
	/*____________________________ LOGIN FUNTION _______________________________*/

	int user = loginfunction();

	/*____________________________ LIST SONGS _______________________________*/

	listsongs(songs);

	/*______________________________ SAVE PATHS___________________________*/


	cout << "Output of vector:\n\n ";
	for (int i = 0; i < songs.size(); ++i) {
		cout << songs[i] << " " << endl;
	}


}

