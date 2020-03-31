//
// Created by hyy on 2020/3/31.
//

#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        if(nums.size()==0 || nums.size()<2){
            return nums;
        }
//        QuickSort(nums, 0, nums.size()-1);
//        mergeSort(nums, 0, nums.size()-1);
        heapSort(nums, 0 , nums.size()-1);
        return nums;
    }

    //快排,不稳定

    void QuickSort(vector<int>& nums, int l, int r) {
        if(l<r) {
            srand((int)time(0));
            int x = rand() % (r-l+1)+l;
            swap(nums[x], nums[r]);

            vector<int> jie(2,0);
            jie = Qpartition(nums, l, r);

            QuickSort(nums, l, jie[0]-1);
            QuickSort(nums, jie[1]+1, r);
        }

    }

    vector<int> Qpartition(vector<int>& nums, int l, int r){
        int less = l-1;
        int more = r;
        vector<int> jie;
        int i = l;
        while (i < more){
            if(nums[i]<nums[r]){
                less++;
                swap(nums[less], nums[i]);
                i++;
            } else if (nums[i]>nums[r]) {
                more--;
                swap(nums[i],nums[more]);
            } else {
                i++;
            }
        }
        swap(nums[more], nums[r]);
        jie.push_back(less+1);
        jie.push_back(more);
        return jie;
    }

    void swap(int &a, int &b){
        a = a^b;
        b = a^b;
        a = a^b;
    }

    //归并排序，稳定
    void mergeSort(vector<int>& nums, int l, int r){
        if(l==r){
            return;
        }
        int mid = l + ((r-l)>>1);
        mergeSort(nums, l , mid);
        mergeSort(nums, mid+1, r);
        merge(nums, l, mid, r);
    }
    void merge (vector<int> &nums, int l, int mid, int r){
        vector<int> help(r-l+1);
        int i = 0;
        int p1 = l;
        int p2 = mid+1;
        while (p1<=mid && p2<=r){
            if(nums[p1]<nums[p2]){
                help[i] = nums[p1];
                p1++;
                i++;
            } else {
                help[i] = nums[p2];
                i++;
                p2++;
            }
        }
        while (p1<=mid){
            help[i++] = nums[p1++];
        }
        while(p2<=r){
            help[i++] = nums[p2++];
        }
        for(i=0;i<help.size();++i){
            nums[l+i] = help[i];
        }
    }

    //堆排序，不稳定
    void heapSort(vector<int>& nums, int l, int r){
        for (int i =0;i<nums.size();++i){
            heapInsert(nums, i);
        }

        int size = nums.size();
        swap(nums[0], nums[--size]);
        while(size>0){
            heapBuild(nums, 0 ,size);
            swap(nums[0], nums[--size]);
        }
    }

    void heapInsert(vector<int>& nums, int index){
        while(nums[index]>nums[(index-1)/2]){
            swap(nums[index],nums[(index-1)/2]);
            index = (index-1)/2;
        }
    }

    void heapBuild(vector<int> &nums, int index, int size){
        int left = index*2 +1;
        while (left<size) {
            int max_child_pos;
            int max_child_value;
            if(left+1<size && nums[left+1] > nums[left]){
                max_child_pos = left+1;
            } else {
                max_child_pos = left;
            }
            if(max_child_pos==index){
                break;
            }
            swap(nums[max_child_pos], nums[index]);
            index = max_child_pos;
            left = index*2+1;
        }
    }


};

int main(){
    Solution s;
    vector<int> nums = {1,8,6,4,3,7,5,2};
    for(int i = 0;i<nums.size();++i){
        cout<<nums[i]<<" ";
    }
    cout<<endl;
    s.sortArray(nums);
    for(int i = 0;i<nums.size();++i){
        cout<<nums[i]<<" ";
    }

    return 0;
}