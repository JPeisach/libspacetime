#include <libspacetime/mars.h>
#include <stdio.h>

int main()
{
    char str[16];

    struct mars_tm sagittarius;
    strpmarstime("Sagittarius", "%B ", &sagittarius);
    printf("%d ", sagittarius.mars_tm_mon);

    struct mars_tm dhanus;
    strpmarstime("Dhanus", "%B ", &dhanus);
    printf("%d ", dhanus.mars_tm_mon);

    struct mars_tm capricornus;
    strpmarstime("Capricornus", "%B ", &capricornus);
    printf("%d ", capricornus.mars_tm_mon);

    struct mars_tm makara;
    strpmarstime("Makara", "%B ", &makara);
    printf("%d ", makara.mars_tm_mon);

    struct mars_tm aquarius;
    strpmarstime("Aquarius", "%B ", &aquarius);
    printf("%d ", aquarius.mars_tm_mon);

    struct mars_tm kumbha;
    strpmarstime("Kumbha", "%B ", &kumbha);
    printf("%d ", kumbha.mars_tm_mon);

    struct mars_tm pisces;
    strpmarstime("Pisces", "%B ", &pisces);
    printf("%d ", pisces.mars_tm_mon);

    struct mars_tm mina;
    strpmarstime("Mina", "%B ", &mina);
    printf("%d ", mina.mars_tm_mon);

    struct mars_tm aries;
    strpmarstime("Aries", "%B ", &aries);
    printf("%d ", aries.mars_tm_mon);

    struct mars_tm mesha;
    strpmarstime("Mesha", "%B ", &mesha);
    printf("%d ", mesha.mars_tm_mon);

    struct mars_tm taurus;
    strpmarstime("Taurus", "%B ", &taurus);
    printf("%d ", taurus.mars_tm_mon);

    struct mars_tm rishabha;
    strpmarstime("Rishabha", "%B ", &rishabha);
    printf("%d ", rishabha.mars_tm_mon);

    struct mars_tm gemini;
    strpmarstime("Gemini", "%B ", &gemini);
    printf("%d ", gemini.mars_tm_mon);

    struct mars_tm mithuna;
    strpmarstime("Mithuna", "%B ", &mithuna);
    printf("%d ", mithuna.mars_tm_mon);

    struct mars_tm cancer;
    strpmarstime("Cancer", "%B ", &cancer);
    printf("%d ", cancer.mars_tm_mon);

    struct mars_tm karka;
    strpmarstime("Karka", "%B ", &karka);
    printf("%d ", karka.mars_tm_mon);

    struct mars_tm leo;
    strpmarstime("Leo", "%B ", &leo);
    printf("%d ", leo.mars_tm_mon);

    struct mars_tm simha;
    strpmarstime("Simha", "%B ", &simha);
    printf("%d ", simha.mars_tm_mon);

    struct mars_tm virgo;
    strpmarstime("Virgo", "%B ", &virgo);
    printf("%d ", virgo.mars_tm_mon);

    struct mars_tm kanya;
    strpmarstime("Kanya", "%B ", &kanya);
    printf("%d ", kanya.mars_tm_mon);

    struct mars_tm libra;
    strpmarstime("Libra", "%B ", &libra);
    printf("%d ", libra.mars_tm_mon);

    struct mars_tm tula;
    strpmarstime("Tula", "%B ", &tula);
    printf("%d ", tula.mars_tm_mon);

    struct mars_tm scorpius;
    strpmarstime("Scorpius", "%B ", &scorpius);
    printf("%d ", scorpius.mars_tm_mon);

    struct mars_tm vrishika;
    strpmarstime("Vrishika", "%B ", &vrishika);
    printf("%d", vrishika.mars_tm_mon);

    return 0;
}
