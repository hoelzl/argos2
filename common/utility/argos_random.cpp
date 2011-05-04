/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/**
 * @file <common/utility_classes/argos_random.cpp>
 *
 * @brief This file provides the definition of
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "argos_random.h"
#include <argos2/common/utility/configuration/argos_exception.h>
#include <argos2/common/utility/logging/argos_log.h>
#include <cstring>
#include <limits>
#include <cmath>

#ifndef CROSSCOMPILING
#   include <gsl/gsl_randist.h>
#endif

namespace argos {

   /****************************************/
   /****************************************/

   std::map<std::string, CARGoSRandom::CCategory> CARGoSRandom::m_mapCategories;

#ifndef CROSSCOMPILING
   /* Creates an array of all the available generator types, terminated by a null pointer */
   const gsl_rng_type** CARGoSRandom::m_pptRNGTypes = gsl_rng_types_setup();
#endif

   /* Checks that a category exists. It internally creates an iterator that points to the category, if found.  */
#define CHECK_CATEGORY(category)                                        \
   std::map<std::string, CCategory>::iterator itCategory = m_mapCategories.find(category); \
   if(itCategory == m_mapCategories.end()) {                            \
      THROW_ARGOSEXCEPTION("CARGoSRandom::CreateRNG: can't create an RNG in category \"" << category << "\" because it doesnt exist."); \
   }

   /****************************************/
   /****************************************/

   CARGoSRandom::CRNG::CRNG(UInt32 un_seed,
                            const std::string& str_type) :
      m_unSeed(un_seed),
      m_strType(str_type),
      m_ptRNG(NULL),
#ifdef CROSSCOMPILING
      m_pchRNGState(NULL),
#endif
      m_pcIntegerRNGRange(NULL) {
      CreateRNG();
   }
   
   /****************************************/
   /****************************************/
   
   CARGoSRandom::CRNG::CRNG(CByteArray& c_buffer) :
      m_ptRNG(NULL),
#ifdef CROSSCOMPILING
      m_pchRNGState(NULL),
#endif
      m_pcIntegerRNGRange(NULL) {
      /* Get the seed of the generator */
      c_buffer >> m_unSeed;
      /* Get the type of the generator */
      c_buffer >> m_strType;
      /* Create the RNG */
      CreateRNG();
      /* Restore the state of the generator */
#ifndef CROSSCOMPILING
      size_t unStateSize = gsl_rng_size(m_ptRNG);
      UInt8* pStateBuffer = new UInt8[unStateSize];
      c_buffer.FetchBuffer(pStateBuffer, unStateSize);
      ::memcpy(gsl_rng_state(m_ptRNG), pStateBuffer, unStateSize);
      /* Cleanup */
      delete[] pStateBuffer;
#else
      c_buffer.FetchBuffer(reinterpret_cast<UInt8*>(m_pchRNGState), 256);
      setstate_r(m_pchRNGState, m_ptRNG);
#endif
   }

   /****************************************/
   /****************************************/

   CARGoSRandom::CRNG::CRNG(const CRNG& c_rng) :
      m_unSeed(c_rng.m_unSeed),
      m_strType(c_rng.m_strType),
      m_ptRNG(NULL),
#ifdef CROSSCOMPILING
      m_pchRNGState(NULL),
