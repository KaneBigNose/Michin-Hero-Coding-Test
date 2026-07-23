#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 접어야 하는 횟수를 찾는 재귀 함수
int FindFoldCount(vector<int> wallet, vector<int> bill, int current)
{
    // 큰 수가 0번으로 오게 정렬
    sort(wallet.begin(), wallet.end(), greater<int>());
    sort(bill.begin(), bill.end(), greater<int>());

    // 지갑에 들어가는 경우
    if (bill[0] <= wallet[0] && bill[1] <= wallet[1])
    {
        return current;
    }

    // 들어가지 않은 경우 큰 쪽을 반으로 접고 재시도
    bill[0] = bill[0] / 2;

    return FindFoldCount(wallet, bill, ++current);
}

int solution(vector<int> wallet, vector<int> bill)
{
    return FindFoldCount(wallet, bill, 0);
}