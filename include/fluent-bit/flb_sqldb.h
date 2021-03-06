/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*  Fluent Bit
 *  ==========
 *  Copyright (C) 2015-2017 Treasure Data Inc.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef FLB_SQLDB_H
#define FLB_SQLDB_H

#include <sqlite3.h>
#include <fluent-bit.h>

struct flb_sqldb {
    char *path;               /* physical path of the database */
    char *desc;               /* database description          */
    int shared;               /* is it a shared handler ?      */
    int users;                /* number of active users        */
    sqlite3 *handler;         /* SQLite3 handler               */
    struct mk_list _head;     /* Link to config->sqldb_list    */
};

struct flb_sqldb *flb_sqldb_open(char *path, const char *desc,
                                 struct flb_config *config);
int flb_sqldb_close(struct flb_sqldb *db);

int flb_sqldb_query(struct flb_sqldb *db, char *sql,
                    int (*callback) (void *, int, char **, char **),
                    void *data);
#endif
