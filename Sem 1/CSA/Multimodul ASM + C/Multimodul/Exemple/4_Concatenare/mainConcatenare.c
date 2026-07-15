/*++
Se cere un program C/C++ care apeleaza procedura asmConcat scrisa in limbaj de asamblare.

Procedura asmConcat:
- primeste ca parametrii: offsetul sirului str1 (care e citit in programul C) si offsetul sirului rezultat strRez
- citeste un alt sir de caractere strCitit cu ajutorul functiei citesteSir (care e definita in programul C)
- acceseaza sirul de caractere str3 (care e definit ca variabila globala in programul C)
- intoarce sirul obtinut prin concatenarea primele 10 caractere din cele 3 siruri de caractere

Sirul obtinut va fi afisat pe ecran in programul C.

Obs: Sirurile citite de la tastatura nu trebuie sa contina spatii.
--*/

#include <stdio.h>

// declararea procedurii definite in limbaj de asamblare
int asmConcat(char sir[], char sirR[]);

// declararea functiei C folosite pentru a citi un sir de la tastatura
void citireSirC(char sir[]);

// definirea sirului global care va fi accesat din asmConcat
char str3[] = "0011223344";


int main()
{
    int lenStrRez = 0;
    char str1[11];
    char strRez[31] = "";

    printf("! Se presupune ca sirurile citite de la tastatura au lungimea 10 !! (nu se fac verificari suplimentare)\n");
    printf("Sirul 1 citit in modulul C: ");
    citireSirC(str1);

    // apel procedura definita in asamblare
    lenStrRez = asmConcat(str1, strRez);
    printf("\nSirul rezultat de lungime %d:\n%s", lenStrRez, strRez);
    
    return 0;
}

// definirea functiei C folosite pentru a citi un sir de la tastatura
void citireSirC(char sir[])
{
    scanf("%s", sir);
}
