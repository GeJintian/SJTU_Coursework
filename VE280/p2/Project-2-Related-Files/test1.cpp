#include "p2.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::vector;

// Use anonymous namespace to make the functions local.
namespace {
    // Test for list_make() function.
    void list_make_test();

    // Construct a list from a vector.
    // MODIFIES: the input list ls.
    void list_from_vec(list_t &ls, const vector<int> &vec);

    // Testing functions for list_t objects. We split the test for
    // various functions into multiple functions.
    void list_fun_test1();
    void list_fun_test2();

    // Recursively construct a binary tree with a given depth d from a
    // vector vec. MODIFIES: the input tree tr.
    tree_t tree_from_vec(const vector<int> &vec, const int d,
                         const int root_pos=0);

    // Test function for tree_from_vec().
    void tree_from_vec_test();

    // Test functions for tree_t objects.
    void tree_fun_test1();
}

int main()
{
    tree_fun_test1();
    return 0;
}

// Beginning of function definitions in anonymous namespace.
namespace {

void list_make_test()
{
    list_t ls = list_make();
    ls = list_make(1, ls);
    ls = list_make(2, ls);
    ls = list_make(3, ls);
    list_print(ls);
    cout << endl;
}

void list_from_vec(list_t &ls, const vector<int> &vec)
{
    ls = list_make();
    for (auto i = vec.crbegin(); i != vec.crend(); ++i) {
        ls = list_make(*i, ls);
    }
}

void list_fun_test1()
{
    // define some lists and accompanying arrays for later use.
    list_t ls1, ls2, ls3, ls4;
    vector<int> vec1 = {1, 2, 3};
    vector<int> vec2 = {2, 4, 6, 8, 10};
    vector<int> vec3 = {};
    vector<int> vec4 = {4, 5, 6};
    list_from_vec(ls1, vec1);
    list_from_vec(ls2, vec2);
    list_from_vec(ls3, vec3);
    list_from_vec(ls4, vec4);

    list_print(ls1);
    cout << endl;
    list_print(ls2);
    cout << endl;
    list_print(ls3);
    cout << endl;
    list_print(ls4);
    cout << '\n'
         << endl;

    // Test for the size() function.
    cout << "Size of the lists:\n";
    cout << size(ls1) << ' ' << size(ls2) << ' ' << size(ls3) << ' ' << endl;

    // Test for the memberOf() function.
    for (int i = 1; i != 11; ++i) {
        cout << i << " in ls2: " << memberOf(ls2, i) << endl;
    }

    // Test for the dot function.
    cout << "Dot product of ls1 and ls2: " << dot(ls1, ls2) << endl;
    cout << "Dot product of ls2 and ls1: " << dot(ls2, ls1) << endl;
    cout << "Dot product of ls1 and ls3: " << dot(ls1, ls3) << endl;
    cout << "Dot product of ls1 and ls4: " << dot(ls1, ls4) << endl;

    // test for the isIncreasing() function.
    vec2 = {2};
    list_from_vec(ls2, vec2);
    vec4 = {1, 2, 3, 2, 5};
    list_from_vec(ls4, vec4);
    cout << isIncreasing(ls1) << ' ' << isIncreasing(ls2) << ' '
         << isIncreasing(ls3) << ' ' << isIncreasing(ls4) << endl;

    // test for the reverse() function.
    list_print(reverse(ls1));
    cout << endl;
    list_print(ls1);
    cout << endl;

    // test for the append() function.
    vec3 = {5, 6, 7};
    list_from_vec(ls3, vec3);
    cout << "ls1: ";
    list_print(ls1);
    cout << endl
         << "ls3: ";
    list_print(ls3);
    cout << endl
         << "ls1 + ls3: ";
    list_print(append(ls1, ls3));
    cout << endl
         << "ls3 + ls1: ";
    list_print(append(ls3, ls1));
    cout << endl;
}

void list_fun_test2()
{
    // define some lists and accompanying arrays for later use.
    list_t ls1, ls2, ls3, ls4, ls5;
    vector<int> vec1 = {1};
    vector<int> vec2 = {};
    vector<int> vec3 = {1, 3, 5, 7};
    vector<int> vec4 = {1, 2};
    vector<int> vec5 = {10, 3, 2};
    list_from_vec(ls1, vec1);
    list_from_vec(ls2, vec2);
    list_from_vec(ls3, vec3);
    list_from_vec(ls4, vec4);
    list_from_vec(ls5, vec5);

    // Test for isArithmeticSequence().
    cout << isArithmeticSequence(ls1) << ' ' << isArithmeticSequence(ls2) << ' '
         << isArithmeticSequence(ls3) << ' ' << isArithmeticSequence(ls4) << ' '
         << isArithmeticSequence(ls5) << '\n'
         << endl;

    // Test for filter_odd().
    vec4 = {3, 4, 1, 5, 6};
    vec5 = {2, 4, 6, 8, 10};
    list_from_vec(ls4, vec4);
    list_from_vec(ls5, vec5);
    list_print(filter_odd(ls1));
    cout << endl;
    list_print(filter_odd(ls2));
    cout << endl;
    list_print(filter_odd(ls3));
    cout << endl;
    list_print(filter_odd(ls4));
    cout << endl;
    list_print(filter_odd(ls5));
    cout << '\n'
         << endl;

    // Test for unique().
    vec3 = {1, 1, 2, 1, 3, 5, 5, 3, 4, 5, 4};
    vec4 = {2, 1, 2, 3, 3, 4, 4, 5, 4, 3, 1};
    vec5 = {1, 1, 1, 1};
    list_from_vec(ls1, vec1);
    list_from_vec(ls2, vec2);
    list_from_vec(ls3, vec3);
    list_from_vec(ls4, vec4);
    list_from_vec(ls5, vec5);
    list_print(unique(ls1));
    cout << endl;
    list_print(unique(ls2));
    cout << endl;
    list_print(unique(ls3));
    cout << endl;
    list_print(unique(ls4));
    cout << endl;
    list_print(unique(ls5));
    cout << '\n'
         << endl;

    // Test for the insert_list() and chop() function.
    vec3 = {1, 2, 3, 4, 5};
    vec4 = {12, 11, 10};
    list_from_vec(ls3, vec3);
    list_from_vec(ls4, vec4);
    list_print(insert_list(ls3, ls4, 0));
    cout << '\n';
    list_print(insert_list(ls3, ls4, 2));
    cout << '\n';
    list_print(insert_list(ls3, ls4, 5));
    cout << '\n';
    list_print(insert_list(ls3, ls1, 3));
    cout << '\n';
    list_print(insert_list(ls3, ls2, 3));
    cout << '\n';
    list_print(insert_list(ls2, ls3, 0));
    cout << '\n'
         << endl;
}

tree_t tree_from_vec(const vector<int> &vec, const int d, const int root_pos)
{
    // To represent a binary tree of depth d using a vector, vec[0]
    // stores the integer element of the root node, vec[0*2+1] = vec[1]
    // and vec[0*2+2] = vec[2] stores the element of the root of the
    // tree's left subtree and right subtree, etc. We use 0 to denote
    // an empty tree node, which is somewhat flawed, since by doing this
    // the elements of the generated tree cannot be zero.

    // Return an empty tree when vec is empty.
    if (vec.size() == 0) {
        return tree_make();
    }

    if (vec[root_pos] == 0) {
        return tree_make();
    }
    // From calculation, we know that for a tree with depth d, the
    // elements in vec with index greater than 2^(d-1) - 2 are the
    // nodes with depth d.
    if (root_pos > std::pow(2, d-1)-2) {
        tree_t tr_empty = tree_make();
        return tree_make(vec[root_pos], tr_empty, tr_empty);
    }
    // In the following case, the node must have a depth less than d,
    // so it have (potentially empty) left and right subtrees.
    tree_t tr_left = tree_from_vec(vec, d, root_pos*2 + 1);
    tree_t tr_right = tree_from_vec(vec, d, root_pos*2 + 2);
    return tree_make(vec[root_pos], tr_left, tr_right);
}

void tree_from_vec_test()
{
    int depth = 4;
    vector<int> vec = {4, 2, 5, 0, 3, 0, 8, 0, 0, 6, 7, 1, 0, 0, 0};
    tree_t tree = tree_from_vec(vec, depth);
    tree_print(tree);
    cout << "end" << endl;
    tree = tree_from_vec({}, 0);
    tree_print(tree);
    cout << "end" << endl;
    tree = tree_from_vec({-1}, 1);
    tree_print(tree);
    cout << "end" << endl;
    tree = tree_from_vec({1, 0, -2, 0, 1, 3, 0}, 3);
    tree_print(tree);
    cout << "end" << endl;
}

void tree_fun_test1()
{
    vector<int> vec = {-1, 2, -3, 4, -5, 6, -7};
    tree_t tree = tree_from_vec(vec, 3);

    // Test for tree_sum().
    assert(tree_sum(tree) == -1+2-3+4-5+6-7);
    tree = tree_from_vec({1, 2, 3, 0, 0, 0, 1}, 3);
    assert(tree_sum(tree) == 1+2+3+1);
    tree = tree_from_vec({-3, 1, 0}, 2);
    assert(tree_sum(tree) == -3+1);

    // Test for tree_search().
    tree = tree_from_vec(vec, 3);
    assert(tree_search(tree, -1));
    assert(tree_search(tree, 2));
    assert(tree_search(tree, -5));
    assert(tree_search(tree, -7));
    assert(!tree_search(tree, 10));
    assert(!tree_search(tree, -10));

    // Test for depth().
    assert(depth(tree) == 3);
    tree = tree_from_vec({4, 2, 5, 0, 3, 0, 8, 0, 0, 6, 7, 0, 0, 0, 0}, 4);
    assert(depth(tree) == 4);
    tree = tree_from_vec({1}, 1);
    tree = tree_make();
    assert(depth(tree) == 0);

    // Test for tree_max().
    tree = tree_from_vec(vec, 3);
    assert(tree_max(tree) == 6);
    tree = tree_from_vec({-1, -2, -3}, 2);
    assert(tree_max(tree) == -1);
    tree = tree_from_vec({1, 6, 3, 1, 0, 5, 6}, 3);
    assert(tree_max(tree) == 6);
    tree = tree_from_vec({1}, 1);
    assert(tree_max(tree) == 1);
    tree = tree_from_vec({-10000}, 1);
    assert(tree_max(tree) == -10000);

    // Test for traversal().
    cout << "Test for traversal:\n\n";
    tree = tree_from_vec(vec, 3);
    tree_print(tree);
    list_print(traversal(tree));
    cout << '\n' << endl;
    tree = tree_from_vec({4, 2, 5, 0, 3, 0, 0}, 3);
    tree_print(tree);
    list_print(traversal(tree));
    cout << '\n' << endl;
    tree = tree_from_vec({1, 0, 2, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 4}, 4);
    tree_print(tree);
    list_print(traversal(tree));
    cout << '\n' << endl;
    tree = tree_make();
    list_print(traversal(tree));
    cout << '\n' << endl;

    // Test for tree_hasMonotonicPath().
    tree = tree_from_vec(vec, 3);
    assert(tree_hasMonotonicPath(tree));
    tree = tree_from_vec({4, 8, 0, 3, 16, 0, 0}, 3);
    assert(tree_hasMonotonicPath(tree));
    tree = tree_from_vec({1, 22, 23, 4, 5, 6, 27, 8, 9, 10, 11, 12, 13, 14,
                          30}, 4);
    assert(tree_hasMonotonicPath(tree));

    // Test for tree_allPathSumGreater().
    tree = tree_from_vec({4, 1, 5, 3, 6, 0, 0}, 3);
    assert(!tree_allPathSumGreater(tree, 8));
    cout << endl;
    assert(tree_allPathSumGreater(tree, 7));
    cout << endl;
    tree = tree_from_vec(vec, 3);
    assert(tree_allPathSumGreater(tree, -100));
    cout << endl;

    // Print "Test passed!" in the end.
    cout << "Test passed!" << endl;
}

// Ending brace of the anonymous namespace.
}
