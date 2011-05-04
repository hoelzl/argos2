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
 * @file <common/utility_classes/argos_random.h>
 *
 * @brief This file provides the definition of the random number generator of ARGoS.
 *
 * This file provides the definition of the random number generator of ARGoS. It is
 * meant to be used not only inside ARGoS, but also from controllers, loop functions
 * as well as external applications.
 *
 * In general, RNGs have the greatest impact on the reproducibility of experiments.
 * However, once the random seed has been set, the series of random numbers generated
 * by RNG is fixed. In this way, experiments are reproducible.
 * To further complicate things, ARGoS is a multi-thread program. Multi-threading and
 * RNG create issues to reproducibility. In fact, if the RNG were shared among the
 * threads, it would be impossible to predict the order in which the RNG are accessed,
 * because thread scheduling is not controllable nor predictable.
 * For this reason, a common solution is to assign a separated RNG to each thread. For
 * ARGoS, this is not a viable method because we want the number of threads to be
 * set by the user and we want the outcome of an experiment to be reproducible no matter
 * how many threads are used.
 *
 * All these considerations brought us to the design of a RNG with a different approach.
 * The class CARGoSRandom is a static factory that creates RNG objects. Every time a
 * component (sensor, actuator, controller, etc.) needs to create random numbers, it
 * has to first create a local RNG class. Internally, the factory assigns a seed to it.
 *
 * To allow for usage from different components (such as ARGoS main code, an evolutionary
 * algorithm, controllers, etc.) RNGs are divided up in categories. The ARGoS core uses
 * the "argos" category, so if you reset it you just affect the simulator, but not the
 * other components. In other words, categories give the user complete power on the
 * RNGs, while ensuring compartmentalization.
 *
 * In practice, when you want to use random numbers with a custom category you need to
 * first call the function providing a label for the category and a base seed:
 *
 * CARGoSRandom::CreateCategory("my_category", my_seed);
 *
 * Once the category is created, you can get a new RNG with a call to the function
 *
 * CARGoSRandom::CreateRNG("my_category");
 *
 * The CARGoSRandom::CRNG allows one to get random numbers with the wanted distributions.
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef ARGOS_RANDOM
#define ARGOS_RANDOM

namespace argos {
   class CARGoSRandom;
}

#include <argos2/common/utility/configuration/memento.h>
#include <argos2/common/utility/math/range.h>
#include <map>

#ifndef CROSSCOMPILING
#   include <gsl/gsl_rng.h>
#else
#   include <cstdlib>
#endif

namespace argos {

   class CARGoSRandom {

   public:

      class CRNG : public CMemento {

      public:

         CRNG(UInt32 un_seed,
              const std::string& str_type = "mt19937");
         CRNG(CByteArray& c_buffer);
         CRNG(const CRNG& c_rng);
         virtual ~CRNG();

         inline UInt32 GetSeed() const {
            return m_unSeed;
         }

         inline void SetSeed(UInt32 un_seed) {
            m_unSeed = un_seed;
         }

         inline std::string GetType() const {
            return m_strType;
         }

         inline void SetType(const std::string& str_type) {
            m_strType = str_type;
         }

         virtual void SaveState(CByteArray& c_buffer);
         virtual void LoadState(CByteArray& c_buffer);

         void Reset();

         bool Bernoulli(Real f_true = 0.5);
         Real Uniform(const CRange<Real>& c_range);
         SInt32 Uniform(const CRange<SInt32>& c_range);
         UInt32 Uniform(const CRange<UInt32>& c_range);
         Real Exponential(Real f_mean);
         Real Gaussian(Real f_std_dev, Real f_mean = 0.0f);

      private:

         void CreateRNG();
         void DisposeRNG();

      private:

         UInt32 m_unSeed;
         std::string m_strType;
#ifndef CROSSCOMPILING
         gsl_rng* m_ptRNG;
#else
         random_data* m_ptRNG;
         char* m_pchRNGState;
#endif
         CRange<UInt32>* m_pcIntegerRNGRange;

      };

      class CCategory : public CMemento {

      public:

         CCategory(const std::string& str_id,
                   UInt32 un_seed);
         CCategory(CByteArray& c_buffer);
         virtual ~CCategory() {}

         inline const std::string& GetId() const {
            return m_strId;
         }
         void SetId(const std::string& str_id) {
            m_strId = str_id;
         }

         inline UInt32 GetSeed() const {
            return m_unSeed;
         }
         void SetSeed(UInt32 un_seed);

         virtual void SaveState(CByteArray& c_buffer);
         virtual void LoadState(CByteArray& c_buffer);

         CRNG* CreateRNG(const std::string& str_type = "mt19937");

         void ResetRNGs();

         void ReseedRNGs();

      private:

         std::string m_strId;
         std::vector<CRNG*> m_vecRNGList;
         UInt32 m_unSeed;
         CRNG m_cSeeder;
         CRange<UInt32> m_cSeedRange;
      };

   public:

      static bool CreateCategory(const std::string& str_category,
                                 UInt32 un_seed);
      static CCategory& GetCategory(const std::string& str_category);
      static void RemoveCategory(const std::string& str_category);

      static CRNG* CreateRNG(const std::string& str_category,
                             const std::string& str_type = "mt19937");

      static UInt32 GetSeedOf(const std::string& str_category);
      static void SetSeedOf(const std::string& str_category,
                            UInt32 un_seed);

      static void SaveState(CByteArray& c_buffer);
      static void LoadState(CByteArray& c_buffer);

      static void Reset();

#ifndef CROSSCOMPILING
      inline static const gsl_rng_type** GetRNGTypes() {
         return m_pptRNGTypes;
      }
#endif

   private:

      static std::map<std::string, CCategory> m_mapCategories;
#ifndef CROSSCOMPILING
      static const gsl_rng_type** m_pptRNGTypes;
#endif

   };

}

#endif
