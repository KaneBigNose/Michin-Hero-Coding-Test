#include <string>
#include <vector>

using namespace std;

// 타겟의 꼭대기 층 구하는 함수
int FindTargetTopFloor(int n, int w, int index)
{
	int top_floor = n / w; // 타겟 꼭대기 층
	int remain_box = n % w; // 마지막 층 상자 개수
	bool left_start = top_floor % 2 == 0; // 마지막 제외 쌓인 층이 짝수면 왼쪽부터 쌓고, 아니면 오른쪽부터

	// 꼭대기에 왼쪽부터 쌓아야 하고, 타겟 인덱스가 추가로 상자로 쌓이는 인덱스에 포함되는 경우
	if (left_start && index < remain_box)
	{
		++top_floor;
	}
	// 꼭대기에 오른쪽부터 쌓아야 하고, 타겟 인덱스가 추가로 상자로 쌓이는 인덱스에 포함되는 경우
	else if (!left_start && index >= w - remain_box)
	{
		++top_floor;
	}

	return top_floor;
}

// 타겟의 인덱스를 구하는 함수
int FindTargetIndex(int w, int num, int target_floor)
{
	bool left_index = target_floor % 2 == 1; // 타겟의 층이 홀수면 왼쪽부터, 아니면 오른쪽부터
	int index = num % w == 0 ? w - 1 : num % w - 1; // 타겟 인덱스

	// 오른쪽부터 쌓는 층이라면 인덱스 반전
	if (!left_index)
	{
		index = w - index - 1;
	}

	return index;
}

// 타겟이 있는 층 구하는 함수
int FindTargetCurrentFloor(int w, int num)
{
	// 쌓아야 할 상자가 있으면 +1 층
	return num % w > 0 ? num / w + 1 : num / w;
}

// n은 총 상자 개수, w는 가로 폭, num은 타겟 번호
int solution(int n, int w, int num)
{
	int target_floor = FindTargetCurrentFloor(w, num);
	int target_index = FindTargetIndex(w, num, target_floor);

	int top_floor = FindTargetTopFloor(n, w, target_index);

	// 꼭대기 층 - 타겟 층 + 1
	return top_floor - target_floor + 1;
}