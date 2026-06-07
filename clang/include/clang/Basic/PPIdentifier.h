//===--- PPIdentifier.h - PP extension names header -------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Defines functions to mangle, identify and demangle PP extension identifier
/// names.
///
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_BASIC_PPIDENTIFIER_H
#define LLVM_CLANG_BASIC_PPIDENTIFIER_H

#include <charconv>
#include <optional>
#include <sstream>

#include "clang/Basic/LLVM.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/Twine.h"
#include "llvm/Support/ErrorHandling.h"

namespace clang {

//===----------------------------------------------------------------------===//
// Name prefixes
//===----------------------------------------------------------------------===//

inline constexpr llvm::StringLiteral kPPMMIdentifierPrefix = "__pp_mm_";
inline constexpr llvm::StringLiteral kPPMMArrayIdentifierPrefix =
    "__pp_mminitarr_";
inline constexpr llvm::StringLiteral kPPStructIdentifierPrefix = "__pp_struct_";
inline constexpr llvm::StringLiteral kPPTagIdentifierPrefix = "__pp_tag_";
inline constexpr llvm::StringLiteral kPPTagsIdentifierPrefix = "__pp_tags_";
inline constexpr llvm::StringLiteral kPPIncTagsIdentifierPrefix =
    "__pp_inc_tags_";
inline constexpr llvm::StringLiteral kPPGvInitPrefix = "__pp_gvinit__";
inline constexpr llvm::StringLiteral kPPDefaultPrefix = "__pp_default";
inline constexpr llvm::StringLiteral kPPRecordPrefix = "__pp_record";
inline constexpr llvm::StringLiteral kPPRecordCSPrefix = "__pp_record_cs_";
inline constexpr llvm::StringLiteral kPPInitPrefix = "__pp_init_";
inline constexpr llvm::StringLiteral kPPInitCSArrPrefix = "__pp_init_cs_arr_";
inline constexpr llvm::StringLiteral kPPCSArrPrefix = "__pp_cs_arr_";
inline constexpr llvm::StringLiteral kPPAllocPrefix = "__pp_alloc";
inline constexpr llvm::StringLiteral kPPGeneralPrefix = "__pp_";
inline constexpr llvm::StringLiteral kPPSpecSuffix = "__pp_spec";
inline constexpr llvm::StringLiteral kPPPtrSuffix = "_pp_ptr";

//===----------------------------------------------------------------------===//
// Field names
//===----------------------------------------------------------------------===//

inline constexpr llvm::StringLiteral kPPHeadFieldName = "__pp_head";
inline constexpr llvm::StringLiteral kPPTailFieldName = "__pp_tail";
inline constexpr llvm::StringLiteral kPPSpecTypeFieldName =
    "__pp_specialization_type";

//===----------------------------------------------------------------------===//
// Runtime function names (bare, without struct suffix)
//===----------------------------------------------------------------------===//

inline constexpr llvm::StringLiteral kPPCreateSpecName = "create_spec";
inline constexpr llvm::StringLiteral kPPGetSpecPtrName = "get_spec_ptr";
inline constexpr llvm::StringLiteral kPPGetSpecSizeName = "get_spec_size";
inline constexpr llvm::StringLiteral kPPSpecIndexCmpName = "spec_index_cmp";
inline constexpr llvm::StringLiteral kPPInitSpecName = "init_spec";

//===----------------------------------------------------------------------===//
// Spec function kind enum
//===----------------------------------------------------------------------===//

enum class PPSpecFuncKind {
  CreateSpec,
  GetSpecPtr,
  GetSpecSize,
  SpecIndexCmp,
  InitSpec
};

/// Lookup table pairing each spec function name with its kind.
/// Used by all spec function query/mangle/demangle helpers below.
inline constexpr std::pair<llvm::StringLiteral, PPSpecFuncKind>
    kPPSpecFuncDescs[] = {
        {kPPCreateSpecName, PPSpecFuncKind::CreateSpec},
        {kPPGetSpecPtrName, PPSpecFuncKind::GetSpecPtr},
        {kPPGetSpecSizeName, PPSpecFuncKind::GetSpecSize},
        {kPPSpecIndexCmpName, PPSpecFuncKind::SpecIndexCmp},
        {kPPInitSpecName, PPSpecFuncKind::InitSpec},
};

/// Return the kind for an exact spec function name match.
/// Returns std::nullopt if Name is not a PP spec function.
inline std::optional<PPSpecFuncKind> GetPPSpecFuncKind(StringRef Name) {
  for (auto [SpecName, Kind] : kPPSpecFuncDescs)
    if (Name == SpecName)
      return Kind;
  return std::nullopt;
}

//===----------------------------------------------------------------------===//
// Detection predicates
//===----------------------------------------------------------------------===//

inline bool IsPPMMIdentifier(StringRef Name) {
  return Name.starts_with(kPPMMIdentifierPrefix);
}
inline bool IsPPMMArrayIdentifier(StringRef Name) {
  return Name.starts_with(kPPMMArrayIdentifierPrefix);
}
inline bool IsPPStructIdentifier(StringRef Name) {
  return Name.starts_with(kPPStructIdentifierPrefix);
}
inline bool IsPPIncTagsIdentifier(StringRef Name) {
  return Name.starts_with(kPPIncTagsIdentifierPrefix);
}
inline bool IsPPGvInitIdentifier(StringRef Name) {
  return Name.starts_with(kPPGvInitPrefix);
}
inline bool IsPPDefaultHandler(StringRef Name) {
  return Name.starts_with(kPPDefaultPrefix);
}
inline bool IsPPGeneralIdentifier(StringRef Name) {
  return Name.starts_with(kPPGeneralPrefix);
}

/// Exact match check — is Name exactly one of the spec function names?
inline bool IsPPSpecFunctionToken(StringRef Name) {
  return GetPPSpecFuncKind(Name).has_value();
}

/// Prefix check — does Name start with one of the spec function names?
inline bool IsPPSpecFunctionIdentifier(StringRef Name) {
  for (auto [SpecName, _] : kPPSpecFuncDescs)
    if (Name.starts_with(SpecName))
      return true;
  return false;
}

/// True if the name denotes a PP struct specialization (has a variant suffix).
/// "__pp_struct_Figure__Circle" -> true
/// "__pp_struct_Figure" -> false
inline bool IsPPStructSpecialization(StringRef StructName) {
  if (!IsPPStructIdentifier(StructName))
    return false;
  StringRef Body = StructName.substr(kPPStructIdentifierPrefix.size());
  return Body.find("__") != StringRef::npos;
}

//===----------------------------------------------------------------------===//
// Mangle (build names from parts)
//===----------------------------------------------------------------------===//

/// Mangle a multimethod identifier from its base name and parameter count.
/// "PrintFigure", 3 -> "__pp_mm_3_PrintFigure"
inline std::string ManglePPMM(StringRef Name, unsigned Arity) {
  std::stringstream Ss;
  Ss << std::string_view(kPPMMIdentifierPrefix) << Arity << "_"
     << std::string_view(Name);
  return std::move(Ss).str();
}

/// Mangle the init array name for a multimethod given its full MM name.
/// "__pp_mm_1_zzz" -> "__pp_mminitarr___pp_mm_1_zzz"
inline std::string ManglePPMMInitArray(StringRef MMName) {
  return (Twine(kPPMMArrayIdentifierPrefix) + MMName).str();
}

/// Mangle a PP struct name from a generalization base and optional variant.
/// Base-only ("Figure") -> "__pp_struct_Figure"
/// Base + variant ("Figure", "Circle") -> "__pp_struct_Figure__Circle"
/// With IsPtr, appends "_pp_ptr": "__pp_struct_Figure__Circle_pp_ptr"
/// With AddPrefix=false, omits the "__pp_struct_" prefix.
inline std::string ManglePPStruct(StringRef Base, StringRef Variant = "",
                                  bool IsPtr = false, bool AddPrefix = true) {
  std::stringstream Ss;
  if (AddPrefix) {
    Ss << std::string_view(kPPStructIdentifierPrefix);
  }
  Ss << std::string_view(Base);
  if (!Variant.empty()) {
    Ss << "__" << std::string_view(Variant);
    if (IsPtr) {
      Ss << std::string_view(kPPPtrSuffix);
    }
  }
  return std::move(Ss).str();
}

inline std::string ManglePPTag(StringRef StructName) {
  return (Twine(kPPTagIdentifierPrefix) + StructName).str();
}

inline std::string ManglePPTags(StringRef GenName) {
  return (Twine(kPPTagsIdentifierPrefix) + GenName).str();
}

inline std::string ManglePPIncTags(StringRef GenName) {
  return (Twine(kPPIncTagsIdentifierPrefix) + GenName).str();
}

inline std::string ManglePPGvInit(StringRef VarName) {
  return (Twine(kPPGvInitPrefix) + VarName).str();
}

inline std::string ManglePPCSArr(StringRef Name) {
  return (Twine(kPPCSArrPrefix) + Name).str();
}

inline std::string ManglePPInitCSArr(StringRef GenName) {
  return (Twine(kPPInitCSArrPrefix) + GenName).str();
}

inline std::string ManglePPInit(StringRef Name) {
  return (Twine(kPPInitPrefix) + Name).str();
}

inline std::string ManglePPAlloc(StringRef Name) {
  return (Twine(kPPAllocPrefix) + Name).str();
}

inline std::string ManglePPDefaultHandler(StringRef FnName) {
  return (Twine(kPPDefaultPrefix) + FnName).str();
}

inline std::string ManglePPRecord(StringRef FnName) {
  return (Twine(kPPRecordPrefix) + FnName).str();
}

inline std::string ManglePPRecordCS(StringRef SpecName) {
  return (Twine(kPPRecordCSPrefix) + SpecName).str();
}

/// Mangle a spec function name with a struct suffix.
/// e.g. ManglePPSpecFunction(PPSpecFuncKind::CreateSpec, "Foo")
///        -> "create_specFoo"
inline std::string ManglePPSpecFunction(PPSpecFuncKind Kind,
                                        StringRef StructName) {
  for (auto [SpecName, K] : kPPSpecFuncDescs) {
    if (K == Kind)
      return (Twine(SpecName) + StructName).str();
  }
  llvm_unreachable("invalid PP spec function kind");
}

/// Describes one specialization argument for a PP multimethod.
struct PPSpecArg {
  StringRef TypeName;
  bool IsGenAsSpec = false;
};

/// Mangle a specialized multimethod name. Appends each specialization
/// argument's type name (with "__0" prefix for GenAsSpec parameters),
/// followed by the "__pp_spec" suffix.
/// "__pp_mm_1_zzz", [{"__pp_struct_xxx__yyy", false}]
///   -> "__pp_mm_1_zzz__pp_struct_xxx__yyy__pp_spec"
template <typename Range>
std::string ManglePPMMSpecialization(StringRef BaseMMName,
                                     const Range &SpecArgs) {
  std::stringstream Ss;
  Ss << std::string_view(BaseMMName);
  for (const auto &Arg : SpecArgs) {
    if (Arg.IsGenAsSpec)
      Ss << "__0";
    Ss << std::string_view(Arg.TypeName);
  }
  Ss << std::string_view(kPPSpecSuffix);
  return std::move(Ss).str();
}

//===----------------------------------------------------------------------===//
// Demangle (extract parts from mangled names)
//===----------------------------------------------------------------------===//

/// PP-EXT TODO: remove demanlging in favor of storing/retrieving information
/// from declarations directly, if possible

/// Demangle a multimethod identifier: extract base name and parameter count.
/// "__pp_mm_3_PrintFigure" -> {"PrintFigure", 3}
/// Does NOT strip specialization suffixes (use DemanglePPMMSpecialization).
inline std::pair<StringRef, unsigned> DemanglePPMM(StringRef Mangled) {
  assert(IsPPMMIdentifier(Mangled));
  Mangled = Mangled.substr(kPPMMIdentifierPrefix.size());
  size_t Pos = Mangled.find("_");
  assert(Pos != std::string::npos);
  auto ArityStr = Mangled.substr(0, Pos);
  unsigned Arity;
  auto [_, EC] = std::from_chars(ArityStr.begin(), ArityStr.end(), Arity);
  assert(EC == std::errc{});
  return std::make_pair(Mangled.substr(Pos + 1), Arity);
}

/// Demangle a specialized multimethod name back to base (name, arity).
/// Reconstructs the suffix from SpecArgs, strips it + "__pp_spec",
/// then demangles the remaining base MM identifier.
template <typename Range>
std::pair<StringRef, unsigned>
DemanglePPMMSpecialization(StringRef Mangled, const Range &SpecArgs) {
  std::stringstream Suffix;
  for (const auto &Arg : SpecArgs) {
    if (Arg.IsGenAsSpec)
      Suffix << "__0";
    Suffix << std::string_view(Arg.TypeName);
  }
  Suffix << std::string_view(kPPSpecSuffix);
  std::string SuffixStr = std::move(Suffix).str();
  assert(Mangled.ends_with(SuffixStr));
  return DemanglePPMM(Mangled.substr(0, Mangled.size() - SuffixStr.size()));
}

/// Strip the "__pp_struct_" prefix from a mangled struct name. Returns the base
/// name.
/// "__pp_struct_Figure" -> "Figure"
/// "__pp_struct_Figure__Circle" -> "Figure__Circle"
inline StringRef DemanglePPStruct(StringRef Mangled) {
  assert(IsPPStructIdentifier(Mangled));
  return Mangled.substr(kPPStructIdentifierPrefix.size());
}

/// Demangle a specialization struct name into {generalization, variant}.
/// "__pp_struct_Figure__Circle" -> {"Figure", "Circle"}
inline std::pair<StringRef, StringRef>
DemanglePPStructSpecialization(StringRef Mangled) {
  assert(IsPPStructSpecialization(Mangled));
  StringRef Body = DemanglePPStruct(Mangled);
  auto Pos = Body.find("__");
  return {Body.substr(0, Pos), Body.substr(Pos + 2)};
}

inline StringRef DemanglePPTag(StringRef Mangled) {
  assert(Mangled.starts_with(kPPTagIdentifierPrefix));
  return Mangled.substr(kPPTagIdentifierPrefix.size());
}

inline StringRef DemanglePPTags(StringRef Mangled) {
  assert(Mangled.starts_with(kPPTagsIdentifierPrefix));
  return Mangled.substr(kPPTagsIdentifierPrefix.size());
}

inline StringRef DemanglePPIncTags(StringRef Mangled) {
  assert(IsPPIncTagsIdentifier(Mangled));
  return Mangled.substr(kPPIncTagsIdentifierPrefix.size());
}

inline StringRef DemanglePPDefaultHandler(StringRef Mangled) {
  assert(IsPPDefaultHandler(Mangled));
  return Mangled.substr(kPPDefaultPrefix.size());
}

/// Demangle a spec function like "create_specFoo" into {Kind, StructName}.
inline std::pair<PPSpecFuncKind, StringRef>
DemanglePPSpecFunction(StringRef Mangled) {
  for (auto [SpecName, Kind] : kPPSpecFuncDescs) {
    if (Mangled.starts_with(SpecName))
      return {Kind, Mangled.substr(SpecName.size())};
  }
  llvm_unreachable("not a PP spec function name");
}

} // namespace clang

#endif
