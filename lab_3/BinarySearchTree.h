#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <algorithm>
using namespace std;

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinarySearchTree
{
    
public:
    BinarySearchTree( ) : root{ nullptr }
    {
    }
    
    /**
     * Copy constructor
     */
    BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }
    
    /**
     * Move constructor
     */
    BinarySearchTree( BinarySearchTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
    
    /**
     * Destructor for the tree
     */
    ~BinarySearchTree( )
    {
        makeEmpty( );
    }
    
    /**
     * Copy assignment
     */
    BinarySearchTree & operator=( const BinarySearchTree & rhs )
    {
        BinarySearchTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
    
    /**
     * Move assignment
     */
    BinarySearchTree & operator=( BinarySearchTree && rhs )
    {
        std::swap( root, rhs.root );
        return *this;
    }
    
    /**
     find_pred_succ, given a value x returns a and b
     such that a is the predecc. of x and b is the succ. of x.
     **/
    
    void find_pred_succ(const Comparable& x, Comparable& pred, Comparable& suc) const {
        
        BinaryNode * tmp = this->root;
        
        
        while (tmp != nullptr)
        {
            
            if (tmp->element == x)
            {
                BinaryNode * pre = find_predecessor(tmp);
                BinaryNode * su = find_successor(tmp);
                
                if (pre != nullptr) pred = pre->element;
                
                if (su != nullptr) suc = su->element;
                
                return;
                
            }
            
            else if (tmp->element > x) {
                suc = tmp->element;
                tmp = tmp->left;
            }
            
            else { //(temp->element < x)
                pred = tmp->element;
                tmp = tmp->right;
            }
        }
        
        
        
    }
    
    
    
    
    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }
    
    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }
    
    
    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }
    
    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ostream & out = cout ) const
    {
        int indent = 0;
        
        if( isEmpty( ) )
            out << "Empty tree" << endl;
        else {
            preOrder( root, out, indent);
        }
        
    }
    
    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }
    
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        insert( x, root );
    }
    
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x )
    {
        insert( std::move( x ), root );
    }
    
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const Comparable & x )
    {
        remove( x, root );
    }
    
    Comparable get_parent(const Comparable & x )
    {
        if (!contains(x))
            return Comparable();
        
        BinaryNode* temp = root;
        
        if(temp->element == x)
            return Comparable();
        
        while(temp != nullptr) {
            
            if (temp->element == x)
            {
                return temp->parent->element; //fel på parent
                
            }
            
            else if(temp->element > x){
                temp = temp->left;
            }
            else //(temp->element < x)
            {
                temp = temp->right;
            }
            
        }
        return Comparable();
        
        
    }
    
    

    
private:
    
    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;
        BinaryNode *parent; //J&E
        
        BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt, BinaryNode *par )
        : element{ theElement }, left{ lt }, right{ rt }, parent{ par } { }
        
        BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt, BinaryNode *par )
        : element{ std::move( theElement ) }, left{ lt }, right{ rt }, parent{ par } { }
    };
    
    BinaryNode *root;

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, BinaryNode * & t )
    {
        if( t == nullptr )
            t = new BinaryNode{ x, nullptr, nullptr, nullptr};
        else if( x < t->element ){
            insert( x, t->left );
            t->left->parent = t;
        }
        else if( t->element < x ){
            insert( x, t->right );
            t->right->parent = t;
            
        }
        else
        {
            ;  // Duplicate; do nothing
        }
    }
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, BinaryNode * & t )
    {
        if( t == nullptr )
            t = new BinaryNode{ std::move( x ), nullptr, nullptr, nullptr};
        else if( x < t->element ){
            insert( std::move( x ), t->left );
            t->left->parent = t;
        }
        else if( t->element < x ){
            insert( std::move( x ), t->right );
            t->right->parent = t;
            
        }
        else
        {
            ;  // Duplicate; do nothing
        }
    }
    
    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
