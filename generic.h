#ifndef GENERIC_H_
#define GENERIC_H_
typedef void* Item_ptr;
struct generic_vector {
  void(*assignment)(Item_ptr* pLeft, Item_ptr Right);
  void(*destroy)(Item_ptr* ppItem);
  int size;  // The number of elements in the vector
  int capacity;  // The number of elements the vector CAN hold
  Item_ptr* data;
};

typedef struct generic_vector Generic_vector;





#endif  // GENERIC_H_
