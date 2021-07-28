#include <limits.h>

void exchange(long &a, long &b){ // ����a, b��Ԫ��
    long temp;
    temp = a;
    a = b;
    b = temp;
}

void insertion_sort(long a[], int n){ // ��������
    int i, j;
    long key;
    for(j = 1; j < n; j++){
        key = a[j];
        i = j - 1;
        while(i >= 0 && a[i] > key){
            a[i+1] = a[i];
            i--;
        }
        a[i+1] = key;
    }
}

void merge_s(long a[], int p, int q, int r){ // �鲢_�ϲ�
    int n1 = q-p+1;
    int n2 = r-q;
    long L[n1+1], R[n2+1];
    int i, j, k;
    for(i = 0; i < n1; i++){
        L[i] = a[p+i];
    }
    for(j = 0; j < n2; j++){
        R[j] = a[q+1+j];
    }
    L[n1] = INT_MAX;
    R[n2] = INT_MAX;
    i = 0;
    j = 0;
    for(k = p; k <= r; k++){
        if(L[i] <= R[j]){
            a[k] = L[i];
            i++;
        }
        else{
            a[k] = R[j];
            j++;
        }
    }
}

void merge_sort(long a[], int p, int r){ // �鲢����
    if(p < r){
        int q = (p+r)/2;
        merge_sort(a, p, q);
        merge_sort(a, q+1, r);
        merge_s(a, p, q, r);
    }
}

void max_heapify(long a[], int i,int n){ // ���ֶ�����
    int l = 2*i;
    int r = (2*i)+1;
    int largest;
    int heap_size = n;
    if(l <= heap_size-1 && a[l] > a[i])
        largest = l;
    else
        largest = i;
    if(r <= heap_size-1 && a[r] > a[largest])
        largest = r;
    if(largest != i){
        exchange(a[i], a[largest]);
        max_heapify(a, largest, n);
    }
}

void build_max_heap(long a[],int n){ // ������
    int heap_size = n;
    for(int i = (heap_size-1)/2; i >=0; i--){
        max_heapify(a, i, n);
    }
}

void heapsort(long a[], int n){ // ������
    build_max_heap(a, n);
    int heap_size = n;
    for(int i = heap_size-1; i >= 1; i--){
        exchange(a[0], a[i]);
        heap_size--;
        max_heapify(a, 0, heap_size);
    }
}

int partition_q(long a[], int p, int r){ // ����_����
    int x = a[r];
    int i = p-1;
    for(int j = p; j < r; j++){
        if(a[j] <= x){
            i = i + 1;
            exchange(a[i], a[j]);
        }
    }
    exchange(a[i+1], a[r]);
    return (i+1);
}

void quicksort(long a[], int p, int r){ // ����
    if(p < r){
        int q = partition_q(a, p, r);
        quicksort(a, p, q-1);
        quicksort(a, q+1, r);
    }
}
