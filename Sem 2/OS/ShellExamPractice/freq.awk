{
    for(i=1;i<=NF;++i){
        freq[$i]++;
    }
}
END{
    for(word in freq){
        print word, freq[word];
    }
}
