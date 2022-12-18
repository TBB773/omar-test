#include <string>
#include <iostream>
#include <filesystem>
#include <vector>
#include <cstdlib>
#include <windows.h>
#include <ctime>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#pragma comment(lib, "Winmm.lib")

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
		if (ext == ".wav") {
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

	/*______________________________ PATHS___________________________*/

	//add a second backslash to all paths to avoid errors

	for (int i = 0; i < songs.size(); i++) {
		for (int j = 0; j < songs[i].size(); j++) {
			if (songs[i][j] == '\\') {
				songs[i].insert(j, "\\");
				j++;
			}
		}
	}



	/*cout << "Output of vector:\n\n ";
	for (int i = 0; i < songs.size(); ++i) {
		cout << songs[i] << " " << endl;
	}

	cout << "AND SIZE IS..." << songs.size() << endl;*/

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

	int n;

	cout << "YOU CHOSE :   " << TEXT(song.c_str());




	/*------------------------------------------CONTROLS---------------------------------------------*/

	//play, pause, replay from the time you paused, next song, previous song and exit using playsound. reset to inex 0 if you leave the range of vector

	cout << "\n\n\n\n" << " 1- play the song \n 2- stop the song \n 3- ERROR - WIP \n 4- next song \n 5- previous song \n 6- exit \n\n" << endl;
	cout << "enter your choice: ";
	cin >> n;

	while (n != 6) {

		if (n == 1) {
			PlaySound(TEXT(song.c_str()), NULL, SND_ASYNC);
			cout << " 1- play the song \n 2- stop the song \n 3- ERROR - WIP \n 4- next song \n 5- previous song \n 6- exit \n\n" << endl;
			cout << "enter your choice: ";
			cin >> n;
		}

		if (n == 2) {
			PlaySound(NULL, NULL, SND_ASYNC);
			cout << " 1- play the song \n 2- stop the song \n 3- ERROR - WIP \n 4- next song \n 5- previous song \n 6- exit \n\n" << endl;
			cout << "enter your choice: ";
			cin >> n;
		}

		if (n == 3) {
			PlaySound(TEXT(song.c_str()), NULL, SND_ASYNC);
			cout << " 1- play the song \n 2- stop the song \n 3- ERROR - WIP \n 4- next song \n 5- previous song \n 6- exit \n\n" << endl;
			cout << "enter your choice: ";
			cin >> n;
		}

		if (n == 4) {
			songnum = songnum + 1;
			if (songnum >= songs.size()) {
				cout << "song number not found, track 1 chosen";
				songnum = 0;
			}
			song = songs[songnum];
			PlaySound(TEXT(song.c_str()), NULL, SND_ASYNC);
			cout << " 1- play the song \n 2- stop the song \n 3- ERROR - WIP \n 4- next song \n 5- previous song \n 6- exit \n\n" << endl
				<< endl << TEXT(song.c_str()) << endl;
			cout << "enter your choice: ";
			cin >> n;
		}

		if (n == 5) {
			songnum = songnum - 1;
			if (songnum < 0) {
				cout << "song number not found, last track chosen";
				songnum = songs.size() - 1;
			}
			song = songs[songnum];
			PlaySound(TEXT(song.c_str()), NULL, SND_ASYNC);
			cout << " 1- play the song \n 2- stop the song \n 3- ERROR - WIP \n 4- next song \n 5- previous song \n 6- exit \n\n" << endl
				<< endl << TEXT(song.c_str()) << endl;
			cout << "enter your choice: ";
			cin >> n;
		}
	}



	return 0;
}



