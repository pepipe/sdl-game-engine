#include "Score.h"

int Score::GetScore() const
{
    return _score;
}

void Score::IncreaseScore()
{
    _score++; 
}

void Score::IncreaseScore(const int amount)
{
    _score += amount; 
}

void Score::ResetScore()
{
    _score = 0;
}