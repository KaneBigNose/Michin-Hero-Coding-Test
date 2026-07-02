#include <string>
#include <vector>

using namespace std;

enum State
{
    Green,
    Yellow,
    Red
};

class SinHoDeung
{
public:
    void CheckState()
    {
        ++time;

        switch (state)
        {
        case State::Green:
        {
            if (time >= green_max)
            {
                state = State::Yellow;
                time = 0;
            }
            break;
        }
        case State::Yellow:
        {
            if (time >= yellow_max)
            {
                state = State::Red;
                time = 0;
            }
            break;
        }
        case State::Red:
        {
            if (time >= red_max)
            {
                state = State::Green;
                time = 0;
            }
            break;
        }
        }
    }

public:
    State state = State::Green;

    int green_max = 0;
    int yellow_max = 0;
    int red_max = 0;

    int time = 0;
};

int solution(vector<vector<int>> signals)
{
    size_t shd_count = signals.size();
    vector<SinHoDeung> shd;
    shd.reserve(shd_count);

    for (size_t i = 0; i < shd_count; ++i)
    {
        SinHoDeung temp;
        temp.green_max = signals[i][0];
        temp.yellow_max = signals[i][1];
        temp.red_max = signals[i][2];
        shd[i] = temp;
    }

    int max_time = 1;

    for (size_t i = 0; i < shd_count; ++i)
    {
        max_time *= 20;
    }

    for (int i = 1; i <= max_time; ++i)
    {
        bool found_time = true;
        for (int j = 0; j < shd_count; ++j)
        {
            if (shd[j].state != State::Yellow)
            {
                found_time = false;
            }

            shd[j].CheckState();
        }

        if (found_time)
        {
            return i;
        }
    }

    return -1;
}