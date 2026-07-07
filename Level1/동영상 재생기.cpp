#include <string>
#include <vector>

using namespace std;

// string으로 된 시간을 int로 변경
// "11:23"이면 1123으로 변경
int RevertToInteger(string time)
{
	string removedtime;

	for (size_t i = 0; i < time.size(); ++i)
	{
		char target = time[i];
		if (target == ':') // 필요없는 ':' 문자 제거
		{
			continue;
		}

		removedtime += target;
	}

	return stoi(removedtime);
}

// 자릿 수 맞추기
string TimeTwoString(string time)
{
	string temp = time;

	while (temp.size() < 2)
	{
		temp.insert(temp.begin(), '0');
	}

	return temp;
}

// int로 된 시간을 string으로 변경
// 1123이면 "11:23"으로 변경
string RevertToString(int time)
{
	int int_minute = time / 100;
	int int_seconds = time % 100;

	string str_minute = to_string(int_minute);
	string str_seconds = to_string(int_seconds);

	str_minute = TimeTwoString(str_minute);
	str_seconds = TimeTwoString(str_seconds);

	return str_minute + ':' + str_seconds;;
}

// 시간을 특정 값만큼 조정
int AdjustTime(int time, int add)
{
	int minute = time / 100;
	int seconds = time % 100 + add;

	if (seconds >= 60) // 초의 숫자가 60을 넘은 경우
	{
		++minute; // 분 ++
		seconds -= 60; // 초 초기화
	}
	else if (seconds < 0)
	{
		--minute; // 분 --
		seconds = 60 + seconds; // 초 초기화
	}

	return minute * 100 + seconds;
}

// 비디오 유효 범위로 변경
int ValidateVideoTime(int video_len, int time)
{
	if (time < 0)
	{
		return 0;
	}
	else if (video_len < time)
	{
		return video_len;
	}

	return time;
}

// 오프닝 스킵
int SkipOpenning(int op_start, int op_end, int time)
{
	if (op_start <= time && time <= op_end)
	{
		return op_end;
	}

	return time;
}

// 시간 계산
int CalculateVideoTime(int video_len, int pos, int op_start, int op_end, vector<string> commands)
{
	int currenttime = pos;
	int minute = currenttime / 100;
	int seconds = currenttime % 100;

	currenttime = SkipOpenning(op_start, op_end, currenttime);

	for (size_t i = 0; i < commands.size(); ++i)
	{
		if (commands[i] == "prev")
		{
			currenttime = AdjustTime(currenttime, -10);
		}
		else if (commands[i] == "next")
		{
			currenttime = AdjustTime(currenttime, 10);
		}

		currenttime = ValidateVideoTime(video_len, currenttime);
		currenttime = SkipOpenning(op_start, op_end, currenttime);
	}

	return currenttime;
}

string solution(string video_len, string pos, string op_start, string op_end, vector<string> commands)
{
	int length = RevertToInteger(video_len);
	int current_pos = RevertToInteger(pos);
	int start = RevertToInteger(op_start);
	int end = RevertToInteger(op_end);

	current_pos = CalculateVideoTime(length, current_pos, start, end, commands);

	return RevertToString(current_pos);
}