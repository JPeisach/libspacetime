#include <libspacetime/mars.h>
#include <stdio.h>

int main()
{
    char str[16];

    struct mars_tm sagittarius;
    sagittarius.mars_tm_mon = 0;
    strfmarstime(str, 16, "%b ", &sagittarius);
    printf("%s", str);

    struct mars_tm dhanus;
    dhanus.mars_tm_mon = 1;
    strfmarstime(str, 16, "%b ", &dhanus);
    printf("%s", str);

    struct mars_tm capricornus;
    capricornus.mars_tm_mon = 2;
    strfmarstime(str, 16, "%b ", &capricornus);
    printf("%s", str);

    struct mars_tm makara;
    makara.mars_tm_mon = 3;
    strfmarstime(str, 16, "%b ", &makara);
    printf("%s", str);

    struct mars_tm aquarius;
    aquarius.mars_tm_mon = 4;
    strfmarstime(str, 16, "%b ", &aquarius);
    printf("%s", str);

    struct mars_tm kumbha;
    kumbha.mars_tm_mon = 5;
    strfmarstime(str, 16, "%b ", &kumbha);
    printf("%s", str);

    struct mars_tm pisces;
    pisces.mars_tm_mon = 6;
    strfmarstime(str, 16, "%b ", &pisces);
    printf("%s", str);

    struct mars_tm mina;
    mina.mars_tm_mon = 7;
    strfmarstime(str, 16, "%b ", &mina);
    printf("%s", str);

    struct mars_tm aries;
    aries.mars_tm_mon = 8;
    strfmarstime(str, 16, "%b ", &aries);
    printf("%s", str);

    struct mars_tm mesha;
    mesha.mars_tm_mon = 9;
    strfmarstime(str, 16, "%b ", &mesha);
    printf("%s", str);

    struct mars_tm taurus;
    taurus.mars_tm_mon = 10;
    strfmarstime(str, 16, "%b ", &taurus);
    printf("%s", str);

    struct mars_tm rishabha;
    rishabha.mars_tm_mon = 11;
    strfmarstime(str, 16, "%b ", &rishabha);
    printf("%s", str);

    struct mars_tm gemini;
    gemini.mars_tm_mon = 12;
    strfmarstime(str, 16, "%b ", &gemini);
    printf("%s", str);

    struct mars_tm mithuna;
    mithuna.mars_tm_mon = 13;
    strfmarstime(str, 16, "%b ", &mithuna);
    printf("%s", str);

    struct mars_tm cancer;
    cancer.mars_tm_mon = 14;
    strfmarstime(str, 16, "%b ", &cancer);
    printf("%s", str);

    struct mars_tm karka;
    karka.mars_tm_mon = 15;
    strfmarstime(str, 16, "%b ", &karka);
    printf("%s", str);

    struct mars_tm leo;
    leo.mars_tm_mon = 16;
    strfmarstime(str, 16, "%b ", &leo);
    printf("%s", str);

    struct mars_tm simha;
    simha.mars_tm_mon = 17;
    strfmarstime(str, 16, "%b ", &simha);
    printf("%s", str);

    struct mars_tm virgo;
    virgo.mars_tm_mon = 18;
    strfmarstime(str, 16, "%b ", &virgo);
    printf("%s", str);

    struct mars_tm kanya;
    kanya.mars_tm_mon = 19;
    strfmarstime(str, 16, "%b ", &kanya);
    printf("%s", str);

    struct mars_tm libra;
    libra.mars_tm_mon = 20;
    strfmarstime(str, 16, "%b ", &libra);
    printf("%s", str);

    struct mars_tm tula;
    tula.mars_tm_mon = 21;
    strfmarstime(str, 16, "%b ", &tula);
    printf("%s", str);

    struct mars_tm scorpius;
    scorpius.mars_tm_mon = 22;
    strfmarstime(str, 16, "%b ", &scorpius);
    printf("%s", str);

    struct mars_tm vrishika;
    vrishika.mars_tm_mon = 23;
    strfmarstime(str, 16, "%b ", &vrishika);
    printf("%s", str);

    return 0;
}
