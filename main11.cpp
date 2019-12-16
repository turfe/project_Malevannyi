#include <iostream>
#include <chrono>

using namespace std;

struct Node {
    Node *left;
    Node *right;
    unsigned long int value;

    Node(unsigned long int value, Node *left) : value(value), left(left), right(nullptr) {}

    Node(unsigned long int value) : value(value), left(nullptr), right(nullptr) {}

    Node() : value(0), left(nullptr), right(nullptr) {}

    ~Node() {
        if (left) delete(left);
        if (right) delete(right);
    }
};

void printer(struct Node *root, long long int depth) {
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

struct Node *build_from_prototype(Node *proto, unsigned long main) {
    Node* new_node = new Node(proto->value+main);
    if(proto->left != nullptr)
        new_node->left = build_from_prototype(proto->left, main);

    if(proto->right != nullptr)
        new_node->right = build_from_prototype(proto->right, main);

    return new_node;
}

int main() {
    unsigned long long int depth;
    cin >> depth;

    if (depth <= 0) return 0;
    depth++;

    auto start = std::chrono::system_clock::now();


    Node *node = new Node(0);

    for (unsigned long i = 1; i <= depth; i++) {
        if (i == 1) {
            node = new Node(1);
        } else if (i == 2) {
            node = new Node(2, node);
        } else {
            unsigned long lv = node->value;
            unsigned long llv = node->left->value;
            unsigned long value = lv + llv;
            node = new Node(value, node);

            Node *prototype = node->left->left;
            node->right = build_from_prototype(prototype, value);
        }
    }

    auto end = std::chrono::system_clock::now();

    chrono::duration<double> elapsed_seconds = end-start;
    time_t end_time = chrono::system_clock::to_time_t(end);

    cout << "finished computation at " << std::ctime(&end_time)
         << "run time: " << elapsed_seconds.count() << " seconds" << endl;

    cout << node;
    //printer(node, depth);
    delete (node);
}
