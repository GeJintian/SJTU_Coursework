//
// Created by 69009 on 2019/6/2.
//
#include <iostream>
#include<cstdlib>
#include"p2.h"
static int size_helper(list_t list, int count);
static int dot_helper(list_t v1, list_t v2, int sum);
static list_t reverse_helper(list_t list, list_t rev_list);
static list_t append_helper(list_t rev_first, list_t second);
static list_t odd_helper(list_t list, list_t odd);
static list_t filter_helper(list_t rev_list, list_t fil, bool (*fn)(int));
static list_t unique_helper(list_t rev_list, list_t uniq);
static list_t insert_helper(list_t first, list_t second, unsigned int n, int s1, int s2, list_t inst);
static list_t chop_helper(list_t list, unsigned int n, list_t cho);
static int sum_helper(tree_t tree, int sum);
static int depth_helper(tree_t tree, int count);
static int max_helper(tree_t tree, int max);
static list_t traversal_helper(tree_t tree, list_t list);
static bool Monotonic_helper(tree_t tree, bool (*fn)(int, int), int n);
static bool allPathSum_helper(tree_t tree, int Sum, int sum);







int size(list_t list)
// EFFECTS: Returns the number of elements in "list".
//          Returns zero if "list" is empty.
{
    return size_helper(list, 0);
}
static int size_helper(list_t list, int count)
//EFFECTS: Returns count + lengthof(list) if "list" is not empty
//         Returns 0 if "list" is empty
{
    if(list_isEmpty(list))
    {
        return count;
    }
    else
    {
        return size_helper(list_rest(list),count+1);
    }
}




bool memberOf(list_t list, int val)
// EFFECTS: Returns true if the value "val" appears in "list".
//          Returns false otherwise.
{
    if(list_isEmpty(list))
    {
        return false;
    }
    else if(list_first(list)==val)
    {
        return true;
    }
    else
    {
        return memberOf(list_rest(list),val);
    }
}





int dot(list_t v1, list_t v2)
// REQUIRES: Both "v1" and "v2" are non-empty
//
// EFFECTS: Treats both lists as vectors. Returns the dot
//          product of the two vectors. If one list is longer
//          than the other, ignore the longer part of the vector.
{
    return dot_helper(v1,v2,0);
}
static int dot_helper(list_t v1, list_t v2, int sum)
//EFFECTS:Returns sum + (dot product of elements in v1 and v2)
{
    if(list_isEmpty(v1) == 1 || list_isEmpty(v2) ==1)
    {
        return sum;
    }
    else
    {
        return dot_helper(list_rest(v1), list_rest(v2), sum + list_first(v1) * list_first(v2));
    }
}



bool isIncreasing(list_t v)
// EFFECTS: Checks if the list of integers is increasing.
//          A list is increasing if and only if no element
//          is smaller than its previous element. By default,
//          an empty list and a list of a single element are
//          increasing.
{
    if(list_isEmpty(v) || list_isEmpty(list_rest(v))) return true;
    if(list_first(v) <= list_first(list_rest(v))) return isIncreasing(list_rest(v));
    else return false;

}





list_t reverse(list_t list)
// EFFECTS: Returns the reverse of "list".
{
    return reverse_helper(list,list_make());
}
static list_t reverse_helper(list_t list, list_t rev_list)
//EFFECTS: Return the reverse of "list"
{
    if(list_isEmpty(list)) return rev_list;
    else return reverse_helper(list_rest(list), list_make(list_first(list), rev_list));
}




list_t append(list_t first, list_t second)
// EFFECTS: Returns the list (first second).
{
    return append_helper(reverse(first), second);
}
static list_t append_helper(list_t rev_first, list_t second)
//EFFECTS: Returns the list (rev_first second)
{
    if(list_isEmpty(rev_first)) return second;
    else return append_helper(list_rest(rev_first), list_make(list_first(rev_first), second));
}





bool isArithmeticSequence(list_t v)
// EFFECTS: Checks if the list of integers forms an
//          arithmetic sequence. By default, an empty list and
//          a list of a single element are arithmetic sequences.
{
    if(list_isEmpty(v) || list_isEmpty(list_rest(v)) || list_isEmpty(list_rest(list_rest(v)))) return true;
    if(list_first(v) - list_first(list_rest(v)) == list_first(list_rest(v)) - list_first(list_rest(list_rest(v)))) return isArithmeticSequence(list_rest(v));
    else return false;
}





list_t filter_odd(list_t list)
// EFFECTS: Returns a new list containing only the elements of the
//          original "list" which are odd in value,
//          in the order in which they appeared in list.
{
    return odd_helper(reverse(list),list_make());
}
static list_t odd_helper(list_t list, list_t odd)
//EFFECTS: Return odd with odd in "list"
{
    if(list_isEmpty(list)) return odd;
    if(list_first(list)%2 == 1) return odd_helper(list_rest(list), list_make(list_first(list), odd));
    else return odd_helper(list_rest(list), odd);
}




