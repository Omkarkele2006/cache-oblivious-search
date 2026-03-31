#pragma once

class ISearchStructure {
public:
    virtual void insert(int key) = 0;
    virtual bool search(int key) = 0;
    virtual ~ISearchStructure() {}
};