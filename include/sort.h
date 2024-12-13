#ifndef __SORT_H__
#define __SORT_H__

int BinarySearchIterative(int *arr , size_t size , int k);
int BinarySearchRecursive(int *arr ,int start, int end , int k);
int MergeSort(int *arr_to_sort, size_t num_of_element);
void Qsort(void *base, size_t nmemb, size_t size,
                  int (*compar)(const void *, const void *));
/*
#define ARR_SIZE 50
void RealCountingSort(int array[], int size, int place) ;
void Creat2Arr(int arr[], int arr2[]);
void RadixSort(int arr[], size_t size);
int *CreatArr(int arr[]);
void BubleSort(int *arr, size_t size);
void SelectionSort(int arr[], int n);
void insertionSort(int arr[], int n);
void FindMinMax(int *arr , size_t size, int *min_num , int *max_num );
void CountingSort(int arr[], size_t n);
*/
#endif /*__SORT_H__*/
