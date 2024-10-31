#pragma once

class Score
{
public:
    int GetScore() const;
    void IncreaseScore();
    void IncreaseScore(int amount);
    void ResetScore();

private:
    int _score = 0;
};
