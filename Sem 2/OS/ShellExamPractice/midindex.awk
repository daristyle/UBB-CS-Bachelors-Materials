{
    if(NF%2==1){
        print $((NF+1)/2);
    }
    if(NF>2){
        if(list!="") list = list " ";
        list=list NR;
    }
}
END{
    print list;
}
