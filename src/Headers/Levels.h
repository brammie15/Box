#pragma once
#include <tice.h>
#include "Common.h"
// Player = PlayerObj, box = box , wall = wall , goal = goal
Entitytypes level1[5][5] = {
    {player, wall,  empty, empty, empty},
    {empty,     wall,  empty, wall,  box},
    {empty,     wall,  empty, wall,  empty},
    {empty,     wall,  empty, wall,  empty},
    {empty,     empty, empty, wall,  goal}};

Entitytypes level2[5][5] = {
    {player, empty, empty, empty, empty},
    {wall,      wall,  empty, wall,  empty},
    {wall,      wall,  empty, box,   empty},
    {wall,      wall,  empty, wall,  empty},
    {goal,      empty, empty, empty, empty}};

Entitytypes lebelDbg[5][5] = {
        {player, empty, empty, empty, empty},
        {wall,      wall,  empty, wall,  empty},
        {wall,      wall,  empty, box,   empty},
        {wall,      wall,  empty, wall,  empty},
        {goal,      empty, empty, empty, empty}};
