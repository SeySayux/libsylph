/*
 * LibSylph Class Library
 * Copyright (C) 2009 Frank "SeySayux" Erens <seysayux@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the LibSylph Pulbic License as published
 * by the LibSylph Developers; either version 1.0 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the LibSylph
 * Public License for more details.
 *
 * You should have received a copy of the LibSylph Public License
 * along with this Library, if not, contact the LibSylph Developers.
 *
 * Created on 19 december 2008, 14:46
 */

#ifndef _HASHABLE_H
#define	_HASHABLE_H

#include "Object.h"
#include "Primitives.h"

/*< rev Object-1
 *  rev Hashable-1
 */

SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC
class Hashable : public virtual Object {
public:
    virtual sint hashCode() const = 0;
};
SYLPH_END_NAMESPACE

#endif	/* _HASHABLE_H */

