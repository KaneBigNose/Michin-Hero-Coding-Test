#include <string>
#include <vector>

using namespace std;

// 함수의 인자로 계속 넘겨주기엔 메모리 사이즈가 큼
vector<vector<string>> maps;

// 해당 위치에서 만들 수 있는 가장 큰 정사각형 땅의 크기 찾기 (좌측 상단 기준)
int FindMaxBoundSize(int x, int y)
{
	// 해당 위치에서 만들 수 있는 정사각형의 이론상의 최대 길이
	int max_length = min(maps.size() - x, maps[0].size() - y);

	// 탐색 방법: 크기가 1인 것부터 시작하여 겉부분에 1칸씩 크기를 늘려가면서 탐색
	for (int i = 0; i < max_length; ++i)
	{
		// 탐색 도중 선점 자리 발견 시 만들 수 있는 최대 크기: 현재 탐색 크기 - 1
		for (int j = 0; j <= i; ++j)
		{
			if (maps[x + j][y + i] != "-1")
			{
				return i;
			}
		}
		for (int j = 0; j <= i; ++j)
		{
			if (maps[x + i][y + j] != "-1")
			{
				return i;
			}
		}
	}

	return max_length;
}

int solution(vector<int> mats, vector<vector<string>> park)
{
	maps = park;

	// 만들 수 있는 가장 큰 정사각형 땅의 크기
	int max_size = 0;

	for (int i = 0; i < maps.size(); ++i)
	{
		for (int j = 0; j < maps[0].size(); ++j)
		{
			// 이미 돗자리가 깔린 경우
			if (maps[i][j] != "-1")
			{
				continue;
			}

			max_size = max(max_size, FindMaxBoundSize(i, j));
		}
	}

	// 가진 돗자리 중 가장 큰 크기
	int max_mat = -1;

	for (int mat : mats)
	{
		if (mat > max_size)
		{
			continue;
		}

		max_mat = max(max_mat, mat);
	}

	return max_mat;
}