#include <string>
#include <vector>
#include "PlayfairCipher.hpp"

PlayfairCipher::PlayfairCipher(const std::string& key)
        :key_{"aaa"};
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
    }
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
        if(a.find(dupletchar)=="npos"){
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
    using Letter2CoordMap=std::map<char, int>;
    Letter2CoordMap letterstocoord;
    for(int i{0};i<25;++i){
        letterstocoord[a[i]]=i;
    }

    //store the playfair cipher key map
}
std::string PlayfairCipher::applyCipher(const std::string& inputText, const CipherMode cipherMode) const
{
    std::string outputText{};
    std::string tempText{};
    char processedChar{'x'};
    for(const auto& origChar : inputText){
        if(isalpha(origChar)){
                //changej->i
            if(origChar=='J'){
                origChar=='I';
            }
    //start to fill temporary string
           tempText+=origChar;
    //check if repeated characters
           if(tempText.length()>1 && tempText[tempText.length()]==tempText[tempText.length()-1]){
               //add X between repeating characters
               tempText.insert(tempText.length(),"X");
           }
           //Q in case of double X
           if(tempText.length()>1 && tempText[tempText.length()]=="X" && tempText[tempText.length()-1]=="X"){
               tempText.insert(tempText.length(),"Q");
           }
    }
    }
    //f the size of input is odd, add a trailing Z
    if(tempText.length()%2!=0){
        tempText+="Z";
    }
    //put spaces after every 2nd letter

    //Loop over the input in digraphs
    for(auto iter=std::begin(tempText);iter!=tempText.end();iter+=2){
        auto iter1=letterstocoord.find(*iter);
        auto iter2=letterstocoord.find(*(iter+1));
        //check whether at end of map
        if(iter1!=letterstocoord.end() && iter2!=letterstocoord.end()){
            //check same row
            int order[2]={(*iter2).second,(*iter1).second};
            sort(order.begin(),order.end());
            switch (cipherMode){
                case CipherMode::Encrypt :
            if(order[2]-order[1]<5 && order[1]%5<=order[2]%5){
                *iter=(*(iter1+1)).first;
                *(iter+1)=(*(iter2+1)).first;
                if(*iter%5==0){
                    *iter-=5;
                }
                if(*(iter+1)%5==0){
                    *(iter+1)-=5;
                }
            }
            //check same column
            else if(abs((*iter2).second-(*iter1).second)%5==0){
                if(order[2]<20){
                    *iter=(*(iter1+5)).first;
                    *(iter+1)=(*(iter2+5)).first;
                }
                else if(order[2]==(*iter2).second && order[2]=>20 && order[1]<20){
                    *iter=(*(iter1+5)).first;
                    *(iter+1)=(*(iter2-20)).first;
                }
                else if(order[2]==(*iter1).second && order[2]=>20 && order[1]<20){
                    *iter=(*(iter1-20)).first;
                    *(iter+1)=(*(iter2+5)).first;
                }
                else if((*iter1).second==(*iter2).second && order[2]=>20){
                    *iter=(*(iter1-20)).first;
                    *(iter+1)=(*(iter2-20)).first;
                }
            }
            //apply rectangular rule if not in one of the above cases
            else{
                int jumps=abs(order[2]%5-order[1]%5);
                if((*iter1).second%5<(*iter2).second%5){
                    *iter=(*(iter1+jumps)).first;
                    *(iter+1)=(*(iter2-jumps)).first;
                }
                else{
                    *iter=(*(iter1+jumps)).first;
                    *(iter+1)=(*(iter2-jumps)).first;
                }
            }

            break;
           case CipherMode::Decrypt :
            //same as above, but reflect the steps, change the boundary row/column conditions for the first 2 cases
        }
        }
    }
    //put spaces between every pair of characters
    for(auto iter=std::begin(tempText)+1;iter!=tempText.end();iter+=2){
        tempText.insert(iter+1," ");
    }
    outputText=tempText;
    return outputText;
}
