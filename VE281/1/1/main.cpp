#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<int*> findTriplet(vector<int>&nums, int n);

int main() {
    return 0;
}

vector<int*> findTriplet(vector<int>&nums, int n){
    vector<int*> vec;
    sort(nums.begin(),nums.end());
    int i, j, k;
    bool is_Empty = true;
    for(i = 0;i<n-1;i++){
        k = n - 1, j = i + 1;
        while(k != j){
            if(nums[i] + nums[j] + nums[k] < 0){
                j++;
            }
            else if(nums[i] + nums[j] + nums[k] > 0){
                k --;
            }
            else{
                if(!is_Empty){
                    if(vec.back()[0] != nums[i] || vec.back()[1] != nums[j] || vec.back()[2] != nums[k]){
                        int a[3] = {nums[i], nums[j], nums[k]};
                        vec.push_back(new int[3](a));
                        is_Empty = false;
                    }
                }
                else{
                    int a[3] = {nums[i], nums[j], nums[k]};
                    vec.push_back(new int[3](a));
                    is_Empty = false;
                }
                j++;
                k--;
            }
        }
    }
}