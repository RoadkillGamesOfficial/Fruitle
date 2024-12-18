#include "Switchle.h"
#include <iostream>
#include <algorithm>
#include <ctime>

void Switchle::GenerateAnswer()
{
    letterAndCount.clear();
    auto it = validBank.begin();
    answer = GenerateAnswerHelper(it);
    //Set up the count of each letter
    for(char c: answer)
    {
        letterAndCount[c] ++;
    }
}
string Switchle::GenerateAnswerHelper(unordered_set<string>::iterator & it)
{
    //Seed the random generation to whatever the current time is
    //This will make sure the random number is different every time
    srand(time(nullptr));
    //Find an index in the range of [0, wordList length]
    int index = rand() % validBank.size();
    //Iterate through the unordered_set of valid guesses to find an iterator to the guess
    it = validBank.begin();
    for(int i = 0; i < index; i++)
    {
        it ++;
    }
    //Recursively call the generator if the randomly chosen answer has been guessed already
    //The iterator is passed by reference so it will be updated to an unguessed answer and return
    if(find(guesses.begin(), guesses.end(), *it) != guesses.end())
    {
        GenerateAnswerHelper(it);
    }
    return *it;
}
void Switchle::StartGame()
{
    GenerateAnswer();
}
void Switchle::Update()
{
    //Generate a new answer before finding the accuracy of current guesses with it
    GenerateAnswer();
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
    for(int i = guesses.size(); i < TRIES; i++)
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
    if(guesses.size() == TRIES)
    {
        cout << "Out of guesses!" << endl;
        return true;
    }
    return false;
}
void Switchle::FindAccuracyGrid(string guess)
{
    vector<string> output (answer.size(), "");
    for(int i = 0; i < answer.size(); i++)
    {
        //If it is in the right index then add 2 to the output
        //Also, remove one occurunce of the letter since it has been processed
        if(guess[i] == answer[i])
        {
            output[i] = "2 ";
            letterAndCount[guess[i]] --;
        }
    }
    for(int i = 0; i < answer.size(); i++)
    {
        //If the highest priority position of the letter is found, skip it
        if(output[i] == "2 ")
        {
            continue;
        }
        //If an occurance of the letter is still present in the word then place a 1 and subtract an occurance
        if(letterAndCount[guess[i]] > 0)
        {
            output[i] = "1 ";
            letterAndCount[guess[i]] --;
        }
        //Otherwise, the letter is not present so add a 0
        else
        {
            output[i] = "0 ";
        }
    }
    for(string s: output)
    {
        cout << s;
    }
}