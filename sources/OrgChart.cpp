
#include "OrgChart.hpp"
#include<bits/stdc++.h>

using namespace std;

namespace ariel{

    // Contructor:
    OrgChart :: OrgChart()
            
            : _manager(NULL){

                cout << "Contructor" << endl;

            }

    // void del(Node* emp){

    //     for (Node* employee : emp->_employees){

    //         del(employee);
    //     }
        
    //     delete *emp;
    // }

        // Destructor:
    OrgChart :: ~OrgChart(){

        cout << "Destructor" << endl;

        // // del(this->_manager);
        if (this->_manager != NULL){

            vector<Node*> temp;

            try
            {
                for(auto i = this->begin();i != this->end();++i){
                
                    temp.push_back(i.getAddress());
                }

                for (auto i = temp.begin();i!=temp.end();i++){
                 
                    delete *i;
                }
            }
            catch(const std::exception& e){
               
            }
        }
    }

    

    OrgChart ::OrgChart (OrgChart const &other){

        this->_manager = other._manager;
    }

    // The function receives one input and places it at the root of the tree.
    OrgChart& OrgChart :: add_root(string const& name){

        // If there is no manager:
        if (this->_manager == NULL) {

            this->_manager = new Node(name);
        }
        
        // If a manager already exists:
        else {

            this->_manager->_name = name;
        }

        return *this;
    }

    /*
    The function receives two inputs: a person who already exists in the organizational structure,
    and another person who reports to the first person and is below him in the organizational hierarchy.
    */
    OrgChart& OrgChart :: add_sub(string const& employer, string const& employee){

        // If there is no manager:
        if (this->_manager == NULL){

            throw runtime_error("There is no manager");
        }

        for (auto it = this->begin_level_order(); it != this->end_level_order(); ++it) {

            if (*it == employer){

                it.addEmployee(new Node(employee));
                return *this;
            }
        } 
    
        throw runtime_error("There is no employer");
        // return *this;
    }

    OrgChart :: iterator OrgChart :: begin_level_order(){

        // If there is no manager:
        if (this->_manager == NULL){

            throw runtime_error("There is no manager");
        }

        return OrgChart :: iterator(1, this->_manager);
    }

    OrgChart :: iterator OrgChart :: end_level_order(){

        if (this->_manager == NULL){

            throw runtime_error("There is no manager");
        }

        return OrgChart :: iterator(-2);
    }
    
    OrgChart :: iterator OrgChart :: begin_reverse_order(){

        // If there is no manager:
        if (this->_manager == NULL){

            throw runtime_error("There is no manager");
        }

        return OrgChart :: iterator(0, this->_manager);
    }
    OrgChart :: iterator OrgChart :: reverse_order(){

        if (this->_manager == NULL){

            throw runtime_error("There is no manager");
        }

        return OrgChart :: iterator(-2);
    }

    OrgChart :: iterator OrgChart :: begin_preorder(){

        // If there is no manager:
        if (this->_manager == NULL){

            throw runtime_error("There is no manager");
        }

        return OrgChart :: iterator(-1, this->_manager);
    }
    OrgChart :: iterator OrgChart :: end_preorder(){

        if (this->_manager == NULL){

            throw runtime_error("There is no manager");
        }

        return OrgChart :: iterator(-2);
    }

    OrgChart :: iterator OrgChart :: begin(){

        // If there is no manager:
        if (this->_manager == NULL){

            throw runtime_error("There is no manager");
        }

        return OrgChart :: iterator(1, this->_manager);
    }

    OrgChart :: iterator OrgChart :: end(){

        if (this->_manager == NULL){

            throw runtime_error("There is no manager");
        }

        return OrgChart :: iterator(-2);
    }

    ostream& operator << (ostream& out, const OrgChart& org){

        // OrgChart temp = org;

        //  for (const auto const element : org) { // this should work like level order
            
        //     out << element << " " ;
        // } 

        // for(auto const i = org.begin();i != this->end();++i){
            
        //     temp.push_back(i.getAddress());
        // }

        // return out;

            // If there is no manager:
        if (org._manager == NULL){

            throw runtime_error("There is no manager");
        }

        queue<Node*> q;

        Node* temp = nullptr;

        q.push(org._manager);

        while (!q.empty()) {
        
            temp = q.front();

            out << temp->_name << " " ;
        
            q.pop();

            for (Node *employee : temp->_employees) {
                
                q.push(employee);
            }
        }
        
        return out;
    }

    OrgChart :: OrgChart(OrgChart &&org) noexcept {
        
        this->_manager = org._manager;
        
        org._manager = nullptr;
    }

            // Assignment Operator (for deep copying):
    // OrgChart& OrgChart :: operator=(const OrgChart &org){

    //     if (this == &org) {
    //             return *this;
    //         }
    //     this->_manager = make_shared<Node*>(*org._manager);
    //     return *this;
    // }

       // 	// Move assignment
	// // Transfer ownership of a.m_ptr to m_ptr
	// Auto_ptr4& operator=(Auto_ptr4&& a) noexcept
	// {
	// 	// Self-assignment detection
	// 	if (&a == this)
	// 		return *this;

	// 	// Release any resource we're holding
	// 	delete m_ptr;

	// 	// Transfer ownership of a.m_ptr to m_ptr
	// 	m_ptr = a.m_ptr;
	// 	a.m_ptr = nullptr; // we'll talk more about this line below

