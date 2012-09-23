/*
 * LibSylph Class Library
 * Copyright (C) 2012 Frank "SeySayux" Erens <seysayux@gmail.com>
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *   1. The origin of this software must not be misrepresented; you must not
 *   claim that you wrote the original software. If you use this software
 *   in a product, an acknowledgment in the product documentation would be
 *   appreciated but is not required.
 *
 *   2. Altered source versions must be plainly marked as such, and must not be
 *   misrepresented as being the original software.
 *
 *   3. This notice may not be removed or altered from any source
 *   distribution.
 *
 *  Created on: Aug 21, 2012
 */

#include "GuessOS.h"

#ifdef SYLPH_OS_OSX
#include <mach-o/dyld.h>
#include <sys/param.h>
#include <stdint.h>
#include <stdlib.h>

const char* OSXExeLocator() {
    char* path = (char*)malloc(MAXPATHLEN);
    uint32_t bufsize = MAXPATHLEN;

    if(_NSGetExecutablePath(path, &bufsize) == -1) {
        path = (char*)realloc(path, bufsize);
        _NSGetExecutablePath(path, &bufsize);
    }

    return path;
    
}

const char* OSXLibLocator(const void* symbol) {
    return DladdrLibLocator(symbol);
}

const char* (*ExeLocator)() = OSXExeLocator;
const char* (*LibLocator)(const void*) = OSXLibLocator;

#endif
