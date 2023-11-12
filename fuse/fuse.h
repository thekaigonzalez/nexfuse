/*Copyright 2019-2023 Kai D. Gonzalez*/

#ifndef FUSE_FUSE_H
#define FUSE_FUSE_H

// FUSE main

#include "fdef.h"
#include "ffnmap.h"
#include "fvcpu.h"
#include "fctx.h"
#include "fbcp.h"
#include "fbcc.h"
#include "fou.h"

#include <stdio.h>
#include <sys/stat.h>

int FMain (int argc, char *argv[]);

#endif
