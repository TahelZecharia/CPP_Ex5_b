#pragma once

#include <iostream>
#include <vector>
#include <string>

namespace ariel{
    
    struct Node{

        std::string _name;
        
        std::vector<Node*> _employees; // List of employees working under this node.
        
        Node* _nextPreorder;        // Pointer to the next employee by 'preorder for the iterator.
        Node* _nextReverseOrder;    // Pointer to the next employee by 'reverse order' for the iterator.
        Node* _nextLevelOrder;       // Pointer to the next employee by 'level order' for the iterator.

        Node(const std::string &name)
			: _name(name), _nextPreorder(nullptr), _nextReverseOrder(nullptr), _nextLevelOrder(nullptr) {
		}

        ~Node() {}

    };

    class OrgChart{

        Node* _manager;

        public:

        // OrgChart Contructor:
        OrgChart();

        // Copy Contructor:
        OrgChart(OrgChart const &other);
        
        // Assignment Operator (for deep copying):
        OrgChart &operator=(const OrgChart &org);       

        /*
        The function receives one input and places it at the root of the tree.
        If there is already something in the root, it is replaced.
         */
        OrgChart& add_root(std::string const& name);

        /*
        The function receives two inputs: a person who already exists in the organizational structure,
        and another person who reports to the first person and is below him in the organizational hierarchy.
        */
        OrgChart &add_sub(std::string const& employer, std::string const& employee);

        friend std::ostream &operator<<(std::ostream &out, const OrgChart &org);

        OrgChart(OrgChart &&org) noexcept;  // tidy
        
        OrgChart &operator=(OrgChart &&org) noexcept; // tidy

        // Destructor:
        ~OrgChart();

        // *************************: Iterator Class *************************:
        
        class iterator {  

		    Node* _currNodePointer;

            int _type;  // -1: preorder | 0: reverse order | 1: level order

	        public:

            // Iterator Contructor:
		    iterator(int type, Node* ptr = nullptr);

            // ~iterator();

            void initLevelOrder(Node* manager);

            void initReverseOrder(Node* manager);

            void initPreOrder(Node* manager);

            void addEmployee(Node* employee);

            Node* getAddress();

		    // Note that the method is const as this operator does not
		    // allow changing of the iterator.
		    // Note that it returns T& as it allows to change what it points to.
		    // A const_iterator class will return const T&
		    // and the method will still be const
		    std::string operator*() const;

		    std::string* operator->() const;

            // ++i
		    iterator& operator++();

		    // i++;
		    // Usually iterators are passed by value and not by const& as they are small.
		    // const iterator operator++(int);

		    bool operator == (const iterator& other) const;

		    bool operator!=(const iterator& other) const;
	    };  // END OF CLASS ITERATOR

        iterator begin_level_order();
        iterator end_level_order();
        
        iterator begin_reverse_order();
        iterator reverse_order();

        iterator begin_preorder();
        iterator end_preorder();

        // regular iterator. ( for 'foreach' )
        iterator begin();
        iterator end();
    };

}