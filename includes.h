/* 
 * File:   includes.h
 * Author: h4x0r
 *
 * Created on 20 de abril de 2016, 05:36 PM
 */

#ifndef INCLUDES_H
#define INCLUDES_H

// system
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>

#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/time.h>
#include <ctime>
#endif

typedef unsigned long long uint64;

// me
#include "cputime.h"
#include "utility.h"
#include "quine.h"

#endif /* INCLUDES_H */

