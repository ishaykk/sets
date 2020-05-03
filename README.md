# sets
a basic c written program for functions between sets of numbers, each set contain numbers between 0-127 without duplicated values, a set will have a name (A, B, C, D or F).

Functions:
- read_set: create a new set of numbers, end set with -1.
  e.g. `read_set A, 5, 6, 5, 66, 41 -1` - a new set named A with values: 5, 6, 66, 41.
  
- print_set: e.g. `print_set B` - print B set values.

- union_set:
  - print result of two sets union: `union_set A,B`.
  - store result of two sets union in set: `union A,B,C` - union of sets A & B will be stored in set C.
  
- intersect_set: 
  - print result of two sets intersect: `intersect_set A,B`.
  - store result of two sets intersect in set: `intersect_set A,B,A` intersect of sets A, B will be stored in set A.
  
- sub_set: 
  - print elements that exist in set A but doesn't exist in set B: `sub_set A,B`.
  - elements that exist in set A but doesn't exist in set B will be stored in set C: `sub_set A,B,C`.
  
- comp_set: 
  - print complement numbers of a set: `comp_set A` - if A is 1, 2, 3 then 0, 4, 5..127 will be printed.
  - store complement numbers of a set in a set: `comp_set A,A` - if A is 1,2,3 then 0, 4, 5..127 will be stored in A.
