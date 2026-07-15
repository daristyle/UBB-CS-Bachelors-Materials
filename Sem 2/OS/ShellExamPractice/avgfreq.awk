BEGIN{
    cnt=0;
}
{
    cnt+=NF;
    for(i=1;i<=NF;i++){
        freq[$i]++;
    }
}
END{
    if(NR>0){
        avg=cnt/NR;
        print avg
        for(word in freq){
            if(freq[word] < avg){
                print word
            }
        }
    }else{
        print "The file is empty"
    }
}