#endif
      m_pcIntegerRNGRange(new CRange<UInt32>(*c_rng.m_pcIntegerRNGRange)) {
      /* Clone RNG of original */
#ifndef CROSSCOMPILING
      m_ptRNG = gsl_rng_clone(c_rng.m_ptRNG);
#else
      m_ptRNG = new random_data;
      ::memset(m_ptRNG, 0, sizeof(random_data));
      m_pchRNGState = new char[256];
      SInt32 nError = initstate_r(m_unSeed, m_pchRNGState, 256, m_ptRNG);
      if(nError != 0) {
         THROW_ARGOSEXCEPTION("Unable to create random number generator (initstate_r returned " << nError << ").");
      }
      ::memcpy(m_pchRNGState, c_rng.m_pchRNGState, 256);
      setstate_r(m_pchRNGState, m_ptRNG);
#endif
   }

   /****************************************/
   /****************************************/

   CARGoSRandom::CRNG::~CRNG() {
      DisposeRNG();
   }

   /****************************************/
   /****************************************/

   void CARGoSRandom::CRNG::CreateRNG() {
#ifndef CROSSCOMPILING
      /* Look for RNG type in the RNG type list */
      bool bFound = false;
      const gsl_rng_type** pptRNGType = GetRNGTypes();
      while((!bFound) && (pptRNGType != NULL)) {
         if(m_strType == (*pptRNGType)->name) {
            bFound = true;
         }
         else {
            ++pptRNGType;
         }
      }
      if(!bFound) {
         /* RNG type not found, error! */
         THROW_ARGOSEXCEPTION("Unknown random number generator type '" << m_strType << "'.");
      }
      /* We found the wanted RNG type, create the actual RNG */
      m_ptRNG = gsl_rng_alloc(*pptRNGType);
      gsl_rng_set(m_ptRNG, m_unSeed);
      /* Initialize RNG range */
      m_pcIntegerRNGRange = new CRange<UInt32>(gsl_rng_min(m_ptRNG),
                                               gsl_rng_max(m_ptRNG));
#else
      /* Initialize RNG */
      m_ptRNG = new random_data;
      ::memset(m_ptRNG, 0, sizeof(random_data));
      m_pchRNGState = new char[256];
      SInt32 nError = initstate_r(m_unSeed, m_pchRNGState, 256, m_ptRNG);
      if(nError != 0) {
         THROW_ARGOSEXCEPTION("Unable to create random number generator (initstate_r returned " << nError << ").");
      }
      /* Initialize RNG range */
      m_pcIntegerRNGRange = new CRange<UInt32>(0, RAND_MAX);
#endif
   }

   /****************************************/
   /****************************************/

   void CARGoSRandom::CRNG::DisposeRNG() {
#ifndef CROSSCOMPILING
      gsl_rng_free(m_ptRNG);
#else
      delete m_ptRNG;
      delete[] m_pchRNGState;
#endif
      delete m_pcIntegerRNGRange;
   }

   /****************************************/
   /****************************************/

   void CARGoSRandom::CRNG::SaveState(CByteArray& c_buffer) {
      /* Dump the seed of the generator */
      c_buffer << m_unSeed;
      /* Dump the type of the generator */
      c_buffer << m_strType;
      /* Dump the state of the generator */
#ifndef CROSSCOMPILING
      UInt8* pStateBuffer = reinterpret_cast<UInt8*>(gsl_rng_state(m_ptRNG));
      c_buffer.AddBuffer(pStateBuffer, gsl_rng_size(m_ptRNG));
#else
      c_buffer.AddBuffer(reinterpret_cast<UInt8*>(m_pchRNGState), 256);
#endif
   }

   /****************************************/
   /****************************************/

   void CARGoSRandom::CRNG::LoadState(CByteArray& c_buffer) {
      /* Get the seed of the generator */
      c_buffer >> m_unSeed;
      /* Get the type of the generator */
      std::string strReadType;
      c_buffer >> strReadType;
#ifndef CROSSCOMPILING
      /* Check if the type read and the current type match */
      if(strReadType != m_strType) {
         /* The types don't match.
            We need to recreate the generator with the right type */
         m_strType = strReadType;
         DisposeRNG();
         CreateRNG();
      }
      /* Get the state of the generator */
      size_t unStateSize = gsl_rng_size(m_ptRNG);
      UInt8* pStateBuffer = new UInt8[unStateSize];
      c_buffer.FetchBuffer(pStateBuffer, unStateSize);
      /* Restore the state of the RNG */
      ::memcpy(gsl_rng_state(m_ptRNG), pStateBuffer, unStateSize);
      /* Cleanup */
      delete[] pStateBuffer;
#else
      c_buffer.FetchBuffer(reinterpret_cast<UInt8*>(m_pchRNGState), 256);
      setstate_r(m_pchRNGState, m_ptRNG);
#endif
   }
   
   /****************************************/
   /****************************************/

   void CARGoSRandom::CRNG::Reset() {
#ifndef CROSSCOMPILING
      gsl_rng_set(m_ptRNG, m_unSeed);
#else
      initstate_r(m_unSeed, m_pchRNGState, 256, m_ptRNG);
#endif
   }
   
   /****************************************/
   /****************************************/

   bool CARGoSRandom::CRNG::Bernoulli(Real f_true) {
#ifndef CROSSCOMPILING
      return gsl_rng_uniform(m_ptRNG) < f_true;
#else
      UInt32 unNumber;
      random_r(m_ptRNG, reinterpret_cast<int32_t*>(&unNumber));
      return m_pcIntegerRNGRange->NormalizeValue(unNumber) < f_true;
#endif
   }

   /****************************************/
   /****************************************/

   Real CARGoSRandom::CRNG::Uniform(const CRange<Real>& c_range) {
#ifndef CROSSCOMPILING
      return c_range.GetMin() + gsl_rng_uniform(m_ptRNG) * c_range.GetSpan();
#else
      UInt32 unNumber;
      random_r(m_ptRNG, reinterpret_cast<int32_t*>(&unNumber));
      Real fRetVal;
      m_pcIntegerRNGRange->MapValueIntoRange(fRetVal, unNumber, c_range);
      return fRetVal;
#endif
   }
   
   /****************************************/
   /****************************************/

   SInt32 CARGoSRandom::CRNG::Uniform(const CRange<SInt32>& c_range) {
#ifndef CROSSCOMPILING
      SInt32 nRetVal;
      m_pcIntegerRNGRange->MapValueIntoRange(nRetVal, gsl_rng_get(m_ptRNG), c_range);
      return nRetVal;
#else
      UInt32 unNumber;
      random_r(m_ptRNG, reinterpret_cast<int32_t*>(&unNumber));
      SInt32 nRetVal;
      m_pcIntegerRNGRange->MapValueIntoRange(nRetVal, unNumber, c_range);
      return nRetVal;
#endif
   }
   
   /****************************************/
   /****************************************/

   UInt32 CARGoSRandom::CRNG::Uniform(const CRange<UInt32>& c_range) {
#ifndef CROSSCOMPILING
      UInt32 unRetVal;
      m_pcIntegerRNGRange->MapValueIntoRange(unRetVal, gsl_rng_get(m_ptRNG), c_range);
      return unRetVal;
#else
      UInt32 unNumber;
      random_r(m_ptRNG, reinterpret_cast<int32_t*>(&unNumber));
      UInt32 unRetVal;
      m_pcIntegerRNGRange->MapValueIntoRange(unRetVal, unNumber, c_range);
      return unRetVal;
#endif
   }
   
   /****************************************/
   /****************************************/

   Real CARGoSRandom::CRNG::Exponential(Real f_mean) {
#ifndef CROSSCOMPILING
      return gsl_ran_exponential(m_ptRNG, f_mean);
#else      
      CRange<Real> fRange(0.0f, 1.0f);
      return -log(Uniform(fRange)) / f_mean;
#endif
   }
   
   /****************************************/
   /****************************************/

   Real CARGoSRandom::CRNG::Gaussian(Real f_std_dev,
                                     Real f_mean) {
#ifndef CROSSCOMPILING
      return f_mean + gsl_ran_gaussian(m_ptRNG, f_std_dev);
#else
      /* This is the Box-Muller method in its cartesian variant
         see http://www.dspguru.com/dsp/howtos/how-to-generate-white-gaussian-noise
      */
      CRange<Real> fRange(-1.0f, 1.0f);
      Real fNum1, fNum2;
      Real fSquare;
      do {
         fNum1 = Uniform(fRange);
         fNum2 = Uniform(fRange);
         fSquare = fNum1 * fNum1 + fNum2 * fNum2;
      } while(fSquare >= 1);
      return f_mean + f_std_dev * fNum1;
#endif
   }

   /****************************************/
   /****************************************/

   CARGoSRandom::CCategory::CCategory(const std::string& str_id,
                                      UInt32 un_seed) :
      m_strId(str_id),
      m_unSeed(un_seed),
      m_cSeeder(un_seed),
      m_cSeedRange(1, std::numeric_limits<UInt32>::max()) {}

   /****************************************/
   /****************************************/

   CARGoSRandom::CCategory::CCategory(CByteArray& c_buffer) :
      m_unSeed(0),
      m_cSeeder(0),
      m_cSeedRange(1, std::numeric_limits<UInt32>::max()) {
      LoadState(c_buffer);
   }

   /****************************************/
   /****************************************/

   void CARGoSRandom::CCategory::SetSeed(UInt32 un_seed) {
      m_unSeed = un_seed;
      m_cSeeder.SetSeed(m_unSeed);
   }

   /****************************************/
   /****************************************/

   void CARGoSRandom::CCategory::SaveState(CByteArray& c_buffer) {
      /* Dump id */
      c_buffer << m_strId;
      /* Dump seed */
      c_buffer << m_unSeed;
      /* Dump number of RNG in this category */
      c_buffer << m_vecRNGList.size();
      /* Dump the state of each RNG */
      for(size_t i = 0; i < m_vecRNGList.size(); ++i) {
         m_vecRNGList[i]->SaveState(c_buffer);
      }
      /* Dump seeder */
      m_cSeeder.SaveState(c_buffer);
   }

   /****************************************/
   /****************************************/

   void CARGoSRandom::CCategory::LoadState(CByteArray& c_buffer) {
      /* Empty the RNG list */
      while(!m_vecRNGList.empty()) {
         delete m_vecRNGList.back();
         m_vecRNGList.pop_back();
      }
      /* Get id */
      c_buffer >> m_strId;
      /* Get seed */
      c_buffer >> m_unSeed;
      /* Get number of RNG in this category */
      size_t unRNGNum;
      c_buffer >> unRNGNum;
      /* Create new generators */
      for(size_t i = 0; i < unRNGNum; ++i) {
         m_vecRNGList.push_back(new CRNG(c_buffer));
      }
      /* Get seeder */
      m_cSeeder.LoadState(c_buffer);
   }

   /****************************************/
   /****************************************/

   CARGoSRandom::CRNG* CARGoSRandom::CCategory::CreateRNG(const std::string& str_type) {
      /* Get seed from internal RNG */
      UInt32 unSeed = m_cSeeder.Uniform(m_cSeedRange);
      /* Create new RNG */
      m_vecRNGList.push_back(new CRNG(unSeed, str_type));
      return m_vecRNGList.back();
   }

   /****************************************/
   /****************************************/

   void CARGoSRandom::CCategory::ResetRNGs() {
      /* Reset internal RNG */
      m_cSeeder.Reset();
      ReseedRNGs();
      /* Reset the RNGs */
      for(size_t i = 0; i < m_vecRNGList.size(); ++i) {
         m_vecRNGList[i]->Reset();
      }
   }

   /****************************************/
   /****************************************/

   void CARGoSRandom::CCategory::ReseedRNGs() {
      for(size_t i = 0; i < m_vecRNGList.size(); ++i) {
         /* Get seed from internal RNG */
         m_vecRNGList[i]->SetSeed(m_cSeeder.Uniform(m_cSeedRange));
      }
   }

   /****************************************/
   /****************************************/

   bool CARGoSRandom::CreateCategory(const std::string& str_category,
                                     UInt32 un_seed) {
      /* Is there a category already? */
      std::map<std::string, CCategory>::iterator itCategory = m_mapCategories.find(str_category);
      if(itCategory == m_mapCategories.end()) {
         /* No, create it */
         m_mapCategories.insert(
            std::pair<std::string,
                      CARGoSRandom::CCategory>(str_category,
                                               CARGoSRandom::CCategory(str_category,
                                                                       un_seed)));
         return true;
      }
      return false;
   }

   /****************************************/
   /****************************************/

   CARGoSRandom::CCategory& CARGoSRandom::GetCategory(const std::string& str_category) {
      CHECK_CATEGORY(str_category);
      return itCategory->second;
   }

   /****************************************/
   /****************************************/

   void CARGoSRandom::RemoveCategory(const std::string& str_category) {
      CHECK_CATEGORY(str_category);
      m_mapCategories.erase(itCategory);
   }

   /****************************************/
   /****************************************/

   CARGoSRandom::CRNG* CARGoSRandom::CreateRNG(const std::string& str_category,
                                               const std::string& str_type) {
      CHECK_CATEGORY(str_category);
      return itCategory->second.CreateRNG(str_type);
   }
   
   /****************************************/
   /****************************************/

   UInt32 CARGoSRandom::GetSeedOf(const std::string& str_category) {
      CHECK_CATEGORY(str_category);
      return itCategory->second.GetSeed();
   }

   /****************************************/
   /****************************************/

   void CARGoSRandom::SetSeedOf(const std::string& str_category,
                                UInt32 un_seed) {
      CHECK_CATEGORY(str_category);
      itCategory->second.SetSeed(un_seed);
   }

   /****************************************/
   /****************************************/

   void CARGoSRandom::SaveState(CByteArray& c_buffer) {
      /* Dump the number of categories */
      c_buffer << m_mapCategories.size();
      /* Dump the categories */
      for(std::map<std::string, CCategory>::iterator itCategory = m_mapCategories.begin();
          itCategory != m_mapCategories.end();
          ++itCategory) {
         itCategory->second.SaveState(c_buffer);
      }
   }

   /****************************************/
   /****************************************/

   void CARGoSRandom::LoadState(CByteArray& c_buffer) {
      /* Get the number of categories */
      size_t unCategories;
      c_buffer >> unCategories;
      /* Restore the categories */
      for(UInt32 i = 0; i < unCategories; ++i) {
         CCategory cCat(c_buffer);
         m_mapCategories.insert(
            std::pair<std::string, CARGoSRandom::CCategory>(cCat.GetId(), cCat));
      }
   }

   /****************************************/
   /****************************************/

   void CARGoSRandom::Reset() {
      for(std::map<std::string, CCategory>::iterator itCategory = m_mapCategories.begin();
          itCategory != m_mapCategories.end();
          ++itCategory) {
         itCategory->second.ResetRNGs();
      }
   }

   /****************************************/
   /****************************************/

}
