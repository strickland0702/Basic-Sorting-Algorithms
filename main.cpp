#include <iostream>
#include <cmath>
using namespace std;
void merge(int array[], int left, int mid, int right);
void mergeTwo(int array[],int left,int mid,int right);
int partition(int array[], int left, int right);
int ChoosePivot(int array[], int left, int right);

void swap(int &a, int &b){
    int c = a;
    a = b;
    b = c;
}

// 插入排序
void insertion_sort(int array[], int n){
    for (int i = 1; i<n; i++){
        int temp = array[i];
        int j = i-1;
        while ((j >=0) && (temp < array[j])){
            array[j+1] = array[j];
            j--;
        }
        array[j+1] = temp;
    }
}

// 选择排序
void selection_sort(int array[], int n){
    for (int i=0;i<n-1;i++){
        int min_index = i;
        for (int j=i; j<n;j++){
            if (array[j] < array[min_index]){
                min_index = j;
            }
        }
        swap(array[min_index], array[i]);
    }
}

//冒泡排序
void bubble_sort(int array[], int n){
    for (int i = n-1; i>=0; i--){
        for (int j=0; j<i;j++){
            if (array[j] > array[j+1]){
                swap(array[j], array[j+1]);
            }
        }
    }
}

//归并排序
void merge_sort(int a[], int left, int right){
    if (left >= right) return;
    int mid = (left + right)/2;
    merge_sort(a, left, mid);
    merge_sort(a, mid+1, right);
    merge(a, left, mid, right);
}

void merge(int array[], int left, int mid, int right){
    int i = 0;
    int j = 0;
    int k = left;
    int left_size = mid - left +1;
    int right_size = right - mid;
    int a[left_size];
    int b[right_size];

    // 将原数组拷贝进A,B当中
    while (i < left_size){
        a[i] = array[left + i];
        i++;
    }

    while(j < right_size){
        b[j] = array[mid+1+j];
        j++;
    }

    // 尽可能取A,B中最小的数直到两者其中一个数组被取尽
    i = 0;
    j = 0;
    while ((i < left_size) && (j < right_size)){
        if(a[i] <= b[j]) array[k++] = a[i++];
        else array[k++] = b[j++];
    }

    //在新数组后衔接剩余的数
    if (i == left_size){
        while(j < right_size) array[k++] = b[j++];
    }
    else{
        while(i < left_size) array[k++] = a[i++];
    }
}

// CS Merge Sort
void mergeSort(int array[],int left,int right){
    if (left>=right) return;
    int mid=(left+right)/2;
    mergeSort(array,left,mid);
    mergeSort(array,mid+1,right);
    mergeTwo(array,left,mid,right);
}

void mergeTwo(int array[],int left,int mid,int right){
    int num1=mid-left+1;
    int num2=right-mid;
    int c[num1];
    int d[num2];
    int i=0;
    int j=0;
    int k=left;
    for (int m=0;m<num1;m++){
        c[m]=array[left+m];
    }


    for (int n=0;n<num2;n++){
        d[n]=array[mid+1+n];
    }
    while (i<num1 && j<num2){
        if (c[i]<=d[j]){
            array[k]=c[i];
            i++;
            k++;
        }
        else {
            array[k]=d[j];
            j++;
            k++;
        } }
    if (i==num1){
        for (int s=j;s<num2;s++){
            array[k]=d[s];
            k++;
        } }
    else {
        for (int s=i;s<num1;s++){
            array[k]=c[s];
            k++;
        } }
}

//快速排序
void quick_sort(int array[], int left, int right){
    //快排母函数
    if (left >= right) return;
    int pivotat = partition(array, left, right); // index of the pivot
    quick_sort(array, left, pivotat-1);
    quick_sort(array, pivotat+1, right);
}

int partition(int array[], int left, int right){
    // 选取数组的首个元素为pivot
    int pivot = array[left];
    int i = left + 1;
    int j = right;

    do{
        while(array[i] < pivot) i++;
        while(array[j] > pivot) j--;
        if (i < j) swap(array[i], array[j]);
    }while(i < j);

    swap(array[j], array[left]);

    int pivotat = j;
    return pivotat;
}

//计数排序简单实现，不稳定
void easy_counting_sort(int* array, int length){
    if (array == nullptr || length <= 0)
        return;

    //确定数列最大值
    int max = array[0];
    for (int i = 1; i < length; ++i){
        if (array[i] > max)
            max = array[i];
    }

    // 确定统计数组长度并进行初始化
    int* count = new int[max + 1];
    for (int i = 0; i <= max; ++i)
        count[i] = 0;

    // 遍历数组，统计每个数出现的次数
    for (int i = 0; i < length; i++)
        count[array[i]]++;

    // 排序数组，某个数出现了几次，便在data里累计输出几次
    int index = 0;
    for (int i = 0; i <= max; i++)
    {
        for (int j = 0; j < count[i]; j++)
        {
            array[index++] = i;
        }
    }

    delete[] count;
}

