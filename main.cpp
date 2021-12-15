#include <iostream>
#include "algorithm"
#include "math.h"

using namespace std;

class tree
{
public:
    int h;
    int src;
    int clones;
    tree *left;
    tree *right;
    int add(int x);
    tree(int x);
    void print();
    void print_leaves();
    bool balance();
    void do_balance();
    tree *rotate_right();
    tree *rotate_left();
    tree *search(int x);
    tree *minimum();
    tree *del(int x);
    void print_tree();
};

tree *tree::rotate_right() {
    tree *y = right;
    right = y->left;
    y->left = this;
    return y;
}

tree *tree::rotate_left() {
    tree *y = left;
    left = y->right;
    y->right = this;
    return y;
}

void tree::do_balance() {
    
}



tree::tree(int x) {
    src = x;
    left = NULL;
    right = NULL;
    h = 1;
    clones = 1;
}
int tree::add(int x) {
    if(x > src)
    {
        if(right != NULL)
            h = max(right->add(x), h);
        else
        {
            tree *new_element = new tree(x);
            right = new_element;
            if(left == NULL)
                h = 2;
        }
    }
    else if (x < src)
    {
        if(left != NULL)
            h = max(left->add(x), h);
        else
        {
            tree *new_element = new tree(x);
            left = new_element;
            if(right == NULL)
                h = 2;
        }
    }
    else
        clones++;
    return h+1;
}



void tree::print() {
    if(left != NULL)
        left->print();
    cout << src << " " << clones << endl;
    if(right != NULL)
        right->print();
}

void tree::print_leaves() {
    if(left != NULL)
        left->print_leaves();
    if(left == NULL && right == NULL)
        cout << src << endl;
    if(right != NULL)
        right->print_leaves();
}

bool tree::balance() {
    if(right != NULL && left != NULL)
        return (right->balance() && left->balance() && (left->h - right->h)*(left->h - right->h) <= 1);
    else if (right != NULL)
        return right->h*right->h <= 1;
    else if(left != NULL)
        return left->h*left->h <= 1;
    else
        return true;
}

int main() {
    int x;
    cin >> x;
    if(x != 0) {
        tree a(x);
        a.clones = 0;
        while(x!=0) {
            a.add(x);
            cin >> x;
        }
       a.print();
    }
    else
        cout << 0;
    return 0;
}
