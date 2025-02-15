#include <iostream>
using namespace std;

// Node structure for AVL Tree
struct Node {
    int data;
    Node* left;
    Node* right;
    int height;

    // Constructor to initialize node
    Node(int value) {
        data = value;
        left = right = nullptr;
        height = 1;  // New node is initially added at height 1
    }
};

// AVL Tree class
class AVL {
public:
    Node* root;

    // Constructor
    AVL() { root = nullptr; }

    // Function to get the height of a node
    int getHeight(Node* node) {
        return node ? node->height : 0;
    }

    // Function to get the balance factor of a node
    int getBalanceFactor(Node* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    // Right Rotation (Single Rotation)
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        // Rotation
        x->right = y;
        y->left = T2;

        // Update heights
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;  // New root
    }

    // Left Rotation (Single Rotation)
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        // Rotation
        y->left = x;
        x->right = T2;

        // Update heights
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;  // New root
    }

    // Insert a node into the AVL tree
    Node* insert(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }

        // Standard BST insert
        if (value < node->data) {
            node->left = insert(node->left, value);
        } else if (value > node->data) {
            node->right = insert(node->right, value);
        } else {
            return node;  // No duplicate values
        }

        // Update height
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

        // Get balance factor
        int balance = getBalanceFactor(node);

        // **Rotations for balancing**
        // Left-Heavy (Right Rotate)
        if (balance > 1 && value < node->left->data) {
            return rightRotate(node);
        }
        // Right-Heavy (Left Rotate)
        if (balance < -1 && value > node->right->data) {
            return leftRotate(node);
        }
        // Left-Right (Left Rotate + Right Rotate)
        if (balance > 1 && value > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        // Right-Left (Right Rotate + Left Rotate)
        if (balance < -1 && value < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;  // Return unchanged node
    }

    // Wrapper function for insertion
    void insert(int value) {
        root = insert(root, value);
    }

    // Find the minimum value node in the tree (for deletion)
    Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    // Delete a node from AVL Tree
    Node* deleteNode(Node* node, int key) {
        if (node == nullptr) return node;

        // Perform standard BST deletion
        if (key < node->data) {
            node->left = deleteNode(node->left, key);
        } else if (key > node->data) {
            node->right = deleteNode(node->right, key);
        } else {
            // Node with one or no child
            if ((node->left == nullptr) || (node->right == nullptr)) {
                Node* temp = node->left ? node->left : node->right;
                if (!temp) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {
                // Node with two children: Get inorder successor
                Node* temp = findMin(node->right);
                node->data = temp->data;
                node->right = deleteNode(node->right, temp->data);
            }
        }

        if (node == nullptr) return node;

        // Update height
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

        // Get balance factor
        int balance = getBalanceFactor(node);

        // **Rotations for balancing**
        // Left-Heavy (Right Rotate)
        if (balance > 1 && getBalanceFactor(node->left) >= 0) {
            return rightRotate(node);
        }
        // Left-Right (Left Rotate + Right Rotate)
        if (balance > 1 && getBalanceFactor(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        // Right-Heavy (Left Rotate)
        if (balance < -1 && getBalanceFactor(node->right) <= 0) {
            return leftRotate(node);
        }
        // Right-Left (Right Rotate + Left Rotate)
        if (balance < -1 && getBalanceFactor(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    // Wrapper function for deletion
    void deleteNode(int key) {
        root = deleteNode(root, key);
    }

    // Inorder Traversal (Left - Root - Right)
    void inorder(Node* node) {
        if (node == nullptr) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    // Wrapper for inorder traversal
    void inorder() { inorder(root); cout << endl; }
};

int main() {
    AVL tree;

    // Insert nodes
    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    tree.insert(10);
    tree.insert(25);
    tree.insert(35);
    tree.insert(50);

    cout << "Inorder Traversal (Sorted Order): ";
    tree.inorder();

    // Deleting a node
    cout << "Deleting node 25..." << endl;
    tree.deleteNode(25);

    cout << "Inorder Traversal after deletion: ";
    tree.inorder();

    return 0;
}
