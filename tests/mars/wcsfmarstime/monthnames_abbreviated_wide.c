#include <libspacetime/mars.h>
#include <stdio.h>
#include <wchar.h>

int main()
{
    wchar_t str[16];

    struct mars_tm sagittarius;
    sagittarius.mars_tm_mon = 0;
    wcsfmarstime(str, 16, L"%b ", &sagittarius);
    printf("%ls", str);

    struct mars_tm dhanus;
    dhanus.mars_tm_mon = 1;
    wcsfmarstime(str, 16, L"%b ", &dhanus);
    printf("%ls", str);

    struct mars_tm capricornus;
    capricornus.mars_tm_mon = 2;
    wcsfmarstime(str, 16, L"%b ", &capricornus);
    printf("%ls", str);

    struct mars_tm makara;
    makara.mars_tm_mon = 3;
    wcsfmarstime(str, 16, L"%b ", &makara);
    printf("%ls", str);

    struct mars_tm aquarius;
    aquarius.mars_tm_mon = 4;
    wcsfmarstime(str, 16, L"%b ", &aquarius);
    printf("%ls", str);

    struct mars_tm kumbha;
    kumbha.mars_tm_mon = 5;
    wcsfmarstime(str, 16, L"%b ", &kumbha);
    printf("%ls", str);

    struct mars_tm pisces;
    pisces.mars_tm_mon = 6;
    wcsfmarstime(str, 16, L"%b ", &pisces);
    printf("%ls", str);

    struct mars_tm mina;
    mina.mars_tm_mon = 7;
    wcsfmarstime(str, 16, L"%b ", &mina);
    printf("%ls", str);

    struct mars_tm aries;
    aries.mars_tm_mon = 8;
    wcsfmarstime(str, 16, L"%b ", &aries);
    printf("%ls", str);

    struct mars_tm mesha;
    mesha.mars_tm_mon = 9;
    wcsfmarstime(str, 16, L"%b ", &mesha);
    printf("%ls", str);

    struct mars_tm taurus;
    taurus.mars_tm_mon = 10;
    wcsfmarstime(str, 16, L"%b ", &taurus);
    printf("%ls", str);

    struct mars_tm rishabha;
    rishabha.mars_tm_mon = 11;
    wcsfmarstime(str, 16, L"%b ", &rishabha);
    printf("%ls", str);

    struct mars_tm gemini;
    gemini.mars_tm_mon = 12;
    wcsfmarstime(str, 16, L"%b ", &gemini);
    printf("%ls", str);

    struct mars_tm mithuna;
    mithuna.mars_tm_mon = 13;
    wcsfmarstime(str, 16, L"%b ", &mithuna);
    printf("%ls", str);

    struct mars_tm cancer;
    cancer.mars_tm_mon = 14;
    wcsfmarstime(str, 16, L"%b ", &cancer);
    printf("%ls", str);

    struct mars_tm karka;
    karka.mars_tm_mon = 15;
    wcsfmarstime(str, 16, L"%b ", &karka);
    printf("%ls", str);

    struct mars_tm leo;
    leo.mars_tm_mon = 16;
    wcsfmarstime(str, 16, L"%b ", &leo);
    printf("%ls", str);

    struct mars_tm simha;
    simha.mars_tm_mon = 17;
    wcsfmarstime(str, 16, L"%b ", &simha);
    printf("%ls", str);

    struct mars_tm virgo;
    virgo.mars_tm_mon = 18;
    wcsfmarstime(str, 16, L"%b ", &virgo);
    printf("%ls", str);

    struct mars_tm kanya;
    kanya.mars_tm_mon = 19;
    wcsfmarstime(str, 16, L"%b ", &kanya);
    printf("%ls", str);

    struct mars_tm libra;
    libra.mars_tm_mon = 20;
    wcsfmarstime(str, 16, L"%b ", &libra);
    printf("%ls", str);

    struct mars_tm tula;
    tula.mars_tm_mon = 21;
    wcsfmarstime(str, 16, L"%b ", &tula);
    printf("%ls", str);

    struct mars_tm scorpius;
    scorpius.mars_tm_mon = 22;
    wcsfmarstime(str, 16, L"%b ", &scorpius);
    printf("%ls", str);

    struct mars_tm vrishika;
    vrishika.mars_tm_mon = 23;
    wcsfmarstime(str, 16, L"%b ", &vrishika);
    printf("%ls", str);

    return 0;
}
