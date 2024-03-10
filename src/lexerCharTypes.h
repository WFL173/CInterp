#ifndef CHARTYPES_H
#define CHARTYPES_H

int IsSingleCharToken(char key);
int IsIdentifier(char key);
int IsIdentifierStart(char key);

int IsAlpha(char key);
int IsAlNum(char key);
int IsDigit(char key);
int IsWhiteSpace(char key);

#endif