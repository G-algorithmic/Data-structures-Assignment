#include <stdio.h>
#include <stdlib.h>

// Define structure for BST node
typedef struct TreeNode
{
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// Function to create a new BST node
TreeNode *createNode(int value)
{
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a new node into BST
TreeNode *insert(TreeNode *root, int value)
{
    // Base case: if the tree is empty, create a new node and return it as root
    if (root == NULL)
    {
        return createNode(value);
    }
    // Recursive case: insert into the appropriate subtree
    if (value < root->data)
    {
        root->left = insert(root->left, value);
    }
    else if (value > root->data)
    {
        root->right = insert(root->right, value);
    }
    // Ignore duplicate values
    return root;
}

// Function to find the minimum value node in a BST
TreeNode *findMin(TreeNode *node)
{
    while (node->left != NULL)
    {
        node = node->left;
    }
    return node;
}

// Function to delete a node from BST
TreeNode *deleteNode(TreeNode *root, int key)
{
    // Base case: if the tree is empty
    if (root == NULL)
    {
        return root;
    }
    // Recursive cases: traverse the tree to find the node to delete
    if (key < root->data)
    {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->data)
    {
        root->right = deleteNode(root->right, key);
    }
    else
    { // Found the node to delete
        // Case 1: Node has no children or only one child
        if (root->left == NULL)
        {
            TreeNode *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            TreeNode *temp = root->left;
            free(root);
            return temp;
        }
        // Case 2: Node has two children
        TreeNode *temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function to calculate the height of the BST
int height(TreeNode *root)
{
    if (root == NULL)
    {
        return -1;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Function to calculate the height of a specific node in the BST
int nodeHeight(TreeNode *root, int key)
{
    if (root == NULL)
    {
        return -1;
    }
    if (root->data == key)
    {
        return height(root);
    }
    else if (key < root->data)
    {
        return nodeHeight(root->left, key);
    }
    else
    {
        return nodeHeight(root->right, key);
    }
}

// Function to calculate the level of a specific node in the BST
int nodeLevel(TreeNode *root, int key, int level)
{
    if (root == NULL)
    {
        return -1;
    }
    if (root->data == key)
    {
        return level;
    }
    else if (key < root->data)
    {
        return nodeLevel(root->left, key, level + 1);
    }
    else
    {
        return nodeLevel(root->right, key, level + 1);
    }
}

// Function to print inorder traversal of BST
void inorderTraversal(TreeNode *root)
{
    if (root != NULL)
    {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

int main()
{
    int arr[] = {30, 20, 40, 10, 25, 45, 5, 15};
    int n = sizeof(arr) / sizeof(arr[0]);

    TreeNode *root = NULL;
    for (int i = 0; i < n; i++)
    {
        root = insert(root, arr[i]);
    }

    printf("Inorder traversal of the created BST: ");
    inorderTraversal(root);
    printf("\n");

    // Delete a node from the BST
    int keyToDelete;
    printf("Enter the node to be deleted: ");
    scanf("%d", &keyToDelete);
    root = deleteNode(root, keyToDelete);
    printf("Inorder traversal after deleting %d: ", keyToDelete);
    inorderTraversal(root);
    printf("\n");

    // Print the height of the BST
    printf("Height of the BST: %d\n", height(root));

    // Print the height of a specific node
    int keyToFindHeight;
    printf("Enter the node whose height is to be found: ");
    scanf("%d", &keyToFindHeight);
    printf("Height of node %d: %d\n", keyToFindHeight, nodeHeight(root, keyToFindHeight));

    // Print the level of a specific node
    int keyToFindLevel;
    printf("Enter the node whose level is to be found: ");
    scanf("%d", &keyToFindLevel);
    printf("Level of node %d: %d\n", keyToFindLevel, nodeLevel(root, keyToFindLevel, 0));

    return 0;
}
