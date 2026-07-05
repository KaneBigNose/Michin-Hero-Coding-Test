#include <string>
#include <vector>

using namespace std;

// 희망 출근 시간을 받아 마감 시간을 리턴
int DeadlineTime(int hopetime)
{
    int time = hopetime + 10;

    if (time % 100 >= 60) // 더한 값이 60분을 넘는 경우
    {
        time += 100; // 시간 ++
        time -= 60; // 분 초기화
    }

    return time;
}

// 다음 요일로 넘기는 함수
int GetNextWorkDay(int today)
{
    int nextday = today + 1;

    if (nextday > 7) // 일요일 -> 월요일
    {
        nextday = 1;
    }

    return nextday;
}

// 해당 직원이 출근 시간을 지켰는지 여부
bool IsNotLateWork(int hopetime, vector<int> timelogs, int startday)
{
    int deadlinetime = DeadlineTime(hopetime);
    int today = startday;

    // 일주일 동안 근무 시간을 잘 지켰는지 체크
    for (int i = 0; i < 7; ++i)
    {
        if (today == 6 || today == 7) // 주말 제외
        {
            today = GetNextWorkDay(today); // 처음에 이 부분에 요일 넘기기 처리를 안해줘서 틀렸었음...
            continue;
        }

        if (timelogs[i] > deadlinetime)
        {
            return false;
        }

        today = GetNextWorkDay(today);
    }

    return true;
}

int solution(vector<int> schedules, vector<vector<int>> timelogs, int startday)
{
    int answer = 0;

    for (size_t i = 0; i < schedules.size(); ++i)
    {
        if (IsNotLateWork(schedules[i], timelogs[i], startday))
        {
            ++answer;
        }
    }

    return answer;
}