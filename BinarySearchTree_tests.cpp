// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"
#include <sstream>

using namespace std;

TEST(test_stub) {
    
    ASSERT_TRUE(true);
}

TEST(test_empty)
{
    BinarySearchTree<int> b;
    ASSERT_TRUE(b.empty());
    b.insert(0);
    ASSERT_FALSE(b.empty());
}

TEST(test_size)
{
    BinarySearchTree<int> b;
    ASSERT_EQUAL(0, b.size());
    b.insert(1);
    b.insert(2);
    ASSERT_EQUAL(2, b.size());
}

TEST(test_height)
{
    BinarySearchTree<int> b;
    ASSERT_EQUAL(0, b.height());
    b.insert(2);
    b.insert(1);
    b.insert(3);
    ASSERT_EQUAL(2, b.height());
    b.insert(0);
    b.insert(4);
    b.insert(5);
    ASSERT_EQUAL(4, b.height());
}

TEST(test_copy)
{
    BinarySearchTree<int> b;
    b.insert(4);
    b.insert(5);
    b.insert(2);
    BinarySearchTree<int> c;
    c = b;
    ASSERT_EQUAL(*c.begin(), *b.begin());
    ASSERT_EQUAL(*++c.begin(), *++b.begin());
    ASSERT_EQUAL(*++c.begin(), *++b.begin());


    BinarySearchTree<int> d;
    d.insert(12);
    d.insert(4);
    d.insert(5);
    d.insert(7);

    d = b;
    ASSERT_EQUAL(*d.begin(), *b.begin());
    ASSERT_EQUAL(*d.find(4), *b.find(4));
    ASSERT_EQUAL(*d.find(5), *b.find(5));
}

TEST(test_find)
{
    BinarySearchTree<int> b;
    b.insert(4);
    b.insert(5);
    b.insert(2);
   ASSERT_EQUAL(b.find(3), b.end());
   ASSERT_EQUAL(b.find(2), b.begin());
}

TEST(test_insert)
{
    BinarySearchTree<int> b;
    b.insert(4);
    b.insert(5);
    b.insert(2);
    b.insert(3);

}

TEST(test_min_elem)
{
    BinarySearchTree<int> b;
    ASSERT_EQUAL(b.min_element(), b.end());
    BinarySearchTree<int> c;
    c.insert(4);
    c.insert(5);
    c.insert(2);
    c.insert(3);
    ASSERT_EQUAL(c.min_element(), c.begin());
}

TEST(test_max_elem)
{
    BinarySearchTree<int> b;
    ASSERT_EQUAL(b.max_element(), b.end());
    BinarySearchTree<int> c;
    c.insert(4);
    c.insert(5);
    c.insert(2);
    c.insert(3);
    c.begin();
    ++c.begin();
    ++c.begin();
    ++c.begin();
    ASSERT_EQUAL(c.min_element(), c.begin());
}

TEST(test_check_sorting_invariant)
{
    BinarySearchTree<int> c;
    ASSERT_TRUE(c.check_sorting_invariant());
    c.insert(4);
    c.insert(5);
    c.insert(2);
    c.insert(3);
    c.insert(8);
    ASSERT_TRUE(c.check_sorting_invariant());
    *c.begin() = 7;
    ASSERT_FALSE(c.check_sorting_invariant());
    *c.begin() = 3;

    BinarySearchTree<int> d;
    d.insert(2);
    d.insert(4);
    d.insert(5);
    d.insert(1);
    ASSERT_TRUE(d.check_sorting_invariant());
    *d.find(4) = 9;
    ASSERT_FALSE(d.check_sorting_invariant());

}

TEST(test_traverse_inorder)
{
    BinarySearchTree<int> c;
    c.insert(4);
    c.insert(5);
    c.insert(2);
    c.insert(3);

    ostringstream oss_preorder;
    c.traverse_preorder(oss_preorder);
    cout << "preorder" << endl;
    cout << oss_preorder.str() << endl << endl;
    ASSERT_TRUE(oss_preorder.str() == "4 2 3 5 ");


}

TEST(test_traverse_preorder)
{
    BinarySearchTree<int> c;
    c.insert(4);
    c.insert(5);
    c.insert(2);
    c.insert(3);
    ostringstream oss_inorder;
    c.traverse_inorder(oss_inorder);
    cout << "inorder" << endl;
    cout << oss_inorder.str() << endl << endl;
    ASSERT_TRUE(oss_inorder.str() == "2 3 4 5 ");
}

TEST(test_min_greater)
{
    BinarySearchTree<int> c;
    ASSERT_EQUAL(c.min_greater_than(2), c.end());
    c.insert(4);
    c.insert(5);
    c.insert(2);
    c.insert(3);
    ASSERT_EQUAL(*c.min_greater_than(3), 4);
    ASSERT_EQUAL(c.min_greater_than(6), c.end());
}




TEST_MAIN()
