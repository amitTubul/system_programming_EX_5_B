#ifndef SYSTEM_PROGRAMMING_EX_5_A_MAGICALCONTAINER_HPP
#define SYSTEM_PROGRAMMING_EX_5_A_MAGICALCONTAINER_HPP
#include <vector>
#include <algorithm>
#include <iostream>

namespace ariel {
    class MagicalContainer {
    private:
        //vector for basic use
        std::vector<int> _mysticalElements;

    public:
        MagicalContainer();

        ~MagicalContainer();

        void addElement(int element);

        void removeElement(int element);

        size_t size() const;

        class AscendingIterator {
        private:
            const MagicalContainer *_container;
            size_t _position;// current position
        public:
            AscendingIterator();

            explicit AscendingIterator(const MagicalContainer& container);

            AscendingIterator(AscendingIterator const &iterator);

            ~AscendingIterator();

            AscendingIterator & operator=(AscendingIterator other);

            bool operator==(const AscendingIterator& other) const;

            bool operator!=(const AscendingIterator& other) const;

            bool operator<(const AscendingIterator& other) const;

            bool operator>(const AscendingIterator& other) const;

            int operator*()const;

            AscendingIterator& operator++();

            AscendingIterator begin();

            AscendingIterator end();
        };


        class SideCrossIterator {
        private:
            const MagicalContainer *_container;
            size_t _last_position;// the last position
            size_t _position;// the current position
            size_t _nextPosition;// the next position
            size_t _amountOfIncrementation;// amount of ++

        public:
            SideCrossIterator();

            SideCrossIterator(SideCrossIterator const &other);

            explicit SideCrossIterator(const MagicalContainer& container);

            ~SideCrossIterator();

            SideCrossIterator &operator=(SideCrossIterator other);

            bool operator==(const SideCrossIterator& other) const;

            bool operator!=(const SideCrossIterator& other) const;

            bool operator<(const SideCrossIterator& other) const;

            bool operator>(const SideCrossIterator& other) const;

            int operator*()const;

            SideCrossIterator& operator++();

            SideCrossIterator begin();

            SideCrossIterator end();
        };

        class PrimeIterator {
        private:
            const MagicalContainer *_container;
            size_t _position;// current position
            size_t _lastPosition;// the last prime element position
            size_t _numberOfPrimes;// the amount of primes

        public:
            PrimeIterator();

            PrimeIterator(PrimeIterator const &other);

            explicit PrimeIterator(const MagicalContainer& container);

            ~PrimeIterator();

            PrimeIterator &operator=(PrimeIterator other);

            bool operator==(const PrimeIterator& other) const;

            bool operator!=(const PrimeIterator& other) const;

            bool operator<(const PrimeIterator& other) const;

            bool operator>(const PrimeIterator& other) const;

            int operator*()const;

            PrimeIterator& operator++();

            PrimeIterator begin();

            PrimeIterator end();

            size_t nextPrime();

            size_t lastPrime();

            size_t primesAmount();
        };
    };
    bool isPrime(int number);
}



#endif //SYSTEM_PROGRAMMING_EX_5_A_MAGICALCONTAINER_HPP
