#include <cstddef>
#include <stdexcept>

template <typename T>
class Sequence {
protected:
    size_t lenght_;
public:2
    Sequence();
    Sequence(size_t lenght);
    virtual ~Sequence() = default;
    virtual T& Get(size_t index) = 0;
    virtual T& GetLast() = 0;
    virtual T& GetFirst() = 0;
    virtual const T& Get(size_t index) const = 0;
    virtual const T& GetLast() const = 0;
    virtual const T& GetFirst() const = 0;
    virtual size_t GetLenght() const = 0;
    virtual Sequence<T>* GetSubsequence(size_t start_index, size_t end_index) = 0;
    virtual Sequence<T>* Append(const T& item) = 0;
    virtual Sequence<T>* Prepend(const T& item) = 0;
    virtual Sequence<T>* Concat(const Sequence<T>& list1, const Sequence<T>& list2) = 0;
};

template <typename T>
Sequence<T>::Sequence() : lenght_(0) {}

template <typename T>
Sequence<T>::Sequence(size_t lenght) : lenght_(lenght) {}

template <typename T>
class ArraySequence : public Sequence<T> {
public:
    ArraySequence();
    ArraySequence(size_t lenght);
};

template <typename T>
ArraySequence<T>::ArraySequence() : Sequence<T>() {}

template <typename T>
ArraySequence<T>::ArraySequence(size_t lenght) : Sequence<T>(lenght) {}

template <typename T>
class DynamicArray : public ArraySequence<T> {
private:
    T* data_;
    size_t capacity_;
public:
    DynamicArray();
    DynamicArray(size_t lenght);
    DynamicArray(const DynamicArray<T>& other);
    ~DynamicArray();
    T& Get(size_t index) override;
    T& GetLast() override;
    T& GetFirst() override;
    const T& Get(size_t index) const override;
    const T& GetLast() const override;
    const T& GetFirst() const override;
    size_t GetLenght() const override;
    Sequence<T>* GetSubsequence(size_t start_index, size_t end_index) override;
    void Append(const T& item) override;
    void Prepend(const T& item) override;
    Sequence<T>* Concat(const Sequence<T>& list1, const Sequence<T>& list2) override;
    void Set(size_t index, const T& value);
    void ReSize(size_t new_size);
};

template <typename T>
DynamicArray<T>::DynamicArray() : ArraySequence<T>(), data_(nullptr), capacity_(0) {}

template <typename T>
DynamicArray<T>::DynamicArray(size_t lenght) : ArraySequence<T>(lenght), data_(new T[lenght]), capacity_(lenght) {}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& other) : ArraySequence<T>(other.lenght_), data_(new T[other.lenght_]), capacity_(other.capacity_) {
    for (size_t i = 0; i < lenght_; ++i) {
        data_[i] = other.data_[i];
    }
}

template <typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] data_;
}

