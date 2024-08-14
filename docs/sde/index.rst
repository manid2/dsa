=================================
SDE General topics for interviews
=================================

General SDE topics to prepare for software engineering interviews.

C programming
=============

* Memory layout.
* Storage classes: scope and visibility of variables.
* Structure padding.
* Structure Bit fields.
* Pointer arithmetic.
* Operator precedence.
* Function pointers.
* Memory allocation routines: ``malloc ()``, ``calloc ()`` & ``realloc ()``.
* Memory routines: ``memcpy ()``, ``memmove ()``, & ``memset ()``.
* String routines: ``strncpy ()``, ``strcat ()``, & ``strlen ()``.

Python programming
==================

* Generators.
* Lists.
* Dictionary or maps.
* Object oriented programming concepts.
* Garbage collector.
* Memory management.

Operating system (Linux)
========================

* Multiple threads: synchronization & safety.
* Memory management: NUMA, UMA, own malloc implementation.
* Cache management: LRU.
* Scheduler: Round Robin, Time slicing.

DPDK
====

* Why dpdk is used instead of operating system network stack.
* Example APIs, mbuf data structures, lcore management.
* HugePages.

Network stack
=============

* Network layers: TCP/IP network layers.
* Protocols: HTTP, SIP, SSH, TCP, UDP, IP, Ethernet, WiFi.
* Architectures: REST, SOAP, RPC.

Database
========

* Relational (SQL): PostgreSQL.
* Non-Relational (NoSQL): MongoDB.

C++ programming
===============

* Construction and Destruction order.
* Virtual destructor role.
* How to override functions, avoid incorrect overriding.
* Different ways to initialize class members if they don't have a default
  constructor.
* Tell the difference between static local, static unit-private, global,
  ``extern`` variables.
* ``volatile`` variables.
* Anonymous namespaces.
* Static variables initialization in one compilation unit, in exe-file, in
  shared-library.
* Linkage types.
* Optimization techniques.
* Move-semantics.
* Using Standard Template Library algorithms and structures.
* Recognize problematic cases with ``std::shared_ptr``.
* Explain when to use ``std::shared_ptr``, ``std::unique_ptr``,
  ``std::weak_ptr``.
* Smart pointers in multi-threaded environment.
* Be familiar with the exception safety levels and be able to provide related
  examples.
* Explain pros and cons of throwing from a constructor.
* Explain main problems of throwing from a destructor.
* SOLID, DRY, KISS, SFINAE (Substitution Failure Is Not An Error) principles.
