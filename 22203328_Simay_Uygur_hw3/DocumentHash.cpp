/**
* Title:documenthash
* Author : Simay Uygur
* ID: 22203328
* Section : 1
* Homework : 3
* Description : methods are for adding one char shifting etc and calcualting hash values.
*/

#include "DocumentHash.h"
#include <iostream>
#include <cstring>
#include <algorithm>

DocumentHash::DocumentHash(int numOfStrings, char** const& docStrings)
        : numOfStrings(numOfStrings), docStrings(docStrings), currentPatternChars(nullptr), currentPatternTuple(nullptr), totalCharsLength(0) {

    precomputedPowers1 = new long long*[26];
    precomputedPowers2 = new long long*[26];
    for (int i = 0; i < 26; ++i) {
        precomputedPowers1[i] = new long long[100005]();
        precomputedPowers2[i] = new long long[100005]();
    }

    precomputePowsAccordingBase();

    allPermutations = new DocTuple[numOfStrings * 100010];     // değiştir burayı hesabı farklı
    allPatternsHash = new DocTuple[numOfStrings];

    computeStringHashes();

}


DocumentHash::~DocumentHash() {

    for (int i = 0; i < 26; ++i) {
        delete[] precomputedPowers1[i];
        delete[] precomputedPowers2[i];
    }
    delete[] precomputedPowers1;
    delete[] precomputedPowers2;

    delete[] allPermutations;
    delete[] allPatternsHash;

    currentPatternChars = nullptr;
}


void DocumentHash::precomputePowsAccordingBase() {
    int maxLength = 100005;

    for (int i = 0; i < 26; ++i) {
        precomputedPowers1[i][0] = i + 1;
        precomputedPowers2[i][0] = i + 1;
    }

    for (int i = 0; i < 26; ++i) {
        for (int j = 1; j < maxLength; ++j) {
            precomputedPowers1[i][j] = (precomputedPowers1[i][j - 1] * BASE) % MOD1;
            precomputedPowers2[i][j] = (precomputedPowers2[i][j - 1] * BASE) % MOD2;
        }
    }
}


int DocumentHash::calculateCommonDocNums() {
    int docNum = 0;

    //add delete change cyclic- - - then sort  then search and mark visited  - -while searching if sth is encountered before
    int startInd = 0;
    for (int i = 0; i < numOfStrings; ++i) {
        DocTuple curPattern = allPatternsHash[i];
        int length = curPattern.length;
        allPermutations[startInd].hash1 = curPattern.hash1;
        allPermutations[startInd].hash2 = curPattern.hash2;
        startInd++;

        addOneChar(startInd, length);
        deleteOneChar(startInd, length);
        changeOneChar(startInd, length);
        cyclicShift(startInd, length); //umarım zortlamaz

    }
    int totalChars = 100;   //bunu hesaplamak ı lazım
    int size = 28 * totalChars +2 * numOfStrings;   //size ı yaz

    std::sort(allPermutations, allPermutations + size, [](const DocTuple& a, const DocTuple& b) {
        return (a.hash1 < b.hash1) || (a.hash1 == b.hash1 && a.hash2 < b.hash2);
    });

    setCountsForElements();  //umarım çalışır

    std::sort(allPatternsHash, allPatternsHash + numOfStrings, [](const DocTuple& a, const DocTuple& b) {
        return a.count > b.count;
    }); //umarım



    //arama  visited ve sonra alıp almamaya karar veriş



    return docNum;
}

//aynı metod aslında commenttekiyle
void DocumentHash::computeStringHashes() {
    for (int j = 0; j < numOfStrings; ++j) {
        int patternLen = static_cast<int>(strlen(docStrings[j]));
        totalCharsLength += patternLen;
        char* pattern = docStrings[j];

        DocTuple patternHash;

        for (int i = 0; i < patternLen; ++i) {
            int charValue = pattern[i] - 'a';
            patternHash.hash1 = (patternHash.hash1 + precomputedPowers1[charValue][patternLen - i - 1]) % MOD1;
            patternHash.hash2 = (patternHash.hash2 + precomputedPowers2[charValue][patternLen - i - 1]) % MOD2;
        }

        allPatternsHash[j] = DocTuple(patternHash.hash1, patternHash.hash2, j, 0 , patternLen, false );
    }
}

