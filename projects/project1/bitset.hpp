/** @file bitset.hpp*/
#ifndef BITSET_HPP
#define BITSET_HPP
#include <stdint.h>
#include <stdlib.h>

#include <string>

class Bitset {
   public:
    /** @post Bitset of size 8, filled with zeros, will be created. */
    Bitset();

    /** @param size The length of the new bitset.
     *  @post Bitset of size `size`, filled with zeros, will be created. */
    Bitset(intmax_t size);

    /** @param value The string that will be used to create a new bitset.
     *  @pre The string `value` only contains 0 and 1.
     *  @post A bitset with the same size as the string `value`, filled with 0's and 1's according to the string, will be created. */
    Bitset(const std::string &value);

    /** @post Bitset of any size wil be deallocated from memory. */
    ~Bitset();

    Bitset(const Bitset &) = delete;
    Bitset &operator=(const Bitset &) = delete;

    /** @pre None
     *  @post None
     *  @return The number of bits 'n' in the bitset. */
    intmax_t size() const;

    /** @return True if the bitset contains only 0's and or 1's, false otherwise. */
    bool good() const;

    /** @param index The bit that we want to set to 1
     *  @pre 0 <= index <= n-1, where n is the length of the bitset.
     *  @post bit at index will hold a value of 1. */
    void set(intmax_t index);

    /** @param index The bit that we want to reset to 0
     *  @pre 0 <= index <= n-1, where n is the length of the bitset.
     *  @post bit at index will hold a value of 0. */
    void reset(intmax_t index);

    /** @param index The bit that we want to toogle from 1 to 0 or from 0 to 1.
     *  @pre 0 <= index <= n-1, where n is the length of the bitset.
     *  @post bit at index will hold a value of 0 if originally 1 or a value of 1 if originally 0. */
    void toggle(intmax_t index);

    /** @param index The bit that we want the value of.
     *  @pre 0 <= index <= n-1, where n is the length of the bitset.
     *  @post None
     *  @return True if the bit holds a value of 1, false otherwise. */
    bool test(intmax_t index);

    /** @return A string of 0's and 1's that represent the bitset digits from left-to-right with MSB first. */
    std::string asString() const;

   private:
    int8_t *arr;

    intmax_t size;
};

#endif