	// 	return *this;
	// }

    OrgChart& OrgChart :: operator = (OrgChart &&org) noexcept {

        if (&org == this){

            return *this;
        } 		
        
        this->_manager = org._manager;
        
        org._manager = nullptr;
        
        return *this;
    }

    // 	// Move constructor
	// // Transfer ownership of a.m_ptr to m_ptr
	// Auto_ptr4(Auto_ptr4&& a) noexcept
	// 	: m_ptr(a.m_ptr)
	// {
	// 	a.m_ptr = nullptr; // we'll talk more about this line below
	// }

    // ********************* Iterator Class *********************

    // Iterator Contructor:
	OrgChart :: iterator ::	iterator(int type, Node* ptr)
			
                : _currNodePointer(ptr), _type(type) {

        // level order (if type is 1):
        if (type == 1){

            this->initLevelOrder(ptr);
        }
                
        // reverse order (if type is 0):
        else if (type == 0){

            this->initReverseOrder(ptr);
        }
                
        // preorder (if type is -1):
        else if (type == -1){

           this->initPreOrder(ptr);
        }

	}

    void OrgChart :: iterator :: addEmployee(Node* employee){

        this->_currNodePointer->_employees.push_back(employee);
    }

    Node* OrgChart :: iterator :: getAddress(){

        return this->_currNodePointer;
    }

    /*
    This function uses the BFS algorithm and directs the pointers of
    level order according to the transition order of the algorithm.
    */
    void OrgChart :: iterator :: initLevelOrder(Node* manager){

        // If there is no manager:
        if (manager == NULL){

            throw runtime_error("There is no manager");
        }

        queue<Node*> q;

        Node* temp = nullptr;

        q.push(manager);

        while (!q.empty()) {
        
            temp = q.front();
        
            q.pop();

            for (Node *employee : temp->_employees) {
                
                q.push(employee);
            }

            temp->_nextLevelOrder = q.front();
        }

        if (temp != nullptr){

            temp->_nextLevelOrder = nullptr;
        }

        this->_currNodePointer = manager;
    }

    /*
    This function also uses the BFS algorithm, the only change is that the iterator
    goes through the list of employees from end to beginning and not in the usual order.
    The function directs the pointers of reverse order according to the transition order of the algorithm.
    */
    void OrgChart :: iterator :: initReverseOrder(Node* manager){

         // If there is no manager:
        if (manager == NULL){

            throw runtime_error("There is no manager");
        }

        queue<Node*> q;

        Node* temp = nullptr;

        manager->_nextReverseOrder = nullptr;

        q.push(manager);

        while (!q.empty()) {
        
            temp = q.front();
            q.pop();

            for (auto it = temp->_employees.rbegin(); it != temp->_employees.rend(); it++) {
                
                q.push(*it);
            }

            if (!q.empty()) {
                
                q.front()->_nextReverseOrder = temp;
            }     
        }

        this->_currNodePointer = temp;
    }

    void OrgChart :: iterator :: initPreOrder(Node* manager){

    // If there is no manager:
        if (manager == NULL){

            throw runtime_error("There is no manager");
        }

        vector<Node*> v;

        Node* temp = nullptr;

        v.push_back(manager);

        int index = 0;
        int innerIndex = 1;

        while (index < v.size()) {

            temp = v.at((unsigned long)index);
            
            innerIndex = 1;

            for (Node *employee : temp->_employees) {

                v.insert((v.begin() + innerIndex + index), employee);
                innerIndex++;
            }
            index++;            
        }

        for (size_t i = 0; i < v.size() - 1; i++) {

            v.at(i)->_nextPreorder = v.at(i+1);
        }

        v.at(v.size() - 1)->_nextPreorder = nullptr;

        this->_currNodePointer = manager;
    }

    string OrgChart :: iterator :: operator * () const {
			
        //return *pointer_to_current_node;
		return this->_currNodePointer->_name;
	}

    string* OrgChart :: iterator :: operator -> () const {
			
        return &(this->_currNodePointer->_name);
	}

    // ++i
    OrgChart :: iterator &OrgChart :: iterator :: operator ++ () {

        // level order (if type is 1):
        if (this->_type == 1){

            _currNodePointer = _currNodePointer->_nextLevelOrder;
        }
                
        // reverse order (if type is 0):
        else if (this->_type == 0){

            _currNodePointer = _currNodePointer->_nextReverseOrder;
        }
                
        // preorder (if type is -1):
        else if (this->_type == -1){

            _currNodePointer = _currNodePointer->_nextPreorder;
        }

        return *this;
	}

    // i++;
	// Usually iterators are passed by value and not by const& as they are small.
	// const OrgChart :: iterator OrgChart :: iterator :: operator ++ (int) {
			
    //     iterator temp= *this;
		
    //     this->_currNodePointer = _currNodePointer->_nextLevelOrder;
		
    //     return temp;
	// }

    bool OrgChart :: iterator :: operator == (const iterator& other) const {
			    
        return _currNodePointer == other._currNodePointer;
	}

    bool OrgChart :: iterator :: operator != (const iterator& other) const {
			    
        return _currNodePointer != other._currNodePointer;
	}

    //     OrgChart::iterator::~iterator()
    // {
    //     this->_currNodePointer = nullptr;
    //     std::move(this->_type);
    // }

}