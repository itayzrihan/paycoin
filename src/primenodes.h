// Copyright (c) 2015 The Paycoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef PRIMENODES_H
#define PRIMENODES_H

#include "db.h"
#include "script.h"

void initPrimeNodes();
void WritePrimeNodeDB();

/* This is used to unseralize the a database entry retaining all of the the
 * primenode information */
class CPrimeNodeDBEntry
{
public:
    std::string key;
    int primeNodeRate;
    unsigned int valid_starting;
    unsigned int valid_until;

    CPrimeNodeDBEntry()
    {
        SetNull();
    }

    void SetNull()
    {
        key.clear();
        primeNodeRate = 0;
        valid_starting = 0;
        valid_until = 0;
    }

    IMPLEMENT_SERIALIZE
    (
        READWRITE(primeNodeRate);
        READWRITE(valid_starting);
        READWRITE(valid_until);
    )
};

class CPrimeNodeDB : public CDB
{
public:
    CPrimeNodeDB(const char* pszMode="r+") : CDB("primenodes.dat", pszMode) { }
private:
    CPrimeNodeDB(const CPrimeNodeDB&);
    void operator=(const CPrimeNodeDB);
public:
    bool WritePrimeNodeKey(const std::string /*key*/, int /*primeNodeRate*/, unsigned int /*valid_starting*/, unsigned int /*valid_until*/);
    bool IsPrimeNodeKey(CScript /*scriptPubKeyType*/, unsigned int /*nTime*/, CPrimeNodeDBEntry &/*entry*/);
    bool CheckPrimeNodeKey(const std::string /*key*/);
};

extern CPrimeNodeDB* primeNodeDB;

#endif // PRIMENODES_H