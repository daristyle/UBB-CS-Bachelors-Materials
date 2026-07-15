BEGIN{
    max=-1
    min=-1
    cnt=0;
}
{
    if(NF>max){
        max=NF;
        list_max=$0;
    }else if(NF==max){
        list_max=list_max "\n" $0
    }
    if(NF<min || min==-1){
        min=NF;
        list_min=$0;
    }else if(NF==min){
        list_min=list_min "\n" $0
    }
    cnt+=NF;
}
END{
    if(NR>0){
        print "The maximum number of words on a line is " max;
        print list_max;
        print "The minimum number of words on a line is " min;
        print list_min;
        print "The average number of words on a line is " cnt/NR;
    }else{
        print "The file is empty"
    }
}
