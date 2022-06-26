/*
  fft.c

  Copyright:
          Copyright (c) 2002-2004 SFNT Finland Oy.
                All rights reserved.

  Implementation of complex FFT. This version is a children of the
  version by J.G.G. Dobbe in DDJ Feb '95.

 */

#include "sshincludes.h"
#include "fft.h"

static double fft_cos[64] =
{ /* cos{-2pi/N} for N = 2, 4, 8, ... 16384 */
  -1.00000000000000000000000000000,
  0.E-38,
  0.707106781186547524400844362104,
  0.923879532511286756128183189396,
  0.980785280403230449126182236134,
  0.995184726672196886244836953109,
  0.998795456205172392714771604759,
  0.999698818696204220115765649666,
  0.999924701839144540921646491196,
  0.999981175282601142656990437728,
  0.999995293809576171511580125700,
  0.999998823451701909929025710171,
  0.999999705862882219160228217738,
  0.999999926465717851144731480707,
  0.999999981616429293808346915403,
  0.999999995404107312890971933139,
  0.999999998851026827562673307794,
  0.999999999712756706849413972218,
  0.999999999928189176709775095884,
  0.999999999982047294177282624147,
  0.999999999995511823544310584173,
  0.999999999998877955886077016551,
  0.999999999999719488971519214794,
  0.999999999999929872242879801239,
  0.999999999999982468060719950156,
  0.999999999999995617015179987529,
  0.999999999999998904253794996881,
  0.999999999999999726063448749220,
  0.999999999999999931515862187305,
  0.999999999999999982878965546826,
  0.999999999999999995719741386706,
  0.999999999999999998929935346676,

  /* cos{2pi/N} for N = 2, 4, 8, ... 16384 */
   -1.00000000000000000000000000000,
  0.E-38,
  0.707106781186547524400844362104,
  0.923879532511286756128183189396,
  0.980785280403230449126182236134,
  0.995184726672196886244836953109,
  0.998795456205172392714771604759,
  0.999698818696204220115765649666,
  0.999924701839144540921646491196,
  0.999981175282601142656990437728,
  0.999995293809576171511580125700,
  0.999998823451701909929025710171,
  0.999999705862882219160228217738,
  0.999999926465717851144731480707,
  0.999999981616429293808346915403,
  0.999999995404107312890971933139,
  0.999999998851026827562673307794,
  0.999999999712756706849413972218,
  0.999999999928189176709775095884,
  0.999999999982047294177282624147,
  0.999999999995511823544310584173,
  0.999999999998877955886077016551,
  0.999999999999719488971519214794,
  0.999999999999929872242879801239,
  0.999999999999982468060719950156,
  0.999999999999995617015179987529,
  0.999999999999998904253794996881,
  0.999999999999999726063448749220,
  0.999999999999999931515862187305,
  0.999999999999999982878965546826,
  0.999999999999999995719741386706,
  0.999999999999999998929935346676
};

