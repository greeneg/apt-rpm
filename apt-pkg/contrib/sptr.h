/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

// -*- mode: c++; mode: fold -*-
// Description								/*{{{*/
// $Id: sptr.h,v 1.1 2002/07/23 17:54:51 niemeyer Exp $
/* ######################################################################

   Trivial non-ref counted 'smart pointer'

   This is really only good to eliminate
     {
       delete Foo;
       return;
     }

   Blocks from functions.

   I think G++ has become good enough that doing this won't have much
   code size implications.

   ##################################################################### */
/*}}}*/
#ifndef SMART_POINTER_H
#define SMART_POINTER_H

template <class T>
class SPtr {
  public:
    T *Ptr;

    inline T *operator->() {
        return Ptr;
    }
    inline T &operator*() {
        return *Ptr;
    }
    inline operator T *() {
        return Ptr;
    }
    inline operator void *() {
        return Ptr;
    }
    inline T *UnGuard() {
        T *Tmp = Ptr;
        Ptr = 0;
        return Tmp;
    }
    inline void operator=(T *N) {
        Ptr = N;
    }
    inline bool operator==(T *lhs) const {
        return Ptr == lhs;
    }
    inline bool operator!=(T *lhs) const {
        return Ptr != lhs;
    }
    inline T *Get() {
        return Ptr;
    }

    inline SPtr(T *Ptr) : Ptr(Ptr) {
    }
    inline SPtr() : Ptr(0) {
    }
    inline ~SPtr() {
        delete Ptr;
    }
};

template <class T>
class SPtrArray {
  public:
    T *Ptr;

    // inline T &operator *() {return *Ptr;}
    inline operator T *() {
        return Ptr;
    }
    inline operator void *() {
        return Ptr;
    }
    inline T *UnGuard() {
        T *Tmp = Ptr;
        Ptr = 0;
        return Tmp;
    }
    // inline T &operator [](signed long I) {return Ptr[I];}
    inline void operator=(T *N) {
        Ptr = N;
    }
    inline bool operator==(T *lhs) const {
        return Ptr == lhs;
    }
    inline bool operator!=(T *lhs) const {
        return Ptr != lhs;
    }
    inline T *Get() {
        return Ptr;
    }

    inline SPtrArray(T *Ptr) : Ptr(Ptr) {
    }
    inline SPtrArray() : Ptr(0) {
    }
    inline ~SPtrArray() {
        delete[] Ptr;
    }
};

#endif
