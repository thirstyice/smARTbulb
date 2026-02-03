/*******************************************************************************
* Project: smARTbulb                                                           *
* Filename: /include/macros.h                                                  *
*                                                                              *
* Created: 2026-01-27                                                          *
* Author: thirstyice                                                           *
*                                                                              *
* Copyright (c) 2026 Tauran - https://github.com/thirstyice                    *
* For details see smARTbulb/LICENSE (if applicable)                            *
*                                                                              *
*******************************************************************************/
#pragma once
/**
** @file
** @brief Assorted handy macros
**
**/


#define PARENS ()
#define EXPAND(...) EXPAND4(EXPAND4(EXPAND4(EXPAND4(__VA_ARGS__))))
#define EXPAND4(...) EXPAND3(EXPAND3(EXPAND3(EXPAND3(__VA_ARGS__))))
#define EXPAND3(...) EXPAND2(EXPAND2(EXPAND2(EXPAND2(__VA_ARGS__))))
#define EXPAND2(...) EXPAND1(EXPAND1(EXPAND1(EXPAND1(__VA_ARGS__))))
#define EXPAND1(...) __VA_ARGS__

/**
** @brief Apply a macro to each of a variable number of args
** @param macro: The macro to apply
**/
#define FOR_EACH(macro, ...)                                    \
  __VA_OPT__(EXPAND(FOR_EACH_HELPER(macro, __VA_ARGS__)))
#define FOR_EACH_HELPER(macro, a1, ...)                         \
  macro(a1)                                                     \
  __VA_OPT__(FOR_EACH_AGAIN PARENS (macro, __VA_ARGS__))
#define FOR_EACH_AGAIN() FOR_EACH_HELPER

/**
** @brief Transforms the argument into a string
**/
#define STRINGIFY(x) #x

#define _STR_ARRAY(x) , STRINGIFY(x)
/**
** @brief Transforms the arguments into a list of strings,
** e.g. for array initialization
**/
#define STR_ARRAY(x, ...) STRINGIFY(x) __VA_OPT__(FOR_EACH(_STR_ARRAY, __VA_ARGS__))