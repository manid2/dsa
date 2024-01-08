=================================
SDE General topics for interviews
=================================

Genenral SDE topics to prepare for software engineering interviews.

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

Operating system (Linux)
========================

* Scheduler: Round Robin, Time slicing.
* Memory management: NUMA & UMA.
* Cache management: LRU.
* Multiple threads: synchronization & safety.

DPDK
====

* Why dpdk is used instead of operating system network stack.
* Example APIs.

Network stack
=============

* Network layers: TCP/IP network layers.
* Protocols: HTTP, SIP, SSH, TCP, UDP, IP, Ethernet, WiFi.
* Architectures: REST, SOAP, RPC.

Distributed computing
=====================

* Multi node programs.

Python programming
==================

* Generators.
* Lists.
* Dictionary or maps.
* Object oriented programming concepts.
* Garbage collector.
* Memory management.

Database
========

* Relational (SQL): PostgreSQL.
* Non-Relational (NoSQL): MongoDB.

Cpp language
============

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

Cpp system
==========

* Using ``std::thread`` joining, detaching, passing arguments to a thread by
  reference; handling exceptions etc.
* Using ``std::condition_variable`` be able to recognize a situation and use
  it, alternative etc.
* ``std::mutex``, ``std::recursive_mutex``, ``std::shared_mutex`` provide
  scenarios of their realistic usage.
* ``std::once_flag`` how to use it.
* ``std::atomic`` - be able to explain some common use-cases, problems etc.
* ``std::future``, ``std::shared_future``, ``std::promise``,
  ``std::packaged_task`` theoretical knowledge and possible problems
  description.
* How to use std::bind, std::async and for what cases.
* Thread pool implementation.
* Some skills in debugging multithreaded applications.

Tools
=====

* GDB from command-line (including coredumps analysis).
* Unix make
* CMake
* Git
* Docker
