#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <climits>
#include <ctime>
#include <cassert>

using namespace std;

void swap(int &a, int &b);
void bubble(int *array, int n);
void insertion(int *array, int n);
void selection(int *array, int n);
void mergesort(int *array, int n);
void quick(int *array, int n);
int random(int *array, int n, int location);
int deterministic(int *array, int n, int location);
int partition(int *array, int left, int right);
int partit(int *array, int left, int right, int pivotat);


int main() {
	int type;
	int number;
	cin>>type>>number;
	if(type<5){
		int a[number];
		for(int i = 0; i < number; i++){
			cin>>a[i];
		}
		switch(type){
			case 0:
			bubble(a,number);
			break;
			case 1:
			insertion(a,number);
			break;
			case 2:
			selection(a,number);
			break;
			case 3:
			mergesort(a,number);
			break;
			case 4:
			quick(a,number);
			break;
		} 
		for(int j = 0; j < number; j++){
			cout<<a[j]<<endl;
		}
	}
	else{
		int location;
		cin>>location;
		int a[number];
		for(int i = 0; i < number; i++){
			cin>>a[i];
		}		
		if(type == 5) cout<<"The order-"<<location<<" item is "<<random(a,number,location)<<endl;
		else cout<<"The order-"<<location<<" item is "<<deterministic(a,number,location)<<endl;
	}
    return 0;
}


void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

void bubble(int *array, int n){
    for(int i = n - 2; i >= 0; i--){
        for(int j = 0; j <= i; j++){
            if(array[j] > array[j+1]){
                swap(array[j], array[j+1]);
            }
        }
    }
}

void insertion(int *array, int n){
    for(int i = 1; i < n; i++){
        int t = array[i];
        int location = 0;
        for(int j = i - 1; j >=0; j--){
            if(array[j] > t){
                array[j + 1] = array[j];
            }
            else{
                location = j + 1;
                break;
            }
        }
        array[location] = t;
    }
}

void selection(int *array, int n){
    for(int i = 0; i < n - 1; i ++){
        int t = i;
        for(int j = i + 1; j < n; j++){
            if(array[t] > array[j]) t = j;
        }
        swap(array[i], array[t]);
    }
}

void merge(int *a, int left, int mid, int right){
    int i = left, j = mid + 1, k = 0;
    int *c = new int[right - left + 1];
    while(i <= mid && j <= right){
        if(a[i] <= a[j]) c[k++] = a[i++];
        else c[k++] = a[j++];
    }
    while(i <= mid) c[k++] = a[i++];
    while(j <= right) c[k++] = a[j++];
    for(int m = 0; m <= right - left; m++) a[left + m] = c[m];
    delete[] c;
}
static void merge_helper(int *array, int left, int right){
    if(left >= right) return;
    int mid = (int)(left+right)/2;
    merge_helper(array, left, mid);
    merge_helper(array, mid + 1, right);
    merge(array, left, mid, right);
}
void mergesort(int *array, int n){
    merge_helper(array, 0, n - 1);
}

int partition(int *array, int left, int right){
    int i = left+1;
    int j = right;
    int p = left + rand()%(right - left + 1);
    int pivot = array[p];
    swap(array[left],array[p]);
    if(i == j){
        if(array[left]<=array[right]) return left;
        else{
            swap(array[left],array[right]);
            return right;
        }
    }
    while(i<j){
        while(array[i] < pivot && i <= right){i++;}
        while(array[j] >= pivot && j > left){j--;}
        if(i < j) swap(array[i],array[j]);
    }
    swap(array[left],array[j]);
    return j;
}
static void quick_helper(int *array, int left, int right){
    int pivotat = 0;
    if(left >= right) return;
    pivotat = partition(array, left, right);
    quick_helper(array, left, pivotat - 1);
    quick_helper(array, pivotat + 1, right);

}
void quick(int *array, int n){
    quick_helper(array, 0, n - 1);
}


int random_helper(int *array, int left, int right, int location){
    if(right - left == 0) return array[left];
    int pivotat;
    pivotat = partition(array, left, right);
    if(pivotat == location) return array[pivotat];
    if(pivotat > location) return random_helper(array, left, pivotat-1, location);
    else return random_helper(array, pivotat+1, right, location);
}
int random(int *array, int n, int location){
    return random_helper(array, 0, n - 1, location);
}


int partit(int *array, int left, int right, int pivotat){
    int i = left + 1;
    int j = right;
    for(int m = left; m <= right; m++){
        if(pivotat == array[m]){
            swap(array[m], array[left]);
            break;
        }
    }
    if(i == j){
        if(array[left]<=array[right]) return left;
        else{
            swap(array[left],array[right]);
            return right;
        }
    }
    while(i<j){
        while(array[i] < pivotat && i <= right){i++;}
        while(array[j] >= pivotat && j > left){j--;}
        if(i < j) {
            swap(array[i],array[j]);}
    }
    swap(array[left],array[j]);
    return j;
}
int d_helper(int *array, int left, int right, int location){
    if(right - left == 0) return array[left];
    int n = right - left +1;
    int number = n/5;
    int medians[number];
    int j;
    if(n>=5){
        int i;
        for(i = 0; i < n - 4; i += 5){

            selection(array+ left + i, 5);

            medians[i/5] = array[left + i + 2];

        }
        int p = d_helper(medians, 0, number - 1, number/2);
        j = partit(array, left, right,p);
    }
    else {j = partition(array, left, right);}
    if(j == location) return array[j];
    if(j > location) return d_helper(array, left, j - 1, location);
    else return d_helper(array, j + 1, right, location);
}
int deterministic(int *array, int n, int location){
    return d_helper(array, 0, n - 1, location);
}