void DocumentHash::addOneChar(int& startIndex, int patternLength) {
    // Iterate over all possible characters ('a' to 'z')
    for (int charValue = 0; charValue < 26; ++charValue) {

        DocTuple newHash ;
        newHash.hash1 = currentPatternTuple->hash1;
        newHash.hash2 = currentPatternTuple->hash2;

        //first one  - - last gibi
        newHash.hash1 = (newHash.hash1  + precomputedPowers1[charValue][patternLength]) % MOD1;  //-1 değil
        newHash.hash2 = (newHash.hash2  + precomputedPowers2[charValue][patternLength]) % MOD2;

        allPermutations[startIndex].hash1 = newHash.hash1;
        allPermutations[startIndex].hash2 = newHash.hash2;

        for (int pos = 0; pos < patternLength; ++pos) {  //umarım sınırlar doğrudur

            //switching those two.
            int existingCharValue = currentPatternChars[pos] - 'a';
            /*
            //same calculation
            newHash.hash1 = newHash.hash1 - precomputedPowers1[charValue][patternLength - pos];  //+MOd1 yapmayı unutma
            newHash.hash2 = newHash.hash2 - precomputedPowers2[charValue][patternLength - pos];

            newHash.hash1 = newHash.hash1 - precomputedPowers1[existingCharValue][patternLength - pos - 1];
            newHash.hash2 = newHash.hash2 - precomputedPowers2[existingCharValue][patternLength - pos - 1];

            newHash.hash1 = (newHash.hash1 + precomputedPowers1[charValue][patternLength - pos - 1]) % MOD1;
            newHash.hash2 = (newHash.hash2 + precomputedPowers2[charValue][patternLength - pos - 1]) % MOD2;

            newHash.hash1 = (newHash.hash1 + precomputedPowers1[existingCharValue][patternLength - pos]) % MOD1;
            newHash.hash2 = (newHash.hash2 + precomputedPowers2[existingCharValue][patternLength - pos]) % MOD2;

             */
            newHash.hash1 = newHash.hash1 + precomputedPowers1[existingCharValue][patternLength - pos -1] * (BASE - 1);
            newHash.hash2 = newHash.hash2 + precomputedPowers2[charValue][patternLength - pos - 1] * (1 - BASE);  // hope it works cidden
            //umarım doğru düşünmğşümdüe

            allPermutations[startIndex].hash1 = newHash.hash1;
            allPermutations[startIndex].hash2 = newHash.hash2;

            startIndex++;
        }


    }
}

void DocumentHash::deleteOneChar(int& startIndex, int patternLength) {
    // Separate arrays for prefix and suffix hash values
    DocTuple* prefixHashes = new DocTuple[patternLength + 1];  //bunları fized size da yapabilirim
    DocTuple* suffixHashes = new DocTuple[patternLength + 1];

    // doğru buralar sanırım
    for (int i = 0; i < patternLength; ++i) {
        int charValue = currentPatternChars[i] - 'a';

        prefixHashes[i + 1].hash1 = (prefixHashes[i].hash1 * BASE + precomputedPowers1[charValue][0]) % MOD1;
        prefixHashes[i + 1].hash2 = (prefixHashes[i].hash2 * BASE + precomputedPowers2[charValue][0]) % MOD2;
    }

    for (int i = patternLength - 1; i >= 0; --i) {
        int charValue = currentPatternChars[i] - 'a';

        suffixHashes[i].hash1 = (suffixHashes[i + 1].hash1 * BASE + precomputedPowers1[charValue][0]) % MOD1;
        suffixHashes[i].hash2 = (suffixHashes[i + 1].hash2 * BASE + precomputedPowers2[charValue][0]) % MOD2;
    }

    // Iterate over all positions in the pattern
    for (int pos = 0; pos < patternLength; ++pos) {
        //int oldCharVal = currentPatternChars[pos] - 'a';
        long long hash1 =0, hash2 = 0;
        hash1 = prefixHashes[pos - 1].hash1 * precomputedPowers1[0][patternLength - pos - 1] + suffixHashes[pos +1].hash1;   //hope it works gerçekten ya
        hash2 = prefixHashes[pos - 1].hash2 * precomputedPowers2[0][patternLength - pos - 1] + suffixHashes[pos +1].hash2;

        allPermutations[startIndex].hash1 = hash1;
        allPermutations[startIndex].hash2 = hash2;

        startIndex++;
    }

    // Clean up
    delete[] prefixHashes;
    delete[] suffixHashes;
}

void DocumentHash::cyclicShift(int& startIndex, int patternLength) {

    DocTuple patternHash;
    patternHash.hash1= currentPatternTuple -> hash1;
    patternHash.hash2 = currentPatternTuple -> hash2;

    int leftPointer = 0;
    int modulo = patternLength;

    for (int j = 1; j < patternLength; ++j) {
        int leftCharValue = currentPatternChars[leftPointer] - 'a';

        patternHash.hash1 = (patternHash.hash1 - precomputedPowers1[leftCharValue][patternLength - 1] + MOD1) % MOD1;
        patternHash.hash2 = (patternHash.hash2 - precomputedPowers2[leftCharValue][patternLength - 1] + MOD2) % MOD2;

        patternHash.hash1 = ((patternHash.hash1 * BASE) % MOD1 + precomputedPowers1[leftCharValue][0]) % MOD1;
        patternHash.hash2 = ((patternHash.hash2 * BASE) % MOD2 + precomputedPowers2[leftCharValue][0]) % MOD2;

        allPermutations[startIndex].hash1 = patternHash.hash1;
        allPermutations[startIndex].hash2 = patternHash.hash2;

        leftPointer = (leftPointer + 1) % modulo;
        startIndex++;
    }
}

