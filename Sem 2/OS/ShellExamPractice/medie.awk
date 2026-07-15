{
    medie=($3+$4+$5)/3;
    print $1, $2, medie;
    if(medie > 8){
        if(list!="") list=list "\n";
        list=list $1 $2;
    }
}
END{
    print list;
}
