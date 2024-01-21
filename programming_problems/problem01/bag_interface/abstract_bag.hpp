/** @file abstract_bag.hpp */

#ifndef _ABSTRACT_BAG_HPP_
#define _ABSTRACT_BAG_HPP_

#include <cstdlib>

// TODO
template <typename T>
class AbstractBag {
   public:
    AbstractBag(){};
    ~AbstractBag(){};

    /** @returns The Number of items the bag can hold. */
    virtual std::size_t getCurrentSize() const = 0;

    /** @return True if the bag contains zero items, false otherwise. */
    virtual bool isEmpty() const = 0;

    /** @param entry The object to be added to the bag.
     *  @post If addition is successful, the bag contains a new item, otherwise no change.
     *  @return True if the addition was sucessful, false otherwise. */
    virtual bool add(const T& entry) = 0;

    /** @param entry The object to be removed from the bag.
     *  @post If removal is successful, the bag no longer contains the specified item, otherwise no change.
     *  @return True if the removal was sucessful, false otherwise. */
    virtual bool remove(const T& entry) = 0;

    /** @post The bag no longer contains item and is empty */
    virtual void clear() = 0;

    /** @param entry The object we want the frequenc of.
     *  @return The quantity of a specific item present in the bag. */
    virtual std::size_t getFrequencyOf(const T& entry) const = 0;

    /** @param entry The item we want to check if its in the bag or not.
     *  @return True if the item is in the bag, false otherwise. */
    virtual bool contains(const T& entry) const = 0;
};

#endif