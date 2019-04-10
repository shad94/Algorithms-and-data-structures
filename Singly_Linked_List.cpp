#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;


template <typename Key, typename Info>
class Sequence
{
    struct Node{
        Key key;
        Info info;
        Node *next;
    };

    Node *head = NULL;

public:
class iterator{

    Node* el_head;

    public:
    iterator();
    ~iterator();
    iterator operator+(int n);
    void set_iterator(Node *x);
    Key get_key();
    Info get_info();
    bool end();
};

    Sequence();
    ~Sequence();
    bool insertFront (const Key& key, const Info& info);
    bool insertEnd(const Key &key, const Info &info);
	void popBack();
	void popFront();
    Sequence(const Sequence<Key,Info> &x);
    bool insertAfter(const Key &kNew, const Info &iNew, const Key &kWhere, int which = 1);
    bool remove_el(const Key &kOld, int which = 1);
    bool find_el(const Key &k, Node *&curr, Node *&previous);
    friend ostream& operator << (ostream &o, const Sequence<Key, Info> &S){S.print(); return o;};
    Sequence<Key, Info> &operator = (const Sequence<Key, Info> &S);
    Sequence<Key, Info> &operator + (const Sequence<Key, Info> &S);
    Sequence<Key, Info> &operator - (const Sequence<Key, Info> &S);
    void print()const;
    bool ifExist(const Key &k);
    bool isEmpty();
    int length()const;
    Key getKey(int pos)const;
    Info getInfo(int pos)const;
    iterator begin();
    Key get_key(iterator &x);
    Info get_info(iterator &x);
    bool end(iterator &p);
};

