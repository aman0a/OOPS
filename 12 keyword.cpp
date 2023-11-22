#include<bits/stdc++.h>
using namespace std;

struct node
{
    string key;
    string meaning;
    struct node *left, *right;
};

struct node *newNode(string item, string meaning)
{
    struct node *temp =  (struct node *)malloc(sizeof(struct node));
    temp->key = item;
    temp->meaning = meaning;
    temp->left = temp->right = NULL;
    return temp;
}

void inorder(struct node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        cout << root->key << " : " << root->meaning << endl;
        inorder(root->right);
    }
}

struct node* insert(struct node* node, string key, string meaning)
{
    if (node == NULL) return newNode(key, meaning);

    if (key < node->key)
        node->left  = insert(node->left, key, meaning);
    else if (key > node->key)
        node->right = insert(node->right, key, meaning);

    return node;
}

struct node * minValueNode(struct node* node)
{
    struct node* current = node;

    while (current && current->left != NULL)
        current = current->left;

    return current;
}

struct node* deleteNode(struct node* root, string key)
{
    if (root == NULL) return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);

    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    else
    {
        if (root->left == NULL)
        {
            struct node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }

        struct node* temp = minValueNode(root->right);

        root->key = temp->key;

        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

int main()
{
    struct node *root = NULL;
    string key, meaning;
    char choice;
    do
    {
        cout << "Enter a keyword: ";
        cin >> key;
        cout << "Enter its meaning: ";
        cin >> meaning;
        root = insert(root, key, meaning);
        cout << "Do you want to add another keyword? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    cout << "\nInorder traversal of the given tree \n";
    inorder(root);

    cout << "\nEnter the keyword you want to delete: ";
    cin >> key;
    root = deleteNode(root, key);
    cout << "Inorder traversal of the modified tree \n";
    inorder(root);

    return 0;
}

