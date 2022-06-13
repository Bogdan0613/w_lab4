#include "prioritylist.h"
#include <cstring>
#include <iostream>
#include <sstream>

#define TEST_STAGE 6

#if TEST_STAGE > 0
void check_empty_list(const prioritylist& plist)
{
    if (not plist.is_empty())
        std::cerr << "Error in empty() for empty list.\n";

    if (plist.size() != 0)
        std::cerr << "Error in size() for empty list.\n";

    if (plist.get_first() != nullptr)
        std::cerr << "Error in head pointer - it should be nullptr.\n";
}
#endif // TEST_STAGE

int main()
{

#if TEST_STAGE > 0

    {
        std::cerr << "tests on empty list\n";

        prioritylist empty_list;
        check_empty_list(empty_list);
    }

#endif // TEST_STAGE

#if TEST_STAGE > 1

    {
        std::cerr << "tests on one-element list\n";

        prioritylist oneelement;
        oneelement.push_front("the first client");

        if (oneelement.is_empty())
            std::cerr << "Error in is_empty() for one-element list.\n";
        if (oneelement.size() != 1)
            std::cerr << "Error in size() for one-element list.\n";

        if (oneelement.get_first() == nullptr)
            std::cerr << "Error in header pointer for one-element list.\n";
        else
        {
            if (oneelement.get_first()->get_priority() != default_priority) // default priority
                std::cerr << "Error in val member in one-element list.\n";
            if (oneelement.get_first()->get_next() != nullptr)
                std::cerr << "Error in next member in one-element list.\n";
        }

        // pop the only client & check empty
        oneelement.pop_front();
        check_empty_list(oneelement);

        // let's try to pop from empty list - should do no harm
        oneelement.pop_front();
        check_empty_list(oneelement);
    }

#endif // TEST_STAGE

#if TEST_STAGE > 2

    {
        std::cerr << "try inserting element at the front\n";

        prioritylist multiple;
        multiple.insert("the first", 55);

        if (multiple.size() != 1)
            std::cerr << "Error in size() after the first insert.\n";

        if (multiple.get_first() == nullptr)
            std::cerr << "Error in header pointer after the first insert.\n";
        else
        {
            if (multiple.get_first()->get_priority() != 55)
                std::cerr << "Error in priority member after the first insert.\n";
            if (strcmp(multiple.get_first()->get_name(), "the first") != 0)
                std::cerr << "Error in the name after the first insert.\n";
            if (multiple.get_first()->get_next() != nullptr)
                std::cerr << "Error in next member after the first insert.\n";
        }

        std::cerr << "add the second element again at the front\n";
        prioritylist::pl_node const* the_last = multiple.get_first();

        multiple.insert("the second", 33);

        if (multiple.size() != 2)
            std::cerr << "Error in size() after the second insert.\n";

        if (multiple.get_first() == nullptr)
            std::cerr << "nullptr header pointer after the second insert.\n";
        else
        {
            if (multiple.get_first()->get_priority() != 33)
                std::cerr << "Error in priority member after the second insert.\n";
            if (strcmp(multiple.get_first()->get_name(), "the second") != 0)
                std::cerr << "Error in the name after the second insert.\n";
            if (multiple.get_first()->get_next() != the_last)
                std::cerr << "Error in next member after the second insert.\n";
        }

        std::cerr << "now the third element in the middle\n";

        prioritylist::pl_node const* the_first = multiple.get_first();

        multiple.insert("the third", 44);

        if (multiple.size() != 3)
            std::cerr << "Error in size() after the third insert.\n";

        if (multiple.get_first() == nullptr)
            std::cerr << "nullptr header pointer after the third insert.\n";
        else
        {
            // head of the list should not change
            if (multiple.get_first() != the_first)
                std::cerr << "header pointer changed after the third insert.\n";

            prioritylist::pl_node const* inserted = multiple.get_first()->get_next();
            if (inserted != nullptr)
            {
                if (inserted->get_priority() != 44)
                    std::cerr << "Error in priority member after the third insert.\n";
                if (strcmp(inserted->get_name(), "the third") != 0)
                    std::cerr << "Error in the name after the third insert.\n";
                if (inserted->get_next() != the_last)
                    std::cerr << "Error in next member after the third insert.\n";
            }
        }

        std::cerr << "now the fourth element at the end\n";

        multiple.insert("the fourth", 66);

        if (multiple.size() != 4)
            std::cerr << "Error in size() after the fourth insert.\n";

        if (multiple.get_first() == nullptr)
            std::cerr << "nullptr header pointer after the fourth insert.\n";
        else
        {
            // head of the list should not change
            if (multiple.get_first() != the_first)
                std::cerr << "header pointer changed after the fourth insert.\n";
            prioritylist::pl_node const* inserted = the_last->get_next();
            if (inserted != nullptr)
            {
                if (inserted->get_priority() != 66)
                    std::cerr << "Error in priority member after the fourth insert.\n";
                if (strcmp(inserted->get_name(), "the fourth") != 0)
                    std::cerr << "Error in the name after the fourth insert.\n";
                if (inserted->get_next() != nullptr)
                    std::cerr << "Error in next member after the fourth insert.\n";
            }
        }

        if (multiple.get_first() == nullptr || the_last == nullptr || the_first == nullptr)
        {
            std::cerr << "\nThe list is broken - skipping remove tests.\n";
            return 1;
        }

        // now let's test remove
        if (multiple.remove("non-removing"))
            std::cerr << "remove returns true for non-existing name.\n";
        if (multiple.size() != 4)
            std::cerr << "Error in size() after non-removing remove.\n";

        // remove the last element
        if (not multiple.remove("the fourth"))
            std::cerr << "remove returns false for existing name.\n";
        if (multiple.size() != 3)
            std::cerr << "Error in size() after removing the last element.\n";
        if (the_last->get_next() != nullptr)
            std::cerr << "Invalid next pointer after removing the last element.\n";

        // remove the middle element
        if (not multiple.remove("the third"))
            std::cerr << "remove returns false for existing name.\n";
        if (multiple.size() != 2)
            std::cerr << "Error in size() after removing the middle element.\n";
        if (the_first->get_next() != the_last)
            std::cerr << "Invalid next pointer after removing the middle element.\n";

        // remove the first element
        if (not multiple.remove("the second"))
            std::cerr << "remove returns false for existing name.\n";
        if (multiple.size() != 1)
            std::cerr << "Error in size() after removing the first element.\n";
        if (multiple.get_first()->get_next() != nullptr)
            std::cerr << "Invalid next pointer after removing the first element.\n";

        // remove the first (and only) element
        if (not multiple.remove("the first"))
            std::cerr << "remove returns false for existing name.\n";
        check_empty_list(multiple);
    }

#endif // TEST_STAGE

#if TEST_STAGE > 3

    {
        std::cerr << "test print method (implementation of the test is interesting)\n";
        // first test empty list
        prioritylist to_print;

        std::stringstream ss;

        to_print.print(ss);
        if (ss.str() != "[]")
            std::cerr << "**** error printing empty list.\n";

        to_print.push_front("the last one");
        ss.str("");  // clear the stringstream content

        to_print.print(ss);
        if (ss.str() != "[(1000, \"the last one\")]")
            std::cerr << "**** error printing one element list.\n";

        to_print.push_front("the middle one");
        ss.str("");

        to_print.print(ss);
        if (ss.str() != "[(999, \"the middle one\"), (1000, \"the last one\")]")
            std::cerr << "**** error printing two element list.\n";

        to_print.push_front("the first one");
        ss.str("");

        to_print.print(ss);
        if (ss.str() != "[(998, \"the first one\"), (999, \"the middle one\"), (1000, \"the last one\")]")
            std::cerr << "**** error printing three element list.\n";
    }

#endif // TEST_STAGE

#if TEST_STAGE > 4

    {
        std::cerr << "test assignment operator (operator=)\n";
        std::stringstream ss;

        prioritylist source;
        source.insert("666", 666);

        {
            prioritylist assigned;
            assigned = source;

            assigned.print(ss);
            if (ss.str() != "[(666, \"666\")]")
                std::cerr << "**** error in one element list assignment.\n";
        }

        ss.str("");
        source.print(ss);
        if (ss.str() != "[(666, \"666\")]")
            std::cerr << "**** error in source after one element list assignment.\n";
        ss.str("");

        {
            prioritylist assigned;
            assigned.insert("999", 999);
            assigned = source;

            assigned.print(ss);
            if (ss.str() != "[(666, \"666\")]")
                std::cerr << "**** error in one-element list assignment (2).\n";
        }
        ss.str("");

        source.insert("333", 333);
        {
            prioritylist assigned;
            assigned = source;

            assigned.print(ss);
            if (ss.str() != "[(333, \"333\"), (666, \"666\")]")
                std::cerr << "**** error in two-element list assignment.\n";
        }
        ss.str("");

        source.insert("999", 999);
        {
            prioritylist assigned;
            assigned.push_front("3");
            assigned.push_front("2");
            assigned.push_front("1");

            assigned = source;

            assigned.print(ss);
            if (ss.str() != "[(333, \"333\"), (666, \"666\"), (999, \"999\")]")
                std::cerr << "**** error in three-element list assignment.\n";
        }
        ss.str("");

        // this is really insert test
        source.insert("665", 666);
        {
            prioritylist assigned;
            assigned = source;

            assigned.print(ss);
            if (ss.str() != "[(333, \"333\"), (666, \"665\"), (666, \"666\"), (999, \"999\")]")
                std::cerr << "**** error in four-element list assignment (or in insert).\n";
        }
        ss.str("");

        // the weird assignment
        source = source;
        source.print(ss);
        if (ss.str() != "[(333, \"333\"), (666, \"665\"), (666, \"666\"), (999, \"999\")]")
            std::cerr << "**** error in auto-assignment.\n";

    }

#endif // TEST_STAGE

#if TEST_STAGE > 5

    {
        std::cerr << "test copy constructor\n";
        std::stringstream ss;

        prioritylist source;
        source.insert("666", 666);
        source.insert("333", 333);
        source.insert("999", 999);
        source.insert("665", 666);
        source.print(ss);
        if (ss.str() != "[(333, \"333\"), (666, \"665\"), (666, \"666\"), (999, \"999\")]")
            std::cerr << "**** error in source before copy.\n";
        ss.str("");
        {
            prioritylist copied(source);

            copied.print(ss);
            if (ss.str() != "[(333, \"333\"), (666, \"665\"), (666, \"666\"), (999, \"999\")]")
                std::cerr << "**** error in four-element list assignment (or in insert).\n";
        }
        ss.str("");
    }

#endif // TEST_STAGE

    std::cerr << "End of tests.\n";
    return 0;
}
