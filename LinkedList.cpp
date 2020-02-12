
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
        
        
        Node(T value, Node* nextNode, Node* prevNode)
        {
            this.value = value;
            next = nextNode;
            previous = prevNode;

            if(nextNode)
                nextNode->previous = this;
            if(prevNode)
                prevNode->next = this;
        }


        // make sure that structure of linked list is not broken
        // after delete this node
        ~Node()
        {
            if(next)
                next->previous = this->previous;
            if(previous)
                previous->next = this->next;
        }

        
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

    Node* getNodeByValue(T query)
    {
        Node* wantedNode = head;
        for(; wantedNode && wantedNode->value != query; wantedNode = wantedNode->next);
        return wantedNode;
    }


    void switchHeadTail ()
    {
        Node* temp = head;
        head = tail;
        tail = temp;
    }


public:

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


    T first()
    {
        if(isEmpty())
            throw "empty linked list";
        return head->value;
    }


    T last()
    {
        if(isEmpty())
            throw "empty linked list";
        return tail->value;
    }

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


    bool contains(T element)
    {
        return getNodeByValue(element);
    }


   
    int indexOf(T element)
    {
        Node* currentNode = head;
        for(int i = 0; currentNode; currentNode = currentNode->next, i++)
            if(currentNode->value == element)
                return i;
        return -1;
    }

    // remove the last node in linked list and return the value
    T removeFirst()
    {
        if(isEmpty())
            throw "empty LinkedList";

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

    // remove the last node in linked list and return the value
    T removeLast()
    {
        if(!head)
            throw "Empty LinkedList";

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
        }

        size--;

        return lastNodeValue;
    }


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
        switchHeadTail();

        // loop over each node and switch next and previous
        for(Node* i = head; i; i->switchNextPrev(), i = i->next);
    }

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

