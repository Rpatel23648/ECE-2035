extern "C" {
    #include "doubly_linked_list.h"
}
#include "gtest/gtest.h"


// Use the TEST macro to define your tests.
//
// TEST has two parameters: the test case name and the test name.
// After using the macro, you should define your test logic between a
// pair of braces.  You can use a bunch of macros to indicate the
// success or failure of a test.  EXPECT_TRUE and EXPECT_EQ are
// examples of such macros.  For a complete list, see gtest.h.
//
// <TechnicalDetails>
//
// In Google Test, tests are grouped into test cases.  This is how we
// keep test code organized.  You should put logically related tests
// into the same test case.
//
// The test case name and the test name should both be valid C++
// identifiers.  And you should not use underscore (_) in the names.
//
// Google Test guarantees that each test you define is run exactly
// once, but it makes no guarantee on the order the tests are
// executed.  Therefore, you should write your tests in such a way
// that their results don't depend on their order.
//
// </TechnicalDetails>

// Dummy value to store in LLNode
// Note that any type of data (e.g. int, double, struct and etc.) can
// be stored in the data of the LLNode for testing your doubly linked list.
// Only the pointer to the data will be stored in the LLNode.
struct ListItem {};

// Helper function to create dummy items
void make_items(ListItem* result[], unsigned n) {
    while (n--) {
        result[n] = (ListItem*)malloc(sizeof(ListItem));
    }
}

// Initialization Tests

TEST(InitTest, CreateDestroy) {
    DLinkedList* list = create_dlinkedlist();
    EXPECT_NE(nullptr, list);  // Ensure the list is created
    EXPECT_EQ(0, getSize(list));  // Ensure size is initially 0
    EXPECT_EQ(nullptr, getHead(list));
    EXPECT_EQ(nullptr, getTail(list));
    destroyList(list);  // Verify no memory leaks
}


// Access Tests


TEST(Access, getHead_Empty) {
    DLinkedList* list = create_dlinkedlist();
    EXPECT_EQ(nullptr, getHead(list));
    destroyList(list);
}

TEST(Access, getTail_Empty) {
    DLinkedList* list = create_dlinkedlist();
    EXPECT_EQ(nullptr, getTail(list));
    destroyList(list);
}

TEST(Access, getSize_Empty) {
    DLinkedList* list = create_dlinkedlist();
    EXPECT_EQ(0, getSize(list));
    destroyList(list);
}


// Insertion Tests

TEST(Insert, Head_Single) {
    ListItem* item = (ListItem*)malloc(sizeof(ListItem));
    DLinkedList* list = create_dlinkedlist();

    insertHead(list, item);

    EXPECT_EQ(item, getData(getHead(list)));
    EXPECT_EQ(item, getData(getTail(list)));
    EXPECT_EQ(1, getSize(list));

    destroyList(list);  // Free list and item
}

TEST(Insert, Head_Multiple) {
    size_t num_items = 3;
    ListItem* m[num_items];
    make_items(m, num_items);

    DLinkedList* list = create_dlinkedlist();

    for (size_t i = 0; i < num_items; i++) {
        insertHead(list, m[i]);
    }

    // Validate forward links
    LLNode* current = getHead(list);
    for (int i = num_items - 1; i >= 0; i--) {
        ASSERT_EQ(m[i], getData(current));
        current = getNext(current);
    }
    ASSERT_EQ(nullptr, current);

    // Validate backward links
    current = getTail(list);
    for (size_t i = 0; i < num_items; i++) {
        ASSERT_EQ(m[i], getData(current));
        current = getPrev(current);
    }
    ASSERT_EQ(nullptr, current);

    ASSERT_EQ(num_items, getSize(list));

    destroyList(list);  // Free list and items
}

TEST(Insert, Tail_Single) {
    ListItem* item = (ListItem*)malloc(sizeof(ListItem));
    DLinkedList* list = create_dlinkedlist();

    insertTail(list, item);

    EXPECT_EQ(item, getData(getHead(list)));
    EXPECT_EQ(item, getData(getTail(list)));
    EXPECT_EQ(1, getSize(list));

    destroyList(list);
}

