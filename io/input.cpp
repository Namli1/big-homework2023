#include <iostream>
#include <cstdlib>


using namespace std;

void menu();
void mainMenu();
void optionsMenu();
void options();
int choice1 = 0;
int choice2 = 3;

int main(int argc, char** argv) {



    menu();



    return 0;
}


void menu(){

        do {
        choice2 = 0;
        mainMenu();

        switch(choice1) {

            case 1:
                cout << "Pew pew!\n";
                break;

            case 2:
                options();
                break;

            case 3:
                break;

        }

    } while(choice1 != 3);


}

void options(void) {

    do {
        optionsMenu();

        switch(choice2){

            case 1:
                cout << "So difficult!\n";
                break;

            case 2: 
                cout << "Beep!\n";
                break;

            case 3:
                break;

            default: 
                break;

        }

    } while(choice2 != 3);


}




void mainMenu(void) {



    cout << "Main Menu\n";
    cout << "1 - Start game\n";
    cout << "2 - Options\n";
    cout << "3 - Quit\n";
    cout << "Please choose: ";
            cin >> choice1;

}

void optionsMenu(void) {



    cout << "Options Menu\n";
    cout << "1 - Difficulty\n";
    cout << "2 - Sound";
    cout << "3 - Back\n";
    cout << "Please choose: ";
            cin >> choice2;

}