void DocumentHash::changeOneChar(int& startIndex, int patternLength) { //25 * pL kadar
    for (int pos = 0; pos < patternLength -1; ++pos) {
        int oldCharVal = currentPatternChars[pos] - 'a';

        for (int newChar = 0; newChar < 26; ++newChar) {

            int curPowInd = patternLength - pos - 1;
            DocTuple newHash ;
            newHash.hash1 = currentPatternTuple->hash1;
            newHash.hash2 = currentPatternTuple->hash2;

            if(oldCharVal != newChar){
                newHash.hash1 = (newHash.hash1  - precomputedPowers1[oldCharVal][curPowInd]) % MOD1;
                newHash.hash2 = (newHash.hash2  - precomputedPowers2[oldCharVal][curPowInd]) % MOD2;

                newHash.hash1 = (newHash.hash1  + precomputedPowers1[newChar][curPowInd]) % MOD1;
                newHash.hash2 = (newHash.hash2  + precomputedPowers2[newChar][curPowInd]) % MOD2;

                allPermutations[startIndex].hash1 = newHash.hash1;
                allPermutations[startIndex].hash2 = newHash.hash2;
                startIndex++;

            }
        }
    }
}

void DocumentHash::setCountsForElements() {
    int firstPointer = 0;

    while (firstPointer < numOfStrings) {
        // Initialize count for the current group of similar hashes
        int count = 1;
        int secondPointer = firstPointer + 1;

        // Count the number of tuples with the same hash1 and hash2 values
        while (secondPointer < numOfStrings &&
               allPatternsHash[secondPointer].hash1 == allPatternsHash[firstPointer].hash1 &&
               allPatternsHash[secondPointer].hash2 == allPatternsHash[firstPointer].hash2) {
            count++;
            secondPointer++;
        }

        // Set the count for all tuples in the current group
        for (int i = firstPointer; i < secondPointer; ++i) {
            allPatternsHash[i].count = count;
        }

        // Move the first pointer to the start of the next group
        firstPointer = secondPointer;
    }
}
/*
void DocumentHash::setCountsForElements() {
    int firstPointer = 0;

    while (firstPointer < numOfStrings) {
        // Initialize count for the current group of similar hashes
        int count = 1;
        int secondPointer = firstPointer + 1;

        // Count the number of tuples with the same hash1 and hash2 values
        while (secondPointer < numOfStrings &&
               allPatternsHash[secondPointer].hash1 == allPatternsHash[firstPointer].hash1 &&
               allPatternsHash[secondPointer].hash2 == allPatternsHash[firstPointer].hash2) {
            count++;
            secondPointer++;
        }

        // Set the count for all tuples in the current group
        for (int i = firstPointer; i < secondPointer; ++i) {
            allPatternsHash[i].count = count;
        }

        // Move the first pointer to the start of the next group
        firstPointer = secondPointer;
    }
}*/


int DocumentHash::processAndCountUnique() {
    int totalCount = 0;
    int leftPointer = 0;

    while (leftPointer < numOfStrings) {
        int count = allPatternsHash[leftPointer].count;
        int rightPointer = leftPointer;
        bool hasVisited = false;

        // Check if any tuple in the group is already visited
        while (rightPointer < numOfStrings && allPatternsHash[rightPointer].count == count) {
            if (allPatternsHash[rightPointer].isVisited) {
                hasVisited = true;
            }
            rightPointer++;
        }

        if (!hasVisited) {
            // Mark all tuples in the group as visited and add count to totalCount
            for (int i = leftPointer; i < rightPointer; ++i) {
                allPatternsHash[i].isVisited = true;
            }
            totalCount += count;
        }

        // Move leftPointer to the start of the next group
        leftPointer = rightPointer;
    }

    return totalCount;
}

/*void DocumentHash::computeStringHashes() {
    for (int j = 0; j < numOfStrings; ++j) {
        int patternLen = static_cast<int>(strlen(docStrings[j]));
        char* pattern = docStrings[j];

        DocTuple patternHash;
        for (int i = 0; i < patternLen; ++i) {
            int charValue = pattern[i] - 'a';

            patternHash.hash1 = (patternHash.hash1 + precomputedPowers1[charValue][patternLen - i - 1]) % MOD1;
            patternHash.hash2 = (patternHash.hash2 + precomputedPowers2[charValue][patternLen - i - 1]) % MOD2;
        }

        allPatternsHash[j] = DocTuple(patternHash.hash1, patternHash.hash2, j, false, 0);
    }
}*//*void DocumentHash::deleteOneChar(int& startIndex, int patternLength) {
    DocTuple prefixes [100000];   //size'ı değiştir
    DocTuple suffixes[100000];


    for (int pos = 0; pos < patternLength; ++pos) {


        //allPermutations

        startIndex++;
    }
}*/
