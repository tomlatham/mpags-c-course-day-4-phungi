#ifndef MPAGSCIPHER_CIPHERTYPE_HPP
#define MPAGSCIPHER_CIPHERTYPE_HPP
/**
  *\file CipherType.hpp
  *\brief Enumeration to define cipher type (caesar or playfair)
  */
enum class CipherType {
    Caesar, ///< Apply Caesar cipher
    Playfair ///< Apply Playfair cipher
};
#endif
