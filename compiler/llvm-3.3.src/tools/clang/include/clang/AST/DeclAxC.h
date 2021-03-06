//==============================================================================
//Copyright (c) 2013 Intel Corporation.
//All rights reserved.
//==============================================================================
//
//Developed by:
//
//    Programming Systems Lab, Intel Labs
//
//    Intel Corporation
//
//    http://www.intel.com
//
//Permission is hereby granted, free of charge, to any person obtaining a copy of
//this software and associated documentation files (the "Software"), to deal with
//the Software without restriction, including without limitation the rights to
//use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
//of the Software, and to permit persons to whom the Software is furnished to do
//so, subject to the following conditions:
//
//    * Redistributions of source code must retain the above copyright notice,
//      this list of conditions and the following disclaimers.
//
//    * Redistributions in binary form must reproduce the above copyright notice,
//      this list of conditions and the following disclaimers in the
//      documentation and/or other materials provided with the distribution.
//
//    * Neither the names of the LLVM Team, University of Illinois at
//      Urbana-Champaign, nor the names of its contributors may be used to
//      endorse or promote products derived from this Software without specific
//      prior written permission.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
//FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
//CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS WITH THE
//SOFTWARE.
//==============================================================================


#ifndef LLVM_CLANG_AST_AXC_H
#define LLVM_CLANG_AST_AXC_H

#include "clang/AST/DeclBase.h"
#include "llvm/ADT/ArrayRef.h"

namespace clang {

  struct InEntry {
    // We just use a sentinel to represent when the stack is set to mac68k
    // alignment.
    static const unsigned kMac68kAlignmentSentinel = ~0U;

    unsigned ArgNum;
    float errorBound;
  };

  struct OutEntry {
    // We just use a sentinel to represent when the stack is set to mac68k
    // alignment.
    static const unsigned kMac68kAlignmentSentinel = ~0U;

    unsigned ArgNum;
  };

  /// Raj AxCInfo - Simple class to wrap the AxC data
  class AxCInfo {
    typedef std::vector<InEntry> in_ty;
	typedef std::vector<OutEntry> out_ty;
    
    /// in and out vectors to hold entries in the #pragma memoize stack
    
  public:
	in_ty In;
	out_ty Out;

    AxCInfo() { In.clear(); Out.clear();}

    /// insert - Push the current arg and error 
    void insert(unsigned ArgNum, float ErrorBound) {
      InEntry IE = { ArgNum, ErrorBound };
      In.push_back(IE);
    }

	/// insert the current out arg 
    void insert(unsigned ArgNum) {
      OutEntry OE = { ArgNum};
      Out.push_back(OE);
    }

	bool empty() {
		return In.empty() || Out.empty();
	}
  };
}  // end namespace clang

#endif
