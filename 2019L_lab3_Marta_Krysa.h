#include <iostream>
#include <iomanip>

template <typename keyType, typename dataType>
class AVLTree
{
      class Node
      {
      public:
             keyType key;
             dataType data;
             short int balanceFactor;
             Node * left;
             Node * right;

             Node(const keyType & newKey, const dataType & newData) : key(newKey), data(newData), balanceFactor(0), left(NULL), right(NULL) {};
      };
//      typedef Node * NodePtr;
      Node * Root;

      void insert(AVLTree<keyType, dataType>::Node* & subtreeRoot,  const keyType & newKey, const dataType & newData);
      void clear(AVLTree<keyType, dataType>::Node* & subtreeRoot);
      void graph(AVLTree<keyType, dataType>::Node* const & subtreeRoot, int indent) const;

      int max(int a, int b);
      int set_factors(AVLTree<keyType, dataType>::Node* const & subtreeRoot);
      void Lrotation(AVLTree<keyType, dataType>::Node* ptr);
      void Rrotation(AVLTree<keyType, dataType>::Node* ptr);

      Node* copy (AVLTree<keyType, dataType>::Node* & lhsRoot, AVLTree<keyType, dataType>::Node* const & rhsRoot);
      bool compare (AVLTree<keyType, dataType>::Node* const & lhsRoot, AVLTree<keyType, dataType>::Node* const & rhsRoot) const;
 public:
      AVLTree() : Root(NULL) {};
      AVLTree(const AVLTree<keyType, dataType> & original) : Root(NULL) {*this = original;};
      ~AVLTree() {clear();};

      const AVLTree<keyType, dataType> & operator= (const AVLTree<keyType, dataType> & rhs);
      bool operator== (const AVLTree<keyType, dataType> & rhs) const;
      bool operator!= (const AVLTree<keyType, dataType> & rhs) const {return !(*this == rhs);};

      bool empty() const {return (Root == NULL);};

      void insert(const keyType & newKey, const dataType & newData) {insert(Root, newKey, newData);};
      void remove(const keyType & removeKey);
      void clear() {clear(Root); Root = NULL;};

      void search(const keyType & findKey) const;
      void graph() const {graph(Root, 0);};
};

template <typename keyType, typename dataType>
const AVLTree<keyType, dataType> & AVLTree<keyType, dataType>::operator= (const AVLTree<keyType, dataType> & rhs)
{
      if (this->Root == rhs.Root) // assignment to the same object
         return *this;

      clear();  // prepare object by removing all elements

      if (rhs.empty())     // alredy done becasuse lhs and rhs are empty
         return *this;

      this->Root = copy(this->Root, rhs.Root);
      return *this;
}

template <typename keyType, typename dataType>
bool AVLTree<keyType, dataType>::operator== (const AVLTree<keyType, dataType> & rhs) const
{
     return compare(this->Root, rhs.Root);
}

template <typename keyType, typename dataType>
typename AVLTree<keyType, dataType>::Node* AVLTree<keyType, dataType>::copy (AVLTree<keyType, dataType>::Node* & lhsRoot, AVLTree<keyType, dataType>::Node* const & rhsRoot)
{
      if (rhsRoot == NULL)
         return NULL;

      lhsRoot = new Node(rhsRoot->key, rhsRoot->data);
      lhsRoot->left = copy(lhsRoot->left, rhsRoot->left);
      lhsRoot->right = copy(lhsRoot->right, rhsRoot->right);
      return lhsRoot;
}
template <typename keyType, typename dataType>
bool AVLTree<keyType, dataType>::compare (AVLTree<keyType, dataType>::Node* const & lhsRoot, AVLTree<keyType, dataType>::Node* const & rhsRoot) const
{
     if (lhsRoot == NULL && rhsRoot == NULL)
        return true;
     else if (lhsRoot == NULL || rhsRoot == NULL)
        return false;
     else if (!compare(lhsRoot->left, rhsRoot->left) || !compare(lhsRoot->right, rhsRoot->right))
        return false;
     else if (lhsRoot->key != rhsRoot->key)
        return false;
     else if (lhsRoot->data != rhsRoot->data)
        return false;
     else
        return true;
}

template <typename keyType, typename dataType>
void AVLTree<keyType, dataType>::insert(AVLTree<keyType, dataType>::Node* & subtreeRoot, const keyType & newKey, const dataType & newData)
{
     if (subtreeRoot == NULL) {
        subtreeRoot = new Node(newKey, newData);
        std::cout << "\"" << subtreeRoot->key << "\" added\n";
        set_factors(Root);
     }
     else if (newKey < subtreeRoot->key)
        insert(subtreeRoot->left, newKey, newData);
     else if (newKey > subtreeRoot->key)
        insert(subtreeRoot->right, newKey, newData);
     else
         {std::cout << "\"" << newKey << "\" ALREADY IN THE LIST. KEY MUST BE UNIQUE.\n";
         remove(newKey);}
}

template <typename keyType, typename dataType>
void AVLTree<keyType, dataType>::search(const keyType & findKey) const
{
     Node * ptr = Root;
     bool found = false;

     while (!found && ptr != NULL) {
           if (findKey < ptr->key)
              ptr = ptr->left;
           else if (findKey > ptr->key)
              ptr = ptr->right;
           else
               found = true;
     }
     if (found)
        std::cout << ptr->key << " - " << ptr->data << std::endl;
     else
     std::cout << "\"" << findKey << "\" not found\n";
}

