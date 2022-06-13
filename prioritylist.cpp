#include "prioritylist.h"
#include <cstring>

const int default_priority = 1000;


prioritylist::pl_node::pl_node(const char* elname, int elprior, pl_node* elnext)
{
    name = new char[strlen(elname) + 1];
    strcpy(name, elname);
    priority = elprior;
    next = elnext;
}

prioritylist::pl_node::~pl_node()
{
    delete [] name;
}

prioritylist::~prioritylist() {
    while (get_first() != nullptr)
        pop_front();
}

int prioritylist::pl_node::get_priority() const
{
    return priority;
}

const char* prioritylist::pl_node::get_name() const
{
    return name;
}

const prioritylist::pl_node* prioritylist::pl_node::get_next() const
{
    return next;
}

bool prioritylist::is_empty() const{
    return pl_head == nullptr;
}

int prioritylist::size() const{
    int counter = 0;
    pl_node* pHead = pl_head;
    while(pHead != nullptr){
        ++counter;
        pHead = pHead->next;
    }
    return counter;
}

const prioritylist::pl_node* prioritylist::get_first() const{
    return pl_head;
}

void prioritylist::push_front(const char* name){
    int front_priority = default_priority;
    if (pl_head != nullptr)
        front_priority = pl_head->priority - 1;
    pl_head = new pl_node(name, front_priority, pl_head);
}

void prioritylist::pop_front(){
    if(pl_head != nullptr){
        pl_node* new_head = pl_head->next;
        delete pl_head;
        pl_head = new_head;
    }
}

void prioritylist::insert(const char* name, int priority){
    pl_node* temp = pl_head;
    pl_node* prev = nullptr;
    while(temp != nullptr){
        if(priority <= temp->priority)
            break;
        prev = temp;
        temp = temp->next;
    }

    pl_node* new_node = new pl_node(name, priority, temp);
    if(prev == nullptr)
        pl_head = new_node;
    else
        prev->next = new_node;
}

bool prioritylist::remove(const char* name){
    pl_node* temp = pl_head;
    pl_node* prev = nullptr;
    while(temp != nullptr){
        if(strcmp(name, temp->name)==0)
            break;
        prev = temp;
        temp = temp->next;
    }

    if(temp == nullptr)
        return 0;

    if(prev == nullptr){
        pl_node* new_head = pl_head->next;
        delete pl_head;
        pl_head = new_head;
    }else{
        prev->next = temp->next;
        delete temp;
    }
    return 1;
}

void prioritylist::print(std::ostream& os) const
{
    pl_node* temp = pl_head;
    os << '[';
    while(temp != nullptr)
    {
        os << '(' << temp->priority << ", \"" << temp->name << "\")";
        temp = temp->next;
        if(temp != nullptr)
            os << ", ";
    }
    os << ']';
}

prioritylist& prioritylist::operator=(const prioritylist& other)
{
    if(this == &other)
        return *this;

    pl_node* node = pl_head;
//    while(node != nullptr)
//    {
//        node = node->next;
//        delete pl_head;
//        pl_head = node;
//    }

    pl_node *temp = other.pl_head;
    while(temp != nullptr)
    {
        pl_node* new_node = new pl_node(temp->name, temp->priority, temp->next);

        if(!pl_head)
            pl_head = new_node;
        else
            node->next = new_node;
        node = new_node;
        temp = temp->next;
    }

    return *this;
}

prioritylist::prioritylist (const prioritylist& other){
//    pl_node* prev = nullptr;
//    pl_node* temp = other.pl_head;
//    while(temp != nullptr){
//        pl_node* new_node = new pl_node(temp->name, temp->priority, temp->next);
//
//        if(!pl_head)
//            pl_head = new_node;
//        else
//            prev->next = new_node;
//
//        prev = new_node;
//        temp = temp->next;
//    }

}
