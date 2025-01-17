#include <iostream>
#include <vector>

using namespace std;

/* 选择排序: 开启一个循环，每轮从未排序区间选择最小的元素，将其放到已排序区间的末尾。*/
void selectionSort(vector<int> &nums)
{
    int n = nums.size();
    // 外循环：未排序区间为 [i, n-1]
    for (int i = 0; i < n - 1; i++) {
        // 内循环：找到未排序区间内的最小元素
        int k = i;
        for (int j = i + 1; j < n; j++) {
            if (nums[j] < nums[k])
                k = j; // 记录最小元素的索引
        }
        // 将该最小元素与未排序区间的首个元素交换
        swap(nums[i], nums[k]);
    }
}

void print(vector<int> &nums)
{
    for (const int num : nums) {
        cout << num << " ";
    }
    cout << endl;
}

int main(int argc, char *argv[])
{
    vector<int> nums{ 20, 10, 43, 33, 44 };
    print(nums);
    selectionSort(nums);
    print(nums);
    return 0;
}
