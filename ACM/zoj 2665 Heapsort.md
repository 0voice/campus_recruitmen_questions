# 题目
A well known algorithm called heapsort is often used when deterministic sorting algorithm with O(n log n) time and O(1) additional memory is needed. Let us describe the heapsort algorithm briefly. We will describe sorting of an array of different integer numbers, although generally heapsort can be applied to any array of comparable elements, and equal elements are allowed. We will consider ascending sort.

The algorithm consists of two phases. On the first phase, called heapification, the array of integers to be sorted is converted to heap. An array a[1 . . . n] of integers is called a heap if for all 1 ≤ i ≤ n the following conditions are satisfied:

if 2i ≤ n then a[i] &gt a[2i];<br>
if 2i + 1 ≤ n then a[i] &gt a[2i + 1].<br>
These conditions are called the heap conditions.<br>

We can interpret an array as a binary tree, considering children of element a[i] to be a[2i] and a[2i + 1].

In this case the parent of a[i] is a[i div 2]. Here (i div 2) means the quotient of an integer division of i by 2, for example 6 div 2 = 3, 7 div 2 = 3. In terms of trees the property of being a heap means that for each node its value is greater than the values of its children.

After the array is converted to heap, it is turned to sorted array in the following way. Because of the heap condition the greatest element in the heapified array is a[1]. Let us exchange it with a[n], now the greatest element of the array is at its correct position in the sorted array. This is called extract-max.

Now let us consider the part of the array a[1 . . . n- 1]. It may be not a heap because the heap condition may fail for i = 1. If it is so (that is, either a[2] or a[3], or both are greater than a[1]) let us exchange the greater child of a[1] with it, restoring the heap condition for i = 1. Now it is possible that the heap condition fails for the position that now contains the former value of a[1]. Apply the same procedure to it, exchanging it with its greater child. Proceeding so we convert the whole array a[1 . . . n - 1] to heap.

This procedure is called sifting down. After converting the part a[1 . . . n- 1] to heap by sifting, we apply extract-max again, putting second greatest element of the array to a[n - 1], and so on. It is easy to see that the heap can be converted to the sorted array in O(n log n) time.

For example, let us see how the heap a = (5, 4, 2, 1, 3) is converted to a sorted array. Let us make the first extract-max. After that the array turns to (3, 4, 2, 1, 5). Heap condition is failed for a[1] = 3 because its child a[2] = 4 is greater than it. Let us sift it down, exchanging a[1] and a[2]. Now the array is (4, 3, 2, 1, 5). The heap condition is satisfied for all elements, so sifting is over. Let us make extract-max again. Now the array turns to (1, 3, 2, 4, 5). Again the heap condition is failed for a[1], exchanging it with its greater child we get the array (3, 1, 2, 4, 5) which is the correct heap. So we make extract-max and get (2, 1, 3, 4, 5). This time the heap condition is satisfied for all elements, so we make extract-max, getting (1, 2, 3, 4, 5). The leading part of the array is a heap, and the last extract-max finally gives (1, 2, 3, 4, 5).

The array is sorted.

It is known that heapification can be done in O(n) time. Therefore, the most time consuming operation in heapsort algorithm is sifting.

In this problem you have to find a heapified array containing different numbers from 1 to n, such that when converting it to the sorted array, the total number of exchanges in all sifting operations is maximal possible. In the example above the number of exchanges is 1 + 1 + 0 + 0 + 0 = 2. If the initial heapified array was (5, 4, 3, 2, 1), one would totally need 4 exchange operations in all sifting procedures of converting the array back to heap after extract-max operations. This is the maximal possible number among all heapified arrays containing 5 integers.

Input

There are several test cases in the input. Each case contains n (1 ≤ n ≤ 50 000).

Output

Output the array containing n elements, all being different integer numbers from 1 to n, such that

it is a heap;<br>
when converting it to a sorted array in the way described, the total number of exchanges in sifting operations is maximal possible.<br>
Separate numbers by spaces.<br>

Sample Input
```
4
5
6
```
Sample Output
```
4 2 3 1
5 4 3 2 1
6 5 3 2 4 1
```
# 参考答案
```c++
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int pos;
int perm[50008];

int num;
int input[100];
int *data[100];

int list[100];

void siftup(int leaf){
    int t, root;
    while(leaf != 0){
		root = (leaf -1 )/2;
		t = perm[leaf]; perm[leaf] = perm[root]; perm[root] = t;
		leaf = root;
	}
}

int MyComp(const int *a, const int *b){
	return input[*a] - input[*b];
}

int main(){
    int i,t;
    num = 0;

    scanf("%d", &t);
    while(!feof(stdin)){
		input[num] = t;
		list[num] = num;
		data[num] = malloc(sizeof(int) * t);

		num ++;
		scanf("%d", &t);
	}

    qsort(list, num, sizeof(int), MyComp);

    pos = 1;
    perm[0] = 1;

    for(i=0;i<num;i++){
    	while(pos<input[list[i]]){		
			perm[pos] = perm[pos-1];
			perm[pos-1] = pos + 1;
			siftup(pos-1);
			pos ++;		
		}
		memcpy(data[list[i]], perm, sizeof(int) * pos);
	}
	int *ptr;
	for(i=0;i<num;i++){
		ptr = data[i];
		printf("%d", ptr[0]);
		for(t=1;t<input[i];t++){
			printf(" %d", ptr[t]);
		}
		printf("\n");
	}
    return 0;
}




