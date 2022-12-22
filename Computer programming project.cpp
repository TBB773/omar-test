#include <string>
#include <iostream>
#include <filesystem>
#include <cstdlib>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include <winuser.h>
#pragma comment( lib, "winmm.lib" )
using namespace std;
namespace fs = std::filesystem;

namespace fywauv {


	//a class that imitates a vector for strings using a dynamic array with push, pop, size, delete clear and print functions because the vector library isn't allowed :/
	class vector
	{
		//class variables
		std::string* array;
		int size;
		int capacity;

	public:
		//constructor that creates an empty dynamic array of size 0
		vector()
		{
			array = new std::string[0];
			size = 0;
			capacity = 0;
		}

		//push function that adds a new string to the end of the array and doubles the capacity if the array is full to avoid overflow
		void push(std::string newString)
		{



			//if the array is full, create a new array with double the capacity and copy the data from the old array into the new one
			if (size == capacity)
			{
				if (capacity == 0)          //update capacity on first call
				{
					capacity = 1;
				}
				capacity = capacity * 2;
				std::string* newArray = new std::string[capacity];
				for (int i = 0; i < size; i++)
				{
					newArray[i] = array[i];
				}
				array = newArray;
			}

			//add the new string to the end of the array and increment the size
			array[size] = newString;
			size++;

		}

		//pop function that removes the last string from the array and halves the capacity if the array is 1/4 full
		void pop()
		{
			if (size == 0)
			{
				std::cout << "The array is empty. There is nothing to pop." << std::endl;  //if the array is empty, do nothing
			}

			else
			{
				if (size <= capacity / 4)                                    //if the array is 1/4 full (gurantees stuff in it cause we double when we add)
				{
					std::string* tempArray = new std::string[size];
					for (int i = 0; i < size; i++)
					{
						tempArray[i] = array[i];
					}
					delete[] array;                                           //same as push but in reverse not rewriting all that again, fight me -turnip
					capacity = capacity / 2;
					array = new std::string[capacity];
					for (int i = 0; i < size; i++)
					{
						array[i] = tempArray[i];
					}
					delete[] tempArray;
				}
				size--;
			}
		}

		//function that returns the size of the array
		int getsize()
		{
			return size;                     //just return the size we were using
		}

		//function that deletes the array and creates a new empty array
		void clear() {
			delete[] array;
			array = new std::string[0];                 //remove the array and replace it with an array of size and capacity 0
			size = 0;
			capacity = 0;
		}

		//function that deletes the array at the specified index
		void erase(int index)
		{
			if (index >= size)
			{
				std::cout << "The index specified is out of range." << std::endl;
			}
			else
			{
				for (int i = index; i < size - 1; i++)
				{
					array[i] = array[i + 1];
				}
				size--;
			}
		}

		//function that prints the array
		void print()
		{
			//if the vecotr is empty, print that it is empty
			if (size == 0)
			{
				std::cout << "The array is empty." << std::endl;
			}
			//else, print the contents
			else
			{
				for (int i = 0; i < size; i++)
				{
					std::cout << array[i] << std::endl;
				}
			}

		}
		//function that returns the string at the specified index
		std::string get(int index)
		{
			if (index >= size)
			{
				std::cout << "The index specified is out of range." << std::endl;
				return "error";
			}
			else
			{
				return array[index];
			}
		}
	};
}



