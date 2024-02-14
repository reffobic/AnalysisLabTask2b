#include <iostream>

using namespace std;

// A class for Min Heap
class MaxHeap{
    int *heap_array; // pointer to array of elements in heap
    int capacity; // maximum possible size of min heap
    int heap_size; // Current number of elements in min heap

public:
    // Constructor: Initialise a capacity and heap_array;
    MaxHeap(int capacity){
        this->heap_size = 0;
        this->capacity = capacity;
        this->heap_array = new int[capacity];
    }

    // method to heapify a subtree with the root at given index i
    void MaxHeapify(int i){
        /* A recursive method to heapify 'heap_array' */
        int l = left(i);
        int r = right(i);

        int largest = i;
        if (l < heap_size && heap_array[l] > heap_array[i])
            largest = l;
        if (r < heap_size && heap_array[r] > heap_array[largest])
            largest = r;

        if (largest != i){
            swap(heap_array[i], heap_array[largest]);
            MaxHeapify(largest);
        }
    }

    // method to get index of parent of node at index i
    int parent(int i){ return (i-1)/2; }

    // method to get index of left child of node at index i
    int left(int i){ return (2*i + 1); }

    // method to get index of right child of node at index i
    int right(int i){ return (2*i + 2); }

    // method to remove minimum element (or root) from min heap
    int extractMax() {
        if (heap_size <= 0)
            return INT_MAX;

        if (heap_size == 1) {
            heap_size--;
            return heap_array[0];
        }

        int root = heap_array[0];
        heap_array[0] = heap_array[heap_size - 1];
        heap_size--;
        MaxHeapify(0);

        return root;
    }

    // method to decrease key value of key at index i to new_val
    void increaseKey(int i, int new_val) {
        heap_array[i] = new_val;
        while (i != 0 && heap_array[parent(i)] < heap_array[i]) {
            swap(heap_array[i], heap_array[parent(i)]);
            i = parent(i);
        }
    }

    // Returns the minimum key (key at root) from min heap
    int getMax(){ return heap_array[0]; }

    // method deletes key at index i
    // (It first reduced value to minus infinite, then calls extractMin() )
    void deleteKey(int i){
        increaseKey(i, INT_MAX);
        extractMax();
    }

    // method to inserts a new key 'k'
    void insertKey(int k){
        if (heap_size == capacity){
            cout << "\nOverflow: Could not insertKey\n";
            return;
        }

        // Inserting the new key at the end
        int i = heap_size;
        heap_array[heap_size++] = k;

        while (i != 0 && heap_array[parent(i)] < heap_array[i]){
            swap(heap_array[i], heap_array[parent(i)]);
            i = parent(i);
        }
    }

    // method to build a min heap from array
    void BuildMaxHeap(int* A, int n) {
        // Copy the given array to the heap array
        for (int i = 0; i < n; ++i) {
            heap_array[i] = A[i];
        }

        // Update the size of the heap
        heap_size = n;

        // Heapify each node in reverse order
        for (int i = n / 2 - 1; i >= 0; --i) {
            MaxHeapify(i);
        }
    }

    //utility function to preview heap_array
    void heap_array_preview()
    {
        for(int i = 0; i < heap_size; ++i) {
            cout << heap_array[i] << ' ';
        }
        cout << endl;
    }

    void heapSort(int* arr, int size) {

        for (int i = size / 2 - 1; i >= 0; i--){
            MaxHeapify(arr[i]);
        }

        for (int i = size - 1; i > 0; i--){
            swap(arr[0], arr[i]);
            MaxHeapify(arr[i]);
        }

    }

    void push(int k) {
        if (heap_size == capacity) {
            cout << "\nOverflow: Could not push\n";
            return;
        }

        int i = heap_size;
        heap_array[heap_size++] = k;

        while (i != 0 && heap_array[parent(i)] < heap_array[i]) {
            swap(heap_array[i], heap_array[parent(i)]);
            i = parent(i);
        }
    }

    void pop(int &poppedValue) {
        if (heap_size <= 0) {
            cout << "\nHeap is empty: Could not pop\n";
            return;
        }

        poppedValue = heap_array[0];

        if (heap_size == 1) {
            heap_size--;
            return;
        }

        heap_array[0] = heap_array[heap_size - 1];
        heap_size--;
        MaxHeapify(0);
    }

};

// Driver program to test above functions
int main(){

    int popped;

    MaxHeap h(11);
    h.push(15);
    h.push(2);
    h.push(3);
    h.push(1);
    h.push(45);
    h.push(5);
    h.push(4);

    cout << "maximum element: " << h.extractMax() << endl;
    cout << "second maximum element: " << h.getMax() << endl;

    h.pop(popped);
    cout << "After pop, top element: " << popped << endl;

    int arr[11] = {40, 10, 50, 90, 11, 20, 60, 70, 80, 30, 100};
    MaxHeap h2(11);
    h2.BuildMaxHeap(arr, 11);
    h2.heapSort(arr, 11);
    h2.heap_array_preview();

    for(int i = 0; i < 11; ++i) {
        cout << h2.extractMax() << ' ';
    }

    return 0;
}