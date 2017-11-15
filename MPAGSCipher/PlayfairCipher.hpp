#ifndef MPAGSCIPHER_PLAYFAIRCIPHER_HPP
#define MPAGSCIPHER_PLAYFAIRCIPHER_HPP

#include <string>
#include <map>
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

    /**
     * Create a new PlayfairCipher with the given key
     *
     * \param key the key to use in the cipher
     */
    PlayfairCipher( const std::string& key);

    /**
     * Set the key to be used for the encryption/decryption
     *
     * \param key the key to use in the cipher
     */
    void setKey(const std::string& key);

    /**
     * Apply the cipher to the provided text
     *
     * \param inputText the text to encrypt or decrypt
     * \param cipherMode whether to encrypt or decrypt the input text
     * \return the result of applying the cipher to the input text
     */
    std::string applyCipher(const std::string& inputText, const CipherMode cipherMode) const;

    private:
    /// The cipher key
    std::string key_;

    // Lookup tables generated from the key

    /// Lookup table to go from the character to the index in the key
    std::map<char,size_t> charLookup_;

    /// Lookup table to go from the key index to the character
    std::map<size_t,char> coordLookup_;

};
#endif
