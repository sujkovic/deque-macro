#ifndef DEQUE_H
#define DEQUE_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Deque_DEFINE(t)                     \
    struct Deque_##t;                       \
    struct Deque_##t##_Iterator;            \
    typedef struct Deque_##t##_Iterator {                                         \
        Deque_##t* deque;                                                         \
        size_t index;                                                             \
        bool (*equal)(struct Deque_##t##_Iterator, struct Deque_##t##_Iterator);  \
        void (*inc)(struct Deque_##t##_Iterator*);                                \
        void (*dec)(struct Deque_##t##_Iterator*);                                \
        t &(*deref)(struct Deque_##t##_Iterator*);                                \
    } Deque_##t##_Iterator;                                                       \
    typedef struct Deque_##t {                                                                     \
        t* array;                                                                                  \
        size_t arrFront;                                                                           \
        size_t arrBack;                                                                            \
        size_t arrSize;                                                                            \
        size_t arrCapacity;                                                                        \
        char type_name[strlen("Deque_"#t) + 1];                                                    \
        bool (*compare)(const t& x, const t& y);                                                   \
        void (*dtor)(struct Deque_##t*);                                                           \
        size_t (*size)(struct Deque_##t*);                                                         \
        bool (*empty)(struct Deque_##t*);                                                          \
        t &(*front)(struct Deque_##t*);                                                            \
        t &(*back)(struct Deque_##t*);                                                             \
        void (*push_front)(struct Deque_##t*, t element);                                          \
        void (*push_back)(struct Deque_##t*, t element);                                           \
        void (*pop_front)(struct Deque_##t*);                                                      \
        void (*pop_back)(struct Deque_##t* );                                                      \
        struct Deque_##t##_Iterator (*begin)(struct Deque_##t*);                                   \
        struct Deque_##t##_Iterator (*end)(struct Deque_##t*);                                     \
        void (*resize)(struct Deque_##t*);                                                         \
        void (*clear)(struct Deque_##t*);                                                          \
        t &(*at)(struct Deque_##t*, size_t);                                                          \
        bool (*equal)(struct Deque_##t, struct Deque_##t);                                         \
        int (*sortCompare)(const void*, const void*);     \
        void (*sort)(struct Deque_##t*, struct Deque_##t##_Iterator, struct Deque_##t##_Iterator); \
    } Deque_##t;                                                                                   \
    \
    \
    \
    bool Deque_##t##_Iterator_equal(struct Deque_##t##_Iterator it1, struct Deque_##t##_Iterator it2) {     \
        return it1.index == it2.index;                                                                      \
    }                                                                                                       \
    void Deque_##t##_Iterator_inc(struct Deque_##t##_Iterator* it) {      \
        it->index = (it->index + 1) % it->deque->arrCapacity;             \
    }                                                                     \
    void Deque_##t##_Iterator_dec(struct Deque_##t##_Iterator* it) {                      \
        it->index = (it->index - 1 + it->deque->arrCapacity) % it->deque->arrCapacity;    \
    }                                                                                     \
    t& Deque_##t##_Iterator_deref(struct Deque_##t##_Iterator* it) {      \
        return it->deque->array[(it->deque->arrFront + it->index) % it->deque->arrCapacity];                               \
    }                                                                     \
    \
    \
    \
    void Deque_##t##_dtor(struct Deque_##t* deque) {            \
        free(deque->array);                                     \
    }                                                           \
    size_t Deque_##t##_size(struct Deque_##t* deque) {        \
        return deque->arrSize;                                \
    }                                                         \
    bool Deque_##t##_empty(struct Deque_##t* deque) {           \
        return deque->arrSize <= 0;                             \
    }                                                           \
    t &Deque_##t##_front(struct Deque_##t* deque) {           \
        return deque->array[deque->arrFront];                 \
    }                                                         \
    t &Deque_##t##_back(struct Deque_##t* deque) {                                          \
        return deque->array[(deque->arrFront + deque->arrSize - 1) % deque->arrCapacity];   \
    }                                                                                       \
    void Deque_##t##_resize(struct Deque_##t* deque) {                             \
        t* newArr = (t*)malloc((deque->arrCapacity * 2) * sizeof(t));              \
        for (size_t i = 0; i < deque->arrSize; i++) {                              \
            newArr[i] = deque->array[(deque->arrFront + i) % deque->arrCapacity];  \
        }                                                                          \
        free(deque->array);                                                        \
        deque->array = newArr;                                                     \
        deque->arrFront = 0;                                                       \
        deque->arrBack = deque->arrSize - 1;                                       \
        deque->arrCapacity = deque->arrCapacity * 2;                               \
    }                                                                              \
    void Deque_##t##_push_front(struct Deque_##t* deque, t element) {                        \
        if (deque->arrSize >= deque->arrCapacity) {                                          \
            Deque_##t##_resize(deque);                                                       \
        }                                                                                    \
        deque->arrFront = (deque->arrFront - 1 + deque->arrCapacity) % deque->arrCapacity;   \
        deque->array[deque->arrFront] = element;                                             \
        deque->arrSize++;                                                                    \
    }                                                                                        \
    void Deque_##t##_push_back(struct Deque_##t* deque, t element) {                          \
        if (deque->arrSize >= deque->arrCapacity) {                                           \
            Deque_##t##_resize(deque);                                                        \
        }                                                                                     \
        deque->array[(deque->arrFront + deque->arrSize) % deque->arrCapacity] = element;      \
        deque->arrSize++;                                                                     \
    }                                                                                         \
    void Deque_##t##_pop_front(struct Deque_##t* deque) {                      \
        if (!deque->empty(deque)) {                                            \
            deque->arrFront = (deque->arrFront + 1) % deque->arrCapacity;      \
            deque->arrSize--;                                                  \
        }                                                                      \
    }                                                                          \
    void Deque_##t##_pop_back(struct Deque_##t* deque) {                    \
        if (!deque->empty(deque)) {                                         \
            deque->arrSize--;                                               \
        }                                                                   \
    }                                                                       \
    Deque_##t##_Iterator Deque_##t##_begin(struct Deque_##t* deque) {          \
        Deque_##t##_Iterator it;                    \
        it.index = deque->arrFront;                 \
        it.deque = deque;                           \
        it.equal = Deque_##t##_Iterator_equal;      \
        it.inc = Deque_##t##_Iterator_inc;          \
        it.dec = Deque_##t##_Iterator_dec;          \
        it.deref = Deque_##t##_Iterator_deref;      \
        return it;                                  \
    }                                               \
    Deque_##t##_Iterator Deque_##t##_end(struct Deque_##t* deque) {             \
        Deque_##t##_Iterator it;                                                \
        it.index = (deque->arrFront + deque->arrSize) % deque->arrCapacity;     \
        it.deque = deque;                                                       \
        it.equal = Deque_##t##_Iterator_equal;                                  \
        it.inc = Deque_##t##_Iterator_inc;                                      \
        it.dec = Deque_##t##_Iterator_dec;                                      \
        it.deref = Deque_##t##_Iterator_deref;                                  \
        return it;                                                              \
    }                                                                           \
    void Deque_##t##_clear(struct Deque_##t* deque) {                       \
        free(deque->array);                                                 \
        deque->array = (t*)malloc(sizeof(t));                               \
        deque->arrFront = 0;                                                \
        deque->arrBack = 0;                                                 \
        deque->arrSize = 0;                                                 \
        deque->arrCapacity = 1;                                             \
    }                                                                       \
    t &Deque_##t##_at(struct Deque_##t* deque, size_t i) {                 \
        return deque->array[(deque->arrFront + i) % deque->arrSize];   \
    }                                                                      \
    bool Deque_##t##_equal(struct Deque_##t d1, struct Deque_##t d2) {  \
        if (d1.arrSize != d2.arrSize) {                                 \
            return false;                                               \
        }                                                               \
        for (size_t i = 0; i < d1.arrSize; i++) {                       \
            if (d1.compare(d1.at(&d1, i), d2.at(&d2, i)) || d1.compare(d2.at(&d2, i), d1.at(&d1, i))) {             \
                return false;                                           \
            }                                                           \
        }                                                               \
        return true;                                                    \
    }                                                                   \
    int Deque_##t##_sortCompare(const void*x, const void*y) {       \
        Deque_##t deque;                                                \
        return deque.compare(*(t*)x, *(t*)y);                                     \
    }                                                                   \
    void Deque_##t##_sort(struct Deque_##t* deque, struct Deque_##t##_Iterator it1, struct Deque_##t##_Iterator it2) {  \
        size_t count = 0;                               \
        struct Deque_##t##_Iterator it = it1;           \
        while (!Deque_##t##_Iterator_equal(it, it1)) {  \
            it.inc(&it);                                \
            count++;                                    \
        }                                               \
        qsort(deque->array, count++, sizeof(t), deque->sortCompare);                     \
    }                                                                                                                   \
    \
    void Deque_##t##_ctor(struct Deque_##t* deque, bool (*compareParam)(const t& x, const t& y)) {                      \
        deque->array = (t*)malloc(sizeof(t));                   \
        deque->arrFront = 0;                                    \
        deque->arrBack = 0;                                     \
        deque->arrSize = 0;                                     \
        deque->arrCapacity = 1;                                 \
        strcpy(deque->type_name, "Deque_"#t);                   \
        deque->compare = compareParam;                          \
        deque->size = Deque_##t##_size;                         \
        deque->empty = Deque_##t##_empty;                       \
        deque->dtor = Deque_##t##_dtor;                         \
        deque->front = Deque_##t##_front;                       \
        deque->back = Deque_##t##_back;                         \
        deque->resize = Deque_##t##_resize;                     \
        deque->push_back = Deque_##t##_push_back;               \
        deque->push_front = Deque_##t##_push_front;             \
        deque->pop_back = Deque_##t##_pop_back;                 \
        deque->pop_front = Deque_##t##_pop_front;               \
        deque->clear = Deque_##t##_clear;                       \
        deque->at = Deque_##t##_at;                             \
        deque->begin = Deque_##t##_begin;                       \
        deque->end = Deque_##t##_end;                           \
        deque->sort = Deque_##t##_sort;                         \
        deque->equal = Deque_##t##_equal;                       \
        deque->sortCompare = Deque_##t##_sortCompare;           \
    }                                                           \

#endif
