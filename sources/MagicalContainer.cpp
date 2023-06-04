#include "MagicalContainer.hpp"
using namespace std;

namespace ariel{
    MagicalContainer::MagicalContainer() {}

    MagicalContainer::~MagicalContainer() {}

    // adding element using lower bound to insert it as sorted container
    void MagicalContainer::addElement(int element) {
        auto it = lower_bound(_mysticalElements.begin(),_mysticalElements.end(),element);
        _mysticalElements.insert(it,element);
    }

    // remove element using find algorithm
    void MagicalContainer::removeElement(int element) {
        auto i=find(_mysticalElements.begin(),_mysticalElements.end(),element);
        if(i!=_mysticalElements.end())_mysticalElements.erase(i);
        else{throw runtime_error("element did not found");}
    }

    //using the same size function as vector
    size_t MagicalContainer::size() const {return _mysticalElements.size();}



    // for AscendingIterator
    //default constructor
    MagicalContainer::AscendingIterator::AscendingIterator() {}
    //constructor for other container
    MagicalContainer::AscendingIterator::AscendingIterator(const MagicalContainer& container):_container(&container),_position(0) {}
    //constructor for other iterators
    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer::AscendingIterator const &other):
        _container(other._container),_position(other._position){}
    //destructor
    MagicalContainer::AscendingIterator::~AscendingIterator() {}

    MagicalContainer::AscendingIterator&
    MagicalContainer::AscendingIterator::operator=(MagicalContainer::AscendingIterator other) {
        if(this->_container!=other._container){// has to  be the same container
            throw runtime_error("cannot assign between different containers");
        }
        if(this!=&other){// only if its about different iterators
            this->_container=other._container;
            this->_position=other._position;
        }
        return *this;
    }

    //comparison is by position
    bool MagicalContainer::AscendingIterator::operator==(const MagicalContainer::AscendingIterator &other) const {
        return _position==other._position;
    }
    // using the == operator
    bool MagicalContainer::AscendingIterator::operator!=(const MagicalContainer::AscendingIterator &other) const {
        return !(*this==other);
    }
    // by position
    bool MagicalContainer::AscendingIterator::operator<(const MagicalContainer::AscendingIterator &other) const {
        return _position<other._position;
    }
    // by position
    bool MagicalContainer::AscendingIterator::operator>(const MagicalContainer::AscendingIterator &other) const {
        return _position>other._position;
    }
    // returns the element
    int MagicalContainer::AscendingIterator::operator*() const {
        return _container->_mysticalElements.at(_position);
    }
    // can increment only if its valid
    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++()  {
        if(_position==_container->size()) throw runtime_error("cannot increment beyond");
        ++_position;
        return *this;
    }
    // the pointer to the beginning
    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() {
        return MagicalContainer::AscendingIterator(*_container);
    }
    // pointer to the end of the container
    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() {
        MagicalContainer::AscendingIterator it(*_container);
        it._position=_container->_mysticalElements.size();
        return it;
    }



    // for SideCrossIterator
    MagicalContainer::SideCrossIterator::SideCrossIterator() {}
    MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer& container):
        _container(&container),_last_position(0),_position(0),_nextPosition(container.size()-1),_amountOfIncrementation(0) {}
    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer::SideCrossIterator const &other):
            _container(other._container),_last_position(other._last_position),_position(other._position)
            ,_nextPosition(other._nextPosition),_amountOfIncrementation(0){}
    MagicalContainer::SideCrossIterator::~SideCrossIterator() {}

    MagicalContainer::SideCrossIterator&
    MagicalContainer::SideCrossIterator::operator=(MagicalContainer::SideCrossIterator other) {
        if(this->_container!=other._container){// has to  be the same container
            throw runtime_error("cannot assign between different containers");
        }
        if(this!=&other){
            this->_container=other._container;
            this->_position=other._position;
        }
        return *this;
    }

    bool MagicalContainer::SideCrossIterator::operator==(const MagicalContainer::SideCrossIterator &other) const {
        return _position==other._position;
    }

    bool MagicalContainer::SideCrossIterator::operator!=(const MagicalContainer::SideCrossIterator &other) const {
        return _position!=other._position;
    }

    bool MagicalContainer::SideCrossIterator::operator<(const MagicalContainer::SideCrossIterator &other) const {
        return _position<other._position;
    }

    bool MagicalContainer::SideCrossIterator::operator>(const MagicalContainer::SideCrossIterator &other) const {
        return _position>other._position;
    }

    int MagicalContainer::SideCrossIterator::operator*() const {
        return _container->_mysticalElements.at(_position);
    }
    // cannot increment more than the size of container
    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++()  {
        if(_amountOfIncrementation==_container->size())throw runtime_error("cannot increment beyond");
        if(_last_position>=_nextPosition)_position=_container->size();

        if(_position==_last_position){// check the last state
            _position=_nextPosition;
            ++_last_position;
        }
        else if(_position==_nextPosition){// check the last state
            _position=_last_position;
            --_nextPosition;
        }
        _amountOfIncrementation++;
        return *this;
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() {
        return MagicalContainer::SideCrossIterator(*_container);
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() {
        MagicalContainer::SideCrossIterator it(*_container);
        it._position=_container->_mysticalElements.size();// tricking the compiler
        return it;
    }

    // for PrimeIterator
    MagicalContainer::PrimeIterator::PrimeIterator() {}
    MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer& container)
        :_container(&container),_position(0) {
        _position=MagicalContainer::PrimeIterator::nextPrime();//position of the next close prime number
        _lastPosition=lastPrime();// position of last prime number in container
        _numberOfPrimes=primesAmount();// number of prime numbers in the container

    }
    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer::PrimeIterator const &other):
            _container(other._container),_position(other._position),_lastPosition(other._lastPosition),
            _numberOfPrimes(other._numberOfPrimes){}
    MagicalContainer::PrimeIterator::~PrimeIterator() {}

    MagicalContainer::PrimeIterator&
    MagicalContainer::PrimeIterator::operator=(MagicalContainer::PrimeIterator other) {
        if(this->_container!=other._container){ // has to  be the same container
            throw runtime_error("cannot assign between different containers");
        }
        if(this!=&other){
            this->_container=other._container;
            this->_position=other._position;
        }
        return *this;
    }

    bool MagicalContainer::PrimeIterator::operator==(const MagicalContainer::PrimeIterator &other) const {
        return _position==other._position;
    }

    bool MagicalContainer::PrimeIterator::operator!=(const MagicalContainer::PrimeIterator &other) const {
        return _position!=other._position;
    }

    bool MagicalContainer::PrimeIterator::operator<(const MagicalContainer::PrimeIterator &other) const {
        return _position<other._position;
    }

    bool MagicalContainer::PrimeIterator::operator>(const MagicalContainer::PrimeIterator &other) const {
        return _position>other._position;
    }

    int MagicalContainer::PrimeIterator::operator*() const {
        return _container->_mysticalElements.at(_position);
    }

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++()  {
        if(_position==_lastPosition+1 || _numberOfPrimes==0) throw runtime_error("cannot increment beyond");
        ++_position;
        _position=MagicalContainer::PrimeIterator::nextPrime();
        return *this;
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() {
        return MagicalContainer::PrimeIterator(*_container);
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() {
        MagicalContainer::PrimeIterator it(*_container);
        if(_numberOfPrimes==0){
            it._position=_numberOfPrimes;
        }
        else it._position=_lastPosition+1;// one after last position
        return it;
    }

    // function returns the next prime position
    size_t MagicalContainer::PrimeIterator::nextPrime() {
        for (size_t i = _position; i < _container->size(); ++i) {
            if (isPrime(_container->_mysticalElements.at(i)))return i;
        }
        return _position;
    }
    // the last prime position
    size_t MagicalContainer::PrimeIterator::lastPrime() {
        size_t lastPrime=0;
        for (size_t i = 0; i < _container->size(); ++i) {
            if(isPrime(_container->_mysticalElements.at(i))) lastPrime = i;
        }
        return lastPrime;
    }
    // check if number is prime
    bool isPrime(int number){
        if(number<=1)return false;
        for (int i = 2; i*i <= number; ++i) if(number % i == 0)return false;
        return true;
    }
    // the amount of prime numbers
    size_t MagicalContainer::PrimeIterator::primesAmount() {
        size_t sum=0;
        for (size_t i = 0; i < _container->size(); ++i) {
            if(isPrime(_container->_mysticalElements.at(i))) sum++;
        }
        return sum;
    }
}