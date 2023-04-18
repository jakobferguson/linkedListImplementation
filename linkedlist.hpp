//
// Created by Jakob Ferguson on 3/14/23.
//

#ifndef INC_2023_SP_2_HW3_JBFMNF_LINKEDLIST1_H
#define INC_2023_SP_2_HW3_JBFMNF_LINKEDLIST1_H

// Utility Function for Printing
// Purpose: prints a LinkedList
template <typename T>
std::ostream& operator<< (std::ostream& out, const LinkedList<T>& list){
    LLNode<T>* ptr = list.m_head;
    out << "[";
    while(ptr->m_next != NULL){
        out << ptr->m_data << ", ";
        ptr = ptr->m_next;
    }
    out << "]";
    return out;
}

// -------------
// --------- Big 3 Member Functions ---
// -------------

// Purpose: Destructor
// Postconditions: All dynamically allocated Nodes are de-allocated
template <typename T>
LinkedList<T>::~LinkedList(){
    LLNode<T>* current = m_head;
    LLNode<T>* next = NULL;
        while(current!=NULL){
            next = current->m_next;
            delete current;
            current = next;
        }
}

// Purpose: performs a deep copy of the data from rhs into this linkedlist
// Parameters: rhs is linked list to be copied
// Returns: *this
// Postconditions: this list contains same data values (in the same order)
//     as are in rhs; any memory previously used by this list has been
//     deallocated.
template <typename T>
const LinkedList<T>&  LinkedList<T>::operator= (const LinkedList<T>& rhs){
    clear();
    LLNode<T>* runner = rhs.m_head;
    for(int i=0;i<rhs.m_size;i++){
        insert_back(runner->m_data);
        runner=runner->m_next;
    }
    return *this;
}

// Purpose: copy constructor
// Parameters: rhs is the LinkedList that is to be copied
// Postconditions: this list contains same data values (in same order)
//      as in rhs.
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& rhs){
    m_size = 0;
    m_head = new LLNode<T>;
    *this = rhs;
}



// -------------
// --------- Basic Accessor Operations ---
// -------------

// Purpose: accessor function to the size the list
// Returns: current size of the list
template <typename T>
int LinkedList<T>::size() const{
    return m_size;
}

// Purpose: determines whether the list is empty
// Returns: 'true' if list is empty; 'false' otherwise
template <typename T>
bool LinkedList<T>::isEmpty() const{
    if(m_head->m_next==NULL){
        return true;
    }
    return false;
}

// Purpose: Get a pointer to the first element node
// Returns: pointer to the first node in the list;
//     returns NULL if the list is empty
template <typename T>
LLNode<T>* LinkedList<T>::getFirstPtr(){
    LLNode<T>* ptr = m_head;
    if (ptr->m_next==NULL){
        return NULL;
    }
    return ptr;
}

// Purpose: accessor function for a node in the list
// Returns: pointer to the node at the i'th position in the list;
//          counting starts from '0' .
//     returns NULL if no such element exists.
template <typename T>
LLNode<T>* LinkedList<T>::getAtPtr(int i){
    LLNode<T>* ptr = m_head;
    if(i >= m_size){
        ptr = NULL;
        return ptr;
    }
    if(i==0){
        return ptr;
    }
    for(int j=0;j<i;j++){
        ptr=ptr->m_next;
    }
    return ptr;
}



// -------------
// --------- Basic Mutator Operations ---
// -------------

// Purpose: effectively "empties" the list,
//          Turn the list into an empty list.
// Postconditions: dynamically allocated non-sentinel nodes
//          are de-allicated.
//          m_size is set to zero.
//          m_head points to a sentinel node.
template <typename T>
void LinkedList<T>::clear(){
    LLNode<T>* current = m_head;
    LLNode<T>* next = NULL;
    while(current->m_next!=NULL){
        next = current->m_next;
        delete current;
        current = next;
    }
    m_head = current;
    m_size=0;
}

// Purpose: insert element x in the front of the list
// Parameters: x is data value to inserted
// Postconditions: x is the first element of the list
template <typename T>
void LinkedList<T>::insert_front(const T& x){
    LLNode<T>* tmp = m_head;
    m_head = new LLNode<T>;
    m_head->m_data=x;
    m_head->m_next=tmp;
    m_size++;
}

// Purpose: insert element x in the back of the list
// Parameters: x is data value to inserted
// Postconditions: x is the last element of the list
template <typename T>
void LinkedList<T>::insert_back(const T& x){
    if(m_head->m_next == NULL){
        m_head->m_data = x;
        m_head->m_next=new LLNode<T>;
        m_size++;
    }else{
        LLNode<T>* current = m_head;
        while(current->m_next != NULL) {
            current = current->m_next;
        }
        current->m_next = new LLNode<T>;
        current->m_data = x;
        m_size++;
    }
}

