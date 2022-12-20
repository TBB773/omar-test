#include <string>
#include <iostream>
#include <filesystem>
#include <vector>
#include <cstdlib>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include <winuser.h>
#pragma comment( lib, "winmm.lib" )
using namespace std;

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

		cout << "\nenter username: ";
		cin >> userenter;
		cout << "enter password: ";
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
		if (ext == ".wav" || ext == ".mp3") {
			cout << endl << item << endl;
			songs.push_back(entry.path().string());
		}

	}
}

string mcicommand(string path) {

	string command = "open type mpegvideo alias song";

	int found = command.find(" ");

	command = command.substr(0, found) + " " + path + command.substr(found);

	return command;

}



int main() {
	/*--------------------------------- APETIZERS --------------------------------*/
	vector<string> songs;
	int controller;
	string command;
	time_t t1{}, t2, previous_pause_time = 0;
	/*____________________________ LOGIN FUNTION _______________________________*/

	int user = loginfunction();

	/*____________________________ LIST SONGS _______________________________*/

	listsongs(songs);

	/*______________________________ PATHS___________________________*/

	//add a second backslash to all paths to avoid errors


	cout << "Output of vector:\n\n";
	for (int i = 0; i < songs.size(); ++i) {
		cout << songs[i] << " " << endl;
	}

	cout << "AND SIZE IS..." << songs.size() << endl;

	/*______________________________CHOOSE SONG___________________________*/

	int songnum;
	cout << "\n\nenter song number: ";
	cin >> songnum;

	if (songnum > songs.size()) {
		cout << "song number not found, track 1 chosen";
		songnum = 1;
	}

	songnum = songnum - 1;

	string song = songs[songnum];


	cout << "YOU CHOSE :   " << TEXT(song.c_str()) << endl;

	/*------------------------------PATH TO COMMAND--------------------------*/


	command = mcicommand(song);
	cout << command;


	/*------------------------------------------CONTROLS---------------------------------------------*/

	mciSendString(command.c_str(), NULL, 0, NULL);


	while (true) {
		cout << "\n\n\n\n" << " 1- play\n 2- stop\n 3- pause \n 4- resume \n 5- next \n 6- previous \n 7-Exit \n\n\n" << endl;
		cout << "enter your choice: ";
		cin >> controller;

		switch (controller) {
		case 1: //play
			mciSendString("play song", NULL, 0, NULL);
			t1 = time(nullptr);
			break;
		case 2: //stop
			mciSendString("close song", NULL, 0, NULL);
			mciSendString(command.c_str(), NULL, 0, NULL);
			break;
		case 3: //pause
			mciSendString("pause song", NULL, 0, NULL);
			t2 = time(nullptr);
			previous_pause_time += t2 - t1;
			break;
		case 4: //resume
			mciSendString("resume song", NULL, 0, NULL);
			t1 = time(nullptr);
			break;
		case 5: //next
			mciSendString("close song", NULL, 0, NULL);
			songnum++;
			if (songnum > songs.size() - 1) {
				songnum = 0;
			}
			song = songs[songnum];
			command = mcicommand(song);
			mciSendString(command.c_str(), NULL, 0, NULL);
			mciSendString("play song", NULL, 0, NULL);
			break;
		case 6: //previous
			mciSendString("close song", NULL, 0, NULL);
			songnum--;
			if (songnum < 0) {
				songnum = songs.size() - 1;
			}
			song = songs[songnum];
			command = mcicommand(song);
			mciSendString(command.c_str(), NULL, 0, NULL);
			mciSendString("play song", NULL, 0, NULL);
			break;
		case 7: //exit
			mciSendString("close song", NULL, 0, NULL);
			exit(0);
			break;
		default:
			cout << "invalid choice, try again";
			break;
		}

	}



}