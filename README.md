# openUDT `{++}`

## Open Unique Data Types

openUDT is a large-scale C++ library collection consisting of approximately **37 KLOC** of source code. It provides a wide range of unique, reusable, and general-purpose data types designed for various software applications.

The project follows an STL-like design philosophy, providing familiar interfaces, generic usability, predictable behavior, and easy integration into modern C++ projects.

The `{++}` logo represents the identity of the project:

* `++` is inspired by the C++ programming language, the language in which openUDT is implemented.
* `{}` represents objects and encapsulation, reflecting the object-oriented nature of the provided data types.

## Unique Data Types

openUDT introduces many specialized data types beyond the conventional structures available in standard libraries. Examples include:

### dynamic

A collection of objects designed to provide flexible data types through runtime dynamic memory management. These objects allow data structures to adapt their size and behavior during program execution.

### bfs

A collection of fixed-size bit field objects that provide bitset-like functionality with more predictable compile-time behavior. The bfs family is available in predefined sizes:

* `udt::bfs_8`
* `udt::bfs_16`
* `udt::bfs_32`
* `udt::bfs_64`

### multidimensional

A set of libraries and objects that provide multidimensional arrays and vectors, including types such as:

* `udt::vector`
* `udt::vector_2d`
* `udt::vector_3d`

These components simplify the representation and manipulation of data in multiple dimensions.

And many more unique data types are included throughout the openUDT ecosystem.

## Foundation

openUDT is built on top of **metaCore**, which provides the foundational utilities and infrastructure required by the library collection.

**note:** this project uses the namespace `udt`
