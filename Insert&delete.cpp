#include <iostream>
#include <cmath>
using namespace std;

struct N
{
    int key;
    N *left;
    N *right;
    N(int value) : key(value), left(nullptr), right(nullptr) {}
};

class BST
{
private:
    N *root;

    void inorderTraversal(N *node)
    {
        if (!node)
            return;
        inorderTraversal(node->left);
        cout << node->key << " ";
        inorderTraversal(node->right);
    }

    int calculateHeight(N *node)
    {
        if (!node)
            return 0;
        int leftHeight = calculateHeight(node->left);
        int rightHeight = calculateHeight(node->right);
        return max(leftHeight, rightHeight) + 1;
    }

public:
    BST() : root(nullptr) {}

    void insert(int key)
    {
        N *newN = new N(key);
        if (!root)
        {
            root = newN;
            return;
        }
        N *current = root;
        N *parent = nullptr;
        while (current)
        {
            parent = current;
            if (key < current->key)
                current = current->left;
            else
                current = current->right;
        }
        if (key < parent->key)
            parent->left = newN;
        else
            parent->right = newN;
    }

    void deleteNode(int key)
    {
        N *current = root;
        N *parent = nullptr;
        while (current && current->key != key)
        {
            parent = current;
            if (key < current->key)
                current = current->left;
            else
                current = current->right;
        }
        if (!current)
            return;
        if (!current->left || !current->right)
        {
            N *newChild = current->left ? current->left : current->right;
            if (!parent)
                root = newChild;
            else if (current == parent->left)
                parent->left = newChild;
            else
                parent->right = newChild;

            delete current;
        }
        else
        {
            N *successorParent = current;
            N *successor = current->right;
            while (successor->left)
            {
                successorParent = successor;
                successor = successor->left;
            }
            current->key = successor->key;
            if (successorParent->left == successor)
                successorParent->left = successor->right;
            else
                successorParent->right = successor->right;

            delete successor;
        }
    }

    void inorder()
    {
        inorderTraversal(root);
        cout << endl;
    }

    int getHeight()
    {
        return calculateHeight(root);
    }

    int getHeightDifference()
    {
        if (!root)
            return 0;
        int leftHeight = calculateHeight(root->left);
        int rightHeight = calculateHeight(root->right);
        return abs(leftHeight - rightHeight);
    }
};

int main()
{
    BST bst;
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    for (int value : values)
        bst.insert(value);
    cout << "In-order Traversal of BST: ";
    bst.inorder();
    bst.deleteNode(70);
    cout << "In-order Traversal after deletion: ";
    bst.inorder();
    cout << "Height of BST: " << bst.getHeight() << endl;
    cout << "Height Difference of root: " << bst.getHeightDifference() << endl;
    return 0;
}

