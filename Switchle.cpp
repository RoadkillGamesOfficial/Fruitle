#include "Switchle.h"
#include <iostream>
#include <algorithm>
#include <ctime>

void Switchle::GenerateAnswer()
{
    //Seed the random generation to whatever the current time is
    //This will make sure the random number is different every time
    srand(time(nullptr));
    //Find an index in the range of [0, wordList length]
    int index = rand() % validBank.size();
    //Iterate through the unordered_set of valid guesses to find an iterator to the guess
    auto it = validBank.begin();
    for(int i = 0; i < index; i++)
    {
        it ++;
    }
    answer = *it;
}
void Switchle::StartGame()
{
    GenerateAnswer();
    for(int i = 0; i < 5; i++)
    {
        cout << "*-*-*-*-*" << endl;
    }
}
void Switchle::Update()
{
    //Print out the guesses
    for(string s: guesses)
    {
        for(char c: s)
        {
            cout << c << " ";
        }
        cout << '\t';
        FindAccuracyGrid(s);
        cout << endl;
    }
    //Print out the empty lines
    for(int i = guesses.size(); i < 5; i++)
    {
        cout << "*-*-*-*-*" << endl;
    }
}
void Switchle::TakeGuess()
{
    string ans;
    cin >> ans;
    while(!GuessHelper(ans))
    {
        cin >> ans;
    }
    guesses.push_back(ans);
}
bool Switchle::GuessHelper(string ans)
{
    if(ans.size() != 5)
    {
        cout << "Bad length" << endl;
        return false;
    }
    if(validBank.find(ans) == validBank.end())
    {
        cout << "Invalid guess" << endl;
        return false;
    }
    if(find(guesses.begin(), guesses.end(), ans) != guesses.end())
    {
        cout << "Already guessed!" << endl;
        return false;
    }
    return true;
}
bool Switchle::Check()
{
    if(find(guesses.begin(), guesses.end(), answer) != guesses.end())
    {
        cout << "You found it in " << guesses.size() << " guesses!" << endl;
        return true;
    }
    if(guesses.size() == 5)
    {
        cout << "Out of guesses!" << endl;
        return true;
    }
    return false;
}
void Switchle::FindAccuracyGrid(string guess)
{
    for(int i = 0; i < answer.size(); i++)
    {
        if(guess[i] == answer[i])
        {
            cout << "2 ";
            continue;
        }
        if(answer.find(guess[i]) < 5)
        {
            cout << "1 ";
            continue;
        }
        cout << "0 ";
    }
}