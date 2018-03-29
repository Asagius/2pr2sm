
#ifndef HEADER_H_
#define HEADER_H_

typedef struct Node // Structure
{
    Node *next;
    Node *prev;
    int value; // Data
    Node() {}

    /*Node(Node &second_element) {
        next = NULL;
        prev = &second_element;
        value = second_element.value;
    }*/
} Node;

class List {
public:
    List();

    List(int n);

    ~List();

    List(const List &);

    List &operator=(const List &);

    List operator+(const List &) const;

    List operator-(const List &) const;

    bool operator==(const List &) const;

    bool operator!=(const List &) const;

    bool operator>(const List &) const;

    bool operator<(const List &) const;

    bool operator<=(const List &) const;

    bool operator>=(const List &) const;

    void show() const;

    int getsize() const;

    int get();

    int get(int);

    void add(int, int);

    void add_after(int, int);

    void add_first(int);

    void add_last(int);

    void del_all();

    void del();

    void del(int);

    void del(int, int);

    void del_first();

    void del_repeat();

    bool check(std::vector<int> &, int); // search copies

private:
    Node *head;
    Node *tail;
    int size;
};

#endif