TEST(Insert, Tail_Multiple) {
    size_t num_items = 3;
    ListItem* m[num_items];
    make_items(m, num_items);

    DLinkedList* list = create_dlinkedlist();

    for (size_t i = 0; i < num_items; i++) {
        insertTail(list, m[i]);
    }

    // Validate forward links
    LLNode* current = getHead(list);
    for (size_t i = 0; i < num_items; i++) {
        ASSERT_EQ(m[i], getData(current));
        current = getNext(current);
    }
    ASSERT_EQ(nullptr, current);

    // Validate backward links
    current = getTail(list);
    for (int i = num_items - 1; i >= 0; i--) {
        ASSERT_EQ(m[i], getData(current));
        current = getPrev(current);
    }
    ASSERT_EQ(nullptr, current);

    ASSERT_EQ(num_items, getSize(list));

    destroyList(list);
}

TEST(Insert, BeforeAndAfter) {
    size_t num_items = 3;
    ListItem* m[num_items];
    make_items(m, num_items);

    DLinkedList* list = create_dlinkedlist();

    // Insert the first item
    insertHead(list, m[0]);
    LLNode* first_node = getHead(list);

    // Insert after the first node
    insertAfter(list, first_node, m[1]);
    EXPECT_EQ(m[1], getData(getNext(first_node)));

    // Insert before the first node
    insertBefore(list, first_node, m[2]);
    EXPECT_EQ(m[2], getData(getHead(list)));

    ASSERT_EQ(3, getSize(list));

    destroyList(list);
}


// Deletion Tests

TEST(Delete, SingleNode) {
    ListItem* item = (ListItem*)malloc(sizeof(ListItem));
    DLinkedList* list = create_dlinkedlist();

    insertHead(list, item);
    LLNode* node = getHead(list);

    deleteNode(list, node);

    EXPECT_EQ(0, getSize(list));
    EXPECT_EQ(nullptr, getHead(list));
    EXPECT_EQ(nullptr, getTail(list));

    destroyList(list);
}

TEST(Delete, MultipleNodes) {
    size_t num_items = 3;
    ListItem* m[num_items];
    make_items(m, num_items);

    DLinkedList* list = create_dlinkedlist();

    for (size_t i = 0; i < num_items; i++) {
        insertTail(list, m[i]);
    }

    // Delete the head
    deleteNode(list, getHead(list));
    EXPECT_EQ(2, getSize(list));

    // Delete the tail
    deleteNode(list, getTail(list));
    EXPECT_EQ(1, getSize(list));

    // Delete the remaining node
    deleteNode(list, getHead(list));
    EXPECT_EQ(0, getSize(list));

    destroyList(list);
}


// Split Tests


TEST(Split, SplitAtMiddle) {
    size_t num_items = 4;
    ListItem* m[num_items];
    make_items(m, num_items);

    DLinkedList* list = create_dlinkedlist();

    for (size_t i = 0; i < num_items; i++) {
        insertTail(list, m[i]);
    }

    LLNode* split_node = getNext(getHead(list));
    DLinkedList* second_list = split(list, split_node);

    // Validate the first list
    EXPECT_EQ(2, getSize(list));
    EXPECT_EQ(m[0], getData(getHead(list)));
    EXPECT_EQ(m[1], getData(getTail(list)));

    // Validate the second list
    EXPECT_EQ(2, getSize(second_list));
    EXPECT_EQ(m[2], getData(getHead(second_list)));
    EXPECT_EQ(m[3], getData(getTail(second_list)));

    destroyList(list);
    destroyList(second_list);
}


// Edge Case Tests


TEST(EdgeCases, SplitAtTail) {
    ListItem* item = (ListItem*)malloc(sizeof(ListItem));
    DLinkedList* list = create_dlinkedlist();

    insertHead(list, item);

    DLinkedList* second_list = split(list, getTail(list));
    EXPECT_EQ(nullptr, second_list);

    destroyList(list);
}

TEST(EdgeCases, DeleteEmptyList) {
    DLinkedList* list = create_dlinkedlist();
    deleteNode(list, nullptr);  // Should not crash
    destroyList(list);
}