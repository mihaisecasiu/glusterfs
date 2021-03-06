/*
  Copyright (c) 2012 Gluster, Inc. <http://www.gluster.com>
  This file is part of GlusterFS.

  GlusterFS is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published
  by the Free Software Foundation; either version 3 of the License,
  or (at your option) any later version.

  GlusterFS is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see
  <http://www.gnu.org/licenses/>.
*/

#ifndef _NLM4_H_
#define _NLM4_H_

#ifndef _CONFIG_H
#define _CONFIG_H
#include "config.h"
#endif

#include "rpcsvc.h"
#include "dict.h"
#include "xlator.h"
#include "iobuf.h"
#include "nfs.h"
#include "list.h"
#include "xdr-nfs3.h"
#include "locking.h"
#include "nfs3-fh.h"
#include "uuid.h"
#include "nlm4-xdr.h"
#include "lkowner.h"

/* Registered with portmap */
#define GF_NLM4_PORT            38468
#define GF_NLM                  GF_NFS"-NLM"

extern rpcsvc_program_t *
nlm4svc_init (xlator_t *nfsx);

extern int
nlm4_init_state (xlator_t *nfsx);

#define NLM_PROGRAM 100021
#define NLM_V4 4

typedef struct nlm4_lwowner {
        char temp[1024];
} nlm4_lkowner_t;

typedef struct nlm_client {
        struct sockaddr_storage sa;
        pid_t uniq;
        struct list_head nlm_clients;
        struct list_head fdes;
        struct list_head shares;
        struct rpc_clnt *rpc_clnt;
        char *caller_name;
        int nsm_monitor;
} nlm_client_t;

typedef struct nlm_share {
        struct list_head     client_list;
        struct list_head     inode_list;
        gf_lkowner_t         lkowner;
        inode_t             *inode;
        fsh_mode             mode;
        fsh_access           access;
} nlm_share_t;

typedef struct nlm_fde {
        struct list_head fde_list;
        fd_t *fd;
        int transit_cnt;
} nlm_fde_t;

typedef struct {
        pthread_cond_t cond;
        pthread_mutex_t mutex;
} nlm_condmutex_t;

#endif
