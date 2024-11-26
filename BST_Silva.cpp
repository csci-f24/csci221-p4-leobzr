#include <iostream>
#include <cmath> // For abs()
using namespace std;

struct node {
    int data;
    struct node* left;
    struct node* right;
};

struct node* newNode(int data) {
    struct node* node = new struct node;
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void insert(struct node** rootRef, int data) { 
    if (*rootRef == nullptr) {
        *rootRef = newNode(data);
    } else {
        if (data <= (*rootRef)->data) {
            insert(&((*rootRef)->left), data);
        } else {
            insert(&((*rootRef)->right), data);
        }
    }
}

void printInOrder(struct node* root) {
    if (root == NULL) {
        return;
    }
    printInOrder(root->left);
    cout << (root->data) << " ";
    printInOrder(root->right);
}

void printPreOrder(struct node* root) {
    if (root == NULL) {
        return;
    }
    cout << (root->data) << " ";
    printPreOrder(root->left);
    printPreOrder(root->right);
}

int size(struct node* root) {
    if (root == NULL) return 0;
    return(size(root->left) + size(root->right) + 1);
}

int maxDepth(struct node* node) {
    if (node == NULL) return 0;
    int lheight = maxDepth(node->left);
    int rheight = maxDepth(node->right);

    if (lheight > rheight) {
        return (lheight + 1);
    } else { 
        return (rheight + 1);
    }
}

bool lookup(struct node* root, int target) {
    if (root == NULL) return false;
    if(root->data == target) return true;
    if(root->data > target) {
        return (lookup(root->left, target));
    } else {
        return (lookup(root->right, target));
    }
}

int findMax(struct node* root) {
    struct node* temp = root;

    while (temp->right != NULL) {
        temp = temp->right;
    }
    return temp->data;
}

int findMin(struct node* root) {
    struct node* temp = root;

    while (temp->left != NULL) {
        temp = temp->left;
    }
    return temp->data;
}


int maxAbsDifference(struct node* root) {
    if (root == NULL) return 0;

    int minValue = findMin(root);
    int maxValue = findMax(root);

    return abs(maxValue - minValue);
}


struct node* deleteNode(struct node* root, int key) {
    if (root == NULL) return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        // Node found

        if (root->left == NULL) {
            struct node* temp = root->right;
            delete root; 
            return temp;
        } else if (root->right == NULL) {
            struct node* temp = root->left;
            delete root;
            return temp;
        }

        struct node* temp = root->right;
        while (temp->left != NULL)
            temp = temp->left;

        root->data = temp->data;

        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

void freeTree(struct node* root) {
	if (root == NULL) return;
	freeTree(root->left);
	freeTree(root->right);
	delete root;
}


int main() { 
    struct node* root = nullptr;

    insert(&root, 41);
    insert(&root, 20);
    insert(&root, 11);
    insert(&root, 29);
    insert(&root, 32);
    insert(&root, 65);
    insert(&root, 70);
    insert(&root, 30);

    cout << "In-order traversal before deletion: ";
    printInOrder(root);
    cout << endl;

    cout << "Maximum absolute difference in BST: " << maxAbsDifference(root) << endl;

    // Delete node with value 29
    root = deleteNode(root, 29);

    cout << "In-order traversal after deleting 29: ";
    printInOrder(root);
    cout << endl;

    // Delete node with value 41 (root node)
    root = deleteNode(root, 41);

    cout << "In-order traversal after deleting 41: ";
    printInOrder(root);
    cout << endl;

    freeTree(root);
    root = NULL;

    return 0;
}

