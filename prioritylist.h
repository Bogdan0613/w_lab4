#ifndef SLLIST_H_INCLUDED
#define SLLIST_H_INCLUDED
#include <iostream>

// Rajmund Kozuszek (121528)

class prioritylist
{
public:
    class pl_node
    {
        int priority;
        char *name;
        pl_node *next;

        pl_node(const char* name, int prior, pl_node* pnext);
        ~pl_node();

        friend class prioritylist;
    public:
        int get_priority() const;
        const char* get_name() const;
        const pl_node* get_next() const;
    };

    // start of interface
    prioritylist() = default;

    bool is_empty() const;
    int size() const;
    const pl_node* get_first() const;

    void push_front(const char* name);
    void pop_front();

    void insert(const char* name, int priority);
    bool remove(const char* name);
    ~prioritylist();

    void print(std::ostream& os) const;
    prioritylist& operator=(const prioritylist& other);
    prioritylist(const prioritylist& other);


    // end of interface

private:
    pl_node* pl_head = nullptr;
};

extern const int default_priority;


#endif // SLLIST_H_INCLUDED
