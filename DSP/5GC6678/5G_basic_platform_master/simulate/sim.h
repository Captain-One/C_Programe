#ifndef __SIMULATION_TOOLS_DEFS_H__
#define __SIMULATION_TOOLS_DEFS_H__
#include <pthread.h>
/** @defgroup _numerical_ Useful Numerical Functions
 *@{
The present clause specifies several numerical functions for testing of digital communication systems.

-# Generation of Uniform Random Bits
-# Generation of Quantized Gaussian Random Variables
-# Generation of Floating-point Gaussian Random Variables
-# Generic Multipath Channel Generator

 * @defgroup _channel_ Multipath channel generator
 * @ingroup _numerical_
 * @{

*/

#define NB_SAMPLES_CHANNEL_OFFSET 4



typedef enum {
  rural=0,
  urban,
  indoor
} scenario_t;


typedef enum {
  custom=0,
  SCM_A,
  SCM_B,
  SCM_C,
  SCM_D,
  EPA,
  EVA,
  ETU,
  MBSFN,
  Rayleigh8,
  Rayleigh1,
  Rayleigh1_800,
  Rayleigh1_corr,
  Rayleigh1_anticorr,
  Rice8,
  Rice1,
  Rice1_corr,
  Rice1_anticorr,
  AWGN,
  Rayleigh1_orthogonal,
  Rayleigh1_orth_eff_ch_TM4_prec_real,
  Rayleigh1_orth_eff_ch_TM4_prec_imag,
  Rayleigh8_orth_eff_ch_TM4_prec_real,
  Rayleigh8_orth_eff_ch_TM4_prec_imag,
  TS_SHIFT,
  EPA_low,
  EPA_medium,
  EPA_high,
} SCM_t;

#include "platform_constants.h"


/**@}*/

/**
 * @defgroup _taus_ Tausworthe Uniform Random Variable Generator
 * @ingroup _numerical_
 * @{
\fn unsigned int taus()
\brief Tausworthe Uniform Random Generator.  This is based on the hardware implementation described in
  Lee et al, "A Hardware Gaussian Noise Generator Usign the Box-Muller Method and its Error Analysis," IEEE Trans. on Computers, 2006.
*/
unsigned int taus(void);


/**
\fn void set_taus_seed(unsigned int seed_init)
\brief Sets the seed for the Tausworthe generator.
@param seed_init 0 means generate based on CPU time, otherwise provide the seed
*/
void set_taus_seed(unsigned int seed_init);
/**@} */



#endif


