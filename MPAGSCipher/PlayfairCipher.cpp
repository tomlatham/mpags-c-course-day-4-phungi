#include <string>
#include <vector>
#include "PlayfairCipher.hpp"

PlayfairCipher::PlayfairCipher(const std::string& key)
{
    setKey(key);
}

void PlayfairCipher::setKey(const std::string& key)
{
    //store the original key
    key_=key;

    //append the alphabet
    key_+="ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    //Make sure the key is upper case
    std::transform(key_.begin(),key_.end(),key_.begin(),::toupper);

    //Remove non-alpha chars
    auto func=[] (char character){
        if(!isalpha(character))
            return true;
        else
            return false;
    };
    auto iter=std::remove_if(key_.begin(),key_.end(),func);
    key_.erase(iter,key_.end());

    //change j->i
    auto jtoifunc=[] (char jtoichar){
        if(jtoichar=='J'){
            jtoichar='I';
        }
        return jtoichar;
    };
    std::transform(key_.begin(),key_.end(),key_.begin(),jtoifunc);

    //Remove duplicated letters
    std::string a{""};
    auto dupletfunc=[&] (char dupletchar){
        if(a.find(dupletchar)==std::string::npos){
            a+=dupletchar;
            return false;
        }
        else{
            return true;
        }
    };
    auto iterduplet=std::remove_if(key_.begin(),key_.end(),dupletfunc);
    key_.erase(iterduplet,key_.end());

    //store the coords of each letter
    for ( size_t i{0}; i < key_.size(); ++i ) {
	charLookup_[ key_[i] ] = i;
	coordLookup_[ i ] = key_[i];
    }
}
std::string PlayfairCipher::applyCipher(const std::string& inputText, const CipherMode cipherMode) const
{
    std::string outputText{inputText};

    // TEL:
    // It's best to tackle the J -> I and breaking up identical digraphs separately.
    // Your implementation would insert X's (or Q's) between two identical
    // letters wherever they appear in the text, while it should only be done
    // if they are two letters in the same digraph.  See our solution.

    // Change J -> I
    std::transform( std::begin(outputText), std::end(outputText), std::begin(outputText), [](char c){ return (c == 'J') ? 'I' : c; } );

  // Find repeated characters (but only when they occur within a digraph)
  // and add an X (or a Q for repeated X's) between them
    std::string tmpText{""};
    for(size_t i{0}; i < outputText.size(); i+=2) {

	// Always add the first of the digraph
	tmpText += outputText[i];

	if ( i+1 == outputText.size() ) {
	    // If this was the last character then we need to break out
	    break;

	} else if ( outputText[i] != outputText[i+1] ) {
	    // If the two characters in the digraph are different,
	    // simply add the second one as well
	    tmpText += outputText[i+1];

	} else {
	    // Otherwise, if two characters in the digraph are the same,
	    // we instead add an X (or a Q if the first was an X)
	    tmpText += (outputText[i] == 'X') ? 'Q' : 'X';
	    // Need to decrement i since the second character in this digraph
	    // now becomes the first character in the next one
	    --i;
	}
    }
    outputText = tmpText;

    // If the size of input is odd, add a trailing Z
    // (or add an X if the last character is already a Z)
    if(outputText.length()%2!=0){
	outputText += (outputText[outputText.size()-1] == 'Z') ? 'X' : 'Z';
    }

    //Loop over the input in digraphs
    for(auto iter=std::begin(outputText);iter!=std::end(outputText);iter+=2){
	auto iter1=charLookup_.find(*iter);
	auto iter2=charLookup_.find(*(iter+1));

	size_t index1 = iter1->second;
	size_t row1{ index1/5 };
	size_t column1{ index1%5 };

	size_t index2 = iter2->second;
	size_t row2{ index2/5 };
	size_t column2{ index2%5 };

	//check whether same row / same column / rectangle or square
	if ( row1 == row2 ) {
	    // same row, so increment/decrement the column indices (module 5)
	    switch (cipherMode){
		case CipherMode::Encrypt :
		    column1 = (column1 + 1) % 5;
		    column2 = (column2 + 1) % 5;
		    break;
		case CipherMode::Decrypt :
		    column1 = (5 + column1 - 1) % 5;
		    column2 = (5 + column2 - 1) % 5;
		    break;
	    }

	} else if ( column1 == column2 ) {

	    // same column, so increment/decrement row indices (module 5)
	    switch (cipherMode){
		case CipherMode::Encrypt :
		    row1 = (row1 + 1) % 5;
		    row2 = (row2 + 1) % 5;
		    break;
		case CipherMode::Decrypt :
		    row1 = (5 + row1 - 1) % 5;
		    row2 = (5 + row2 - 1) % 5;
		    break;
	    }

	} else {
	    //apply rectangular rule if not in one of the above cases
	    std::swap( column1, column2 );
	}

	// From the new rows and columns find the new indices
	index1 = 5*row1 + column1;
	index2 = 5*row2 + column2;

	// Find the letters associated with the new indices
	char char1 = coordLookup_.find(index1)->second;
	char char2 = coordLookup_.find(index2)->second;

	// Make the replacements
	(*iter)     = char1;
	(*(iter+1)) = char2;
    }

    return outputText;
}