list_t filter(list_t list, bool (*fn)(int))
// EFFECTS: Returns a list containing precisely the elements of "list"
//          for which the predicate fn() evaluates to true, in the
//          order in which they appeared in list.
{
    return filter_helper(reverse(list), list_make(), fn);
}
static list_t filter_helper(list_t rev_list, list_t fil, bool (*fn)(int))
//EFFECTS: Returns fil with also elements in "list" which is true for fn()
{
    if(list_isEmpty(rev_list)) return fil;
    if(fn(list_first(rev_list))) return filter_helper(list_rest(rev_list), list_make(list_first(rev_list), fil),fn);
    else return filter_helper(list_rest(rev_list), fil, fn);
}





list_t unique(list_t list)
// EFFECTS: Returns a new list comprising of each unique element
//          in "list". The order is determined by the first
//          occurrence of each unique element in "list".
{
    return unique_helper(reverse(list),list_make());
}
static list_t unique_helper(list_t rev_list, list_t uniq)
//EFFECTS: Returns uniq with all unique elements in "rev_list"
{
    if(list_isEmpty(rev_list)) return uniq;
    if(memberOf(list_rest(rev_list),list_first(rev_list))) return unique_helper(list_rest(rev_list),uniq);
    else return unique_helper(list_rest(rev_list), list_make(list_first(rev_list),uniq));
}






list_t insert_list(list_t first, list_t second, unsigned int n)
// REQUIRES: n <= the number of elements in "first".
//
// EFFECTS: Returns a list comprising the first n elements of
//          "first", followed by all elements of "second",
//          followed by any remaining elements of "first".
{
    return insert_helper(reverse(first), reverse(second), n, size(first), size(second), list_make());
}
static list_t insert_helper(list_t first, list_t second, unsigned int n, int s1, int s2, list_t inst)
//REQUIRES: n <= the number of elements in "first".
// EFFECTS: Returns a list comprising the first n elements of
//          "first", followed by all elements of "second",
//          followed by any remaining elements of "first".
{
    if(list_isEmpty(first))
    {
        if(list_isEmpty(inst)) return reverse(second);
        else
        {
            if(list_isEmpty(second)) return inst;
        }
    }
    if(s1-n > 0) return insert_helper(list_rest(first), second, n, s1 - 1 ,s2, list_make(list_first(first),inst));
    else
    {
        if(s2 > 0) return insert_helper(first, list_rest(second), n, s1, s2 - 1, list_make(list_first(second),inst));
        else return insert_helper(list_rest(first), second, n, s1 - 1 ,s2, list_make(list_first(first),inst));
    }
}





list_t chop(list_t list, unsigned int n)
// REQUIRES: "list" has at least n elements.
//
// EFFECTS: Returns the list equal to "list" without its last n
//          elements.
{
    return reverse(chop_helper(list, size(list) - n, list_make()));
}
static list_t chop_helper(list_t list, unsigned int n, list_t cho)
// REQUIRES: "list" has at least n elements.
//
// EFFECTS: Returns the list equal to "list" without its last n
//          elements.
{
    if(n > 0) return chop_helper(list_rest(list), n - 1, list_make(list_first(list),cho));
    else return cho;
}


int tree_sum(tree_t tree)
// EFFECTS: Returns the sum of all elements in "tree".
//          Returns zero if "tree" is empty.
{
    return sum_helper(tree, 0);
}
static int sum_helper(tree_t tree, int sum)
//EFFECTS: Returns sum + the sum of elements in "tree"
{
    if(tree_isEmpty(tree)) return sum;
    else return sum_helper(tree_left(tree),sum + tree_elt(tree))+ sum_helper(tree_right(tree),0);
}


bool tree_search(tree_t tree, int val)
// EFFECTS: Returns true if the value "val" appears in "tree".
//          Returns false otherwise.
{
    if(tree_isEmpty(tree)) return false;
    if(tree_elt(tree) == val) return true;
    else return tree_search(tree_left(tree),val) || tree_search(tree_right(tree),val);
}




int depth(tree_t tree)
// EFFECTS: Returns the depth of "tree", which equals the number of
//          layers of nodes in the tree.
//          Returns zero if "tree" is empty.
{
    return depth_helper(tree,0);
}
static int depth_helper(tree_t tree, int count)
//EFFECTS: Returns the maximum depth of the tree (along right or left)
{
    if(tree_isEmpty(tree)) return count;
    int count_left = depth_helper(tree_left(tree),count+1);
    int count_right = depth_helper(tree_right(tree),count+1);
    if(count_left > count_right) return count_left;
    else return count_right;
}





int tree_max(tree_t tree)
// REQUIRES: "tree" is non-empty.
//
// EFFECTS: Returns the largest element in "tree".
{
    return max_helper(tree, tree_elt(tree));
}
static int max_helper(tree_t tree, int max)
//EFFECTS: Returns the maximum between max and the elements in the "tree"
{
    if(tree_isEmpty(tree)) return max;
    if(max<tree_elt(tree)) max = tree_elt(tree);
    int max_left = max_helper(tree_left(tree),max);
    int max_right = max_helper(tree_right(tree),max);
    if(max_left > max_right) return max_left;
    else return max_right;
}



