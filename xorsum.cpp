 #include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <unordered_map>
using namespace std;
 int subarraysWithXorK(vector<int> &nums, int k) {
     int xsum=0;
     int c=0;
     int x=0;
     unordered_map<int ,int>m;

       for(int i=0;i<nums.size();i++){
        m[xsum]++;
        xsum^=nums[i];
        x=xsum^k;

        c+=m[x];
        


       }
    return c;}
        int main() {
    vector<int> arr = {4,2,2,6,4};
    cout << "Count: " << subarraysWithXorK(arr,6);
}
