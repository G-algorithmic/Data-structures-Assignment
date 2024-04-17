#include <stdio.h>
#include <stdlib.h>

// Definition of a binary tree node
struct Node
{
    int value;
    struct Node *leftChild;
    struct Node *rightChild;
};

// Function to create a new node
struct Node *createNewNode(int val)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->value = val;
    newNode->leftChild = newNode->rightChild = NULL;
    return newNode;
}

// Function to find the index of a value in an array
int findIndex(int arr[], int start, int end, int value)
{
    int i;
    for (i = start; i <= end; i++)
    {
        if (arr[i] == value)
            return i;
    }
    return -1; // Not found
}

// Function to construct the binary search tree from in-order and post-order traversal arrays
struct Node *buildBST(int inOrder[], int postOrder[], int start, int end, int *postIndex)
{
    if (start > end)
        return NULL;

    struct Node *node = createNewNode(postOrder[*postIndex]);
    (*postIndex)--;

    if (start == end)
        return node;

    int index = findIndex(inOrder, start, end, node->value);

    node->rightChild = buildBST(inOrder, postOrder, index + 1, end, postIndex);
    node->leftChild = buildBST(inOrder, postOrder, start, index - 1, postIndex);

    return node;
}

// Function to print nodes of a binary tree in breadth-first-search (DFS) traversal
void printDFS(struct Node *root)
{
    if (root == NULL)
        return;

    // Create a queue for DFS
    struct Node **queue = (struct Node **)malloc(sizeof(struct Node *) * 100);
    int front = -1, rear = -1;

    // Enqueue root and initialize count of nodes at current level
    queue[++rear] = root;

    while (front < rear)
    {
        // Dequeue node and print it
        struct Node *node = queue[++front];
        printf("%d ", node->value);

        // Enqueue left child
        if (node->leftChild != NULL)
            queue[++rear] = node->leftChild;

        // Enqueue right child
        if (node->rightChild != NULL)
            queue[++rear] = node->rightChild;
    }

    free(queue);
}

int main()
{
    int post[] = {5, 15, 10, 25, 45, 30, 20};
    int in[] = {5, 10, 15, 20, 25, 30, 45};
    int size = sizeof(post) / sizeof(post[0]);

    int postIdx = size - 1;
    struct Node *root = buildBST(in, post, 0, size - 1, &postIdx);

    printf("Breadth-First Search (DFS) Traversal of the constructed BST:\n");
    printDFS(root);
    printf("\n");

    return 0;
}