list_t traversal(tree_t tree)
// EFFECTS: Returns the elements of "tree" in a list using an
//          in-order traversal. An in-order traversal prints
//          the "left most" element first, then the second-left-most,
//          and so on, until the right-most element is printed.
//
//          For any node, all the elements of its left subtree
//          are considered as on the left of that node and
//          all the elements of its right subtree are considered as
//          on the right of that node.
{
    return traversal_helper(tree, list_make());
}
static list_t traversal_helper(tree_t tree, list_t list)
{
    if(tree_isEmpty(tree)) return list;
    else
    {
        return append(traversal_helper(tree_left(tree),list_make(tree_elt(tree),list_make())),traversal_helper(tree_right(tree),list));
    }
}



bool increase(int a, int b)
{
    if(a<b) return true;
    else return false;
}
bool decrease(int a, int b)
{
    if(a>b) return true;
    else return false;
}


bool tree_hasMonotonicPath(tree_t tree)
// EFFECTS: Returns true if and only if "tree" has at least one
//          root-to-leaf path such that all the elements along the
//          path form a monotonically increasing or decreasing
//          sequence.
//
//          A root-to-leaf path is a sequence of elements in a tree
//          starting with the root element and proceeding downward
//          to a leaf (an element with no children).
//
//          An empty tree has no root-to-leaf path.
//
//          A monotonically increasing (decreasing) sequence is a
//          sequence of numbers where no number is smaller (larger)
//          than its previous number.
{
    if(tree_isEmpty(tree)) return false;
    else return Monotonic_helper(tree,increase,tree_elt(tree) - 1) || Monotonic_helper(tree, decrease, tree_elt(tree) + 1);
}
static bool Monotonic_helper(tree_t tree, bool (*fn)(int, int), int n)
{
    if(tree_isEmpty(tree)) return true;
    if(tree_isEmpty(tree_left(tree)) && !tree_isEmpty(tree_right(tree))) {
        if(!fn(n,tree_elt(tree))) return false;
        else return Monotonic_helper(tree_right(tree), fn, tree_elt(tree));
    }
    if(!tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree))) {
        if(!fn(n,tree_elt(tree))) return false;
        else return Monotonic_helper(tree_left(tree), fn, tree_elt(tree));
    }
    //if(tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree))) return true;
    else
    {
        if(!fn(n,tree_elt(tree))) return false;
        else return Monotonic_helper(tree_left(tree), fn, tree_elt(tree)) || Monotonic_helper(tree_right(tree), fn, tree_elt(tree));
    }
}







bool tree_allPathSumGreater(tree_t tree, int sum)
// REQUIRES: tree is not empty
//
// EFFECTS: Returns true if and only if for each root-to-leaf
//          path of "tree", the sum of all elements along the path
//          is greater than "sum".
//
//          A root-to-leaf path is a sequence of elements in a tree
//          starting with the root element and proceeding downward
//          to a leaf (an element with no children).
{
    return allPathSum_helper(tree, sum, 0);
}
static bool allPathSum_helper(tree_t tree, int Sum, int sum)
{
    if(tree_isEmpty(tree)) //return true;
    //if(tree_isEmpty(tree_right(tree)) && tree_isEmpty(tree_left(tree)))
    {
        if(sum > Sum) return true;
        else return false;
    }
    if(tree_isEmpty(tree_left(tree)) && !tree_isEmpty(tree_right(tree))) {
        return allPathSum_helper(tree_right(tree), Sum, sum + tree_elt(tree));
    }
    if(!tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree))) {
        return allPathSum_helper(tree_right(tree), Sum, sum + tree_elt(tree));
    }
    else return allPathSum_helper(tree_right(tree), Sum, sum + tree_elt(tree)) && allPathSum_helper(tree_left(tree), Sum, sum + tree_elt(tree));
}








bool covered_by(tree_t A, tree_t B)
// EFFECTS: Returns true if tree A is covered by tree B.
{
    if(tree_isEmpty(A)) return true;
    else
    {
        if(tree_isEmpty(B)) return false;
        if(tree_elt(A) == tree_elt(B)) return covered_by(tree_right(A),tree_right(B)) && covered_by(tree_left(A),tree_left(B));
        else return false;
    }
}





bool contained_by(tree_t A, tree_t B)
// EFFECTS: Returns true if tree A is covered by tree B
//          or a subtree of B.
{
    if(covered_by(A,B)) return true;
    if(tree_isEmpty(B)) return false;
    else return contained_by(A, tree_right(B)) || contained_by(A, tree_left(B));
}






tree_t insert_tree(int elt, tree_t tree)
// REQUIRES: "tree" is a sorted binary tree.
//
// EFFECTS: Returns a new tree with elt inserted at a leaf such that
//          the resulting tree is also a sorted binary tree.
{
    if(tree_isEmpty(tree)) return tree_make(elt,tree_make(),tree_make());
    else
    {
        if(elt<tree_elt(tree)) return tree_make(tree_elt(tree),insert_tree(elt,tree_left(tree)),tree_right(tree));
        else return tree_make(tree_elt(tree),tree_left(tree),insert_tree(elt,tree_right(tree)));
    }
}





