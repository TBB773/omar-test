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

void listsongs(vector <string>& songs, string path, vector<string>& itemlist) {

	char dot = '.';
	int countT = 1;

	for (const auto& entry : fs::directory_iterator(path)) {
		string item = entry.path().string();
		item = item.substr(item.find_last_of("/\\") + 1);

		size_t found = item.find(dot);
		if (found > 1000000) {
			continue;
		}

		string ext = item.substr(item.find_last_of(".\\"));
		if (ext == ".wav" || ext == ".mp3") {
			cout << countT << "- " << item << endl;
			songs.push_back(entry.path().string());
			itemlist.push_back(item);
			countT++;
		}

	}

}


void listplaylist(vector <string>& playlist, string extpath, int ipath, vector<string>& itemlist) { //I will be using this to controll the playlist
	char dot = '.';
	int count = 1;
	int choice;
	int itemchoice;
	bool whilecontroller = true;
	int switchcontroller;
	string path;
	vector<string> controller;
	vector<string> additemlist;


	if (ipath == 0) { //first initiliaztion making the playlist equal all the files in the original path you choose at the start of the program
		listsongs(playlist, extpath, itemlist);
	}
	else { //this is gonna be the controller for the playlist 
		while (whilecontroller) { //main loop for the controller
			cout << "\n1- Choose a folder to make as a playlist \n\n2- Pick a track to add to the platlist from a folder \n\n3- remove a track from the playlist\n\n4- Exit playlist controller" << endl;
			cout << "\n\n\n";
			cin >> switchcontroller;
			cout << "\n\n\n";
			switch (switchcontroller) {
			case 1: //choses this file to replace the playlist with the stuff inside it
				playlist.clear();
				itemlist.clear();
				cout << "enter the path to the new folder" << ":";
				cin >> path;
				cout << "\n\n\n";
				for (const auto& entry : fs::directory_iterator(path)) {
					string item = entry.path().string();
					item = item.substr(item.find_last_of("/\\") + 1);

					size_t found = item.find(dot);
					if (found > 1000000) {
						continue;
					}

					string ext = item.substr(item.find_last_of(".\\"));
					if (ext == ".wav" || ext == ".mp3") {
						cout << endl << count << "- " << item << endl;
						playlist.push_back(entry.path().string());
						itemlist.push_back(item);
						count++;
					}

				}
				cout << "\n\n\n";

				break;
			case 2: //add a new track to the playlist
				cout << "Pick the folder with tracks you wish to add" << endl;
				cin >> path;
				for (const auto& entry : fs::directory_iterator(path)) {

					string item = entry.path().string(); //this will make us items which is basically the name of the songs
					item = item.substr(item.find_last_of("/\\") + 1);
					size_t found = item.find(dot);
					if (found > 1000000) {
						continue;
					}

					string ext = item.substr(item.find_last_of(".\\"));
					if (ext == ".wav" || ext == ".mp3") {
						controller.push_back(entry.path().string());
						additemlist.push_back(item);

					}

				}
				cout << "current controller playlist" << endl;
				for (int i = 0; i < additemlist.size(); i++) {
					cout << i + 1 << "- " << additemlist[i] << endl;

				}

				while (whilecontroller) {
					cout << "\n1- Add all the songs to the playlist \n\n2- Pick a song to add \n\n3- Exit folder\n\n";
					cin >> choice;
					switch (choice)
					{
					case 1: //this function will add the entirity of the folder to the playlist
						if (controller.size() == 0) {
							cout << "Out of tracks in this folder" << endl;
							whilecontroller = false;
							break;
						}
						for (int i = 0; i < controller.size(); i++) {
							playlist.push_back(controller[i]);
							itemlist.push_back(additemlist[i]);
							controller.clear();
							additemlist.clear();

						}
						cout << "current controller playlist" << endl;
						for (int i = 0; i < itemlist.size(); i++) {
							cout << i + 1 << "- " << itemlist[i] << endl;

						}
						break;
					case 2: //this will add one song to the list 
						cout << "Pick a song to add to the playlist" << endl;
						for (int i = 0; i < additemlist.size(); i++) {
							cout << i + 1 << "- " << additemlist[i] << endl;
						}

						if (controller.size() == 0) {
							cout << "Out of tracks in this folder" << endl;
							whilecontroller = false;
							break;
						}

						cin >> itemchoice;
						if (itemchoice > controller.size()) {
							cout << "item doesn't exist" << endl;
							whilecontroller = false;
							break;
						}

						playlist.push_back(controller[itemchoice - 1]);
						itemlist.push_back(additemlist[itemchoice - 1]);
						cout << "added " << additemlist[itemchoice - 1] << " to the playlist" << endl;
						controller.erase(controller.begin() + itemchoice - 1);
						additemlist.erase(additemlist.begin() + itemchoice - 1);

						break;
					case 3:
						whilecontroller = false;
						break;
					}
				}
				controller.clear();
				additemlist.clear();
				whilecontroller = true;
				count = 1;
				break;
			case 3: //remove a song from the playlist
				count = 1;
				cout << "current playlist" << endl;
				for (int i = 0; i < playlist.size(); i++) {
					cout << i + 1 << "- " << itemlist[i] << endl;
				}

				cout << "pick a track to remove" << endl;
				cin >> choice;
				itemlist.erase(itemlist.begin() + choice - 1);
				playlist.erase(playlist.begin() + choice - 1);

				cout << "current playlist" << endl;
				for (int i = 0; i < itemlist.size(); i++) {
					cout << i + 1 << "- " << itemlist[i] << endl;
				}

				break;
			case 4:
				whilecontroller = false;
				break;
			}
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
	/*------------------------------------------ APETIZERS ------------------------------------------*/

	int controller;
	string command;
	time_t t1{}, t2{}, previous_pause_time = 0;

	/*_________________________________ LOGIN FUNTION _________________________________*/

	int user = loginfunction();

	/*_______________________________ LIST SONGS __________________________________*/

	vector<string> playlist;
	vector<string> itemlist;
	string ogpath;
	cout << "\n\nselect your music folder using path: ";
	cin >> ogpath;
	cout << endl;

	/*_______________________ Playlist initilaization _______________________*/

	listplaylist(playlist, ogpath, 0, itemlist);
	/*______________________________ PATHS___________________________*/

	//add a second backslash to all paths to avoid errors


	cout << "Output of vector:\n\n";
	for (int i = 0; i < playlist.size(); ++i) {
		cout << playlist[i] << " " << endl;
	}

	cout << "AND SIZE IS..." << playlist.size() << endl;

	/*______________________________CHOOSE SONG___________________________*/

	int songnum;
	cout << "\n\nenter song number: ";
	cin >> songnum;

	if (songnum > playlist.size()) {
		cout << "song number not found, track 1 chosen";
		songnum = 1;
	}

	songnum = songnum - 1;

	string song = playlist[songnum];


	cout << "YOU CHOSE :   " << TEXT(song.c_str()) << endl;

	/*------------------------------PATH TO COMMAND--------------------------*/


	command = mcicommand(song);
	cout << command;


	/*------------------------------------------CONTROLS---------------------------------------------*/

	mciSendString(command.c_str(), NULL, 0, NULL);


	while (true) {
		cout << "\n\n\n\n" << " 1- play\n 2- stop\n 3- pause \n 4- resume \n 5- next \n 6- previous \n 7- edit playlist \n 8- show playlist \n 9- Exit \n\n\n" << endl;
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
			if (songnum > playlist.size() - 1) {
				songnum = 0;
			}
			song = playlist[songnum];
			command = mcicommand(song);
			mciSendString(command.c_str(), NULL, 0, NULL);
			mciSendString("play song", NULL, 0, NULL);
			break;
		case 6: //previous
			mciSendString("close song", NULL, 0, NULL);
			songnum--;
			if (songnum < 0) {
				songnum = playlist.size() - 1;
			}
			song = playlist[songnum];
			command = mcicommand(song);
			mciSendString(command.c_str(), NULL, 0, NULL);
			mciSendString("play song", NULL, 0, NULL);
			break;
		case 7: //Playlist control

			listplaylist(playlist, ogpath, 1, itemlist);
			break;

		case 8: //Show Playlist

			for (int i = 0; i < itemlist.size(); i++) {
				cout << i + 1 << "- " << itemlist[i] << endl;
			}
			break;

		case 9: //exit

			mciSendString("close song", NULL, 0, NULL);
			exit(0);
			break;

		default:
			cout << "invalid choice, try again";
			break;
		}

	}



}