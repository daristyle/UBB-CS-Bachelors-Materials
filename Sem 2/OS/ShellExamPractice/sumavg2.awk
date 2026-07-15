BEGIN{
    sum=0;
    cnt=0;
}
{
    if(NF%2==0){
        print $1+$NF;
    }else{
       sum+=$((NF+1)/2);
       cnt+=1;
    }
}
END{
    print sum/cnt;
}
