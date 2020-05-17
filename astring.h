#ifndef ASTRING_H
#define ASTRING_H

#ifdef __cplusplus
extern "C" {
#endif

class AString 
// it's meant to be very forgiving about out of bounds errors, though still contain consistency
// it's meant to be user intuitive as a replacement as a string-alike class
// it's meant to be able to substring very easily without iterators and whatnot
// it's meant to bring the joy of python string indexing like negatives to count from the end
// it's meant to tolerate both start_from_0_indices and start_from_1_indices, except operator[]
{
private:
    char* byte_array;
    int length;
    int reserve_bytes;
    bool strictly_that_size;
    char NULL_ref; // for referencing out of bounds
    char charAt(int idx); // internally indices are start_from_0
    char& charAtRef(int idx); // internally indices are start_from_0
    void setAt(int idx, char value); // internally indices are start_from_0
public:
    AString(int _reserve_bytes = 0, bool _strictly_that_size = false);
    AString(const char *str);
    ~AString();
    void setMemory(const char *str);
    char* c_str() const;
    int getLength() const;
    // get a substring with begin and end indices
    AString subRange1(int idx_from, int idx_to); // indices starting from 1
    AString subRange0(int idx_from, int idx_to); // indices starting from 0
    // get a substring with begin and length
    AString subLen1(int idx_from, int count); // indices starting from 1
    AString subLen0(int idx_from, int count); // indices starting from 1
    AString& operator=(const AString& src);
    AString& operator=(const char *str);
    AString& operator+(const char *str);
    char& operator[](int idx);
    bool operator==(const AString& src);
    bool operator!=(const AString& src);
};

#ifdef __cplusplus
}
#endif

#endif /* ASTRING_H */

