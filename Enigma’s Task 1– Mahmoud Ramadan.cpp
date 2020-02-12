
#include <iostream>

using namespace std;

template <class T>
class LinkedList
{

    class Node
    {
    public:
        T value;
        Node* next;
        Node* previous;

        // constructor
        // v : the value node will hold
        // nextNode: pointer to the next node if exist
        // PrevNode: pointer to the Previous node if exist
        Node(T v, Node* nextNode, Node* prevNode)
        {
            // initialize data members
            value = v;
            next = nextNode;
            previous = prevNode;

            // make the next and the previous nodes point to this node
            if(nextNode)
                nextNode->previous = this;
            if(prevNode)
                prevNode->next = this;
        }

        // destructor
        // make sure that structure of linked list is not broken
        // by make node point to the correct next and previous node
        // after delete this node
        ~Node()
        {
            if(next)
                next->previous = this->previous;
            if(previous)
                previous->next = this->next;
        }

        // switch next and previous
        void switchNextPrev()
        {
            Node* temp = next;
            next = previous;
            previous = temp;
        }
    };
    // head point to the first node in the linked list
    // tail point to the last node in the linked list
    Node  *head, *tail;
    int size;

    // index: represent number of the node started from 0
    // return pointer to the node at the specific index
    // throw exception if index is invalid
    Node* getNodeByIndex(int index)
    {
        if(!head || index < 0 || index >= size)
            throw "invalid index";

        Node* wantedNode;
        // select from which point to start search head or tail
        if(index < size / 2)
            for(wantedNode = head; index; wantedNode = wantedNode->next, index--);
        else
            for(wantedNode = tail; index; wantedNode = wantedNode->previous, index--);

        return wantedNode;
    }

    // query: the value that we search for
    // return: pointer to the first node that hold the same value as query
    //         or null if no match
    Node* getNodeByValue(T query)
    {
        Node* wantedNode = head;
        for(; wantedNode && wantedNode->value != query; wantedNode = wantedNode->next);
        return wantedNode;
    }

    // switch head and tail
    void switchHeadTail ()
    {
        Node* temp = head;
        head = tail;
        tail = temp;
    }


public:

    // constructor
    LinkedList()
    {
        head = tail = NULL;
        size = 0;
    }

    bool isEmpty()
    {
        return !head;
    }

    int getSize()
    {
        return size;
    }

    // return value in the first Node
    // or throw exception if linked list empty
    T first()
    {
        if(isEmpty())
            throw "empty linked list";
        return head->value;
    }

    // return value in the last Node
    // or throw exception if linked list empty
    T last()
    {
        if(isEmpty())
            throw "empty linked list";
        return tail->value;
    }
    // return value in the specific index
    T at(int index)
    {
        return getNodeByIndex(index)->value;
    }

    // add node at the first of linked list
    // value: the data new node will hold
    void addFirst(T value)
    {
        if(isEmpty())
        {
            head = tail = new Node(value, NULL, NULL);
        }
        else
        {
            new Node(value, head, NULL);
            head = head->previous;
        }
        size++;
    }

    // add node at the end
    // value: the data new node will hold
    void addLast(T value)
    {
        if(isEmpty())
        {
            head = tail = new Node(value, NULL, NULL);
        }
        else
        {
            new Node(value, NULL, tail);
            tail = tail->next;
        }
        size++;
    }

    // add new element at specific position
    // index: position of new node start from zero
    // value: data new node will hold
    // return: true if inserted
    //         or false if not
    bool insert(int index, T value)
    {
        if((!head && index != 0) || index < 0 || index > size)
            return false;

        if(index == 0)
        {
            addFirst(value);
            return true;
        }
        else if(index == size)
        {
            addLast(value);
            return true;
        }

        Node* previousNode = getNodeByIndex(index - 1);
        new Node(value, previousNode->next, previousNode);

        size++;

        return true;
    }

    // check if linked list contain element or not
    bool contains(T element)
    {
        return getNodeByValue(element);
    }


    // element: the data we want to find
    // return: first position
    //         that contain data matches element
    //         or -1 if no node contain element
    int indexOf(T element)
    {
        Node* currentNode = head;
        for(int i = 0; currentNode; currentNode = currentNode->next, i++)
            if(currentNode->value == element)
                return i;
        return -1;
    }

    // remove the first node in linked list
    // return the data where hold by the first node
    // throw exception if linked list empty
    T removeFirst()
    {
        if(isEmpty())
            throw "no element to remove empty LinkedList";

        T firstNodeValue = head->value;

        if(head == tail)
        {
            delete head;
            head = tail = NULL;
        }
        else
        {
            head = head->next;
            delete head->previous;
        }

        size--;

        return firstNodeValue;
    }

    // remove the last node in linked list
    // return the data where hold by the last node
    // throw exception if linked list empty
    T removeLast()
    {
        if(!head)
            throw "no element to remove empty LinkedList";

        T lastNodeValue = tail->value;

        if(head == tail)
        {
            delete tail;
            head = tail = NULL;
        }
        else
        {
            tail = tail->previous;
            delete tail->next;
            //tail->next  = NULL;
        }

        size--;

        return lastNodeValue;
    }

    // element: the data we want to delete
    // delete first node contain data equal to element
    // return: true if deleted
    //        false if not
    bool remove(T element)
    {
        Node* selectedNode = getNodeByValue(element);

        if(!selectedNode)
            return false;

        delete selectedNode;

        if(head == tail)
            head = tail = NULL;

        size--;

        return true;
    }

    // index: position of node start from 0
    // element: new data the node will hold
    // change data in node at specific index
    // to element
    // return: true if changed
    //         false if not
    bool update(int index, T element)
    {
        try
        {
            getNodeByIndex(index)->value = element;
            return true;
        }
        catch(const char* msg)
        {
            return false;
        }
    }

    void reverse()
    {
        // switch head and tail of linked list
        switchHeadTail();

        // loop over each node and switch next and previous
        for(Node* i = head; i; i->switchNextPrev(), i = i->next);
    }

    // delete all nodes in linked list
    void clear()
    {
        for(Node* t; head;)
        {
            t = head;
            head = head->next;
            delete t;
        }

        head = tail = NULL;
        size = 0;
    }

    ~LinkedList ()
    {
        clear();
    }


    void print()
    {
        Node *temp = head;
        std::cout << "value \t address \t next \t\t previous" << std::endl;
        while(temp != 0)
        {
            std::cout << temp->value << "\t"
                      << temp << "\t"
                      << temp->next << "\t"
                      << temp->previous << std::endl << std::endl;
            temp = temp->next;
        }
    }



};

