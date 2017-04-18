/*
 * Copyright (c) 2017 Trail of Bits, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef REMILL_BC_COMPAT_TARGETLIBRARYINFO_H_
#define REMILL_BC_COMPAT_TARGETLIBRARYINFO_H_

#include "remill/BC/Version.h"

#if LLVM_VERSION_NUMBER >= LLVM_VERSION(3, 7)
# include <llvm/Analysis/TargetLibraryInfo.h>
#else
# include <llvm/Target/TargetLibraryInfo.h>

namespace llvm {

class TargetLibraryInfoImpl : public TargetLibraryInfo {
 public:
  bool DisableTailCalls;
  bool DisableUnitAtATime;
  bool DisableUnrollLoops;
  bool BBVectorize;
  bool SLPVectorize;
  bool LoopVectorize;
  bool RerollLoops;
  bool LoadCombine;
  bool DisableGVNLoadPRE;
  bool VerifyInput;
  bool VerifyOutput;
  bool MergeFunctions;
  bool PrepareForLTO;

  template <typename T>
  inline void populateFunctionPassManager(T &) { }
};

using TargetLibraryInfoImpl = TargetLibraryInfo;

}  // namespace llvm

#endif

#endif  // REMILL_BC_COMPAT_TARGETLIBRARYINFO_H_