template <typename keyType, typename dataType>
void AVLTree<keyType, dataType>::remove(const keyType & removeKey)
{
     bool found = false;
     Node * del_ptr = Root;
     Node * del_parent = NULL;

     while (!found && del_ptr != NULL) {      // find element with key
           if (removeKey < del_ptr->key) {
              del_parent = del_ptr;
              del_ptr = del_ptr->left;
           }
           else if (removeKey > del_ptr->key) {
              del_parent = del_ptr;
              del_ptr = del_ptr->right;
           }
           else
               found = true;
     }

     if (!found)
        return;

     if (del_ptr->left != NULL && del_ptr->right != NULL) { // 2 children
        Node * succ_ptr = del_ptr->right;
        del_parent = del_ptr;
        while (succ_ptr->left != NULL) {
              del_parent = succ_ptr;
              succ_ptr = succ_ptr->left;
        }
        del_ptr->key = succ_ptr->key;
        del_ptr = succ_ptr;
     }

     Node * subtree = del_ptr->left;    // 0 or 1 child
     if (subtree == NULL)
        subtree = del_ptr->right;
     if (del_parent == NULL)
        Root = subtree;
     else if (del_parent->left == del_ptr)
        del_parent->left = subtree;
     else
        del_parent->right = subtree;

     delete del_ptr;
     set_factors(Root);
}

template <typename keyType, typename dataType>
void AVLTree<keyType, dataType>::clear(AVLTree<keyType, dataType>::Node* & subtreeRoot)
{
     if (subtreeRoot == NULL)
        return;

     clear(subtreeRoot->left);
     clear(subtreeRoot->right);
     delete subtreeRoot;
}

template <typename keyType, typename dataType>
void AVLTree<keyType, dataType>::graph(AVLTree<keyType, dataType>::Node* const & subtreeRoot, int indent) const
{
     if (subtreeRoot != NULL) {
        graph(subtreeRoot->right, indent + 8);
        std::cout << std::setw(indent) << "[" << subtreeRoot->key << "]"<< "[" << subtreeRoot->data << "]" << "(" <<subtreeRoot->balanceFactor<< ")";
        graph(subtreeRoot->left, indent + 8);
     }
     else
         std::cout << std::setw(indent) << " " <<  std::endl;
}

template <typename keyType, typename dataType>
int AVLTree<keyType, dataType>::max(int a, int b)
{
     if ( a < b )
        return b;
     return a;
}

template <typename keyType, typename dataType>
int AVLTree<keyType, dataType>::set_factors(AVLTree<keyType, dataType>::Node* const & subtreeRoot)
{
     if (subtreeRoot == NULL)
        return 0;

     int hightLeft = set_factors(subtreeRoot->left),
         hightRight = set_factors(subtreeRoot->right);

     subtreeRoot->balanceFactor = hightLeft - hightRight;

     /************   BALANCE   ************/
     if (subtreeRoot->balanceFactor == -2 && subtreeRoot->right->balanceFactor == -1) {
        Lrotation(subtreeRoot);
        return set_factors(subtreeRoot);
     }
     if (subtreeRoot->balanceFactor == 2 && subtreeRoot->left->balanceFactor == 1) {
        Rrotation(subtreeRoot);
        return set_factors(subtreeRoot);
     }
     if (subtreeRoot->balanceFactor == -2 && subtreeRoot->right->balanceFactor == 1) {
        Rrotation(subtreeRoot->right);
        Lrotation(subtreeRoot);
        return set_factors(subtreeRoot);
     }
     if (subtreeRoot->balanceFactor == 2 && subtreeRoot->left->balanceFactor == -1) {
        Lrotation(subtreeRoot->left);
        Rrotation(subtreeRoot);
        return set_factors(subtreeRoot);
     }

     return (max(hightLeft, hightRight) + 1);
}

template <typename keyType, typename dataType>
void AVLTree<keyType, dataType>::Lrotation(AVLTree<keyType, dataType>::Node*  ptr)
{
     if (ptr == Root) {
        Root = ptr->right;
        ptr->right = ptr->right->left;
        Root->left = ptr;
        return;
     }

     Node * prev_ptr = Root;
     while (prev_ptr->right != ptr && prev_ptr->left != ptr) {
           if (ptr->key < prev_ptr->key)
              prev_ptr = prev_ptr->left;
           else if (ptr->key > prev_ptr->key)
              prev_ptr = prev_ptr->right;
     }

     if (prev_ptr->right == ptr)
        prev_ptr->right = ptr->right;
     if (prev_ptr->left == ptr)
        prev_ptr->left = ptr->right;
     Node * temp_ptr = ptr->right->left;
     ptr->right->left = ptr;
     ptr->right = temp_ptr;
}

template <typename keyType, typename dataType>
void AVLTree<keyType, dataType>::Rrotation(AVLTree<keyType, dataType>::Node*  ptr)
{
     if (ptr == Root) {
        Root = ptr->left;
        ptr->left = ptr->left->right;
        Root->right = ptr;
        return;
     }

     Node * prev_ptr = Root;
     while (prev_ptr->right != ptr && prev_ptr->left != ptr) {
           if (ptr->key < prev_ptr->key)
              prev_ptr = prev_ptr->left;
           else if (ptr->key > prev_ptr->key)
              prev_ptr = prev_ptr->right;
     }

     if (prev_ptr->right == ptr)
        prev_ptr->right = ptr->left;
     if (prev_ptr->left == ptr)
        prev_ptr->left = ptr->left;
     Node * temp_ptr = ptr->left->right;
     ptr->left->right = ptr;
     ptr->left = temp_ptr;
}
