
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#define NUM 10	 
#include <time.h>
using namespace std;
template <class T>
class Node{
public:
	Node *left;
	Node *right;
	T data;

	Node() : left(NULL), right(NULL){}
	~Node(){}
};


class Sort{
public:
	Sort(){};
	~Sort(){};
	
	template <class T>
	void QuickSort(T arr[], int low, int hight);

	
	template <class T>
	void SelectSort(T arr[], int len);

	
	template <class T>
	void BubbleSort(T arr[], int len);

	
	template <class T>
	void InsertSort(T arr[], int len);

	
	template <class T>
	void HeapSort(T arr[], int len);

	
	template <class T>
	void TreeSort(T arr[], int len);

private:
	
	template <class T>
	int Quick(T arr[], int left, int right);

	
	template <class T>
	void CreateHeap(T arr[], int root, int len);

	
	template <class T>
	Node<T>* BuildTree(Node<T>*root, T data);

	
	template <class T>
	void InTree(Node<T> *root, T arr[]);
};


int main(){
	Sort sort;
	int *arr; 								
	int width = 0; 							
	int len;
	cin>>len;
	arr = (int *)malloc(len * sizeof(int)); 
	if(arr == NULL){						
		cout << "Malloc failed!" << endl;
		exit(1);
	}

	srand(time(NULL));						
	for(int i = 0; i < len ;i++){			
		
		cin>>arr[i];
	}

	
	sort.SelectSort(arr, len);

	


	for(int i = 0; i < len; i++){			
		cout << arr[i] << " ";
		
		if((i + 1) % NUM == 0){				
			cout << endl;
		}
	}

	cout << endl;
	return 0;
}



template <class T>
void Sort::QuickSort(T arr[], int low, int hight){
	int pivot = -1;
	if(low <= hight){
		pivot = Quick(arr, low, hight);
		QuickSort(arr, low, pivot - 1);
		QuickSort(arr, pivot + 1, hight);
	}
}


template <class T>
int Sort::Quick(T arr[], int left, int right){
	int i = left + 1, j = right;
	int flag = left;
	int temp;

	while(i <= j){
		while(i <= j && arr[i] < arr[flag]){
			++i;
		}
		while(i <= j && arr[j] > arr[flag]){
			--j;
		}
		if(i < j){
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			++i;
			--j;
		}
	}

	temp = arr[flag];
	arr[flag] = arr[j];
	arr[j] = temp;
	return j;
}



template <class T>
void Sort::SelectSort(T arr[], int len){
	int index;
	T temp;
	for(int i = 0; i < len - 1; i++){
		index = i;
		for(int j = i + 1; j < len; j++){
			if(arr[index] > arr[j]){
				index = j;
			}
		}
		if(index != i){
			temp = arr[index];
			arr[index] = arr[i];
			arr[i] = temp;
		}
	}
}



template <class T>
void Sort::BubbleSort(T arr[], int len){
	T temp;
	bool flags = true;
	for(int i = len - 1; i > 0; i--){
		if(flags){
			flags = false;
			for(int j = 0; j < i; j++){
				if(arr[j] > arr[j + 1]){
					flags = true;
					temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;
					for(int k = 0; k < len; k++){
						cout << arr[k] << " ";
					}
					cout << endl;
				}
			}
		}else{
			break;
		}
	}
}



template <class T>
void Sort::InsertSort(T arr[], int len){
	T temp;
	int i, j;
	for(i = 1; i < len; i++){
		temp = arr[i];
		for(j = i - 1; j >= 0; j--){
			if(temp < arr[j]) {
				arr[j + 1] = arr[j];
			}else{
				break;
			}
		}
		arr[j + 1] = temp;
	}
}



template <class T>
void Sort::HeapSort(T arr[], int len){
	int i;
	T buff;
	T *temp = (T *)malloc(sizeof(T) * (len + 1));
	if(temp == NULL){
		cout << "Malloc Error!" << endl;
		exit(1);
	}
	for(i = 1; i < len + 1; i++){ 
		temp[i] = arr[i - 1];
	}

	
	for(i = len / 2; i >= 1; i--){
		CreateHeap(temp, i, len);
	}

	for(i = len - 1; i >= 1; i--){
		buff = temp[1];
		temp[1] = temp[i + 1];
		temp[i + 1] = buff;

		CreateHeap(temp, 1, i);
	}

	for(i = 1; i < len + 1; i++){
		arr[i - 1] = temp[i];
	}
}


template <class T>
void Sort::CreateHeap(T arr[], int root, int len){
	int j = 2 * root; 					
	T temp = arr[root];
	bool flags = false;

	while(j <= len && !flags){
		if(j < len){
			if(arr[j] < arr[j + 1]){		
				++j; 						
			}
		}

		if(temp < arr[j]){
			arr[j / 2] = arr[j];
			j *= 2;
		}else{
			flags = true;
		}
	}
 	arr[j / 2]  = temp;
}



template <class T>
void Sort::TreeSort(T arr[], int len){
	Node <T>*root = NULL;
	for(int i = 0; i < len; i++){
		root = BuildTree(root, arr[i]);
	}

	InTree(root, arr);
}


template <class T>
Node<T>* Sort::BuildTree(Node<T>*root, T data){
	Node<T> *tempNode = root;
	Node<T> *parentNode = NULL;

	Node<T> *newNode = new Node<T>;
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;

	if(root == NULL){
		return newNode;
	}else{
		while(tempNode != NULL){
			parentNode = tempNode;
			if(tempNode->data >= data){
				tempNode = tempNode->left;
			}else{
				tempNode = tempNode->right;
			}
		}

		if(parentNode->data >= data){
			parentNode->left = newNode;
		}else{
			parentNode->right = newNode;
		}
	}

	return root;
}


template <class T>
void Sort::InTree(Node<T> *root, T arr[]){
	static int index = 0;
	if(root != NULL){
		InTree(root->left, arr);
		arr[index++] = root->data;
		InTree(root->right, arr);
	}
}