template <typename T>
T& DynamicArray<T>::Get(size_t index) {
    if (index >= lenght_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

template <typename T>
T& DynamicArray<T>::GetLast() {
    if (lenght_ == 0) {
        throw std::out_of_range("List is empty");
    }
    return data_[lenght_ - 1];
}

template <typename T>
T& DynamicArray<T>::GetFirst() {
    if (lenght_ == 0) {
        throw std::out_of_range("List is empty");
    }
    return data_[0];
}

template <typename T>
const T& DynamicArray<T>::Get(size_t index) const {
    if (index >= lenght_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

template <typename T>
const T& DynamicArray<T>::GetLast() const {
    if (lenght_ == 0) {
        throw std::out_of_range("List is empty");
    }
    return data_[lenght_ - 1];
}

template <typename T>
const T& DynamicArray<T>::GetFirst() const {
    if (lenght_ == 0) {
        throw std::out_of_range("List is empty");
    }
    return data_[0];
}

template <typename T>
size_t DynamicArray<T>::GetLenght() const {
    return lenght_;
}

template <typename T>
Sequence<T>* DynamicArray<T>::GetSubsequence(size_t start_index, size_t end_index) {
    if (start_index >= lenght_ || end_index > lenght_ || start_index > end_index) {
        throw std::out_of_range("Invalid start or end index");
    }
    DynamicArray<T>* subsequence = new DynamicArray<T>(end_index - start_index);
    for (size_t i = start_index; i < end_index; ++i) {
        subsequence->data_[i - start_index] = data_[i];
    }
    return subsequence;
}

template <typename T>
void DynamicArray<T>::Append(const T& item) {
    if (lenght_ == capacity_) {
        capacity_ = (capacity_ == 0) ? 1 : capacity_ * 2;
        T* new_data = new T[capacity_];
        for (size_t i = 0; i < lenght_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
    }
    data_[lenght_] = item;
    ++lenght_;
}

template <typename T>
void DynamicArray<T>::Prepend(const T& item) {
    if (lenght_ == capacity_) {
        capacity_ = (capacity_ == 0) ? 1 : capacity_ * 2;
        T* new_data = new T[capacity_];
        for (size_t i = 0; i < lenght_; ++i) {
            new_data[i + 1] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
    } else {
        for (size_t i = lenght_; i > 0; --i) {
            data_[i] = data_[i - 1];
        }
    }
    data_[0] = item;
    ++lenght_;
}

template <typename T>
Sequence<T>* DynamicArray<T>::Concat(const Sequence<T>& list1, const Sequence<T>& list2) {
    size_t new_lenght = list1.GetLenght() + list2.GetLenght();
    DynamicArray<T>* result = new DynamicArray<T>(new_lenght);

    for (size_t i = 0; i < list1.GetLenght(); ++i) {
        result->data_[i] = list1.Get(i);
    }
    for (size_t i = 0; i < list2.GetLenght(); ++i) {
        result->data_[list1.GetLenght() + i] = list2.Get(i);
    }

    return result;
}

template <typename T>
void DynamicArray<T>::Set(size_t index, const T& value) {
    if (index >= lenght_) {
        throw std::out_of_range("Index out of range");
    }
    data_[index] = value;
}

template <typename T>
void DynamicArray<T>::ReSize(size_t new_size) {
    if (new_size > capacity_) {
        capacity_ = new_size;
        T* new_data = new T[capacity_];
        for (size_t i = 0; i < lenght_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
    }
    lenght_ = new_size;
}

template <typename T>
class LinkSequence : public Sequence<T> {
public:
    LinkSequence();
    LinkSequence(size_t lenght);
};

template <typename T>
LinkSequence<T>::LinkSequence() : lenght_(0) {}

template <typename T>
LinkSequence<T>::LinkSequence(size_t lenght) : lenght_(lenght) {}

template <typename T>
class LinkedList : public LinkSequence<T> {
private:
    struct Node_ {
        T* data;
        Node_* next;
        Node_* prev;
    };
    Node_* head_;
    Node_* tail_;
public:
    LinkedList();
    LinkedList(const LinkedList& other);
    LinkedList(const T* items, size_t count);
    T& Get(size_t index) override;
    const T& Get(size_t index) const override;
    T& GetLast() override;
    const T& GetLast() const override;
    T& GetFirst() override;
    const T& GetFirst() const override;
    size_t GetLenght() const override;
    Sequence<T>* GetSubsequence(size_t start_index, size_t end_index) override;
    LinkedList<T>* GetSubLsit(size_t start_index, size_t end_index);
    void Append(const T& item);
    void Prepend(const T& item);
    LinkedList<T>* Concat(const LinkedList<T>& list1, const LinkedList<T>& list2);
    void InsertAt(const T& item, size_t index);
};

template <typename T>
LinkedList<T>::LinkedList() : LinkSequence<T>(), head_(nullptr), tail_(nullptr) {}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList& other) : LinkSequence<T>(other.lenght_), head_(nullptr), tail_(nullptr) {
    if (lenght_ == 0) {
        return;
    }
    head_ = new Node_{other.head_->data, nullptr, nullptr};
    tail_ = head_;
    Node_* current_node = other.head_->next;
    while (current_node != nullptr) {
        tail_->next = new Node_{current_node->data, nullptr, tail_};
        tail_ = tail_->next;
        current_node = current_node->next;
    }
}

template <typename T>
LinkedList<T>::LinkedList(const T* items, size_t count) : LinkSequence<T>(count), head_(nullptr), tail_(nullptr) {
    if (lenght_ == 0) {
        return;
    }
    head_ = new Node_{items[0], nullptr, nullptr};
    tail_ = head_;
    for (size_t i = 1; i < count; ++i) {
        tail_->next = new Node_{items[i], nullptr, tail_};
        tail_ = tail_->next;
    }
}

template <typename T>
T& LinkedList<T>::Get(size_t index) {
    if (index >= lenght_) {
        throw std::out_of_range("Index out of range");
    }
    size_t count = 0;
    Node_* current_node = head_;
    while (current_node != nullptr) {
        if (index == count) {
            return current_node->data;
        }
        current_node = current_node->next;
        ++count;
    }
}

template <typename T>
const T& LinkedList<T>::Get(size_t index) const {
    if (index >= lenght_) {
        throw std::out_of_range("Index out of range");
    }
    size_t count = 0;
    Node_* current_node = head_;
    while (current_node != nullptr) {
        if (index == count) {
            return current_node->data;
        }
        current_node = current_node->next;
        ++count;
    }

}

template <typename T>
T& LinkedList<T>::GetLast() {
    if (lenght_ == 0) {
        throw std::out_of_range("List is empty");
    }
    return tail_->data;
}

template <typename T>
const T& LinkedList<T>::GetLast() const {
    if (lenght_ == 0) {
        throw std::out_of_range("List is empty");
    }
    return tail_->data;
}

template <typename T>
T& LinkedList<T>::GetFirst() {
    if (lenght_ == 0) {
        throw std::out_of_range("List is empty");
    }
    return head_->data;
}

template <typename T>
const T& LinkedList<T>::GetFirst() const {
    if (lenght_ == 0) {
        throw std::out_of_range("List is empty");
    }
    return head_->data;
}

template <typename T>
size_t LinkedList<T>::GetLenght() const {
    return lenght_;
}

template <typename T>
Sequence<T>*  LinhedList<T>::GetSubsequence(size_t start_index, size_t end_index){
    if (start_index >= lenght_ || end_index > lenght_ || start_index > end_index) {
        throw std::out_of_range("Invalid start or end index");
    }
    LikedList<T>* subsequence = new LinkedList<T>(end_index - start_index);
    Node_* current_node = head_;
    for(size_t i = 0; i < start_index; ++i){
        current_node = current_node->next;
    }
    for(size_t i = start_index; i < end_index; ++i){
        subsequence->Append(current_node->data);
        current_node = current_node->next;
    }
    return subsequence;
}

template <typename T>
void LinkedList<T>::Append(const T& item){
    Node_* new_node = new Node_{item, nullptr, tail_};
    if (tail_ != nullptr) {
        tail_->next = new_node;
    } else {
        head_ = new_node;
    }
    tail_ = new_node;
    ++lenght_;
}

template <typename T>
void LikedList<T>::Prepend(const T& item){
    Node_* new_node = new Node_{item, head_, nullptr};
    if(tail_ != nullptr){
        head_->prev = new_node;
    }else{
        tail_ = new_node;
    }
    head_ = new_node;
    ++lenght_;
}

template <typename T>
LinkedList<T>* LinkedList<T>::GetSubList(size_t start_index, size_t end_index){
    if (start_index >= lenght_ || end_index > lenght_ || start_index > end_index) {
        throw std::out_of_range("Invalid start or end index");
    }
    LikedList<T>* sublsit = new LinkedList<T>(end_index - start_index);
    Node_* current_node = head_;
    for(size_t i = 0; i < start_index; ++i){
        current_node = current_node->next;
    }
    for(size_t i = start_index; i < end_index; ++i){
        sublist->Append(current_node->data);
        current_node = current_node->next;
    }
    return sublist;
}

template <typename T>
LinkedList<T>* LinkedList<T>::Concat(const LinkedList& list1, const LinkedList& list2){
    size_t result_lenght = list1.lenght + list2.lenght;
    LinkedList<T>* result_list = new LinkedList;
    if(list1->head_ == nullptr && list2->head_ == nullptr){
        return result_list;
    }
    if(list2->head_ == nullptr){
        result_list->head_ = list1->head_;
        result_list->tail_ = list1->tail_;
        list1->head_ = nullptr;
        list1->tail_ = nullptr;
        list1.lenght = 0;
        return result_list;
    }
    if(list1->head_ == nullptr){
        result_list->head_ = list2->head_;
        result_list->tail_ = list2->tail_;
        list2->head_ = nullptr;
        list2->tail_ = nullptr;
        list2.lenght = 0;
        return result_list;
    }
    result_list->head_ = list1->head_;
    result_list->tail_ = list1-tail_;
    result_list->tail_->next = list2->head_;
    list2->head_->prev = list1->tail_;
    result_list->tail_ = list2->tail_;
    list1.lenght = 0;
    list2.lenght = 0;
    list1.head_ = nullptr;
    list2.head_ = nullptr;
    list1.tail_ = nullptr;
    list2.tail_ = nullptr;
    return result_list;
}


template <typename T>
void LinkedList<T>* LinkedList<T>:: InsertAt(const T* item, size_t index){
    if(index > lenght_){
        throw std::out_of_range("Index Out Of Range");
    }
    if(index == 0){
        Prepend(item);
        return;
    }
    if(index == lenght_){
        Append(item);
        return;
    }
    Node_* current_node = head_;
    Node_* new_node = new Node{item, nullptr, nullptr};
    for(size_t i = 0; i < index; ++i){
        current_node = corrent_node->next;
    }
    new_node->next = current_node;
    new_node->prev = current_node->prev;
    new_node->prev->next =  new_node;
    new_node->next->prev = new_node;
}


