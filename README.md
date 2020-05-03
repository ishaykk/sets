# sets
a basic c written program for sets of numbers

Functions:
- read_set: create a new set (A-F) of numbers between 0-127, set will always end with -1. e.g. `read_set A, 5, 6, 5, 76, 44, 23, 23, 98, 23, -1`
- print_set: e.g. `print_set B`
- union_set:
  - print result of two sets union: `union_set A,B`
  - store result of two sets union in set: `union A,B,C` - union of sets A & B will be stored in set C
- intersect_set: 
  - print result of two sets intersect: `intersect_set A,B`
  - store result of two sets intersect in set: `intersect_set A,B,A` intersect of sets A, B will be stored in set A
- sub_set: e.g. `sub_set A, B` - print elements that exist in set A but doesn't exist in set B'
- comp_set: 
  - print complement numbers of a set: `comp_set A` - if A is 1, 2, 3 then 0, 4, 5..127 will be printed
  - store complement numbers of a set in a set: `comp_set A, A` - if A is 1,2,3 then 0, 4, 5..127 will be stored in A
