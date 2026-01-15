#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <unordered_map>
using namespace std;

int maxLen(vector<int>& nums, int tar) {
    unordered_map<int, int> prefixIndex;
    int sum = 0, maxlen = 0;
    int start = -1, end = -1;

    for (int i = 0; i < nums.size(); i++) {
        sum += nums[i];

        if (sum == tar) {
            maxlen = i + 1;
            start = 0;
            end = i;
        } 
        else if (prefixIndex.find(sum - tar) != prefixIndex.end()) {
            if (i - prefixIndex[sum - tar] > maxlen) {
                maxlen = i - prefixIndex[sum - tar];
                start = prefixIndex[sum - tar] + 1;
                end = i;
            }
        }

        // store prefix only if not already present
        if (prefixIndex.find(sum) == prefixIndex.end())
            prefixIndex[sum] = i;
    }

    if (maxlen > 0) {
        cout << "Subarray: ";
        copy(nums.begin() + start, nums.begin() + end + 1,
             ostream_iterator<int>(cout, " "));
        cout << endl;
    } else {
        cout << "No subarray found\n";
    }

    return maxlen;
}

int main() {
    vector<int> arr = {-5, -4, -3, -2, 0, 1, 2, 3, 4, 5};
    cout << "Length: " << maxLen(arr, 1);
}
