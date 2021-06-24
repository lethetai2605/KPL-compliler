/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#ifndef __SEMANTICS_H__
#define __SEMANTICS_H__

#include "symtab.h"

void checkFreshIdent(char *name);
Object* checkDeclaredIdent(char *name);
Object* checkDeclaredConstant(char *name);
Object* checkDeclaredType(char *name);
Object* checkDeclaredVariable(char *name);
Object* checkDeclaredFunction(char *name);
Object* checkDeclaredProcedure(char *name);
Object* checkDeclaredLValueIdent(char *name);

void checkIntType(Type* type);
void checkCharType(Type* type);
void checkStringType(Type* type);           // TODO: Check kieu du lieu là string
void checkDoubleType(Type* type);           // TODO: Check kieu du lieu la double
void checkNumberType(Type* type);           // TODO: Check du lieu la so 
void checkLetterType(Type* type);           // TODO: check char or string


void checkArrayType(Type* type);
void checkBasicType(Type* type);
void checkTypeEquality(Type* type1, Type* type2);                        // check type 2 type is equal

// TODO: B2
void checkTypeInAssignment(Type* type1, Type* type2);                    // TODO: Check type left and right in assignment
void checkMultiTypeAssignment(TypeNode* list1, TypeNode* list2);         // TODO: Check type for multi assignment
#endif