template <typename Key, typename Info>
bool Sequence<Key, Info>::insertFront(const Key& key, const Info& info) {

	Node* nextNode = head;

	head = new Node();
	head->key = key;
	head->info = info;
	head->next = nextNode;
	return true;
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::insertEnd(const Key &key, const Info &info)
{
    Node *curr = head;
    if(curr == NULL) // sequence is empty
    {
        Node *el_new = new Node;
        el_new->key = key;
        el_new->info = info;
        el_new->next = NULL;
        head = el_new; // inser first Node
        return true;
    }
    while(curr) //iterate to the end of the sequence
    {
        if(curr->next == NULL)   // stop at the last Node
        {
            Node *el_new = new Node;
            el_new->key = key;
            el_new->info = info;
            el_new->next = NULL;
            curr->next = el_new;
            return true;
        }
        curr = curr->next;
    }
    return false;
}

template <typename Key, typename Info>
void Sequence<Key, Info>::popBack() {

	if (head->next == NULL) {
    delete head;
    head = NULL;
}
else {
    Node *nextToEnd = head;
    Node *end = head->next;
    while (end->next != NULL) {
        nextToEnd = end;
        end = end->next;
    }
    delete end;
    nextToEnd->next = NULL;
}}

template <typename Key, typename Info>
void Sequence<Key, Info>::popFront() {
if(head)
{
Node *tmp=head;
head=head->next;
delete tmp;}
}

template <typename Key, typename Info>
Key Sequence<Key, Info>::getKey(int pos)const
{
    Node *curr = head;
    int i = 1;
    while((curr) && (i < pos))
    {
        i++;
        curr = curr->next;

    }
    if(curr)
    {
        return curr->key;
    }
    cout << "no Node with such a key, returns 1st Node: ";
    return head->key;
}

template <typename Key, typename Info>
Info Sequence<Key, Info>::getInfo(int pos)const
{
    Node *curr = head;
    int i = 1;
    while((curr) && (i < pos))
    {
        i++;
        curr = curr->next;

    }
    if(curr)
    {
        return curr->info;
    }
    cout << "no Node with such a key, returns 1st Node: ";
    return head->info;


}

template <typename Key, typename Info>
bool Sequence<Key, Info>::ifExist(const Key &k)
{
    Node *curr = head;
    if(head == NULL)
    {
        cout << "The key does not exist" << endl;
        return false;
    }
    while(curr)
    {
        if(curr->key == k)
        {
            cout << "The key exists" << endl;
            return true;
        }
        curr = curr->next;
    }
    cout << "The key does not exist" << endl;
    return false;
}

template <typename Key, typename Info>
int Sequence<Key, Info>::length()const
{
    int counter = 0;
    Node *curr = head;
    while(curr)
    {
        counter++;
        curr = curr->next;
    }
    return counter;
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::isEmpty()
{
    if(head == NULL)
    {
        cout << "Empty Sequence" << endl;
        return true;
    }
    cout << "Non-empty Sequence" << endl;
    return false;
}

template <typename Key, typename Info>
Sequence<Key, Info>::Sequence()
{
    this->head = NULL;
    cout << "Empty Sequence created" << endl;
}

template<typename Key, typename Info>
void Sequence<Key, Info>::print()const
{
    Node * curr = head;

    if(curr == NULL)
    {
        cout << "Empty Sequence" << endl;
        return;
    }
    while(curr)
    {
        cout << "\t(" << curr->key <<":"<< curr->info << ")";
        curr = curr->next;
    }
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::remove_el(const Key &kOld, int which)
{
    Node * curr = this->head;
    Node * previous = NULL;
    int counter = 1;
    while(curr)
    {
        if((curr->key == kOld) && (counter == which))
        {
            if(curr == head) // if it is first Node
            {
                head = curr->next;
                delete curr;
                return true;
            }
            else    // if it is other Node
            {
                previous->next = curr->next;
                delete curr;
                return true;
            }
        }
        if(curr->key == kOld)
            counter++;          // counting to the next Node with such Key
        previous = curr;     // go to the next Node
        curr = curr->next;
    }
    return false;
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::find_el(const Key &k, Node *&curr, Node *&previous)
{
    previous = NULL;
    curr = this->head;
    while(curr)
    {
        if(curr->key == k)
            return true;
        previous = curr;
        curr = curr->next;
    }
    return false;
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::insertAfter(const Key &kNew, const Info &iNew, const Key &kWhere, int which)
{
    Node *curr = this->head;
    int counter = 0;

    if(curr == NULL) // insert first Node
    {
        Node *el_new = new Node;
        el_new->key = kNew;
        el_new->info = iNew;
        el_new->next = NULL;
        head = el_new;
        counter ++;
        return true;
    }

    while((curr != NULL)&&(counter < which)) // insert other Node
    {
        if(curr->key == kWhere)
        {
            counter++; // After which Node with such Key should insert new Node - defould = 1
            if(counter == which)
            {
                if(curr->next == NULL) // if it is last Node
                {
                    Node *el_new = new Node;
                    el_new->key = kNew;
                    el_new->info = iNew;
                    el_new->next = NULL;
                    curr->next = el_new;
                    return true;
                }
                else if(curr->next != NULL) // if it is somewhere in the middle of sequence
                {
                    Node *el_new = new Node;
                    el_new->key = kNew;
                    el_new->info = iNew;
                    el_new->next = curr->next;
                    curr->next = el_new;
                    return true;
                }
            }
        }
        curr = curr->next;
    }
    return false;
}

template <typename Key, typename Info>
Sequence<Key, Info>::~Sequence()
{
    Node * curr = NULL;
    while(head)
    {
        curr = head;
        head = head->next;
        delete curr;
    }
    cout << "Sequence deleted (destructed)" << endl;
}

template <typename Key, typename Info>
Sequence<Key, Info>& Sequence<Key, Info>::operator=(const Sequence<Key, Info> &S)
{
    if(this == &S)
    {
        return *this;
    }
   // this->~Sequence();
    Node *curr = S.head; // curr_el of orginal Sequence
    while(curr) // iterate through orginal sequence
    {
        this->insertEnd(curr->key, curr->info);
        curr = curr->next;
    }
    return *this;
}

template <typename Key, typename Info>
Sequence<Key, Info>& Sequence<Key, Info>::operator+(const Sequence<Key, Info> &S)
{
    Node *curr = S.head;
    Node *temp = head;

    if(temp == NULL) // if first sequence is empty -> insert only second sequence
    {
        while(curr)
            {
                this->insertEnd(curr->key, curr->info); // insert whole second sequence
                curr = curr->next;
            }
    }
    while(temp) // if first sequence extists
    {
        if(temp->next == NULL) // iterate to the last Node of first sequence
        {
            while(curr)
            {
                this->insertEnd(curr->key, curr->info); // insert whole second sequence
                curr = curr->next;
            }
        }
        temp = temp->next;
    }
    return *this;
}

template <typename Key, typename Info>
Sequence<Key, Info>& Sequence<Key, Info>::operator-(const Sequence<Key, Info> &S)
{
    Node *curr = S.head;

    while(curr)
    {
        Node *temp = head;
        while(temp)
        {
            //cout << "("<<curr->key<< ","<< curr->info <<") -> ("<<temp->key<< "," << temp->info << ")"<<endl;
            if(curr->key == temp->key)
            {
                //cout <<"[OK]"<<endl;
                this->remove_el(curr->key);
            }
            temp = temp->next;
        }
        curr = curr->next;
    }
    return *this;
}

/***/
template <typename Key, typename Info>
Sequence<Key,Info>::iterator::iterator()
{
 el_head = NULL;
}

template <typename Key, typename Info>
Sequence<Key,Info>::iterator::~iterator()
{
 el_head = NULL;
}

template <typename Key, typename Info>
typename Sequence<Key,Info>::iterator Sequence<Key,Info>::begin()
{
iterator x;
if (head==NULL)
 {
  return x;
 }
x.set_iterator(head);
return iterator(x);
}

template <typename Key, typename Info>
typename Sequence<Key,Info>::iterator Sequence<Key,Info>::iterator::operator+(int n)
{
if (el_head == NULL)
{
 return *this;
}
for (int i=0 ; i < n ; i++)
{
 if (el_head -> next == NULL)
 {
  iterator x;
  x.set_iterator(el_head);
  return x;
 }
 el_head = el_head->next;
}
iterator x;
x.set_iterator(el_head);
return x;
}

template <typename Key, typename Info>
void Sequence<Key,Info>::iterator::set_iterator(Node *x)
{
if (x==NULL)
{
 return;
}
el_head = x;
}

template <typename Key, typename Info>
Key Sequence<Key,Info>::iterator::get_key()
{
Key type;
try
{
if (el_head == NULL)
{
 throw "head==NULL";
}
 return el_head->key;
}

catch (const char* x)
{
 cout<<x<<endl;
 return type;
}
}

template <typename Key, typename Info>
Info Sequence<Key,Info>::iterator::get_info()
{
Info type;
try
{
 if (el_head == NULL)
{
throw "head==NULL";
}
 return el_head->info;
}
catch (const char* x)
{
 cout<<x<<endl;
 return type;
}
}

template <typename Key, typename Info>
Info Sequence<Key,Info>::get_info(iterator &x)
{
 return x.get_info();
}

template <typename Key, typename Info>
Key Sequence<Key,Info>::get_key(iterator &x)
{
 return x.get_key();
}

template <typename Key, typename Info>
bool Sequence<Key,Info>::iterator::end()
{
if
(el_head->next==NULL)
 return 1;
else
 return 0;
}

template <typename Key, typename Info>
bool Sequence<Key,Info>::end(iterator &n)
{
if (n.end())
 return 1;
else
 return 0;
}


template <typename Key, typename Info>
Sequence<Key,Info> produce( Sequence<Key,Info> &s1, int start1, int length1, Sequence<Key,Info> &s2, int start2, int length2, int limit)
{
Sequence<Key,Info> prod;
int k = s1.length();
int l = s2.length();
int m;

if ((k == 0 && l == 0)|limit==0)
{
 return prod;
}


typename Sequence<Key,Info>::iterator q;
typename Sequence<Key,Info>::iterator r;

 q = s1.begin();
 q = q + start1;

 r = s2.begin();
 r = r + start2;

if(length2!=0|| length1!=0 )
while (prod.length() < limit )
{


if(k==0)
{
 for (int j = 0; j < length2 && prod.length() < limit; j++)
 {
  prod.insertEnd(s2.get_key(r), s2.get_info(r));
  if (s2.end(r))
  {
   r = s2.begin();
   continue;
  }
 r = r + 1;
 }

}



if(l==0)
{
  for (int i = 0; i < length1 && prod.length() < limit; i++)
  {
   prod.insertEnd(s1.get_key(q), s1.get_info(q));
   if (s1.end(q))
  {
   q = s1.begin();
   continue;
  }
q = q + 1;
 }

}

//cout<<"zdjjdh"<<endl;
 if (k!= 0 && l!=0)
 {
  for (int i = 0; i < length1 && prod.length() < limit; i++)
  {
   prod.insertEnd(s1.get_key(q), s1.get_info(q));
   if (s1.end(q))
  {
   q = s1.begin();
   continue;
  }
q = q + 1;
 }
 for (int j = 0; j < length2 && prod.length() < limit; j++)
 {
  prod.insertEnd(s2.get_key(r), s2.get_info(r));
  if (s2.end(r))
  {
   r = s2.begin();
   continue;
  }
 r = r + 1;
 }
}


}

return prod;
cout<<endl;

}

int main()
{
    cout << "*Creating initial Sequence" << endl;
    Sequence<int, string> S0;

    S0.insertEnd(1,(char*)"a");
    S0.insertEnd(2,(char*)"b");
    S0.insertEnd(3,(char*)"c");
    S0.insertEnd(1,(char*)"d");
    S0.insertEnd(2,(char*)"e");
    S0.insertEnd(4,(char*)"f");
    S0.insertEnd(5,(char*)"g");
    S0.insertEnd(6,(char*)"i");
    S0.insertEnd(7,(char*)"j");
    S0.insertEnd(30,(char*)"k");
    S0.insertEnd(0,(char*)"l");
    S0.insertEnd(8,(char*)"m");
    S0.insertEnd(9,(char*)"n");
    S0.insertEnd(10,(char*)"o");
    S0.insertEnd(11,(char*)"p");
    S0.insertEnd(50,(char*)"q");

    cout << "Initial Sequence S0: " ;
    S0.print();
    cout<< endl;

    cout<<"\n**************"<<endl;

    cout << "getKey(): for positions 20 and 3" << endl;
    cout << S0.getKey(20) << endl;
    cout << S0.getKey(3) << endl;

    cout<<"\n------------------"<<endl;
    cout << "getInfo(): for positions 0 and 3 " << endl;
    cout << S0.getInfo(0) << endl;
    cout << S0.getInfo(3) << endl;

    cout<<"\n------------------"<<endl;
    cout << "Operator << test: " << endl;
    cout << "S0 <<" << S0 << endl;

    cout<<"\n------------------"<<endl;
    cout << "Constructor: S1" << endl;
    Sequence<int, string> S1;

    cout<<"\n------------------"<<endl;
    cout << "print(): " << endl;
    S1.print();

    cout<<"\n------------------"<<endl;
    cout << "InsertAfter(): " << endl;
    S1.insertAfter(1,(char*)"a",1);
    S1.insertAfter(2,(char*)"b",1);
    S1.insertAfter(3,(char*)"c",2);
    S1.insertAfter(4,(char*)"d",1);
    S1.insertAfter(4,(char*)"e",1);
    S1.insertAfter(4,(char*)"f",1);
    S1.insertAfter(5,(char*)"g",4, 2);
    cout << "S1 =";
    S1.print();

    cout<<"\n------------------"<<endl;
    cout << "remove() Nodes with keys 5 and 3" << endl;
    S1.remove_el(5);
    S1.remove_el(3);
    cout << "S1 =";
    S1.print();
    cout << endl;

    cout<<"\n------------------"<<endl;
    cout << "Destructor: " << endl;
    S1.~Sequence();
    S1.print();

    cout<<"\n------------------"<<endl;
    cout << "Operator = : " << endl;
    cout << "S1 = ";
    S1.insertAfter(1,(char*)"a",1);
    S1.insertAfter(2,(char*)"b",1);
    S1.insertAfter(3,(char*)"c",2);
    S1.insertAfter(4,(char*)"d",1);
    S1.insertAfter(4,(char*)"e",1);
    S1.insertAfter(4,(char*)"f",1);
    S1.insertAfter(5,(char*)"g",4, 2);
    S1.print();
    cout << endl;
    Sequence<int, string> S2;
    cout << "S2 = S1"<<endl;
    S2 = S1;
    cout << "S2 =";
    S2.print();
    cout << endl;

    cout<<"\n------------------"<<endl;
    cout << "isEmpty() for created Sequence S3: " << endl;
    Sequence<int, string> S3;
    S3.print();
    S3.isEmpty();
    S1.isEmpty();

    cout<<"\n------------------"<<endl;
    cout << "length(): " << endl;
    cout << "Size of S1 = "<< S1.length() << endl;
    cout << "Size of S3 = "<< S3.length() << endl;

    cout<<"\n------------------"<<endl;
    cout<<"Printing Sequence S1:"<<endl;
    S1.print();
    cout << endl;
    cout << "ifExist()  in Sequence S1 Nodes with keys 1 and 7: " << endl;
    S1.ifExist(1);
    S1.ifExist(7);
    cout<<"\n------------------"<<endl;
    cout << "insertEnd() to an empty Sequence S3 Nodes 1 a, 2 b, 3 c: " << endl;
    S3.insertEnd(1,(char*)"a");
    S3.insertEnd(2,(char*)"b");
    S3.insertEnd(3,(char*)"c");
    cout << "S3 =";
    S3.print();
    cout << endl;

    cout<<"\n------------------"<<endl;
    cout << "Operator +: " << endl;
    cout<<"Creating Sequence S4: "<<endl;
    Sequence<int, string> S4;
    cout << "S3 + S4" << endl;
    S4 = S3 + S4;
    cout << "S4 =";
    S4.print();
    cout << endl;

    cout<<"\n------------------"<<endl;
    cout << "Operator -: " << endl;
    cout<<"Creating Sequence S5: "<<endl;
    Sequence<int, string> S5;
    cout << "S1 - S3" << endl;
    S1.print();
    cout<<" - ";
    S3.print();
    cout<<endl;
    S5 = S1 - S3;
    cout << "S5 =";
    S5.print();
    cout << endl;

    cout<<"\n------------------"<<endl;
    Sequence<int, string> S10, S11, S20, S21, S22, S23,S24,S30, S31, S32,S33,S34,S40;
    S10.insertEnd(1,(char*)"a");
    S10.insertEnd(2,(char*)"b");
    S10.insertEnd(3,(char*)"c");
    S10.insertEnd(4,(char*)"d");
    S10.insertEnd(3,(char*)"e");
    S10.insertEnd(2,(char*)"b");
    S10.print();
    S40.insertEnd(10,(char*)"f");
    S40.insertEnd(20,(char*)"g");
    S40.insertEnd(30,(char*)"h");
    S40.insertEnd(40,(char*)"i");
    S40.insertEnd(30,(char*)"j");
    S40.insertEnd(20,(char*)"k");
    S40.print();


    cout<<"\nWe are testing function PRODUCE. Description of tests below:\n";
    cout<<"\n1. When limit =0"<<endl;
    cout<<"produce(S10,1,2,S10,1,2,0)"<<endl;
    S11=produce(S10,1,2,S10,1,2,0);
    S11.print();
    cout<<endl;

    cout<<"\n2. When start1 or/and start2 are out of range"<<endl;
    cout<<"produce(S10,6,2,S10,2,2,2)"<<endl;
    S20=produce(S10,6,2,S10,2,2,2);
    S20.print();
    cout<<endl;

    cout<<"\n3. When length1 or/and length2 are out of range"<<endl;
    cout<<"produce(S10,2,7,S10,2,4,2)"<<endl;
    S21=produce(S10,2,7,S10,2,4,2);
    S21.print();
    cout<<endl;

    cout<<"\n4. When length1 or/and length2 are equal 0"<<endl;
    cout<<"produce(S10,2,0,S10,2,0,2)"<<endl;
    S22=produce(S10,2,0,S10,2,0,2);
    S22.print();
    cout<<endl;

    cout<<"\n5. When s1=s2, start1=start2, length1=length2"<<endl;
    cout<<"produce(S10,2,0,S10,2,0,2)"<<endl;
    S23=produce(S10,2,0,S10,2,0,2);
    S23.print();
    cout<<endl;

    cout<<"\n6. When start1 and start2 are zeros, "<<endl;
    cout<<"produce(S10,0,1,S10,0,2,2)"<<endl;
    S24=produce(S10,0,1,S40,0,2,10);
    S24.print();
    cout<<endl;

    cout<<"\n7. When one of the Sequence is empty"<<endl;
    cout<<"produce(S10,2,3,S30,2,3,2)"<<endl;
    S31=produce(S10,2,3,S30,2,3,2);
    S31.print();
    cout<<endl;

    cout<<"\n8. When limit is <= len(s1)+len(s2)"<<endl;
    cout<<"produce(S10,2,3,S40,1,3,5)"<<endl;
    S32=produce(S10,2,3,S40,1,3,5);
    S32.print();
    cout<<endl;

    cout<<"\n9. When limit is >len(s1)+len(s2)"<<endl;
    cout<<"produce(S10,0,6,S40,1,3,5)"<<endl;
    S33=produce(S10,0,6,S40,1,3,5);
    S33.print();
    cout<<endl;

    cout<<"\n10. Unusually big offset"<<endl;
    cout<<"produce(S10,2,3,S40,1,11,5)"<<endl;
    S34=produce(S10,2,3,S40,1,11,5);
    S34.print();
    cout<<endl;

    return 0;
}

