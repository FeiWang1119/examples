# 55 Specific Ways to Improve Your Programs and Designs 

Table of contents
-----------------

  * [Item 1: View C++ as a federation of languages](#item-1:-view-c++-as-a-federation-of-languages)

# Item 1: View C++ as a federation of languages

The easiest way is to view C++ not as a single language but as a federation of related languages.
To make sense of C++, you have to recognize its primary sublanguages. Fortunately, there are
only four:

- C. Way down deep, C++ is still based on C. 

- Object-Oriented C++. This part of C++ is what C with Classes was all
about: classes (including constructors and destructors), encapsulation,
inheritance, polymorphism, virtual functions (dynamic binding), etc.

- Template C++. This is the generic programming part of C++, the one
that most programmers have the least experience with.

- The STL. The STL is a template library, of course, but it's a very special
template library. Its conventions regarding containers, iterators,
algorithms, and function objects mesh beautifully, but templates and
libraries can be built around other ideas, too.
