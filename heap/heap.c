#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void printHeap(int v[], int size) {
    printf("Max Heap : ");
    for (int i = 0; i < size; i++)
        printf("%d ", v[i]);
    printf("\n");
}

void assertHeap(int heap[], int ans[], int size) {
    for (int i = 0; i < size; i++) {
        assert(heap[i] == ans[i]);
    }
}

int getMaxValue(int V[]) {
    return V[0];
}

void swap(int *a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}

int getFather(int node) {
    return ((node - 1) / 2);
}

void testGetFather(void) {
    assert(getFather(0) == 0);
    assert(getFather(1) == 0);
    assert(getFather(3) == 1);
    assert(getFather(7) == 3);
    assert(getFather(12) == 5);
}

int getLeftChild(int node) {
    return (node * 2 + 1);
}

void testGetLeftChild(void) {
    assert(getLeftChild(0) == 1);
    assert(getLeftChild(1) == 3);
    assert(getLeftChild(2) == 5);
    assert(getLeftChild(6) == 13);
    assert(getLeftChild(10) == 21);
}

int getRightChild(int node) {
    return (node * 2 + 2);
}

void testGetRightChild(void) {
    assert(getRightChild(0) == 2);
    assert(getRightChild(1) == 4);
    assert(getRightChild(2) == 6);
    assert(getRightChild(6) == 14);
    assert(getRightChild(10) == 22);
}

void fixDown(int v[], int size, int node) {
    int max = node;
    int leftNode = getLeftChild(node);
    int rightNode = getRightChild(node);

    if (v[leftNode] > v[max] && leftNode < size)
        max = leftNode;
    if (v[rightNode] > v[max] && rightNode < size)
        max = rightNode;

    if (max != node) {
        swap(&v[max], &v[node]);
        fixDown(v, size, max);
    }
}

void testFixDown(void) {
    int array[7] = {1, 5, 3, 4, 10, 2, 0};
    fixDown(array, 7, 1);
    int answer[7] = {1, 10, 3, 4, 5, 2, 0};
    assertHeap(array, answer, 7);

    int array2[7] = {9, 5, 8, 20, 4, 6, 3};
    fixDown(array2, 7, 1);
    fixDown(array2, 7, 0);
    int answer2[7] = {20, 9, 8, 5, 4, 6, 3};
    assertHeap(array2, answer2, 5);

    int array3[3] = {3, 2, 1};
    fixDown(array3, 3, 0);
    int answer3[3] = {3, 2, 1};
    assertHeap(array3, answer3, 3);

    int array4[7] = {7, 6, 5, 4, 3, 2, 10};
    fixDown(array4, 7, 2);
    int answer4[7] = {7, 6, 10, 4, 3, 2, 5};
    assertHeap(array4, answer4, 7);
}

void fixUp(int v[], int node) {
    int father = getFather(node);
    if (v[father] < v[node]) {
        swap(&v[father], &v[node]);
        fixUp(v, father);
    }
}

void testFixUp(void) {
    int array[3] = {8, 9, 10};
    fixUp(array, 2);
    int answer[3] = {10, 9, 8};
    assertHeap(array, answer, 3);

    int array2[7] = {11, 9, 8, 20, 4, 2, 1};
    fixUp(array2, 3);
    int answer2[7] = {20, 11, 8, 9, 4, 2, 1};
    assertHeap(array2, answer2, 7);

    int array3[7] = {25, 24, 23, 22, 21, 24, 19};
    fixUp(array3, 5);
    int answer3[7] = {25, 24, 24, 22, 21, 23, 19};
    assertHeap(array3, answer3, 7);

    int array4[7] = {7, 6, 5, 4, 3, 2, 1};
    fixUp(array4, 6);
    int answer4[7] = {7, 6, 5, 4, 3, 2, 1};
    assertHeap(array4, answer4, 7);
}

void buildHeap(int v[], int size) {
    for (int node = getFather(size); node >= 0; node--)
        fixDown(v, size, node);
}

void testBuildHeap(void) {
    int array[7] = {1, 5, 3, 4, 10, 2, 0};
    buildHeap(array, 7);
    int answer[7] = {10, 5, 3, 4, 1, 2, 0};
    assertHeap(array, answer, 7);

    int array2[3] = {1, 2, 3};
    buildHeap(array2, 3);
    int answer2[3] = {3, 2, 1};
    assertHeap(array2, answer2, 3);

    int array3[7] = {7, 6, 5, 4, 3, 2, 1};
    buildHeap(array3, 7);
    int answer3[7] = {7, 6, 5, 4, 3, 2, 1};
    assertHeap(array3, answer3, 7);

    int array4[7] = {10, 20, 5, 35, 50, 6, 100};
    buildHeap(array4, 7);
    int answer4[7] = {100, 50, 10, 35, 20, 6, 5};
    assertHeap(array4, answer4, 7);
}

void insertNode(int v[], int value, int index) {
    v[index] = value;
    fixUp(v, index);
}

void testInsertNode(void) {
    int array[7] = {10, 5, 3, 1, 4, 2};
    insertNode(array, 6, 6);
    int answer[7] = {10, 5, 6, 1, 4, 2, 3};
    assertHeap(array, answer, 7);

    int array2[3] = {1, 2};
    insertNode(array2, 4, 2);
    int answer2[3] = {4, 2, 1};
    assertHeap(array2, answer2, 3);

    int array3[7] = {7, 6, 5, 4, 3, 2};
    insertNode(array3, 8, 6);
    int answer3[7] = {8, 6, 7, 4, 3, 2, 5};
    assertHeap(array3, answer3, 7);

    int array4[7] = {10, 50, 6, 35, 20, 5};
    insertNode(array4, 100, 6);
    int answer4[7] = {100, 50, 10, 35, 20, 5, 6};
    assertHeap(array4, answer4, 7);
}

int main(void) {
    // Roda os testes para garantir que as funções estão corretas
    testGetFather();
    testGetLeftChild();
    testGetRightChild();
    testFixDown();
    testFixUp();
    testBuildHeap();
    testInsertNode();

    printf("All tests passed!\n");

    int heap[15] = {2, 1, 3, 4, 5, 6, 7};
    buildHeap(heap, 7);
    printHeap(heap, 7);

    insertNode(heap, 8, 7);
    insertNode(heap, 9, 8);
    insertNode(heap, 10, 9);
    insertNode(heap, 11, 10);
    insertNode(heap, 12, 11);
    insertNode(heap, 13, 12);
    insertNode(heap, 14, 13);
    insertNode(heap, 15, 14);

    printHeap(heap, 15);

    return EXIT_SUCCESS;
}
