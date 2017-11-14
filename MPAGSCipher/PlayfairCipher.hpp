#ifndef MPAGSCIPHER_PLAYFAIRCIPHER_HPP
#define MPAGSCIPHER_PLAYFAIRCIPHER_HPP

#include <string>
#include <vector>
#include "CipherMode.hpp"

/**
  *\file PlayfairCipher.hpp
  *\brief Contains the declaration of the CaesarCipher class
  */
/**
  *\class PlayfairCipher
  *\brief Encrypt or decrypt text using the Caesar cipher with a given key
  */
class PlayfairCipher{
    public:
    PlayfairCipher( const std::string& key);
    void setKey(const std::string& key);
    std::string applyCipher(const std::string& inputText, const CipherMode cipherMode) const;
    private:
    std::string key_;

};
#endif
