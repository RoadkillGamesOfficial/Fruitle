#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

void startGame()
{
    for(int i = 0; i < 5; i++)
    {
        cout << "*-*-*-*-*" << endl;
    }
    string ans;
    cin >> ans;
}
int main()
{
    string wordList[] = {"apple", "peach", "mango", "berry", "melon", "lemon", "grape", "guava", "gourd", "olive"};
    //seed the random generation to whatever the current time is
    //this will make sure the random number is different every time
    srand(time(nullptr));
    //find an index in the range of [0, wordList length]
    int index = rand() % size(wordList);
    string answer = wordList[index];
    startGame();
    return 0;
}
