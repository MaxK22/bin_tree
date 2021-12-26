#include <iostream>
#include "algorithm"
#include "vector"
#include "math.h"
#include "string"

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
    //tree *remove(int x);
    tree *remove_min();
    void print_tree();
    tree *fmin();
    tree *fmax();
    void math_for_print(vector<string>&s,int hs, int x);
    void math_for_print2(vector<string>& s,int hs, int x);
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
    fix_h();
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
    //fix_h();
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

tree *tree::fmin() {
    tree * l = this;
    while(l->left != NULL)
        l = l->left;
    return l;
}

tree *tree::fmax() {
    tree * l = this;
    while(l->right != NULL)
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

/*tree *tree::remove(int x) {//doesn't work because it's...
    if(x < src)
    {
        if(left != NULL && left->src == x) {
            cout << "here";
            if (left->left != NULL) {
                cout << "here";
                tree *l = left->left;
                tree *r = left->right;
                tree *bm = left->left->before_max();
                tree * m = bm->right;
                bm->right = m->left;
                cout << "here";
                delete left;
                cout << "element was deleted";
                left = m;
                left->left = l;
                left->right = r;

            }
            else
            {
                tree *n = left->right;
                delete left;
                cout << "element was deleted";
                left = n;
            }
            if(left != NULL)left->fix_h();

        }
        else if(left != NULL)
            left = left->remove(x);
        else
            cout << "element wasn't founded";
    }
    else if(x > src)
    {
        if(right != NULL && right->src == x)
        {
            cout << "here";
            if(right->right != NULL) {
                cout << "here";
                tree *l = right->left;
                tree *r = right->right;
                //tree *bm = right->fmin();
                //t/ree * m = bm->left;
               // bm->left = m->right;
                cout << "here";
                delete right;
                cout << "element was deleted";
               // right = m;
                right->left = l;
                right->right = r;

            }
            else
            {
                tree* n = right->left;
                delete right;
                cout << "element was deleted";
                right = n;
            }
            if(right != NULL)right->fix_h();

        }
        else if(right != NULL)
            right = right->remove(x);
        else
            cout << "element wasn't founded";

    }
    else
    {
        ////??????? - i did it outside the function
    }
    fix_h();
    return do_balance();
}
*/
///prrrrrrrrrrrrint treeeeeeeeeee

void tree::print_tree() {
    //vector<int> len(h, 0);
    vector<string> str(h, "");
    int q = to_string(fmax()->src).size();
    int m = (1 << h) - 1;
    math_for_print(str,h, q);

    for(int i = h-1; i >=0 ; i--)
    {
        string a(((1 << i)-1)*q,' ');
        cout << a << str[i] << endl;
    }

}

void tree::math_for_print( vector<string>& s,int hs, int x) {
    string a = to_string(src);
    int need = x - a.size();
    s[hs-1]+= string(need/2, ' ') + a + string ((need - need/2) + (1 << hs)*x-x, ' ');
    if(left!=NULL)
        left->math_for_print(s,hs-1, x);
    else
        math_for_print2(s,hs-1, x);
    if(right!=NULL)
        right->math_for_print(s,hs-1, x);
    else
        math_for_print2(s,hs-1, x);

}

void tree::math_for_print2(vector<string>& s, int hs, int x) {
    if(hs >= 1) s[hs-1] += string((1 << hs)*x, ' ');
    if(hs >= 2) {
        math_for_print2(s, hs - 1, x);
        math_for_print2(s, hs - 1, x);
    }
}

//remake of remove

tree* remove(tree* p, int x)
{
    if( p == NULL ) {
        cout << "element wasn't founded";
        return NULL;
    }
    if( x < p->src )
        p->left = remove(p->left,x);
    else if( x > p->src )
        p->right = remove(p->right,x);
    else //  k == p->src
    {
        tree* l = p->left;
        tree* r = p->right;
        delete p;
        cout << "element was deleted";
        if( r == NULL ) return l;
        tree* min = r->fmin();
        min->right = r->remove_min();
        min->left = l;
        return min->do_balance();
    }
    return p->do_balance();
}

///end of functions

int main() {
cout << (1 << 3);
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
    cout << "Enter tree (введите последовательность натуральных чисел." << endl <<  "Последовательность завершается числом 0, которое означает конец ввода, без его добавления в дерево)" << endl;
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
                 "simple print: 'print'" << endl <<
                 "print full tree with leaves and other tree things: 'fprint'" << endl <<
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
            else {
                a =
                        remove(a, x);

            }
        }
        else if(command == "del_min")
        {
            if(a == NULL)
            {
                cout << "Tree is empty";
            }
            else {//sfjvbsdkhbvsdkhbvskvbsuhfbvks
                a = a->remove_min();
                cout << "element was deleted";
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
            if(a == NULL)
            {
                cout << "Tree is empty";
            }
            else {

                a->print();
            }
        }
        else if(command == "fprint")
        {
            if(a == NULL)
            {
                cout << "Tree is empty";
            }
            else {
                a->print_tree();
            }
        }
        cout << endl;
        cin >> command;
    }


    return 0;
}
/*
 * if(a->left != NULL)
                {
                    cout << "here";
                    tree *l = a->left;
                    tree *r = a->right;
                    tree *bm = a->left->before_max();
                    tree * m = bm->right;
                    bm->right = m->left;
                    cout << "here";
                    delete a;
                    cout << "element was deleted";
                    a = m;
                    a->left = l;
                    a->right = r;
                }
                else if (a->right != NULL)
                {
                    cout << "here";
                    tree *l = a->left;
                    tree *r = a->right;
                    tree *bm = a->right->before_min();
                    tree * m = bm->left;
                    bm->left = m->right;
                    cout << "here";
                    delete a;
                    cout << "element was deleted";
                    a = m;

                    a->left = l;
                    a->right = r;
                }
                else
                {
                    delete a;
                    a = NULL;
                }
                if(a != NULL)
                {
                    a = a->do_balance();
                }

            }
            else {
                a = a->remove(x);
            }
 */