#include <libspacetime/mars.h>
#include <stdio.h>

int main()
{
    char str[16];

    struct mars_tm sagittarius;
    sagittarius.mars_tm_mon = 0;
    strfmarstime(str, 16, "%B ", &sagittarius);
    printf("%s", str);

    struct mars_tm dhanus;
    dhanus.mars_tm_mon = 1;
    strfmarstime(str, 16, "%B ", &dhanus);
    printf("%s", str);

    struct mars_tm capricornus;
    capricornus.mars_tm_mon = 2;
    strfmarstime(str, 16, "%B ", &capricornus);
    printf("%s", str);

    struct mars_tm makara;
    makara.mars_tm_mon = 3;
    strfmarstime(str, 16, "%B ", &makara);
    printf("%s", str);

    struct mars_tm aquarius;
    aquarius.mars_tm_mon = 4;
    strfmarstime(str, 16, "%B ", &aquarius);
    printf("%s", str);

    struct mars_tm kumbha;
    kumbha.mars_tm_mon = 5;
    strfmarstime(str, 16, "%B ", &kumbha);
    printf("%s", str);

    struct mars_tm pisces;
    pisces.mars_tm_mon = 6;
    strfmarstime(str, 16, "%B ", &pisces);
    printf("%s", str);

    struct mars_tm mina;
    mina.mars_tm_mon = 7;
    strfmarstime(str, 16, "%B ", &mina);
    printf("%s", str);

    struct mars_tm aries;
    aries.mars_tm_mon = 8;
    strfmarstime(str, 16, "%B ", &aries);
    printf("%s", str);

    struct mars_tm mesha;
    mesha.mars_tm_mon = 9;
    strfmarstime(str, 16, "%B ", &mesha);
    printf("%s", str);

    struct mars_tm taurus;
    taurus.mars_tm_mon = 10;
    strfmarstime(str, 16, "%B ", &taurus);
    printf("%s", str);

    struct mars_tm rishabha;
    rishabha.mars_tm_mon = 11;
    strfmarstime(str, 16, "%B ", &rishabha);
    printf("%s", str);

    struct mars_tm gemini;
    gemini.mars_tm_mon = 12;
    strfmarstime(str, 16, "%B ", &gemini);
    printf("%s", str);

    struct mars_tm mithuna;
    mithuna.mars_tm_mon = 13;
    strfmarstime(str, 16, "%B ", &mithuna);
    printf("%s", str);

    struct mars_tm cancer;
    cancer.mars_tm_mon = 14;
    strfmarstime(str, 16, "%B ", &cancer);
    printf("%s", str);

    struct mars_tm karka;
    karka.mars_tm_mon = 15;
    strfmarstime(str, 16, "%B ", &karka);
    printf("%s", str);

    struct mars_tm leo;
    leo.mars_tm_mon = 16;
    strfmarstime(str, 16, "%B ", &leo);
    printf("%s", str);

    struct mars_tm simha;
    simha.mars_tm_mon = 17;
    strfmarstime(str, 16, "%B ", &simha);
    printf("%s", str);

    struct mars_tm virgo;
    virgo.mars_tm_mon = 18;
    strfmarstime(str, 16, "%B ", &virgo);
    printf("%s", str);

    struct mars_tm kanya;
    kanya.mars_tm_mon = 19;
    strfmarstime(str, 16, "%B ", &kanya);
    printf("%s", str);

    struct mars_tm libra;
    libra.mars_tm_mon = 20;
    strfmarstime(str, 16, "%B ", &libra);
    printf("%s", str);

    struct mars_tm tula;
    tula.mars_tm_mon = 21;
    strfmarstime(str, 16, "%B ", &tula);
    printf("%s", str);

    struct mars_tm scorpius;
    scorpius.mars_tm_mon = 22;
    strfmarstime(str, 16, "%B ", &scorpius);
    printf("%s", str);

    struct mars_tm vrishika;
    vrishika.mars_tm_mon = 23;
    strfmarstime(str, 16, "%B ", &vrishika);
    printf("%s", str);

    return 0;
}
