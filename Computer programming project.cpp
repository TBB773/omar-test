#include <iostream>
#include <string>

using namespace std;


void loginfunction() {

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
            break;

        }
        else {
            cout << "username or password incorrect." << endl;

        }



    }

}


int main() {

    /*____________________________ LOGIN FUNTION _____________________________*/
    loginfunction();

}