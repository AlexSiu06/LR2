#include <cassert>
#include "sequense.h"

void testDynamicArrayDefaultConstructor() {
    DynamicArray<int> arr;
    assert(arr.GetLenght() == 0);
}

void testDynamicArrayConstructorWithSize() {
    DynamicArray<int> arr(5);
    assert(arr.GetLenght() == 5);
    for (int i = 0; i < 5; ++i) {
        assert(arr.Get(i) == int());
    }
}

void testDynamicArraySetAndGet() {
    DynamicArray<int> arr(3);
    arr.Set(0, 10);
    arr.Set(1, 20);
    arr.Set(2, 30);
    assert(arr.Get(0) == 10);
    assert(arr.Get(1) == 20);
    assert(arr.Get(2) == 30);
}

void testDynamicArrayAppend() {
    DynamicArray<int> arr;
    arr.Append(10);
    arr.Append(20);
    assert(arr.GetLenght() == 2);
    assert(arr.Get(0) == 10);
    assert(arr.Get(1) == 20);
    arr.Append(30);
    assert(arr.GetLenght() == 3);
    assert(arr.Get(2) == 30);
}

void testDynamicArrayPrepend() {
    DynamicArray<int> arr;
    arr.Prepend(10);
    arr.Prepend(20);
    assert(arr.GetLenght() == 2);
    assert(arr.Get(0) == 20);
    assert(arr.Get(1) == 10);
    arr.Prepend(30);
    assert(arr.GetLenght() == 3);
    assert(arr.Get(0) == 30);
    assert(arr.Get(1) == 20);
    assert(arr.Get(2) == 10);
}

void testDynamicArrayGetSubsequence() {
    DynamicArray<int> arr(5);
    for (int i = 0; i < 5; ++i) {
        arr.Set(i, i + 1);
    }
    Sequence<int>* sub = arr.GetSubsequence(1, 3);
    assert(sub->GetLenght() == 2);
    assert(sub->Get(0) == 2);
    assert(sub->Get(1) == 3);
    delete sub;
}

void testDynamicArrayReSize() {
    DynamicArray<int> arr(5);
    arr.ReSize(10);
    assert(arr.GetLenght() == 10);
    for (int i = 0; i < 5; ++i) {
        assert(arr.Get(i) == int());
    }
    arr.ReSize(3);
    assert(arr.GetLenght() == 3);
}



void testDynamicArrayWhere() {
    DynamicArray<int> arr;
    arr.Append(10);
    arr.Append(20);
    arr.Append(30);
    arr.Append(40);
    
    DynamicArray<int>* select_arr = dynamic_cast<DynamicArray<int>*>(arr.Where([](int value){
        return value > 25;
    }));
    assert(select_arr->GetLenght() == 2);
    assert(select_arr->Get(0) == 30);
    assert(select_arr->Get(1) == 40);
    delete select_arr;
}

void unary(int& value) {
    value += 1;
}

void testDynamicArrayMap() {
    DynamicArray<int> arr;
    arr.Append(10);
    arr.Append(20);
    arr.Append(30);
    DynamicArray<int>* mapped = dynamic_cast<DynamicArray<int>*>(arr.Map([](int& value){
        value += 1;
    }));
    assert(mapped->GetLenght() == 3);
    assert(mapped->Get(0) == 11);
    assert(mapped->Get(1) == 21);
    assert(mapped->Get(2) == 31);
    delete mapped;
}

void testLinkedListDefaultConstructor() {
    LinkedList<int> list;
    assert(list.GetLenght() == 0);
}

void testLinkedListConstructorWithSize() {
    LinkedList<int> list(5);
    assert(list.GetLenght() == 5);
    for (int i = 0; i < 5; ++i) {
        assert(list.Get(i) == int());
    }
}

void testLinkedListAppend() {
    LinkedList<int> list;
    list.Append(10);
    list.Append(20);
    assert(list.GetLenght() == 2);
    assert(list.Get(0) == 10);
    assert(list.Get(1) == 20);
    list.Append(30);
    assert(list.GetLenght() == 3);
    assert(list.Get(2) == 30);
}

void testLinkedListPrepend() {
    LinkedList<int> list;
    list.Prepend(10);
    list.Prepend(20);
    assert(list.GetLenght() == 2);
    assert(list.Get(0) == 20);
    assert(list.Get(1) == 10);
    list.Prepend(30);
    assert(list.GetLenght() == 3);
    assert(list.Get(0) == 30);
    assert(list.Get(1) == 20);
    assert(list.Get(2) == 10);
}

void testLinkedListGetSubsequence() {
    LinkedList<int> list;
    for (int i = 0; i < 5; ++i) {
        list.Append(i + 1);
    }
    Sequence<int>* sub = list.GetSubsequence(1, 3);
    assert(sub->GetLenght() == 2);
    assert(sub->Get(0) == 2);
    assert(sub->Get(1) == 3);
    delete sub;
}

void testLinkedListInsertAt() {
    LinkedList<int> list;
    list.Append(10);
    list.Append(30);
    list.InsertAt(20, 1);
    assert(list.GetLenght() == 3);
    assert(list.Get(0) == 10);
    assert(list.Get(1) == 20);
    assert(list.Get(2) == 30);
    list.InsertAt(5, 0);
    assert(list.GetLenght() == 4);
    assert(list.Get(0) == 5);
    assert(list.Get(1) == 10);
    list.InsertAt(40, 4);
    assert(list.GetLenght() == 5);
    assert(list.Get(4) == 40);
}

void testLinkedListWhere() {
    LinkedList<int> list;
    list.Append(11);
    list.Append(20);
    list.Append(30);
    list.Append(40);
    LinkedList<int>* select_list = static_cast<LinkedList<int>*>(list.Where([](int value){
        return value % 2 == 0;
    }));
    assert(select_list->GetLenght() == 2);
    assert(select_list->Get(0) == 30);
    assert(select_list->Get(1) == 40);
    delete select_list;
}

void testLinkedListMap() {
    LinkedList<int> list;
    list.Append(10);
    list.Append(20);
    list.Append(30);
    list.Append(40);
    LinkedList<int>* mapped = static_cast<LinkedList<int>*>(list.Map([](int& value){
        value *= 2;
    }));
    assert(mapped->GetLenght() == 4);
    assert(mapped->Get(0) == 20);
    assert(mapped->Get(1) == 40);
    assert(mapped->Get(2) == 60);
    assert(mapped->Get(3) == 80);
    delete mapped;
}


