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
// $Id: acquire-worker.h,v 1.1 2002/07/23 17:54:50 niemeyer Exp $
/* ######################################################################

   Acquire Worker - Worker process manager

   Each worker class is associated with exaclty one subprocess.

   ##################################################################### */
/*}}}*/
#ifndef PKGLIB_ACQUIRE_WORKER_H
#define PKGLIB_ACQUIRE_WORKER_H

#include <apt-pkg/acquire.h>

// Interfacing to the method process
class pkgAcquire::Worker {
    friend class pkgAcquire;

  protected:
    friend class Queue;

    /* Linked list starting at a Queue and a linked list starting
       at Acquire */
    Worker *NextQueue;
    Worker *NextAcquire;

    // The access association
    Queue *OwnerQ;
    pkgAcquireStatus *Log;
    MethodConfig *Config;
    string Access;

    // This is the subprocess IPC setup
    pid_t Process;
    int InFd;
    int OutFd;
    bool InReady;
    bool OutReady;

    // Various internal things
    bool Debug;
    vector<string> MessageQueue;
    string OutQueue;

    // Private constructor helper
    void Construct();

    // Message handling things
    bool ReadMessages();
    bool RunMessages();
    bool InFdReady();
    bool OutFdReady();

    // The message handlers
    bool Capabilities(string Message);
    bool SendConfiguration();
    bool MediaChange(string Message);
    bool Authenticate(string Message);

    bool MethodFailure();
    void ItemDone();

  public:
    // The curent method state
    pkgAcquire::Queue::QItem *CurrentItem;
    string Status;
    unsigned long CurrentSize;
    unsigned long TotalSize;
    unsigned long ResumePoint;

    // Load the method and do the startup
    bool QueueItem(pkgAcquire::Queue::QItem *Item);
    bool Start();
    void Pulse();
    inline const MethodConfig *GetConf() const {
        return Config;
    }

    Worker(Queue *OwnerQ, MethodConfig *Config, pkgAcquireStatus *Log);
    Worker(MethodConfig *Config);
    ~Worker();
};

#endif

// vim:ts=4:sw=4:et