// Purpose: puts the data value x at the position pointed by pos
// Parameters: x : data value to be inserted
//     pos : pointer to the position to insert x at.
// Preconditions: pos is a pointer to a node in this list.
// Postconditions: x is inserted at the position pointed by pos
template <typename T>
void LinkedList<T>::insert(const T& x, LLNode<T>* pos){
    LLNode<T>* tmp = new LLNode<T>;
    tmp->m_data = pos->m_data;
    tmp->m_next = pos->m_next;
    pos->m_data=x;
    pos->m_next=tmp;
    m_size++;
}


// Purpose: remove the element in the front of the list
// Postconditions: the first element of the list is removed
template <typename T>
void LinkedList<T>::remove_front(){
    LLNode<T>* tmp = m_head;
    m_head = m_head->m_next;
    delete tmp;
    m_size--;
}

// Purpose: removes the element at the back of the list
// Postconditions: the last element of the list is removed
template <typename T>
void LinkedList<T>::remove_back(){
    LLNode<T>* tmp = getAtPtr(m_size-1);
    delete tmp->m_next;
    tmp->m_next=NULL;
    m_size--;
}

// Purpose: remove the element in the position pointed by pos
// Parameters: pos : pointer to the position to remove.
// Preconditions: pos is a pointer to a node in this list.
// Postconditions: element pointed by pos is removed from the list
template <typename T>
void LinkedList<T>::remove(LLNode<T>* pos){
    LLNode<T>* tmp = pos->m_next;
    pos->m_data = tmp->m_data;
    pos->m_next=tmp->m_next;
    delete tmp;
    m_size--;
}


// --------
// ---- Complex Operations ---
// --------

// Purpose: determines whether this list is identical to rhs list in
//      terms of data values and their order in the list
// Parameters: rhs is list to be compared to this list
// Returns: true if lists are identical; otherwise, false
template <typename T>
bool LinkedList<T>::operator== (const LinkedList<T>& rhs) const{
    int counter = 0;
    LLNode<T>* tmp1 = m_head;
    LLNode<T>* tmp2 = rhs.m_head;
    while(counter<m_size){
        if(tmp1->m_data != tmp2->m_data){
            return false;
        }
        tmp1=tmp1->m_next;
        tmp2=tmp2->m_next;
        counter++;
    }
    return true;
}

// Purpose: determines whether x is in the list
// Parameters: x : data value to be found
// Returns: a pointer to the position of x in the list;
//     otherwise, NULL
template <typename T>
LLNode<T>* LinkedList<T>::find(const T& x){
    LLNode<T>* current = m_head;
    while(current->m_next!=NULL){
        if(current->m_data==x){
            return current;
        }
        current=current->m_next;
    }
    return NULL;

}


// Purpose: reverses the elements from the list
// Postconditions: the list is now in reverse order
template <typename T>
void LinkedList<T>::reverse(){
    LinkedList<T> tempL;
    LLNode<T>* current = m_head;
    for(int i=0;i<m_size;i++){
        tempL.insert_front(current->m_data);
        current=current->m_next;
    }
    *this = tempL;
    tempL.clear();
}

// Purpose: Removes duplicates from a Linked List.
// Postconditions: all duplicate elements are removed from the list.
//    the first occurance of an element is kept.
template <typename T>
void LinkedList<T>::purge(){
    LLNode<T>* comp = m_head;
    while(comp -> m_next != NULL) {
        LLNode<T> *node = comp->m_next;
        while (node->m_next != NULL) {
            if (comp->m_data == node->m_data) {
                if (node->m_next == NULL) {
                    remove_back();
                } else {
                    remove(node);
                }
            } else {
                node = node->m_next;
            }
        }
        comp=comp->m_next;
    }
}

// Purpose: appends two lists
// Parameters: l2, a list to append to the end of 'this' list
// Postconditions: elements of l2 are appended to 'this' list
template <typename T>
void LinkedList<T>::append(const LinkedList<T>& l2){
    LLNode<T>* runner = l2.m_head;
    for(int i=0;l2.m_size > i;i++){
        this->insert_back(runner->m_data);
        runner=runner->m_next;
    }
}

// Purpose: Makes 'this' list a slice of another list.
// Parameters:    l2, the source of a slice of data.
//                start, pointer to the begining of the slice.
//                stop, pointer to the end of the slice.
// Preconditions: 'start' and 'stop' are pointers to nodes in the l2 list.
//                'start' precedes 'stop' in the l2 list
// Postconditions: 'this' list is made a copy of the elements between 'start'
//                  and 'stop' (*exclusive*) in l2.
template <typename T>
void LinkedList<T>::slice( const LinkedList<T>& l2, LLNode<T>* start, LLNode<T>* stop){
    clear();
    LLNode<T>* current = start;
    while(current!=stop){
        insert_back(current->m_data);
        current=current->m_next;
    }
}

#endif //INC_2023_SP_2_HW3_JBFMNF_LINKEDLIST1_H
