#include <iostream>
#include <time.h>

using namespace std;

struct tree_node {
    long long int value;
    struct tree_node *left;
    struct tree_node *right;
};

struct tree_node *create_tree_node(long long int a) {
    struct tree_node *new_one = new struct tree_node;
    new_one->value = a;
    new_one->left = NULL;
    new_one->right = NULL;
    return new_one;
}

void change_tree_node(struct tree_node *node, long long int value) {
    node->value = value;
    node->left = NULL;
    node->right = NULL;
}

void printer(struct tree_node *root, long long int depth) {
    if (root == NULL) return;
    else {
        cout << "node's value = " << root->value << endl;
        if (depth != 0) {
            printer(root->left, depth - 1);
            printer(root->right, depth - 2);
        } else {
            cout << endl;
        }
    }
}

long long int fibonacci(long long int n) {
    long long int aff[1000];
    aff[0] = 1;
    aff[1] = 1;
    for (int i = 2; i < n; ++i) {
        aff[i] = aff[i - 1] + aff[i - 2];
    }
    return aff[n - 1];
}

struct tree_node *create_fibonacci_tree(struct tree_node *root, int depth, long long int current_number) {
    if (depth >= 0) {
        if (depth == 0)
            change_tree_node(root, current_number);
        else if (depth == 1) {
            change_tree_node(root, current_number);
            root->left = create_tree_node(root->value - fibonacci(depth));
            create_fibonacci_tree(root->left, depth - 1, root->value - fibonacci(depth));
        } else {
            change_tree_node(root, current_number);
            root->left = create_tree_node(root->value - fibonacci(depth));
            root->right = create_tree_node(root->value + fibonacci(depth));
            create_fibonacci_tree(root->left, depth - 1, root->value - fibonacci(depth));
            create_fibonacci_tree(root->right, depth - 2, root->value + fibonacci(depth));
        }
        return root;
    } else {
        return NULL;
    }
}

int main() {
    time_t start = time(NULL);

    struct tree_node *fib = create_tree_node(0);
    long long int depth;
    cin >> depth;
    struct tree_node *tree = create_fibonacci_tree(fib, depth, fibonacci(depth + 2));
    if (tree != NULL) printer(tree, depth);
    else cout << "Your depth is not correct" << endl;
    cout << endl;

    time_t end = time(NULL);

    cout << "Run time = " << end - start << "s" << endl;
    return 0;
}