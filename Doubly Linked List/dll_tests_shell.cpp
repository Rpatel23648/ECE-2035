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

// Helper function for creating a lot of dummy values
void make_items(ListItem* result[], unsigned n)
{
	while(n--)
	{
		result[n] = (ListItem*) malloc(sizeof(ListItem));
	}
}


// Initialization tests
TEST(InitTest, CreateDestroy)
{
	DLinkedList* list = create_dlinkedlist();
	destroyList(list);
}

// Access tests
TEST(Access, getHead_Empty)
{
	DLinkedList* list = create_dlinkedlist();
	EXPECT_EQ(NULL, getHead(list));
	destroyList(list);
}

TEST(Access, getTail_Empty)
{
	DLinkedList* list = create_dlinkedlist();
	EXPECT_EQ(NULL, getTail(list));
	destroyList(list);
}

TEST(Access, getSize_Empty)
{
	DLinkedList* list = create_dlinkedlist();
	EXPECT_EQ(0, getSize(list));
	destroyList(list);
}

// Insertion tests
TEST(Insert, Head_Single)
{
	// Initialize items for your test
	size_t num_items = 1;
	ListItem* m[num_items]; make_items(m, num_items);

	// Use the items in your list
	DLinkedList* list = create_dlinkedlist();
	insertHead(list, m[0]);

	// Check that the behavior was correct
	EXPECT_EQ(m[0], getData(getHead(list)));
	EXPECT_EQ(m[0], getData(getTail(list)));
	EXPECT_EQ(1, getSize(list));

	// Delete the list
	destroyList(list);
}

TEST(Insert, Head_Multiple)
{
	// Create list items
	size_t num_items = 3;
	ListItem* m[num_items]; make_items(m, num_items);

	// Insert 3 items at the head (resulting list is [2, 1, 0])
	DLinkedList* list = create_dlinkedlist();
	for (int i = 0; i < 3; i++){
	  insertHead(list, m[i]);
	}

	// Check forward links
	LLNode* current = getHead(list);
	for (int i = 2; i >= 0; i--){
	  ASSERT_EQ(m[i], getData(current));
	  current = getNext(current);
	}
	ASSERT_EQ(NULL, current);

	// Check backward links
	current = getTail(list);
	for (int i = 0; i <= 2; i++){
	  ASSERT_EQ(m[i], getData(current));
	  current = getPrev(current);
	}
	ASSERT_EQ(NULL, current);

	ASSERT_EQ(num_items, getSize(list));

	// Delete the list
	destroyList(list);
}

// Add more tests (e.g., inserting at tail, inserting before/after a node
// in the middle)

// Add deletion tests

// Add split tests