void remove( const Comparable & x, BinaryNode * & t )
{
        if( t == nullptr ) // Item not found; do nothing
            return;   
        if( x < t->element ) //Item is smaller than t
            remove( x, t->left );
        else if( t->element < x ) //Item is bigger than t
            remove( x, t->right );
       
		else { //item found

                /* ITEM HAS TWO CHILDREN */
				if (t->right != nullptr && t->left != nullptr)
				{
					BinaryNode* tmp = findMin(t->right); //make tmp point to the "replacer"

                       /* Methods to release the tmpnode */

                        //If tmp has right child (cannot have left child since findMin found the leftmost child)
						if (tmp->right != nullptr)
						{
							tmp->right->parent = tmp->parent;

                            //if tmp is right or left child to its parent
							if (tmp->parent->right == tmp) {
								tmp->parent->right = tmp->right;
							}
							else
								tmp->parent->left = tmp->right;
                            
						}

						else // If tmp right is nullptr
						{
							if(tmp->parent->right == tmp) //tmp is right child
								tmp->parent->right = nullptr;

							else// (tmp->parent->left == tmp)
								tmp->parent->left = nullptr;

							t->left->parent = tmp;
						}
				 

					//change tmps pointers
					tmp->parent = t->parent;
					tmp->right = t->right;
					tmp->left = t->left;

                    //redirect pointers to tmp
                    if(t->left != tmp && t->left!=nullptr)
                    t->left->parent = tmp;
                    
                    if(t->right != tmp && t->right!=nullptr)
                        t->right->parent = tmp;

                    //free memory
                    BinaryNode* toDeleate = t;
					t = tmp;
                    delete toDeleate;


				}

            /* ITEM HAS RIGHT CHILD */
			else if(t->right != nullptr && t->left == nullptr)
			{
                    //om t är left child till parent
					if (t->parent->left == t)
					{
						//BinaryNode* toDeleate = t;
                        
                        t->right->parent = t->parent;
						t->parent->left = t->right;
						delete t;
					}

                    //om t är right child till parent
					else if (t->parent->right == t)
					{
                        t->right->parent = t->parent;
						t->parent->right = t->right;
						delete t;
					}

			}

            /* ITEM HAS LEFT CHILD */
            else if (t->right == nullptr && t->left != nullptr)
			{
                //om t är left child till parent
				if (t->parent->left == t)
				{
                    t->left->parent = t->parent;
                    t->parent->left = t->left;
					delete t;
				}

                //om t är right child till parent
				else if (t->parent->right == t)
				{
                    t->left->parent = t->parent;
                    t->parent->right = t->left;
					delete t;
				}

			}

            /* ITEM HAS NO CHILDREN */
			else
			{
				//If t is left child to its parent
				if (t->parent->left == t)
				{
                    t->parent->left = nullptr;
					delete t;
				}

                //if t is right child to its parent
				else if (t->parent->right == t)
				{
                    t->parent->right = nullptr;
					delete t;
				}
			}

		}
}
    
    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    static BinaryNode * findMin( BinaryNode *t )
    {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }
    
    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    static BinaryNode * findMax( BinaryNode *t )
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }
    
    
    
    
    /****** NONRECURSIVE VERSION*************************
     bool contains( const Comparable & x, BinaryNode *t ) const
     {
     while( t != nullptr )
     if( x < t->element )
     t = t->left;
     else if( t->element < x )
     t = t->right;
     else
     return true;    // Match
     
     return false;   // No match
     }
     *****************************************************/
    
    /**
     * Internal method to make subtree empty.
     */
    //called from destructor
    void makeEmpty( BinaryNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }
    
    /**
     * Internal method to print a subtree rooted at t in sorted order.
     * In-order traversal is used
     */
    void printTree( BinaryNode *t, ostream & out ) const
    {
        if( t != nullptr )
        {
            printTree( t->left, out );
            out << t->element << endl;
            printTree( t->right, out );
        }
    }

    //method to print a subtree rooted at t in sorted order:
    //Pre-order traversal is used
    void preOrder(BinaryNode *n, ostream & out, int indent) const
    {
        if(n != nullptr)
        {
            for(int i=0; i< indent; i++){
                out << "\t";
            }
            out << n->element << endl;
            
            preOrder(n->left, out, indent+1);
            preOrder(n->right, out, indent+1);
        }

    }
    
    /**
     * Internal method to clone subtree.
     */
    BinaryNode * clone( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else {
            auto newNode = new BinaryNode{ t->element, clone(t->left), clone(t->right), nullptr };
            
            if(newNode->left)
                newNode->left->parent = newNode;
            if (newNode->right)
                newNode->right->parent = newNode;
            
            return newNode;
        }
    }
    
public:
    
    /**
     Method to find successor: returns a pointer to the node storing the successor (after) of the value stored in given node.
     If successor doesn't exist return nullptr **/
    static BinaryNode * find_successor(BinaryNode* t) {
        
        if (t == nullptr && !t->right) return nullptr;
        
        if (t->right)
            return findMin(t->right);
        
        while (t->parent != nullptr && t->parent->left != t) {
            t = t->parent;
        }
        
        return t->parent;
    }
    
    
    /**
     Method to find predecessor: returns a pointer to the node storing the predecessor (before) of the value stored in given node.
     If predecessor doesn't exist return nullptr **/
    static BinaryNode * find_predecessor(BinaryNode* t)  {
        
        
        if (t == nullptr && !t->left) return nullptr;
        
        if (t->left)
            return findMax(t->left);
        
        while (t->parent != nullptr && t->parent->right != t ) {
            t = t->parent;
        }
        
        return t->parent;
    }
    
    
    /*  BIITERATOR CLASS    */

    class BiIterator {
    public:
        BiIterator()
        : current(nullptr) {}
        
        BiIterator(BinaryNode* p)
        : current(p) {}
        
        
        Comparable& operator*() const {
            return current->element;
        }
        
        Comparable* operator->() const {
            return &(current->element);
        }
    
        bool operator==(const BiIterator &it) const{
            return current == it.current;
        }
        
        bool operator!=(const BiIterator &it) const{
            return current != it.current;
        }
        
        BiIterator& operator++() {
            current = find_successor(current);
            return *this;
            
        }
        
        
        BiIterator& operator--() {
            current = find_predecessor(current);
            return *this;
        }
        
        
    private:
        BinaryNode *current;
    };
    
    
    BiIterator begin() const {
        if(isEmpty()) return end();

        return BiIterator(findMin(root));
    };
    
    BiIterator end() const {
        
        return BiIterator();
    };
    /**
     * Returns true if x is found in the tree.
     */
    BiIterator contains( const Comparable & x ) const
    {
        return contains( x, root );
    }

    /*
	bool contains(const Comparable & x) const {
		return contains(x, root);
	}*/

    
    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     */
    /*bool contains( const Comparable & x, BinaryNode *t ) const
     {
     if( t == nullptr )
     return false;
     else if( x < t->element )
     return contains( x, t->left );
     else if( t->element < x )
     return contains( x, t->right );
     else
     return true;    // Match
     }*/
    
    
   BiIterator contains( const Comparable & x, BinaryNode *t ) const
    {
        if( t == nullptr )
            return BiIterator(nullptr);
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return BiIterator(t);
    }
    
};


#endif