// 优化计数排序，稳定
void general_counting_sort(int array[], int length, int max){
    // 确定统计数组长度并进行初始化
    int* count = new int[max + 1];
    for (int i = 0; i <= max; i++)
        count[i] = 0;

    // 遍历数组，统计每个数出现的次数
    for (int i = 0; i < length; i++)
        count[array[i]]++;

    for (int i=1; i<= max; i++)
        count[i] = count[i] + count[i - 1];

    int *sort_array = new int[length];
    for (int i=length-1; i>=0; i--){
        sort_array[count[array[i]] - 1] = array[i];
        count[array[i]]--;
    }

    for (int i=0; i<length; i++){
        array[i] = sort_array[i];
    }

    delete[] count;
    delete[] sort_array;
}

//桶排序
void bucket_sort(int array[], int length, int max){

//    int* container_1 = new int[length];
//    int* container_2 = new int[length];
//    int* container_3 = new int[length];
//
//    int pt1 = 0;
//    int pt2 = 0;
//    int pt3 = 0;
//
//    //分配原数组元素到每一个桶内
//    for (int i=0;i<length;i++){
//        if (0 <= array[i] && array[i] <= 3){
//            container_1[pt1++] = array[i];
//        }
//        else if (4 <= array[i] && array[i] <= 6){
//            container_2[pt2++] = array[i];
//        }
//        else{
//            container_3[pt3++] = array[i];
//        }
//    }
//
//    //每个桶内分别简单排序
//    insertion_sort(container_1, pt1);
//    insertion_sort(container_2, pt2);
//    insertion_sort(container_3, pt3);
//
//    //赋值给原数组
//    int m = 0;
//    for (int i=0;i<pt1;i++){
//        array[m++] = container_1[i];
//    }
//    for (int i=0;i<pt2;i++){
//        array[m++] = container_2[i];
//    }
//    for (int i=0;i<pt3;i++){
//        array[m++] = container_3[i];
//    }

    int** container = new int* [3];
    for (int i=0;i<3; i++){
        container[i] = new int [length];
    }

    int *pt = new int[3];
    for (int i=0;i<3;i++){
        pt[i] = 0;
    }


    //分配原数组元素到每一个桶内
    for (int i=0;i<length;i++){
        if (0 <= array[i] && array[i] <= max/3){
            container[0][pt[0]++] = array[i];
        }
        else if (max/3 < array[i] && array[i] <= 2*max/3){
            container[1][pt[1]++] = array[i];
        }
        else{
            container[2][pt[2]++] = array[i];
        }
    }

    //每个桶内分别简单排序
    for (int i=0;i<3;i++)
        insertion_sort(container[i], pt[i]);

    //赋值给原数组
    int m = 0;
    for (int i = 0; i<3; i++){
        for (int j=0;j<pt[i];j++){
            array[m++] = container[i][j];
        }
    }
}

// 随机选择：从长度为n的数组中选出第i小的数
// 即排好序选取序号为j的数

int randomized_selection(int *array, int left, int right, int target)
{
    if(left < right){
        int j = partition(array, left, right);
        if(j == target)
            return array[j];
        else if(j > target)
            return randomized_selection(array, left, j - 1, target);
        else
            return randomized_selection(array, j + 1, right, target);
    }
    else return array[left];
}

//时间线性选择
int deterministic_selection(int array[], int left, int right, int target){
    if(left < right){
        int pivot = ChoosePivot(array, left,right);
        // 这里需要添加以pivot为基准分割的partition函数
        int j = partition(array, left, right);
        if(j == target)
            return array[j];
        else if(j > target)
            return randomized_selection(array, left, j - 1, target);
        else
            return randomized_selection(array, j + 1, right, target);
    }
    else return array[left];
}

int ChoosePivot(int array[], int left, int right)
{
    int size = right - left + 1;
    int sub_num = size/5 ;
    int i, j, k=0;
    int tmp[sub_num][5];
    int Sub[sub_num];

    for(i=0; i<sub_num; i++){
        for(j=0; j<5; j++)
            tmp[i][j] = array[k++];
        Sub[i] = deterministic_selection(tmp[i], 0, 4, 2);
    }

    return deterministic_selection(Sub , 0, sub_num-1, sub_num/2);
}


int main() {
    int arr[8] = {2,5,0,8,3,7,9,4};
    int length = 8;
    // insertion_sort(arr, length);
    // selection_sort(arr,length);
    // bubble_sort(arr,length);

    // merge_sort(arr, 0, length-1);
     quick_sort(arr,0,length-1);

    // easy_counting_sort(arr, length);
    // general_counting_sort(arr, length, 9);
    // bucket_sort(arr, 8,9);
    // cout << random_selection(arr, 8,3) << endl;
    // cout << randomized_selection(arr, 0, 7, 7) << endl;
    for (int i = 0; i < length; i++){
        cout << arr[i] << endl;
    }
    return 0;
}

