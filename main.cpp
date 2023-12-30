#include <iostream>
#include <windows.h>
#include <array>
#include <vector>
#include <conio.h>
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN


//snake properties

enum direction {UP,LEFT,DOWN,RIGHT,STOP};
int snakex = 24;
int snakey = 14;
int snakedir = STOP;
bool dead;

//food properties

int foodx = rand() % 49 + 1;
int foody = rand() % 24 + 1;
int score = 0;

//tail properties

int tailx[100];
int taily[100];
int tailSize = 1;



void setCursorPosition(int x, int y)
{
    //idk how this works but it does work good
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}
void ShowConsoleCursor(bool x) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = x;
    SetConsoleCursorInfo(out, &cursorInfo);
}

void draw() {

    char map[50][70];

    map[10][60] = 'S'; map[10][61] = 'C'; map[10][62] = 'O';
    map[10][63] = 'R'; map[10][64] = 'E'; map[10][65] = ' ';
    map[10][66] = '='; map[10][67] = ' ';

   
    //i copied this off of the internet idk what it does 
    char prevmap[50][50];
    std::memset((char*)prevmap, 0, 50 * 50);
    ShowConsoleCursor(false);

    // ...

    for (int y = 0; y != 25; ++y)
    {
        
        if (dead == true) {
            std::cout << "DEAD " << "\a";
            break;
        }

        if (y == 5) {
        
            for (int k = 0; k < 9; k++) {
                
                int b = 60 + k;
                
                if (b == 68) {
                
                    setCursorPosition((b), y);
                    std::cout << score;
                
                }
                
                else {
                    setCursorPosition((b), y);
                    std::cout << map[10][b];
                
                }
            }
        
        }

        for (int x = 0; x != 50; ++x)
        {
            
            //do nothing if the map has not changed
            
            if (map[50][50] == prevmap[50][50]) {
                continue;
            }

            //draw the left and right borders of map

            if (x == 0 || x == 49) {

                setCursorPosition(x, y);
                map[y][x] = 'I';
                std::cout << map[y][x];
            }
            
            //draw the top and bottom borders of map

            else if (y == 0 || y == 24) {
            
                setCursorPosition(x, y);
                map[y][x] = '=';
                std::cout << map[y][x];
            
            }

           


             //fill the map with empty space

            else {
                setCursorPosition(x, y);
                map[y][x] = ' ';
                std::cout << map[y][x];


                if(x == snakex && y == snakey){ 
            
            
                    setCursorPosition(x, y);
                    map[y][x] = '0';
                    std::cout << map[y][x];
            

            }



                 else if (x == tailx[0] && y == taily[0]) {
                    
                      setCursorPosition(x, y);
                      map[y][x] = 'O';
                      std::cout << map[y][x];


                   
                }

                else if (x == foodx && y == foody){

                    setCursorPosition(x, y);
                    map[y][x] = 'o';
                    std::cout << map[y][x];
            }

                for (int e = 1; e < tailSize; e++) {
                
                    if (x == tailx[e] && y == taily[e]) {

                        setCursorPosition(x, y);
                        map[y][x] = 'O';
                        std::cout << map[y][x];

                    }


                }
            }

        }
    std::cout << std::endl;
    }
    //i have 0 idea about this too  
    std::cout.flush();
    std::memcpy((char*)prevmap, (char const*)map, 50 * 50);

}


void input() {
    
    
    if (_kbhit()) {

        
        switch (_getch()) {

        case 'w':
            
            snakedir = UP;
            break;

        case 'a':

            snakedir = LEFT;
            break;

        case 's':

            snakedir = DOWN;
            break;

        case 'd':

            snakedir = RIGHT;
            break;

        case 'p':

            snakedir = STOP;
            break;
        }




    }


}

void logic() {
   
    int prevx = tailx[0];
    int prevy = taily[0];
    int prevx2, prevy2;
    
    for (int e = 1; e < tailSize; e++) {
                
        prevy2 = taily[e];    
        prevx2 = tailx[e];
        tailx[e] = prevx; taily[e] = prevy;
        prevx = prevx2; prevy = prevy2;
    }

    for (int i = 0; i < tailSize + 1; i++) {
        
        if (tailx[i] == snakex && taily[i] == snakey) {
            
            dead = true;
        }

    }
    
    switch (snakedir) {

    case UP: 
        snakey--;
        tailx[0] = snakex;
        taily[0] = snakey + 1;
        break;

    case LEFT:
        snakex--;
        tailx[0] = snakex + 1;
        taily[0] = snakey;
        break;

    case DOWN:
        snakey++;
        tailx[0] = snakex;
        taily[0] = snakey - 1;
        break;


    case RIGHT:
        snakex++;
        tailx[0] = snakex - 1;
        taily[0] = snakey;
        break;

    case STOP:
        snakey = snakey;
        snakex = snakex;
        break;

    }

    //the snake will come out of the opposite wall

    if (snakex == 49) { snakex = 1; }
    if (snakex == 0) { snakex = 48; }
    if (snakey == 24) { snakey = 1; }
    if (snakey == 0) { snakey = 24; }

    //food eating

    if (foodx == snakex && foody == snakey) {

         foodx = rand() % 48 + 1;
         foody = rand() % 23 + 1;
         score++;
         tailSize++;
    }

    
}


int main(){

    while(true) {

    
    input();
    logic();
    draw();

    }   

    return 0;
}