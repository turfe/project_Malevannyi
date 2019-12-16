#include <iostream>
#include <chrono>

using namespace std;

struct tree_node {
    ~tree_node() {
        if (left) delete(left);
        if (right) delete(right);
    }
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
    long long int aff[100000];
    aff[0] = 1;
    aff[1] = 1;
    for (int i = 2; i < n; ++i)
        aff[i] = aff[i - 1] + aff[i - 2];
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
    struct tree_node *fib = create_tree_node(0);
    long long int depth;
    cin >> depth;

    auto start = std::chrono::system_clock::now();

    struct tree_node *tree = create_fibonacci_tree(fib, depth, fibonacci(depth + 2));
    if (tree != NULL) printer(tree, depth);
    else cout << "Your depth is not correct" << endl;
    cout << endl;

    auto end = std::chrono::system_clock::now();

    chrono::duration<double> elapsed_seconds = end-start;
    time_t end_time = chrono::system_clock::to_time_t(end);

    //std::cout << "fib = " << fib << ", tree = " << tree << std::endl;
    delete(fib);

    cout << "finished computation at " << std::ctime(&end_time)
         << "run time: " << elapsed_seconds.count() << " seconds" << endl;
    return 0;
}