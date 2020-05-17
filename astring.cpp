#include "astring.h"
#include <string.h> // for strlen

// could be useful if storing not text (char buffer), but not yet implemented and not quite sure if I leave it here
AString::AString(int _reserve_bytes, bool _strictly_that_size)
{
    this->reserve_bytes = _reserve_bytes;
    this->strictly_that_size = _strictly_that_size;
    if (_reserve_bytes)
        this->byte_array = new char[_reserve_bytes];
    else
    {
        this->byte_array = new char;
        *this->byte_array = 0x00; // just a zero term
    }
    this->length = 1;
    this->NULL_ref = 0x00;
}

// setting data from const char*, like a normal std::string
AString::AString(const char *str)
{
    this->reserve_bytes = 0;
    this->strictly_that_size = false;
    this->byte_array = new char[1];
    *this->byte_array = 0x00; // just a zero term
    this->length = 1;
    this->operator=(str);
    this->NULL_ref = 0x00;
}

AString::~AString()
{
    delete[] this->byte_array;
}

// overwriting local memory
void AString::setMemory(const char *str)
{
    delete[] this->byte_array;
    int len = strlen(str)+1; // plus trailing 0
    this->byte_array = new char[len];
    memcpy(this->byte_array, str, len-1);
    this->byte_array[len-1] = 0x00;
    this->length = len;        
}

char* AString::c_str() const
{
    char *cc = this->byte_array;
    return cc;
}

int AString::getLength() const
{
    const int len = this->length-1;
    return len; // minus trailing 0
}

char AString::charAt(int idx)
{
    if ((idx < 0) || (idx >= this->length))
        // not sure what to do 
        return 0x00;
    return this->byte_array[idx];
}

char& AString::charAtRef(int idx)
{
    if ((idx < 0) || (idx >= this->length))
    {
        // not sure what to do 
        this->NULL_ref = 0x00;
        return this->NULL_ref;
    }
    return this->byte_array[idx];
}

void AString::setAt(int idx, char value)
{
    if ((idx < 0) || (idx >= this->length))
        // not sure what to do 
        return;
    this->byte_array[idx] = value;
}

AString AString::subRange1(int idx_from, int idx_to)
{
    // don't change if negative, negatives are automatically start_from_-1 based
    int idx_new_from = (idx_from>0)?idx_from-1:idx_from;
    int idx_new_to = (idx_to>0)?idx_to-1:idx_to;    
    return this->subRange0(idx_new_from,idx_new_to);
}

AString AString::subRange0(int idx_from, int idx_to) // idx_to is included
{
    if (idx_from<0)
        idx_from = this->length-1-(-idx_from);
    if (idx_to<0)
        idx_to = this->length-1-(-idx_to);    
    int new_len = idx_to-idx_from+1;
    char *cc = new char[new_len+1]; // for trailing 0
    for (int i=0;i<=new_len;i++)
    {
        cc[i] = *(this->byte_array+idx_from+i);
    }
    cc[new_len] = 0x00;
    const char *ccc = cc;
    AString new_str = ccc;
    delete[] cc;
    return new_str;
}

AString AString::subLen1(int idx_from, int count)
{
    return this->subRange1(idx_from, idx_from+count-1);
}

AString AString::subLen0(int idx_from, int count)
{
    return this->subRange0(idx_from, idx_from+count-1);
}

AString& AString::operator=(const AString& src)
{
    if (this == &src)
        return *this;
    delete[] this->byte_array;
    const int len = src.getLength()+1; // will need a trailing 0
    this->byte_array = new char[len];
    const char *cc = src.c_str();
    memcpy(this->byte_array, src.c_str(), len-1);
    this->byte_array[len-1] = 0x00;
    this->length = len;
    return *this;
}

AString& AString::operator=(const char *str)
{        
    this->setMemory(str);
    return *this;
}

AString& AString::operator+(const char *str)
{
    int str_len = strlen(str); // strlen does not include trailing 0
    int old_len = this->length-1; // minus trailing 0
    int new_len = old_len + str_len;
    char *new_array = new char[new_len+1]; // plus new trailing 0
    memcpy(new_array, this->byte_array, old_len);
    memcpy(new_array+old_len, str, str_len);
    new_array[new_len] = 0x00; // put new trailing 0
    delete[] this->byte_array;
    this->byte_array = new_array;
    this->length = new_len+1;
    return *this;
}

char& AString::operator[](int idx)
{   
    if (idx<0)
        idx = this->length-1-(-idx);
    return this->charAtRef(idx);
}

bool AString::operator==(const AString& src)
{
    if (this == &src)
        return true; // comparing with self
    int len1 = this->length;
    int len2 = src.getLength()+1; // getLength() ignores trailing 0
    if (len1!=len2)
        return false;
    const char *c1 = this->byte_array;
    const char *c2 = src.c_str();
    for (int i=0;i<len1;i++)
        if (c1[i] != c2[i])
            return false;
    return true;
}

bool AString::operator!=(const AString& src)
{
    return !this->operator==(src);
}