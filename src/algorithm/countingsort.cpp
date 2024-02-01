#include <vector>

using namespace std;

/* 计数排序通过统计元素数量来实现排序，通常应用于整数数组。
 */
/* 计数排序 */
// 简单实现，无法用于排序对象
void countingSortNaive(vector<int> &nums)
{
    // 1. 统计数组最大元素 m
    int m = 0;
    for (int num : nums) {
        m = max(m, num);
    }
    // 2. 统计各数字的出现次数
    // counter[num] 代表 num 的出现次数
    vector<int> counter(m + 1, 0);
    for (int num : nums) {
        counter[num]++;
    }
    // 3. 遍历 counter ，将各元素填入原数组 nums
    int i = 0;
    for (int num = 0; num < m + 1; num++) {
        for (int j = 0; j < counter[num]; j++, i++) {
            nums[i] = num;
        }
    }
}

int main(int argc, char *argv[])
{
    return 0;
}