static double fft_sin[64] =
{ /* sin{-2pi/N} for N = 2, 4, 8, ... 16384 */
  0.E-38,
  -1.00000000000000000000000000000,
  -0.70710678118654752440084436210,
  -0.38268343236508977172845998403,
  -0.19509032201612826784828486847,
  -0.09801714032956060199419556388,
  -0.04906767432741801425495497694,
  -0.02454122852291228803173452945,
  -0.01227153828571992607940826195,
  -0.00613588464915447535964023459,
  -0.00306795676296597627014536549,
  -0.00153398018628476561230369715,
  -0.00076699031874270452693856835,
  -0.00038349518757139558907246168,
  -0.00019174759731070330743990956,
  -0.00009587379909597734587051721,
  -0.00004793689960306688454900399,
  -0.00002396844980841821872918657,
  -0.00001198422490506970642152156,
  -0.00000599211245264242784287971,
  -0.00000299605622633466075045481,
  -0.00000149802811316901122885427,
  -0.00000074901405658471572113049,
  -0.00000037450702829238412390316,
  -0.00000018725351414619534486882,
  -0.00000009362675707309808279906,
  -0.00000004681337853654909269511,
  -0.00000002340668926827455275950,
  -0.00000001170334463413727718124,
  -0.00000000585167231706863869080,
  -0.00000000292583615853431935792,
  -0.00000000146291807926715968052,

  /* sin{2pi/N} for N = 2, 4, 8, ... 16384 */
  0.E-38,
  1.00000000000000000000000000000,
  0.70710678118654752440084436210,
  0.38268343236508977172845998403,
  0.19509032201612826784828486847,
  0.09801714032956060199419556388,
  0.04906767432741801425495497694,
  0.02454122852291228803173452945,
  0.01227153828571992607940826195,
  0.00613588464915447535964023459,
  0.00306795676296597627014536549,
  0.00153398018628476561230369715,
  0.00076699031874270452693856835,
  0.00038349518757139558907246168,
  0.00019174759731070330743990956,
  0.00009587379909597734587051721,
  0.00004793689960306688454900399,
  0.00002396844980841821872918657,
  0.00001198422490506970642152156,
  0.00000599211245264242784287971,
  0.00000299605622633466075045481,
  0.00000149802811316901122885427,
  0.00000074901405658471572113049,
  0.00000037450702829238412390316,
  0.00000018725351414619534486882,
  0.00000009362675707309808279906,
  0.00000004681337853654909269511,
  0.00000002340668926827455275950,
  0.00000001170334463413727718124,
  0.00000000585167231706863869080,
  0.00000000292583615853431935792,
  0.00000000146291807926715968052
};

/* The FFT routine */

void fft(double *re, double *im, unsigned int exp, int inv)
{
  unsigned int section, n,
    angle_counter, fly_distance, fly_count,
    index1, index2, tmp, tmp1;
  double temp, s, c, scale, Qr, Qi, tempr, tempi;

  /* Compute the size. */
  n = (1 << exp);

  /* Shuffle array */
  for (index1 = 0; index1 < n; index1++)
    {
      /* Shuffle index */
      for (tmp1 = index1, index2 = 0, tmp = n >> 1; tmp; tmp >>= 1)
        {
          index2 = index2 << 1;
          if ((tmp1 & 1) != 0)
            index2 ++;
          tmp1 >>= 1;
        }

      if (index2 > index1)
        {
          temp = re[index1];
          re[index1] = re[index2];
          re[index2] = temp;

          temp = im[index1];
          im[index1] = im[index2];
          im[index2] = temp;
        }
    }

  /* Set up the table pointers. */
  if (inv)
    angle_counter = 32;
  else
    angle_counter = 0;

  section = 1;
  while (section < n)
    {
      fly_distance = section << 1;
      c = fft_cos[angle_counter];
      s = fft_sin[angle_counter];
      Qr = 1;
      Qi = 0;

      for (fly_count = 0; fly_count < section; fly_count++)
        {
          index1 = fly_count;
          do
            {
              index2 = index1 + section;

              tempr = Qr * re[index2] - Qi * im[index2];
              tempi = Qr * im[index2] + Qi * re[index2];

              re[index2] = re[index1] - tempr;
              re[index1] = re[index1] + tempr;

              im[index2] = im[index1] - tempi;
              im[index1] = im[index1] + tempi;

              index1 = index1 + fly_distance;
            }
          while (index1 < n);

          temp = Qr;
          Qr = Qr*c - Qi*s;
          Qi = Qi*c + temp*s;
        }
      section <<= 1;
      angle_counter++;
    }

  if (inv)
    {
      scale = 1.0/n;
      for (index1 = 0; index1 < n; index1++)
        {
          re[index1] = scale * re[index1];
          im[index1] = scale * im[index1];
        }
    }
}

/* fft.c */