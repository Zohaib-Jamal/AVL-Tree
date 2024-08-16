#include <iostream>
#include <algorithm>
#include <cmath>     

using namespace std;

class Node
{
public:
    int key;
    Node *left;
    Node *right;
    int height;

    Node(int k)
    {
        key = k;
        left = nullptr;
        right = nullptr;
        height = 1; 
    }
};

class AVLTree
{
private:
    Node *root;

    int height(Node *node)
    {
        if (!node)
            return 0;
        return node->height;
    }

    int getBalance(Node *node)
    {
        if (!node)
            return 0;
        return height(node->left) - height(node->right);
    }

    Node *rightRotate(Node *y)
    {
        Node *x = y->left;
        Node *T2 = x->right;

        
        x->right = y;
        y->left = T2;

        
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        
        return x;
    }

    Node *leftRotate(Node *x)
    {
        Node *y = x->right;
        Node *T2 = y->left;

       
        y->left = x;
        x->right = T2;

     
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

     
        return y;
    }

    Node *insert(Node *node, int key)
    {
     
        if (!node)
            return new Node(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else
            return node;

        
        node->height = max(height(node->left), height(node->right)) + 1;

       
        int balance = getBalance(node);


        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

  
        if (balance > 1 && key > node->left->key)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

     
        if (balance < -1 && key < node->right->key)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

  
        return node;
    }

    Node *minValueNode(Node *node)
    {
        Node *current = node;
        while (current->left)
            current = current->left;
        return current;
    }

    Node *deleteNode(Node *root, int key)
    {
       
        if (!root)
            return root;

        if (key < root->key)
            root->left = deleteNode(root->left, key);
        else if (key > root->key)
            root->right = deleteNode(root->right, key);
        else
        {
         
            if (!root->left)
            {
                Node *temp = root->right;
                delete root;
                return temp;
            }
            else if (!root->right)
            {
                Node *temp = root->left;
                delete root;
                return temp;
            }

           
            Node *temp = minValueNode(root->right);

            
            root->key = temp->key;

          
            root->right = deleteNode(root->right, temp->key);
        }

       
        root->height = max(height(root->left), height(root->right)) + 1;

        int balance = getBalance(root);

     
        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);


        if (balance > 1 && getBalance(root->left) < 0)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }


        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

 
        if (balance < -1 && getBalance(root->right) > 0)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

   
        return root;
    }

    Node *update(Node *node, int oldKey, int newKey)
    {

        node = deleteNode(node, oldKey);

        node = insert(node, newKey);

        return node;
    }

    void inorder(Node *root)
    {
        if (root)
        {
            inorder(root->left);
            cout << root->key << " ";
            inorder(root->right);
        }
    }

public:
    AVLTree() : root(nullptr)
    {
    }

    void insert(int key)
    {
        root = insert(root, key);
        cout << "Inorder traversal after insertion: ";
        inorder(root);
        cout << endl;
    }

    void deleteKey(int key)
    {
        root = deleteNode(root, key);
        cout << "Inorder traversal after deletion: ";
        inorder(root);
        cout << endl;
    }

    void update(int oldKey, int newKey)
    {
        root = update(root, oldKey, newKey);
        cout << "Inorder traversal after update: ";
        inorder(root);
        cout << endl;
    }

    ~AVLTree()
    {
    
    }
};

int main()
{
    AVLTree db;

    db.insert(10);
    db.insert(1);
    db.insert(30);
    db.insert(6);
    db.insert(11);
    db.insert(5);
    db.insert(9);

    db.deleteKey(10);
    db.update(6, 12);

    return 0;
}