int loginfunction() { //simple login function


	//This was made by Ahmed for further questions you can ask him but I will be writing the comments here for now -Mazen


	bool login = true;
	string users[] = { "ahmed", "youssef", "omar", "mazen" }; //the two arrays where we have the passwords and usernames saved
	string passwords[] = { "pass1", "pass2", "pass3", "pass4" };
	string passenter;
	string userenter;
	int attempts = 0;

	while (login)
	{
		if (attempts >= 5) { //this is a password cracking catcher for anyone who tries to enter passwords until they find the ones saved (as if someone would)
			cout << "\nYou have made too many attempts!\n";
			exit(0);
		}

		int locationuser = -1;
		int locationpass = -1;

		attempts++;

		cout << "\nenter username: ";  //these two asks for the input of the username and password
		cin >> userenter;
		cout << "enter password: ";
		cin >> passenter;

		for (int i = 0; i < 4; i++) { //this loop checks if the password exists in the "users" array if it does exist it will take it's location and equal it to locationuser for later use to confirm if the password entered is that of the same user

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

		if (locationuser == locationpass) { //this if statement ensure that the password entered is that of the user who logined in and not any password in the array

			cout << "welcome!";
			return locationuser;
			break;

		}
		else {
			cout << "username or password incorrect." << endl;

		}

	}

}

void listsongs(fywauv::vector& songs, string path, fywauv::vector& itemlist) { //this function is very important, it is the function we use to read the files in the folders


	//This was made by Ahmed for further questions but I will be writing the commends to explain it here for now -Mazen

	/*
	* first parameter is a pointer vector which will be the song paths in playlist
	* second parameter is the path for the folder which will be read
	* third parameter is a pointer vector which will be the song names in playlist
	* -Mazen
	*/


	char dot = '.'; //making a char called dot with the dot character for later use
	int count = 1;

	for (const auto& entry : fs::directory_iterator(path)) { //this is a for loop that uses the "directory iterator" to read all the paths of items in a folder and saving it to "entry" with each time it loops
		string item = entry.path().string(); //this makes a new string called "item" then takes the "entry" valuable and turns it to a string and makes items equal to that
		item = item.substr(item.find_last_of("/\\") + 1); //this uses the .subtry which will make the item shorter by taking everything after a certain location, here being "item.find_last_of("/\\") + 1" which is finding the last / in the path so we can make item equal just the name of the file, the +1 is because it start with / and we want it in the file name 

		size_t found = item.find(dot); //this makes an item called found which looks for a dot in the item valuable, which is the item name
		if (found > 1000000) { //this is a bug chatcher, where if it doesn't find a dot in the item name it will realize that this is not a file and instead a folder so then it will force the loop to go into the next run to check for the next item in line
			continue;
		}

		string ext = item.substr(item.find_last_of(".\\")); //if the file is not a folder it will run this instead which gets the extension of the file
		if (ext == ".wav" || ext == ".mp3") { //after it gets the "ext" or extension it will see if it mp3 or wav, we can add as many audio types as we want but for now we test with wav and mp3
			cout << count << "- " << item << endl; //this outputs the names of the items it finds 
			songs.push(entry.path().string()); //this puts the path of the audio fill in the "songs" vector
			itemlist.push(item); //this puts the name of the song into the "itemlist" vector
			count++;
		}

	}

}


void listplaylist(fywauv::vector& playlist, string extpath, int ipath, fywauv::vector& itemlist) { //I will be using this to controll the playlist


	//This was made by Mazen for further questions


	/*
	* first parameter is a pointer vector which will be the song paths in playlist
	* second parameter is the path for the folder which will be read
	* third parameter is either 1 or 0, zero for first initilization 1 is for when you want to edit the playlist
	* forth parameter is a pointer vector which will be the song names in playlist
	* -Mazen
	*/

	/*------------------------------------------ APETIZERS ------------------------------------------*/

	char dot = '.';
	int count = 1;
	int choice;
	int itemchoice;
	bool whilecontroller = true; //this bool value will be used to exist the while loops inside the playlist controller since I am too lazy to figure out how to break it otherwise
	int switchcontroller;
	string path;
	fywauv::vector controller;
	fywauv::vector additemlist;


	/*________________________________The Playlist controller________________________________*/

	if (ipath == 0) { //first initiliaztion making the playlist equal all the files in the first path you choose at the start of the program
		listsongs(playlist, extpath, itemlist);
	}
	else { //this is gonna be the controller for the playlist 
		while (whilecontroller) { //main loop for the controller thar doesn't end until you pick 4
			cout << "\n1- Choose a folder to make as a playlist \n\n2- Pick a track to add to the platlist from a folder \n\n3- remove a track from the playlist\n\n4- Exit playlist controller" << endl;
			cout << "\n\n\n";
			cin >> switchcontroller; //this value will decide which switch case you go into
			cout << "\n\n\n";
			switch (switchcontroller) {


			case 1: // this case choses this file to clear everything in the playlist and replace it with songs inside it
				playlist.clear(); //this clears the two vectors playlist and itemlist
				itemlist.clear();
				cout << "enter the path to the new folder" << ":";
				cin >> path;
				cout << "\n\n\n";
				listsongs(playlist, path, itemlist); //this changes adds all the items in the new folder to the playlist
				cout << "\n\n\n";
				break;


			case 2: //add a new track to the playlist
				cout << "Pick the folder with tracks you wish to add" << endl;
				cin >> path;
				for (const auto& entry : fs::directory_iterator(path)) {

					string item = entry.path().string(); //refer to the listsongs function to know how this works
					item = item.substr(item.find_last_of("/\\") + 1);
					size_t found = item.find(dot);
					if (found > 1000000) {
						continue;
					}

					string ext = item.substr(item.find_last_of(".\\"));
					if (ext == ".wav" || ext == ".mp3") {
						controller.push(entry.path().string()); //unlike the list songs function this pushes back to two new vectors called "controller" and "additemlist" which we use as temporary vectors for the path and song names in the folder we are picking a song to add to the playlist from
						additemlist.push(item);

					}
				}
				cout << "current controller playlist" << endl; //shows you the current items in the folder you are picking from
				for (int i = 0; i < additemlist.getsize(); i++) {
					cout << i + 1 << "- " << additemlist.get(i) << endl;

				}

				while (whilecontroller) { //this gives you two choices to either add all the items in the folder you are choosing from to the playlist or add one song from it
					cout << "\n1- Add all the songs to the playlist \n\n2- Pick a song to add \n\n3- Exit folder\n\n";
					cin >> choice;
					switch (choice)
					{
					case 1: //this function will add the entirity of the folder to the playlist
						if (controller.getsize() == 0) {
							cout << "Out of tracks in this folder" << endl; //this is used to prevent the program from adding the songs over and over again
							whilecontroller = false;
							break;
						}
						for (int i = 0; i < controller.getsize(); i++) { //this pushes items from the temporary "controller" and "additemlist" vectors to the "playlist" and "additemlist" vectors 
							playlist.push(controller.get(i));
							itemlist.push(additemlist.get(i));

						}

						cout << "current controller playlist" << endl; //shows you the new "itemlist" which is the name of the songs in the playlist
						for (int i = 0; i < itemlist.getsize(); i++) {
							cout << i + 1 << "- " << itemlist.get(i) << endl;
						}

						controller.clear(); //clears the temporary vectors
						additemlist.clear();

						break;
					case 2: //this will add one song to the list 
						cout << "Pick a song to add to the playlist" << endl;
						for (int i = 0; i < additemlist.getsize(); i++) { //this shows you the song name list of the stuff in the temporay vector
							cout << i + 1 << "- " << additemlist.get(i) << endl;
						}

						if (controller.getsize() == 0) { //this ensure this code stops working as soon as the there are no more songs to add from this list
							cout << "Out of tracks in this folder" << endl;
							whilecontroller = false;
							break;
						}

						cin >> itemchoice;
						if (itemchoice > controller.getsize()) { //this ensure the given value is in the vector so we don't get an error
							cout << "item doesn't exist" << endl;
							whilecontroller = false;
							break;
						}

						playlist.push(controller.get(itemchoice - 1)); //this pushes the path of the song from the temp vector to the playlist vector
						itemlist.push(additemlist.get(itemchoice - 1)); //this pushes the name of the song from the temp vector to the playlist vector
						cout << "added " << additemlist.get(itemchoice - 1) << " to the playlist" << endl; //shows you what you picked
						controller.erase(itemchoice - 1); //removes the path you picked from the temp list so you can't pick it twice
						additemlist.erase(itemchoice - 1); //remove the name of the song you picked you picked from the temp list so you can't pick it twice

						break;


					case 3:
						whilecontroller = false;
						break;
					}
				}
				controller.clear(); //clears the controller and additemlist vectors after being done running
				additemlist.clear();
				whilecontroller = true;
				count = 1;
				break;


			case 3: //remove a song from the playlist
				count = 1;
				cout << "current playlist" << endl; //shows you the current playlist
				for (int i = 0; i < playlist.getsize(); i++) {
					cout << i + 1 << "- " << itemlist.get(i) << endl;
				}

				cout << "pick a track to remove" << endl;
				cin >> choice;
				itemlist.erase(choice - 1); //remove the path you picked from the playlist
				playlist.erase(choice - 1);//remove the name of the song you picked from the playlist

				cout << "current playlist" << endl; //shows you the playlist after the song was removed
				for (int i = 0; i < itemlist.getsize(); i++) {
					cout << i + 1 << "- " << itemlist.get(i) << endl;
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


	//This was made by Mazen for further questions


	/*
	* this is called the mci command function
	* since playsound doesn't do anything other than play one sound me (Mazen) decided we will be moving to a better function called mcisendstring
	* but mci send string takes a LPCSTR string as the command for it to work
	* I had to make this function, which will create the command for us
	* when we open a file in mcisendstring we can easily play pause or resume, but first we need the string command to open it
	* to do that it uses this layout "open path mpegvideo alias name"
	* the open at the start says we want to open this file which is a
	* the path shows us where that file is on the computer
	* mpegvideo is the type of file
	* alias can be anything it is just a name so we know what this opened file is classified as, can be mp3 wav or as I choose song
	* more stuff on the open function of mcisendtstring  https://learn.microsoft.com/en-us/windows/win32/multimedia/open
	* -Mazen
	*/

	string command = "open type mpegvideo alias song"; //the template for the open command we will use

	int found = command.find(" "); //finds the first space in the template

	command = command.substr(0, found) + " " + path + command.substr(found); //adds the stuff before the first space then the path after the first space then second space then everything after that second space

	return command; //returns the command which we will use in mcisend string

}



int main() {

	/*__________________________________________________ QUOTE UN QUOTE __________________________________________________*/





	/*------------------------------------------ APETIZERS ------------------------------------------*/

	int controller;
	string command;
	time_t t1{}, t2{}, previous_pause_time = 0; //this is a timer saver for when we pause a song

	/*_________________________________ LOGIN FUNTION _________________________________*/

	int user = loginfunction(); //starts the login function

	/*_______________________________ LIST SONGS __________________________________*/

	fywauv::vector playlist;  //the playlist including all the paths to the songs we use
	fywauv::vector itemlist; //the itemlist which includes all the song names we use
	string ogpath;
	cout << "\n\nselect your music folder using path: ";
	cin >> ogpath; //asks for the first path to the starting folder
	cout << endl;

	/*_______________________ Playlist initilaization _______________________*/



	listplaylist(playlist, ogpath, 0, itemlist); // we put 0 in the third parameter to use the first time initilization for the playlist



	/*______________________________ PATHS___________________________*/

	//add a second backslash to all paths to avoid errors (no longer needed but kept just incase will probably be replaced with the fix to the sapce issue)


	cout << "Output of vector:\n\n";
	for (int i = 0; i < playlist.getsize(); ++i) {
		cout << playlist.get(i) << " " << endl;
	}

	cout << "AND SIZE IS..." << playlist.getsize() << endl;

	/*______________________________CHOOSE SONG___________________________*/


	/*
	* this is the function for choosing which song to play first from the given playlist at the start
	*/


	int songnum;
	cout << "\n\nenter song number: ";
	cin >> songnum;

	if (songnum > playlist.getsize()) {
		cout << "song number not found, track 1 chosen";
		songnum = 1;
	}

	songnum = songnum - 1;

	string song = playlist.get(songnum);


	cout << "YOU CHOSE :   " << TEXT(song.c_str()) << endl;

	/*------------------------------PATH TO COMMAND--------------------------*/

	/*
	* this is the first time initiliazing the command function in int main() with the song you choose to be the first one to run
	*/

	command = mcicommand(song);
	cout << command;


	/*------------------------------------------CONTROLS---------------------------------------------*/

	/*
	* the main controls of the program, first it initiliazes the mcisendstring with the command from the last function to open that song
	*/

	mciSendString(command.c_str(), NULL, 0, NULL);


	while (true) {

		//an infinite function that has one exit, this function will be the responsible to full controls of the program

		cout << "\n\n\n\n" << " 1- play\n 2- stop\n 3- pause \n 4- resume \n 5- next \n 6- previous \n 7- edit playlist \n 8- show playlist \n 9- Exit \n\n\n" << endl;
		cout << "enter your choice: ";
		cin >> controller; //chooses which switch case we will be running

		switch (controller) {
		case 1: //play

			//once a song is opened using the command function you don't have to call the command function unless you are changing it
			//therefore the play function is just the play command with the alias which is song

			mciSendString("play song", NULL, 0, NULL);
			t1 = time(nullptr);
			break;
		case 2: //stop

			//because of my (Mazen) low knowledge of the mcisendstring function me and Ahmed decided we will making the stop function like this

			mciSendString("close song", NULL, 0, NULL); //closes the song
			mciSendString(command.c_str(), NULL, 0, NULL); //opens it from the start with the command function
			break;
		case 3: //pause

			//uses the mcisendstring command pause to pause the song

			mciSendString("pause song", NULL, 0, NULL);
			t2 = time(nullptr);
			previous_pause_time += t2 - t1;
			break;
		case 4: //resume

			//uses the mcisendstring command resume to resume the song

			mciSendString("resume song", NULL, 0, NULL);
			t1 = time(nullptr);
			break;
		case 5: //next

			/*
			* this is more complicated than just using a next function in mcisendstring, since when you use it, it works with one song at a time
			* so Ahmed made this using the previous value songnum to be able to switch tracks
			* -Mazen
			*/

			mciSendString("close song", NULL, 0, NULL); //first it closes the song we are playing right now
			songnum++; //second it changes the songnum value increasing it by one 
			if (songnum > playlist.getsize() - 1) { //this is so if the number is out of the playlist, it starts the playlist from the begining
				songnum = 0;
			}
			song = playlist.get(songnum); //this changes song which is a value holding a path from the old song to the path of the new song
			command = mcicommand(song); //send back the new path to the function command to make us the new command to use in mcisend string
			mciSendString(command.c_str(), NULL, 0, NULL); //opens the new song using the command made in the previous line
			mciSendString("play song", NULL, 0, NULL); //starts playing the new song
			break;
		case 6: //previous

			//same as next but in reverse, not rewriting all of that again fight me -Mazen

			mciSendString("close song", NULL, 0, NULL);
			songnum--;
			if (songnum < 0) {
				songnum = playlist.getsize() - 1;
			}
			song = playlist.get(songnum);
			command = mcicommand(song);
			mciSendString(command.c_str(), NULL, 0, NULL);
			mciSendString("play song", NULL, 0, NULL);
			break;
		case 7: //Playlist control

			//this starts the playlist controls function with a value of 1 in ipath to run the controls rather than the first initliazation

			listplaylist(playlist, ogpath, 1, itemlist);
			break;

		case 8: //Show Playlist

			//read the titel :D

			for (int i = 0; i < itemlist.getsize(); i++) {
				cout << i + 1 << "- " << itemlist.get(i) << endl;
			}
			break;

		case 9: //exit

			//exits the program

			mciSendString("close song", NULL, 0, NULL);
			exit(0);
			break;

		default:

			//bug catcher for any value that isn't a number or a number that doesn't have a control in the switch case

			cout << "invalid choice, try again";
			break;
		}

	}



}