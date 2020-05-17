#include <assert.h>
#include <string.h> // for memcmp
#include "AString_Tester.h"
#include "astring.h"

bool AString_Tester::run_tests() 
{
    // test direct assign from const char* like std::string
    AString sss = "hahaha";
    assert(memcmp(sss.c_str(), "hahaha", 6) == 0);
    
    // test addition (concatenation)
    
    sss = sss + "111";
    assert(memcmp(sss.c_str(), "hahaha111", 9) == 0);
    
    // test chained assignment
    
    AString s1,s2,s3;
    s1 = s2 = s3 = "22222";
    assert(memcmp(s1.c_str(), "22222", 5) == 0);
    assert(memcmp(s2.c_str(), "22222", 5) == 0);
    assert(memcmp(s3.c_str(), "22222", 5) == 0); 
    
    // test op== and op!=
    
    AString e1;
    AString e2;
    
    // empty ones must equal
    assert(e1 == e2);
    
    e1 = "tada!";
    assert(e1 != e2);
    e2 = "tada!";
    assert(e1 == e2);
    e2 = "aaaa";
    e1 = e2;
    assert(e1 == e2);

    // test op[] lvalue and rvalue
    
    s1[3] = 't';
    assert(memcmp(s1.c_str(), "222t2", 5) == 0);
    
    assert(s1[3] = 't');
    assert(s1[2] = '2');
    
    // test out of bounds op[]
    
    s1[8] = 'r';
    char ww = s1[9];
    assert(ww == 0x00);
    
    // test python's -1 and other negatives []
    
    s1 = "12345678";
    assert(s1[-1] == '8');
    assert(s1[-2] == '7');
    
    // test subRange1()
    
    AString sub1 = s1.subRange1(1,5);
    assert(memcmp(sub1.c_str(), "12345\0", 6) == 0);
    AString sub2 = s1.subRange1(1,-1); // must be whole string
    assert(memcmp(sub2.c_str(), "12345678\0", 9) == 0);
    
    // test subRange0()
    
    AString sub3 = s1.subRange0(0,2);
    assert(memcmp(sub3.c_str(), "123\0", 4) == 0);
    AString sub4 = s1.subRange1(0,-1); // must be whole string
    assert(memcmp(sub4.c_str(), "12345678\0", 9) == 0);
    
    // test 2 last 
    
    AString sub5 = s1.subRange1(-2,-1);
    assert(memcmp(sub5.c_str(), "78\0", 3) == 0);
    AString sub6 = s1.subRange0(-2,-1);
    assert(memcmp(sub6.c_str(), "78\0", 3) == 0);
    
    // with negatives, it doesn't matter if 0 or 1
    assert(sub5 == sub6);
    
    // test subLenx()
    AString sub7 = s1.subLen1(2,4);
    assert(memcmp(sub7.c_str(), "2345\0", 5) == 0);
    AString sub8 = s1.subLen0(2,4);
    assert(memcmp(sub8.c_str(), "3456\0", 5) == 0);

    // test copy op
    
    AString ddd = "lalala";
    AString dd = ddd;
    assert(memcmp(dd.c_str(), "lalala\0", 7) == 0);
    assert(memcmp(dd.c_str(), ddd.c_str(), 6) == 0);
    
    return true;
}