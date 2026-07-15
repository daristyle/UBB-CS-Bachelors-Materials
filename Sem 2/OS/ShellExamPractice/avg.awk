BEGIN{
    sum=0
    count=0
}
{
    sum+=$2;
    count+=1;
}
END{
    print sum/count
}
