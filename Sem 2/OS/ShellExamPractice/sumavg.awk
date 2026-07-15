BEGIN{
    sum1=0
    sum2=0
    cnt=0
}
{
    for(i = 1; i <= NF; i++){
        if(NR%2==0){
            sum2+=$i;
        }
        if($i%2==1){
            sum1+=$i;
            cnt++;
        }
    }
}
END{
    if(cnt==0){
        print "No odd values found";
    }else{
        print sum1/cnt;
    }
    print sum2;
}
