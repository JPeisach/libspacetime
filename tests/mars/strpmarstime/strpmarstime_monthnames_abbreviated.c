#include <libspacetime/mars.h>
#include <stdio.h>

int main()
{
    char str[16];

    struct mars_tm sagittarius;
    strpmarstime("Sag", "%b ", &sagittarius);
    printf("%d ", sagittarius.mars_tm_mon);

    struct mars_tm dhanus;
    strpmarstime("Dha", "%b ", &dhanus);
    printf("%d ", dhanus.mars_tm_mon);

    struct mars_tm capricornus;
    strpmarstime("Cap", "%b ", &capricornus);
    printf("%d ", capricornus.mars_tm_mon);

    struct mars_tm makara;
    strpmarstime("Mak", "%b ", &makara);
    printf("%d ", makara.mars_tm_mon);

    struct mars_tm aquarius;
    strpmarstime("Aqu", "%b ", &aquarius);
    printf("%d ", aquarius.mars_tm_mon);

    struct mars_tm kumbha;
    strpmarstime("Kum", "%b ", &kumbha);
    printf("%d ", kumbha.mars_tm_mon);

    struct mars_tm pisces;
    strpmarstime("Pis", "%b ", &pisces);
    printf("%d ", pisces.mars_tm_mon);

    struct mars_tm mina;
    strpmarstime("Min", "%b ", &mina);
    printf("%d ", mina.mars_tm_mon);

    struct mars_tm aries;
    strpmarstime("Ari", "%b ", &aries);
    printf("%d ", aries.mars_tm_mon);

    struct mars_tm mesha;
    strpmarstime("Mes", "%b ", &mesha);
    printf("%d ", mesha.mars_tm_mon);

    struct mars_tm taurus;
    strpmarstime("Tau", "%b ", &taurus);
    printf("%d ", taurus.mars_tm_mon);

    struct mars_tm rishabha;
    strpmarstime("Ris", "%b ", &rishabha);
    printf("%d ", rishabha.mars_tm_mon);

    struct mars_tm gemini;
    strpmarstime("Gem", "%b ", &gemini);
    printf("%d ", gemini.mars_tm_mon);

    struct mars_tm mithuna;
    strpmarstime("Mit", "%b ", &mithuna);
    printf("%d ", mithuna.mars_tm_mon);

    struct mars_tm cancer;
    strpmarstime("Can", "%b ", &cancer);
    printf("%d ", cancer.mars_tm_mon);

    struct mars_tm karka;
    strpmarstime("Kar", "%b ", &karka);
    printf("%d ", karka.mars_tm_mon);

    struct mars_tm leo;
    strpmarstime("Leo", "%b ", &leo);
    printf("%d ", leo.mars_tm_mon);

    struct mars_tm simha;
    strpmarstime("Sim", "%b ", &simha);
    printf("%d ", simha.mars_tm_mon);

    struct mars_tm virgo;
    strpmarstime("Vir", "%b ", &virgo);
    printf("%d ", virgo.mars_tm_mon);

    struct mars_tm kanya;
    strpmarstime("Kan", "%b ", &kanya);
    printf("%d ", kanya.mars_tm_mon);

    struct mars_tm libra;
    strpmarstime("Lib", "%b ", &libra);
    printf("%d ", libra.mars_tm_mon);

    struct mars_tm tula;
    strpmarstime("Tul", "%b ", &tula);
    printf("%d ", tula.mars_tm_mon);

    struct mars_tm scorpius;
    strpmarstime("Sco", "%b ", &scorpius);
    printf("%d ", scorpius.mars_tm_mon);

    struct mars_tm vrishika;
    strpmarstime("Vri", "%b ", &vrishika);
    printf("%d", vrishika.mars_tm_mon);

    return 0;
}
