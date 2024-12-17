#pragma once

#include <vector>
#include <unordered_set>
#include <string>
using namespace std;

class Switchle
{
    private:
        unordered_set<string> validBank = {"apple", "peach", "mango", "berry", "melon", "lemon", "grape", "guava", "gourd", "olive"};
        vector<string> guesses;
        string answer;
        void GenerateAnswer();
        bool GuessHelper(string ans);
        void FindAccuracyGrid(string guess);
    public:
        void StartGame();
        void Update();
        void TakeGuess();
        bool Check();
};