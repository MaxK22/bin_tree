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
    tree *add(int x);
    tree(int x);
    tree(){};
    void print();
    void print_leaves();
    bool balance();
    tree *do_balance();
    tree *rotate_right();
    tree *rotate_left();
    void fix_h();
    tree *search(int x);
    tree *minimum();
    tree *remove(int x);
    tree *remove_min();
    void print_tree();
    tree *before_min();
    tree *before_max();
};

void tree::fix_h() {
    h = max((left ? left->h : 0) , (right ? right->h : 0))+1;
}

tree *tree::rotate_right() {
    tree *y = right;
    right = y->left;
    y->left = this;
    this->fix_h();
    y->fix_h();
    return y;
}

tree *tree::rotate_left() {
    tree *y = left;
    left = y->right;
    y->right = this;
    this->fix_h();
    y->fix_h();
    return y;
}

tree *tree::do_balance() {
    tree * change = this;
    if((left ? left->h : 0) - (right ? right->h : 0) == 2)
    {
        if(right != NULL && (right->left ? right->left->h : 0) > (right->right ? right->right->h : 0))
            right = right->rotate_right();
        change = rotate_left();
    }
    else if((left ? left->h : 0) - (right ? right->h : 0) == -2)
    {
        if(left != NULL && (left->right ? left->right->h : 0) > (left->left ? left->left->h : 0))
            left = left->rotate_left();
        change = rotate_right();
    }
    //h = max((left ? left->h : 0) , (right ? right->h : 0))+1;
    return  change;
}



tree::tree(int x) {
    src = x;
    left = NULL;
    right = NULL;
    h = 1;
    clones = 1;
}


tree *tree::add(int x) {
    if(x > src)
    {
        if(right != NULL)
            right = right->add(x);
        else
        {
            tree *new_element = new tree(x);
            right = new_element;
        }
    }
    else if (x < src)
    {
        if(left != NULL)
            left = left->add(x);
        else
        {
            tree *new_element = new tree(x);
            left = new_element;
        }
    }
    else
        clones++;
    fix_h();
    return do_balance();
}

tree *tree::search(int x) {
    if(x > src)
        return (right ? right->search(x) : NULL);
    else if (x < src)
        return (left ? left->search(x) : NULL);
    else
        return this;
}

tree *tree::minimum() {
    tree * l = this;
    while(l->left != NULL)
        l = l->left;
    return l;
}

tree *tree::before_min() {
    tree * l = this;
    while(l->left != NULL && l->left->left != NULL)
        l = l->left;
    return l;
}

tree *tree::before_max() {
    tree * l = this;
    while(l->right != NULL && l->right->right != NULL)
        l = l->right;
    return l;
}

void tree::print() {
    if(left != NULL)
        left->print();
    cout << src << " " << h << endl;
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

tree *tree::remove_min() {
    if(!left)
        return right;
    left = left->remove_min();
    return do_balance();
}

tree *tree::remove(int x) {
    if(x < src)
    {
        if(left != NULL && left->src == x) {
            if (left->left != NULL) {
                tree *l = left->left;
                tree *r = left->right;
                tree *bm = left->left->before_max();
                delete left;
                left = bm->right;
                bm->right = left->left;
                left->left = l;
                left->right = r;
            }
            else
            {
                tree *n = left->right;
                delete left;
                left = n;
            }

        }
        else if(left != NULL)
            left = left->remove(x);
    }
    else if(x > src)
    {
        if(right != NULL && right->src == x)
        {

            if(right->right != NULL) {
                tree *l = right->left;
                tree *r = right->right;
                tree *bm = right->right->before_min();
                delete right;
                right = bm->left;
                bm->left = right->right;
                right->left = l;
                right->right = r;
            }
            else
            {
                tree* n = right->left;
                delete right;
                right = n;
            }


        }
        else if(right != NULL)
            right = right->remove(x);

    }
    else
    {
        tree *l = left;
        tree *r = right;
        delete this;
    }
    return do_balance();
}

int main() {
    /*
    int x;
    cin >> x;
    if(x != 0) {
        tree *a = new tree(x);
        a->clones = 0;
        while(x!=0) {
            a = a->add(x);
            cin >> x;
        }
       a->print();


        cout << "test" << endl;

    }
    else
        cout << 0;
    */
    setlocale(LC_ALL, "Russian");
    cout << "Enter tree (введите последовательность натуральных чисел." << endl <<  "Последовательность завершается числом 0, которое означает конец ввода, без его добавления в дерево" << endl;
    int x;
    cin >> x;
    tree *a;
    if(x != 0) {
        a = new tree(x);
        a->clones = 0;
        while(x!=0) {
            a = a->add(x);
            cin >> x;
        }
    }

    cout << "Enter 'help' to see all commands" << endl;
    string command;
    cin >> command;
    while(command != "end")
    {
        if(command == "help")
            cout << "search element by key i: 'search' [int](key)" << endl <<
                "search minimum element: 'search_min'" << endl <<
                 //"size: 'size'" << endl <<
                 //"is empty: 'is_empty'" << endl <<
                 //"push front: 'p_f' [int](new element)" << endl <<
                 //"push back: 'p_b' [int](new element)" << endl <<
                 "push i: 'add' [int](key)" << endl <<
                 "search element by key i: 'search' [int](key)" << endl <<
                 "delete: 'del' [int](key)" << endl <<
                 "delete_minimum: 'del_min'" << endl <<
                 "print: 'print'" << endl <<
                 "close programm: 'end'";
        else if(command == "search")
        {
            int x;
            cin >> x;
            if(a == NULL)
            {
                cout << "Tree is empty";
            }
            else {
                tree *f = a->search(x);
                if (f != NULL)
                    cout << f->src;
                else
                    cout << "Element wasn't found";
            }
        }
        else if(command == "search_min")
        {
            if(a == NULL)
            {
                cout << "Tree is empty";
            }
            else {
                tree *f = a->minimum();
                if (f != NULL)
                    cout << f->src;
                else
                    cout << "Element wasn't found";
            }
        }
        else if(command == "del")
        {
            int x;
            cin >> x;
            if(a == NULL)
            {
                cout << "Tree is empty";
            }
            else {//kjsvfbhkdsfvbgds
                tree *f = a->search(x);
                if (f != NULL)
                    cout << f->src;
                else
                    cout << "Element wasn't found";
            }
        }
        else if(command == "del_min")
        {
            if(a == NULL)
            {
                cout << "Tree is empty";
            }
            else {//sfjvbsdkhbvsdkhbvskvbsuhfbvks
                tree *f = a->minimum();
                if (f != NULL)
                    cout << f->src;
                else
                    cout << "Element wasn't found";
            }
        }
        else if(command == "add")
        {
            int x;
            cin >> x;
            if(a != NULL)
            a = a->add(x);
            else
                a = new tree(x);
            cout << "element was added";
        }
        else if(command == "print")
        {
            a->print();
        }
        cout << endl;
        cin >> command;
    }


    return 0;
}
