/*******************************************************
这里整理c语言常用算法，主要有：
交换算法
查找最小值算法
冒泡排序
选择排序
插入排序
shell排序 (希尔排序)
归并排序
快速排序
二分查找算法
查找重复算法
****************************************************/





//交换
void swap(int *a, int *b){
    int tmp=*a;
    *a=*b;
    *b=tmp;
}

//查找最小
int min(int x, int y) {
    return x < y ? x : y;
}

typedef struct _Range {
    int start, end;
} Range;

Range new_Range(int s, int e) {
    Range r;
    r.start = s;
    r.end = e;
    return r;
}


//冒泡排序
void looperSort(int *arr, int len){
    int i,j;
    for (i = 0; i < len - 1; ++i) {
        for (j = 0; j < len - 1-i; ++j) {
            if (arr[j]>arr[j+1]){
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

//选择排序
void selectSort(int *arr, int num){
    int min, i, j;
    for (i = 0; i < num - 1; ++i) {
        min=i;
        for (j = i+1; j < num; ++j) {
            if (arr[j]<arr[min]){
                min=j;
            }
        }
        if (min!=i)
            swap(&arr[min], &arr[i]);
    }
}

//插入排序
void insertSort(int *arr, int num){
    int i,j, tmp;
    for (i = 1; i < num; ++i) {
        tmp=arr[i];
        for (j = i; j > 0 && arr[j-1] > tmp; --j) {
            arr[j]=arr[j-1];
        }
        arr[j]=tmp;
    }
}

//希尔排序
void shellSort(int *arr, int num) {
    int gap, i, j, temp;
    for (gap = num >> 1; gap > 0; gap = gap >>= 1)
        for (i = gap; i < num; i++) {
            temp = arr[i];
            for (j = i - gap; j >= 0 && arr[j] > temp; j -= gap){
                arr[j + gap] = arr[j];
            }
            arr[j + gap] = temp;
        }
}

//归并排序
void mergeSort(int *arr, int num) {
    int* a = arr;
    int* b = (int*) malloc(num * sizeof(int));
    int seg, start;
    for (seg = 1; seg < num; seg += seg) {
        for (start = 0; start < num; start += seg + seg) {
            int low = start, mid = min(start + seg, num), high = min(start + seg + seg, num);
            int k = low;
            int start1 = low, end1 = mid;
            int start2 = mid, end2 = high;
            while (start1 < end1 && start2 < end2){
                b[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
            }
            while (start1 < end1){
                b[k++] = a[start1++];
            }
            while (start2 < end2){
                b[k++] = a[start2++];
            }
        }
        int* temp = a;
        a = b;
        b = temp;
    }
    if (a != arr) {
        int i;
        for (i = 0; i < num; i++)
            b[i] = a[i];
        b = a;
    }
    free(b);
}


void merge_sort_recursive(int arr[], int reg[], int start, int end) {
    if (start >= end)
        return;
    int len = end - start, mid = (len >> 1) + start;
    int start1 = start, end1 = mid;
    int start2 = mid + 1, end2 = end;
    merge_sort_recursive(arr, reg, start1, end1);
    merge_sort_recursive(arr, reg, start2, end2);
    int k = start;
    while (start1 <= end1 && start2 <= end2)
        reg[k++] = arr[start1] < arr[start2] ? arr[start1++] : arr[start2++];
    while (start1 <= end1)
        reg[k++] = arr[start1++];
    while (start2 <= end2)
        reg[k++] = arr[start2++];
    for (k = start; k <= end; k++)
        arr[k] = reg[k];
}

//归并排序 递归
void mergeSort2(int *arr, const int len) {
    int reg[len];
    merge_sort_recursive(arr, reg, 0, len - 1);
}


//快速排序
void quickSort(int *arr, const int num) {
    if (num <= 0)
        return; // 避免len等於負值時引發段錯誤（Segment Fault）
    // r[]模擬列表,p為數量,r[p++]為push,r[--p]為pop且取得元素
    Range r[num];
    int p = 0;
    r[p++] = new_Range(0, num - 1);
    while (p) {
        Range range = r[--p];
        if (range.start >= range.end)
            continue;
        int mid = arr[(range.start + range.end) / 2]; // 選取中間點為基準點
        int left = range.start, right = range.end;
        do
        {
            while (arr[left] < mid) ++left;   // 檢測基準點左側是否符合要求
            while (arr[right] > mid) --right; //檢測基準點右側是否符合要求

            if (left <= right)
            {
                swap(&arr[left],&arr[right]);
                left++;right--;               // 移動指針以繼續
            }
        } while (left <= right);

        if (range.start < right) r[p++] = new_Range(range.start, right);
        if (range.end > left) r[p++] = new_Range(left, range.end);
    }
}

void quick_sort_recursive(int arr[], int start, int end) {
    if (start >= end)
        return;
    int mid = arr[end];
    int left = start, right = end - 1;
    while (left < right) {
        while (arr[left] < mid && left < right)
            left++;
        while (arr[right] >= mid && left < right)
            right--;
        swap(&arr[left], &arr[right]);
    }
    if (arr[left] >= arr[end])
        swap(&arr[left], &arr[end]);
    else
        left++;
    if (left)
        quick_sort_recursive(arr, start, left - 1);
    quick_sort_recursive(arr, left + 1, end);
}
//快速排序 递归
void quickSort2(int *arr, int len) {
    quick_sort_recursive(arr, 0, len - 1);
}

//二分查找
int halfSearch(int key, int *a, int n) //自定义函数binary_search()
{
    int start=0;
    int end=n-1;
    while (start<=end){
        int middle=(start+end)/2;
        if (key<a[middle]){
            end=middle-1;
        } else if (key>a[middle]){
            start=middle+1;
        } else{
            return middle;
        }
    }
    return -1;
}

//查找重复
void searchRepeat(int *arr, int num, int searchKey){
    for (int i = 0; i < num; ++i) {
        for (int j = i+1; j < num; ++j) {
            if (arr[i]==arr[j]){
                LOGI("repeat num index:%d", i);
                break;
            }
        }
    }
}
原文链接：https://blog.csdn.net/mhhyoucom/article/details/87929783