
//in game we are move using arrows


#include <iostream>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <experimental/random>


using namespace std;

// define here, assign names to value for keys (arrows)


#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ESC 27

//function responsibility for random position obstacles

int* obstacles(int rows){
    int obst_num=rows-2; //remove finish and start position
    int* obs_tab=new int[obst_num]; //obs_tab[obst_num]
    for(int i=0; i<obst_num;i++ ){

        obs_tab[i]=experimental::randint(1, 10);

    }

    return obs_tab;

}
//changing obstacle position
int* substraction(int minuend[],int substrahend[]){

    static int wartosc[10];
    for(int i=0;i<10;i++){

        wartosc[i]=minuend[i]-substrahend[i];
    }
    return wartosc;

};
//random choice move direction our obstacles
int* randi(int zmienna){
    int *tab=new int[zmienna];
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(-1, 1);
    for (int i=0; i<zmienna; ++i){
        //cout<<dist(mt)<<endl;
        tab[i]= dist(mt);
    }

    return tab;
}


//checking position out player, if player position is equal position of obstacle we finish game
int crash_game(int position_X, int position_Y,int money,int obst[10])
{   int exit;

    if((position_Y==0)and (position_X==money)){
        cout<<"YOU WIN"<<endl;
        return 1;
    }
    else if((position_Y == 0) or (position_X ==0)or (position_X==11) )
    {
        cout<<"GAME OVER"<<endl;

        return 1;
    }


    for(int i=0;i<10;i++){

        int X=obst[i];
        if((position_Y==i+1)and (position_X==X)){
            cout<<"GAME OVER"<<endl;
            return 1;
        }

    }


     return 0;

}
//random choose our start and finish position
int randomizer()
{
    int random_number = experimental::randint(0, 9)  +1;
    return random_number;
}
//function resposibility for display game in console
void print_function(int position_rows,int position_cols,int money,int obst[10]) {
    int n = 12;
    int m = 12;
    int i=0;
    system("CLS");
    char tab[n][m];
    for (int j = 0; j < 12; j++) {
        for (int k = 0; k < 12; k++) {
            if ((j == position_rows) and (k == position_cols)) {
                tab[j][k] = 'P';
            }
            else if((j==0)and (k==money)){
                tab[j][k]='S';
            }

            else if((j==0) or (j==11)){
                tab[j][k]='-';
            }
            else if((k==0) or (k==11)){
                tab[j][k]='|';
            }

            else {
                tab[j][k] = ' ';
            }

        }
        //display our obstacles
        if((j != 0)and (j != 11)){

            tab[j][obst[i]]='X';
            i=i+1;
        }


    }

    for(int j=0; j<12; j++)
    {
        for(int k=0;k<12;k++)
        {
            //std::cout<<tab[j][k];
            std::cout << tab[j][k] << " \n"[k == n-1];
        }

    }
}

int start_positition_X=randomizer();
int start_position_Y=11;


int main() {

    int money=randomizer();


    int * objects=obstacles(12);
    int tablica[10];
    for(int i=0; i<10;i++)
    {
        tablica[i]=*(objects+i);
        cout<<tablica[i]<<endl;
    }

    print_function(start_position_Y, start_positition_X,money,tablica);
    //Sleep(5000);
    //system("CLS");


    int c = 0;
    int war=0;
    while (war<1) {
        c = 0;

        int * looking_up=randi(10);
        int zbior[10];
        for(int i=0; i<10; i++) {
            //cout<<*(looking_up+i)<<endl;
            zbior[i] = *(looking_up + i);
            //cout << zbior[i] << endl;
        }

        int* wynik;
        wynik=substraction(tablica,zbior);
        //int table[10];
        for(int i=0;i<10;i++){

            tablica[i]=*(wynik+i);
            //cout<<table[i]<<endl;
        }

        //loads data from keyboard, which arrow was press
        switch ((c = getch())) {
            case KEY_UP:
                start_position_Y = start_position_Y - 1;


                print_function(start_position_Y, start_positition_X,money,tablica);

                break;
            case KEY_DOWN:
                start_position_Y = start_position_Y + 1;

                print_function(start_position_Y, start_positition_X,money,tablica);
                break;
            case KEY_LEFT:
                start_positition_X = start_positition_X - 1;
                print_function(start_position_Y, start_positition_X,money,tablica);
                break;
            case KEY_RIGHT:
                start_positition_X = start_positition_X + 1;

                print_function(start_position_Y, start_positition_X,money,tablica);
                break;
            case ESC:
                cout << endl << "ESC" << endl;
                war = 1;
                start_positition_X=5;
                start_position_Y=0;
                break;
            default:
                //cout << endl << "null" << endl;  // not arrow
                break;
        }

        //check position compatibility
        war=crash_game(start_positition_X,start_position_Y,money,tablica);

    }
    return 0;
}