#!/bin/bash

read TEXT
UPPERLETTERS='ABCDEFGHIJKLMNOPQRSTUVWXYZ'
LOWERLETTERS='abcdefghijklmnopqrstuvwxyz'
LETTERS_AND_SPACE="${UPPERLETTERS}${LOWERLETTERS} \t\n"
message="$TEXT"
symbols="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890 !?."
wordPercentage=20
letterPercentage=85

loadDictionary(){
arr=()
while IFS= read -r line || [ -n "$line" ]; do
  arr+=("$line")
done < dictionary.txt
}
loadDictionary
getEnglishCount(){
  message=$1
  messageUpper=$(echo "$message" | tr '[:lower:]' '[:upper:]')
  IFS=' ' read -r -a possibleWords <<< "$(removeNonLetters "$messageUpper")"
  possibleWordsLength=${#possibleWords[@]}
  if [[ ${#possibleWords[@]} -eq 0 ]]; then
    echo 0
  else
    matches=0
      for word in "${possibleWords[@]}"
      do
          if [[ ! -z $(printf '%s\n' "${arr[@]}" | grep -w $word) ]]; then
            matches=$((matches+1))
          fi
      done
      matchDiv=$(bc <<< "scale=2;$matches/$possibleWordsLength")
      echo $matchDiv
  fi
}
removeNonLetters(){
  message=$1
  mesLen=${#message}
  for((i=0; i<mesLen;i++)); do
    symbol="${message:$i:1}"
    if [[ $LETTERS_AND_SPACE == *"$symbol"* ]]; then
      lettersOnly="${lettersOnly}${symbol}"
      fi
    done
    echo $lettersOnly
}

isEnglish(){
  currMsg=$1
  currMsgLen=${#currMsg}
  matchVal=$(getEnglishCount "$currMsg")
  matchPercentage=$(bc <<< "scale=2;$matchVal*100")
  matchInt=${matchPercentage%.*}
  if [[ $matchInt -ge $wordPercentage ]]; then
    wordsMatch=true
  else
    wordsMatch=false
  fi
  letters=$(removeNonLetters "$currMsg")
  numLetters=${#letters}
  messageLetters=$(bc <<< "scale=2;$numLetters/$currMsgLen")
  messageLettersPercentage=$(bc <<< "scale=2;$messageLetters*100")
  intm=${messageLettersPercentage%.*}
  if [[ $intm -ge $letterPercentage ]]; then
    lettersMatch=true
  else
    lettersMatch=false
  fi
  if [[ "$wordsMatch" == true && "$lettersMatch" == true ]]; then
    echo true
  else
    echo false
    fi
}

messageLen=${#message}
symbolLen=${#symbols}
for((key=0; key<symbolLen;key++)); do
  translated=""
  for((i=0; i<messageLen;i++)); do
    symbol="${message:$i:1}"
    if [[ $symbols == *"$symbol"* ]]; then
        for((j=0;j<symbolLen;j++)); do
          if [[ "$symbol" == "${symbols:$j:1}" ]]; then
            symbolIndex=$j
          fi
        done
        translatedIndex=$((symbolIndex - key))
        if [[ "$translatedIndex" -lt 0 ]]; then
          translatedIndex=$((translatedIndex + symbolLen))
        fi
        translated="${translated}${symbols:$translatedIndex:1}"
    else
      translated="${translated}${symbol}"
#      echo "$translated"
    fi
    done
  if [[ "$(isEnglish "$translated")" == true ]]; then
    echo "$translated"
    break
  fi
done

