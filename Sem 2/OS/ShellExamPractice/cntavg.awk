BEGIN{
    cnt1=0;
    cnt2=0;
}
{
    if(NR%2==0){
        cnt2+=NF;
    }else{
        cnt1+=NF;
    }
}
END{
    lines = (NR - NR%2)/2
    print cnt1, cnt2/lines;
}
