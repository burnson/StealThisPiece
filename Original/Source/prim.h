/*
  ==============================================================================

  Copyright 2007-2012 Andi Brae. All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

     1. Redistributions of source code must retain the above copyright notice,
        this list of conditions and the following disclaimer.

     2. Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY ANDI BRAE ''AS IS'' AND ANY EXPRESS
  OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
  EVENT SHALL ANDI BRAE OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
  OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

  The views and conclusions contained in the software and documentation are
  those of the authors and should not be interpreted as representing official
  policies, either expressed or implied, of Andi Brae.

  ------------------------------------------------------------------------------

  This file is part of prim.cc -- the one file C++ library with serious style.
  Generated on:  2012-02-05 at 15:36 -0600
  Permalink:     http://prim.cc/old/prim20120205.h
  Documentation: http://prim.cc/doc

  To use:
  1) #include "prim.h" in your main file and #define PRIM_COMPILE_INLINE above.
  2) #include "prim.h" in your other files.
  3) Optionally, above all #include "prim.h" statements,
     #define PRIM_WITH_MODULES to activate modules or
     #define PRIM_WITH_[ModuleName] for specific modules listed below.

  ==============================================================================
*/

#ifndef PRIM_H
#define PRIM_H

//Header includes all the prim files grouped by stages and modules.

//............................................................................//

/*External support headers from the C++ standard library are included here in
alphabetical order. Note that these are only activated in the source in which
prim is compiled. The global namespace will be clean in all other sources. Note
as well that only the headers without .h are included here. These are the
portable headers. Non-portable or compiler-specific headers are included in
modules instead.*/
#ifdef PRIM_COMPILE_INLINE
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#endif

//............................................................................//

//Include the following modules automatically.
#define PRIM_WITH_PLANAR
#define PRIM_WITH_XML

//If all modules are requested then set the remaining module defines.
#ifdef PRIM_WITH_MODULES
#define PRIM_WITH_FFT
#define PRIM_WITH_GRAPH
#define PRIM_WITH_MD5
#define PRIM_WITH_SERIALIZATION
#define PRIM_WITH_THREAD
#define PRIM_WITH_TIMER
#endif

//Set module dependencies.
#if defined(PRIM_WITH_GRAPH) && !defined(PRIM_WITH_SERIALIZATION)
#define PRIM_WITH_SERIALIZATION
#endif

#if defined(PRIM_WITH_SERIALIZATION) && !defined(PRIM_WITH_MD5)
#define PRIM_WITH_MD5
#endif

#if 1 //........MOVE MATCHING ENDIF TO INCLUDE A SUBSET OF THE LIBRARY........//

/*Higher level stages depend on lower level stages. Thus if you want to only
bring in part of the library for your project, you can just not include higher
level stages or modules. Within a stage headers do not depend on each other. The
ordering is by lowest to highest stage, then alphabetical within each stage.*/

//............................................................................//

#ifndef PRIM_ENVIRONMENT_H
#define PRIM_ENVIRONMENT_H

//The big picture: Windows or POSIX?
#if defined(WINDOWS) || defined(WIN32) || defined(_WIN32) || defined(_WIN64)
  //Windows XP and later (32-bit or 64-bit)
  #define PRIM_ENVIRONMENT_WINDOWS

  //Among Windows: 32-bit or 64-bit?
  #if defined(_WIN64)
    //64-bit Windows
    #define PRIM_ENVIRONMENT_WINDOWS_64
  #else
    //32-bit Windows
    #define PRIM_ENVIRONMENT_WINDOWS_32
  #endif
#else
  //GNU/Linux, BSD, Mac OS X, iOS, Android and variants
  #define PRIM_ENVIRONMENT_POSIX
#endif

//Is it an Apple platform?
#if defined(__APPLE__)
  //Mac OS X (iMac, MacBook variants, Mac mini) or iOS (iPhone and iPad)
  #define PRIM_ENVIRONMENT_APPLE
#endif

//Is it a GNU/Linux variant?
#if defined(__linux__)
  #define PRIM_ENVIRONMENT_GNULINUX
#endif

//Is it a BSD variant?
#if defined(BSD)
  #define PRIM_ENVIRONMENT_BSD
#endif

//What is the data model?
#if defined(PRIM_ENVIRONMENT_WINDOWS_64)
  //Model LLP64: int = long = 4 bytes, long long = 8 bytes, pointers = 8 bytes
  #define PRIM_ENVIRONMENT_LLP64
#elif defined (__LP64__) || defined (_LP64)
  //Model LP64: int = 4 bytes, long = long long = 8 bytes, pointers = 8 bytes
  #define PRIM_ENVIRONMENT_LP64
#else
  //Model ILP32: int = long = 4 bytes, long long = 8 bytes, pointers = 4 bytes
  #define PRIM_ENVIRONMENT_ILP32
#endif

//What is the endianness?
#if defined(PRIM_ENVIRONMENT_WINDOWS) || defined(__LITTLE_ENDIAN__) || \
  !(defined(_BIG_ENDIAN) || defined(__BIG_ENDIAN__))
  //Little-endian
  #define PRIM_ENVIRONMENT_LITTLE_ENDIAN
#else
  //Big-endian
  #define PRIM_ENVIRONMENT_BIG_ENDIAN
#endif

namespace prim
{
  /**Inspects the current build environment.
  - Platform:
    - PRIM_ENVIRONMENT_WINDOWS
      - PRIM_ENVIRONMENT_WINDOWS_32
      - PRIM_ENVIRONMENT_WINDOWS_64
    - PRIM_ENVIRONMENT_POSIX
      - PRIM_ENVIRONMENT_APPLE
      - PRIM_ENVIRONMENT_BSD
      - PRIM_ENVIRONMENT_GNULINUX
  - Data Model:
    - PRIM_ENVIRONMENT_ILP32
    - PRIM_ENVIRONMENT_LP64
    - PRIM_ENVIRONMENT_LLP64
  - Endianness:
    - PRIM_ENVIRONMENT_BIG_ENDIAN
    - PRIM_ENVIRONMENT_LITTLE_ENDIAN
  */
  struct Environment
  {
    ///Prints all environment definitions in effect to diagnose porting issues.
    static void Print(void);
  };
}
#ifdef PRIM_COMPILE_INLINE
#include <iostream>
namespace prim
{
  void Environment::Print(void)
  {
    std::cout << " Compiler-Detected Environment \n";
    std::cout << "-------------------------------\n";
    #ifdef PRIM_ENVIRONMENT_WINDOWS
    std::cout << "PRIM_ENVIRONMENT_WINDOWS\n";
    #endif
    #ifdef PRIM_ENVIRONMENT_WINDOWS_32
    std::cout << "PRIM_ENVIRONMENT_WINDOWS_32\n";
    #endif
    #ifdef PRIM_ENVIRONMENT_WINDOWS_64
    std::cout << "PRIM_ENVIRONMENT_WINDOWS_64\n";
    #endif
    #ifdef PRIM_ENVIRONMENT_POSIX
    std::cout << "PRIM_ENVIRONMENT_POSIX\n";
    #endif
    #ifdef PRIM_ENVIRONMENT_APPLE
    std::cout << "PRIM_ENVIRONMENT_APPLE\n";
    #endif
    #ifdef PRIM_ENVIRONMENT_BSD
    std::cout << "PRIM_ENVIRONMENT_BSD\n";
    #endif
    #ifdef PRIM_ENVIRONMENT_GNULINUX
    std::cout << "PRIM_ENVIRONMENT_GNULINUX\n";
    #endif
    #ifdef PRIM_ENVIRONMENT_ILP32
    std::cout << "PRIM_ENVIRONMENT_ILP32\n";
    #endif
    #ifdef PRIM_ENVIRONMENT_LP64
    std::cout << "PRIM_ENVIRONMENT_LP64\n";
    #endif
    #ifdef PRIM_ENVIRONMENT_LLP64
    std::cout << "PRIM_ENVIRONMENT_LLP64\n";
    #endif
    #ifdef PRIM_ENVIRONMENT_BIG_ENDIAN
    std::cout << "PRIM_ENVIRONMENT_BIG_ENDIAN\n";
    #endif
    #ifdef PRIM_ENVIRONMENT_LITTLE_ENDIAN
    std::cout << "PRIM_ENVIRONMENT_LITTLE_ENDIAN\n";
    #endif
  }
}
#endif
#endif

#ifndef PRIM_TYPES_H
#define PRIM_TYPES_H

/** \file
Standardizes the library intrinsic types according to their purpose. For
example, sometimes you need a data type of an exact number of bytes. Other times
you need mathematical precision or simply the ability to count things. In
general, you do not need to worry about this file unless you are compiling on a
non-standard compiler or platform. The purpose of using standardized data types
is to make prim portable and understandable.

The three customizable types are prim::count (at least the size of a pointer),
prim::integer (a big integer), and prim::number (a precise number). You can
change what these mean by changing their type definitions below.*/

/*
.............................................................
.                    Standard Data Models                   .
.............................................................
. Model .  char . short . int . long . long long . pointers .
.............................................................
. ILP32 .   1   .   2   .  4  .  4   .     8     .    4     .
. LP64  .   1   .   2   .  4  .  8   .     8     .    8     .
. LLP64 .   1   .   2   .  4  .  4   .     8     .    8     .
. ILP64 .   1   .   2   .  8  .  8   .     8     .    8     .
.............................................................

Note that short is the same as short int, long as long int, and long long as
long long int.

More information on cross-platform issues and data models:
http://en.wikipedia.org/wiki/64-bit
http://www.unix.org/version2/whatsnew/lp64_wp.html

In this header file the data models are referred to by number:

#  Data Model  System
-  ----------  ------
1  ILP32       Most 32-bit systems
2  LP64        Linux/Mac OS X 64-bit systems
3  LLP64       Windows 64-bit systems
4  ILP64       Rare and untested; needs clarification for 32-bit types
*/

namespace prim
{
  //------------------------//
  //Fixed Byte Integer Types//
  //------------------------//

  /**An unsigned 8-bit integer
  \code
  *  uint8 a1 = 100, a2 = (uint8)300, a3 = (uint8)-300;
  *  c >> a1 << ", " << a2 << ", " << a3;
  \endcode
  */
  typedef unsigned char uint8;

  /**A signed 8-bit integer
  \code
  *  int8 a1 = 65, a2 = 66, a3 = 67;
  *  c >> a1 << ", " << a2 << ", " << a3;
  \endcode
  */
  typedef char int8;

  /**An unsigned 16-bit integer
  \code
  *  uint16 a1 = 1000, a2 = (uint16)40000, a3 = (uint16)-40000;
  *  c >> a1 << ", " << a2 << ", " << a3;
  \endcode
  */
  typedef unsigned short uint16;

  /**A signed 16-bit integer
  \code
  *  int16 a1 = 1000, a2 = (int16)40000, a3 = (int16)-40000;
  *  c >> a1 << ", " << a2 << ", " << a3;
  \endcode
  */
  typedef short int16;

  /**An unsigned 32-bit integer
  \code
  *  uint32 a1 = 1000000000LL, a2 = (uint32)5000000000LL,
  *    a3 = (uint32)-5000000000LL;
  *  c >> a1 << ", " << a2 << ", " << a3;
  \endcode
  */
  typedef unsigned int uint32;

  /**A signed 32-bit integer
  \code
  *  int32 a1 = 1000000000LL, a2 = (int32)5000000000LL,
  *    a3 = (int32)-5000000000LL;
  *  c >> a1 << ", " << a2 << ", " << a3;
  \endcode
  */
  typedef int int32;

  /*While a long long is 8-bytes for all data models, we want to avoid compiling
  with the long long type when we can just compile with long due to portability
  concerns. For example, long long requires the C99 extensions in GNU g++.*/
#ifdef PRIM_ENVIRONMENT_LP64
  /**A signed 64-bit integer
  \code
  *  int64 a1 = 1000000000LL, a2 = (int64)5000000000LL,
  *    a3 = (int64)-5000000000LL;
  *  c >> a1 << ", " << a2 << ", " << a3;
  \endcode
  */
  typedef long int64;

  /**An unsigned 64-bit integer
  \code
  *  uint64 a1 = 1000000000LL, a2 = (uint64)(void*)&a1,
  *    a3 = (uint64)(-(int64)a2);
  *  c >> a1 << ", " << a2 << ", " << a3;
  *  c >> &a1 << ", " << &a2 << ", " << &a3;
  \endcode
  */
  typedef unsigned long uint64;
#else

  typedef long long int64;
  typedef unsigned long long uint64;
#endif

  //--------------------//
  //Floating-Point Types//
  //--------------------//

  /**A 32-bit single precision floating point type
  \code
  *  c >> "float32 has " << Precision<float32>() << " bits of precision";
  \endcode
  */
  typedef float float32;

  /**A 64-bit single precision floating point type
  \code
  *  c >> "float64 has " << Precision<float64>() << " bits of precision";
  \endcode
  */
  typedef double float64;

  /**An 80-bit float for compilers supporting x87 extended precision.  Support
  for this type can vary a great deal from platform to platform.
  \code
  *  c >> "float80 has " << Precision<float80>() << " bits of precision";
  \endcode
  */
  typedef long double float80;

  //-------------------------//
  //Counting and Memory Types//
  //-------------------------//

#ifdef PRIM_ENVIRONMENT_ILP32
  /**A signed counting integer at least the size of a pointer.
  \code
  *  for(count i = 0; i < 10; i++)
  *    c += "Hello!";
  \endcode
  */
  typedef int32 count; //CUSTOMIZE HERE: Use int64 if you like.

  /**An unsigned integer the size of a pointer. Only low-level memory
  operations make use of this type.
  \code
  *  uintptr a = (uintptr)(void*)&a;
  *  c += "Value of a: "; c << a;
  *  c += "Address of a: "; c << &a;
  \endcode
  */
  typedef uint32 uintptr;
#else
  typedef int64 count;
  typedef uint64 uintptr;
#endif

  //------------------//
  //Mathematical Types//
  //------------------//

  /**A data type for doing general purpose math with integers.
  \code
  *  integer a = 1;
  *  for(count i = 1; i <= 20; i++)
  *    a *= (integer)i;
  *  c += "20! = "; c << a;
  \endcode
  */
  typedef int64 integer; //CUSTOMIZE HERE: Use int32 if you like.

  /**A data type for doing general purpose math with floating-point numbers.
  \code
  *  number root1 = 0, root2 = 0;
  *  {
  *    number a = 1, b = -2, c = -3;
  *    root1 = (-b + Sqrt(Square(b) - 4 * a * c)) / (2 * a);
  *    root2 = (-b - Sqrt(Square(b) - 4 * a * c)) / (2 * a);
  *  }
  *  c += "Roots of x^2 - 2x - 3 = 0:";
  *  c += "root1 = "; c << root1;
  *  c += "root2 = "; c << root2;
  \endcode
  */
  typedef float64 number; //CUSTOMIZE HERE: Use float32 if you like.

  ///Returns the actual mantissa precision of a float type.
  template <typename FloatT> count Precision(void)
  {
    FloatT Original = (FloatT)1;
    FloatT Delta = (FloatT)1;
    count BitsPrecision = 0;
    while(Original + Delta != Original)
    {
      Delta /= (FloatT)2;
      BitsPrecision++;
    }

    return BitsPrecision;
  }

  //--------------------//
  //ASCII Character Type//
  //--------------------//

  /**A signed eight-bit integer used for storing low-level char strings
  \code
  *  const ascii* SomeString = "Hello there!";
  *  c += SomeString;
  \endcode
  */
  typedef int8 ascii; //Do not change this!

  //----------------------//
  //Unicode Character Type//
  //----------------------//
  /**Four-byte character code capable of representing any Unicode codepoint
  \code
  *  c >> "Example forthcoming...";
  \endcode
  */
  typedef uint32 unicode; //Do not change this!

  //----------------//
  //Binary Data Type//
  //----------------//

  /**An unsigned eight-bit integer used for storing low-level binary data
  \code
  *  byte SomeByteArray[10];
  *  for(count i = 0; i < 10; i++)
  *    SomeByteArray[i] = (byte)(i * 100);
  *  for(count i = 0; i < 10; i++)
  *    c >> "SomeByteArray[" << i << "] = " << SomeByteArray[i];
  \endcode
  */
  typedef uint8 byte; //Do not change this!
}

//---------//
//Constants//
//---------//

namespace prim { namespace meta
{
  //Minimums and maximums
  static const int8 int8Max = 127;
  static const int8 int8Min = -128;
  static const uint8 uint8Max = 255;
  static const int16 int16Min = -32768;
  static const int16 int16Max = 32767;
  static const uint16 uint16Max = 65535;
  static const int32 int32Min = -2147483647 - 1;
  static const int32 int32Max = 2147483647;
  static const uint32 uint32Max = 0xFFFFFFFFU;
#ifdef PRIM_ENVIRONMENT_ILP32
  static const int64 int64Min = -0x7FFFFFFFFFFFFFFFLL - 1LL;
  static const int64 int64Max = 0x7FFFFFFFFFFFFFFFLL;
  static const uint64 uint64Max = 0xFFFFFFFFFFFFFFFFULL;
#else
  static const int64 int64Min = -0x7FFFFFFFFFFFFFFFL - 1L;
  static const int64 int64Max = 0x7FFFFFFFFFFFFFFFL;
  static const uint64 uint64Max = 0xFFFFFFFFFFFFFFFFUL;
#endif

  //Pointer properties
#ifdef PRIM_ENVIRONMENT_ILP32
  static const count PointerBytes = 4;
  static const count PointerBits = 32;
  static const count PointerBytesLog2 = 2;
  static const uintptr PointerHighBit = (uintptr)int32Min;
#else
  static const count PointerBytes = 8;
  static const count PointerBits = 64;
  static const count PointerBytesLog2 = 3;
  static const uintptr PointerHighBit = (uintptr)int64Min;
#endif
}}
#endif

//............................................................................//

#ifndef PRIM_ENDIAN_H
#define PRIM_ENDIAN_H

namespace prim
{
  ///Checks endianness to make requested endianness conversions.
  struct Endian
  {
    ///Returns true if the system is little-endian (low-to-high).
    static inline bool IsLittleEndian(void)
    {
#ifdef PRIM_ENVIRONMENT_LITTLE_ENDIAN
      return true;
#else
      return false;
#endif
    }

    ///Reverses the byte order of any complex data type.
    template <class T>
    static void ReverseOrder(T& Value)
    {
      T NewValue = 0;
      uint8* OldPointer = (uint8*)&Value;
      uint8* NewPointer = (uint8*)&NewValue;

      for(count i = 0; i < (count)sizeof(T); i++)
        NewPointer[i] = OldPointer[sizeof(T) - i - 1];

      Value = NewValue;
    }

    ///Ensures that a value is stored in little-endian.
    template <class T>
    static void ConvertToLittleEndian(T& Value)
    {
      if(!IsLittleEndian())
        ReverseOrder(Value);
    }

    ///Ensures that a value is stored in big-endian.
    template <class T>
    static void ConvertToBigEndian(T& Value)
    {
      if(IsLittleEndian())
        ReverseOrder(Value);
    }

    ///Ensures that an array of items is stored in little-endian.
    template <class T>
    static void ConvertToLittleEndian(T* ItemArray, count ItemCount)
    {
      if(!IsLittleEndian())
        for(count i = 0; i < ItemCount; i++)
          ReverseOrder(ItemArray[i]);
    }

    ///Ensures that an array of items is stored in big-endian.
    template <class T>
    static void ConvertToBigEndian(T* ItemArray, count ItemCount)
    {
      if(IsLittleEndian())
        for(count i = 0; i < ItemCount; i++)
          ReverseOrder(ItemArray[i]);
    }
  };
}
#endif

#ifndef PRIM_MEMORY_H
#define PRIM_MEMORY_H

/** \file
Provides a wrapper for memory operations via the Memory class.*/

namespace prim
{
  /**Wrapper for clearing and copying memory via templated methods.

  Also provides a templated placement new. You should only use the Clear and
  Copy methods on plain-old data objects, that is, objects not containing
  members with their own special constructors or containing virtual methods (and
  thus a vtable which would be wiped out).*/
  struct Memory
  {
    ///Private wrapper for memset. Use Clear instead since it is strongly typed.
    static void MemSet(void* Destination, byte ValueToSet, count BytesToSet);
    //(see prim.cpp for implementation)

    ///Private wrapper for memcpy. Use Copy instead since it is strongly typed.
    static void MemCopy(void* Destination, void* Source, count BytesToCopy);
    //(see prim.cpp for implementation)

    ///Clears an object with a particular byte-value.
    template <class T>
    static void Clear(T& Object, byte Value = 0)
    {
      MemSet((void*)&Object, Value, sizeof(T));
    }

    ///Clears an array of consecutive objects with a particular byte-value.
    template <class T>
    static void Clear(T* Object, count Items, byte Value = 0)
    {
      MemSet((void*)Object, Value, sizeof(T) * Items);
    }

    ///Copies an object's data to another object.
    template <class T>
    static void Copy(T& Destination, const T& Source)
    {
      MemCopy((void*)&Destination, (void*)&Source, sizeof(T));
    }

    ///Copies an array of consecutive objects to another array.
    template <class T>
    static void Copy(T* Destination, const T* Source, count Items)
    {
      MemCopy((void*)Destination, (void*)Source, sizeof(T) * Items);
    }

    /**Calls a placement new on an object. A placement new is used to call an
    object's constructor in the case that the memory for the object has already
    been allocated. To use this method you will need to include &lt;new&gt;
    before you include prim.h.*/
    template <class T>
    static T* PlacementNew(T* Object)
    {
      return new (Object) T;
    }

    /**Safely swaps two objects of the same type using an intermediate object.
    This requires a default constructor and a copy constructor for the temporary
    placeholder as well as an assignment operator if the type is a class.*/
    template <class T>
    static void Swap(T& a, T& b)
    {
      T c = a;
      a = b;
      b = c;
    }

    /**Iterates through two arrays of the same type and size safely swapping
    their elements using an intermediate object. Internally calls Swap(a, b).*/
    template <class T>
    static void Swap(T* a, T* b, count Items)
    {
      for(count i = 0; i < Items; i++)
        Swap(a[i], b[i]);
    }

    ///Swaps the memory of a single object. Internally calls Swap(a, b, Items).
    template <class T>
    static void SwapMemory(T& a, T& b)
    {
      SwapMemory(&a, &b, 1);
    }

    /**Swaps the memory of two arrays using an un-typed temporary buffer. By
    doing this you avoid the construction-destruction of the temporary, as well
    as the assignment operator. Obviously, you must be careful to do this only
    when the result is defined. The regions of memory may not overlap.*/
    template <class T>
    static void SwapMemory(T* a, T* b, count Items)
    {
      if(a == b)
        return;

      const count BufferSize = 1024;
      byte Buffer[BufferSize];
      byte* a_byte = (byte*)a;
      byte* b_byte = (byte*)b;
      count BytesToSwap = sizeof(T) * Items;
      while(BytesToSwap > 0)
      {
        count BytesToCopy = BytesToSwap < BufferSize ? BytesToSwap : BufferSize;
        Copy(&Buffer[0], a_byte, BytesToCopy);
        Copy(a_byte, b_byte, BytesToCopy);
        Copy(b_byte, &Buffer[0], BytesToCopy);
        a_byte += BytesToCopy;
        b_byte += BytesToCopy;
        BytesToSwap -= BytesToCopy;
      }
    }
  };

#ifdef PRIM_COMPILE_INLINE
  void Memory::MemSet(void* Destination, uint8 ValueToSet, count BytesToSet)
  {
    if(Destination != 0 && BytesToSet > 0)
      memset(Destination, ValueToSet, BytesToSet);
  }

  void Memory::MemCopy(void* Destination, void* Source, count BytesToCopy)
  {
    if(Destination != 0 && Source != 0 && BytesToCopy > 0)
      memcpy(Destination, Source, BytesToCopy);
  }
#endif
}
#endif

#ifndef PRIM_MATH_H
#define PRIM_MATH_H

namespace prim
{
  //---------//
  //Constants//
  //---------//

  extern const float80 Deg;
  extern const float80 E;
  extern const float80 Pi;
  extern const float80 TwoPi;
  extern const float80 HalfPi;
  extern const float80 Log2Inv;

  //---------------------//
  //Exponential Functions//
  //---------------------//

  ///Returns the exponential of x.
  float32 Exp(float32 x);

  ///Returns the exponential of x.
  float64 Exp(float64 x);

  ///Returns the exponential of x.
  float80 Exp(float80 x);

  ///Returns x to the power y.
  float32 Power(float32 x, float32 y);

  ///Returns x to the power y.
  float64 Power(float64 x, float64 y);

  ///Returns x to the power y.
  float80 Power(float80 x, float80 y);

  ///Returns the natural logarithm of x.
  float32 Log(float32 x);

  ///Returns the natural logarithm of x.
  float64 Log(float64 x);

  ///Returns the natural logarithm of x.
  float80 Log(float80 x);

  ///Returns the logarithm of x to base b.
  float32 Log(float32 b, float32 x);

  ///Returns the logarithm of x to base b.
  float64 Log(float64 b, float64 x);

  ///Returns the logarithm of x to base b.
  float80 Log(float80 b, float80 x);

  ///Returns the base-2 logarithm of x.
  float32 Log2(float32 x);

  ///Returns the base-2 logarithm of x.
  float64 Log2(float64 x);

  ///Returns the base-2 logarithm of x.
  float80 Log2(float80 x);

  ///Returns the base-10 logarithm of x.
  float32 Log10(float32 x);

  ///Returns the base-10 logarithm of x.
  float64 Log10(float64 x);

  ///Returns the base-10 logarithm of x.
  float80 Log10(float80 x);

  ///Returns the square root of x.
  float32 Sqrt(float32 x);

  ///Returns the square root of x.
  float64 Sqrt(float64 x);

  ///Returns the square root of x.
  float80 Sqrt(float80 x);

  //----------------//
  //Bessel Functions//
  //----------------//

  ///Computes the zeroth-order modified Bessel function of the first kind of z.
  template<typename FloatT> FloatT BesselI0(FloatT z)
  {
    /*The BesselI[0, z] function, also known as the zeroth-order modified Bessel
    function of the first kind, is defined by:

            oo                    oo
            __  (z ^ 2 / 4) ^ k   __  [(z / 2) ^ k ]
    I0(z) = \   _______________ = \   |____________| ^ 2  =
            /_     (k!) ^ 2       /_  [     k!     ]

           k = 0                 k = 0

               oo                            oo
               __  [(z / 2) ^ k ]            __
          1 +  \   |____________| ^ 2  = 1 + \   P_z[k] ^ 2, where
               /_  [     k!     ]            /_

              k = 1                         k = 1

                                z / 2
          P_z[k] = P_z[k - 1] * -----, P_z[0] = 1
                                  k

    We note that the function is evenly symmetric and I0(0) = 1 is the function
    minimum. The function grows monotonically at an exponential pace. I0(700) is
    above 10^300, and since this is the near the limit of the double floating-
    point arithmetic, the valid domain of this numeric function is [-700, 700].

    The numerical accuracy of the function depends on the value of z chosen, but
    it appears that over the given range 15 decimal digit accuracy is typical in
    double arithmetic. The approach taken is to continue the summation so long
    as it has an effect on the output. When the number added is too small to
    affect the result, the loop exits. Since the formula is well-conditioned,
    there should not be any input in the domain which would not eventually exit.
    Still, in case there is some number that could cause this to occur, a
    conservative value of 1000 summations is used to prevent a dead-lock. It was
    calculated that the maximum number of summations before total convergence is
    465 in double arithmetic. Note as well that the number of summations is
    essentially proportional to the input z:

    Summations ~= 3 + z * 0.66.

    Note that in the Kaiser window which uses this Bessel function, the domain
    used is [0, beta], where beta is the alpha-pi constant that determines the
    window's sidelobe attenuation. For example, a beta of 20 (i.e., a Kaiser-20
    window) has sidelobe attenuation of about -190 dB.

    Source:
    http://mathworld.wolfram.com/ModifiedBesselFunctionoftheFirstKind.html
    http://en.wikipedia.org/wiki/Kaiser_window
    */

    /*1) The function is evenly symmetric, so to make things simpler, wrap the
    domain so that it is always used positively.*/
    if(z < 0.)
      z = -z;

    //2) Simple case: for z = 0, the result is exactly 1.
    if(z == 0.)
      return 1.;

    //Set initial conditions.
    FloatT z_Half = z * 0.5, Result = 1.0, PreviousResult = 0.0,
      Pz_k = 1.0, k = 1.0;

    /*Calculate until the series converges on a single decimal value. This
    happens because at some point a very small number is added to a large number
    and there is no change. This event causes the loop to stop. The loop
    continues so long as the floating-point representation does not change. In
    this case, its representation is casted to a uint64 to prevent a floating-
    point not-equal-to comparison.*/
    while(PreviousResult != Result && k < 1000.)
    {
      PreviousResult = Result;
      Pz_k = Pz_k * (z_Half / k++);
      Result += Pz_k * Pz_k;
    }
    return Result;
  }

  //-----------------------//
  //Trigonometric Functions//
  //-----------------------//

  ///Returns the sine of x.
  float32 Sin(float32 x);

  ///Returns the sine of x.
  float64 Sin(float64 x);

  ///Returns the sine of x.
  float80 Sin(float80 x);

  ///Returns the cosine of x.
  float32 Cos(float32 x);

  ///Returns the cosine of x.
  float64 Cos(float64 x);

  ///Returns the cosine of x.
  float80 Cos(float80 x);

  ///Returns the tangent of x.
  float32 Tan(float32 x);

  ///Returns the tangent of x.
  float64 Tan(float64 x);

  ///Returns the tangent of x.
  float80 Tan(float80 x);

  ///Returns the sine of x.
  float32 ArcSin(float32 x);

  ///Returns the sine of x.
  float64 ArcSin(float64 x);

  ///Returns the sine of x.
  float80 ArcSin(float80 x);

  ///Returns the cosine of x.
  float32 ArcCos(float32 x);

  ///Returns the cosine of x.
  float64 ArcCos(float64 x);

  ///Returns the cosine of x.
  float80 ArcCos(float80 x);

  ///Returns the cosine of x.
  float32 ArcTan(float32 x);

  ///Returns the cosine of x.
  float64 ArcTan(float64 x);

  ///Returns the cosine of x.
  float80 ArcTan(float80 x);

  ///Returns the sinc of x.
  template<typename FloatT>
  FloatT Sinc(FloatT x)
  {
    if(x == (FloatT)0.0)
      return (FloatT)1.0;
    return Sin(x) / x;
  }

  //------------------------------//
  //Floors, Ceilings, and Rounding//
  //------------------------------//

  ///Returns the greatest integer less than or equal to x.
  integer Floor(float32 x);

  ///Returns the greatest integer less than or equal to x.
  integer Floor(float64 x);

  ///Returns the integer closest to x.
  integer Round(float32 x);

  ///Returns the integer closest to x.
  integer Round(float64 x);

  ///Returns the smallest integer greater than or equal to x.
  integer Ceiling(float32 x);

  ///Returns the smallest integer greater than or equal to x.
  integer Ceiling(float64 x);

  ///Returns the smallest power-of-two greater than or equal to x.
  float32 PowerOfTwoCeiling(float32 x);

  ///Returns the smallest power-of-two greater than or equal to x.
  float64 PowerOfTwoCeiling(float64 x);

  ///Returns the smallest power-of-two greater than or equal to m.
  int32 PowerOfTwoCeiling(int32 m);

  ///Returns the smallest power-of-two greater than or equal to m.
  int64 PowerOfTwoCeiling(int64 m);

  ///Returns the integer part of x.
  integer IntegerPart(float32 x);

  ///Returns the integer part of x.
  integer IntegerPart(float64 x);

  ///Returns the fractional part of x.
  float32 FractionalPart(float32 x);

  ///Returns the fractional part of x.
  float64 FractionalPart(float64 x);

  ///Returns zero for x that are within delta of zero and returns x otherwise.
  float32 Chop(float32 x, float32 Delta);

  ///Returns zero for x that are within delta of zero and returns x otherwise.
  float64 Chop(float64 x, float64 Delta);

  ///Returns x clipped to be between min and max.
  float32 Clip(float32 x, float32 min, float32 max);

  ///Returns x clipped to be between min and max.
  float64 Clip(float64 x, float64 min, float64 max);

  //---------------------------------//
  //Sign, Absolute Value and Distance//
  //---------------------------------//

  ///Returns -1, 0 or 1 depending on whether x is negative, zero, or positive.
  float32 Sign(float32 x);

  ///Returns -1, 0 or 1 depending on whether x is negative, zero, or positive.
  float64 Sign(float64 x);

  ///Returns -1, 0 or 1 depending on whether m is negative, zero, or positive.
  int32 Sign(int32 m);

  ///Returns -1, 0 or 1 depending on whether m is negative, zero, or positive.
  int64 Sign(int64 m);

  ///Returns the absolute value of x.
  float32 Abs(float32 x);

  ///Returns the absolute value of x.
  float64 Abs(float64 x);

  ///Returns the absolute value of m.
  int32 Abs(int32 m);

  ///Returns the absolute value of m.
  int64 Abs(int64 m);

  ///Returns the absolute value of the vector {x, y}.
  float32 Abs(float32 x, float32 y);

  ///Returns the absolute value of the vector {x, y}
  float64 Abs(float64 x, float64 y);

  ///Returns the argument (principle angle) of the vector {x, y} over (-Pi, Pi].
  float32 Arg(float32 x, float32 y);

  ///Returns the argument (principle angle) of the vector {x, y} over (-Pi, Pi].
  float64 Arg(float64 x, float64 y);

  ///Returns the angle of the vector {x, y} over [0, 2*Pi).
  float32 Angle(float32 x, float32 y);

  ///Returns the angle of the vector {x, y} over [0, 2*Pi).
  float64 Angle(float64 x, float64 y);

  ///Returns the distance between the vectors {x1, y1} and {x2, y2}.
  float32 Distance(float32 x1, float32 y1, float32 x2, float32 y2);

  ///Returns the distance between the vectors {x1, y1} and {x2, y2}.
  float64 Distance(float64 x1, float64 y1, float64 x2, float64 y2);

  //-----------//
  //Polynomials//
  //-----------//

  count Roots(number a, number b, number& Root1);

  count Roots(number a, number b, number c, number& Root1, number& Root2);

  //------//
  //Modulo//
  //------//

  /**Returns the remainder on division of m by n. This modulo is defined to be
  cyclic for negative m, so that Mod(-1, 3) = 2.*/
  int32 Mod(int32 m, int32 n);

  /**Returns the remainder on division of m by n. This modulo is defined to be
  cyclic for negative m, so that Mod(-1, 3) = 2.*/
  int64 Mod(int64 m, int64 n);

  /**Returns the remainder on division of x by y. This modulo is defined to be
  cyclic for negative x, so that Mod(-1.0, 3.0) = 2.0.*/
  float32 Mod(float32 x, float32 y);

  /**Returns the remainder on division of x by y. This modulo is defined to be
  cyclic for negative x, so that Mod(-1.0, 3.0) = 2.0.*/
  float64 Mod(float64 x, float64 y);

  //-------------------------------//
  //Swapping, Minimums and Maximums//
  //-------------------------------//

  ///Swaps two things.
  template <class T> static void Swap(T& a, T& b)
  {
    T t = a;
    a = b;
    b = t;
  }

  ///Sorts two things in ascending order.
  template <class T> static void Ascending(T& a, T& b)
  {
    if(a > b)
      Swap(a, b);
  }

  ///Sorts two things in descending order.
  template <class T> static void Descending(T& a, T& b)
  {
    if(a < b)
      Swap(a, b);
  }

  ///Returns the greater of two values.
  template <class T> static T Max(const T& a, const T& b)
  {
    return a > b ? a : b;
  }

  ///Returns the lesser of two values.
  template <class T> static T Min(const T& a, const T& b)
  {
    return (a < b ? a : b);
  }

  ///Returns the square of a value.
  template <class T> static T Square(const T& a)
  {
    return a * a;
  }

  ///Returns the cube of a value.
  template <class T> static T Cube(const T& a)
  {
    return a * a * a;
  }

  ///Makes a at least the value of b.
  template <class T> static void MakeAtLeast(T& a, const T& b)
  {
    if(a < b)
      a = b;
  }

  ///Makes a at most the value of b.
  template <class T> static void MakeAtMost(T& a, const T& b)
  {
    if(a > b)
      a = b;
  }

  ///Returns whether c is inclusively between a and b.
  template <class T> static bool IsBetween(const T& c, const T& a,
    const T& b)
  {
    return (b >= a && c >= a && c <= b) || (a > b && c >= b && c <= a);
  }

#ifdef PRIM_COMPILE_INLINE
  const float80 Deg    = 0.017453292519943295769236907684886127134428718885417L;
  const float80 E       = 2.7182818284590452353602874713526624977572470937000L;
  const float80 Pi      = 3.1415926535897932384626433832795028841971693993751L;
  const float80 TwoPi   = 6.2831853071795864769252867665590057683943387987502L;
  const float80 HalfPi  = 1.5707963267948966192313216916397514420985846996876L;
  const float80 Log2Inv = 1.4426950408889634073599246810018921374266459541530L;

  //---------------------//
  //Exponential Functions//
  //---------------------//

  float32 Exp(float32 x)
  {
    return exp(x);
  }

  float64 Exp(float64 x)
  {
    return exp(x);
  }

  float80 Exp(float80 x)
  {
    return exp(x);
  }

  float32 Power(float32 x, float32 y)
  {
    return pow(x, y);
  }

  float64 Power(float64 x, float64 y)
  {
    return pow(x, y);
  }

  float80 Power(float80 x, float80 y)
  {
    return pow(x, y);
  }

  float32 Log(float32 x)
  {
    return log(x);
  }

  float64 Log(float64 x)
  {
    return log(x);
  }

  float80 Log(float80 x)
  {
    return log(x);
  }

  float32 Log(float32 b, float32 x)
  {
    return log(x) / log(b);
  }

  float64 Log(float64 b, float64 x)
  {
    return log(x) / log(b);
  }

  float80 Log(float80 b, float80 x)
  {
    return log(x) / log(b);
  }

  float32 Log2(float32 x)
  {
    return log(x) * (float32)Log2Inv;
  }

  float64 Log2(float64 x)
  {
    return log(x) * (float64)Log2Inv;
  }

  float80 Log2(float80 x)
  {
    return log(x) * (float80)Log2Inv;
  }

  float32 Log10(float32 x)
  {
    return log10(x);
  }

  float64 Log10(float64 x)
  {
    return log10(x);
  }

  float80 Log10(float80 x)
  {
    return log10(x);
  }

  float32 Sqrt(float32 x)
  {
    return sqrt(x);
  }

  float64 Sqrt(float64 x)
  {
    return sqrt(x);
  }

  float80 Sqrt(float80 x)
  {
    return sqrt(x);
  }

  //-----------------------//
  //Trigonometric Functions//
  //-----------------------//

  float32 Sin(float32 x)
  {
    return sin(x);
  }

  float64 Sin(float64 x)
  {
    return sin(x);
  }

  float80 Sin(float80 x)
  {
    return sin(x);
  }

  float32 Cos(float32 x)
  {
    return cos(x);
  }

  float64 Cos(float64 x)
  {
    return cos(x);
  }

  float80 Cos(float80 x)
  {
    return cos(x);
  }

  float32 Tan(float32 x)
  {
    return tan(x);
  }

  float64 Tan(float64 x)
  {
    return tan(x);
  }

  float80 Tan(float80 x)
  {
    return tan(x);
  }

  float32 ArcSin(float32 x)
  {
    return asin(x);
  }

  float64 ArcSin(float64 x)
  {
    return asin(x);
  }

  float80 ArcSin(float80 x)
  {
    return asin(x);
  }

  float32 ArcCos(float32 x)
  {
    return acos(x);
  }

  float64 ArcCos(float64 x)
  {
    return acos(x);
  }

  float80 ArcCos(float80 x)
  {
    return acos(x);
  }

  float32 ArcTan(float32 x)
  {
    return atan(x);
  }

  float64 ArcTan(float64 x)
  {
    return atan(x);
  }

  float80 ArcTan(float80 x)
  {
    return atan(x);
  }

  //------------------------------//
  //Floors, Ceilings, and Rounding//
  //------------------------------//

  integer Floor(float32 x)
  {
    return (integer)floor(x);
  }

  integer Floor(float64 x)
  {
    return (integer)floor(x);
  }

  integer Round(float32 x)
  {
    return Floor(x + 0.5f);
  }

  integer Round(float64 x)
  {
    return Floor(x + 0.5);
  }

  integer Ceiling(float32 x)
  {
    return (integer)ceil(x);
  }

  integer Ceiling(float64 x)
  {
    return (integer)ceil(x);
  }

  float32 PowerOfTwoCeiling(float32 x)
  {
    return (float32)Power(2.0f, (float32)Ceiling(Log2(Abs(x))));
  }

  float64 PowerOfTwoCeiling(float64 x)
  {
    return (float64)Power(2.0, (float64)Ceiling(Log2(Abs(x))));
  }

  int32 PowerOfTwoCeiling(int32 m)
  {
    return (int32)Power(2.0f, (float32)Ceiling(Log2((float32)Abs(m))));
  }

  int64 PowerOfTwoCeiling(int64 m)
  {
    return (int64)Power(2.0, (float64)Ceiling(Log2((float64)Abs(m))));
  }

  integer IntegerPart(float32 x)
  {
    if(x >= 0.0f)
      return Floor(x);
    else
      return Ceiling(x);
  }

  integer IntegerPart(float64 x)
  {
    if(x >= 0.0)
      return Floor(x);
    else
      return Ceiling(x);
  }

  float32 FractionalPart(float32 x)
  {
    if(x >= 0.0f)
      return Floor(x) - x;
    else
      return x - Ceiling(x);
  }

  float64 FractionalPart(float64 x)
  {
    if(x >= 0.0)
      return Floor(x) - x;
    else
      return x - Ceiling(x);
  }

  float32 Chop(float32 x, float32 Delta)
  {
    if(x > -Delta && x < Delta)
      return 0.0f;
    return x;
  }

  float64 Chop(float64 x, float64 Delta)
  {
    if(x > -Delta && x < Delta)
      return 0.0;
    return x;
  }

  float32 Clip(float32 x, float32 MinBound, float32 MaxBound)
  {
    if(x < MinBound)
      return MinBound;
    else if(x > MaxBound)
      return MaxBound;
    return x;
  }

  float64 Clip(float64 x, float64 MinBound, float64 MaxBound)
  {
    if(x < MinBound)
      return MinBound;
    else if(x > MaxBound)
      return MaxBound;
    return x;
  }

  //---------------------------------//
  //Sign, Absolute Value and Distance//
  //---------------------------------//

  float32 Sign(float32 x)
  {
    if(x > 0.0f)
      return 1.0f;
    else if(x < 0.0f)
      return -1.0f;

    return 0.0f;
  }

  float64 Sign(float64 x)
  {
    if(x > 0.0)
      return 1.0;
    else if(x < 0.0)
      return -1.0;

    return 0.0;
  }

  int32 Sign(int32 m)
  {
    if(m > 0)
      return 1;
    else if(m < 0)
      return -1;

    return 0;
  }

  int64 Sign(int64 m)
  {
    if(m > 0)
      return 1;
    else if(m < 0)
      return -1;

    return 0;
  }

  float32 Abs(float32 x)
  {
    return x >= 0.0f ? x : -x;
  }

  float64 Abs(float64 x)
  {
    return x >= 0.0 ? x : -x;
  }

  int32 Abs(int32 m)
  {
    return m >= 0 ? m : -m;
  }

  int64 Abs(int64 m)
  {
    return m >= 0 ? m : -m;
  }

  float32 Abs(float32 x, float32 y)
  {
    return sqrt(x * x + y * y);
  }

  float64 Abs(float64 x, float64 y)
  {
    return sqrt(x * x + y * y);
  }

  float32 Arg(float32 x, float32 y)
  {
    if(x == 0.0f && y == 0.0f)
      return 0.0f;
    else
      return atan2(y, x);
  }

  float64 Arg(float64 x, float64 y)
  {
    if(x == 0.0 && y == 0.0)
      return 0.0;
    else
      return atan2(y, x);
  }

  float32 Angle(float32 x, float32 y)
  {
    float32 Principle = Arg(x, y);
    if(Principle < 0.0f)
      Principle += 2.0f * (float32)Pi;
    return Principle;
  }

  float64 Angle(float64 x, float64 y)
  {
    float64 Principle = Arg(x, y);
    if(Principle < 0.0)
      Principle += 2.0 * Pi;
    return Principle;
  }

  float32 Distance(float32 x1, float32 y1, float32 x2, float32 y2)
  {
    float32 xd = x2 - x1, yd = y2 - y1;
    return sqrt(xd * xd + yd * yd);
  }

  float64 Distance(float64 x1, float64 y1, float64 x2, float64 y2)
  {
    float64 xd = x2 - x1, yd = y2 - y1;
    return sqrt(xd * xd + yd * yd);
  }

  //-----------//
  //Polynomials//
  //-----------//

  count Roots(number a, number b, number& Root1)
  {
    if(a != 0.0f)
    {
      Root1 = -b / a;
      return 1;
    }
    else
    {
      Root1 = 0.0f;
      return 0;
    }
  }

  count Roots(number a, number b, number c, number& Root1, number& Root2)
  {
    //Implemented according to the algorithm given at:
    //http://en.wikipedia.org/wiki/Quadratic_equation

    number DiscriminantSquared = b * b - 4 * a * c;
    if(DiscriminantSquared < 0)
    {
      Root1 = Root2 = 0;
      return 0;
    }

    number Discriminant = Sqrt(DiscriminantSquared);
    if(Discriminant > 0)
    {
      number t = -0.5f * (b + Sign(b) * Discriminant);
      if(t != 0)
      {
        Root1 = c / t;
        if(a != 0)
          Root2 = t / a;
        else
          return 1;
      }
      else
      {
        Root1 = (-b + Discriminant) * (number)0.5 * a;
        Root2 = (-b - Discriminant) * (number)0.5 * a;
      }
      Ascending(Root1, Root2);
      return 2;
    }
    else if(Discriminant == 0)
    {
      Root1 = (number)0.5 * b / a;
      Root2 = 0;
      return 1;
    }
    else
    {
      Root1 = 0;
      Root2 = 0;
      return 0;
    }
  }

  //------//
  //Modulo//
  //------//

  int32 Mod(int32 m, int32 n)
  {
    int32 n2 = Abs(n);

    if(n2 == 0)
      return -1;
    if(m < 0)
      return (n2 - (-m % n2)) * Sign(n);

    return (m % n2) * Sign(n);
  }

  int64 Mod(int64 m, int64 n)
  {
    int64 n2 = Abs(n);

    if(n2 == 0)
      return -1;
    if(m < 0)
      return (n2 - (-m % n2)) * Sign(n);

    return (m % n2) * Sign(n);
  }

  float32 Mod(float32 x, float32 y)
  {
    return (float32)Mod((float64)x, (float64)y);
  }

  float64 Mod(float64 x, float64 y)
  {
    float64 IntegerPart = 0;
    return modf(Abs(x / y), &IntegerPart) * y;
  }
#endif
}
#endif

#ifndef PRIM_RANDOM_H
#define PRIM_RANDOM_H

namespace prim
{
  /**A random number generator using the multiply-with-carry algorithm. This
  algorithm produces an extremely uniform and uncorrelated distribution and has
  an extremely long period somewhere on the order of 2^64. This particular
  version of the number generator has been evaluated with the "Dieharder" random
  number generator test battery and performs extremely well (see results below).
  The generator defaults to seeding with the system clock, so you only need to
  seed it if you want to be able to reproduce a given random sequence.

  A summary page of the results of the Dieharder analysis are as follows:

  \verbatim
  Assessment: PASSED at > 5% for RGB Bit Distribution Test
  Assessment: PASSED at > 5% for RGB Bit Distribution Test
  Assessment: PASSED at > 5% for RGB Bit Distribution Test
  Assessment: PASSED at > 5% for RGB Bit Distribution Test
  Assessment: POSSIBLY WEAK at < 5% for RGB Bit Distribution Test
  Recommendation:  Repeat test to verify failure.
  Assessment: PASSED at > 5% for RGB Bit Distribution Test
  Assessment: PASSED at > 5% for RGB Bit Distribution Test
  Assessment: PASSED at > 5% for RGB Bit Distribution Test
  Assessment: PASSED at > 5% for RGB Bit Distribution Test
  Assessment: PASSED at > 5% for RGB Bit Distribution Test
  Assessment: PASSED at > 5% for RGB Bit Distribution Test
  Assessment: PASSED at > 5% for RGB Bit Distribution Test
  Assessment: PASSED at > 5% for RGB Generalized Minimum Distance Test
  Assessment: PASSED at > 5% for RGB Generalized Minimum Distance Test
  Assessment: PASSED at > 5% for RGB Generalized Minimum Distance Test
  Assessment: PASSED at > 5% for RGB Generalized Minimum Distance Test
  Assessment: PASSED at > 5% for RGB Permutations Test
  Assessment: POSSIBLY WEAK at < 5% for RGB Permutations Test
  Recommendation:  Repeat test to verify failure.
  Assessment: PASSED at > 5% for RGB Permutations Test
  Assessment: PASSED at > 5% for RGB Permutations Test
  Assessment: PASSED at > 5% for RGB Permutations Test
  Assessment: PASSED at > 5% for RGB Permutations Test
  Assessment: PASSED at > 5% for RGB Lagged Sum Test
  Assessment: PASSED at > 5% for RGB Lagged Sum Test
  Assessment: PASSED at > 5% for RGB Lagged Sum Test
  Assessment: PASSED at > 5% for RGB Lagged Sum Test
  Assessment: PASSED at > 5% for RGB Lagged Sum Test
  Assessment: POOR at < 1% for RGB Lagged Sum Test
  Recommendation:  Repeat test to verify failure.
  Assessment: PASSED at > 5% for RGB Lagged Sum Test
  Assessment: POSSIBLY WEAK at < 5% for RGB Lagged Sum Test
  Recommendation:  Repeat test to verify failure.
  Assessment: PASSED at > 5% for RGB Lagged Sum Test
  Assessment: PASSED at > 5% for RGB Lagged Sum Test
  Assessment: PASSED at > 5% for RGB Lagged Sum Test
  Assessment: POSSIBLY WEAK at < 5% for RGB Lagged Sum Test
  Recommendation:  Repeat test to verify failure.
  Assessment: PASSED at > 5% for RGB Lagged Sum Test
  Assessment: PASSED at > 5% for RGB Lagged Sum Test
  Assessment: PASSED at > 5% for RGB Lagged Sum Test
  Assessment: FAILED at < 0.01% for RGB Lagged Sum Test
  Assessment: PASSED at > 5% for RGB Lagged Sum Test
  Assessment: PASSED at > 5% for RGB Lagged Sum Test
  Assessment: PASSED at > 5% for RGB Lagged Sum Test
  Assessment: POSSIBLY WEAK at < 5% for RGB Lagged Sum Test
  Recommendation:  Repeat test to verify failure.
  Assessment: PASSED at > 5% for RGB Lagged Sum Test
  Assessment: PASSED at > 5% for RGB Lagged Sum Test
  Assessment: PASSED at > 5% for RGB Lagged Sum Test
  Assessment: POOR at < 1% for RGB Lagged Sum Test
  Recommendation:  Repeat test to verify failure.
  Assessment: FAILED at < 0.01% for RGB Lagged Sum Test
  Assessment: PASSED at > 5% for RGB Lagged Sum Test
  Assessment: PASSED at > 5% for RGB Lagged Sum Test
  Assessment: PASSED at > 5% for RGB Lagged Sum Test
  Assessment: PASSED at > 5% for RGB Lagged Sum Test
  Assessment: PASSED at > 5% for RGB Lagged Sum Test
  Assessment: PASSED at > 5% for RGB Lagged Sum Test
  Assessment: FAILED at < 0.01% for RGB Lagged Sum Test
  Assessment: PASSED at > 5% for RGB Lagged Sum Test
  Assessment: PASSED at > 5% for Diehard Birthdays Test
  Assessment: PASSED at > 5% for Diehard 32x32 Binary Rank Test
  Assessment: PASSED at > 5% for Diehard 6x8 Binary Rank Test
  Assessment: PASSED at > 5% for Diehard Bitstream Test
  Assessment: PASSED at > 5% for Diehard OPSO
  Assessment: PASSED at > 5% for Diehard OQSO Test
  Assessment: PASSED at > 5% for Diehard DNA Test
  Assessment: PASSED at > 5% for Diehard Count the 1s (stream) Test
  Assessment: PASSED at > 5% for Diehard Count the 1s Test (byte)
  Assessment: POSSIBLY WEAK at < 5% for Diehard Parking Lot Test
  Recommendation:  Repeat test to verify failure.
  Assessment: PASSED at > 5% for Diehard Minimum Distance (2d Circle) Test
  Assessment: PASSED at > 5% for Diehard 3d Sphere (Minimum Distance) Test
  Assessment: PASSED at > 5% for Diehard Squeeze Test
  Assessment: PASSED at > 5% for Diehard Runs Test
  Assessment: PASSED at > 5% for Diehard Runs Test
  Assessment: PASSED at > 5% for Diehard Craps Test
  Assessment: PASSED at > 5% for Diehard Craps Test
  Assessment: POSSIBLY WEAK at < 5% for Marsaglia and Tsang GCD Test
  Recommendation:  Repeat test to verify failure.
  Assessment: PASSED at > 5% for Marsaglia and Tsang GCD Test
  Assessment: PASSED at > 5% for STS Monobit Test
  Assessment: PASSED at > 5% for STS Runs Test
  Assessment: PASSED at > 5% for STS Serial Test (Generalized)
  Assessment: PASSED at > 5% for STS Serial Test (Generalized)
  Assessment: PASSED at > 5% for STS Serial Test (Generalized)
  Assessment: PASSED at > 5% for STS Serial Test (Generalized)
  Assessment: PASSED at > 5% for STS Serial Test (Generalized)
  Assessment: PASSED at > 5% for STS Serial Test (Generalized)
  Assessment: POSSIBLY WEAK at < 5% for STS Serial Test (Generalized)
  Recommendation:  Repeat test to verify failure.
  Assessment: PASSED at > 5% for STS Serial Test (Generalized)
  Assessment: PASSED at > 5% for STS Serial Test (Generalized)
  Assessment: PASSED at > 5% for STS Serial Test (Generalized)
  Assessment: PASSED at > 5% for STS Serial Test (Generalized)
  Assessment: PASSED at > 5% for STS Serial Test (Generalized)
  Assessment: PASSED at > 5% for STS Serial Test (Generalized)
  Assessment: PASSED at > 5% for STS Serial Test (Generalized)
  Assessment: PASSED at > 5% for STS Serial Test (Generalized)
  Assessment: PASSED at > 5% for STS Serial Test (Generalized)
  Assessment: PASSED at > 5% for STS Serial Test (Generalized)
  Assessment: PASSED at > 5% for STS Serial Test (Generalized)
  Assessment: PASSED at > 5% for STS Serial Test (Generalized)
  Assessment: PASSED at > 5% for STS Serial Test (Generalized)
  Assessment: PASSED at > 5% for STS Serial Test (Generalized)
  Assessment: PASSED at > 5% for STS Serial Test (Generalized)
  Assessment: PASSED at > 5% for STS Serial Test (Generalized)
  Assessment: PASSED at > 5% for STS Serial Test (Generalized)
  Assessment: PASSED at > 5% for STS Serial Test (Generalized)
  Assessment: PASSED at > 5% for STS Serial Test (Generalized)
  Assessment: PASSED at > 5% for STS Serial Test (Generalized)
  Assessment: PASSED at > 5% for STS Serial Test (Generalized)
  Assessment: PASSED at > 5% for STS Serial Test (Generalized)
  Assessment: PASSED at > 5% for STS Serial Test (Generalized)
  Assessment: PASSED at > 5% for Lagged Sum Test
\endverbatim
*/
  class Random
  {
    ///Stores the state of the random number generator.
    uint32 History[5];

    ///Accesses the system clock in order to seed the generator.
    uint32 GetSystemTicks(void);

  public:
    //Returns the next uniform 32-bit random number.
    uint32 Next(void)
    {
      uint64 Sum = (uint64)2111111111UL * (uint64)History[3] + //
                   (uint64)1492 * (uint64)(History[2]) +       //
                   (uint64)1776 * (uint64)(History[1]) +       //
                   (uint64)5115 * (uint64)(History[0]) +       //
                   (uint64)History[4];                         //

      History[3] = History[2];
      History[2] = History[1];
      History[1] = History[0];
      History[4] = (uint32)(Sum >> (uint64)32);
      History[0] = (uint32)Sum;

      return History[0];
    }

    ///Returns a uniformly random signed 64-bit integer.
    int64 NextSignedInt64(void)
    {
      uint64 RandomInteger = ((uint64)Next() << (uint64)32) + (uint64)Next();
      return RandomInteger;
    }

    ///Returns a uniformly random unsigned 64-bit integer.
    uint64 NextUnsignedInt64(void)
    {
      return (uint64)NextSignedInt64();
    }

    ///Returns a uniform random integer.
    integer NextInteger(void)
    {
      return (integer)NextSignedInt64();
    }

    /**Returns a uniformly random 64-bit float over [1.0, 2.0). It is
    calculated by fixing the floating-point exponent and dumping random bits
    into the mantissa.*/
    float64 NextRawFloat64(void)
    {
      float64 Float = 0;
      void* FloatVoid = (void*)&Float;
      uint64* BinaryFloat = reinterpret_cast<uint64*>(FloatVoid);
      *BinaryFloat = ((uint64)1023 << (uint64)52);
      uint64 RandomMantissa = ((uint64)Next() << (uint64)32) + (uint64)Next();
      RandomMantissa = RandomMantissa >> (uint64)12;
      *BinaryFloat += RandomMantissa;
      return Float;
    }

    /**Returns a uniformly random number over [0.0, 1.0) = NextRawFloat64() -
    1.0. In theory, the floating-point subtraction used in this method will not
    cause any loss of precision and so it should not introduce correlation.*/
    number NextNumber(void)
    {
      return (number)(NextRawFloat64() - (float64)1.0);
    }

    /**Returns a random integer in a particular range. The order of the
    arguments does not make a difference. Note that the upper integer is
    excluded. In other words the interval is [Low, High).*/
    integer NextIntegerInRange(integer RangeBound1, integer RangeBound2 = 0)
    {
      //If bounds are equal, return the bound.
      if(RangeBound1 == RangeBound2)
        return RangeBound1;

      //Determine floating point range.
      float64 Low, High;
      integer LowInteger, HighInteger;
      if(RangeBound1 < RangeBound2)
      {
        Low = (float64)RangeBound1;
        LowInteger = RangeBound1;
        High = (float64)RangeBound2;
        HighInteger = RangeBound2;
      }
      else
      {
        Low = (float64)RangeBound2;
        LowInteger = RangeBound2;
        High = (float64)RangeBound1;
        HighInteger = RangeBound1;
      }

      //Generate a random number in the interval [1.0, 2.0).
      float64 Float = NextRawFloat64();

      //Set the range.
      Float = Float * High - Float * Low - High + (float64)2.0 * Low;

      //Convert to integer.
      integer Integer = (integer)Float;

      //Clamp the range in case of any floating-point arithmetic errors.
      if(Integer < LowInteger)
        Integer = LowInteger;
      else if(Integer >= HighInteger)
        Integer = HighInteger - 1;

      return Integer;
    }

    /**Returns a random number in a particular range. The order of the arguments
    does not make a difference. Note that the upper number is excluded. In other
    words the interval is [Low, High).*/
    number NextNumberInRange(number RangeBound1, number RangeBound2 = 0)
    {
      //Determine floating point range.
      float64 Low, High;
      if(RangeBound1 < RangeBound2)
      {
        Low = (float64)RangeBound1;
        High = (float64)RangeBound2;
      }
      else
      {
        Low = (float64)RangeBound2;
        High = (float64)RangeBound1;
      }

      //Generate a random number in the interval [1.0, 2.0).
      float64 Float = NextRawFloat64();

      //Set the range.
      Float = Float * High - Float * Low - High + (float64)2.0 * Low;

      //Clamp the range in case of floating-point arithmetic errors.
      if(Float < Low)
        Float = Low;
      if(Float > High)
        Float = High;
      return (number)Float;
    }

    ///Pick a random sequence using a 32-bit seed.
    void PickSequence(uint32 Seed)
    {
      //Use recommended MCA initialization arithmetic to generate initial state.
      for(count i = 0; i < 5; i++)
      {
        Seed *= 29943829;
        Seed -= 1;
        History[i] = Seed;
      }

      //Break in the sequence by discarding the first 100 values.
      for(count i = 0; i < 100; i++)
        Next();
    }

    ///Picks a random sequence automatically using the system clock.
    void PickRandomSequence(void)
    {
      PickSequence(GetSystemTicks());
    }

    ///Initialize the random number generator with the system clock.
    Random()
    {
      PickRandomSequence();
    }

    ///Initialize the random number generator with a 32-bit seed.
    Random(uint32 Seed)
    {
      PickSequence(Seed);
    }

    ///Returns a uniformly random number [0, 1).
    number Between(void)
    {
      return NextNumber();
    }

    ///Returns a uniformly random number [0, Max).
    float32 Between(float32 Max)
    {
      return (float32)NextNumberInRange((number)Max);
    }

    ///Returns a uniformly random number [0, Max).
    float64 Between(float64 Max)
    {
      return (float64)NextNumberInRange((number)Max);
    }

    ///Returns a uniformly random number [Min, Max).
    float32 Between(float32 Min, float32 Max)
    {
      return (float32)NextNumberInRange((number)Min, (number)Max);
    }

    ///Returns a uniformly random number [Min, Max).
    float64 Between(float64 Min, float64 Max)
    {
      return (float64)NextNumberInRange((number)Min, (number)Max);
    }

    ///Returns a uniformly random integer [0, Max).
    int32 Between(int32 Max)
    {
      return (int32)NextIntegerInRange((integer)Max);
    }

    ///Returns a uniformly random integer [0, Max).
    int64 Between(int64 Max)
    {
      return (int64)NextIntegerInRange((integer)Max);
    }

    ///Returns a uniformly random integer [Min, Max).
    int32 Between(int32 Min, int32 Max)
    {
      return (int32)NextIntegerInRange((integer)Min, (integer)Max);
    }

    ///Returns a uniformly random integer [Min, Max).
    int64 Between(int64 Min, int64 Max)
    {
      return (int64)NextIntegerInRange((integer)Min, (integer)Max);
    }
  };

#ifdef PRIM_COMPILE_INLINE
  uint32 Random::GetSystemTicks(void)
  {
    return (uint32)clock();
  }
#endif
}
#endif

//............................................................................//

#ifndef PRIM_ARRAY_H
#define PRIM_ARRAY_H

/**\file Array.h Implements the Array class.*/

namespace prim { namespace meta
{
  ///Pure class intended for implementing different heap growth models.
  struct BaseGrowthModel
  {
    ///Override ensuring the real size is greater or equal to the apparent size.
    virtual count CalculateRealSize(count ApparentSize) = 0;

    ///Virtual destructor to the base growth model.
    virtual ~BaseGrowthModel() {}
  };

  /**Growth model that rounds apparent size up to nearest power of two.
  \code  c >> "Array.h: PowerOfTwoGrowthModel";
  *  //Note that PowerOfTwoGrowthModel is the default for an Array.
  *  Array<count, meta::PowerOfTwoGrowthModel> a;
  *  a.n(5);
  *  for(count i = 0; i < a.n(); i++)
  *    a[i] = i;
  *  for(count i = 0; i < a.n(); i++)
  *    c >> a[i];
  \endcode
  */
  struct PowerOfTwoGrowthModel : BaseGrowthModel
  {
    /**Returns the lowest power-of-two that can contain the input. The real
    size is always greater than or equal to the apparent size, permitting the
    apparent size to grow for a time before the real size must be increased.

    \code  c >> "Array.h: PowerOfTwoGrowthModel::CalculateRealSize";
    *  meta::PowerOfTwoGrowthModel p;
    *  for(count i = 1; i < 100; i += 5)
    *    c >> i << " will be stored using " << p.CalculateRealSize(i);
    \endcode
    */
    count CalculateRealSize(count ApparentSize)
    {
      //Return 0 if bad argument.
      if(ApparentSize < 0)
        return 0;

      //If 1 or 2, then Real = Apparent
      if(ApparentSize <= 2)
        return ApparentSize;

      /*If 3 or higher calculate the physical size by finding the least power of
      two greater to equal than than the logical size.*/
      count RealSize = 2;
      do
      {
        RealSize *= 2;
        if(RealSize >= ApparentSize)
          return RealSize;
      }
      while(RealSize > 0 && (uintptr)RealSize < PointerHighBit);

      //Overflow returns zero.
      return 0;
    }
  };

  /**Growth model in which the real size is the apparent size.
  \code  c >> "Array.h: LinearGrowthModel";
  *  Array<count, meta::LinearGrowthModel> a;
  *  a.n(5);
  *  for(count i = 0; i < a.n(); i++)
  *    a[i] = i;
  *  for(count i = 0; i < a.n(); i++)
  *    c >> a[i];
  \endcode
  */
  struct LinearGrowthModel : BaseGrowthModel
  {
    /**Returns the same number of storage elements as actual elements. The real
    size is equal to the apparent size.
    \code  c >> "Array.h: LinearGrowthModel::CalculateRealSize";
    *  meta::LinearGrowthModel p;
    *  for(count i = 1; i < 100; i += 5)
    *    c >> i << " will be stored using " << p.CalculateRealSize(i);
    \endcode
    */
    count CalculateRealSize(count ApparentSize)
    {
      //Return 0 if bad argument.
      if(ApparentSize < 0)
        return 0;

      return ApparentSize;
    }
  };

  /**Growth model in which apparent size is rounded up to nearest multiple of m.
  \code  c >> "Array.h: ConstantGrowthModel";
  *  Array<count, meta::ConstantGrowthModel<3> > a;
  *  a.n(5);
  *  for(count i = 0; i < a.n(); i++)
  *    a[i] = i;
  *  for(count i = 0; i < a.n(); i++)
  *    c >> a[i];
  \endcode
  */
  template <count m>
  struct ConstantGrowthModel : BaseGrowthModel
  {
    /**Returns the least multiple of the argument m containing the actual size.
    The real size is always greater than or equal to the apparent size,
    permitting the apparent size to grow for a time before the real size must be
    increased. This type of growth is good for arrays which have fairly certain
    upper-bounds and sizes that stay mostly constant.
    \code  c >> "Array.h: ConstantGrowthModel::CalculateRealSize";
    *  meta::ConstantGrowthModel<20> p;
    *  for(count i = 1; i < 100; i += 5)
    *    c >> i << " will be stored using " << p.CalculateRealSize(i);
    \endcode
    */
    count CalculateRealSize(count ApparentSize)
    {
      //Return 0 if bad argument.
      if(ApparentSize < 0)
        return 0;

      if(ApparentSize % m == 0)
        return ApparentSize;
      else
        return (ApparentSize / m + 1) * m;
    }
  };
}}

namespace prim
{
  /**An array with customizable growth model allocation and dynamic resizing.
  The default growth model is exponential base-two so that memory copies only
  occur when power-of-two lengths are exceeded. This model is a good choice for
  most dynamic array situations since it is reasonable to assume that a given
  array could easily expand to twice its current value. Other models may be more
  appropriate though, for example, when memory conservation is important, or
  when the dynamics of the array growth are well-known ahead of time.

  Typical usage:
  \code  c >> "Array.h: Array (part 1)";
  *  //Create an array of numbers.
  *  Array<number> a;
  *
  *  //Resize the array to contain 10 elements.
  *  a.n(10);
  *  for(count i = 0; i < a.n(); i++)
  *    a[i] = (number)i * 4.2 - 3.8;
  *
  *  //Dynamically resize the array to contain 8 elements (removes last two).
  *  a.n(8);
  *
  *  //Print out contents of array.
  *  for(count i = 0; i < a.n(); i++)
  *    c >> a[i];
  \endcode

  You can also change the type of growth by specifying a different growth model:
  \code  c >> "Array.h: Array (part 2)";
  *  //Create array with a linear growth model so it uses the least memory.
  *  Array<number, meta::LinearGrowthModel> a;
  *
  *  //Allocate exactly 300 elements (instead of 512) to save space.
  *  a.n(300);
  *  c >> a.n();
  *
  *  //Adding just one element means reallocating the whole array.
  *  a.n(301); //Should have just stuck with PowerOfTwoGrowthModel!
  *  c >> a.n();
  \endcode
  */
  template <class T, class GM = meta::PowerOfTwoGrowthModel>
  class Array : public GM
  {
    ///Untyped pointer to the beginning of the array data.
    T* Data;

    /**The apparent number of elements in the array. The real number of elements
    allocated can be derived with CalculateRealSize().*/
    count ApparentSize;

  public:

    //--------------//
    //Element Access//
    //--------------//

    /**Returns the i-th element by index. The method does not check bounds
    before accessing the data. The returned element is not const protected.
    \code  c >> "Array.h: Array::ith";
    *  Array<count> a;
    *  a.n(10);
    *  for(count i = 0; i < a.n(); i++)
    *    a.ith(i) = 4; // <-- Method used here
    *
    *  for(count i = 0; i < a.n(); i++)
    *    c >> a.ith(i); // <-- Method used here
    \endcode
    */
    inline T& ith(count i) const
    {
      return Data[i];
    }

    /**Returns the i-th const element by index. The method does not check bounds
    before accessing the data. The returned element is const protected.
    \code  c >> "Array.h: Array::ithConst";
    *  Array<count> a;
    *  a.n(10);
    *  for(count i = 0; i < a.n(); i++)
    *    a[i] = 4;
    *
    *  //Can not do this because of const-protection.
    *  //a.ithConst(6) = 5; // <-- Method used here, but commented out
    *
    *  for(count i = 0; i < a.n(); i++)
    *    c >> a.ithConst(i); // <-- Method used here
    \endcode
    */
    inline const T& ithConst(count i) const
    {
      return (const T&)Data[i];
    }

    /**Returns the indexed element. Internally inlines ith().
    \code  c >> "Array.h: Array::operator []";
    *  Array<count> a;
    *  a.n(10);
    *  for(count i = 0; i < a.n(); i++)
    *    a[i] = 4; // <-- Method used here
    *
    *  for(count i = 0; i < a.n(); i++)
    *    c >> a[i]; // <-- Method used here
    \endcode
    */
    inline T& operator [] (count i) const
    {
      return ith(i);
    }

    /**Returns the first element of the array. Assumes that there is at least
    one element in the array. The returned element is const protected. Note
    lowercase is used because the method is treated like a mathematical variable.
    \code  c >> "Array.h: Array::first";
    *  Array<number> a;
    *  a.n(10);
    *  for(count i = 0; i < a.n(); i++)
    *    a[i] = (number)i * 4.2 - 3.8;
    *
    *  c >> a.a(); // <-- Method used here
    \endcode
    */
    inline T& a(void) const
    {
      return ith(0);
    }

    /**Returns the last element of the array or an element with respect to last.
    ItemsFromEnd must be nonnegative. Assumes that there is at least one element
    in the array. The returned element is const protected. Note lowercase is
    used because the method is treated like a mathematical variable.
    \code  c >> "Array.h: Array::last";
    *  Array<number> a;
    *  a.n(10);
    *  for(count i = 0; i < a.n(); i++)
    *    a[i] = (number)i * 4.2 - 3.8;
    *
    *  c >> a.z(); // <-- Method used here
    \endcode
    */
    inline T& z(count ItemsFromEnd = 0) const
    {
      return ith(ApparentSize - 1 - ItemsFromEnd);
    }

    //----//
    //Size//
    //----//

    /**Returns the size of the array.
    \code  c >> "Array.h: Array::n()";
    *  Array<number> a;
    *  a.n(10);
    *  count NewSize = 10 * 5 - 3 + 2;
    *  NewSize += a.n(); // <-- Method used here
    *  a.n(NewSize);
    *  c >> a.n(); // <-- Method used here
    \endcode
    */
    inline count n(void) const
    {
      return ApparentSize;
    }

    /**Sets the size of the array. New elements will have constructors called.
    If the array does not fit the current allocation, then the copy constructors
    of all the preexisting elements will also be called. The array returns a
    pointer to the data, which can be used for error-checking. If the array has
    no elements, the pointer will be zero.
    \code  c >> "Array.h: Array::n(count)";
    *  //Create an array of numbers.
    *  Array<number> a;
    *
    *  //Resize the array to contain 10 elements.
    *  a.n(10); // <-- Method used here
    *  for(count i = 0; i < a.n(); i++)
    *    a[i] = (number)i * 4.2 - 3.8;
    *
    *  //Dynamically resize the array to contain 8 elements (removes last two).
    *  a.n(8); // <-- Method used here
    *
    *  //Print out contents of array.
    *  for(count i = 0; i < a.n(); i++)
    *    c >> a[i];
    \endcode
    */
    const T* n(count NewSize)
    {
      //In case the new requested size is the same, immediately return.
      if(NewSize == ApparentSize)
        return Data;

      //In the case of a no size array, just delete all the data.
      if(NewSize <= 0)
      {
        //Delete each of the elements (this will call destructors).
        delete [] Data;
        Data = 0;
        ApparentSize = 0;
        return 0;
      }

      /*Calculate the real size using the growth model passed by template
      argument.*/
      count OldRealSize =
        ((meta::BaseGrowthModel*)this)->CalculateRealSize(ApparentSize);
      count NewRealSize =
        ((meta::BaseGrowthModel*)this)->CalculateRealSize(NewSize);

      /*If no extra data needs to be allocated, then just change the size of the
      array.*/
      if(OldRealSize == NewRealSize)
      {
        //Set the new apparent size of the array.
        ApparentSize = NewSize;
        return Data;
      }

      //Allocate a new contiguous block of memory.
      T* NewData = new T[NewRealSize];

      //If memory could not be allocated, return zero.
      if(!NewData)
        return 0;

      //Get the minimum of the new size and the current apparent size.
      count ElementsInCommon = NewSize > ApparentSize ? ApparentSize : NewSize;

      /*Swap memory contents of Data and NewData. The following two lines are a
      bait-and-switch. Data is about to be deleted so we want to take the newly
      constructed empty objects of NewData and swap them for the real content in
      Data. This way, when Data is deleted it is only deleting empty objects and
      any objects which are supposed to be deleted. This absolutely assumes that
      the user has not stored a pointer to the elements in the array (which can
      only be guaranteed for as long as this resize function is not called).*/
      Memory::SwapMemory(Data, NewData, ElementsInCommon);

      //Delete old array.
      delete [] Data;

      //Set the new size of the array.
      ApparentSize = NewSize;

      //Return pointer to the new data array.
      return Data = NewData;
    }

    //--------//
    //Clearing//
    //--------//

    /**Clears the array. The destructors are called on each element.
    \code  c >> "Array.h: Array::Clear";
    *  //Create an array of numbers.
    *  Array<number> a;
    *
    *  //Resize the array to contain 10 elements.
    *  a.n(10);
    *  for(count i = 0; i < a.n(); i++)
    *    a[i] = (number)i * 4.2 - 3.8;
    *
    *  //Print out contents of array.
    *  for(count i = 0; i < a.n(); i++)
    *    c >> a[i];
    *
    *  //Clear the array.
    *  a.Clear(); // <-- Method used here
    *
    *  //Print out contents of array.
    *  for(count i = 0; i < a.n(); i++)
    *    c >> a[i];
    \endcode
    */
    inline void Clear(void)
    {
      n(0);
    }

    /**Clears the array after deleting the object pointed to by each element.
    Elements are deleted in reverse order from last to first. This method may
    only be used when the element is a pointer type.
    \code  c >> "Array.h: Array::ClearAndDeleteAll";
    *  //Create an array of pointers to numbers.
    *  Array<number*> a;
    *
    *  //Create 10 new numbers on the heap and store their pointers.
    *  a.n(10);
    *  for(count i = 0; i < a.n(); i++)
    *  {
    *    a[i] = new number;
    *    *a[i] = (number)i * 4.2 - 3.8;
    *  }
    *
    *  //Print out contents of array.
    *  for(count i = 0; i < a.n(); i++)
    *    c >> (void*)a[i] << ": " << *a[i];
    *
    *  //Clear the array, deleting the heap data pointed to by the pointers.
    *  a.ClearAndDeleteAll(); // <-- Method used here
    *
    *  //Print out contents of array.
    *  for(count i = 0; i < a.n(); i++)
    *    c >> (void*)a[i] << ": " << *a[i];
    \endcode
    */
    inline void ClearAndDeleteAll(void)
    {
      for(count i = n() - 1; i >= 0; i--)
        delete Data[i];
      n(0);
    }

    /**Zeroes the memory contents of the array. Only use this method with
    plain-old data. Objects with virtual tables should not be zeroed.
    \code  c >> "Array.h: Array::Zero";
    *  //Create an array of numbers.
    *  Array<number> a;
    *
    *  //Resize the array to contain 10 elements.
    *  a.n(10);
    *  a.Zero(); // <-- Method used here
    *
    *  //It is safe to print out contents of array now.
    *  for(count i = 0; i < a.n(); i++)
    *    c >> a[i];
    \endcode
    */
    void Zero(void)
    {
      Memory::Clear(Data, ApparentSize);
    }

    /**Zeroes the memory contents of the array starting at the given index. Only
    use this method with plain-old-data. Objects with virtual tables should not
    be zeroed.
    \code  c >> "Array.h: Array::ZeroFrom";
    *  //Create an array of numbers.
    *  Array<number> a;
    *
    *  //Size the array to contain 10 elements and initialize it.
    *  a.n(10);
    *  a.Zero();
    *
    *  //Resize the array to contain 5 more elements and initialize just those.
    *  a.n(15);
    *  a.ZeroFrom(10);
    *
    *  //It is safe to print out contents of array now.
    *  for(count i = 0; i < a.n(); i++)
    *    c >> a[i];
    \endcode
    */
    void ZeroFrom(count Index)
    {
      if(Index < 0)
        Index = 0;
      else if(Index >= ApparentSize)
        return;
      Memory::Clear(&Data[Index], ApparentSize - Index);
    }

    //------//
    //Adding//
    //------//

    /**Adds an element to the array and returns a reference to that element.
    \code  c >> "Array.h: Array::Add()";
    *  //Create an array of numbers.
    *  Array<number> a;
    *  a.Add() = 2.3;
    *  a.Add() = 43.23;
    *  a.Add() = 323.32;
    *
    *  //Print out the numbers.
    *  for(count i = 0; i < a.n(); i++)
    *    c >> a[i];
    \endcode
    */
    T& Add(void)
    {
      n(ApparentSize + 1);
      return (T&)z();
    }

    /**Adds an element to the array using a copy constructor.
    \code  c >> "Array.h: Array::Add(const T&)";
    *  //Create an array of numbers.
    *  Array<number> a;
    *  number x = 2.3;
    *  a.Add(x);
    *  x = 43.23;
    *  a.Add(x);
    *  x = 323.32;
    *  a.Add(x);
    *
    *  //Print out the numbers.
    *  for(count i = 0; i < a.n(); i++)
    *    c >> a[i];
    \endcode
    */
    void Add(const T& NewElement)
    {
      n(ApparentSize + 1);
      Data[ApparentSize - 1] = NewElement;
    }

    //-------//
    //Copying//
    //-------//

    /**Copys elements one-by-one from other array data. First the array is
    resized to have the same number of elements as the other. Then each element
    from the other is copied by assignment. Note that the resizing step will
    cause constructors to be called, which may be inefficient. If your array
    contains plain-old data then you are better off using CopyMemoryFrom().
    \code  c >> "Array.h: Array::CopyFrom(const T*, count)";
    *  count a[5] = {123, 234, 345, 456, 567};
    *  Array<count> b;
    *  //Copy memory directly from static array a to Array b.
    *  b.CopyFrom(a, 5); //Element-by-element copy
    *  c >> b[0];
    \endcode
    */
    void CopyFrom(const T* OtherArray, count NumberOfElementsToTake)
    {
      //If the source and destination are the same, no copying is necessary.
      if(Data == OtherArray)
        return;

      //Resize the array.
      n(NumberOfElementsToTake);

      //Copy each element by assignment.
      for(count i = 0; i < ApparentSize; i++)
        Data[i] = OtherArray[i];
    }

    /**Copys elements one-by-one from another array. First the array is resized
    to have the same number of elements as the other. Then each element from the
    other is copied by assignment. Note that the resizing step will cause
    constructors to be called, which may be inefficient. If your array contains
    plain-old data then you are better off using CopyMemoryFrom().
    \code  c >> "Array.h: Array::CopyFrom(const Array<T>&)";
    *  Array<count> a;
    *  a.Add() = 123;
    *  Array<count> b;
    *  //Copy memory directly from a to b.
    *  b.CopyFrom(a); //Element-by-element copy
    *  c >> b[0];
    \endcode
    */
    void CopyFrom(const Array<T>& Other)
    {
      CopyFrom((const T*)Other.Data, Other.ApparentSize);
    }

    /**Copies the memory of other array data. This method will only call the
    constructors of the newly created elements. If the source is already an
    Array, then it is preferable to pass in the Array object so that the
    assignment operators will be used. Only use this copy constructor if the
    elements are plain-old data.
    \code  c >> "Array.h: Array:CopyMemoryFrom(const T*, count)";
    *  count a[5] = {123, 234, 345, 456, 567};
    *  Array<count> b;
    *  //Copy memory directly from static array a to Array b.
    *  b.CopyMemoryFrom(a, 5); //(OK since count is plain-old data).
    *  c >> b[0];
    \endcode
    */
    void CopyMemoryFrom(const T* OtherArray, count NumberOfElementsToTake)
    {
      //If the source and destination are the same, no copying is necessary.
      if(Data == OtherArray)
        return;

      //Resize the array.
      n(NumberOfElementsToTake);

      //Copy the entire array as plain-old data.
      Memory::Copy(Data, OtherArray, ApparentSize);
    }

    /**Copies the memory of another array. First the array is resized to have
    the same number of elements. Then a memory copy operation is done on the
    array to copy the contents of the other array byte-for-byte into this one.
    Note well, in order for this to be valid, the elements must be plain-old
    data, i.e., they must not contain members with special constructors and must
    not contain virtual methods. Use the CopyFrom() method for complex objects
    so that they will be properly copied using the assignment operator.
    \code  c >> "Array.h: Array::CopyMemoryFrom(const Array<T>&)";
    *  Array<count> a;
    *  a.Add() = 123;
    *  Array<count> b;
    *  //Copy memory directly from a to b.
    *  b.CopyMemoryFrom(a); //(OK since count is plain-old data).
    *  c >> b[0];
    \endcode
    */
    void CopyMemoryFrom(const Array<T>& Other)
    {
      CopyMemoryFrom(Other.Data, Other.ApparentSize);
    }

    /**Swaps data with another array by simply exchanging pointers and size.
    \code  c >> "Array.h: Array::SwapWith";
    *  Array<count> a, b;
    *  a.Add() = 12345;
    *  for(count i = 0; i < 10000; i++)
    *    b.Add() = (i + 19) * 11;
    *  c >> "a.n() = " << a.n() << ", b.n() = " << b.n();
    *  c >> "a[0] = " << a[0] << ", b[0] = " << b[0];
    *  a.SwapWith(b);
    *  c >> "a.n() = " << a.n() << ", b.n() = " << b.n();
    *  c >> "a[0] = " << a[0] << ", b[0] = " << b[0];
    \endcode
    */
    void SwapWith(Array<T>& Other)
    {
      Memory::Swap(Data, Other.Data);
      Memory::Swap(ApparentSize, Other.ApparentSize);
    }

    //--------//
    //Encoding//
    //--------//

    ///Creates a hex version of this array.
    void EncodeAsASCIIHex(Array<byte>& HexArray)
    {
      HexArray.Clear();
      HexArray.n(n() * 2 * sizeof(T));
      count HexIndex = 0;
      byte* ByteData = (byte*)Data;
      for(count i = 0; i < n(); i++)
      {
        for(count j = 0; j < (count)sizeof(T); j++)
        {
          byte X = ByteData[i * sizeof(T) + j];
          byte A = (X >> 4) & 15;
          if(A < 10)
            A += 48;
          else
            A += 55;
          byte B = X & 15;
          if(B < 10)
            B += 48;
          else
            B += 55;
          HexArray[HexIndex++] = A;
          HexArray[HexIndex++] = B;
        }
      }
    }

    //----------------------//
    //Constructor-Destructor//
    //----------------------//

    /**Initializes an empty array.
    \code  c >> "Array.h: Array::Array()";
    *  Array<count> a;
    *  c >> a.n() << " elements at memory location " << &a[0];
    \endcode
    */
    Array() : Data(0), ApparentSize(0) {}

    /**One-by-one element level copy constructor. Internally calls the
    CopyFrom() method. You could also use CopyMemoryFrom() if your element is
    plain-old data.
    \code  c >> "Array.h: Array::Array(const Array<T>&)";
    *  Array<count> a;
    *  a.Add() = 123;
    *  //Use copy-constructor.
    *  Array<count> b = a;
    *  c >> b[0];
    \endcode
    */
    Array(const Array<T>& Other) : GM(), Data(0), ApparentSize(0)
    {
      CopyFrom(Other);
    }

    /**Assignment operator to copy array elements one-by-one. Internally calls
    CopyFrom().
    \code  c >> "Array.h: Array::operator =";
    *  Array<count> a;
    *  a.Add() = 123;
    *  Array<count> b;
    *  //Use assignment operator with already-constructed object.
    *  b = a;
    *  c >> b[0];
    \endcode
    */
    Array<T>& operator = (const Array<T>& Other)
    {
      CopyFrom(Other);
      return *this;
    }

    /**Clears the array, calling each of the elements' destructors. Note that if
    you have pointers to objects, call ClearAndDeleteAll() before the array goes
    out of scope.
    \code  c >> "Array.h: Array::~Array";
    *  //The following would leak memory:
    *  if(false)
    *  {
    *    Array<number*> a;
    *    for(count i = 0; i < 5; i++)
    *    {
    *      a.Add() = new number;
    *      *a.z() = 1.2345;
    *    }
    *    c >> a.n();
    *  }
    *
    *  //The following does not leak memory:
    *  if(true)
    *  {
    *    Array<number*> a;
    *    for(count i = 0; i < 5; i++)
    *    {
    *      a.Add() = new number;
    *      *a.z() = 1.2345;
    *    }
    *    a.ClearAndDeleteAll();
    *    c >> a.n();
    *  }
    \endcode
    */
    virtual ~Array() {n(0);}
  };
}
#endif

#ifndef PRIM_COMPLEX_H
#define PRIM_COMPLEX_H

namespace prim
{
  ///Stores a complex number (or a point on a plane).
  template <class T>
  struct Complex
  {
    ///Stores the value for the real part (or x-coordinate).
    T x;

    ///Stores the value for the imaginary part (or y-coordinate).
    T y;

    ///Alias for x-coordinate, i().
    inline T& i(void) {return x;}

    ///Alias for y-coordinate, j().
    inline T& j(void) {return y;}

    ///Alias for x-coordinate, a().
    inline T& a(void) {return x;}

    ///Alias for y-coordinate, b().
    inline T& b(void) {return y;}

    //---------------------------//
    //Cartesian-Polar Conversions//
    //---------------------------//

    /**\brief Stores the cartesian equivalent of the given angle (in
    radians) and magnitude. \details Note that specifying a negative
    magnitude will cause the angle to increase by Pi. This method loses
    less precision than by calling Mag and Ang separately.*/
    inline void Polar(number Angle,  number Magnitude = 1.f)
    {
      x = (T)(Cos(Angle) * Magnitude);
      y = (T)(Sin(Angle) * Magnitude);
    }

    ///Returns the magnitude (distance from the origin) of the x-y pair.
    inline number Mag(void) const
    {
      return Abs((number)x, (number)y);
    }

    ///Changes the magnitude keeping the angle the same.
    inline void Mag(number Magnitude)
    {
      number Angle = Ang();
      Polar(Angle, Magnitude);
    }

    ///Returns the angle of the x-y pair relative to the origin.
    inline number Ang(void) const
    {
      return Angle(x, y);
    }

    ///Changes the angle of the x-y pair keeping the magnitude the same.
    inline void Ang(number Angle)
    {
      number Magnitude = Mag();
      Polar(Angle, Magnitude);
    }

    ///Returns the magnitude distance to another x-y pair.
    inline number Mag(Complex<T> Other) const
    {
      return Distance((number)x, (number)y, (number)Other.x, (number)Other.y);
    }

    ///Returns the angle between this x-y pair and another.
    inline number Ang(Complex<T> Other) const
    {
      Complex<T> Delta(Other.x - x, Other.y - y);
      return Delta.Ang();
    }

    //--------------//
    //Multiplication//
    //--------------//

    /**Multiplies by a scalar and returns the result.
    \code
    *  Complex<number> a(3.2, 2.3);
    *  Complex<number> b = a * 2.0;
    *  c >> b.x << ", " << b.y;
    \endcode
    */
    inline Complex operator * (T Scalar) const
    {
      return Complex(x * Scalar, y * Scalar);
    }

    /**Complex multiplies and returns the result. The formula is: (a + bi)(c
    + di) = (ac - bd) + (bc + ad)i.
    \code
    *  Complex<number> a(3.2, 2.3), b(4.5, 5.4);
    *  Complex<number> c = a * b;
    *  prim::c >> c.x << ", " << c.y;
    \endcode
    */
    inline Complex operator * (Complex Other) const
    {
      return Complex(x * Other.x - y * Other.y, x * Other.y + y * Other.x);
    }

    /**Multiplies by another number, then stores and returns result.
    \code
    *  Complex<number> a(3.2, 2.3);
    *  Complex<number> b = (a *= 2.0);
    *  c >> a.x << ", " << a.y << "; " << b.x << ", " << b.y;
    \endcode
    */
    inline Complex operator *= (T Scalar)
    {
      return *this = *this * Scalar;
    }

    /**Complex multiplies, then stores and returns result.
    \code
    *  Complex<number> a(3.2, 2.3);
    *  Complex<number> b(4.5, 5.4);
    *  b *= a;
    *  c >> a.x << ", " << a.y << "; " << b.x << ", " << b.y;
    \endcode
    */
    inline Complex operator *= (Complex Other)
    {
      return *this = *this * Other;
    }

    //--------//
    //Division//
    //--------//

    /**Divides by a number and returns the result.
    \code
    *  Complex<number> a(3.2, 2.3);
    *  Complex<number> b = a / 2.0;
    *  c >> b.x << ", " << b.y;
    \endcode
    */
    inline Complex operator / (T Divisor) const
    {
      return Complex(x / Divisor, y / Divisor);
    }

    /**Complex divides and returns the result. The formula is: (a + bi)/(c
    + di) = ((ac + bd) + (bc - ad)i) / (c^2 + d^2).
    \code
    *  Complex<number> a(3.2, 2.3), b(4.5, 5.4);
    *  Complex<number> c = a / b;
    *  prim::c >> c.x << ", " << c.y;
    \endcode
    */
    inline Complex operator / (Complex Other) const
    {
      number Divisor = (Square(Other.x) + Square(Other.y));

      return Complex((x * Other.x + y * Other.y) / Divisor,
        (x * Other.y - y * Other.x) / Divisor);
    }

    /**Divides by another number, then stores and returns result.
    \code
    *  Complex<number> a(3.2, 2.3);
    *  Complex<number> b = (a /= 2.0);
    *  c >> a.x << ", " << a.y << "; " << b.x << ", " << b.y;
    \endcode
    */
    inline Complex operator /= (T Divisor)
    {
      return *this = *this / Divisor;
    }

    /**Complex divides, then stores and returns result.
    \code
    *  Complex<number> a(3.2, 2.3);
    *  Complex<number> b(4.5, 5.4);
    *  b /= a;
    *  c >> a.x << ", " << a.y << "; " << b.x << ", " << b.y;
    \endcode
    */
    inline Complex operator /= (Complex Other)
    {
      return *this = *this / Other;
    }

    //------------------------//
    //Addition and Subtraction//
    //------------------------//

    ///Adds another x-y pair to this one and returns the result.
    inline Complex operator + (Complex Other) const
    {
      return Complex(x + Other.x, y + Other.y);
    }

    ///Substracts another x-y pair to this one and returns the result.
    inline Complex operator - (Complex Other) const
    {
      return Complex(x - Other.x, y - Other.y);
    }

    ///Adds another x-y pair to this one and stores the result.
    inline Complex operator += (Complex Other)
    {
      x += Other.x;
      y += Other.y;
      return *this;
    }

    ///Substracts another x-y pair to this one and stores the result.
    inline Complex operator -= (Complex Other)
    {
      x -= Other.x;
      y -= Other.y;
      return *this;
    }

    //----------//
    //Assignment//
    //----------//

    ///Assignment operator copies another x-y pair into this one.
    inline Complex operator = (Complex Other)
    {
      x = Other.x;
      y = Other.y;
      return *this;
    }

    //-----------//
    //Equivalence//
    //-----------//

    ///Equivalence comparison operator.
    inline bool operator == (Complex Other) const
    {
      return x == Other.x && y == Other.y;
    }

    ///Unequivalence comparison operator.
    inline bool operator != (Complex Other) const
    {
      return x != Other.x || y != Other.y;
    }

    //------------//
    //Constructors//
    //------------//

    ///Creates a complex number with a real and imaginary part (or coordinate).
    Complex(T x, T y)
    {
      Complex<T>::x = x;
      Complex<T>::y = y;
    }

    ///Creates a complex number from an angle with unity magnitude.
    Complex(number Angle)
    {
      Polar(Angle);
    }

    ///Copy constructor copies another complex number onto this one.
    Complex(const Complex& Other)
    {
      x = Other.x;
      y = Other.y;
    }

    ///Creates a complex number at the origin.
    Complex() : x((T)0), y((T)0) {}

    ///Casts this coordinate type into a different coordinate type.
    template <class U>
    operator Complex<U> (void) const
    {
      return Complex<U>((U)x, (U)y);
    }
  };
}
#endif

#ifndef PRIM_LIST_H
#define PRIM_LIST_H

namespace prim
{
  /**Doubly-linked list with an automatic iterator.

  List recognizes and optimizes sequential access by maintaining three origins
  of traversal: the beginning, a variable index, and the end. The variable index
  is updated each time an element is requested by index. This way, sequential
  access is as efficient as an iterator. You can thus use array-like indexing
  with no performance penalty.

  In the above example, the list automatically saves the last retrieved link
  so that if you ask for an adjacent index, it will find the element without
  having to retraverse the whole list. This cached index is saved until the
  list is modified.

  This indexing optimization does not make random access more efficient. If
  random or contiguous access is a requirement, then the Array would be a better
  choice.*/
  template <class T>
  class List
  {
    protected:
    ///Implements a simple double link.
    struct DoubleLink
    {
      ///Object containing data of the list type
      T Data;

      ///Pointer to the next link, or null if there is none.
      DoubleLink* Next;

      ///Pointer to the previous link, or null if there is none.
      DoubleLink* Prev;

      ///Default constructor
      DoubleLink() : Next(0), Prev(0) {}

      ///Copy constructor
      DoubleLink(T& DataToCopy) : Next(0), Prev(0) {Data = DataToCopy;}

      ///Assignment operator
      T operator = (const T& Other)
      {
        Data = Other;
        return Data;
      }

      ///Automatic casting into T
      operator T&()
      {
        return Data;
      }
    };

    ///Pointer to the first link
    DoubleLink* First;

    ///Pointer to the last link
    DoubleLink* Last;

    ///Pointer to the last referenced link
    mutable DoubleLink* LastReferenced;

    ///Index of the last referenced link
    mutable count LastReferencedIndex;

    ///The number of items in the list
    count Items;

    ///Returns a pointer to the link containing the given data.
    DoubleLink* GetLinkFromItem(const T& i)
    {
      /*Using a trick in order to get pointers to the DoubleLink by calculating
      the beginning of the class using a test link for reference to determine
      where the data part is in relation to the rest of the class. By doing this
      no non-portable assumptions are made about what a compiler does with
      member order in physical memory.*/

      static DoubleLink TestLink;

      return (DoubleLink*)((uintptr)(void*)&i +
        (uintptr)(void*)&TestLink.Data - (uintptr)(void*)&TestLink);
    }

    /**Swaps the position of two elements without copying their internal data.
    Only elements from the same list may be swapped.*/
    void Swap(const T& A, const T& B)
    {
      //Get pointers to the actual links.
      DoubleLink* PointerA = GetLinkFromItem(A);
      DoubleLink* PointerB = GetLinkFromItem(B);

      //If links are the same, no swap is necessary.
      if(PointerA == PointerB)
        return;

      //Remember the original link pointers.
      DoubleLink* OldAPrev = PointerA->Prev;
      DoubleLink* OldANext = PointerA->Next;
      DoubleLink* OldBPrev = PointerB->Prev;
      DoubleLink* OldBNext = PointerB->Next;

      //Update the traversal optimization.
      if(LastReferenced == PointerA)
        LastReferenced = PointerB;
      else if(LastReferenced == PointerB)
        LastReferenced = PointerA;

      //Perform the swap depending on what the condition is.
      if(PointerA->Next == PointerB)
      {
        //Element A is just to the left of B.
        PointerB->Prev = OldAPrev;
        PointerB->Next = PointerA;
        PointerA->Prev = PointerB;
        PointerA->Next = OldBNext;

        //Fix adjacent links.
        if(OldAPrev)
          OldAPrev->Next = PointerB;
        else
          First = PointerB;

        if(OldBNext)
          OldBNext->Prev = PointerA;
        else
          Last = PointerA;
      }
      else if(PointerB->Next == PointerA)
      {
        //Element B is just to the left of A.
        PointerA->Prev = OldBPrev;
        PointerA->Next = PointerB;
        PointerB->Prev = PointerA;
        PointerB->Next = OldANext;

        //Fix adjacent links.
        if(OldBPrev)
          OldBPrev->Next = PointerA;
        else
          First = PointerA;

        if(OldANext)
          OldANext->Prev = PointerB;
        else
          Last = PointerB;
      }
      else
      {
        //There is a positive number of elements between A and B.
        Memory::Swap(PointerA->Prev, PointerB->Prev);
        Memory::Swap(PointerA->Next, PointerB->Next);

        //Fix adjacent links.
        if(OldAPrev)
          OldAPrev->Next = PointerB;
        else
          First = PointerB;

        if(OldANext)
          OldANext->Prev = PointerB;
        else
          Last = PointerB;

        if(OldBPrev)
          OldBPrev->Next = PointerA;
        else
          First = PointerA;

        if(OldBNext)
          OldBNext->Prev = PointerA;
        else
          Last = PointerA;
      }
    }

    ///Finds the i-th element by traversing the list from the beginning.
    T* TraverseFromBeginning(count i) const
    {
      //Test for out of bounds index.
      if(i < 0 || i >= Items)
      {
        LastReferencedIndex = -1;
        LastReferenced = 0;
        return 0;
      }

      //Traverse the list from the beginning.
      DoubleLink* Current = First;
      for(count j = 0; j < Items; j++)
      {
        if(j == i)
        {
          LastReferencedIndex = i;
          LastReferenced = Current;
          return &Current->Data;
        }
        Current = Current->Next;
      }

      //Could not find the element.
      LastReferencedIndex = -1;
      LastReferenced = 0;
      return 0;
    }

    ///Finds the i-th element by traversing the list from the end.
    T* TraverseFromEnd(count i) const
    {
      //Test for out of bounds index.
      if(i < 0 || i >= Items)
      {
        LastReferencedIndex = -1;
        LastReferenced = 0;
        return 0;
      }

      //Traverse the list from the beginning.
      DoubleLink* Current = Last;
      for(count j = Items - 1; j >= 0; j--)
      {
        if(j == i)
        {
          LastReferencedIndex = i;
          LastReferenced = Current;
          return &Current->Data;
        }
        Current = Current->Prev;
      }

      //Could not find the element.
      LastReferencedIndex = -1;
      LastReferenced = 0;
      return 0;
    }

    ///Finds the i-th element traversing from another element of known position.
    T* TraverseFromElement(count i, DoubleLink* Element,
      count ElementIndex) const
    {
      //Test for out of bounds index.
      if(i < 0 || i >= Items || ElementIndex < 0 ||
        ElementIndex >= Items || Element == 0)
      {
        LastReferencedIndex = -1;
        LastReferenced = 0;
        return 0;
      }

      if(i == ElementIndex)
      {
        //No traversal necessary.
        LastReferencedIndex = i;
        LastReferenced = Element;
        return &Element->Data;
      }
      else if(i > ElementIndex)
      {
        for(count j = ElementIndex; j <= i; j++)
        {
          //Traverse forward to the element.
          if(j == i)
          {
            LastReferencedIndex = i;
            LastReferenced = Element;
            return &Element->Data;
          }
          Element = Element->Next;
        }
      }
      else
      {
        for(count j = ElementIndex; j >= i; j--)
        {
          //Traverse backwards to the element.
          if(j == i)
          {
            LastReferencedIndex = i;
            LastReferenced = Element;
            return &Element->Data;
          }
          Element = Element->Prev;
        }
      }

      //Could not find element.
      LastReferencedIndex = -1;
      LastReferenced = 0;
      return 0;
    }

  public:

    ///Constructor initializes empty list.
    List<T>() : First(0), Last(0), LastReferenced(0), LastReferencedIndex(0),
      Items(0) {}

    ///Destructor
    ~List<T>()
    {
      //Traverse the list and delete all of the elements.
      DoubleLink* Current = First;
      for(count i = 0; i < Items; i++)
      {
        DoubleLink* Next = Current->Next;
        delete Current;
        Current = Next;
      }
    }

    ///Returns the number of items in the list as a shorthand for Size().
    inline count n(void) const {return Items;}

    /**Returns an item by index. If the next item returned is near to this
    index (i.e. sequential iteration), then the traversal time will be very
    fast.*/
    T& ith(count i) const
    {
      if(LastReferencedIndex > 0)
      {
        if(i < LastReferencedIndex)
        {
          //Determine whether to traverse from the reference element.
          if(i <= LastReferencedIndex / 2)
            return *TraverseFromBeginning(i);
          else
            return *TraverseFromElement(i, LastReferenced, LastReferencedIndex);
        }
        else
        {
          //Determine whether to traverse from the reference element.
          if(i <= Items + LastReferencedIndex / 2)
            return *TraverseFromElement(i, LastReferenced, LastReferencedIndex);
          else
            return *TraverseFromEnd(i);
        }
      }
      else
      {
        //Determine which end has the quickest traversal.
        if(i <= Items / 2)
          return *TraverseFromBeginning(i);
        else
          return *TraverseFromEnd(i);
      }
    }

    ///Gets an element reference using the familiar bracket notation.
    inline T& operator [] (count i) const {return ith(i);}

    /**Shorthand for getting the first element. Assumes there is at least one
    element in the list. Note lowercase is used because the method is treated
    like a mathematical variable.*/
    inline T& a(void) const {return *TraverseFromBeginning(0);}

    /**Shorthand for getting an element with respect to the end of the list.
    ItemsFromEnd must be nonnegative. Assumes there is at least one element in
    the list. Note lowercase is used because the method is treated like a
    mathematical variable.*/
    inline T& z(count ItemsFromEnd = 0) const {return *TraverseFromEnd(Items -
      1 - ItemsFromEnd);}

    ///Swaps the position of two elements without copying their internal data.
    void Swap(count i, count j)
    {
      //Check bounds and make sure the elements are not the same.
      if(i == j || i < 0 || j < 0 || i >= Items || j >= Items)
        return;

      //Swap the items.
      Swap(ith(i), ith(j));
    }

    ///Appends an element to the end of the list by copying the argument.
    void Append(const T& NewElement)
    {
      DoubleLink* NewLink = new DoubleLink;
      if(!Items)
        Last = First = NewLink;
      else
      {
        NewLink->Prev = Last;
        Last = Last->Next = NewLink;
      }

      NewLink->Data = NewElement;
      Items++;
    }

    /**Pushes an element to the end of the list as though it were a stack. This
    is equivalent to append.*/
    inline void Push(const T& NewElement)
    {
      Append(NewElement);
    }

    ///For adding an element to the list using its default constructor.
    T& Add(void)
    {
      DoubleLink* NewLink = new DoubleLink;

      if(!Items)
        Last = First = NewLink;
      else
      {
        NewLink->Prev = Last;
        Last = Last->Next = NewLink;
      }

      Items++;

      return z();
    }

    ///Prepends an element to the beginning of the list.
    void Prepend(const T& NewElement)
    {
      DoubleLink* NewLink = new DoubleLink;

      if(!Items)
        Last = First = NewLink;
      else
      {
        NewLink->Next = First;
        First = First->Prev = NewLink;
      }

      NewLink->Data = NewElement;

      Items++;

      //The reference link must be updated.
      LastReferencedIndex++;
    }

    ///Inserts an element before some other element referenced by index.
    void InsertBefore(const T& NewElement, count ElementAfter)
    {
      //Use normal appends if the index is at one of the ends.
      if(ElementAfter <= 0)
      {
        Prepend(NewElement);
        return;
      }
      if(ElementAfter >= Items)
      {
        Append(NewElement);
        return;
      }

      //Traverse the list to update the reference link.
      ith(ElementAfter);

      //Determine the correct links to squeeze the new element between.
      DoubleLink* LeftLink = LastReferenced->Prev;
      DoubleLink* RightLink = LastReferenced;
      DoubleLink* NewLink = new DoubleLink;

      //Update the link pointers.
      RightLink->Prev = LeftLink->Next = NewLink;
      NewLink->Prev = LeftLink;
      NewLink->Next = RightLink;

      //Copy the data.
      NewLink->Data = NewElement;

      //Increment the size.
      Items++;

      //Update the reference link.
      LastReferencedIndex = ElementAfter;
      LastReferenced = NewLink;
    }

    ///Inserts an element after some other element referenced by index.
    void InsertAfter(const T& NewElement, count ElementBefore)
    {
      //Use normal appends if the index is at one of the ends.
      if(ElementBefore < 0)
      {
        Prepend(NewElement);
        return;
      }
      if(ElementBefore >= Items - 1)
      {
        Append(NewElement);
        return;
      }

      //Traverse the list to update the reference link.
      ith(ElementBefore);

      //Determine the correct links to squeeze the new element between.
      DoubleLink* LeftLink = LastReferenced;
      DoubleLink* RightLink = LastReferenced->Next;
      DoubleLink* NewLink = new DoubleLink;

      //Update the link pointers.
      RightLink->Prev = LeftLink->Next = NewLink;
      NewLink->Prev = LeftLink;
      NewLink->Next = RightLink;

      //Copy the data.
      NewLink->Data = NewElement;

      //Increment the size.
      Items++;

      //The reference link is no good anymore.
      LastReferencedIndex = ElementBefore + 1;
      LastReferenced = NewLink;
    }

    ///Removes an item by its index.
    void Remove(count i)
    {
      //If index is out of bounds, no item is removed.
      if(i < 0 || i >= Items)
        return;

      /*Calling ith() will find the element using the reference link instead of
      having to traverse all the way through.*/
      ith(i);

      DoubleLink* LeftLink = LastReferenced->Prev;
      DoubleLink* RightLink = LastReferenced->Next;

      if(!LeftLink && !RightLink)
        First = Last = 0;
      else
      {
        if(LeftLink == 0)
          First = RightLink;
        else
          LeftLink->Next = RightLink;

        if(RightLink == 0)
          Last = LeftLink;
        else
          RightLink->Prev = LeftLink;
      }

      delete LastReferenced;

      Items--;

      if(LeftLink != 0)
      {
        LastReferencedIndex = i - 1;
        LastReferenced = LeftLink;
      }
      else if(RightLink != 0)
      {
        LastReferencedIndex = i;
        LastReferenced = RightLink;
      }
      else
      {
        LastReferencedIndex = -1;
        LastReferenced = 0;
      }
    }

    /**Removes an element from the list and calls delete on it. Only use this
    if the element is a pointer to an object on the heap.*/
    void RemoveAndDelete(count i)
    {
      delete ith(i);
      Remove(i);
    }

    /**Pops the element at the end of the list off as though it were a stack.
    This undoes Push().*/
    void Pop(void)
    {
      Remove(n() - 1);
    }

    ///Pops and deletes the element at the end of the list off.
    void PopAndDelete(void)
    {
      RemoveAndDelete(n() - 1);
    }

    /**Removes each element from the list and calls its destructor. Note if the
    element is a pointer to an object, then call RemoveAndDeleteAll to call
    delete on the pointers automatically.*/
    void RemoveAll(void)
    {
      while(Items > 0)
        Remove(0);
    }

    /**Deletes all elements and then removes them from the list. Only call this
    if the element is some kind of pointer to an object on the heap.*/
    void RemoveAndDeleteAll(void)
    {
      while(Items > 0)
      {
        delete ith(0);
        Remove(0);
      }
    }

    /**Copy constructor (use sparingly). Normally you would want to use
    references to a List rather than copy the whole thing.*/
    List<T>(const List<T> &Other) : First(0), Last(0),
      LastReferenced(0), LastReferencedIndex(0), Items(0)
    {
      count ItemCount = Other.Items;
      for(count i = 0; i < ItemCount; i++)
        Add() = Other[i];
    }

    ///Copy assigns a list by calling copy assignments on each of its items.
    List<T>& operator = (const List<T>& Other)
    {
      //Exit if the other list is the same as this one.
      if(&Other == this)
        return *this;

      //If anything is in this list, remove it first.
      RemoveAll();

      //Copy each item.
      count ItemCount = Other.Items;
      for(count i = 0; i < ItemCount; i++)
        Add() = Other[i];

      return *this;
    }
  };
}
#endif

//............................................................................//

#ifndef PRIM_SORTABLE_H
#define PRIM_SORTABLE_H

namespace prim
{
  ///Container primitives with various sorting algorithms
  struct Sortable
  {
    ///An array with sorting facilities
    template <class T>
    class Array : public prim::Array<T>
    {
      ///Private helper that implements Quicksort recursion.
      static void QuicksortRecursive(T* ArrayData, count Left, count Right)
      {
        count Pivot, LeftIndex = Left, RightIndex = Right;
        if(Right - Left <= 0)
          return;
        Pivot = (Left + Right) / 2;
        while(LeftIndex <= Pivot && RightIndex >= Pivot)
        {
          while(ArrayData[LeftIndex] < ArrayData[Pivot] && LeftIndex <= Pivot)
            LeftIndex = LeftIndex + 1;

          while(ArrayData[RightIndex] > ArrayData[Pivot] && RightIndex >= Pivot)
               RightIndex = RightIndex - 1;

          T SwapValue = ArrayData[LeftIndex];
          ArrayData[LeftIndex] = ArrayData[RightIndex];
          ArrayData[RightIndex] = SwapValue;
          LeftIndex++;
          RightIndex--;
          if(LeftIndex - 1 == Pivot)
            Pivot = RightIndex = RightIndex + 1;
          else if(RightIndex + 1 == Pivot)
            Pivot = LeftIndex = LeftIndex - 1;
        }
        QuicksortRecursive(ArrayData, Left, Pivot - 1);
        QuicksortRecursive(ArrayData, Pivot + 1, Right);
      }

      public:

      /**Returns whether or not the array is sorted.
      \code  c >> "Array.h: Sortable::Array::IsSorted";
      *  //Create an array of numbers in reverse order.
      *  Sortable::Array<number> a;
      *  for(count i = 5; i >= 1; i--)
      *    a.Add() = (number)i;
      *
      *  //Print out the numbers.
      *  for(count i = 0; i < a.n(); i++)
      *    c >> a[i];
      *
      *  //Test whether the array is sorted.
      *  c >> "IsSorted: " >> (a.IsSorted() ? "Yes" : "No");
      *
      *  //Sort the array and test again.
      *  c >> "Sorting...";
      *  a.Sort();
      *  c >> "IsSorted now: " >> (a.IsSorted() ? "Yes" : "No");
      *
      *  //Print out the numbers.
      *  for(count i = 0; i < a.n(); i++)
      *    c >> a[i];
      \endcode
      */
      bool IsSorted(void) const
      {
        for(count i = 0; i < prim::Array<T>::n() - 1; i++)
        {
          if(prim::Array<T>::ithConst(i) > prim::Array<T>::ithConst(i + 1))
            return false;
        }
        return true;
      }

      /**Runs the Quicksort routine.
      \code  c >> "Array.h: Sortable::Array::Quicksort";
      *  //Create an array of numbers in reverse order.
      *  Sortable::Array<integer> a;
      *  for(count i = 0; i < 10000; i++)
      *    a.Add() = (int16)(i * 1234567);
      *
      *  //Print out first 10 numbers.
      *  for(count i = 0; i < 10; i++)
      *    c >> a[i];
      *  c++;
      *
      *  //Sort explicitly using the Quicksort routine.
      *  a.Quicksort();
      *
      *  //Print out first 10 numbers.
      *  for(count i = 0; i < 10; i++)
      *    c >> a[i];
      \endcode
      */
      void Quicksort(void)
      {
        QuicksortRecursive(&prim::Array<T>::ith(0), 0, prim::Array<T>::n() - 1);
      }

      /**Determines if sorting is necessary and runs the most appropriate sort.
      \code  c >> "Array.h: Sortable::Array::Sort";
      *  //Create an array of numbers in reverse order.
      *  Sortable::Array<integer> a;
      *  for(count i = 0; i < 10000; i++)
      *    a.Add() = (int16)(i * 1234567);
      *
      *  //Print out first 10 numbers.
      *  for(count i = 0; i < 10; i++)
      *    c >> a[i];
      *  c++;
      *
      *  //Sort explicitly using the Quicksort routine.
      *  a.Quicksort();
      *
      *  //Print out first 10 numbers.
      *  for(count i = 0; i < 10; i++)
      *    c >> a[i];
      \endcode
      */
      void Sort(void)
      {
        if(IsSorted())
          return;

        Quicksort();
      }
    };

    ///A list with sorting facilities.
    template <class T>
    class List : public prim::List<T>
    {
      /**Internal data structure for QuickSort recursing. Since the QuickSort
      algorithm is massively recursive it overflows stack space very quickly. To
      cope with this inherent problem a non-recursing algorithm was implemented
      utilizing a heap-based stack. Keep in mind that for lists in the
      hundred-thousands of elements, the algorithm will quickly consume around
      10 or 20 megabytes.*/
      struct QuickSortStack
      {
        typename prim::List<T>::DoubleLink* Left;
        typename prim::List<T>::DoubleLink* Right;
        typename prim::List<T>::DoubleLink* Start;
        typename prim::List<T>::DoubleLink* Current;
        typename prim::List<T>::DoubleLink* OldCurrent;
        count Control;
        QuickSortStack* Next;

        ///Pushes a state onto the stack.
        void Push(QuickSortStack*& VarHead,
          typename prim::List<T>::DoubleLink* VarLeft,
          typename prim::List<T>::DoubleLink* VarRight,
          typename prim::List<T>::DoubleLink* VarStart,
          typename prim::List<T>::DoubleLink* VarCurrent,
          typename prim::List<T>::DoubleLink* VarOldCurrent,
          count VarControl)
        {
          Next = VarHead;
          VarHead = this;
          Left = VarLeft;
          Right = VarRight;
          Start = VarStart;
          Current = VarCurrent;
          OldCurrent = VarOldCurrent;
          Control = VarControl;
        }

        ///Pops the most recent state off the stack.
        QuickSortStack* Pop(QuickSortStack*& VarHead,
          typename prim::List<T>::DoubleLink*& VarLeft,
          typename prim::List<T>::DoubleLink*& VarRight,
          typename prim::List<T>::DoubleLink*& VarStart,
          typename prim::List<T>::DoubleLink*& VarCurrent,
          typename prim::List<T>::DoubleLink*& VarOldCurrent,
          count VarControl)
        {
          VarLeft = VarHead->Left;
          VarRight = VarHead->Right;
          VarStart = VarHead->Start;
          VarCurrent = VarHead->Current;
          VarOldCurrent = VarHead->OldCurrent;
          VarControl = VarHead->Control;
          QuickSortStack* OldHead = VarHead;
          VarHead = VarHead->Next;
          return OldHead;
        }

        ///Code control types which gate execution to one of three given paths.
        enum ControlType
        {
          FirstBranch,
          SecondBranch,
          ThirdBranch
        };

        ///Zeroing constructor.
        QuickSortStack() : Left(0), Right(0), Start(0), Current(0), OldCurrent(0),
          Control(0), Next(0) {}
      };

      public:

      ///Sorts the list using the QuickSort algorithm.
      void QuickSort(bool Ascending = true)
      {
        //Ensure there are at least two elements in the list.
        if(prim::List<T>::Items < 2)
          return;

        //Stack state variables
        typename prim::List<T>::DoubleLink* Left = prim::List<T>::First;
        typename prim::List<T>::DoubleLink* Right = prim::List<T>::Last;
        typename prim::List<T>::DoubleLink* Start = 0;
        typename prim::List<T>::DoubleLink* Current = 0;
        typename prim::List<T>::DoubleLink* OldCurrent = 0;
        count Control = QuickSortStack::FirstBranch;

        //Initialize stack state.
        QuickSortStack* Head = 0;

        //Start the control loop.
        do
        {
          switch(Control)
          {
          case QuickSortStack::FirstBranch:
            //Set the Start and the Current item pointers.
            Start = Left;
            Current = Left; //This is the algorithm's "pivot".

            //Loop until we encounter the right pointer.
            while(Current != Right)
            {
              //Move to the next item in the list
              Current = Current->Next;

              //Swap items if they are out of order.
              if(Ascending && Start->Data < Current->Data)
                Memory::Swap(Current->Data, Start->Data);
              else if(!Ascending && Start->Data > Current->Data)
                Memory::Swap(Current->Data, Start->Data);
            }

            //Swap the First and Current items.
            Memory::Swap(Left->Data, Current->Data);

            //Save this Current item.
            OldCurrent = Current;

            //Check if we need to sort the left-hand side of the Current point.
            Current = OldCurrent->Prev;

            if(Current && Left->Prev != Current && Current->Next != Left &&
              Left != Current)
            {
              Control = QuickSortStack::SecondBranch;
              //---------------SAVE----------------
              //Save the stack state.
              QuickSortStack* NewStackItem = new QuickSortStack;
              NewStackItem->Push(Head, Left, Right, Start, Current,
                OldCurrent, Control);
              //-----------------------------------
              Left = Left;
              Right = Current;
              Start = 0;
              Current = 0;
              OldCurrent = 0;
              Control = QuickSortStack::FirstBranch;
              break;
            }
            else
            {
              Control = QuickSortStack::SecondBranch;
              break;
            }
          case QuickSortStack::SecondBranch:
            //Check if we need to sort the right hand side of the Current point.
            Current = OldCurrent->Next;
            if(Current && Current->Prev != Right && Right->Next != Current
              && Current != Right)
            {
              Control = QuickSortStack::ThirdBranch;
              //---------------SAVE----------------
              //Save the stack state.
              QuickSortStack* NewStackItem = new QuickSortStack;
              NewStackItem->Push(Head, Left, Right, Start, Current,
                OldCurrent, Control);
              //-----------------------------------
              Left = Current;
              Right = Right;
              Start = 0;
              Current = 0;
              OldCurrent = 0;
              Control = QuickSortStack::FirstBranch;
              break;
            }
            else
            {
              Control = QuickSortStack::ThirdBranch;
              break;
            }
          case QuickSortStack::ThirdBranch:
            if(Head) //If no head, then we're ending anyway.
            {
              //--------------REVERT---------------
              //Revert to the previous stack state.
              QuickSortStack* StackToDelete = Head->Pop(Head, Left, Right,
                Start, Current, OldCurrent, Control);
              delete StackToDelete;
              //-----------------------------------
            }
          };
        } while(Head);
      }

      ///Bubble-sorts the list in either ascending or descending order.
      void BubbleSort(bool Ascending = true)
      {
        if(Ascending)
        {
          for(count i = 0; i < prim::List<T>::Items - 1; i++)
            for(count j = i + 1; j < prim::List<T>::Items; j++)
              if(prim::List<T>::ith(i) > prim::List<T>::ith(j))
                Swap(prim::List<T>::ith(i), prim::List<T>::ith(j));
        }
        else
        {
          for(count i = 0; i < prim::List<T>::Items - 1; i++)
            for(count j = i + 1; j < prim::List<T>::Items; j++)
              if(prim::List<T>::ith(i) < prim::List<T>::ith(j))
                Swap(prim::List<T>::ith(i), prim::List<T>::ith(j));
        }
      }

      /**Sorts using one of two algorithms. For smaller lists, BubbleSort is used
      in conjunction with link-pointer swapping. For bigger lists, the QuickSort
      algorithm is used with data copying.*/
      void Sort(bool Ascending = true)
      {
        if(prim::List<T>::Items < 50)
          BubbleSort(Ascending);
        else
          QuickSort(Ascending);
      }
    };

  };
}
#endif

#ifndef PRIM_STRING_H
#define PRIM_STRING_H

//Enables checking of string consistency per each string operation.
//#define PRIM_DEBUG_STRING
#ifdef PRIM_DEBUG_STRING
#include <iostream>
#endif

namespace prim
{
  namespace meta
  {
    ///Character used for when a bad Unicode character sequence is decoded.
    static const unicode BadCharacter = 0xFFFD; //Unicode replacement character
    //static const unicode BadCharacter = '?' //ASCII alternative...
  }

  /**Efficient flat container of linked-substrings. The string is equally fast
  at append, prepend, insert, and erase, with nearly constant manipulation
  speed with respect to string length.*/
  class String
  {
    public:
    /**Representation of a UTF-32 string stored in system endianness. Since it
    is just an array of unicode values, it does not have any string operation
    methods. To use those methods, append the String::UTF32 to an empty
    string.*/
    typedef Array<unicode> UTF32;

    private:
    ///Container of linked-substrings.
    mutable Array<byte> Data;

    ///Total length of the combined fragments.
    mutable count InternalLength;

    ///Starting position of the last fragment.
    mutable count LastFragmentIndex;

    //--------//
    //Iterator//
    //--------//

    //Iterator needs to access the Data member.
    friend struct Iterator;

    ///Internal iterator used by the string manipulator methods.
    struct Iterator
    {
      ///The string character index at the fragment beginning.
      count i;

      ///The index of the fragment data.
      count f;

      ///The length of the fragment.
      count n;

      ///Location of the previous next-marker.
      count p;

      ///Delay mechanism so that copied iterators will begin correctly.
      bool DelayIterator;

      ///Resets the iterator to the beginning of the string.
      void Reset(void)
      {
        i = 0;
        f = 1;
        n = 0;
        p = 1;
        DelayIterator = false;
      }

      ///Constructor from integer to initialize from default parameter.
      Iterator()
      {
        Reset();
      }

      ///Copy constructor with delay mechanism turned on
      Iterator(const Iterator& Other) : i(Other.i), f(Other.f), n(Other.n),
        DelayIterator(true) {}

      ///Operator= with delay mechanism turned on
      Iterator& operator = (const Iterator& Other)
      {
        i = Other.i;
        f = Other.f;
        n = Other.n;
        DelayIterator = true;
        return *this;
      }

      ///Hops to the next fragment.
      count Next(const String* s)
      {
        //If delaying, hold off for one iteration if the fragment is valid.
        if(DelayIterator && f != 1)
        {
          DelayIterator = false;
          return -1;
        }

        //If starting, go to the first fragment.
        if(f == 1)
        {
          i = 0;
          f = s->ReadMarker(1);
          n = s->ReadMarker(f);
          return f;
        }

        //If the end of the string is reached, just leave.
        if(n == 0)
          return 0;

        //Increase string index.
        i += n;

        //Determine next fragment length.
        p = f + 4 + n;
        f = s->ReadMarker(p);
        if(!f)
          n = 0;
        else
          n = s->ReadMarker(f);

        return f;
      }

      ///Checks whether the requested character index is in this fragment.
      inline bool Contains(count j)
      {
        return j >= i && j < i + n;
      }
    };

    ///The default iterator is used for Get() operations.
    mutable Iterator DefaultIterator;

    //-------------------//
    //Character Retrieval//
    //-------------------//

    ///Internal use only. Gets a character at the specified index.
    inline byte Get(count i) const
    {
      //If index is out of bounds return null.
      if(i < 0 || i >= InternalLength)
        return 0;

      //If the iterator is not useful then reset it.
      if(i < DefaultIterator.i)
        DefaultIterator.Reset();

      //Start iterating on the current fragment.
      DefaultIterator.DelayIterator = true;
      while(DefaultIterator.Next(this))
      {
        if(i < DefaultIterator.i + DefaultIterator.n)
          return Data[DefaultIterator.f + 4 + (i - DefaultIterator.i)];
      }
      return 0;
    }

    //--------------//
    //Marker Control//
    //--------------//

    ///Internal use only. Reads a marker at some index.
    inline uint32 ReadMarker(count Index) const
    {
#ifdef PRIM_DEBUG_STRING
      using namespace std;
      //Sanity check--debug only.
      if(Index < 0 || Index + 4 > Data.n())
      {
        PrintData();
        cout << "The requested marker position is bad." << endl;
        cout.flush();
      }
#endif
      return *((uint32*)&Data[Index]);
    }

    ///Internal use only. Writes a marker value at some index.
    inline void WriteMarker(count Index, uint32 Value)
    {
#ifdef PRIM_DEBUG_STRING
      using namespace std;
      //Sanity check--debug only.
      if(Index < 0 || Index + 4 > Data.n())
      {
        PrintData();
        cout << "The requested marker position is bad." << endl;
        cout.flush();
      }
#endif
      *((uint32*)&Data[Index]) = Value;
    }

    ///Assumes there is space has been allocated.
    void WriteFragment(count Index, count Length, const byte* Fragment,
      count Next)
    {
      WriteMarker(Index, (uint32)Length);
      WriteMarker(Index + 4 + Length, (uint32)Next);
      Memory::Copy(&Data[Index + 4], Fragment, Length);
    }

    //------------//
    //Optimization//
    //------------//

    /**Internal use only. Ensures that the string will never exceed twice its
    length in its representation. For example, this happens when a lot of short
    strings are inserted causing the majority of the data to be link data.*/
    void CollapseBloatedLinks(void)
    {
      if(Data.n() > InternalLength * 2)
        Merge();
    }

    //-----//
    //Debug//
    //-----//

    ///Binary dump of current string array data. Debug use only.
    void PrintData(void) const
    {
#ifdef PRIM_DEBUG_STRING
      using std::cout;
      cout << std::endl << "BEGIN (ROWS CONTAIN 16 BYTES)" << std::endl;
      cout << "0    1    2    3    4    5    6    7    8"
        "    9    10   11   12   13   14   15" << std::endl;
      cout << "=----=----=----=----=----=----=----=----="
        "----=----==---==---==---==---==---==---";

      for(count i = 0; i < Data.n(); i++)
      {
        if(i % (80 / 5) == 0)
          cout << std::endl;

        byte c = Data[i];

        if(c >= (byte)' ' && c <= (byte) '~')
          cout << (ascii)c;
        else
          cout << " ";

        if(c < 10)
          cout << "  " << (int)c;
        else if(c < 100)
          cout << " " << (int)c;
        else
          cout << "" << (int)c;

        cout << " ";
      }
      cout << std::endl;
      cout << "LAST FRAGMENT INDEX: " << LastFragmentIndex << std::endl;
      cout << "INTERNAL LENGTH: " << InternalLength << std::endl;
      cout << "END" << std::endl;
#endif
    }

    ///Checks the internal consistency of the string. Debug use only.
    bool CheckConsistency(void)
    {
#ifdef PRIM_DEBUG_STRING
      using std::cout;
      using std::endl;

      //Check empty string.
      if(InternalLength == 0)
      {
        if(Data.n() != 0 || LastFragmentIndex != 0)
        {
          cout << "Bad empty string" << endl; cout.flush();
          PrintData();
          return false;
        }
      }

      if(Data.n() == 0)
      {
        if(InternalLength != 0 || LastFragmentIndex != 0)
        {
          cout << "Bad empty string" << endl; cout.flush();
          PrintData();
          return false;
        }
      }

      if(LastFragmentIndex == 0)
      {
        if(InternalLength != 0 || LastFragmentIndex != 0)
        {
          cout << "Bad empty string" << endl; cout.flush();
          PrintData();
          return false;
        }
        else
          return true;
      }

      if(Data[0] != 0)
      {
        cout << "Bad null boundary character" << endl; cout.flush();
        PrintData();
        return false;
      }

      Iterator q;
      count ActualLength = 0;
      count LastF = 0;
      while(q.Next(this))
      {
        LastF = q.f;
        ActualLength += q.n;
      }

      if(ActualLength != InternalLength)
      {
        cout << "Bad internal length (expected " << ActualLength <<
          ")" << endl; cout.flush();
        PrintData();
        return false;
      }

      if(LastF != LastFragmentIndex)
      {
        cout << "Bad last fragment index (expected " << LastF <<
          ")" << endl; cout.flush();
        PrintData();
        return false;
      }
#endif
      return true;
    }

    public:

    ///Represents an interval of characters in a string by index.
    typedef Complex<count> Span;

    //------------------------//
    //Fundamental Manipulators//
    //------------------------//

    virtual void Append(const byte* Fragment, count Length)
    {
      //If there is no content to add, then just leave.
      if(Length <= 0 || !Fragment)
        return;

      if(InternalLength == 0)
      {
        //Create first fragment of initially empty string.
        Data.n(1 + 4 + 4 + Length + 4);
        Data[0] = 0;
        WriteMarker(1, 5);
        WriteFragment(5, Length, Fragment, 0);
        LastFragmentIndex = 5;
      }
      else if(LastFragmentIndex + 4 + ReadMarker(LastFragmentIndex) + 4 ==
        (uint32)Data.n())
      {
        //Last fragment is at end, so it can be extended.
        Data.n(Data.n() + Length);
        count OldFragmentLength = ReadMarker(LastFragmentIndex);
        count NewFragmentLength = OldFragmentLength + Length;
        WriteMarker(LastFragmentIndex, (uint32)NewFragmentLength);
        Memory::Copy(&Data[LastFragmentIndex + 4 + OldFragmentLength],
          Fragment, Length);
        WriteMarker(LastFragmentIndex + 4 + NewFragmentLength, 0);
      }
      else
      {
        //Last fragment not at end, so a new fragment must be created.
        count OldStringLength = Data.n();
        Data.n(OldStringLength + 4 + Length + 4);
        WriteMarker(LastFragmentIndex + 4 + ReadMarker(LastFragmentIndex),
          (uint32)OldStringLength);
        WriteFragment(OldStringLength, Length, Fragment, 0);
        LastFragmentIndex = OldStringLength;
      }

      //Increase the internal length.
      InternalLength += Length;

      //Reset the default iterator.
      DefaultIterator.Reset();

      //Optimize links.
      CollapseBloatedLinks();
    }

    ///Prepends a byte string of a certain length.
    void Prepend(const byte* Fragment, count Length)
    {
      //If there is no content to add, then just leave.
      if(Length <= 0 || !Fragment)
        return;

      //Prepend = Append for length zero string, so use the simpler Append.
      if(InternalLength == 0)
      {
        Append(Fragment, Length);
        return;
      }

      //Add a new fragment containing the prepended string.
      uint32 OriginalFirstFragment = ReadMarker(1);
      count OldStringLength = Data.n();
      Data.n(OldStringLength + Length + 4 + 4);
      WriteFragment(OldStringLength, Length, Fragment, OriginalFirstFragment);
      WriteMarker(1, (uint32)OldStringLength);
      InternalLength += Length;

      //Reset the default iterator.
      DefaultIterator.Reset();

      //Optimize string.
      CollapseBloatedLinks();
    }

    /**Combines all the string fragments to form a single contiguous string. It
    returns a pointer to the byte or ASCII data. The end of the string will
    always contain a null-terminator regardless of the string contents. Note
    that Merge is declared const because it only changes the representation of
    the content of the string, not the content itself.*/
    const ascii* Merge(void) const
    {
      /*This is a little bit spurious, but it prevents us from having to
      allocate array space on the heap for a null string. Since InternalLength
      is zero, we can safely set the zero-length ascii* null-terminated string
      here.*/
      if(InternalLength == 0)
        return (const ascii*)&InternalLength;

      /*If already merged, do not create a new copy. This is determined by
      checking whether the string takes up the smallest possible space.*/
      if(Data.n() == 1 + 4 + 4 + InternalLength + 4)
        return (ascii*)&Data[1 + 4 + 4];

      //Create an array to the flattened string data.
      Array<byte> FlatData;
      FlatData.n(1 + 4 + 4 + InternalLength + 4);
      FlatData[0] = 0;
      *((uint32*)&FlatData[1]) = 1 + 4;
      *((uint32*)&FlatData[5]) = (uint32)InternalLength;
      *((uint32*)&FlatData[1 + 4 + 4 + InternalLength]) = 0;

      //Location of flattened string in data.
      byte* NewString = &FlatData[1 + 4 + 4];

      //Iterate through fragments and copy substrings one by one.
      Iterator q;
      while(q.Next(this))
        Memory::Copy(&NewString[q.i], &Data[q.f + 4], q.n);

      //Now switch array data, so that the old data goes out of scope.
      Data.SwapWith(FlatData);
      LastFragmentIndex = 1 + 4;

      //Reset the default iterator.
      DefaultIterator.Reset();

      //Return pointer to new string.
      return (ascii*)NewString;
    }

    ///Inserts a fragment before the character at the index.
    void Insert(const byte* Fragment, count Length, count IndexBefore)
    {
      //If there is no content to add, then just leave.
      if(Length <= 0 || !Fragment)
        return;

      //If index is 0 or below, then this is a prepend.
      if(IndexBefore <= 0)
      {
        Prepend(Fragment, Length);
        return;
      }

      //If index is n or above, then this is a prepend.
      if(IndexBefore >= InternalLength)
      {
        Append(Fragment, Length);
        return;
      }

      //Add length of incoming fragment to length of total string.
      InternalLength += Length;
      Iterator q;
      while(q.Next(this))
      {
        if(q.i + q.n == IndexBefore)
        {
          //Inserting in between two fragments.
          count OldLength = Data.n();
          Data.n(OldLength + 4 + Length + 4);
          count NextIndex = q.f + 4 + q.n;
          count RightFragment = ReadMarker(NextIndex);
          WriteFragment(OldLength, Length, Fragment, RightFragment);
          WriteMarker(NextIndex, (uint32)OldLength);
          break;
        }
        else if(q.Contains(IndexBefore))
        {
          count IndexInFragment = IndexBefore - q.i;
          count OldLength = Data.n();

          /*There will always be at least one character on the left, since the
          above case takes care of fragment insert.*/

          //-----//
          //Cases//
          //-----//

          //1) Partition (large enough to hold NEXTLENG and 1 char each side)
          if(q.n - IndexInFragment > 8)
          {
            count SquashStart = q.f + 4 + IndexInFragment;
            uint32 SquashedCharacters[2] = {ReadMarker(SquashStart),
              ReadMarker(SquashStart + 4)};
            Data.n(OldLength + 4 + (4 + 4) + Length + 4);

            //Write fragment A length.
            WriteMarker(q.f, (uint32)IndexInFragment);

            //Write fragment A pointer.
            WriteMarker(SquashStart, (uint32)OldLength);

            //Write fragment C length (pointer does not change).
            WriteMarker(SquashStart + 4,
              (uint32)(q.n - IndexInFragment - (4 + 4)));

            //Write fragment B length.
            WriteMarker(OldLength, (uint32)(Length + (4 + 4)));

            //Copy fragment B data.
            Memory::Copy(&Data[OldLength + 4], Fragment, Length);

            //Copy fragment B first squash part data.
            WriteMarker(OldLength + 4 + Length, SquashedCharacters[0]);

            //Copy fragment B second squash part data.
            WriteMarker(OldLength + 4 + Length + 4, SquashedCharacters[1]);

            //Write fragment B pointer.
            WriteMarker(OldLength + 4 + Length + 4 + 4,
              (uint32)(SquashStart + 4));

            //Update last fragment index if necessary.
            if(LastFragmentIndex == q.f)
              LastFragmentIndex = SquashStart + 4;
          }

          /*2) Total absorb and collapse -- there is no space for pointer
          redirection in the existing fragment.*/
          else if(q.n < 1 + (4 + 4) + 1)
          {
            //Precalculate some constants.
            count LeftSideLength = IndexBefore - q.i;
            count RightSideLength = q.n - LeftSideLength;
            count NewFragmentLength = LeftSideLength + Length + RightSideLength;

            //Resize the data array to make room for the new fragment.
            Data.n(OldLength + 4 + LeftSideLength +
              Length + RightSideLength + 4);

            //Point previous fragment to new fragment.
            WriteMarker(q.p, (uint32)OldLength);

            //Length of new amalgamated fragment.
            WriteMarker(OldLength, (uint32)NewFragmentLength);

            //Subfragment 1 (left) copy
            Memory::Copy(&Data[OldLength + 4], &Data[q.f + 4], LeftSideLength);

            //Subfragment 2 (incoming) copy
            Memory::Copy(&Data[OldLength + 4 + LeftSideLength],
              Fragment, Length);

            //Subfragment 3 (right) copy
            Memory::Copy(&Data[OldLength + 4 + LeftSideLength + Length],
              &Data[q.f + 4 + LeftSideLength], RightSideLength);

            //Pointer to next fragment
            WriteMarker(OldLength + 4 + NewFragmentLength,
              ReadMarker(q.f + 4 + q.n));

            //Clear out original fragment.
            Memory::Clear(&Data[q.f], q.n + 8);

            //Update last fragment index.
            if(LastFragmentIndex == q.f)
              LastFragmentIndex = OldLength;

            //Update iterator.
            q.f = OldLength;
            q.n = NewFragmentLength;
          }

          //3) Right-side absorb
          else
          {
            //Precalculate some constants.
            count EightCharAbsorbStart = q.f + 4 + q.n - 8;
            count LeftSideLength = (IndexBefore - q.i) - (q.n - 8);
            count RightSideLength = 8 - LeftSideLength;
            count NewFragmentLength = LeftSideLength + Length + RightSideLength;

            //Resize the data array to make room for the new fragment.
            Data.n(OldLength + 4 + LeftSideLength +
              Length + RightSideLength + 4);

            //Length of new amalgamated fragment.
            WriteMarker(OldLength, (uint32)NewFragmentLength);

            //Subfragment 1 (left) copy
            Memory::Copy(&Data[OldLength + 4],
              &Data[EightCharAbsorbStart], LeftSideLength);

            //Subfragment 2 (incoming) copy
            Memory::Copy(&Data[OldLength + 4 + LeftSideLength],
              Fragment, Length);

            //Subfragment 3 (right) copy
            Memory::Copy(&Data[OldLength + 4 + LeftSideLength + Length],
              &Data[EightCharAbsorbStart + LeftSideLength], RightSideLength);

            //Pointer to next fragment
            WriteMarker(OldLength + 4 + NewFragmentLength,
              ReadMarker(q.f + 4 + q.n));

            //Pointer to new fragment from old fragment
            WriteMarker(EightCharAbsorbStart, (uint32)OldLength);

            //Update old fragment length.
            WriteMarker(q.f, (uint32)(EightCharAbsorbStart - (q.f + 4)));

            //Clear out original fragment.
            Memory::Clear(&Data[EightCharAbsorbStart + 4], 8);

            //Update last fragment index.
            if(LastFragmentIndex == q.f)
              LastFragmentIndex = OldLength;

            //Update iterator.
            q.n = ReadMarker(q.f);
          }

          //Insert is finished.
          break;
        }
      }

      //Reset the default iterator.
      DefaultIterator.Reset();
    }

    /**Erases any characters that exist from i to j. If j < i, then no
    characters are erased.*/
    void Erase(count i, count j)
    {
      Iterator q;

      //If no characters to erase, then leave.
      if(!InternalLength)
        return;

      //If j < i, then no characters should be erased.
      if(j < i)
        return;

      //If i >= n or j < 0 then no characters need to be erased.
      if(i >= InternalLength || j < 0)
        return;

      //If i is out of bounds, then bring it back in bounds.
      if(i < 0)
        i = 0;

      //If j is out of bounds, then bring it back in bounds.
      if(j >= InternalLength)
        j = InternalLength - 1;

      //Number of characters to erase
      count EraseLength = j - i + 1;

      //If erasing the whole string, just clear it.
      if(EraseLength == InternalLength)
      {
        Clear();
        return;
      }

      //Subtract length of erased portion.
      InternalLength -= ((j + 1) - i);

      //Tracks the last seen fragment for last fragment index update.
      Iterator LastSeenFragment = q;

      while(q.Next(this))
      {
        //Get the left and right boundaries of the fragment.
        count l = q.i, r = q.i + q.n - 1;

        if(r < i)
        {
          //The iterator has not hit an erasure point yet.
          LastSeenFragment = q;
        }
        else if(l > j)
        {
          /*The iterator is past the erasure point, so the iterator may stop.
          Also, since this means the last fragment was not touched, the last
          fragment index does not change either.*/
          break;
        }
        else if(i <= l && j >= r)
        {
          //The entire fragment may be erased.

          //Calculate the previous pointer position.
          count PrevPointerPosition;
          if(LastSeenFragment.f != 1)
          {
            PrevPointerPosition = LastSeenFragment.f + 4 +
              ReadMarker(LastSeenFragment.f);
          }
          else
            PrevPointerPosition = 1;

          //Update previous pointer.
          WriteMarker(PrevPointerPosition, ReadMarker(q.f + 4 + q.n));

          //Do not clear the next pointer since iteration must continue.
          Memory::Clear(&Data[q.f], 4 + q.n);

          //If the last fragment was cleared, update the last fragment index.
          if(q.f == LastFragmentIndex)
            LastFragmentIndex = LastSeenFragment.f;
        }
        else if(i <= l && (j >= l && j < r))
        {
          //Perform a left trim.

          //Make a new length.
          count NewFragmentPosition = q.f + (j + 1 - q.i);
          WriteMarker(NewFragmentPosition, (uint32)(q.n - (j + 1 - q.i)));

          //Calculate the previous pointer position.
          count PrevPointerPosition;
          if(LastSeenFragment.f != 1)
          {
            PrevPointerPosition = LastSeenFragment.f + 4 +
              ReadMarker(LastSeenFragment.f);
          }
          else
            PrevPointerPosition = 1;

          //Update previous pointer.
          WriteMarker(PrevPointerPosition, (uint32)NewFragmentPosition);

          //If the last fragment was cleared, update the last fragment index.
          if(q.f == LastFragmentIndex)
            LastFragmentIndex = NewFragmentPosition;

          //By definition the erasing is over if left trim was used.
          break;
        }
        else if(j >= r && (i > l && i <= r))
        {
          //Perform a right trim.

          //Move next pointer down.
          count FragmentALength = i - q.i;
          WriteMarker(q.f + 4 + FragmentALength, ReadMarker(q.f + 4 + q.n));

          /*Update iterator so it does not break when it looks for the pointer,
          and also adjust bounds of erasure so erase does not overshoot.*/
          j -= (q.n - FragmentALength);
          q.n = FragmentALength;

          //Adjust length.
          WriteMarker(q.f, (uint32)FragmentALength);

          //Remember that this fragment was kept.
          LastSeenFragment = q;
        }
        else
        {
          /*Excise within fragment. There are three cases:
              1) Large excise, in middle of long fragment
              2) Small excise, in middle of long fragment
              3) Small excise near right edge of long fragment*/
          if(EraseLength < (4 + 4))
          {
            //Small excise
            if((i - q.i) + (4 + 4) < q.n)
            {
              //In middle: create new fragment for squashed characters.
              count SquashedLength = (4 + 4) - EraseLength;
              count SquashedStart = q.f + 4 + (j + 1 - q.i);
              count NewFragmentStart = Data.n();
              count FragmentALength = i - q.i;
              count FragmentBStart = q.f + 4 + FragmentALength + 4;
              count FragmentBLength = q.n - FragmentALength - (4 + 4);

              //Create a new fragment for the squashed characters.
              Data.n(NewFragmentStart + 4 + SquashedLength + 4);
              WriteMarker(NewFragmentStart, (uint32)SquashedLength);
              Memory::Copy(&Data[NewFragmentStart + 4], &Data[SquashedStart],
                SquashedLength);
              WriteMarker(NewFragmentStart + 4 + SquashedLength,
                (uint32)FragmentBStart);

              //Update fragment A length.
              WriteMarker(q.f, (uint32)FragmentALength);

              //Point fragment A to the squashed fragment.
              WriteMarker(q.f + 4 + FragmentALength, (uint32)NewFragmentStart);

              //Set fragment B length.
              WriteMarker(q.f + 4 + FragmentALength + 4,
                (uint32)FragmentBLength);

              //If the last fragment was altered, update last fragment index.
              if(q.f == LastFragmentIndex)
                LastFragmentIndex = FragmentBStart;
            }
            else
            {
              //Near right edge: shift characters down including pointer.
              count ShiftStart = q.f + 4 + (i - q.i);
              count ShiftDistance = EraseLength;
              count ShiftSize = q.n - (j + 1 - q.i) + 4;
              for(count k = ShiftStart; k < ShiftStart + ShiftSize; k++)
                Data[k] = Data[k + ShiftDistance];

              //Update the fragment length.
              WriteMarker(q.f, (uint32)(q.n - EraseLength));

              /*Since fragment beginnings were not created or altered, there is
              no need to update the last fragment index.*/
            }
          }
          else
          {
            /*Note that it is implied that since this is not a fragment trim
            operation, the maximum value of 'j' is the position of the second-
            to-last character of the fragment. Thus, with an erase length of
            at least 4 + 4, there will be enough room in the erasure space to
            create a new length-pointer marker.*/

            /*Large excise using pointers to skip erased section. Fragment is
            split into two fragments A and B using erased character space for
            the length-pointer markers.*/

            //Adjust fragment A length.
            count FragmentALength = i - q.i;
            WriteMarker(q.f, (uint32)FragmentALength);

            //Write fragment A pointer to fragment B.
            count FragmentBStart = q.f + 4 + ((j + 1) - q.i) - 4;
            WriteMarker(q.f + 4 + FragmentALength, (uint32)FragmentBStart);

            //Write fragment B length (fragment B pointer to next is the same).
            count FragmentBLength = q.n - (j - q.i) - 1;
            WriteMarker(FragmentBStart, (uint32)FragmentBLength);

            //Clear any additional erased space.
            Memory::Clear(&Data[q.f + 4 + FragmentALength + 4],
              EraseLength - (4 + 4));

            //If the last fragment was altered, update the last fragment index.
            if(q.f == LastFragmentIndex)
              LastFragmentIndex = FragmentBStart;
          }

          /*Since the excise occurred within the fragment, the operation is
          complete.*/
          break;
        }
      }

      //Reset the default iterator.
      DefaultIterator.Reset();
    }

    ///Wrapper to insert null-terminated string.
    void Insert(const ascii* s, count IndexBefore)
    {
      Insert((const byte*)s, LengthOf(s), IndexBefore);
    }

    ///Wrapper to append null-terminated string.
    void Append(const ascii* s) {Append((const byte*)s, LengthOf(s));}

    ///Wrapper to prepend null-terminated string.
    void Prepend(const ascii* s) {Prepend((const byte*)s, LengthOf(s));}

    ///Clears the string so that it is zero-length and has no data on the heap.
    inline void Clear(void)
    {
      //Zero out the members.
      Data.n(LastFragmentIndex = InternalLength = 0);

      //Reset the default iterator.
      DefaultIterator.Reset();
    }

    /**Replaces a fragment with another string. The method first erases the
    fragment to be replaced, and then inserts the new string.*/
    void Replace(count SourceIndex, count SourceLength, byte* Destination,
      count DestinationLength)
    {
      Erase(SourceIndex, SourceIndex + SourceLength - 1);
      Insert(Destination, DestinationLength, SourceIndex);
    }

    ///Wrapper to replace fragment with null-terminated string.
    void Replace(count SourceIndex, count SourceLength, ascii* Destination)
    {
      Replace(SourceIndex, SourceLength, (byte*)Destination,
        LengthOf(Destination));
    }

    //------------------//
    //Character Indexing//
    //------------------//

    ///Gets a character at the specified index.
    inline byte operator [] (count i) const
    {
      return Get(i);
    }

    //----------------//
    //Find and Replace//
    //----------------//

    /**Finds the next occurrence of the source string. Returns -1 if no match
    is found. Use StartIndex to start the find at a different position. Also,
    if StartIndex is less than 0, then no find occurs and -1 is returned.*/
    count Find(const byte* Source, count SourceLength, count StartIndex) const
    {
      if(!Source || SourceLength == 0 || InternalLength == 0 || StartIndex < 0)
        return -1;

      count MaxCharacter = InternalLength - SourceLength;

      if(Data.n() == 1 + 4 + 4 + InternalLength + 4)
      {
        //Take advantage of a merged string by randomly accessing.
        const byte* StringStart = &((const byte*)Merge())[StartIndex];
        for(count i = StartIndex; i <= MaxCharacter; i++, StringStart++)
        {
          bool MatchFound = true;
          for(count j = 0; j < SourceLength; j++)
          {
            if(StringStart[j] != Source[j])
            {
              MatchFound = false;
              break;
            }
          }
          if(MatchFound)
            return i;
        }
      }
      else
      {
        /*If not merged use the slower but more string-manipulation friendly
        find which uses an iterator.*/
        for(count i = StartIndex; i <= MaxCharacter; i++)
        {
          bool MatchFound = true;
          for(count j = 0; j < SourceLength; j++)
          {
            if(Get(i + j) != Source[j])
            {
              MatchFound = false;
              break;
            }
          }
          if(MatchFound)
            return i;
        }
      }
      return -1;
    }

    ///Wrapper to find next occurrence of source string
    count Find(const ascii* Source, count StartIndex) const
    {
      return Find((byte*)Source, LengthOf(Source), StartIndex);
    }

    ///Wrapper to find first occurrence of source string
    count Find(const ascii* Source) const
    {
      return Find(Source, 0);
    }

    /**Globally replaces source string with destination string. Returns the
    number of replacements made.*/
    count Replace(const ascii* Source, const ascii* Destination)
    {
      count Replacements = 0;

      //Precalculate lengths of strings.
      count SourceLength = LengthOf(Source);
      count DestinationLength = LengthOf(Destination);

      //For each occurrence of the source, replace it with the destination.
      count Next = Find((byte*)Source, SourceLength, 0);
      while(Next != -1)
      {
        Replace(Next, SourceLength, (byte*)Destination, DestinationLength);
        Replacements++;
        Next = Find((byte*)Source, SourceLength, Next + DestinationLength);
      }

      //Return the number of replacements made.
      return Replacements;
    }

    ///Returns whether the string contains the source string.
    bool Contains(const ascii* Source) const
    {
      return Find(Source) != -1;
    }

    ///Returns a substring of characters between two indices inclusively.
    String Substring(count i, count j) const
    {
      if(i < 0 || j < i || j >= n())
        return "";

      return String((byte*)&(Merge()[i]), j - i + 1);
    }

    ///Returns a substring of characters between two indices inclusively.
    String Substring(String::Span Selection) const
    {
      return Substring(Selection.i(), Selection.j());
    }

    /**Returns the start and end index of the next string containing the tokens.
    If no start is found then <-1, -1> is returned. If a start is found, but no
    end is found then <Start Index, -1> is returned. If no span is found, then
    BetweenText will be empty as well.*/
    String::Span FindBetween(const ascii* Begin, const ascii* End,
      String& BetweenText, count StartIndex = 0) const
    {
      BetweenText = "";
      count StartPlace = Find(Begin, StartIndex);
      if(StartPlace == -1)
        return String::Span(-1, -1);
      count BeginLength = LengthOf(Begin);
      count EndPlace = Find(End, StartPlace + BeginLength);
      BetweenText = Substring(String::Span(StartPlace + BeginLength,
        EndPlace - 1));
      return String::Span(StartPlace, EndPlace + LengthOf(End) - 1);
    }

    /**Finds which pair of tokens is next. Returns the index if one is found,
    and otherwise, or if the lists are not of equal size, returns -1. Call
    FindBetween using the given tokens to then determine the location of the
    token pair.*/
    count FindBetweenAmong(const List<String>& StartTokens,
      const List<String>& EndTokens, String::Span& Location,
      String& BetweenText, count StartIndex = 0) const
    {
      if(StartTokens.n() != EndTokens.n())
        return -1;

      count LeastIndex = -1, IndexOfFound = -1;

      for(count i = 0; i < StartTokens.n(); i++)
      {
        String FindBetweenText;
        String::Span Next = FindBetween(StartTokens[i], EndTokens[i],
          FindBetweenText, StartIndex);
        if(Next.j() == -1)
          continue;
        if(Next.i() < LeastIndex || LeastIndex == -1)
        {
          Location = Next;
          BetweenText = FindBetweenText;
          LeastIndex = Next.i();
          IndexOfFound = i;
        }
      }
      return IndexOfFound;
    }

    //----------------//
    //Operator Appends//
    //----------------//

    ///String used for newlines. Unix and Mac use 0x0A LF, Windows will

    ///Unix and Mac newline
    static const ascii* LF;

    ///Microsoft Windows newline
    static const ascii* CRLF;

    ///Global newline operator for ++ operations.
    static const ascii* Newline;

    ///Appends a space to the string.
    void operator -- (int Dummy)
    {
      Dummy = 0;
      Append(" ");
    }

    ///Appends a new line to the string.
    void operator ++ (int Dummy)
    {
      Dummy = 0;
      Append(Newline);
    }

    ///Returns whether the string starts with the source.
    bool StartsWith(const ascii* Source) const
    {
      return Find(Source) == 0;
    }

    ///Returns whether the string ends with the source.
    bool EndsWith(const ascii* Source) const
    {
      count SourceLength = LengthOf(Source);
      return Find((byte*)Source, SourceLength,
        InternalLength - SourceLength) != -1;
    }

    /**Returns whether the string matches the other byte for byte.
    \code
    *  String a = "Hello";
    *  a -= "World!";
    *  if(a == "Hello World!")
    *    c += "The strings match.";
    *  else
    *    c += "Uh oh, the strings do not match!";
    *  a = "";
    *  if(a == "")
    *    c += "Empty strings match, too.";
    *  else
    *    c += "Uh oh, empty strings did not match!";
    *  a = "Hmm";
    *  if(a == "Hmmmmm")
    *    c += "Uh oh, different length strings matched!";
    *  else
    *    c += "Different length strings did not match";
    *  a = "Hello";
    *  if(a == "Hexxo")
    *    c += "Uh oh, same length different strings matched!";
    *  else
    *    c += "Same length different strings did not match";
    \endcode
    */
    bool operator == (const ascii* Other) const
    {
      if(LengthOf(Other) != n())
        return false;
      if(n() == 0)
        return true;

      const ascii* This = Merge();
      for(count i = n() - 1; i >= 0; i--)
        if(This[i] != Other[i])
          return false;
      return true;
    }

    /**Returns the opposite of the equivalence operator test.
    \code
    *  String a = "Hello";
    *  a -= "World!";
    *  if(!(a != "Hello World!"))
    *    c += "The strings match.";
    *  else
    *    c += "Uh oh, the strings do not match!";
    *  a = "";
    *  if(!(a != ""))
    *    c += "Empty strings match, too.";
    *  else
    *    c += "Uh oh, empty strings did not match!";
    *  a = "Hmm";
    *  if(!(a != "Hmmmmm"))
    *    c += "Uh oh, different length strings matched!";
    *  else
    *    c += "Different length strings did not match";
    *  a = "Hello";
    *  if(!(a != "Hexxo"))
    *    c += "Uh oh, same length different strings matched!";
    *  else
    *    c += "Same length different strings did not match";
    \endcode
    */
    bool operator != (const ascii* Other) const
    {
      return !(*this == Other);
    }

    //----------------//
    //Stream Appending//
    //----------------//

    ///Appends an uint8 using the familiar standard stream << operator.
    String& operator << (uint8 v);

    //Skipping int8 since it will be handled as ascii.

    ///Appends an uint16 using the familiar standard stream << operator.
    String& operator << (uint16 v);

    ///Appends an int16 using the familiar standard stream << operator.
    String& operator << (int16 v);

    ///Appends an uint32 using the familiar standard stream << operator.
    String& operator << (uint32 v);

    ///Appends an int32 using the familiar standard stream << operator.
    String& operator << (int32 v);

    ///Appends an uint64 using the familiar standard stream << operator.
    String& operator << (uint64 v);

    ///Appends an int64 using the familiar standard stream << operator.
    String& operator << (int64 v);

    ///Appends a float32 using the familiar standard stream << operator.
    String& operator << (float32 v);

    ///Appends a float64 using the familiar standard stream << operator.
    String& operator << (float64 v);

    ///Appends a void pointer using the familiar standard stream << operator.
    String& operator << (void* v);

    ///Appends a letter using the familiar standard stream << operator.
    String& operator << (ascii c)
    {
      Append((byte*)&c, 1);
      return *this;
    }

    ///Appends a string using the familiar standard stream << operator.
    String& operator << (const ascii* s)
    {
      Append(s);
      return *this;
    }

    ///Appends a string using the familiar standard stream << operator.
    String& operator << (const String& s)
    {
      Append(s.Merge());
      return *this;
    }

    ///Appends a newline if string is not empty and then applies << operator.
    template <class T>
    String& operator >> (T v)
    {
      if(InternalLength != 0)
        Append(Newline);
      *this << v;
      return *this;
    }

    ///Appends a newline if string is not empty and then appends the value.
    template <class T>
    String& operator += (T v)
    {
      *this >> v;
      return *this;
    }

    ///Appends a space and then appends the value.
    template <class T>
    String& operator -= (T v)
    {
      *this << " " << v;
      return *this;
    }

    ///Appends the value.
    template <class T>
    String& operator &= (T v)
    {
      *this << v;
      return *this;
    }

    //------//
    //Length//
    //------//

    ///Returns the number of characters in a null-terminated string.
    static count LengthOf(const ascii* s);

    /**Returns the number of bytes in the string. You can also use this to test
    whether or not the string is non-empty, since count casts to true (n != 0)
    and false (n == 0).*/
    inline count n(void) const {return InternalLength;}

    //----------------------//
    //Constructor-Destructor//
    //----------------------//

    ///Constructor creates an empty string.
    inline String() {Clear();}

    ///Virtual destructor
    virtual ~String() {}

    ///Copy constructor to initialize string with contents of other string.
    String(const ascii* Other)
    {
      Clear();
      Append(Other);
    }

    ///Copy constructor to initialize string with contents of other string.
    String(const byte* Other, count Length)
    {
      Clear();
      Append(Other, Length);
    }

    ///Copy assignment to assign string to contents of other string.
    String& operator = (const ascii* Other)
    {
      Clear();
      Append(Other);
      return *this;
    }

    //---------//
    //Operators//
    //---------//

    ///Automatic conversion to const ascii* where possible.
    inline operator const ascii* (void) const {return Merge();}

    /**Returns whether or not the string is not empty. The following shows how
    this can be used in an if-statement:
    \code
    *  String s;
    *  //... something which may or may not modify s ...
    *  if(s)
    *    c >> "s contains something";
    *  else
    *    c >> "s is empty";
    \endcode
    */
    inline operator bool(void) const {return n();}

    //---------------------//
    //Conversion to Numbers//
    //---------------------//
    number ToNumber(void) const;

    //-----//
    //UTF-8//
    //-----//

    /*Encodes and decodes UTF-8 in a String. Remember that a String is a byte
    array with no inherent encoding. String simply provides a means to safely
    encode and decode a string as UTF-8. It will filter out bad character
    sequences as a part of encoding and decoding, but it does nothing to ensure
    that the string data is valid UTF-8 since String does not have an explicit
    encoding.*/
    private:

    static const unicode CodepointBias[256];

    static const count OctetClassification[256];

    /*Given an octet class, the encoded value must be at least this number.
    Otherwise, the value is overlong (has been encoded with higher octet class
    than strictly necessary.*/
    static const count OverlongThresholds[7];

    public:

    /**Decodes the next character of a UTF-8 string according to the ISO
    10646-1:2000 standard for safely decoding an arbitrary byte stream as UTF-8.
    StreamEnd is the location of the first out-of-bounds byte. It is the
    responsibility of the caller to make sure that Stream < StreamEnd. The
    method does handle a sudden stream termination in the middle of a multi-byte
    UTF-8 sequence.
    \code
    *  String Test1;
    *  String::UTF32 Test2;
    *  c >> "Opening...";
    *  File::Read("UTF-8-test.txt", Test1);
    *  if(!Test1.n())
    *  {
    *    c >> "To run this UTF-8 test download examples/UTF-8-test.txt from:";
    *    c >> "http://www.cl.cam.ac.uk/~mgk25/ucs/";
    *    c >> "and place in the same directory as the executable.";
    *  }
    *  else
    *  {
    *    Test1.DecodeTo(Test2);
    *    Test1.Clear();
    *    Test1.Append(Test2);
    *    File::Write("UTF-8-results.txt", Test1);
    *    c >> "Wrote UTF-8-results.txt";
    *  }
    \endcode
    */
    static unicode Decode(const byte*& Stream, const byte* StreamEnd)
    {
      byte Octet1, Octet2, Octet3, Octet4, Octet5, Octet6;
      unicode Value = meta::BadCharacter;

      //Classify by initial octet.
      Octet1 = *Stream++; //Assumes caller knows Stream < StreamEnd.
      count OctetClass = OctetClassification[Octet1];

      if(OctetClass == 1) //ASCII character
        return Octet1; //No need to validate -- ASCII is always valid.
      else if(OctetClass == 2 && Stream != StreamEnd) //2-octet sequence
      {
        Octet2 = *Stream;
        if(OctetClassification[Octet2] == 0 && ++Stream)
          Value = CodepointBias[Octet1] + CodepointBias[Octet2];
      }
      else if(OctetClass == 3 && Stream != StreamEnd) //3-octet sequence
      {
        Octet2 = *Stream;
        if(OctetClassification[Octet2] == 0 && ++Stream != StreamEnd)
        {
          Octet3 = *Stream;
          if(OctetClassification[Octet3] == 0 && ++Stream)
          {
            Value = CodepointBias[Octet1] + (CodepointBias[Octet2] << 6) +
              CodepointBias[Octet3];
          }
        }
      }
      else if(OctetClass == 4 && Stream != StreamEnd) //4-octet sequence
      {
        Octet2 = *Stream;
        if(OctetClassification[Octet2] == 0 && ++Stream != StreamEnd)
        {
          Octet3 = *Stream;
          if(OctetClassification[Octet3] == 0 && ++Stream != StreamEnd)
          {
            Octet4 = *Stream;
            if(OctetClassification[Octet4] == 0 && ++Stream)
            {
              Value = CodepointBias[Octet1] + (CodepointBias[Octet2] << 12) +
                (CodepointBias[Octet3] << 6) + CodepointBias[Octet4];
            }
          }
        }
      }
      else if(OctetClass == 5 && Stream != StreamEnd) //5-octet sequence (bad)
      {
        Octet2 = *Stream;
        if(OctetClassification[Octet2] == 0 && ++Stream != StreamEnd)
        {
          Octet3 = *Stream;
          if(OctetClassification[Octet3] == 0 && ++Stream != StreamEnd)
          {
            Octet4 = *Stream;
            if(OctetClassification[Octet4] == 0 && ++Stream != StreamEnd)
            {
              Octet5 = *Stream;
              if(OctetClassification[Octet5] == 0 && ++Stream)
              {
                Value = CodepointBias[Octet1] + (CodepointBias[Octet2] << 18) +
                  (CodepointBias[Octet3] << 12) + (CodepointBias[Octet4] << 6) +
                  CodepointBias[Octet5];
              }
            }
          }
        }
      }
      else if(OctetClass == 6 && Stream != StreamEnd) //6-octet sequence (bad)
      {
        Octet2 = *Stream;
        if(OctetClassification[Octet2] == 0 && ++Stream != StreamEnd)
        {
          Octet3 = *Stream;
          if(OctetClassification[Octet3] == 0 && ++Stream != StreamEnd)
          {
            Octet4 = *Stream;
            if(OctetClassification[Octet4] == 0 && ++Stream != StreamEnd)
            {
              Octet5 = *Stream;
              if(OctetClassification[Octet5] == 0 && ++Stream != StreamEnd)
              {
                Octet6 = *Stream;
                if(OctetClassification[Octet6] == 0 && ++Stream)
                {
                  Value = CodepointBias[Octet1] +
                    (CodepointBias[Octet2] << 24) +
                    (CodepointBias[Octet3] << 18) +
                    (CodepointBias[Octet4] << 12) +
                    (CodepointBias[Octet5] << 6) +
                    CodepointBias[Octet6];
                }
              }
            }
          }
        }
      }

      //Check for overlongs forms.
      if(OctetClass >= 1 && OctetClass <= 6 &&
        Value < (unicode)OverlongThresholds[OctetClass])
          Value = meta::BadCharacter;

      //Check if value is above maximum usable Unicode point.
      if(Value > 0x10FFFF)
        Value = meta::BadCharacter;

      /*Strip any UTF-16 surrogates and illegal code positions which are invalid
      in UTF-8.*/
      if(Value == 0xD800 || Value == 0xDB7F || Value == 0xDB80 ||
        Value == 0xDBFF || Value == 0xDC00 || Value == 0xDF80 ||
        Value == 0xDFFF || Value == 0xFFFE || Value == 0xFFFF)
          Value = meta::BadCharacter;

      return Value;
    }

    ///Calculates the number of UTF-8 characters in the string.
    count Characters(void)
    {
      const byte* Start = (const byte*)Merge();
      const byte* ReadPosition = Start;
      const byte* EndMarker = &Start[n()];
      count CharacterCount = 0;
      while(ReadPosition != EndMarker)
      {
        Decode(ReadPosition, EndMarker);
        CharacterCount++;
      }
      return CharacterCount;
    }

    ///Shorthand for Characters().
    count c(void) {return Characters();}

    /**Translates a character index to a byte index in UTF-8. If the character
    is negative or if the character is beyond the null-terminator, then -1 is
    returned. The null-terminator is considered a valid character from the
    perspective of indexing.*/
    count CharacterIndex(count c)
    {
      if(!c) return 0;
      if(c < 0) return -1;
      const byte* Start = (const byte*)Merge();
      const byte* ReadPosition = Start;
      const byte* EndMarker = &Start[n()];
      count CharacterCount = 0;
      while(ReadPosition != EndMarker)
      {
        Decode(ReadPosition, EndMarker);
        if(++CharacterCount == c)
          return (count)(ReadPosition - Start);
      }
      return -1;
    }

    ///Shorthand for CharacterIndex().
    count ci(count Character) {return CharacterIndex(Character);}

    ///Returns the unicode value of the c-th character.
    unicode cth(count c)
    {
      count i = CharacterIndex(c);
      if(i < 0)
        return 0;
      const byte* Start = (const byte*)Merge();
      const byte* ReadPosition = &Start[i];
      const byte* EndMarker = &Start[n()];
      return Decode(ReadPosition, EndMarker);
    }

    ///Decodes an entire byte array to a String::UTF32.
    static void DecodeStream(const byte* Start, count Length,
      String::UTF32& Output)
    {
      const byte* ReadPosition = Start;
      const byte* EndMarker = &Start[Length];

      Output.n(0);
      while(ReadPosition != EndMarker)
        Output.Add(Decode(ReadPosition, EndMarker));
    }

    ///Decodes the current string to a String::UTF32.
    void DecodeTo(String::UTF32& Output) const
    {
      DecodeStream((byte*)Merge(), n(), Output);
    }

    /**Appends a Unicode codepoint to the string as UTF-8. If the character is
    not representable a valid Unicode codepoint, then it is substituted with the
    bad character symbol defined at meta::BadCharacter.*/
    inline void Append(unicode Codepoint)
    {
      //Alias...
      unicode d = Codepoint;

      //Do not encode an illegal character.
      if(d > 0x10FFFF || d == 0xD800 || d == 0xDB7F || d == 0xDB80 ||
        d == 0xDBFF || d == 0xDC00 || d == 0xDF80 ||
        d == 0xDFFF || d == 0xFFFE || d == 0xFFFF)
          d = meta::BadCharacter;

      //Encode the codepoint in between 1 and 4 octets.
      byte e[4] = {0, 0, 0, 0};
      if(d < 0x80) //1 octet
      {
        e[0] = (byte)d;
        Append(&e[0], 1);
      }
      else if(d < 0x800) //2 octets
      {
        e[0] = (byte)(((d >> 6) & 0x1F) + 0xC0); //110xxxxx
        e[1] = (byte)((d & 0x3F) + 0x80); //10xxxxxx
        Append(&e[0], 2);
      }
      else if(d < 0x10000) //3 octets
      {
        e[0] = (byte)(((d >> 12) & 0x0F) + 0xE0); //1110xxxx
        e[1] = (byte)(((d >> 6) & 0x3F) + 0x80); //10xxxxxx
        e[2] = (byte)((d & 0x3F) + 0x80); //10xxxxxx
        Append(&e[0], 3);
      }
      else //4 octets
      {
        e[0] = (byte)(((d >> 18) & 0x07) + 0xF0); //11110xxx
        e[1] = (byte)(((d >> 12) & 0x3F) + 0x80); //10xxxxxx
        e[2] = (byte)(((d >> 6) & 0x3F) + 0x80); //10xxxxxx
        e[3] = (byte)((d & 0x3F) + 0x80); //10xxxxxx
        Append(&e[0], 4);
      }
    }

    /**Appends an array of codepoints to the string as UTF-8.
    \code
    *  String::UTF32 s, s3;
    *  String s2;
    *  s.n(0x110000);
    *  c >> "Creating all codepoints...";
    *  for(count i = 0; i < s.n(); i++)
    *    s[i] = i;
    *  s2.Append(s);
    *  s2.DecodeTo(s3);
    *  c >> "Checking all codepoints...";
    *  for(count i = 0; i < s3.n(); i++)
    *    if(s3[i] != i && s3[i] != meta::BadCharacter)
    *      c >> "ERROR: Problem at " << i;
    \endcode
    */
    void Append(const String::UTF32& Codepoints)
    {
      for(count i = 0; i < Codepoints.n(); i++)
        Append(Codepoints[i]);
    }
  };

  /**Standard output that acts like a string. Every operation involving append
  will duplicate the text to the console before performing the append. Since
  Console inherits String you can retrieve all the text that has been written
  to the console via the object.*/
  class Console : public String
  {
    protected:
    ///Append operation through which all console output passes through.
    void Append(const byte* Fragment, count Length);

    public:
    ///Prints a message and waits for the user to type a key and press return.
    void Wait(String Message = "");

    /**Makes a system call using supplied string and returns when finished. Note
    that the behavior of this method is system-dependent. Internally calls
    system() from cstdlib.*/
    static void System(String CommandToExecute);
  };

#ifndef PRIM_WITH_THREAD
  /**Global console object. When the thread module is enabled, the object
  becomes a Threadable::Console and is therefore thread-safe.
  \code
  *  c += "Hello world!";
  \endcode
  */
  extern Console c;
#endif

#ifdef PRIM_COMPILE_INLINE
#ifndef PRIM_WITH_THREAD
  //The global console object.
  Console c;
#endif

  const ascii* String::LF = "\x0A"; //Practically equivalent to '\n'
  const ascii* String::CRLF = "\x0D\x0A"; //Practically equivalent to '\r\n'
  const ascii* String::Newline = String::LF;

  String& String::operator << (uint8 v)
  {
    std::stringstream ss;
    ss << (int32)v;
    char BufferData[32]; ss.read(&BufferData[0], 32);
    Append((byte*)&BufferData[0], (count)ss.gcount());
    return *this;
  }

  String& String::operator << (uint16 v)
  {
    std::stringstream ss;
    ss << v;
    char BufferData[32]; ss.read(&BufferData[0], 32);
    Append((byte*)&BufferData[0], (count)ss.gcount());
    return *this;
  }

  String& String::operator << (int16 v)
  {
    std::stringstream ss;
    ss << v;
    char BufferData[32]; ss.read(&BufferData[0], 32);
    Append((byte*)&BufferData[0], (count)ss.gcount());
    return *this;
  }

  String& String::operator << (unicode v)
  {
    Append(v);
    return *this;
  }

  String& String::operator << (int32 v)
  {
    std::stringstream ss;
    ss << v;
    char BufferData[32]; ss.read(&BufferData[0], 32);
    Append((byte*)&BufferData[0], (count)ss.gcount());
    return *this;
  }

  String& String::operator << (uint64 v)
  {
    std::stringstream ss;
    ss << v;
    char BufferData[32]; ss.read(&BufferData[0], 32);
    Append((byte*)&BufferData[0], (count)ss.gcount());
    return *this;
  }

  String& String::operator << (int64 v)
  {
    std::stringstream ss;
    ss << v;
    char BufferData[32]; ss.read(&BufferData[0], 32);
    Append((byte*)&BufferData[0], (count)ss.gcount());
    return *this;
  }

  String& String::operator << (float32 v)
  {
    v = Chop(v, 1.0e-16f);
    if(Abs(v) >= 1.0e+16f) v = 1.0e+16f * Sign(v);
    std::stringstream ss;
    ss.precision(18);
    ss.setf(std::ios::fixed, std::ios::floatfield);
    ss << v;
    char BufferData[32]; ss.read(&BufferData[0], 32);
    Append((byte*)&BufferData[0], (count)ss.gcount());
    return *this;
  }

  String& String::operator << (float64 v)
  {
    v = Chop(v, 1.0e-16);
    if(Abs(v) >= 1.0e+16) v = 1.0e+16 * Sign(v);
    std::stringstream ss;
    ss.precision(18);
    ss.setf(std::ios::fixed, std::ios::floatfield);
    ss << v;
    char BufferData[32]; ss.read(&BufferData[0], 32);
    Append((byte*)&BufferData[0], (count)ss.gcount());
    return *this;
  }

  String& String::operator << (void* v)
  {
    std::stringstream ss;
    ss << v;
    char BufferData[32]; ss.read(&BufferData[0], 32);
    Append((byte*)&BufferData[0], (count)ss.gcount());
    return *this;
  }

  count String::LengthOf(const ascii* s)
  {
    return (count)(strchr(s, 0) - s);
  }

  number String::ToNumber(void) const
  {
    return (number)atof(Merge());
  }

  void Console::Append(const byte* Fragment, count Length)
  {
    String::Append(Fragment, Length);
    std::cout << &Merge()[n() - Length];
    std::cout.flush();
  }

  void Console::Wait(String Message)
  {
    *this >> Message;
    byte In;
    std::cin >> In;
  }

  void Console::System(String CommandToExecute)
  {
    system(CommandToExecute.Merge());
  }

  const unicode String::CodepointBias[256] =
  {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
  22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
  41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
  60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78,
  79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97,
  98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113,
  114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 0x0,
  0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF,
  0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C,
  0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29,
  0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36,
  0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x0, 0x40, 0x80, 0xC0,
  0x100, 0x140, 0x180, 0x1C0, 0x200, 0x240, 0x280, 0x2C0, 0x300, 0x340, 0x380,
  0x3C0, 0x400, 0x440, 0x480, 0x4C0, 0x500, 0x540, 0x580, 0x5C0, 0x600, 0x640,
  0x680, 0x6C0, 0x700, 0x740, 0x780, 0x7C0, 0x0, 0x1000, 0x2000, 0x3000, 0x4000,
  0x5000, 0x6000, 0x7000, 0x8000, 0x9000, 0xA000, 0xB000, 0xC000, 0xD000,
  0xE000, 0xF000, 0x0, 0x40000, 0x80000, 0xC0000, 0x100000, 0x140000, 0x180000,
  0x1C0000, 0x0, 0x1000000, 0x2000000, 0x3000000, 0x0, 0x4000000, 0, 0};

  const count String::OctetClassification[256] =
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3,
  3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, -1, -1};

  const count String::OverlongThresholds[7] = {0, 0, 0x80, 0x800, 0x10000,
    0x200000, 0x4000000};
#endif
}
#endif

//............................................................................//

#ifndef PRIM_FILE_H
#define PRIM_FILE_H

namespace prim
{
  ///Static methods for reading and writing to files.
  class File
  {
    ///Internal method for reading from file. Fails if file could not be opened.
    static bool Read(const ascii* Filename, byte* ByteData, count Bytes);

    ///Internal method for writing to file. Fails if all bytes are not written.
    static bool Write(const ascii* Filename, const byte* ByteData, count Bytes);

    /**Internal method for appending to file. Fails if all bytes are not
    appended.*/
    static bool Append(const ascii* Filename, const byte* ByteData,
      count Bytes);

  public:
    /**Returns the length of the file in bytes. If the file does not exist, this
    will return 0.
    \code
    *  //Write string to file.
    *  File::Write("example.txt", "Hello World!");
    *
    *  //Get length of file.
    *  c += "Length of Existing File: ";
    *  c << File::Length("example.txt"); // <-- Method used here
    *
    *  //See what happens when non-file is used.
    *  c += "Length of Non-File: ";
    *  c << File::Length("notafile.txt"); // <-- Method used here
    \endcode
    */
    static count Length(const ascii* Filename);

    /**Reads a file into an array and returns whether it was successful. If the
    file length is not a multiple of the object length, then the trailing bytes
    are ignored.
    \code
    *  using namespace planar;
    *
    *  //Create two arrays of vectors, one to be written, one to be read.
    *  Array<Vector> a, b;
    *
    *  //Fill the write array with 10 ascending x's and descending y's.
    *  a.n(10);
    *  for(count i = 0; i < a.n(); i++)
    *    a[i] = Vector((number)i, (number)(a.n() - i));
    *
    *  //Write the array to file.
    *  File::Write("example.dat", a);
    *
    *  //See what happens when a non-file is read.
    *  if(File::Read("notafile.dat", b)) // <-- Method used here
    *    c += "notafile.dat was read (should not happen)";
    *  else
    *    c += "notafile.dat was not read since it does not exist.";
    *
    *  //Try to read the file into the read array.
    *  if(File::Read("example.dat", b)) // <-- Method used here
    *  {
    *    //If successful print out the values of the vectors.
    *    c += "Output:";
    *    for(count i = 0; i < b.n(); i++)
    *      c >> i << ": " << b[i].x << ", " << b[i].y;
    *  }
    *  else
    *    c += "Failed to read example.dat";
    \endcode
    */
    template <class T>
    static bool Read(const ascii* Filename, Array<T>& SomeArray)
    {
      count LengthOfFile = Length(Filename);
      SomeArray.n(LengthOfFile / sizeof(T));
      bool Result = Read(Filename, (byte*)&SomeArray[0], LengthOfFile);
      if(!Result)
        SomeArray.n(0);
      return Result;
    }

    ///Reads the file as a string and returns whether it was successful.
    static bool Read(const ascii* Filename, String& Destination)
    {
      Array<byte> ByteArray;
      Destination.Clear();

      if(!Read(Filename, ByteArray))
        return false;

      Destination.Append(&ByteArray[0], ByteArray.n());
      return true;
    }

    /**Writes a new file from an array and returns whether it was successful.
    \code
    *  using namespace planar;
    *
    *  //Create two arrays of vectors, one to be written, one to be read.
    *  Array<Vector> a, b;
    *
    *  //Fill the write array with 10 ascending x's and descending y's.
    *  a.n(10);
    *  for(count i = 0; i < a.n(); i++)
    *    a[i] = Vector((number)i, (number)(a.n() - i));
    *
    *  //Write the array to file.
    *  File::Write("example.dat", a); // <-- Method used here
    *
    *  //See what happens when a non-file is written.
    *  if(File::Write("", a)) // <-- Method used here
    *    c += "Non-file was written (should not happen)";
    *  else
    *    c += "Non-file was not written since the filename is bad.";
    *
    *  //Try to read the file into the read array.
    *  if(File::Read("example.dat", b))
    *  {
    *    //If successful print out the values of the vectors.
    *    c += "Output:";
    *    for(count i = 0; i < b.n(); i++)
    *      c >> i << ": " << b[i].x << ", " << b[i].y;
    *  }
    *  else
    *    c += "Failed to read example.dat";
    \endcode
    */
    template <class T>
    static bool Write(const ascii* Filename, const Array<T>& SomeArray)
    {
      return Write(Filename, (byte*)&SomeArray[0], SomeArray.n() * sizeof(T));
    }

    ///Writes a new file from a string and returns whether it was successful.
    static bool Write(const ascii* Filename, const String& SomeString)
    {
      return Write(Filename, (const byte*)SomeString.Merge(), SomeString.n());
    }

    /**Appends array data to a file and returns whether it was successful. The
    file is created if it does not exist.
    \code
    *  using namespace planar;
    *
    *  //Create two arrays of vectors, one to be written, one to be read.
    *  Array<Vector> a, b;
    *
    *  //Fill the write array with 10 ascending x's and descending y's.
    *  a.n(10);
    *  for(count i = 0; i < a.n(); i++)
    *    a[i] = Vector((number)i, (number)(a.n() - i));
    *
    *  //Write the array to file, then append the same data.
    *  File::Write("example.dat", a);
    *  File::Append("example.dat", a); // <-- Method used here
    *
    *  //See what happens when a non-file is appended.
    *  if(File::Append("", a)) // <-- Method used here
    *    c += "Non-file was appended (should not happen)";
    *  else
    *    c += "Non-file was not appended since the filename is bad.";
    *
    *  //Try to read the file into the read array.
    *  if(File::Read("example.dat", b))
    *  {
    *    //If successful print out the values of the vectors.
    *    c += "Output:";
    *    for(count i = 0; i < b.n(); i++)
    *      c >> i << ": " << b[i].x << ", " << b[i].y;
    *  }
    *  else
    *    c += "Failed to read example.dat";
    \endcode
    */
    template <class T>
    static bool Append(const ascii* Filename, const Array<T>& SomeArray)
    {
      return Append(Filename, (byte*)&SomeArray[0], SomeArray.n() * sizeof(T));
    }

    /**Appends a string to an existing file. The file is created if it does not
    exist.*/
    static bool Append(const ascii* Filename, const String& SomeString)
    {
      return Append(Filename, (const byte*)SomeString.Merge(), SomeString.n());
    }
  };

#ifdef PRIM_COMPILE_INLINE
  bool File::Read(const ascii* Filename, byte* ByteData, count Bytes)
  {
    //Create an input file stream.
    std::ifstream FileStream;

    //Open the file, but do not truncate it.
    FileStream.open(Filename, std::ios::in | std::ios::binary);

    //Get out of here if for some reason the file could not be opened.
    if(!FileStream.is_open())
    {
      Bytes = 0;
      return false;
    }

    //Seek to the beginning of the file and read into the byte array.
    FileStream.seekg(0, std::ios_base::beg);
    FileStream.read((ascii*)ByteData, Bytes);

    //Return the length of the file.
    return true;
  }

  bool File::Write(const ascii* Filename, const byte* ByteData, count Bytes)
  {
    //Create an input file stream.
    std::ofstream FileStream;

    //Open the file and truncate it.
    FileStream.open(Filename, std::ios::out | std::ios::trunc |
      std::ios::binary);

    //Get out of here if for some reason the file could not be opened.
    if(!FileStream.is_open())
      return false;

    //Write the byte array to the file.
    FileStream.write((ascii*)ByteData, Bytes);

    //Close the file.
    FileStream.close();

    //Return success.
    return true;
  }

  bool File::Append(const ascii* Filename, const byte* ByteData, count Bytes)
  {
    //Create an input file stream.
    std::ofstream FileStream;

    //Open the file and append to it.
    FileStream.open(Filename, std::ios::out | std::ios::app |
      std::ios::binary);

    //Get out of here if for some reason the file could not be opened.
    if(!FileStream.is_open())
      return false;

    //Write the byte array to the file.
    FileStream.write((ascii*)ByteData, Bytes);

    //Close the file.
    FileStream.close();

    //Return success.
    return true;
  }

  count File::Length(const ascii* Filename)
  {
    //C++ implementation (tellg() generates aggregate function warning)

    //Create an input file stream.
    std::ifstream FileStream;

    //Open the file, but do not truncate it.
    FileStream.open(Filename, std::ios::in | std::ios::binary);

    //Get out of here if for some reason the file could not be opened.
    if(!FileStream.is_open())
      return 0;

    //Seek to the end of the file to get the length.
    FileStream.seekg(0, std::ios_base::end);
    return (count)FileStream.tellg(); //tellg() returns aggregate data
  }
#endif
}
#endif

#ifndef PRIM_RATIONAL_H
#define PRIM_RATIONAL_H

namespace prim
{
  ///Templated class for expressing rational numbers.
  template <class IntegralType>
  class Rational
  {
  protected:
    /**The numerator of the Rational number. It is always expressed in its
    simplest form.*/
    IntegralType n;

    /**The denominator of the Rational number. It is always expressed in its
    simplest form.*/
    IntegralType d;

    void SimplifySign(void)
    {
      if(d < 0)
      {
        n = -n;
        d = -d;
      }
    }

    void SimplifyRatio(void)
    {
      if(d == 0) //Indeterminate form
      {
        n = 0;
        return;
      }

      if(n == 0) //Zero: assume denominator of one for consistency.
      {
        d = 1;
        return;
      }

      IntegralType g = GCD(n, d);
      while(g != 1)
      {
        n = n / g;
        d = d / g;
        g = GCD(n, d);
      }
    }

    void Simplify(void)
    {
      SimplifySign();
      SimplifyRatio();
    }

  public:

    ///Creates an empty ratio (not zero).
    Rational() : n(0), d(0) {}

    ///Creates a ratio from a numerator and denominator.
    Rational(IntegralType Numerator, IntegralType Denominator)
    {
      n = Numerator;
      d = Denominator;
      Simplify();
    }

    ///Creates a ratio from a whole number.
    Rational(IntegralType WholeNumber)
    {
      n = WholeNumber;
      d = 1;
    }

    ///Creates a ratio from a string.
    Rational(const String& s)
    {
      *this = FromString(s);
    }

    ///Returns the numerator.
    IntegralType Numerator(void)
    {
      return n;
    }

    ///Returns the denominator.
    IntegralType Denominator(void)
    {
      return d;
    }

    ///Checks whether the number has a non-zero denominator.
    bool IsDeterminate(void)
    {
      return d != 0;
    }

    ///Checks whether the number is whole.
    bool IsWhole(void)
    {
      return d == 1;
    }

    ///Checks whether the number is empty.
    bool IsEmpty(void)
    {
      return d == 0;
    }

    ///Calculates the greatest common denominator.
    static IntegralType GCD(IntegralType a, IntegralType b)
    {
      //Test for zeroes.
      if(a == 0 || b == 0)
        return 0;

      //Naturalize the numbers.
      if(a < 0) a = -a;
      if(b < 0) b = -b;

      //Use the iterative Euclidean algorithm.
      //For more information, see:
      //http://en.wikipedia.org/wiki/Euclidean_algorithm#Implementations
      IntegralType t;
      while(b!=0)
      {
        t = b;
        b = a % b;
        a = t;
      }
      return a;
    }

    ///Calculates the least common multiple.
    static IntegralType LCM(IntegralType a, IntegralType b)
    {
      //Test for zeroes.
      if(a == 0 || b == 0)
        return 0;

      //"Naturalize" the numbers.
      if(a < 0) a = -a;
      if(b < 0) b = -b;

      //Use the GCD to calculate the LCM
      return (a * b) / GCD(a,b);
    }

    ///Calculates the remainder of division.
    static Rational<IntegralType> Mod(Rational<IntegralType> a,
      Rational<IntegralType> b)
    {
      IntegralType d2 = LCM(a.d, b.d);
      IntegralType a2 = d2 / a.d;
      IntegralType b2 = d2 / b.d;
      a.n *= a2;
      b.n *= b2;

      //Now a and b have the same denominator.
      IntegralType n2 = a.n % b.n;

      return Rational<IntegralType>(n2, d2);
    }

    //--------------------//
    //Operator definitions//
    //--------------------//

    Rational<IntegralType> operator + (Rational<IntegralType> Other)
    {
      IntegralType LCD = LCM(d, Other.d);
      IntegralType d2 = LCD;
      IntegralType n2 = n * (LCD / d) + Other.n * (LCD / Other.d);
      return Rational<IntegralType>(n2, d2);
    }

    Rational<IntegralType> operator + (IntegralType Other)
    {
      return *this + Rational<IntegralType>(Other, 1);
    }

    Rational<IntegralType> operator + (const String& Other)
    {
      return *this + Rational<IntegralType>(Other);
    }

    Rational<IntegralType> operator - (Rational<IntegralType> Other)
    {
      IntegralType LCD = LCM(d, Other.d);
      IntegralType d2 = LCD;
      IntegralType n2 = n * (LCD / d) - Other.n * (LCD / Other.d);
      return Rational<IntegralType>(n2, d2);
    }

    Rational<IntegralType> operator - (IntegralType Other)
    {
      return *this - Rational<IntegralType>(Other, 1);
    }

    Rational<IntegralType> operator - (const String& Other)
    {
      return *this - Rational<IntegralType>(Other);
    }

    Rational<IntegralType> operator * (Rational<IntegralType> Other)
    {
      IntegralType n2 = n * Other.n;
      IntegralType d2 = d * Other.d;
      return Rational<IntegralType>(n2, d2);
    }

    Rational<IntegralType> operator * (IntegralType Other)
    {
      return *this * Rational<IntegralType>(Other, 1);
    }

    Rational<IntegralType> operator * (const String& Other)
    {
      return *this * Rational<IntegralType>(Other);
    }

    Rational<IntegralType> operator / (Rational<IntegralType> Other)
    {
      IntegralType n2 = n * Other.d;
      IntegralType d2 = d * Other.n;
      return Rational<IntegralType>(n2, d2);
    }

    Rational<IntegralType> operator / (IntegralType Other)
    {
      return *this / Rational<IntegralType>(Other, 1);
    }

    Rational<IntegralType> operator / (const String& Other)
    {
      return *this / Rational<IntegralType>(Other);
    }

    Rational<IntegralType> operator += (Rational<IntegralType> Other)
    {
      *this = *this + Other;
      return *this;
    }

    Rational<IntegralType> operator += (IntegralType Other)
    {
      *this = *this + Rational<IntegralType>(Other, 1);
      return *this;
    }

    Rational<IntegralType> operator += (const String& Other)
    {
      *this = *this + Rational<IntegralType>(Other);
      return *this;
    }

    Rational<IntegralType> operator -= (Rational<IntegralType> Other)
    {
      *this = *this + Other;
      return *this;
    }

    Rational<IntegralType> operator -= (IntegralType Other)
    {
      *this = *this - Rational<IntegralType>(Other, 1);
      return *this;
    }

    Rational<IntegralType> operator -= (const String& Other)
    {
      *this = *this - Rational<IntegralType>(Other);
      return *this;
    }

    Rational<IntegralType> operator *= (Rational<IntegralType> Other)
    {
      *this = *this * Other;
      return *this;
    }

    Rational<IntegralType> operator *= (IntegralType Other)
    {
      *this = *this * Rational<IntegralType>(Other, 1);
      return *this;
    }

    Rational<IntegralType> operator *= (const String& Other)
    {
      *this = *this * Rational<IntegralType>(Other);
      return *this;
    }

    Rational<IntegralType> operator /= (Rational<IntegralType> Other)
    {
      *this = *this / Other;
      return *this;
    }

    Rational<IntegralType> operator /= (IntegralType Other)
    {
      *this = *this / Rational<IntegralType>(Other, 1);
      return *this;
    }

    Rational<IntegralType> operator /= (const String& Other)
    {
      *this = *this / Rational<IntegralType>(Other);
      return *this;
    }

    Rational<IntegralType> operator = (Rational<IntegralType> Other)
    {
      n = Other.n;
      d = Other.d;
      return *this;
    }

    Rational<IntegralType> operator = (IntegralType Other)
    {
      n = Other;
      d = 1;
      return *this;
    }

    Rational<IntegralType> operator = (const String& Other)
    {
      *this = FromString(Other);
      return *this;
    }

    Rational<IntegralType> operator ++ (int Dummy)
    {
      n = n + d;
      return *this;
    }

    Rational<IntegralType> operator -- (int Dummy)
    {
      n = n - d;
      return *this;
    }

    Rational<IntegralType> operator - (void)
    {
      return *this * -1;
    }

    bool operator == (Rational<IntegralType> Other)
    {
      return n == Other.n && d == Other.d;
    }

    bool operator == (IntegralType Other)
    {
      return n == Other && d == 1;
    }

    bool operator == (const String& Other)
    {
      Rational<IntegralType> r(Other);
      return n == r.n && d == r.d;
    }

    bool operator != (Rational<IntegralType> Other)
    {
      return n != Other.n || d != Other.d;
    }

    bool operator != (IntegralType Other)
    {
      return n != Other || d != 1;
    }

    bool operator != (const String& Other)
    {
      Rational<IntegralType> r(Other);
      return n != r.n || d != r.d;
    }

    bool operator > (Rational<IntegralType> Other)
    {
      Rational<IntegralType> Difference = *this - Other;
      return Difference.n > 0;
    }

    bool operator > (IntegralType Other)
    {
      Rational<IntegralType> Difference = *this -
        Rational<IntegralType>(Other, 1);
      return Difference.n > 0;
    }

    bool operator > (const String& Other)
    {
      Rational<IntegralType> r(Other);
      Rational<IntegralType> Difference = *this - r;
      return Difference.n > 0;
    }

    bool operator >= (Rational<IntegralType> Other)
    {
      Rational<IntegralType> Difference = *this - Other;
      return Difference.n >= 0;
    }

    bool operator >= (IntegralType Other)
    {
      Rational<IntegralType> Difference = *this -
        Rational<IntegralType>(Other, 1);
      return Difference.n >= 0;
    }

    bool operator >= (const String& Other)
    {
      Rational<IntegralType> r(Other);
      Rational<IntegralType> Difference = *this - r;
      return Difference.n >= 0;
    }

    bool operator < (Rational<IntegralType> Other)
    {
      Rational<IntegralType> Difference = *this - Other;
      return Difference.n < 0;
    }

    bool operator < (IntegralType Other)
    {
      Rational<IntegralType> Difference = *this -
        Rational<IntegralType>(Other, 1);
      return Difference.n < 0;
    }

    bool operator < (const String& Other)
    {
      Rational<IntegralType> r(Other);
      Rational<IntegralType> Difference = *this - r;
      return Difference.n < 0;
    }

    bool operator <= (Rational<IntegralType> Other)
    {
      Rational<IntegralType> Difference = *this - Other;
      return Difference.n <= 0;
    }

    bool operator <= (IntegralType Other)
    {
      Rational<IntegralType> Difference = *this -
        Rational<IntegralType>(Other, 1);
      return Difference.n <= 0;
    }

    bool operator <= (const String& Other)
    {
      Rational<IntegralType> r(Other);
      Rational<IntegralType> Difference = *this - r;
      return Difference.n <= 0;
    }

    //-------//
    //Helpers//
    //-------//

    ///Converts a string to x/y format.
    String ToString(void)
    {
      String s;
      s << n << "/" << d;
      return s;
    }

    ///Converts a string into the most common format for that number.
    String ToPrettyString(void)
    {
      if(d == 0) return "NaN";
      String s;
      s << n;
      if(n != 0 && d != 1)
        s << "/" << d;
      return s;
    }

    ///Reads a rational from a string.
    static Rational<IntegralType> FromString(const String& s)
    {
      count Length = s.n();
      IntegralType n = 0, d = 0;
      bool IsPastSlash = false;
      bool IsInvalid = false;

      for(count i = 0; i < Length; i++)
      {
        ascii c = s[i];
        if(c == '/')
        {
          //Invalid use of slash.
          if(i == 0 || i == Length - 1 || IsPastSlash)
          {
            IsInvalid = true;
            break;
          }
          IsPastSlash = true;
        }
        else if(!IsPastSlash)
        {
          if(c >= 48 && c <= 57)
            n = n * 10 + (c - 48);
          else
          {
            //Invalid non-digit numerator.
            IsInvalid = true;
            break;
          }
        }
        else
        {
          if(c >= 48 && c <= 57)
            d = d * 10 + (c - 48);
          else
          {
            //Invalid non-digit denominator
            IsInvalid = true;
            break;
          }
        }
      }

      if(IsInvalid)
      {
        n = 0;
        d = 0;
      }
      else
      {
        if(!IsPastSlash)
          d = 1;
      }

      return Rational<IntegralType>(n, d);
    }

    ///Automatically casts the rational to a string when needed.
    operator String(void)
    {
      return ToPrettyString();
    }

    ///Casts the rational to other types.
    template <class Numeric>
    operator Numeric (void)
    {
      return To<Numeric>();
    }

    ///Casts the rational to other types.
    template <class Numeric>
    Numeric To(void)
    {
      if(d == 0)
        return 0; //Indeterminate case
      else
        return ((Numeric)n) / ((Numeric)d);
    }
  };

  //Template instantiations
  typedef Rational<int32> Ratio64;
  typedef Rational<int16> Ratio32;
  typedef Rational<int8>  Ratio16;
  typedef Ratio64 Ratio;
}
#endif

//............................................................................//

#ifdef PRIM_WITH_MD5

#ifndef PRIM_MD5_H
#define PRIM_MD5_H

/*Module Configuration
================================================================================

Works on both little-endian and big-endian processors provided that the
PRIM_ENVIRONMENT_LITTLE_ENDIAN or PRIM_ENVIRONMENT_BIG_ENDIAN define is
correctly set.

================================================================================
End Module Configuration*/

namespace prim
{
  ///Calculates MD5 checksums.
  struct MD5
  {
    /*The following works in C and C++ on little-endian processors. You can test
    out the code by pasting it into codepad.org as either C or C++.*/
    //----------------------------MD5 EXCERPT START---------------------------//
    #ifndef PRIM_MD5_H
    #include <stdio.h>
    #include <string.h>

    typedef unsigned int uint32;
    typedef unsigned char byte;
    #if defined(WINDOWS) || defined(WIN32) || defined(_WIN32) || defined(_WIN64)
    typedef long long int64;
    #else
    #include <sys/types.h>
    typedef int64_t int64;
    #endif

    static void Calculate(const byte* Data, int64 Length, uint32 Out[4]);

    int main(void)
    {
      const char* Data = "The quick brown fox jumps over the lazy dog";
      uint32 Out[4];
      int i;
      Calculate((const byte*)Data, strlen(Data), Out);
      printf("Calculated: ");
      for(i = 0; i < 16; i++)
        printf("%.2x", ((byte*)Out)[i]);
      printf("\nActual    : 9e107d9d372bb6826bd81d3542a419d6\n");
      return 0;
    }
    #endif

    ///Calculates an MD5 checksum on a string of byte data.
    static void Calculate(const byte* Data, int64 Length, uint32 Out[4])
    {
      //This is just a refactored version of the pseudo-code found at:
      //http://en.wikipedia.org/wiki/MD5#Pseudocode

      uint32 g[192] = { //64 magic numbers each at g[0], g[64], and g[128]
        7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
        5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
        4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
        6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21,
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a,
        0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
        0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340,
        0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8,
        0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
        0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, 0x289b7ec6, 0xeaa127fa,
        0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92,
        0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
        0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391,
        0, 1,  2,  3, 4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
        1, 6, 11,  0, 5, 10, 15,  4,  9, 14,  3,  8, 13,  2,  7, 12,
        5, 8, 11, 14, 1,  4,  7, 10, 13,  0,  3,  6,  9, 12, 15,  2,
        0, 7, 14, 5, 12,  3, 10,  1,  8, 15,  6, 13,  4, 11,  2,  9};

      uint32 a = Out[0] = 0x67452301, //Hash state
             b = Out[1] = 0xefcdab89,
             c = Out[2] = 0x98badcfe,
             d = Out[3] = 0x10325476,
             x, w[16];

      int64 q = 1, j, i; //Loop variables

      byte p[128]; p[0] = 0x80; //Message padding

      int64* p64 = 0;

      while((Length + q) % 64 != 56) //Calculate padding
        p[q++] = 0;
      p64 = (int64*)&p[q];
      *p64 = Length * 8;
#ifdef PRIM_ENVIRONMENT_BIG_ENDIAN
      Endian::ReverseOrder(*p64);
#endif
      for(j = -Length; j < q + 8;)
      {
        for(i = 0; i < 64; i++, j++) //Read in 64-bytes of message
          ((byte*)w)[i] = j < 0 ? *Data++ : p[j];
#ifdef PRIM_ENVIRONMENT_BIG_ENDIAN
        for(i = 0; i < 16; i++)
          Endian::ReverseOrder(w[i]);
#endif
        for(i = 0; i < 64; i++) //Calculate chunk hash
        {
          if(i < 16)      x = (b & c) | (~b & d);
          else if(i < 32) x = (d & b) | (~d & c);
          else if(i < 48) x = (b ^ c) ^ d;
          else            x =  c ^ (b | ~d);

          x += a + g[i + 64] + w[g[i + 128]];
          a = d;
          d = c;
          c = b;
          b += (x << g[i]) | (x >> (32 - g[i]));
        }

        a = Out[0] += a; //Sum chunk hash to output hash
        b = Out[1] += b;
        c = Out[2] += c;
        d = Out[3] += d;
      }
#ifdef PRIM_ENVIRONMENT_BIG_ENDIAN
      for(i = 0; i < 4; i++)
        Endian::ReverseOrder(Out[i]);
#endif
    }
    //-----------------------------MD5 EXCERPT END----------------------------//

    ///Returns the familiar hexadecimal MD5 checksum to a string of byte data.
    static String Hex(const byte* Start, count Length, bool Uppercase = false)
    {
      Array<uint32> Digest;
      Digest.n(4);
      Calculate(Start, Length, &Digest.a());
      Array<byte> HexArray;
      Digest.EncodeAsASCIIHex(HexArray);
      if(!Uppercase)
        for(count i = 0; i < HexArray.n(); i++)
          if(HexArray[i] >= 'A' && HexArray[i] <= 'F')
            HexArray[i] += 'a' - 'A';
      return String(&HexArray.a(), HexArray.n());
    }

    ///Returns the familiar hexadecimal MD5 checksum to an array of byte data.
    static String Hex(const Array<byte>& Data, bool Uppercase = false)
    {
      return Hex(&Data.a(), Data.n(), Uppercase);
    }

    ///Returns the familiar hexadecimal MD5 checksum to a character string.
    static String Hex(const String& DataString, bool Uppercase = false)
    {
      return Hex((const byte*)DataString.Merge(), DataString.n(), Uppercase);
    }
  };
}
#endif

#endif
#ifdef PRIM_WITH_PLANAR

#ifndef PRIM_PLANAR_H
#define PRIM_PLANAR_H

namespace prim { namespace planar
{
  //-----------------------//
  //Vector Type-Definitions//
  //-----------------------//

  /**Type-definition for a planar number coordinate
  \code
  *  using namespace planar;
  *  Vector a(10.2, -11.3);
  *  c >> a.x << ", " << a.y;
  *  c += "Magnitude: "; c << a.Mag();
  \endcode
  */
  typedef Complex<number> Vector;

  /**Type-definition for a planar integer coordinate
  \code
  *  using namespace planar;
  *  VectorInt a(10, -11);
  *  c >> a.x << ", " << a.y;
  *  c += "Magnitude: "; c << a.Mag();
  \endcode
  */
  typedef Complex<integer> VectorInt;

  //----------//
  //Rectangles//
  //----------//

  /**Stores a rectangle as a pair of opposite vectors. A non-empty rectangle
  is defined to be one that has a non-zero area (and thus has four right
  angles). An ordered rectangle is a non-empty rectangle with ordered
  coordinates such that a is the bottom-left corner, and b is the top-right
  corner.*/
  template <class T>
  struct RectangleT
  {

    /**Location of the first of two opposite corners of a rectangle.*/
    Complex<T> a;

    /**Location of the second of two opposite corners of a rectangle.*/
    Complex<T> b;

    //------------//
    //Constructors//
    //------------//

    //Default constructor creates an invalid rectangle.
    RectangleT() {}

    ///Creates a collapsed rectangle at a single point.
    RectangleT(Complex<T> p) : a(p), b(p) {}

    ///Creates a rectangle from a pair of minimum and maximum vectors.
    RectangleT(Complex<T> p1, Complex<T> p2) :
      a(p1), b(p2) {}

    ///Creates a rectangle from the coordinates of its four sides.
    RectangleT(T x1, T y1, T x2, T y2) :
      a(x1, y1), b(x2, y2) {}

    //---------//
    //Emptiness//
    //---------//

    /**Returns true if the rectangle is empty. A rectangle is empty if its area
    is zero. If either the width or height is zero, the rectangle is empty. An
    empty rectangle is mathematically an invalid one since it contains undefined
    angles instead of right angles.*/
    inline bool IsEmpty(void) const
    {
      return a.x == b.x || a.y == b.y;
    }

    /**Clears a rectangle by reinitializing its coordinates to zero. The
    rectangle returns to an invalid and non-ordered state.*/
    inline void Clear(void)
    {
      a = b = Complex<T>();
    }

    //-----//
    //Order//
    //-----//

    /**Ensures that the coordinates are in ascending order. IsOrdered() will
    still return false if either the width or height is zero.*/
    void Order(void)
    {
      Ascending(a.x, b.x);
      Ascending(a.y, b.y);
    }

    /**Returns whether or not the two points a and b are in ascending order.
    The rectangle must also be non-empty (have non-zero area) to be ordered.*/
    bool IsOrdered(void) const
    {
      return a.x < b.x && a.y < b.y;
    }

    //----------//
    //Dimensions//
    //----------//

    /**Returns the positive difference of the x-coordinates. An invalid
    rectangle may have a non-zero width.*/
    inline T Width(void) const
    {
      return Abs(b.x - a.x);
    }

    /**Returns the positive difference of the y-coordinates. An invalid
    rectangle may have a non-zero height.*/
    inline T Height(void) const
    {
      return Abs(b.y - a.y);
    }

    ///Returns the positive size of the rectangle.
    inline Complex<T> Size(void) const
    {
      return Complex<T>(Width(), Height());
    }

    /**Returns the positive or negative difference of the x-coordinates. An
    invalid rectangle may have a non-zero width.*/
    inline T DeltaX(void) const
    {
      return b.x - a.x;
    }

    /**Returns the positive or negative difference of the y-coordinates. An
    invalid rectangle may have a non-zero height.*/
    inline T DeltaY(void) const
    {
      return b.y - a.y;
    }

    /**Returns the difference of the rectangle coordinates. Either dimension may
    be negative depending on how the coordinates are ordered.*/
    inline Complex<T> DeltaSize(void) const
    {
      return Complex<T>(b - a);
    }

    /**Returns the postive area of the rectangle. A rectangle has non-zero
    area if it is valid.*/
    inline T Area(void) const
    {
      return Abs(DeltaX() * DeltaY());
    }

    /**Returns the positive perimeter of the rectangle. An invalid rectangle
    may have a non-zero perimeter if one of its sides is non-zero.*/
    inline T Perimeter(void) const
    {
      return (Width() + Height()) * (T)2;
    }

    ///Returns the coordinate of the left side.
    inline T Left(void) const {return Min(a.x, b.x);}

    ///Returns the coordinate of the bottom side.
    inline T Bottom(void) const {return Min(a.y, b.y);}

    ///Returns the coordinate of the right side.
    inline T Right(void) const {return Max(a.x, b.x);}

    ///Returns the coordinate of the top side.
    inline T Top(void) const {return Max(a.y, b.y);}

    ///Returns the coordinate of the rectangle's bottom-left corner.
    inline Complex<T> BottomLeft(void) const
    {
      return Complex<T>(Left(), Bottom());
    }

    ///Returns the coordinate of the rectangle's bottom-right corner.
    inline Complex<T> BottomRight(void) const
    {
      return Complex<T>(Right(), Bottom());
    }

    ///Returns the coordinate of the rectangle's top-left corner.
    inline Complex<T> TopLeft(void) const
    {
      return Complex<T>(Left(), Top());
    }

    ///Returns the coordinate of the rectangle's top-right corner.
    inline Complex<T> TopRight(void) const
    {
      return Complex<T>(Right(), Top());
    }

    ///Returns the coordinate of the rectangle's center.
    inline Complex<T> Center(void) const
    {
      return Complex<T>((a.x + b.x) / (T)2, (a.y + b.y) / (T)2);
    }

    ///Sets the coordinate of the left side.
    inline void Left(T NewLeft)
    {
      a.x = NewLeft;
    }

    ///Sets the coordinate of the bottom side.
    inline void Bottom(T NewBottom)
    {
      a.y = NewBottom;
    }

    ///Sets the coordinate of the right side.
    inline void Right(T NewRight)
    {
      b.x = NewRight;
    }

    ///Sets the coordinate of the top side.
    inline void Top(T NewTop)
    {
      b.y = NewTop;
    }

    /**Sets the coordinate of the rectangle's bottom-left corner.*/
    inline void BottomLeft(Complex<T> p)
    {
      a = p;
    }

    /**Sets the coordinate of the rectangle's bottom-right corner.*/
    inline void BottomRight(Complex<T> p)
    {
      b.x = p.x;
      a.y = p.y;
    }

    /**Sets the coordinate of the rectangle's top-left corner.*/
    inline void TopLeft(Complex<T> p)
    {
      a.x = p.x;
      b.y = p.y;
    }

    /**Sets the coordinate of the rectangle's top-right corner.*/
    inline void TopRight(Complex<T> p)
    {
      b = p;
    }

    /**Returns true if a particular point is contained by the rectangle. If
    the rectangle is collapsed, the point can still be contained even though
    the rectangle is empty. The rectangles includes the bottom-left point and
    excludes the top-right point.*/
    inline bool Contains(Complex<T> p) const
    {
      return p.x >= Left() && p.y >= Bottom() &&
               p.x < Right() && p.y < Top();
    }

    /**Returns whether or not a particular point is contained by the
    rectangle. If the rectangle is collapsed, the point can still be contained
    even though the rectangle is empty.*/
    inline bool Contains(const RectangleT& r) const
    {
      return Contains(r.a) && Contains(r.b);
    }

    /**Subtracts an amount to 'a', and adds an equivalent amount to 'b'. For
    positive values, the rectangle is guaranteed to always gets bigger,
    regardless of the ordering of the corners; for negative values with
    magnitude less than both the width and height of the rectangle, the
    rectangle gets smaller, and for more negative values the result is
    undefined.*/
    void Dilate(T Amount)
    {
      T SgnOfdx =  Sign(DeltaX());
      T SgnOfdy = Sign(DeltaY());
      T SgnOfdxTimesAmount = SgnOfdx * Amount;
      T SgnOfdyTimesAmount = SgnOfdy * Amount;

      a.x -= SgnOfdxTimesAmount;
      b.x += SgnOfdxTimesAmount;
      a.y -= SgnOfdyTimesAmount;
      b.y += SgnOfdyTimesAmount;
    }

    /**Computes the intersection of two rectangles. If either rectangle is
    empty then an empty rectangle is returned.*/
    static RectangleT Intersection(RectangleT r1, RectangleT r2)
    {
      if(r1.IsEmpty() || r2.IsEmpty())
        return RectangleT(); //Return an empty rectangle.

      r1.Order();
      r2.Order();

      T tblx = r1.a.x;
      T oblx = r2.a.x;
      T tbly = r1.a.y;
      T obly = r2.a.y;
      T ttrx = r1.b.x;
      T otrx = r2.b.x;
      T ttry = r1.b.y;
      T otry = r2.b.y;

      T nblx = (T)0;
      T nbly = (T)0;
      T ntrx = (T)0;
      T ntry = (T)0;

      //X-dimension
      if(tblx <= oblx && oblx <= ttrx)
      {
        nblx = oblx;
        if(otrx <= ttrx)
        {
          //CASE: OTHER is completely contained by THIS.
          ntrx = otrx;
        }
        else
        {
          //CASE: Only OTHER's minimum is contained by THIS.
          ntrx = ttrx;
        }
      }
      else if(tblx <= otrx && otrx <= ttrx)
      {
        //CASE: Only OTHER's maximum is contained by THIS.
        nblx = tblx;
        ntrx = otrx;
      }
      else if(oblx <= tblx && tblx <= otrx && oblx <= ttrx && ttrx <= otrx)
      {
        //CASE: THIS is completely contained by OTHER.
        nblx = tblx;
        ntrx = ttrx;
      }
      else
      {
        //CASE: No intersection.
        nblx = (T)0;
        ntrx = (T)0;
      }

      //Y-dimension
      if(tbly <= obly && obly <= ttry)
      {
        nbly = obly;
        if(otry <= ttry)
        {
          //CASE: OTHER is completely contained by THIS.
          ntry = otry;
        }
        else
        {
          //CASE: Only OTHER's minimum is contained by THIS.
          ntry = ttry;
        }
      }
      else if(tbly <= otry && otry <= ttry)
      {
        //CASE: Only OTHER's maximum is contained by THIS.
        nbly = tbly;
        ntry = otry;
      }
      else if(obly <= tbly && tbly <= otry && obly <= ttry && ttry <= otry)
      {
        //CASE: THIS is completely contained by OTHER.
        nbly = tbly;
        ntry = ttry;
      }
      else
      {
        //CASE: No intersection.
        nbly = (T)0;
        ntry = (T)0;
      }

      return RectangleT(Complex<T>(nblx, nbly), Complex<T>(ntrx, ntry));
    }

    /*Finds the union of two rectangles, or bounding rectangle. If one is
    empty, the other is returned. If both are empty, the result is an
    empty rectangle.*/
    static RectangleT Union(RectangleT r1, RectangleT r2)
    {
      bool r1Empty = r1.IsEmpty();
      bool r2Empty = r2.IsEmpty();

      r1.Order();
      r2.Order();

      if(r1Empty && r2Empty)
        return RectangleT(); //Return an empty rectangle.
      else if(r1Empty)
        return r2;
      else if(r2Empty)
        return r1;

      T tblx = r1.a.x;
      T oblx = r2.a.x;
      T tbly = r1.a.y;
      T obly = r2.a.y;
      T ttrx = r1.b.x;
      T otrx = r2.b.x;
      T ttry = r1.b.y;
      T otry = r2.b.y;

      Complex<T> a(Min(tblx, oblx), Min(tbly, obly));
      Complex<T> b(Max(ttrx, otrx), Max(ttry, otry));

      return RectangleT(a, b);
    }

    /*Finds the bounding rectangle of a rectangle and a point. This method
    does not check to ensure that the rectangle is valid beforehand, so it
    is possible to do a union of a collapsed rectangle of zero area and
    another vector to get the bounding rectangle of the two points.*/
    static RectangleT Union(RectangleT r1, Complex<T> p1)
    {
      T tblx = r1.a.x;
      T tbly = r1.a.y;
      T ttrx = r1.b.x;
      T ttry = r1.b.y;
      T ox = p1.x;
      T oy = p1.y;

      Complex<T> a(Min(tblx, ox), Min(tbly, oy));
      Complex<T> b(Max(ttrx, ox), Max(ttry, oy));

      return RectangleT(a, b);
    }

    /**Finds the intersection of two rectangles. The intersection is a
    commutative operation (the order of arguments does not matter).*/
    RectangleT operator - (const RectangleT& Other) const
    {
      return Intersection(*this, Other);
    }

    /**Finds the union of two rectangles. The union is a commutative
    operation (the order of arguments does not matter).*/
    RectangleT operator + (const RectangleT& Other) const
    {
      return Union(*this, Other);
    }

    /**Calculates the union of a rectangle and a point.*/
    RectangleT operator + (const Complex<T>& Other) const
    {
      return Union(*this, Other);
    }

    ///Determines if this rectangle has the same vertices as another.
    bool operator == (const RectangleT& Other) const
    {
      RectangleT r1 = *this, r2 = Other;
      return r1.a == r2.a && r1.b == r2.b;
    }
  };

  /**Type-definition for a planar rectangle with number coordinates
  \code
  *  Rectangle r(-3.2, -2.3, 5.7, 7.5);
  *  c >> r.a.x << ", " << r.a.y << " to " << r.b.x << ", " << r.b.y;
  *  c += "Area: "; c << r.Area();
  \endcode
  */
  typedef RectangleT<number> Rectangle;

  /**Type-definition for a planar rectangle with integer coordinates
  \code
  *  RectangleInt r(-3, -2, 5, 7);
  *  c >> r.a.x << ", " << r.a.y << " to " << r.b.x << ", " << r.b.y;
  *  c += "Area: "; c << r.Area();
  \endcode
  */
  typedef RectangleT<integer> RectangleInt;

  //-----//
  //Lines//
  //-----//

  ///A line segment represented by two coordinates.
  struct Line
  {
    ///The first coordinate.
    Vector a;

    ///The second coordinate.
    Vector b;

    ///Default constructor.
    Line() {}

    ///Initializing constructor with four individual coordinate values.
    Line(number x1, number y1, number x2, number y2) :
      a(x1, y1), b(x2, y2) {}

    ///Initializing constructor with two vectors.
    Line(Vector p1, Vector p2) : a(p1), b(p2) {}

    ///Returns the length of the segment ab.
    number Length(void) const
    {
      return Distance(a.x, a.y, b.x, b.y);
    }

    ///Returns the angle in radians from a to b.
    number Angle(void) const
    {
      return (b - a).Ang();
    }

    ///Makes a line segment parallel to this one with the same length.
    Line MakeParallelLine(number Displacement) const
    {
      number LineAngle = (b - a).Ang();
      number DisplacementAngle = LineAngle + HalfPi;
      Vector DisplacementVector(DisplacementAngle);
      DisplacementVector *= Displacement;
      return Line(a + DisplacementVector, b + DisplacementVector);
    }

    /*An asymptoteless line-line intersection algorithm that works equally
    well for all configurations of lines by using polar coordinates.*/
    Vector GetPolarLineIntersection(const Line& OtherLine) const
    {
      //Make copies of the parameters so we can modify them.
      Vector Start1 = a, End1 = b, Start2 = OtherLine.a, End2 = OtherLine.b;

      //Rotate the system such that line 1 is horizontal.
      number InitialAngle = (b - a).Ang();
      Start1.Ang(Start1.Ang() - InitialAngle);
      End1.Ang(End1.Ang() - InitialAngle);
      Start2.Ang(Start2.Ang() - InitialAngle);
      End2.Ang(End2.Ang() - InitialAngle);

      /*At this point Start1.y = End1.y; transpose such that line 1 becomes
      the x-axis.*/
      Vector InitialTransposition = Vector(0, Start1.y);
      Start1 -= InitialTransposition;
      End1 -= InitialTransposition;
      Start2 -= InitialTransposition;
      End2 -= InitialTransposition;

      //Now solve for x-axis intersection of line 2.
      Vector Delta = End2 - Start2;

      if(Delta.x == 0 && Delta.y == 0)
        return Vector(0, 0); //We have a point for a line.
      else if(Delta.y == 0)
        return Vector(0, 0); //We have perfectly parallel lines.

      //Initialize intersection to origin; then just find x-component.
      Vector Intersection(0, 0);

      //For lines that are more horizontal than vertical...
      if(Abs(Delta.y) < Abs(Delta.x))
      {
        /*
        Solve x-axis intersection using:
          0 = (dy/dx)x + b
          x = -b / (dy/dx) at y = 0
        with:
          b = y - (dy/dx)x
        */
        number dyOverdx = Delta.y / Delta.x;
        number b = Start2.y - dyOverdx * Start2.x;
        Intersection.x = -b / dyOverdx;
      }
      else //for lines that are as or more vertical than horizontal...
      {
        /*
        Solve x-axis intersection directly:
          x = (dx/dy)y + c
        with:
          c = x - (dx/dy)y
        */
        number dxOverdy = Delta.x / Delta.y;
        number c = Start2.x - dxOverdy * Start2.y;
        Intersection.x = c;
      }

      //Undo the transformations from the beginning.
      Intersection += InitialTransposition;
      Intersection.Ang(Intersection.Ang() + InitialAngle);

      return Intersection;
    }

    /**Calculates a line-line intersection quickly. The method assumes that
    a single intersection exists.*/
    Vector GetLineIntersection(const Line& OtherLine) const
    {
      // a1 * x + b1 * y + c1 = 0 is line 1
      number a1 = b.y - a.y;
      number b1 = a.x - b.x;
      number c1 = b.x * a.y - a.x * b.y;

      // a2 * x + b2 * y + c2 = 0 is line 2
      number a2 = OtherLine.b.y - OtherLine.a.y;
      number b2 = OtherLine.a.x - OtherLine.b.x;
      number c2 = OtherLine.b.x * OtherLine.a.y -
        OtherLine.a.x * OtherLine.b.y;

      number Determinant = a1 * b2 - a2 * b1;
      if(!Abs(Determinant))
      {
        //Lines do not intersect or are the same line.
        return Vector(0, 0);
      }

      number x = (b1 * c2 - b2 * c1) / Determinant;
      number y = (a2 * c1 - a1 * c2) / Determinant;

      Vector Intersection(x, y);

      return Intersection;
    }

    /**Returns the clockwise order of three points. Returns 1 if the points
    are clockwise; returns -1 if the points are counterclockwise; returns 0
    if the points are collinear.*/
    static inline bool DetermineClockwiseOrder(
      Vector p0, Vector p1, Vector p2)
    {
      return (p2.y - p0.y) * (p1.x - p0.x) < (p1.y - p0.y) * (p2.x - p0.x);
    }

    ///Determines whether or not this line intersects with another one.
    inline bool Intersects(const Line& OtherLine) const
    {
      number Pax = a.x, Pay = a.y, Pbx = b.x, Pby = b.y;
      number Qax = OtherLine.a.x, Qay = OtherLine.a.y,
        Qbx = OtherLine.b.x, Qby = OtherLine.b.y;

      number Pbx_Pax = Pbx - Pax;
      number Qax_Pax = Qax - Pax;
      number Qbx_Pax = Qbx - Pax;
      number Pby_Pay = Pby - Pay;
      number Qay_Pay = Qay - Pay;
      number Qby_Pay = Qby - Pay;
      number Qax_Pbx = Qax - Pbx;
      number Qbx_Pbx = Qbx - Pbx;
      number Qay_Pby = Qay - Pby;
      number Qby_Pby = Qby - Pby;

      bool Result = (Qby_Pay * Qax_Pax < Qay_Pay * Qbx_Pax) !=
      (Qby_Pby * Qax_Pbx < Qay_Pby * Qbx_Pbx) &&
      (Qay_Pay * Pbx_Pax < Pby_Pay * Qax_Pax) !=
      (Qby_Pay * Pbx_Pax < Pby_Pay * Qbx_Pax);

      return Result;
    }
  };

  //-------------//
  //Bezier Curves//
  //-------------//

  ///Represents a cubic-spline Bézier curve by its polynomial coefficients.
  struct Bezier
  {
    /*
    Coefficients describing the curve. The curve is defined as a
    polynomial for each dimension:
      f(t){x, y} = {A*t^3 + B*t^2 + C*t + D, E*t^3 + F*t^2 + G*t + H}
    */

    number a;
    number b;
    number c;
    number d;
    number e;
    number f;
    number g;
    number h;

    /**Normally a Bezier curve is defined between the points 0<=t<=1. Of
    course the actual curve is valid at all t. Trim allows you to select
    a new finite domain, so that a different selection of the curve can
    be transposed to the effective domain between zero and one. The
    selection can be greater than or less than the original domain.*/
    void Trim(number tZero, number tOne)
    {
      //Compute the new range.
      number newDelta = tOne - tZero;
      number a1 = newDelta;
      number b1 = tZero;

      /**\brief Substituting in a function f(x) = a*x + b into the
      parametric curve, solves for the new constants. \details This is
      a generalization of de Casteljau's algorithm which bisects the
      curve.*/
      number a2 = a1 * a1;
      number a3 = a2 * a1;

      number b2 = b1 * b1;
      number b3 = b2 * b1;

      number newA = a3 * a;
      number newB = 3.0f * a2 * b1 * a + a2 * b;
      number newC = 3.0f * a1 * b2 * a + 2.0f * a1 * b1 * b + a1 * c;
      number newD = b3 * a + b2 * b + b1 * c + d;

      number newE = a3 * e;
      number newF = 3.0f * a2 * b1 * e + a2 * f;
      number newG = 3.0f * a1 * b2 * e + 2.0f * a1 * b1 * f + a1 * g;
      number newH = b3 * e + b2 * f + b1 * g + h;

      //Make the assignments.
      a = newA;
      b = newB;
      c = newC;
      d = newD;

      e = newE;
      f = newF;
      g = newG;
      h = newH;
    }

    /**Creates a cubic Bezier from the requested control points. The
    curve begins at p0 and ends at p3. The points p1 and p2 are
    intermediate points of influence which typically do not lie on
    curve.*/
    void SetControlPoints(Vector p0, Vector p1, Vector p2, Vector p3)
    {
      a = p3.x - p0.x + 3.f * (p1.x - p2.x);
      b = 3.f * (p2.x - 2.f * p1.x + p0.x);
      c = 3.f * (p1.x - p0.x);
      d = p0.x;
      e = p3.y - p0.y + (number)3.f * (p1.y - p2.y);
      f = 3.f * (p2.y - (number)2.f * p1.y + p0.y);
      g = 3.f * (p1.y - p0.y);
      h = p0.y;
    }

    /**Creates a cubic Bezier from two anchors and just one control
    point. The curve begins at p0 and ends at p2. The point p1 is an
    intermediate point of influence which typically does not lie on the
    curve.*/
    void SetControlPoints(Vector p0, Vector p1, Vector p2)
    {
      a = 0;
      b = p2.x - (number)2.f * p1.x + p0.x;
      c = (number)2.f * (p1.x - p0.x);
      d = p0.x;
      e = 0;
      f = p2.y - (number)2.f * p1.y + p0.y;
      g = (number)2.f * (p1.y - p0.y);
      h = p0.y;
    }

    /**\brief Returns the control points by converting the coefficients
    into x and y coordinates.*/
    void GetControlPoints(Vector& p0, Vector& p1, Vector& p2, Vector& p3)
    {
      p0.x = d;
      p1.x = d + c / 3.f;
      p2.x = d + (number)2 / (number)3 * c + b / 3.f;
      p3.x = d + c + b + a;
      p0.y = h;
      p1.y = h + g / 3.f;
      p2.y = h + (number)2 / (number)3 * g + f / 3.f;
      p3.y = h + g + f + e;
    }

    /**Attempts to return a bezier curve parallel to this one. The start and
    end control points may not be the same.*/
    Bezier MakeQuasiParallelCurve(number Displacement)
    {
      Vector p0, p1, p2, p3;
      Vector q0, q1, q2, q3;
      GetControlPoints(p0, p1, p2, p3);
      number StartNormalAngle = (p1 - p0).Ang() + HalfPi;
      number EndNormalAngle = (p3 - p2).Ang() + HalfPi;
      q0 = p0 + Vector(StartNormalAngle) * Displacement;
      q3 = p3 + Vector(EndNormalAngle) * Displacement;
      number Scale = Line(q0, q3).Length() / Line(p0, p3).Length();
      q1 = q0 + (p1 - p0) * Scale;
      q2 = q3 + (p2 - p3) * Scale;
      Bezier bezier;
      bezier.SetControlPoints(q0, q1, q2, q3);
      return bezier;
    }

    ///Returns the coordinate of the cubic spline for some t.
    Vector Value(number t)
    {
      Vector v;

      number t2 = t * t;
      number t3 = t * t2;

      v.x = a * t3 + b * t2 + c * t + d;
      v.y = e * t3 + f * t2 + g * t + h;

      return v;
    }

    /**\brief Finds the curve's vertical tangents by computing the
    derivative of the x-polynomial and finding the zeroes.*/
    count VerticalTangents(number& Root1, number& Root2)
    {
      number a = (number)3.0 * Bezier::a;
      number b = (number)2.0 * Bezier::b;
      number c = Bezier::c;

      count NumberOfRoots = Roots(a, b, c, Root1, Root2);

      /*Assure that we only get roots in the 0 to 1 range of the
      Bezier curve.*/
      if(NumberOfRoots == 2)
      {
        if(Root1 >= (number)0.0 && Root1 <= (number)1.0)
        {
          if(Root2 >= (number)0.0 && Root2 <= (number)1.0)
          {
            return 2;
          }
          else
          {
            Root2 = 0;
            return 1;
          }
        }
        else if(Root2 >= (number)0.0 && Root2 <= (number)1.0)
        {
          Root1 = Root2;
          Root2 = 0;
          return 1;
        }
        else
        {
          Root1 = 0;
          Root2 = 0;
          return 0;
        }
      }
      else if(NumberOfRoots == 1)
      {
        if(Root1 >= (number)0.0 && Root1 <= (number)1.0)
        {
          return 1;
        }
        else
        {
          Root1 = 0;
          return 0;
        }
      }
      return 0;
    }

    /**\brief Finds the curve's horizontal tangents by computing the
    derivative of the y-polynomial and finding the zeroes.*/
    count HorizontalTangents(number& Root1, number& Root2)
    {
      number a = (number)3.0 * Bezier::e;
      number b = (number)2.0 * Bezier::f;
      number c = Bezier::g;

      count NumberOfRoots = Roots(a, b, c, Root1, Root2);

      /*Assure that we only get roots in the 0 to 1 range of the
      Bezier curve.*/
      if(NumberOfRoots == 2)
      {
        if(Root1 >= (number)0.0 && Root1 <= (number)1.0)
        {
          if(Root2 >= (number)0.0 && Root2 <= (number)1.0)
          {
            return 2;
          }
          else
          {
            Root2 = 0;
            return 1;
          }
        }
        else if(Root2 >= (number)0.0 && Root2 <= (number)1.0)
        {
          Root1 = Root2;
          Root2 = 0;
          return 1;
        }
        else
        {
          Root1 = 0;
          Root2 = 0;
          return 0;
        }
      }
      else if(NumberOfRoots==1)
      {
        if(Root1 >= (number)0.0 && Root1 <= (number)1.0)
        {
          return 1;
        }
        else
        {
          Root1 = 0;
          return 0;
        }
      }
      return 0;
    }

    /**Fits a Bezier curve to a quadrant of an ellipse. Just four cubic
    splines can approximate any ellipse to an error of just one part per
    thousand, which is really convenient for drawing circles that just
    need to look like circles. Even at full screen size, it will only be
    off by about a pixel in some places. Good enough for now!*/
    void Ellipse(Vector Origin, Vector Scale, number Rotation,
      count Quadrant, bool isCounterClockwise)
    {
      /*This is the so-called magic number, which is the distance the
      perpendicular influence points must be from anchors in order to
      produce a curve that is most like a circle/ellipse.*/
      const number FourSplineMagicNumber = (number)0.551784;

      number Width = Scale.x * (number)0.5;
      number Height = Scale.y * (number)0.5;

      Vector p0;
      Vector p1;
      Vector p2;
      Vector p3;

      Quadrant = (count)Mod(Quadrant, (count)4);
      if(Quadrant == 0)
        Quadrant=4;

      if(Quadrant == 3 || Quadrant == 4)
      {
        Rotation += Pi;
        Quadrant -= 2;
      }

      if(Quadrant == 1)
      {
        p0.Polar(Rotation, Width);
        p3.Polar(Rotation + HalfPi, Height);

        p1.Polar(Rotation + HalfPi, Height * FourSplineMagicNumber);
        p1 += p0;

        p2.Polar(Rotation, Width * FourSplineMagicNumber);
        p2 += p3;
      }
      else if(Quadrant == 2)
      {
        p0.Polar(Rotation + HalfPi, Height);
        p3.Polar(Rotation + Pi, Width);

        p1.Polar(Rotation + Pi, Width * FourSplineMagicNumber);
        p1 += p0;

        p2.Polar(Rotation + HalfPi, Height * FourSplineMagicNumber);
        p2 += p3;
      }

      p0 += Origin;
      p1 += Origin;
      p2 += Origin;
      p3 += Origin;

      if(isCounterClockwise)
        SetControlPoints(p0, p1, p2, p3);
      else
        SetControlPoints(p3, p2, p1, p0);
    }

    number FindSimpleYRoot(number tBisectStart = 0,
      number tBisectEnd = (number)1.0)
    {
      count i = 0;
      while(tBisectEnd - tBisectStart > (number)0.00001 && i < 100)
      {
        i++;
        number v0 = Value(tBisectStart).y;
        number tBisect = (tBisectStart + tBisectEnd) * (number)0.5;
        number v1 = Value(tBisect).y;
        number v2 = Value(tBisectEnd).y;
        if((v0 < v1 && v0 <= 0 && v1 >= 0) ||
          (v0 >= v1 && v1 <= 0 && v0 >= 0))
            tBisectEnd = tBisect;
        else if((v1 < v2 && v1 <= 0 && v2 >= 0) ||
          (v1 >= v2 && v2 <= 0 && v1 >= 0))
            tBisectStart = tBisect;
        else
          return 0;
      }
      return (tBisectStart + tBisectEnd) * (number)0.5;
    }

    number FindLineIntersection(Line l)
    {
      number Rotation = -l.Angle();

      /*Rotate and vertically translate the line and curve such that the line
      is horizontal and use Newton's method to solve for the y-root.*/
      Vector p0, p1, p2, p3;
      GetControlPoints(p0, p1, p2, p3);
      l.a.Ang(l.a.Ang() + Rotation);
      l.b.Ang(l.b.Ang() + Rotation);
      p0.Ang(p0.Ang() + Rotation);
      p1.Ang(p1.Ang() + Rotation);
      p2.Ang(p2.Ang() + Rotation);
      p3.Ang(p3.Ang() + Rotation);

      number Translation = -l.a.y;
      p0.y += Translation;
      p1.y += Translation;
      p2.y += Translation;
      p3.y += Translation;

      Bezier b_root; b_root.SetControlPoints(p0, p1, p2, p3);
      return b_root.FindSimpleYRoot();
    }

    void SplitBezier(Bezier& Left, Bezier& Right)
    {
      Left = *this;
      Right = *this;
      Left.Trim(0, 0.5f);
      Right.Trim(0.5f, 1.0f);
    }

    number CalculateArcLength(number Tolerance = 0.001f)
    {
      Vector v0, v1, v2, v3;
      GetControlPoints(v0, v1, v2, v3);
      number PolygonLength = (v0 - v1).Mag() + (v1 - v2).Mag() +
        (v2 - v3).Mag();
      number ChordLength = (v0 - v3).Mag();
      number CurrentError = PolygonLength - ChordLength;
      if(CurrentError > Tolerance)
      {
        Bezier Left, Right;
        SplitBezier(Left, Right);
        return Left.CalculateArcLength(Tolerance) +
          Right.CalculateArcLength(Tolerance);
      }
      else
        return PolygonLength * (number)0.5 + ChordLength * (number)0.5;
    }

    number Length(number Point1 = 1.0f, number Point2 = 0.0f,
      number Tolerance = 0.001f)
    {
      Ascending(Point1, Point2);
      Bezier SubArc = *this; SubArc.Trim(Point1, Point2);
      return SubArc.CalculateArcLength(Tolerance);
    }
  };

  //--------//
  //Ellipses//
  //--------//

  ///Computes information related to rotated ellipses.
  struct Ellipse
  {
    /**\brief Computes the vertical tangent of an ellipse given the the
    lengths of the semimajor and semiminor axises (in other words the
    'horizontal radius' and the 'vertical radius').*/
    static inline Vector VerticalTangent(number a, number b,
      number Rotation)
    {
      //Compute the angle t at which the vertical tangent takes place.
      number cos_theta = Cos(Rotation);
      number sin_theta = Sin(Rotation);

      number a_cos_theta = a * cos_theta;
      number a_sin_theta = a * sin_theta;
      number b_cos_theta = b * cos_theta;
      number b_sin_theta = b * sin_theta;

      number t = ArcTan(-b_sin_theta / a_cos_theta);

      /*Apply the matrix rotation algorithm to determine the Cartesian
      components.*/
      number cos_t = Cos(t);
      number sin_t = Sin(t);

      Vector v(a_cos_theta * cos_t - b_sin_theta * sin_t,
           a_sin_theta * cos_t + b_cos_theta * sin_t);

      return v;
    }

    /**\brief Computes the horizontal tangent of an ellipse given the
    the lengths of the semimajor and semiminor axises (in other words
    the 'horizontal radius' and the 'vertical radius').*/
    static inline Vector HorizontalTangent(number a, number b,
      number Rotation)
    {
      //Compute the angle 't' at which the horizontal tangent takes place
      number cos_theta = Cos(Rotation);
      number sin_theta = Sin(Rotation);

      number a_cos_theta = a * cos_theta;
      number a_sin_theta = a * sin_theta;
      number b_cos_theta = b * cos_theta;
      number b_sin_theta = b * sin_theta;

      number t = ArcTan(b_cos_theta / a_sin_theta);

      /*Apply the matrix rotation algorithm to determine the Cartesian
      components.*/
      number cos_t = Cos(t);
      number sin_t = Sin(t);

      Vector v(a_cos_theta * cos_t - b_sin_theta * sin_t,
           a_sin_theta * cos_t + b_cos_theta * sin_t);

      return v;
    }

    /**\brief Finds the intersection of a vertical line and quadrant one
    of an ellipse by converting it to a spline and using a binary search
    algorithm to look for the intersection.

    It's a little fickle if you don't use it right, so be careful! This
    algorithm is used for creating an exact path for a note and a stem, so
    that a single contiguous outline may be traced.*/
    static number VerticalIntersection(number a, number b,
      number Rotation, number distFromRightVerticalTangent)
    {
      /*This solves for 't' in the cubic spline in quadrant one.*/

      /*Cache the result so that if the same inputs are given next
      time, it will only be a matter of retrieval.*/
      static number cur_a = 0.0;
      static number cur_b = 0.0;
      static number cur_theta = 0.0;
      static number cur_dist = 0.0;
      static number cur_result = 0.0;

      if(a == cur_a && b == cur_b && Rotation == cur_theta
        && distFromRightVerticalTangent == cur_dist)
        return cur_result;

      //Set the cache input properties
      cur_a = a;
      cur_b = b;
      cur_theta = Rotation;
      cur_dist = distFromRightVerticalTangent;

      //Simply use the origin as the center.
      Vector o(0,0);

      //Scale the ellipse.
      Vector s(cur_a * (number)2.0, cur_b * (number)2.0);

      //Create a cubic spline based off of the input information.
      Bezier c;
      c.Ellipse(o,s,cur_theta,1,true);

      //Compute the vertical tangent.
      Vector i;
      i = VerticalTangent(cur_a,cur_b,cur_theta);
      number lx = i.x - distFromRightVerticalTangent;

      //Set the conditions for exiting.
      const number error_acceptability=(number)0.001;
      const count max_steps = 30;

      //Set the initial search bounds.
      number bound_l = 0.0;
      number bound_r = 1.0;
      number bound_mid = 0.0;

      //Get the values of the curve at the ends.
      Vector bound_l_v = c.Value(0.0);
      Vector bound_r_v = c.Value(1.0);

      //Do a binary subdivision search to quickly hone in.
      for(count steps = 0; steps < max_steps; steps++)
      {
        bound_mid = (bound_r + bound_l) / (number)2.0;
        Vector mid_value = c.Value(bound_mid);

        number mx = Abs(mid_value.x);
        number err = Abs(mx - lx);

        //If the error tolerance is acceptable, leave.
        if(err < error_acceptability)
          break;

        //Depending on which side was closer, adjust the boundaries
        if(mid_value.x < lx)
          bound_r = bound_mid;
        else
          bound_l = bound_mid;
      }

      //Cache the result.
      cur_result = bound_mid;

      //Return the result.
      return cur_result;
    }

    /**A helper method for retrieving a elliptical cubic spline. The
    parameters are the same as the fromEllipse method of the Bezier
    class, but the advantage here is that a new cubic spline is
    returned, where as in the other method, you must already have a
    Bezier object declared.*/
    static Bezier toSpline(Vector& Origin, Vector& Scale,
      number Rotation, count Quadrant, bool isCounterClockwise)
    {
      Bezier c;
      c.Ellipse(Origin, Scale, Rotation, Quadrant, isCounterClockwise);
      return c;
    }
  };

  //--------//
  //Polygons//
  //--------//

  ///An array of vertices.
  struct Polygon : public Array<Vector>
  {
    private:

    /*The following class is used to enable use of the list Quicksort method
    in the three-penny convex hull finding algorithm.*/
    struct RadialSortingVector : public Vector
    {
      //Cached angle to make sorting faster.
      number Angle;

      bool operator < (const RadialSortingVector& Other) const
      {
        return Angle < Other.Angle;
      }

      bool operator > (const RadialSortingVector& Other) const
      {
        return Angle > Other.Angle;
      }

      bool operator == (const RadialSortingVector& Other) const
      {
        return Angle == Other.Angle;
      }
    };

    public:

    ///Clears the polygon.
    void Clear(void)
    {
      Array<Vector>::Clear();
    }

    ///Determines whether or not this polygon intersects the outline of another.
    bool IntersectsOutline(const Polygon& Other, Vector OtherDisplacement =
      Vector(0, 0)) const
    {
      Vector p1, p2, q1, q2;

      p1 = z();
      for(count i = n() - 2; i >= 0; i--)
      {
        p2 = ith(i);
        q1 = Other.z() + OtherDisplacement;
        for(count j = Other.n() - 2; j >= 0; j--)
        {
          q2 = Other.ith(j) + OtherDisplacement;
          Line P(p1, p2), Q(q1, q2);
          if(P.Intersects(Q))
            return true;
          q1 = q2;
        }
        p1 = p2;
      }
      return false;
    }

    /**Determines the order of three points. The result can be as clockwise (1),
    counterclockwise (-1), or collinear (0).*/
    static inline count DeterminePointOrder(Vector p0, Vector p1, Vector p2)
    {
      number p1x_p0x = p1.x - p0.x;
      number p2x_p0x = p2.x - p0.x;
      number p1y_p0y = p1.y - p0.y;
      number p2y_p0y = p2.y - p0.y;

      number Left  = p2y_p0y * p1x_p0x;
      number Right = p1y_p0y * p2x_p0x;

      if(Left < Right)
        return 1;
      else if(Left == Right)
        return 0;
      else
        return -1;
    }

    /**Creates a new polygon consisting of the convex hull of this polygon. The
    algorithm employed is the three-penny convex hull finder.*/
    void CreateConvexHull(Polygon& NewPolygon) const
    {
      //Make sure there are at least three points to work with.
      if(n() < 3)
      {
        if(n())
          NewPolygon = *this;
        else
          NewPolygon.Clear();
        return;
      }

      //Copy polygon array into temporary list.
      Sortable::List<RadialSortingVector> L;
      {
        //First find left-most point.
        count this_n = n();
        count LeftMostIndex = 0;
        number LeftMostX = a().x;
        for(count i = 1; i < this_n; i++)
        {
          number CurrentX = ith(i).x;
          if(CurrentX < LeftMostX)
          {
            LeftMostIndex = i;
            LeftMostX = CurrentX;
          }
        }

        /*Now add the points with the left-most point first. This guarantees
        that the first three points in the list will be convex.*/
        for(count i = LeftMostIndex; i < this_n; i++)
          static_cast<Vector&>(L.Add()) = ith(i);

        for(count i = 1; i <= LeftMostIndex; i++)
          static_cast<Vector&>(L.Add()) = ith(i);

        ///Determine the beginning point order.
        Vector L_0 = L[0];
        while(DeterminePointOrder(L_0, L[1], L[2]) == 0)
          L.Remove(1);

        //Determine the angles of the points so that they can be sorted.
        RadialSortingVector v = L[0];
        count L_n_1 = L.n() - 1;
        for(count i = 1; i < L_n_1; i++)
        {
          number Angle = v.Ang(L[i]);
          if(Angle > Pi)
            Angle -= TwoPi;
          L[i].Angle = Angle;
        }

        //Force the first point to be first in the list after the sort.
        L[0].Angle = -Pi;

        //Force the last point to be last in the list after the sort.
        L[L_n_1].Angle = Pi;

        //Sort the vector list radially.
        L.QuickSort();
      }

      //Using the three-penny convex hull algorithm.
      for(count i = 0; i < L.n() - 2; i++)
      {
        Vector p0 = L[i], p1 = L[i + 1], p2 = L[i + 2];
        if(DeterminePointOrder(p0, p1, p2) != -1)
        {
          L.Remove(i + 1);
          i -= 2;
        }
      }

      //Copy results into new polygon.
      {
        NewPolygon.Clear();

        Vector L_first = L.a();
        NewPolygon.n(L.n());
        NewPolygon[0] = L_first;

        count L_n = L.n();
        for(count i = 1; i < L_n; i++)
          NewPolygon[i] = L[i];
      }
    }
  };
}}
#endif

#endif
#ifdef PRIM_WITH_THREAD //Depends on non-portable system headers

#ifndef PRIM_THREAD_H
#define PRIM_THREAD_H

/*Module Configuration
================================================================================
Threads are upcoming in C++11 via std::thread. You may enable their use if your
compiler supports them by enabling:*/

//#define PRIM_THREAD_USE_STD_THREAD

/*The std::thread implementation is known to work with the following.

On Mac (Xcode 4.2), you can now use clang++ with std::thread:
clang++ -stdlib=libc++ -std=c++0x -o BinaryName SourceFile1.cpp ...

On Linux (GCC 4.5+), you can use g++:
g++ -std=c++0x -pthread -o BinaryName SourceFile1.cpp ...

Otherwise:
1) If you are on a Windows system then Windows API threads will be used.
2) If you are on a POSIX then Pthreads will be used. You may need to compile
   with the -pthread or -pthreads compiler option.*/
/*==============================================================================
End Module Configuration*/

#ifndef PRIM_THREAD_USE_STD_THREAD
  #ifdef PRIM_ENVIRONMENT_WINDOWS
    //Use thread API from <windows.h>
    #define PRIM_THREAD_USE_WINDOWS
  #elif defined(PRIM_ENVIRONMENT_POSIX)
    //Use thread API from <pthread.h>
    #define PRIM_THREAD_USE_PTHREAD
  #endif
#endif

namespace prim
{
  ///Recursive thread mutex maintaining a lock and unlock count.
  class Mutex
  {
    //The mutex object -- (void*) avoids including thread headers in this file.
    void* RecursiveMutex;

    public:

    ///Initializes the mutex with a lock count of zero.
    Mutex();

    ///Releases the mutex. The lock count must be zero at this point.
    ~Mutex();

    ///Blocks until a lock is established, incrementing the lock count.
    void Lock(void);

    ///Attempts to establish a lock but returns false if unsuccessful.
    bool TryLock(void);

    /**Decrements the lock count. If the lock count is greater than the unlock
    count, then the lock is still in effect (since it is a recursive mutex).*/
    void Unlock(void);
  };

  ///Locks a given mutex for the lifetime of the object.
  class Lock
  {
    Mutex& ScopedMutex;

    public:
    ///Locks the given mutex.
    Lock(Mutex& ScopedMutex) : ScopedMutex(ScopedMutex)
    {
      ScopedMutex.Lock();
    }

    ///Deleted assignment operator.
    Lock& operator = (const Lock&);

    ///Unlocks the mutex.
    ~Lock()
    {
      ScopedMutex.Unlock();
    }
  };

  ///Base class from which threads inherit and implement their run loops.
  class Thread
  {
    //The platform thread object
    void* ThreadObject; //(void*) avoids including thread headers in this file.

    //Thread state signal
    Mutex InternalMutex;

    //Thread state flags
    bool Running;
    bool Ending;

  #ifdef PRIM_THREAD_USE_PTHREAD
    static void* BeginThread(void* VoidThreadPointer);
  #elif defined(PRIM_THREAD_USE_WINDOWS)
    static unsigned long __stdcall BeginThread(void* VoidThreadPointer);
  #else
    static void BeginThread(Thread* ThreadPointer);
  #endif

    public:

    /**Overload and place thread contents inside. If the thread can be
    interrupted, then make sure to call IsEnding() frequently to see whether or
    not the method should return. You can signal a thread to end by calling
    SignalEnd().*/
    virtual void Run(void) = 0;

    ///Initializes but does not begin the thread.
    Thread();

    /**Releases the thread. WaitToEnd() must be called before this time, or
    else a crash may occur due to members in the subclass not being available.*/
    virtual ~Thread();

    /**Begins the thread. If the thread is already running, then it will wait
    for the current thread instance to end before running the new instance.*/
    bool Begin(void);

    /**Determines whether the end-state was signaled by SignalEnd(). A thread
    that receives true from this method should clean-up and end Run() as quickly
    as possible.*/
    bool IsEnding(void)
    {
      Lock Lock(InternalMutex);
      return Ending;
    }

    /**Determines whether or not the thread is still running. Note that a thread
    is considered to be running until WaitToEnd() is called. Even if the Run()
    method has already returned, the thread is still considered active.*/
    bool IsRunning(void)
    {
      Lock Lock(InternalMutex);
      return Running;
    }

    /**Indicates to the thread that it should end as soon as possible. This is
    achieved by periodically checking IsEnding() in the Run() method and exiting
    if necessary.*/
    void SignalEnd(void)
    {
      Lock Lock(InternalMutex);
      Ending = true;
    }

    /**The proper way to clean up a thread. It automatically signals the thread
    to exit using SignalEnd(), and will block the caller thread until it
    exits.*/
    void WaitToEnd(void);
  };

  ///Thread-safe versions of the primitives
  struct Threadable
  {
    class Console : public prim::Console
    {
      ///Mutex to protect console output.
      Mutex m;

      public:

      ///Appends the fragment to the console within a mutex lock.
      virtual void Append(const byte* Fragment, count Length)
      {
        Lock l(m);
        prim::Console::Append(Fragment, Length);
      }

      ///Appends a newline if string is not empty and then applies << operator.
      template <class T>
      String& operator >> (T v)
      {
        Lock l(m);
        if(n())
          prim::String::Append(Newline);
        *this << v;
        return *this;
      }

      ///Appends a newline if string is not empty and then appends the value.
      template <class T>
      String& operator += (T v)
      {
        Lock l(m);
        *this >> v;
        return *this;
      }

      ///Appends a space and then appends the value.
      template <class T>
      String& operator -= (T v)
      {
         Lock l(m);
        *this << " " << v;
        return *this;
      }
    };
  };

  //Threadable global console object for when the thread module is used.
  extern Threadable::Console c;
}

#ifdef PRIM_COMPILE_INLINE

#ifdef PRIM_THREAD_USE_PTHREAD
#include <pthread.h> //Pthreads
#elif defined(PRIM_THREAD_USE_WINDOWS)
#include <windows.h> //Windows API threads
#else
#include <thread>    //std::thread
#endif

namespace prim
{
  //Threadable global console object (non-threadable version not used).
  Threadable::Console c;

  Mutex::Mutex()
  {
#ifdef PRIM_THREAD_USE_PTHREAD
    //Create the mutex attributes object for a recursive mutex.
    pthread_mutexattr_t MutexAttributes;
    pthread_mutexattr_init(&MutexAttributes);
    pthread_mutexattr_settype(&MutexAttributes, PTHREAD_MUTEX_RECURSIVE);

    //Initialize the mutex using the attributes object.
    RecursiveMutex = (void*)new pthread_mutex_t;
    pthread_mutex_init((pthread_mutex_t*)RecursiveMutex, &MutexAttributes);
#elif defined(PRIM_THREAD_USE_WINDOWS)
    RecursiveMutex = (void*)new HANDLE;
    *((HANDLE*)RecursiveMutex) = CreateMutex(0, FALSE, 0);
#else
    RecursiveMutex = (void*)new std::recursive_mutex;
#endif
  }

  Mutex::~Mutex()
  {
#ifdef PRIM_THREAD_USE_PTHREAD
    delete (pthread_mutex_t*)RecursiveMutex;
#elif defined(PRIM_THREAD_USE_WINDOWS)
    CloseHandle(*((HANDLE*)RecursiveMutex));
#else
    delete (std::recursive_mutex*)RecursiveMutex;
#endif
  }

  void Mutex::Lock(void)
  {
#ifdef PRIM_THREAD_USE_PTHREAD
    pthread_mutex_lock((pthread_mutex_t*)RecursiveMutex);
#elif defined(PRIM_THREAD_USE_WINDOWS)
    WaitForSingleObject(*((HANDLE*)RecursiveMutex), INFINITE);
#else
    ((std::recursive_mutex*)RecursiveMutex)->lock();
#endif
  }

  bool Mutex::TryLock(void)
  {
#ifdef PRIM_THREAD_USE_PTHREAD
    return pthread_mutex_trylock((pthread_mutex_t*)RecursiveMutex) == 0;
#elif defined(PRIM_THREAD_USE_WINDOWS)
    return WaitForSingleObject(*((HANDLE*)RecursiveMutex), 0) == WAIT_OBJECT_0;
#else
    return ((std::recursive_mutex*)RecursiveMutex)->try_lock();
#endif
  }

  void Mutex::Unlock(void)
  {
#ifdef PRIM_THREAD_USE_PTHREAD
    pthread_mutex_unlock((pthread_mutex_t*)RecursiveMutex);
#elif defined(PRIM_THREAD_USE_WINDOWS)
    ReleaseMutex(*((HANDLE*)RecursiveMutex));
#else
    ((std::recursive_mutex*)RecursiveMutex)->unlock();
#endif
  }

#ifdef PRIM_THREAD_USE_PTHREAD
  void* Thread::BeginThread(void* VoidThreadPointer)
  {
    Thread* ThreadPointer = (Thread*)VoidThreadPointer;
    {Lock(ThreadPointer->InternalMutex);} //Wait for initialization
    ThreadPointer->Run();
    return 0;
  }
#elif defined(PRIM_THREAD_USE_WINDOWS)
  unsigned long __stdcall Thread::BeginThread(void* VoidThreadPointer)
  {
    Thread* ThreadPointer = (Thread*)VoidThreadPointer;
    {Lock(ThreadPointer->InternalMutex);} //Wait for initialization
    ThreadPointer->Run();
    return 0;
  }
#else
  void Thread::BeginThread(Thread* ThreadPointer)
  {
    {Lock(ThreadPointer->InternalMutex);} //Wait for initialization
    ThreadPointer->Run();
  }
#endif

  Thread::Thread() : Running(false), Ending(false)
  {
#ifdef PRIM_THREAD_USE_PTHREAD
    ThreadObject = (void*)new pthread_t;
#elif defined(PRIM_THREAD_USE_WINDOWS)
    ThreadObject = (void*)new HANDLE;
#else
    ThreadObject = (void*)new std::thread;
#endif
  }

  Thread::~Thread()
  {
    /*This is to prevent a crash, but all threads should be ended before they
    go out of scope or are deleted. It is really too late here to end the thread
    since the subclass has had member data deleted already.*/
    WaitToEnd();
#ifdef PRIM_THREAD_USE_PTHREAD
    delete (pthread_t*)ThreadObject;
#elif defined(PRIM_THREAD_USE_WINDOWS)
    delete (HANDLE*)ThreadObject;
#else
    delete (std::thread*)ThreadObject;
#endif
  }

  bool Thread::Begin(void)
  {
    WaitToEnd();
    {
      Lock Lock(InternalMutex);
      Running = true;
#ifdef PRIM_THREAD_USE_PTHREAD
      pthread_attr_t ThreadAttributes;
      pthread_attr_init(&ThreadAttributes);
      pthread_attr_setdetachstate(&ThreadAttributes, PTHREAD_CREATE_JOINABLE);
      pthread_create((pthread_t*)ThreadObject, &ThreadAttributes, BeginThread,
        (void*)this);
#elif defined(PRIM_THREAD_USE_WINDOWS)
      DWORD ThreadID = 0;
      *((HANDLE*)ThreadObject) = CreateThread(NULL, 0,
      (LPTHREAD_START_ROUTINE)Thread::BeginThread, (LPVOID)this, 0, &ThreadID);
#else
     *((std::thread*)ThreadObject) = std::thread(BeginThread, this);
#endif
      return true;
    }
  }

  void Thread::WaitToEnd(void)
  {
    if(!IsRunning())
      return;
    SignalEnd();
#ifdef PRIM_THREAD_USE_PTHREAD
    pthread_join(*(pthread_t*)ThreadObject, 0);
#elif defined(PRIM_THREAD_USE_WINDOWS)
    WaitForSingleObject(*((HANDLE*)ThreadObject), INFINITE);
#else
    ((std::thread*)ThreadObject)->join();
#endif
    {
      Lock Lock(InternalMutex);
      Ending = false;
      Running = false;
    }
  }
}
#endif
#endif

#endif
#ifdef PRIM_WITH_TIMER //Depends on non-portable system headers

#ifndef PRIM_TIMER_H
#define PRIM_TIMER_H

namespace prim
{
  ///High-precision timer capable of clocking to the microsecond.
  class Timer
  {
    ///Indicates whether the timer is currently running.
    bool Running;

    ///The length of a tick on systems that use ticks.
    float64 Period;

    ///Start time point in seconds.
    float64 StartTime;

    ///End time point in seconds.
    float64 EndTime;

    ///Seconds accumulated if multiple passes are used.
    float64 AccumulatedTime;

    public:

    ///Initializes the timer.
    Timer();

    ///Begins the timer.
    void Start(void);

    /**Stops the timer and reports the elapsed time in seconds. Any accumulation
    from pauses is cleared after being added to the elapsed time.*/
    number Stop(void);

    /**Pauses the timer until the timer is started again. Time is accumulated.
    Currently elapsed time is reported in seconds.*/
    number Pause(void);

    ///Reports the elapsed time in seconds without stopping the timer.
    number Elapsed(void);
  };
#ifdef PRIM_COMPILE_INLINE

#ifdef PRIM_ENVIRONMENT_WINDOWS
  #include <windows.h>
#else
  #include <sys/time.h>
#endif

  Timer::Timer() : Running(false), Period(0.0), StartTime(0.0), EndTime(0.0),
    AccumulatedTime(0.0)
  {
  #ifdef WIN32
    LARGE_INTERGER PerformanceFrequency;
    QueryPerformanceFrequency(&PerformanceFrequency);
    if(PerformanceFrequency.QuadPart)
      Period = (float64)1.0 / (float64)PerformanceFrequency.QuadPart;
  #endif
  }

  void Timer::Start(void)
  {
    Running = true;
#ifdef PRIM_ENVIRONMENT_WINDOWS
    LARGE_INTEGER StartTicks;
    QueryPerformanceTickser(&StartTicks);
    StartTime = (float64)StartTicks.QuadPart * Period;
#else
    timeval StartTicks;
    gettimeofday(&StartTicks, 0);
    StartTime = (float64)StartTicks.tv_sec +
      (float64)StartTicks.tv_usec * 0.000001;
#endif
  }

  number Timer::Stop(void)
  {
    if(!Running)
      return Elapsed();
    Running = false;
#ifdef PRIM_ENVIRONMENT_WINDOWS
    LARGE_INTEGER EndTicks;
    QueryPerformanceTickser(&EndTicks);
    EndTime = (float64)EndTicks.QuadPart * Period;
#else
    timeval EndTicks;
    gettimeofday(&EndTicks, 0);
    EndTime = (float64)EndTicks.tv_sec + (float64)EndTicks.tv_usec * 0.000001;
#endif
    EndTime += AccumulatedTime;
    AccumulatedTime = 0.0;
    return (number)(EndTime - StartTime);
  }

  number Timer::Pause(void)
  {
    if(!Running)
      return Elapsed();
    Running = false;
#ifdef PRIM_ENVIRONMENT_WINDOWS
    LARGE_INTEGER EndTicks;
    QueryPerformanceTickser(&EndTicks);
    EndTime = (float64)EndTicks.QuadPart * Period;
#else
    timeval EndTicks;
    gettimeofday(&EndTicks, 0);
    EndTime = (float64)EndTicks.tv_sec + (float64)EndTicks.tv_usec * 0.000001;
#endif
    AccumulatedTime += EndTime - StartTime;
    EndTime = StartTime;
    return (number)Elapsed();
  }

  number Timer::Elapsed()
  {
    if(Running)
    {
#ifdef PRIM_ENVIRONMENT_WINDOWS
      LARGE_INTEGER EndTicks;
      QueryPerformanceTickser(&EndTicks);
      EndTime = (float64)EndTicks.QuadPart * Period;
#else
      timeval EndTicks;
      gettimeofday(&EndTicks, 0);
      EndTime = (float64)EndTicks.tv_sec + (float64)EndTicks.tv_usec * 0.000001;
#endif
    }
    return (number)(EndTime + AccumulatedTime - StartTime);
  }
#endif
}
#endif

#endif
#ifdef PRIM_WITH_XML

#ifndef PRIM_XML_H
#define PRIM_XML_H

namespace prim {
///Classes for parsing and binding XML as a DOM tree.
struct XML
{
  ///Base class from which all bound elements derive.
  struct Parser
  {
    ///Internal representation of a segment of text within the XML stream.
    struct Token
    {
      const ascii* Position;
      count ByteLength;
      String Text;

      Token() : Position(0), ByteLength(0) {}

      ///Caches a String copy of the token in member Text.
      void UpdateString(void)
      {
        Text.Clear();
        if(ByteLength && Position)
          Text.Append((const byte*)Position, ByteLength);
      }

      Token& operator = (const Token& Other)
      {
        Position = Other.Position;
        ByteLength = Other.ByteLength;
        Text = Other.Text;

        return *this;
      }
    };

    /**Parses the next 'word'. A word is found by first skipping over any
    white space (as defined by an array of unicode codepoints terminated by
    zero) and then parsing a run of characters until either a white space
    delimiter is found or a word delimiter is found (also defined by an array of
    unicode codepoints terminated by zero). The parser automatically increments
    the pointer to the first character after the word (whether it is white space
    or not). If the first character in a word is a word delimiter then only
    that character will be returned.*/
    static Token ParseNextWord(const ascii*& UTF8String, const ascii* MarkupEnd,
      const unicode* WhiteSpaceDelimiters,
      const unicode* AdditionalWordDelimiters)
    {
      //1) Skip through the white space.
      Token Word;
      {
        const ascii* ptrPreviousCharacter = UTF8String;
        bool isSearchingWhiteSpace = true;
        unicode Character = 0;
        while(isSearchingWhiteSpace)
        {
          //Decode the next UTF8 character.
          ptrPreviousCharacter = UTF8String;
          Character = String::Decode((const byte*&)UTF8String,
            (const byte*)MarkupEnd);

          //At the end of stream -- no word.
          if(!Character)
          {
            Word.UpdateString();
            return Word;
          }

          //Check to see if the character is white space.
          bool isWhiteSpace = false;
          const unicode* WhiteSpaceDelimiterCheck = WhiteSpaceDelimiters;
          while(*WhiteSpaceDelimiterCheck)
          {
            if(Character == *WhiteSpaceDelimiterCheck)
            {
              isWhiteSpace = true;
              break;
            }
            WhiteSpaceDelimiterCheck++;
          }

          if(!isWhiteSpace)
          {
            //The beginning of the word has been found.
            isSearchingWhiteSpace = false;

            /*Decrement the UTF8 string pointer so that it points to the
            beginning of the word.*/
            Word.Position = UTF8String = ptrPreviousCharacter;
          }

          //Otherwise keep skipping white space characters.
        }
      }

      /*2) Determine the word's length by searching for the next white space
      or word delimiter.*/
      {
        const ascii* ptrPreviousCharacter = UTF8String;
        bool isSearchingWord = true;
        unicode Character = 0;
        count WordLength = 0;
        while(isSearchingWord)
        {
          //Decode the next UTF8 character.
          ptrPreviousCharacter = UTF8String;
          Character = String::Decode((const byte*&)UTF8String,
            (const byte*)MarkupEnd);

          //At the end of the stream -- word runs to the end of the stream.
          if(!Character)
          {
            UTF8String = ptrPreviousCharacter;
            Word.ByteLength = (count)(UTF8String - Word.Position);
            Word.UpdateString();
            return Word;
          }

          //Increment the character count.
          WordLength++;

          //Check to see if the character is white space.
          bool isDelimiter = false;
          const unicode* WhiteSpaceDelimiterCheck = WhiteSpaceDelimiters;
          while(*WhiteSpaceDelimiterCheck)
          {
            if(Character == *WhiteSpaceDelimiterCheck)
            {
              isDelimiter = true;
              break;
            }
            WhiteSpaceDelimiterCheck++;
          }

          //Check to see if the character is word delimiter.
          const unicode* AdditionalWordDelimiterCheck =
            AdditionalWordDelimiters;
          while(*AdditionalWordDelimiterCheck && !isDelimiter)
          {
            if(Character == *AdditionalWordDelimiterCheck)
            {
              isDelimiter = true;
              break;
            }
            AdditionalWordDelimiterCheck++;
          }

          if(isDelimiter)
          {
            //The beginning of the word has been found.
            isSearchingWord = false;

            /*Decrement the UTF8 string pointer so that it points to the
            beginning of the word. The exception is if the word is one
            character in which case there is no need for a decrement.*/
            if(WordLength > 1)
              UTF8String = ptrPreviousCharacter;

            Word.ByteLength = (count)(UTF8String - Word.Position);
          }

          //Otherwise keep decoding characters from the word.
        }
      }

      Word.UpdateString();
      return Word;
    }

    ///Stores delimiters used for parsing.
    struct Delimiters
    {
      static const unicode None[1];
      static const unicode WhiteSpace[5];
      static const unicode TagEntry[2];
      static const unicode TagExit[2];
      static const unicode TagName[5];
      static const unicode TagAttributeName[4];
      static const unicode TagAttributeValue[4];
    };

    ///Represents a parsing error.
    struct Error
    {
      typedef count Category;

      ///Represents a type of parsing error.
      struct Categories
      {
        static const Category None = 0;
        static const Category EmptyDocument = 1;
        static const Category UnmatchedBracket = 2;
        static const Category UnexpectedTagName = 3;
        static const Category UnexpectedCharacter = 4;
        static const Category UninterpretableElement = 5;
        static const Category UnmatchedTagName = 6;
      };

      ///Type of error.
      Category Type;

      ///Pointer to beginning of the token.
      const ascii* Position;

      ///Pointer to beginning of markup.
      const ascii* Original;

      ///Index of position in original after UpdateIndex() is called.
      count Index;

      ///Default constructor produces object with no error.
      Error() : Type(Categories::None), Position(0), Original(0), Index(0) {}

      ///Constructor taking an error category and position string.
      Error(Category Type, const ascii* Position) :
        Type(Type), Position(Position), Original(0), Index(0)
      {
      }

      /**Returns a description of the error and its probable location.
      \code
      *  String s;
      *  s >> "<test foo=\"2\">";
      *  s >> "  <subtest bar='2'>";
      *  s >> "    <thisisaproblem ~!@#$%^&*()_+";
      *  s >> "  </subtest>";
      *  s >> "</test>";
      *  c >> s;
      *  c >> "---------------------------------";
      *  xml::Document d;
      *  xml::Parser::Error e = d.ParseDocument(s);
      *  if(e)
      *    c >> e.GetDescription();
      *  else
      *    c >> "ERROR: There should have been a problem reported reading XML.";
      \endcode
      */
      String GetDescription(void)
      {
        switch(Type)
        {
          case Categories::None:
            return "";
          case Categories::EmptyDocument:
            return "The document appears to empty.";
          case Categories::UnmatchedBracket:
            c += "There is an unbalanced bracket.";
            break;
          case Categories::UnexpectedTagName:
            c += "There was an unexpected tag name.";
            break;
          case Categories::UnexpectedCharacter:
            c += "There was an unexpected character.";
            break;
          case Categories::UninterpretableElement:
            c += "There was an uninterpretable element.";
            break;
          case Categories::UnmatchedTagName:
            c += "There was an unbalanced tag name.";
            break;
        }

        //Find the end of the string.
        const ascii* MarkupEnd = &Original[String::LengthOf(Original) + 1];

        //Find 20 characters before the start of the error.
        const ascii* OriginalCopy = Original;
        const ascii* LineBegin = Original;
        const ascii* HeaderStart = 0;
        count CurrentIndex = 0;
        count CurrentLine = 1;

        while(CurrentIndex < Index)
        {
          //Save this position.
          if(CurrentIndex == Index - 20)
            HeaderStart = OriginalCopy;

	  const byte* OriginalCopyCast = (const byte*)OriginalCopy;
          unicode Value = String::Decode(OriginalCopyCast,
            (const byte*)MarkupEnd);
          OriginalCopy = (const ascii*)OriginalCopyCast;
          if(Value == (unicode)*String::Newline)
          {
            CurrentLine++;
            LineBegin = OriginalCopy;
          }
          CurrentIndex++;
        }

        //Start on the same line as the error.
        count SpacesToUse = 20;
        OriginalCopy = HeaderStart;
        if(LineBegin > OriginalCopy)
        {
          SpacesToUse = 20 - (count)(LineBegin - OriginalCopy);
          OriginalCopy = LineBegin;
        }

        //Copy 40 characters of the original XML string.
        String ErrorLocator;

        for(count i = 0; i < 40; i++)
        {
	  const byte* OriginalCopyCast = (const byte*)OriginalCopy;
          unicode Value = String::Decode(OriginalCopyCast,
            (const byte*)MarkupEnd);
          OriginalCopy = (const ascii*)OriginalCopyCast;
          if(!Value)
            break;
          ErrorLocator.Append(Value);
        }

        //Add a pointer to where the error is in the string.
        ErrorLocator.Replace("\n", " ");
        ErrorLocator.Append("\n");
        for(count i = 0; i < SpacesToUse; i++)
          ErrorLocator.Append(" ");
        ErrorLocator.Append("^");
        String LineNumber = "Starting at line ";
        LineNumber << CurrentLine << ":\n";
        ErrorLocator.Prepend(LineNumber);

        return ErrorLocator;
      }

      ///Given the original string and position string finds the position index.
      void UpdateIndex(const ascii* MarkupEnd)
      {
        Index = 0;
        if(Original != 0 && Position != 0)
        {
          const ascii* OriginalCopy = Original;
          while(OriginalCopy < Position)
          {
	    const byte* OriginalCopyCast = (const byte*)OriginalCopy;
            String::Decode(OriginalCopyCast,
              (const byte*)MarkupEnd);
            OriginalCopy = (const ascii*)OriginalCopyCast;
            Index++;
          }
        }
      }

      ///Casts object into a boolean with true meaning it contains an error.
      operator bool (void) const
      {
        return Type != Categories::None;
      }
    };
  };

  /*An object can either be an element or a string of text. It is necessary
  to store a list of generic objects so that something like this:
  <foo>hello<foo2></foo2>there</foo>
  can accurately be represented.*/

  class Element;
  class Text;
  class Document;

  ///Represents some kind of content within an element.
  class Object
  {
  public:
    virtual Element* IsElement(void) {return 0;}
    virtual Text* IsText(void) {return 0;}
    virtual ~Object() {}
  };

  ///Represents string content in an element.
  class Text : public Object, public String
  {
  public:
    friend class Document;

    Text() {}

    Text(const String& NewString) : String(NewString) {}

    Text* IsText(void)
    {
      return this;
    }

    virtual ~Text()
    {
    }
  };

  ///Represents an XML tag within an element and possibly between text.
  class Element : public Object
  {
  public:
    friend class Document;

    ///Stores an XML attribute by its name and value.
    struct Attribute
    {
      String Name;
      String Value;

      Attribute& operator= (const Attribute& Other)
      {
        Name = Other.Name;
        Value = Other.Value;
        return *this;
      }
    };
  protected:
    ///Stores the name of the element tag.
    String Name;

    ///Stores a list of the element tag's attributes.
    List<Attribute> Attributes;

    ///Stores a list of objects containing text and subelements.
    List<Object*> Objects;

  public:
    Element* IsElement(void) {return this;}

    ///Default constructor.
    Element() {}

    ///Constructor specifying the tag name of the element.
    Element(const String& Name)
    {
      Element::Name = Name;
    }

    ///Returns a reference to the list of this element's tag name.
    const String& GetName(void) {return Name;}

    ///Sets the tag name of this element.
    void SetName(const String& NewName)
    {
      Name = NewName;
    }

    ///Returns a reference to the list of this element's tag attributes.
    const List<Attribute>& GetAttributes(void) {return Attributes;}

    ///Adds an attribute to the attribute list.
    void AddAttribute(const Attribute& NewAttribute)
    {
      Attributes.Add() = NewAttribute;
    }

    ///Adds an attribute from a string pair.
    void AddAttribute(const String& Name, const String& Value)
    {
      Attribute a;
      a.Name = Name;
      a.Value = Value;
      Attributes.Add() = a;
    }

    /**Gets the value of a particular attribute. If the attribute can not be
    located, this method will return an empty string.*/
    String GetAttributeValue(const ascii* Attribute)
    {
      for(count i = 0; i < Attributes.n(); i++)
      {
        if(Attributes[i].Name == Attribute)
          return Attributes[i].Value;
      }
      return "";
    }

    /**Removes an attribute by name from the attribute list. Note that it will
    remove all instances of the attribute (however there should only be
    one).*/
    void RemoveAttribute(const String& AttributeName)
    {
      for(count i = 0; i < Attributes.n(); i++)
      {
        if(Attributes[i].Name == AttributeName)
        {
          Attributes.Remove(i);
          i--;
        }
      }
    }

    ///Returns a reference to the list of this element's objects.
    const List<Object*>& GetObjects(void) {return Objects;}

    ///Adds a pointer to an object in the object list.
    void AddObject(Object* NewObject, bool AddAtBeginning = false)
    {
      if(AddAtBeginning)
        Objects.Prepend(NewObject);
      else
        Objects.Append(NewObject);
    }

    ///Adds a pointer to an object in the object list.
    void AddElementInOrder(Element* NewElement, const String* Order)
    {
      String& NewElementName = NewElement->Name;
      count NewElementOrder = -1;
      count OrderNumber = 0;

      const String* ptrOrder = Order;

      while(*ptrOrder != "")
      {
        if(*ptrOrder == NewElementName)
          NewElementOrder = OrderNumber;
        ptrOrder++;
        OrderNumber++;
      }

      if(NewElementOrder == -1)
      {
        /*Could not find element in the ordering scheme so just add to the end
        and exit.*/
        AddObject(NewElement);
        return;
      }

      count ElementToInsertAfter = -1;
      for(count i = Objects.n() - 1; i >= 0; i--)
      {
        if(Element* e = Objects[i]->IsElement())
        {
          //Get the order index of the element in question.
          count CurrentOrder = -1;
          for(count j = 0; j < OrderNumber; j++)
          {
            if(Order[j] == e->Name)
            {
              CurrentOrder = j;
              break;
            }
          }

          if(CurrentOrder != -1 && CurrentOrder <= NewElementOrder)
          {
            /*Found either the same kind of element or the last element that
            would appear before this kind of element.*/
            ElementToInsertAfter = i;
            break;
          }
        }
      }

      if(ElementToInsertAfter != -1)
      {
        /*Insert the element after either the last element of the same kind or
        the last element whose order comes before an element of this kind.*/
        Objects.InsertAfter(NewElement,ElementToInsertAfter);
      }
      else if(NewElementOrder == 0)
      {
        /*This happens when the new element is ordered first and thus has no
        other element to go after.*/
        AddObject(NewElement, true);
      }
      else
      {
        //Unknown situation -- just add the object to the end in this case.
        AddObject(NewElement, false);
      }
    }

    ///Removes all children, both text and elements.
    void RemoveAllObjects(void)
    {
      Objects.RemoveAndDeleteAll();
    }

    ///Removes all elements by a particular tag name.
    void RemoveElementType(const String& ElementTagName)
    {
      for(count i = 0; i < Objects.n(); i++)
      {
        if(Element* e = Objects[i]->IsElement())
        {
          if(e->Name == ElementTagName)
          {
            Objects.RemoveAndDelete(i);
            i--;
          }
        }
      }
    }

    /**Removes an element by its searching for its tag name and id attribute.
    If there are more than one by the same id, then they are all removed.*/
    void RemoveElementByID(const String& ElementTagName, const String& ID)
    {
      for(count i = 0; i < Objects.n(); i++)
      {
        if(Element* e = Objects[i]->IsElement())
        {
          if(e->Name == ElementTagName && e->GetAttributeValue("id") == ID)
          {
            Objects.RemoveAndDelete(i);
            i--;
          }
        }
      }
    }

    //Gets the ith child of a particular tag name.
    Element* GetChildByTagName(const String& tag, count index = 0)
    {
      count Count = 0;
      for(count i = 0; i < Objects.n(); i++)
      {
        if(Element* e = Objects[i]->IsElement())
        {
          if(e->GetName() == tag)
          {
            if(Count == index)
              return e;
            Count++;
          }
        }
      }
      return 0;
    }

    ///Gets the ith child of a particular type.
    template<class ChildType>
    ChildType* GetChildOfType(count index = 0)
    {
      count Count = 0;
      for(count i = 0; i < Objects.n(); i++)
      {
        if(ChildType* c = dynamic_cast<ChildType*>(Objects[i]->IsElement()))
        {
          if(Count == index)
            return c;
          Count++;
        }
      }
      return 0;
    }

    //Gets the ith child of a particular tag name.
    count CountChildrenByTagName(const String& tag)
    {
      count Count = 0;
      for(count i = 0; i < Objects.n(); i++)
      {
        if(Element* e = Objects[i]->IsElement())
        {
          if(e->GetName() == tag)
            Count++;
        }
      }
      return Count;
    }

    ///Determines the number of children in an element of a particular type.
    template<class ChildType>
    count CountChildrenOfType(void)
    {
      count Count = 0;
      for(count i = 0; i < Objects.n(); i++)
      {
        if(dynamic_cast<ChildType*>(Objects[i]->IsElement()))
          Count++;
      }
      return Count;
    }

    ///Virtual destructor.
    virtual ~Element()
    {
      Objects.RemoveAndDeleteAll();
    }

  protected:
    /**Overloaded method for creating virtual elements from an arbitrary name.
    You'll want to do something like:
    /code
    if(TagName == "foo")
      return new foo; //'foo' is a derived Element.
    else if(TagName == "blah")
      return new blah; //'blah' is another derived Element.
    else
      return 0; //Indicates that a generic Element will be created.
    /endcode*/
    virtual Element* CreateChild(const String& TagName)
    {
      TagName.Merge(); //Stop unreferenced formal parameter warning.
      return 0;
    }

    /**Used by virtual elements to cache data in a more efficient manner. This
    is called automatically immediately after parsing. You can use this to
    store cached copies of any data so that the structure of the XML document
    can be used as a way to facilitate organization without having to parse
    strings of text every time you need access to something.*/
    virtual bool Interpret(void)
    {
      bool Success = true;
      for(count i = 0; i < Objects.n(); i++)
      {
        if(Element* e = dynamic_cast<Element*>(Objects[i]))
        {
          if(!e->Interpret())
            Success = false;
        }
      }
      return Success;
    }

    /**Translates cached data in virtual elements back into the XML structure.
    This method is automatically called before XML data is saved to file for
    example.*/
    virtual void Translate(void)
    {
      for(count i = 0; i < Objects.n(); i++)
      {
        if(Element* e = dynamic_cast<Element*>(Objects[i]))
          e->Translate();
      }
    }

    Parser::Error Parse(const ascii*& Markup, const ascii* MarkupEnd)
    {
      //Local variables to use for parsing.
      Parser::Token t;

      //Remember the original location of the markup start.
      const ascii* m = Markup;

      //Entering tag.
      t = Parser::ParseNextWord(Markup, MarkupEnd,
        Parser::Delimiters::WhiteSpace, Parser::Delimiters::TagEntry);
      if(t.Text != "<")
        return Parser::Error(Parser::Error::Categories::EmptyDocument, m);

      //Parse tag name.
      t = Parser::ParseNextWord(Markup, MarkupEnd,
        Parser::Delimiters::WhiteSpace, Parser::Delimiters::TagName);
      if(t.Text == "" || t.Text.Contains(">") || t.Text.Contains("<"))
        return Parser::Error(Parser::Error::Categories::UnexpectedCharacter, m);
      Name = t.Text;

      //Parse the attributes.
      bool isParsingAttributes = true;
      while(isParsingAttributes)
      {
        t = Parser::ParseNextWord(Markup, MarkupEnd,
          Parser::Delimiters::WhiteSpace, Parser::Delimiters::TagAttributeName);

        if(t.Text == "/")
        {
          //Element is in the self-closing notation, i.e. <br/>.

          //Look for the exit character.
          t = Parser::ParseNextWord(Markup, MarkupEnd,
            Parser::Delimiters::WhiteSpace, Parser::Delimiters::TagExit);
          if(t.Text != ">")
            return Parser::Error(Parser::Error::Categories::UnexpectedCharacter,
              m);

          //Element is finished parsing, so return.
          return Parser::Error();
        }
        else if(t.Text == ">")
        {
          //There are no more attributes.
          isParsingAttributes = false;
        }
        else if(t.Text == "=")
        {
          return Parser::Error(Parser::Error::Categories::UnexpectedCharacter,
            m);
        }
        else
        {
          //Parsed attribute name.
          Attributes.Add();
          Attributes.z().Name = t.Text;

          //Look for the equal sign.
          t = Parser::ParseNextWord(Markup, MarkupEnd,
            Parser::Delimiters::WhiteSpace,
            Parser::Delimiters::TagAttributeName);
          if(t.Text != "=")
            return Parser::Error(Parser::Error::Categories::UnexpectedCharacter,
              m);

          //Look for the beginning quotation mark.
          t = Parser::ParseNextWord(Markup, MarkupEnd,
            Parser::Delimiters::WhiteSpace,
            Parser::Delimiters::TagAttributeValue);
          if(t.Text != "\"" && t.Text != "'")
            return Parser::Error(Parser::Error::Categories::UnexpectedCharacter,
              m);

          //Parse the attribute text.
          t = Parser::ParseNextWord(Markup, MarkupEnd, Parser::Delimiters::None,
            Parser::Delimiters::TagAttributeValue);

          if(t.Text != "\"" && t.Text != "'")
          {
            //Attribute value is a non-empty string.
            Attributes.z().Value = t.Text;

            //Look for closing quotation mark.
            t = Parser::ParseNextWord(Markup, MarkupEnd,
              Parser::Delimiters::WhiteSpace,
              Parser::Delimiters::TagAttributeValue);
            if(t.Text != "\"" && t.Text != "'")
              return Parser::Error(
                Parser::Error::Categories::UnexpectedCharacter, m);
          }
        }
      }

      //Parse the element's objects (text and elements).
      bool isParsingObjects = true;
      while(isParsingObjects)
      {
        //Save the parse pointer in case it is a new tag.
        const ascii* TagBeginning = Markup;

        t = Parser::ParseNextWord(Markup, MarkupEnd, Parser::Delimiters::None,
          Parser::Delimiters::TagEntry);
        if(t.Text == "<") //Making new element or closing this one.
        {
          t = Parser::ParseNextWord(Markup, MarkupEnd,
            Parser::Delimiters::WhiteSpace, Parser::Delimiters::TagName);

          if(t.Text == "!")
          {
            //Inside of a comment. Skip to the '>' character.
            t = Parser::ParseNextWord(Markup, MarkupEnd,
              Parser::Delimiters::None, Parser::Delimiters::TagExit);
            t = Parser::ParseNextWord(Markup, MarkupEnd,
              Parser::Delimiters::None, Parser::Delimiters::TagExit);
            if(t.Text != ">")
              return Parser::Error(
                Parser::Error::Categories::UnexpectedCharacter, m);
          }
          else if(t.Text == "/")
          {
            //Closing this element. Make sure tag matches.
            t = Parser::ParseNextWord(Markup, MarkupEnd,
              Parser::Delimiters::WhiteSpace, Parser::Delimiters::TagName);
            if(t.Text != Name)
              return Parser::Error(Parser::Error::Categories::UnmatchedTagName,
                m);

            //Look for '>'
            t = Parser::ParseNextWord(Markup, MarkupEnd,
              Parser::Delimiters::WhiteSpace, Parser::Delimiters::TagExit);
            if(t.Text != ">")
              return Parser::Error(
                Parser::Error::Categories::UnexpectedCharacter, m);

            isParsingObjects = false;
          }
          else //New child element.
          {
            //Create new child element using virtual overloaded method.
            Element* e = CreateChild(t.Text);
            if(!e)
              e = new Element; //Default to generic element.

            //Add the object (with its children) to the objects list.
            Objects.Add() = e;

            //Reverse the markup pointer to the beginning of the tag.
            Markup = TagBeginning;

            //Parse the child element.
            Parser::Error Error = e->Parse(Markup, MarkupEnd);

            /*If there was an error then this causes a cascading failure and
            the entire parse aborts.*/
            if(Error)
              return Error;

            /*We will let the root element trigger Interpret() after the
            document has been completely parsed. This is done because the
            Interpret() method is itself recursive.*/
            //e->Interpret();
          }
        }
        else
        {
          //Making new text object.
          Text* NewText = new Text;
          *NewText &= t.Text;
          Objects.Add() = NewText;
        }
      }
      return Parser::Error();
    }

  public:
    ///Appends this element tag, contents, and closing tag to a string.
    void AppendToString(String& XMLOutput);

    ///Returns all of this element's text as a single string.
    String GetAllSubTextAsString(void)
    {
      String s;
      for(count i = 0; i < Objects.n(); i++)
      {
        Text* t = Objects[i]->IsText();
        if(t)
          s &= *(String*)t;
      }
      return s;
    }
  };

  /**XML DOM which reads XML from a string. Note that this is a
  no-frills XML parser with no validation and several limitations.

  It currently does not accept CDATA, and comments are not retained. Also,
  comments containing XML markup and comments before the root node will cause
  the parser to fail. Special characters are also not properly substituted
  either.

  Nevertheless, the parser can read most XHTML documents with the above
  limitations in mind. Depending on your needs, you may want to employ a
  pre-parse filter on the incoming XML.*/
  class Document
  {
  public:
    Element* Root;

    Document() : Root(0) {}
    virtual ~Document() {delete Root;}

    virtual Element* CreateRootElement(String& RootTagName)
    {
      RootTagName.Merge(); //Stop unreferenced formal parameter warning.
      return 0;
    }
  protected:
    Parser::Error ParseHeader(const ascii*& Markup, const ascii* MarkupEnd,
      String& RootTagName)
    {
      RootTagName.Merge(); //Stop unreferenced formal parameter warning.

      //Local variables to use for parsing.
      Parser::Token t;

      //Remember the original location of the markup start.
      const ascii* m = Markup;

      bool isParsingHeader = true;
      while(isParsingHeader)
      {
        //Save the position of the tag beginning for later reference.
        const ascii* TagBeginning = Markup;

        /*At the document level we look for the XML header and the DOCTYPE
        before attempting to parse the root element.*/
        t = Parser::ParseNextWord(Markup, MarkupEnd,
          Parser::Delimiters::WhiteSpace, Parser::Delimiters::TagEntry);

        //Look inside the tag.
        if(t.Text == "<")
        {
          t = Parser::ParseNextWord(Markup, MarkupEnd,
            Parser::Delimiters::WhiteSpace, Parser::Delimiters::TagName);

          if(t.Text == "?")
          {
            /*Header typically looks something like this:
            <?xml version="1.0" encoding="UTF-8"?>
            Ignoring for now.*/
            while(t.Text != ">")
            {
              t = Parser::ParseNextWord(Markup, MarkupEnd,
                Parser::Delimiters::WhiteSpace, Parser::Delimiters::TagExit);

              if(t.Text == "")
                return Parser::Error(
                  Parser::Error::Categories::UnmatchedBracket, m);
            }
          }
          else if(t.Text == "!")
          {
            t = Parser::ParseNextWord(Markup, MarkupEnd,
              Parser::Delimiters::WhiteSpace, Parser::Delimiters::TagName);
            if(t.Text == "DOCTYPE")
            {
              /*Skip through the DOCTYPE definitions.*/
              while(t.Text != ">")
              {
                t = Parser::ParseNextWord(Markup, MarkupEnd,
                  Parser::Delimiters::WhiteSpace, Parser::Delimiters::TagExit);

                if(t.Text == "")
                  return Parser::Error(
                    Parser::Error::Categories::UnmatchedBracket, m);
              }
            }
            else
            {
              //Unexpected tag name. Parser failed.
              return Parser::Error(
                Parser::Error::Categories::UnexpectedTagName, m);
            }
          }
          else
          {
            //Now we are inside a tag.
            Markup = TagBeginning;
            isParsingHeader = false;
          }
        }
        else
        {
          //Presumably an empty document. Parse failed.
          return Parser::Error(Parser::Error::Categories::EmptyDocument, m);
        }
      }

      return Parser::Error();
    }

    /**Method called before writing the root node to the output stream. Should
    specify the encoding and DOCTYPE if necessary.*/
    virtual void WriteHeader(String& XMLOutput)
    {
      XMLOutput.Merge(); //Stop unreferenced formal parameter warning.
    }
  public:

    /**Parses a string as an XML document and returns any error associated with
    the parsing operation. Use the Parser::Error::GetDescription method on the
    error to retrieve the problem encountered.
    \code
    *  String s;
    *  s >> "<test foo=\"2\">";
    *  s >> "  <subtest bar='2'>";
    *  s >> "    some text";
    *  s >> "  </subtest>";
    *  s >> "</test>";
    *  c >> s;
    *  c >> "---------------------------------";
    *  xml::Document d;
    *  xml::Parser::Error e = d.ParseDocument(s);
    *  if(e)
    *  {
    *    c >> "ERROR: There should not have been a problem.";
    *    c >> e.GetDescription();
    *  }
    *  else
    *  {
    *    c >> "Writing out from DOM-tree...";
    *    s.Clear();
    *    d.WriteToString(s);
    *    c >> s;
    *  }
    \endcode
    */
    Parser::Error ParseDocument(const String& MarkupDocument)
    {
      //Get a pointer to the markup string.
      const ascii* Markup = MarkupDocument.Merge();
      const ascii* MarkupEnd = Markup + MarkupDocument.n() + 1;

      String RootTagName;
      Parser::Error Error = ParseHeader(Markup, MarkupEnd, RootTagName);
      if(Error)
      {
        Error.Original = MarkupDocument.Merge();
        Error.UpdateIndex(MarkupEnd);
        return Error;
      }

      //Delete root note if it already exists.
      delete Root;

      //Create the root node.
      Root = CreateRootElement(RootTagName);
      if(!Root)
        Root = new Element;

      //Parse the document tree.
      Error = Root->Parse(Markup, MarkupEnd);
      if(Error)
      {
        Error.Original = MarkupDocument.Merge();
        Error.UpdateIndex(MarkupEnd);
        delete Root;
        Root = 0;
        return Error;
      }

      //Interpret the entire document.
      Root->Interpret();

      return Parser::Error();
    }

    void WriteToString(String& XMLOutput)
    {
      WriteHeader(XMLOutput);
      Root->AppendToString(XMLOutput);
    }

    void WriteToFile(String Filename)
    {
      String XMLOutput;
      WriteToString(XMLOutput);
      File::Write(Filename, XMLOutput);
    }
  };

  ///Represents a nameable property containing some type of data.
  template <class T>
  class Property
  {
    T Data;
    prim::String Name;
  public:
    Property(const prim::String& InitName) : Name(InitName){}
    operator T& (void) {return Data;}
    T& operator = (const T& In)
    {
      Data = In;
      return Data;
    }

    T& operator = (const prim::String& In)
    {
      Data = (T)In;
      return Data;
    }

    prim::String GetName(void)
    {
      return Name;
    }

    inline bool SetFrom(Element* e)
    {
      if(e && e->GetName() == Name)
      {
        Data = (T)e->GetAllSubTextAsString();
        return true;
      }
      else return false;
    }

    inline bool SetFrom(Object* o)
    {
      return SetFrom(o->IsElement());
    }
  };
};}

#ifdef PRIM_COMPILE_INLINE
namespace prim
{
  const unicode XML::Parser::Delimiters::None[1] = {0};
  const unicode XML::Parser::Delimiters::WhiteSpace[5] = {32, 9, 10, 13, 0};
  const unicode XML::Parser::Delimiters::TagEntry[2] = {'<', 0};
  const unicode XML::Parser::Delimiters::TagExit[2] = {'>', 0};
  const unicode XML::Parser::Delimiters::TagName[5] =
    {'!', '?', '/', '>', 0};
  const unicode XML::Parser::Delimiters::TagAttributeName[4] =
    {'=','>','/', 0};
  const unicode XML::Parser::Delimiters::TagAttributeValue[4] =
    {'"', '\x27', '>', 0};

  //This needs to be outside due to a cyclic dependency.
  void XML::Element::AppendToString(String& XMLOutput)
  {
    /*Pretty-printing will enable automatic indentation, but always adds
    whitespace. This ought to be moved to where the XML document can control the
    feature.*/
    //const bool PrettyPrint = false;
    static count TabLevel = 0; //Really not ideal because this is global.
    String TabString;
    /*
    if(PrettyPrint)
    {
      for(count i = 0; i < TabLevel; i++)
        TabString &= "  ";
      XMLOutput += TabString;
    }
    */

    /*First give the virtual method a chance to update the XML data
    structure.*/
    Translate();

    XMLOutput &= "<";
    XMLOutput &= Name;

    //Write the attributes within the tag.
    for(count i = 0; i < Attributes.n(); i++)
    {
      XMLOutput -= Attributes[i].Name;
      XMLOutput &= "=\"";
      XMLOutput &= Attributes[i].Value;
      XMLOutput &= "\"";
    }

    //Write the objects to the element.
    if(Objects.n() > 0)
    {
      XMLOutput &= ">";
      bool ContainsTags = false;
      for(count i = 0; i < Objects.n(); i++)
      {
        Object* e = Objects[i];
        Text* t = e->IsText();
        Element* el = e->IsElement();
        if(t)
          XMLOutput &= *(String*)t;
        else
        {
          ContainsTags = true;
          TabLevel++;
          el->AppendToString(XMLOutput);
          TabLevel--;
        }
      }
      if(ContainsTags/* && PrettyPrint*/)
        XMLOutput += TabString;
      XMLOutput &= "</";
      XMLOutput &= Name;
      XMLOutput &= ">";
    }
    else
    {
      //Use self-closing syntax: <br/>
      XMLOutput &= "/>";
    }
  }
}
#endif
#endif

#endif

//............................................................................//

#ifdef PRIM_WITH_FFT //Depends on Thread (optional)

#ifndef PRIM_FFT_H
#define PRIM_FFT_H

/*Module Configuration
================================================================================

To enable multithread computation simply include Modules/Thread.h before FFT.h.

================================================================================
End Module Configuration*/

namespace prim { namespace dsp
{
  ///Calculates Cos(A / B * Pi).
  template<typename floatT>
  floatT CosRecursive(floatT A, floatT B, count Iterations = 16)
  {
    floatT Angle = A / B * 3.1415926535897932384626433832795029L;
    floatT Angle_2 = Angle * Angle;
    floatT Value = 1.0L;
    for(count M = Iterations * 2 - 1; M > 0; M -= 2)
      Value = 1.0L - Angle_2 * Value / (floatT)(M * (M + 1));
    return Value;
  }

  ///Calculates Sin(A / B * Pi).
  template<typename floatT>
  floatT SinRecursive(floatT A, floatT B, count Iterations = 16)
  {
    floatT Angle = A / B * 3.1415926535897932384626433832795029L;
    floatT Angle_2 = Angle * Angle;
    floatT Value = 1.0L;
    for(count M = Iterations * 2; M > 0; M -= 2)
      Value = 1.0L - Angle_2 * Value / (floatT)(M * (M + 1));
    return Angle * Value;
  }

  ///Reverses the bitwise index of the complex array (i.e. 10100 <--> 00101).
  template <typename T>
  void BitReverse(Array<Complex<T> >& Data)
  {
    count n, nn,  m, j, i;

    n = Data.n() * 2;
    nn = n >> 1;
    j = 1;
    for(i = 1; i < n; i += 2)
    {
      if(j > i)
        Swap(Data[(j - 1) >> 1], Data[(i - 1) >> 1]);

      m = nn;

      while(m >= 2 && j > m)
      {
        j -= m;
        m >>= 1;
      }

      j += m;
    }
  }

  ///Normalizes the data to correct for magnitude scaling by the FFT.
  template <typename T>
  void Normalize(Array<Complex<T> >& Data)
  {
    T Scale = (T)1.0 / (T)Data.n();
    for(count i = 0; i < Data.n(); i++)
      Data[i] *= Scale;
  }

  ///Generates a complex array of a given size consisting of noise from [-1, 1).
  template <typename T>
  void GenerateWhiteNoise(Array<Complex<T> >& Destination, count FFTSize)
  {
    Random r;
    Destination.n(FFTSize);
    for(count i = 0; i < FFTSize; i++)
      Destination[i] = Complex<T>(r.Between(-1.0, 1.0), r.Between(-1.0, 1.0));
  }

  /**Generates a reusable cosine lookup table for a particular FFT size. The
  typename InternalT controls the float type of intermediate calculations. For
  best results use float80.*/
  template <typename InternalT, typename T>
  void GenerateCosineTable(Array<T>& TableToMake, count FFTSize)
  {
    TableToMake.n((FFTSize / 4) + 1);
    for(count i = 0; i < TableToMake.n(); i++)
      TableToMake[i] = (T)CosRecursive<InternalT>(i * 2, FFTSize, 16);
  }

  ///Calculates the RMS error between two arrays of equal size.
  template <typename T>
  float64 CalculateRMSError(Array<Complex<T> >& Array1,
    Array<Complex<T> >& Array2)
  {
    if(Array1.n() != Array2.n())
      return 0.0;
    float64 Sum = 0.0;
    for(count i = 0; i < Array1.n(); i++)
      Sum += Square((float64)(Array1[i].Mag(Array2[i])));
    return Log2(Sqrt(Sum / (float64)Array1.n()));
  }

#ifdef PRIM_THREAD_H
  ///Internal hook for attaching butterflys to threads.
  template <count FFTSize, count N, count Sign, typename T>
  class ButterflyThreadHook : public Thread
  {
    Complex<T>* Data;
    T* CosTable;
    count MaxThreadDepth;
    count ThreadDepth;

    public:
    ButterflyThreadHook(Complex<T>* Data, T* CosTable, count MaxThreadDepth,
      count ThreadDepth) : Data(Data), CosTable(CosTable),
      MaxThreadDepth(MaxThreadDepth), ThreadDepth(ThreadDepth) {}

    void Run(void);
    virtual ~ButterflyThreadHook() {}
  };
#endif

  /**Represents a single type of butterfly. The template parameters, which are
  determined at compile-time allow the butterfly loop to be unrolled by a
  compiler with speed optimizations turned on.*/
  template <count FFTSize, count N, count Sign, typename T>
  class Butterfly
  {
    Butterfly<FFTSize, N / 2, Sign, T> Next;
  public:
    void Apply(Complex<T>* Data, T* CosTable, count MaxThreadDepth = 3,
      count ThreadDepth = 0)
    {
#ifdef PRIM_THREAD_H
      if(ThreadDepth < MaxThreadDepth)
      {
        Thread* t1 = new ButterflyThreadHook<FFTSize, N / 2, Sign, T>(
          Data, CosTable, MaxThreadDepth, ThreadDepth + 1);
        Thread* t2 = new ButterflyThreadHook<FFTSize, N / 2, Sign, T>(
          Data + (N / 2), CosTable, MaxThreadDepth, ThreadDepth + 1);
        t1->Begin();
        t2->Begin();
        t1->WaitToEnd();
        t2->WaitToEnd();
      }
      else
#endif
      {
        Next.Apply(Data, CosTable, MaxThreadDepth, ThreadDepth + 1);
        Next.Apply(Data + (N / 2), CosTable, MaxThreadDepth, ThreadDepth + 1);
      }

      //Lower power of two better precision, higher power of two better speed.
      const count PrecisionSpeedTradeoff = 16;

      //Initialize butterfly.
      count Index0 = 0, Index1 = 0, i = 0, iHalf = 0, Complement = FFTSize / N;
      Complex<T> Temporary, Angle(1.0, 0.0);
      Complex<T> Wp(CosTable[Complement] - (T)1.0,
                    CosTable[FFTSize / 4 - Complement] * (T)-Sign);

      //Do the first half of the butterfly calculation.
      for(; i < N / 2; i += 2, iHalf++)
      {
        if(iHalf % PrecisionSpeedTradeoff == 0)
        {
          //Update the angle with a fully precise value from the lookup table.
          Angle.x = CosTable[iHalf * Complement];
          Angle.y = CosTable[FFTSize / 4 - iHalf * Complement] * (T)-Sign;
        }
        Index0 = (i >> 1);
        Index1 = ((i + N) >> 1);
        Temporary = Data[Index1] * Angle;
        Data[Index1] = Data[Index0] - Temporary;
        Data[Index0] += Temporary;
        Angle += Angle * Wp;
      }

      /*Do the second half of the butterfly calculation (only difference is
      trig table lookup).*/
      for(; i < N; i += 2, iHalf++)
      {
        if(iHalf % PrecisionSpeedTradeoff == 0)
        {
          //Update the angle with a fully precise value from the lookup table.
          Angle.x = -CosTable[FFTSize / 2 - iHalf * Complement];
          Angle.y = CosTable[iHalf * Complement - FFTSize / 4] * (T)-Sign;
        }
        Index0 = (i >> 1);
        Index1 = ((i + N) >> 1);
        Temporary = Data[Index1] * Angle;
        Data[Index1] = Data[Index0] - Temporary;
        Data[Index0] += Temporary;
        Angle += Angle * Wp;
      }
    }
  };

  ///Template recursion break for the butterfly.
  template <count FFTSize, count Sign, typename T>
  class Butterfly<FFTSize, 1, Sign, T>
  {
  public:
     void Apply(Complex<T>* Data, T* CosTable, count MaxThreadDepth = 3,
      count ThreadDepth = 0) {}
  };

#ifdef PRIM_THREAD_H
  ///Thread entry-point which triggers a particular butterfly to run.
  template <count FFTSize, count N, count Sign, typename T>
  void ButterflyThreadHook<FFTSize, N, Sign, T>::Run(void)
  {
    Butterfly<FFTSize, N, Sign, T> f;
    f.Apply(Data, CosTable, MaxThreadDepth, ThreadDepth);
  }
#endif

  enum FFTDirection
  {
    Forwards = 1,
    Backwards = -1
  };

  /**Calculates a forwards (dsp::Forwards) or backwards (dsp::Backwards) FFT.

  Note that thread depth is a trade-off between the overhead of thread
  management versus the leveraging of multicore environments. The number of
  threads that actually will run will peak at 2^(Depth + 1) - 1. It may be worth
  testing at run-time how various thread depths perform given a particular FFT
  size. In general, small FFTs should have thread depth at 0, and large FFTs on
  a multicore machine may have thread depth up to 3 or 4.

  This FFT implementation has the following advantages and disadvantages:
  <ul>
  <li>Pros
    <ul>
    <li>Compiler-optimizable code. Due to template recursion, a compiler can
    easily unroll loops to create FFT butterflys that spend minimal time in
    for-loop overhead. Note that you must enable full optimization on your
    compiler for this to work.</li>
    <li>Uses (relatively) little memory. While the entire FFT operation is
    performed in memory, its memory consumption is only slightly larger (by an
    eighth) than the footprint of the data itself. The following are the
    memory footprints depending on the float type:
    <ul>
      <li>float32: FFT Size * 9 bytes</li>
      <li>float64: FFT Size * 18 bytes</li>
      <li>float80: FFT Size * 36 bytes (due to 128-bit alignment)</li>
    </ul>
    </li>
    <li>The cosine table which is generated by GenerateCosineTable() is fully
    accurate for 64-bit floats when the internal type for intermediate
    calculations is set to float80.</li>
    <li>Typical precision (largest FFT size to smallest FFT size):
      <ul>
      <li>float32: 20 to 23 bits</li>
      <li>float64: 49 to 53 bits</li>
      <li>float80: 60 to 64 bits</li>
      </ul>
    </li>
    <li>Built-in multithreading. The thread depth may be specified so that the
    initial butterflys each occupy separate threads and distribute themselves
    across multiple cores in a multicore machine.</li>
    <li>Portable and lightweight (only 300 lines of code). Different platforms
    should compile equally well, and there should be little variation in the
    precision or speed of the results.</li>
    <li>Extremely large FFTs (greater than 64 million points) can be calculated.
    The only real limitation is the availability of system memory.</li>
    <li>Consistent with the prim library, using Array&lt;Complex&lt;T&gt;&gt;
    as the argument type, where T can be any float type (even an
    arbitrary-precision floating point class such as MPFR C++ if it were
    available).</li>
    </ul>
  </li>
  <li>Cons
    <ul>
    <li>Only complex 1-D data can be transformed. There are no savings benefits
    for real-to-complex and complex-to-real data. However, in many applications
    it is possible to do two FFTs for the price of one. For example, you can put
    two real signals into the complex real and imaginary parts of the data, take
    the FFT, multiply by the FFT of a real impulse response, then take the
    inverse FFT. The real and imaginary parts correspond to two separate signals
    convolved with the same real impulse response.</li>
    <li>Thread affinity is not managed which leads to possible duplication of
    threads among the same core yielding performance decrease due to thread
    overhead. Also, each butterfly is atomic to a thread which means the final
    large butterflys will not take advantage of multithreading.</li>
    <li>No smart caching of data for large transforms when page file is
    unavoidable. System will essentially grind to halt if physical memory is
    exhausted.</li>
    <li>Though speed is comparable to that of the FFTW benchmark (within a
    factor of two), there is no substitute for a dedicated library such as FFTW.
    On the other hand, prim is released with looser licensing restrictions
    (LGPL instead of GPL).</li>
    </ul>
  </li>
  </ul>
  A complete example (from Examples/FFT.cpp):
\code
#define PRIM_COMPILE_INLINE
#include "../prim.h"

//Uncomment and configure to enable multithreading.
//#include "../Modules/Thread.h"

#include "../Modules/FFT.h"

using namespace prim;
using namespace prim::dsp;

int main(void)
{
  count FFTSize = 1024 * 1024;
  c >> "Generating " << FFTSize << " complex samples of white noise.";

  Array<Complex<float64> > Data, Original;
  Array<float64> CosineTable;
  GenerateWhiteNoise(Data, FFTSize);
  GenerateCosineTable<float80>(CosineTable, FFTSize);
  Original = Data;

  c >> "Calculating forwards and backwards transforms.";
  FFT<Forwards>(Data, CosineTable);
  FFT<Backwards>(Data, CosineTable);
  Normalize(Data);

  c >> "Bits Precision: " << -CalculateRMSError(Data, Original);

  c++;
}
\endcode
  */
  template<count Sign, typename T>
  void FFT(Array<Complex<T> >& Data, Array<T>& CosineTable,
    count ThreadDepth = 3)
  {
    //Create shorthands.
    const count P_0 = 1, P_1 = P_0 * 2, P_2  = P_1  * 2, P_3  = P_2  * 2,
      P_4 = P_3 * 2, P_5 = P_4 * 2, P_6 = P_5 * 2, P_7 = P_6 * 2, P_8 = P_7 * 2,
      P_9  = P_8  * 2, P_10 = P_9  * 2, P_11 = P_10 * 2, P_12 = P_11 * 2,
      P_13 = P_12 * 2, P_14 = P_13 * 2, P_15 = P_14 * 2, P_16 = P_15 * 2,
      P_17 = P_16 * 2, P_18 = P_17 * 2, P_19 = P_18 * 2, P_20 = P_19 * 2,
      P_21 = P_20 * 2, P_22 = P_21 * 2, P_23 = P_22 * 2, P_24 = P_23 * 2,
      P_25 = P_24 * 2, P_26 = P_25 * 2, P_27 = P_26 * 2, P_28 = P_27 * 2,
      P_29 = P_28 * 2, P_30 = P_29 * 2;
    #if 0 && !defined(PRIM_ENVIRONMENT_ILP32)
    const count P_31 = P_30 * 2, P_32 = P_31 * 2,
      P_33 = P_32 * 2, P_34 = P_33 * 2, P_35 = P_34 * 2, P_36 = P_35 * 2,
      P_37 = P_36 * 2, P_38 = P_37 * 2, P_39 = P_38 * 2, P_40 = P_39 * 2;
    #endif
    Array<Complex<T> >& D = Data;
    Array<T>& C = CosineTable;
    count N = D.n();
    count X = ThreadDepth;
    const count S = Sign;

    //If there is no data just return.
    if(N == 0) return;

    //Bit reverse the output.
    BitReverse(D);

    /*Given the FFT size, find the appropriate butterfly to initiate. Note that
    if you know you are not going to be using a particular range of sizes, then
    you can block comment them out to reduce binary size and speed up compile
    times.*/
         if(N==P_0) {Butterfly<P_0,  P_0,  S, T> f; f.Apply(&D.a(), &C.a(), X);}
    else if(N==P_1) {Butterfly<P_1,  P_1,  S, T> f; f.Apply(&D.a(), &C.a(), X);}
    else if(N==P_2) {Butterfly<P_2,  P_2,  S, T> f; f.Apply(&D.a(), &C.a(), X);}
    else if(N==P_3) {Butterfly<P_3,  P_3,  S, T> f; f.Apply(&D.a(), &C.a(), X);}
    else if(N==P_4) {Butterfly<P_4,  P_4,  S, T> f; f.Apply(&D.a(), &C.a(), X);}
    else if(N==P_5) {Butterfly<P_5,  P_5,  S, T> f; f.Apply(&D.a(), &C.a(), X);}
    else if(N==P_6) {Butterfly<P_6,  P_6,  S, T> f; f.Apply(&D.a(), &C.a(), X);}
    else if(N==P_7) {Butterfly<P_7,  P_7,  S, T> f; f.Apply(&D.a(), &C.a(), X);}
    else if(N==P_8) {Butterfly<P_8,  P_8,  S, T> f; f.Apply(&D.a(), &C.a(), X);}
    else if(N==P_9) {Butterfly<P_9,  P_9,  S, T> f; f.Apply(&D.a(), &C.a(), X);}
    else if(N==P_10){Butterfly<P_10, P_10, S, T> f; f.Apply(&D.a(), &C.a(), X);}
    else if(N==P_11){Butterfly<P_11, P_11, S, T> f; f.Apply(&D.a(), &C.a(), X);}
    else if(N==P_12){Butterfly<P_12, P_12, S, T> f; f.Apply(&D.a(), &C.a(), X);}
    else if(N==P_13){Butterfly<P_13, P_13, S, T> f; f.Apply(&D.a(), &C.a(), X);}
    else if(N==P_14){Butterfly<P_14, P_14, S, T> f; f.Apply(&D.a(), &C.a(), X);}
    else if(N==P_15){Butterfly<P_15, P_15, S, T> f; f.Apply(&D.a(), &C.a(), X);}
    else if(N==P_16){Butterfly<P_16, P_16, S, T> f; f.Apply(&D.a(), &C.a(), X);}
    else if(N==P_17){Butterfly<P_17, P_17, S, T> f; f.Apply(&D.a(), &C.a(), X);}
    else if(N==P_18){Butterfly<P_18, P_18, S, T> f; f.Apply(&D.a(), &C.a(), X);}
    else if(N==P_19){Butterfly<P_19, P_19, S, T> f; f.Apply(&D.a(), &C.a(), X);}
    else if(N==P_20){Butterfly<P_20, P_20, S, T> f; f.Apply(&D.a(), &C.a(), X);}
    else if(N==P_21){Butterfly<P_21, P_21, S, T> f; f.Apply(&D.a(), &C.a(), X);}
    else if(N==P_22){Butterfly<P_22, P_22, S, T> f; f.Apply(&D.a(), &C.a(), X);}
    else if(N==P_23){Butterfly<P_23, P_23, S, T> f; f.Apply(&D.a(), &C.a(), X);}
    else if(N==P_24){Butterfly<P_24, P_24, S, T> f; f.Apply(&D.a(), &C.a(), X);}
    else if(N==P_25){Butterfly<P_25, P_25, S, T> f; f.Apply(&D.a(), &C.a(), X);}
    else if(N==P_26){Butterfly<P_26, P_26, S, T> f; f.Apply(&D.a(), &C.a(), X);}
    else if(N==P_27){Butterfly<P_27, P_27, S, T> f; f.Apply(&D.a(), &C.a(), X);}
    else if(N==P_28){Butterfly<P_28, P_28, S, T> f; f.Apply(&D.a(), &C.a(), X);}
    else if(N==P_29){Butterfly<P_29, P_29, S, T> f; f.Apply(&D.a(), &C.a(), X);}
    else if(N==P_30){Butterfly<P_30, P_30, S, T> f; f.Apply(&D.a(), &C.a(), X);}

    /*Note: the following are not possible on most modern day machines due to
    their extreme memory requirements. In general, the amount of memory consumed
    for an FFT is 18x the number of points (16 for the complex data + 2 for the
    compact trig table). Thus, for a 2-billion (2^31) point FFT, you would need
    36 GB of RAM, which would exceed the maximum specs of most workstations.

    Of course, if you just need the FFT to be done and you do not care as much
    about time, then there is a possibility that with a solid-state drive (i.e.
    very low seek times) a large page file would allow the operation to
    eventually complete.*/

    //Enable for FFT sizes > 2^31. See above to enable power constants.
    #if 0 && !defined(PRIM_ENVIRONMENT_ILP32)
    else if(N==P_31){Butterfly<P_31, P_31, S, T> f; f.Apply(&D.a(), &C.a(), X);}
    else if(N==P_32){Butterfly<P_32, P_32, S, T> f; f.Apply(&D.a(), &C.a(), X);}
    else if(N==P_33){Butterfly<P_33, P_33, S, T> f; f.Apply(&D.a(), &C.a(), X);}
    else if(N==P_34){Butterfly<P_34, P_34, S, T> f; f.Apply(&D.a(), &C.a(), X);}
    else if(N==P_35){Butterfly<P_35, P_35, S, T> f; f.Apply(&D.a(), &C.a(), X);}
    else if(N==P_36){Butterfly<P_36, P_36, S, T> f; f.Apply(&D.a(), &C.a(), X);}
    else if(N==P_37){Butterfly<P_37, P_37, S, T> f; f.Apply(&D.a(), &C.a(), X);}
    else if(N==P_38){Butterfly<P_38, P_38, S, T> f; f.Apply(&D.a(), &C.a(), X);}
    else if(N==P_39){Butterfly<P_39, P_39, S, T> f; f.Apply(&D.a(), &C.a(), X);}
    else if(N==P_40){Butterfly<P_40, P_40, S, T> f; f.Apply(&D.a(), &C.a(), X);}
    #endif

    //If unable to do find correct butterfly, undo bit reverse and return.
    else {BitReverse(Data); return;}
  }
}}
#endif

#endif
#ifdef PRIM_WITH_SERIALIZATION //Depends on MD5

#ifndef PRIM_SERIALIZATION_H
#define PRIM_SERIALIZATION_H

/*Module Configuration
================================================================================

Depends on MD5.h for checksum calculation.

================================================================================
End Module Configuration*/

namespace prim
{
  /**Byte array that can read and write various higher-level data types. One
  important thing to note is that data is always stored as the widest type. This
  is to eliminate any confusion over storage sizes on different platforms.
  Effectively this means: (u)int8/16/32/64 as well as the bool type are all
  stored internally as int64, and float32/64 are both stored as float64. String
  data is stored in a Pascal-like format of 64-bit length + byte data. All other
  types use the above primitive types. The first 32 bytes is reserved for a MD5
  checksum of the remaining data in plain-text lowercase hexadecimal format.*/
  class Serial : public Array<byte>
  {
    ///Stores the position of the read head during reading.
    count ReadHead;

    public:

    ///Enumeration of generic serial modes.
    enum Modes
    {
      Reading,
      Writing,
      CheckVersion,
      CheckID
    };

    ///Callback-style interface for objects that require serialization.
    struct Object
    {
      /**Requests the object to read, write, or provide information. VersionOrID
      is used as follows: in Reading mode it contains the version number of the
      string; in CheckVersion mode the method should provide a version (default
      is 0); in CheckID mode the method should provide a unique ID that
      identifies the class; and, in Writing mode it has no purpose.*/
      virtual void Serialize(Serial& s, Serial::Modes Mode,
        count& VersionOrID) = 0;

      ///Virtual destructor
      virtual ~Object() {}
    };

    /**Restores an object from an ID. The method is intended to be overloaded
    in any system that has objects that need to be serialized, and allows the
    system to handle specific memory new operations (possibly with non-default
    constructors, or other logic). Note that the ID refers to the ID assigned
    to the class type in Object::Serialize during the CheckID mode.*/
    virtual Serial::Object* RestoreObject(count ID) {return 0;}

    ///Virtual destructor
    virtual ~Serial() {}

    ///Resets the read head to after the checksum.
    void StartFromBeginning(void) {ReadHead = 32;}

    ///Writes a 64-bit signed integer.
    void Write(int64 Value)
    {
      count WriteHead = n();
      n(WriteHead + sizeof(int64));
      int64 ValueToWrite = Value;
      Endian::ConvertToLittleEndian(ValueToWrite);
      (int64&)ith(WriteHead) = ValueToWrite;
    }

    ///Takes in a uint64, but always writes a 64-bit signed integer.
    void Write(uint64 Value)
    {
      Write((int64)Value);
    }

    ///Takes in an int32, but always writes a 64-bit signed integer.
    void Write(int32 Value)
    {
      Write((int64)Value);
    }

    ///Takes in a uint32, but always writes a 64-bit signed integer.
    void Write(uint32 Value)
    {
      Write((int64)Value);
    }

    ///Takes in an int16, but always writes a 64-bit signed integer.
    void Write(int16 Value)
    {
      Write((int64)Value);
    }

    ///Takes in a uint16, but always writes a 64-bit signed integer.
    void Write(uint16 Value)
    {
      Write((int64)Value);
    }

    ///Takes in an int8, but always writes a 64-bit signed integer.
    void Write(int8 Value)
    {
      Write((int64)Value);
    }

    ///Takes in a uint8, but always writes a 64-bit signed integer.
    void Write(uint8 Value)
    {
      Write((int64)Value);
    }

    /**Writes a bool as a 64-bit integer. The encoded value is -1 for true
    (all bits on) and 0 for false (all bits off).*/
    void Write(bool Value)
    {
      Write(Value ? (int64)-1 : (int64)0);
    }

    ///Writes a number. The encoded value is of float64 type.
    void Write(float64 Value)
    {
      count WriteHead = n();
      n(WriteHead + sizeof(float64));
      float64 ValueToWrite = Value;
      Endian::ConvertToLittleEndian(ValueToWrite);
      (float64&)ith(WriteHead) = ValueToWrite;
    }

    ///Takes in a float32, but always writes a float64.
    void Write(float32 Value)
    {
      Write((float64)Value);
    }

    ///Writes a integer vector to the serial.
    void Write(planar::VectorInt& Value)
    {
      Write(Value.x);
      Write(Value.y);
    }

    ///Writes a number vector to the serial.
    void Write(planar::Vector& Value)
    {
      Write((number)Value.x);
      Write((number)Value.y);
    }

    ///Writes an integer rectangle to the serial.
    void Write(planar::RectangleInt& Value)
    {
      Write(Value.a);
      Write(Value.b);
    }

    ///Writes a rectangle to the serial.
    void Write(planar::Rectangle& Value)
    {
      Write(Value.a);
      Write(Value.b);
    }

    ///Writes a Pascal string (length plus data array) to the serial.
    void Write(String& Value)
    {
      //Writes a string in PASCAL format (length + data)
      Write(Value.n());
      count WriteHead = n();
      n(WriteHead + Value.n());
      Memory::Copy((ascii*)&ith(WriteHead), Value.Merge(), Value.n());
    }

    ///Writes a serial source to the serial.
    void Write(Serial::Object& Value)
    {
      count Version = 0;
      Value.Serialize(*this, CheckVersion, Version);
      Write(Version);
      Value.Serialize(*this, Writing, Version);
    }

    ///Reads a 64-bit signed integer.
    void Read(int64& Value)
    {
      int64 ReadValue = (int64&)ith(ReadHead);
      Endian::ConvertToLittleEndian(ReadValue);
      Value = ReadValue;
      ReadHead += sizeof(int64);
    }

    ///Reads in a uint64 from a 64-bit signed integer.
    void Read(uint64& Value)
    {
      int64 v = 0;
      Read(v);
      Value = (uint64)v;
    }

    ///Reads in an int32 from a 64-bit signed integer.
    void Read(int32& Value)
    {
      int64 v = 0;
      Read(v);
      Value = (int32)v;
    }

    ///Reads in an uint32 from a 64-bit signed integer.
    void Read(uint32& Value)
    {
      int64 v = 0;
      Read(v);
      Value = (uint32)v;
    }

    ///Reads in an int16 from a 64-bit signed integer.
    void Read(int16& Value)
    {
      int64 v = 0;
      Read(v);
      Value = (int16)v;
    }

    ///Reads in an uint16 from a 64-bit signed integer.
    void Read(uint16& Value)
    {
      int64 v = 0;
      Read(v);
      Value = (uint16)v;
    }

    ///Reads in an int8 from a 64-bit signed integer.
    void Read(int8& Value)
    {
      int64 v = 0;
      Read(v);
      Value = (int8)v;
    }

    ///Reads in an uint8 from a 64-bit signed integer.
    void Read(uint8& Value)
    {
      int64 v = 0;
      Read(v);
      Value = (uint8)v;
    }

    ///Reads in a boolean from the serial.
    void Read(bool& Value)
    {
      integer ReadValue = 0;
      Read(ReadValue);
      Value = (bool)ReadValue;
    }

    ///Reads in a number from the serial.
    void Read(float64& Value)
    {
      float64 ReadValue = (float64&)ith(ReadHead);
      Endian::ConvertToLittleEndian(ReadValue);
      Value = (number)ReadValue;
      ReadHead += sizeof(float64);
    }

    ///Reads in a float32 from a float64.
    void Read(float32& Value)
    {
      float64 v = 0;
      Read(v);
      Value = (float32)v;
    }

    ///Reads a integer vector from the serial.
    void Read(planar::VectorInt& Value)
    {
      Read(Value.x);
      Read(Value.y);
    }

    ///Reads a number vector from the serial.
    void Read(planar::Vector& Value)
    {
      Read(Value.x);
      Read(Value.y);
    }

    ///Reads an integer rectangle from the serial.
    void Read(planar::RectangleInt& Value)
    {
      Read(Value.a);
      Read(Value.b);
    }

    ///Reads a rectangle from the serial.
    void Read(planar::Rectangle& Value)
    {
      Read(Value.a);
      Read(Value.b);
    }

    ///Reads in a string from the serial.
    void Read(String& Value)
    {
      integer NumberOfCharacters = 0;
      Read(NumberOfCharacters);
      Value.Clear();
      Value.Append(&ith(ReadHead), (count)NumberOfCharacters);
      ReadHead += (count)NumberOfCharacters;
    }

    ///Reads in a serial source from the serial.
    void Read(Serial::Object& Value)
    {
      //Reads the serial source by checking version and then reading the data.
      count Version = 0;
      Read(Version);
      Value.Serialize(*this, Reading, Version);
    }

    ///Writes a list of items to the serial.
    template <class T>
    void Write(List<T>& ListOfItems)
    {
      Write(ListOfItems.n());
      for(count i = 0; i < ListOfItems.n(); i++)
        Write(ListOfItems[i]);
    }

    ///Reads a list of items from the serial.
    template <class T>
    void Read(List<T>& ListOfItems)
    {
      count NumberOfItems = 0;
      Read(NumberOfItems);
      ListOfItems.RemoveAll();
      for(count i = 0; i < NumberOfItems; i++)
        Read(ListOfItems.Add());
    }

    ///Writes an array of items to the serial.
    template <class T>
    void Write(Array<T>& ArrayOfItems)
    {
      Write(ArrayOfItems.n());
      for(count i = 0; i < ArrayOfItems.n(); i++)
        Write(ArrayOfItems[i]);
    }

    ///Reads an array of items from the serial.
    template <class T>
    void Read(Array<T>& ArrayOfItems)
    {
      count NumberOfItems = 0;
      Read(NumberOfItems);
      ArrayOfItems.Clear();
      for(count i = 0; i < NumberOfItems; i++)
        Read(ArrayOfItems.Add());
    }

    ///Writes a list of objects to the serial.
    template <class T>
    void WriteObjects(List<T>& ListOfItems)
    {
      Write(ListOfItems.n());
      for(count i = 0; i < ListOfItems.n(); i++)
      {
        count x = -1;
        ListOfItems[i]->Serialize(*this, CheckID, x);
        Write(x);
        Write(*ListOfItems[i]);
      }
    }

    ///Writes an array of objects to the serial.
    template <class T>
    void WriteObjects(Array<T>& ArrayOfItems)
    {
      Write(ArrayOfItems.n());
      for(count i = 0; i < ArrayOfItems.n(); i++)
      {
        count x = -1;
        ArrayOfItems[i]->Serialize(*this, CheckID, x);
        Write(x);
        Write(*ArrayOfItems[i]);
      }
    }

    ///Reads a list of objects from the serial.
    template <class T>
    void ReadObjects(List<T*>& ListOfItems)
    {
      count NumberOfItems = 0;
      Read(NumberOfItems);
      ListOfItems.RemoveAll();
      for(count i = 0; i < NumberOfItems; i++)
      {
        count x = -1;
        Read(x);
        Read(*(ListOfItems.Add() = dynamic_cast<T*>(RestoreObject(x))));
      }
    }

    ///Reads an array of objects from the serial.
    template <class T>
    void ReadObjects(Array<T*>& ArrayOfItems)
    {
      count NumberOfItems = 0;
      Read(NumberOfItems);
      ArrayOfItems.ClearAndDeleteAll();
      for(count i = 0; i < NumberOfItems; i++)
      {
        count x = -1;
        Read(x);
        Read(*(ArrayOfItems.Add() = dynamic_cast<T*>(RestoreObject(x))));
      }
    }

    ///Reads or writes a value to the serial depending on the mode of operation.
    template <class T>
    void Do(T& Value, Modes Mode)
    {
      if(Mode == Reading)
        Read(Value);
      else if(Mode == Writing)
        Write(Value);
    }

    ///Reads or writes an array of objects to the serial depending on the mode.
    template <class T>
    void DoObjects(T& Value, Modes Mode)
    {
      if(Mode == Reading)
        ReadObjects(Value);
      else if(Mode == Writing)
        WriteObjects(Value);
    }

    ///Constructor to create checksum header and initialize serial reading.
    Serial()
    {
      n(32);
      StartFromBeginning();
    }

    /**Either reads a stored checksum or calculates the current checksum. When
    calculating the checksum the last 32 bytes are ignored and considered to be
    the storage area for the checksum.*/
    String ReadChecksum(bool ReadStoredChecksum)
    {
      //If no space for checksum, serial is invalid.
      if(n() < 32)
        return "";

      if(ReadStoredChecksum)
        return String(&a(), 32);
      else
        return MD5::Hex(&ith(32), n() - 32, false);
    }

    ///Writes a checksum to the serial.
    void WriteChecksum(void)
    {
      String Checksum = ReadChecksum(false);
      for(count i = 0; i < 32; i++)
        ith(i) = (byte)Checksum[i];
    }

    /**Determines whether the end of the serial contains a valid checksum. This
    method can be used regardless of whether or not it is known that a checksum
    was actually saved. The method will only return true if a checksum was written
    and it matches the data checksum.*/
    bool ChecksumValid(void)
    {
      String StoredChecksum = ReadChecksum(true);
      String ActualChecksum = ReadChecksum(false);
      return StoredChecksum.n() == 32 && StoredChecksum == ActualChecksum;
    }
  };
}
#endif

#endif

//............................................................................//

#ifdef PRIM_WITH_GRAPH

#ifndef PRIM_GRAPH_H
#define PRIM_GRAPH_H

//Enable to check consistency of graph operations and report to console.
//#define PRIM_DEBUG_GRAPH

namespace prim
{
  //Forward declarations
  class Node;

  ///Labeled, directed relationship between two nodes.
  struct Link
  {
    //Node, link, and graph manipulate each other.
    friend class Node;
    friend class Graph;

    ///Stores a link type. Note that non-positive values are reserved by the base.
    typedef count Type;

    ///Stores a link direction.
    typedef count Direction;

    ///Instrinic link types
    struct Types
    {
      static const Link::Type Generic = 0;
      static const Link::Type Unspecified = -1;
    };

    ///Intrinsic link directions forwards and backwards
    struct Directions
    {
      static const Link::Direction Forwards  = 1;
      static const Link::Direction Backwards = -1;
    };

    /**Label of the link type. These are used to efficiently navigate the graph
    without needing to check the subclasses of nodes.*/
    Link::Type Label;

    ///The parent node or previous node (as applicable).
    Node* x;

    ///The child node or next node (as applicable).
    Node* y;

    /**If a link is copied via the copy constructor this flag is set. It
    prevents the copy from automatically cleaning itself up in the graph.*/
    bool IsCopy;

    /**Used to keep track of visited links in a mark and sweep. It is considered
    unvisited if it has a negative value and visited if it has a nonnegative
    value.*/
    count VisitID;

    /**Creates a first-class link. When it is destroyed, it will sever the link
    in the graph automatically.*/
    Link(Link::Type Label, Node* x, Node* y);

    /**Creates an informational copy of a link. It will not affect the graph
    when it is destroyed. The link is only valid while the real link still
    exists.*/
    Link(const Link& Other) : Label(Other.Label), x(Other.x), y(Other.y),
      IsCopy(true) {}

    ///Destructor severs the link in the graph (unless it is a copy).
    ~Link();

    ///Gets the label (link type) of the link.
    inline Link::Type GetLabel(void) const {return Label;}
  };

  ///Graph vertex which can be subclassed as a container for something.
  class Node : public Serial::Object
  {
    public:

    //Nodes and links can manipulate each other.
    friend struct Link;
    friend class Graph;

    ///Stores a node type. Note that non-positive values are reserved by the base.
    typedef count Type;

    ///Instrinsic node types.
    struct Types
    {
      static const Node::Type Generic = 0;
    };

    private:

    ///Type of node.
    Type NodeType;

    /**List of links pertaining to this node. These include both forwards and
    backwards links.*/
    List<Link*> Links;

    public:

    /**Simple string that could be used for debugging purposes. In general,
    though nodes are subclassed to containers for specific information.*/
    String CustomData;

    /**Used to keep track of visited nodes in a mark and sweep. It is considered
    unvisited if it has a negative value and visited if it has a nonnegative
    value.*/
    count VisitID;

    ///Constructor which assigns the node type.
    Node(Node::Type NodeType);

    ///Virtual destructor.
    virtual ~Node();

    ///Gets the node type.
    inline Node::Type GetType(void) const {return NodeType;}

    ///Gets the number of links in the current node.
    inline count GetLinkCount(void) const {return Links.n();}

    ///Gets a link given its index in the current node.
    Link GetLink(count i) const;

    ///Follows a link to another node linked to the current one.
    Node* Next(Link* NodeLink, Link::Type Label = Link::Types::Unspecified,
      Link::Direction Direction = Link::Directions::Forwards) const;

    ///Returns the link index from a pointer to that link.
    count Find(Link* NodeLink) const;

    /**Returns the first link found of a given link type. This method is only
    applicable in situations when it is known that there is only one possible
    node linked in this way. Otherwise, you must use FindAll() as Find() does
    not make any guarantee about which node will be returned if there are
    more than one.*/
    Node* Find(Link::Type Label, Link::Direction Direction =
      Link::Directions::Forwards) const;

    /**Returns the first link found of a given link and node type. The method
    uses dynamic casting to find nodes of the templated node subclass. If a
    matching node is found, then the method returns true.*/
    template <class T> bool Find(T*& NodeToReturn, Link::Type Label,
      Link::Direction Direction = Link::Directions::Forwards) const;

    /**Returns an array of all linked nodes of the given type. The method uses
    dynamic casting to find nodes of the templated node subclass.*/
    template <class T> void FindAll(Array<T*>& Nodes, Link::Type Label,
      Link::Direction Direction = Link::Directions::Forwards)
      const;

    /**Establishes a double link between this node and another node. This method
    is used to add nodes to the graph.*/
    void AddLink(Node* NewNode, Link::Type Label = Link::Types::Generic,
      Link::Direction Direction = Link::Directions::Forwards);

    /**Removes any links between this node and the other. The operation is
    commutative and thus the link direction does not matter.*/
    void Unlink(Node* Other);

    /**Determines whether two nodes exhibit the relationship, y is a child of x.
    Parent-child relationships indicate tree or hierarchical relationships.*/
    virtual bool IsChild(Node::Type x, Node::Type y) {return false;}

    ///Determines whether one node type can lead to another.
    virtual bool CanLeadTo(Link::Type L, Node::Type x, Node::Type y)
    {
      return true;
    }

    ///Removes all linked nodes which are implicitly children.
    void RemoveChildNodes(void);

    ///Serializes the contents of the node.
    virtual void Serialize(Serial &s, Serial::Modes Mode, count &VersionOrID) {}
  };

  /**An unmanaged graph structure. It is unmanaged in that it only internally
  stores a pointer to the top node. All other nodes are accessed via the linked
  relationships.*/
  class Graph : public Serial::Object
  {
    /**Pointer to the a node in the graph. It is considered the starting point
    of the graph, though it does not need to necessarily have any significance
    as such.*/
    Node* Top;

    public:

    ///Constructor sets the top to null.
    Graph() : Top(0) {}

    ///Determines whether or not the graph contains a starting node.
    bool IsEmpty(void) const {return (bool)!Top;}

    ///Sets the top node which is the starting node.
    void SetTop(Node* NewTop) {Top = NewTop;}

    ///Gets the top node which is the starting node.
    Node* GetTop(void) const {return Top;}

    /*The following are built-in graph operations that can be used in
    conjunction with the traversal methods below.*/

    ///Operation to do nothing (i.e. check to make sure program does not crash).
    struct NoOp {static void Perform(const Graph* g, Node* n);};

    ///Operation to print out a node and any of its children.
    struct Print {static void Perform(const Graph* g, Node* n);};

    ///Operation to print out just the node (called by Print::Perform).
    struct PrintChildren {static void Perform(const Graph* g, Node* n);};

    ///Operation to delete a given node.
    struct Delete {static void Perform(const Graph* g, Node* n);};

    /**Traverses the children of a parent node recursively. Note that this does
    follow sibling relationships and assumes that the parent-child relationships
    can not circle back (depth is finite).*/
    template <class Operation>
    void TraverseChildren(Node* Base, count Level = 0) const
    {
      if(Level)
        Operation::Perform(this, Base);

      for(count i = 0; i < Base->GetLinkCount(); i++)
      {
        Link l = Base->GetLink(i);

        //Only look at forwards links
        if(l.x != Base)
          continue;

        c >> l.x->GetType() << ", " << l.y->GetType();

        //Traverse through any children.
        if(l.x->IsChild(l.x->GetType(), l.y->GetType()))
          TraverseChildren<Operation>(l.y, Level + 1);
      }
    }

    ///Gathers all nodes and links in the graph into arrays of nodes and links.
    void Gather(Array<Node*>& Nodes, Array<Link*>& Links, Node* Base = 0,
      count Level = 0, count MaxLevel = -1) const
    {
      if(!Level)
      {
        //Initialize the arrays and use top if no base was given.
        Nodes.n(0);
        Links.n(0);
        if(!Base) Base = Top;
      }

      //Store and mark the current node if it has not yet been visited.
      if(Base->VisitID < 0)
      {
        Base->VisitID = Nodes.n();
        Nodes.Add() = Base;
      }

      //Store, mark, and follow links.
      for(count i = 0; i < Base->GetLinkCount(); i++)
      {
        Link* l = Base->Links[i];

        //Only consider unvisited forward links.
        if((l->x != Base && l->y == Base) || l->VisitID >= 0)
          continue;

        //Store and mark the link.
        l->VisitID = Links.n();
        Links.Add() = l;

        //If it is a cyclic link that points to itself do not recurse.
        if(l->x != l->y && (MaxLevel < 0 || Level + 1 <= MaxLevel))
        {
          //Recursively call the node that is linked to.
          Gather(Nodes, Links, l->y, Level + 1, MaxLevel);
        }
      }

      /*Once all the nodes and links have been gathered, return them to the
      unvisited state.*/
      if(!Level)
      {
        for(count i = 0; i < Nodes.n(); i++)
          Nodes[i]->VisitID = -1;
        for(count i = 0; i < Links.n(); i++)
          Links[i]->VisitID = -1;
      }
    }

    ///Exports all or part of a graph to a string in the Trivial Graph Format.
    void ExportTrivialGraphFormat(String& Output, Node* Base = 0,
      count LevelsToConsider = -1) const
    {
      Output.Clear();
      Array<Node*> Nodes;
      Array<Link*> Links;

      //Gather nodes and links under consideration.
      Gather(Nodes, Links, Base, 0, LevelsToConsider);

      //Set the visit IDs.
      for(count i = 0; i < Nodes.n(); i++)
        Nodes[i]->VisitID = i;

      //Export the nodes.
      for(count i = 0; i < Nodes.n(); i++)
        Output >> Nodes[i]->VisitID << " " << Nodes[i]->CustomData;

      //Node-link separator.
      Output >> "#";

      //Export the links.
      for(count i = 0; i < Links.n(); i++)
      {
        count x = Links[i]->x->VisitID, y = Links[i]->y->VisitID;
        if(x == -1 || y == -1)
          continue; //Skip links with ungathered nodes.
        Output >> x << " " << y << " " <<
          Links[i]->Label;
      }

      //Reset the visit IDs.
      for(count i = 0; i < Nodes.n(); i++)
        Nodes[i]->VisitID = -1;
    }

    ///Virtual destructor gathers all nodes and links and deletes them.
    virtual ~Graph()
    {
      //Gather all the nodes and links.
      Array<Node*> Nodes;
      Array<Link*> Links;
      Gather(Nodes, Links);

      //Throw away the links as they have already been gathered.
      for(count i = 0; i < Nodes.n(); i++)
        Nodes[i]->Links.RemoveAll();

      //Prevent links from doing anything to remove themselves.
      for(count i = 0; i < Links.n(); i++)
        Links[i]->IsCopy = true;

      //Free the memory associated with the nodes and links.
      Nodes.ClearAndDeleteAll();
      Links.ClearAndDeleteAll();
    }

    ///Serializes the graph.
    virtual void Serialize(Serial &s, Serial::Modes Mode, count &VersionOrID)
    {
      /*Note this is a little different than a typical serialization routine in
      that reading and writing are a bit different since in writing out the
      pointer relationships are being stored as indices, and reading in the
      abstract indices are turned back into pointer relationships.*/

      if(Mode == Serial::CheckID || Mode == Serial::CheckVersion) return;

      Array<Node*> Nodes;
      Array<Link*> Links;

      //Gather the nodes for easy access.
      if(Mode == Serial::Writing)
        Gather(Nodes, Links);

      //Do the nodes.
      s.DoObjects(Nodes, Mode);

      //Set the visit ID for each node and do the custom data.
      for(count i = 0; i < Nodes.n(); i++)
      {
        Nodes[i]->VisitID = i;
        s.Do(Nodes[i]->CustomData, Mode);
      }

      //Do the top.
      if(Mode == Serial::Writing)
        s.Write(Top->VisitID);
      else if(Mode == Serial::Reading)
      {
        count TopIndex;
        s.Read(TopIndex);
        Top = Nodes[TopIndex];
      }

      //Do the link count.
      count LinksSize = Links.n();
      s.Do(LinksSize, Mode);
      Links.n(LinksSize);

      //Do the links.
      for(count i = 0; i < Links.n(); i++)
      {
        Link*& l = Links[i];
        if(Mode == Serial::Reading)
        {
          Link::Type LinkLabel;
          count LinkIndex1, LinkIndex2;
          s.Read(LinkLabel);
          s.Read(LinkIndex1);
          s.Read(LinkIndex2);
          l = new Link(LinkLabel, Nodes[LinkIndex1], Nodes[LinkIndex2]);
        }
        else if(Mode == Serial::Writing)
        {
          s.Write(l->Label);
          s.Write(l->x->VisitID);
          s.Write(l->y->VisitID);
        }
      }

      //Clear the visit ID of the nodes.
      for(count i = 0; i < Nodes.n(); i++)
        Nodes[i]->VisitID = -1;
    }
  };

#ifdef PRIM_COMPILE_INLINE
  Node::Node(Node::Type NodeType) : NodeType(NodeType), VisitID(-1) {}

  Node::~Node()
  {
    RemoveChildNodes();
    while(Links.n())
      delete Links.z();
  }

  void Node::RemoveChildNodes(void)
  {
    for(count i = 0; i < Links.n(); i++)
    {
      Node* y = Next(Links[i]);
      if(y && IsChild(NodeType, y->NodeType))
        delete y;
    }
  }

  Link Node::GetLink(count i) const
  {
    return *Links[i];
  }

  Node* Node::Next(Link* NodeLink, Link::Type Label,
    Link::Direction Direction) const
  {
    if(Direction == Link::Directions::Forwards && NodeLink->y == this)
      return 0; //Does not match since it is not in the requested direction.
    else if(Direction == Link::Directions::Backwards && NodeLink->x == this)
      return 0; //Does not match since it is not in the requested direction.
    else if(NodeLink->Label == Label || Label == Link::Types::Unspecified)
    {
      if(Direction == Link::Directions::Forwards)
        return NodeLink->y;
      else
        return NodeLink->x;
    }
    return 0;
  }

  count Node::Find(Link* NodeLink) const
  {
    for(count i = 0; i < Links.n(); i++)
    {
      if(Links[i] == NodeLink)
        return i;
    }
#ifdef PRIM_DEBUG_GRAPH
    c >> "Graph error: Link not found in node.";
#endif
    return -1;
  }

  Node* Node::Find(Link::Type Label, Link::Direction Direction) const
  {
    for(count i = 0; i < Links.n(); i++)
      if(Node* Result = Next(Links[i], Label, Direction))
        return Result;
    return 0;
  }

  template <class T> bool Node::Find(T*& NodeToReturn, Link::Type Label,
    Link::Direction Direction) const
  {
    NodeToReturn = 0;
    for(count i = 0; i < Links.n(); i++)
    {
      if(T* Result = dynamic_cast<T*>(Next(Links[i], Label, Direction)))
      {
        NodeToReturn = Result;
        break;
      }
    }
    return (bool)NodeToReturn;
  }

  template <class T> void Node::FindAll(Array<T*>& Nodes,
    Link::Type Label, Link::Direction Direction) const
  {
    Nodes.Clear();
    for(count i = 0; i < Links.n(); i++)
      if(T* Result = dynamic_cast<T*>(Next(Links[i], Label, Direction)))
        Nodes.Add() = Result;
  }

  void Node::AddLink(Node* NewNode, Link::Type Label, Link::Direction Direction)
  {
    if(Direction == Link::Directions::Forwards)
      new Link(Label, this, NewNode);
    else
      new Link(Label, NewNode, this);
  }

  void Node::Unlink(Node* Other)
  {
    for(count i = Links.n() - 1; i >= 0; i--)
    {
      Link* l = Links[i];
      if((l->x == this && l->y == Other) || (l->x == Other && l->y == this))
        delete l;
    }
  }

  //----//
  //Link//
  //----//

  Link::Link(Link::Type Label, Node* x, Node* y) : Label(Label), x(x), y(y),
    IsCopy(false), VisitID(-1)
  {
#ifdef PRIM_DEBUG_GRAPH
    for(count i = 0; i < x->Links.n(); i++)
      if(x->Next(x->Links[i]) == y)
        c >> "Graph error: Can not create two links between the same nodes.";
    if(!x->CanLeadTo(x->Type, y->Type))
      c >> "Graph error: Link does not follow rules.";
#endif
    x->Links.Add() = this;
    y->Links.Add() = this;
  }

  Link::~Link()
  {
    if(IsCopy)
      return;

    count xl = x->Find(this);
    count yl = y->Find(this);
    x->Links.Remove(xl);
    y->Links.Remove(yl);
  }

  //----------//
  //Operations//
  //----------//

  void Graph::NoOp::Perform(const Graph* g, Node* n) {}

  void Graph::Print::Perform(const Graph* g, Node* n)
  {
    c >> (g->Top == n ? "TOP " : "") << "Node " << n->CustomData << ": " <<
      n->GetType();
    c << ": " << n->CustomData;
    //c >> "Links: " << n->GetLinkCount();
    for(count i = 0; i < n->GetLinkCount(); i++)
    {
      Link l = n->GetLink(i);
      c >> "  " << l.Label << " " << l.x->CustomData << "->" <<
        l.y->CustomData << (n == l.y ? "*" : "");
    }
    c++;
    g->TraverseChildren<Graph::PrintChildren>(n);
  }

  void Graph::PrintChildren::Perform(const Graph* g, Node* n)
  {
    c >> (g->Top == n ? "TOP " : "") << "Node " << n->CustomData << ": " <<
      n->GetType();
    //c >> "Links: " << n->GetLinkCount();
    for(count i = 0; i < n->GetLinkCount(); i++)
    {
      Link l = n->GetLink(i);
      c >> "  " << l.Label << " " << l.x->CustomData << "->" <<
        l.y->CustomData << (n == l.y ? "*" : "");
    }
    c++;
  }

  void Graph::Delete::Perform(const Graph* g, Node* n)
  {
    delete n;
  }
#endif
}
#endif
 //Depends on Serialization
#endif

#endif//.........MOVE THIS LINE UP TO INCLUDE A SUBSET OF THE LIBRARY.........//

#endif
