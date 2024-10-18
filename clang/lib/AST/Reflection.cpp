//===--- Reflection.cpp - Classes for representing reflection ---*- C++ -*-===//
//
// Copyright 2024 Bloomberg Finance L.P.
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
//  This file implements the ReflectionValue class.
//
//===----------------------------------------------------------------------===//

#include "clang/AST/Reflection.h"
#include "clang/AST/ASTContext.h"

namespace clang {

bool TagDataMemberSpec::operator==(TagDataMemberSpec const &Rhs) const {
  return (Ty == Rhs.Ty &&
          Alignment == Rhs.Alignment &&
          BitWidth == Rhs.BitWidth &&
          Name == Rhs.Name);
}

bool TagDataMemberSpec::operator!=(TagDataMemberSpec const &Rhs) const {
  return !(*this == Rhs);
}

TokenSequenceStorage::TokenSequenceStorage(ArrayRef<Token> Tokens) {
  NumTokens = (unsigned)Tokens.size();
  for (unsigned I = 0; I < NumTokens; ++I) {
    auto &Storage = *new ((void *)(getTrailingObjects<TokenInfoStorage>() + I))
                        TokenInfoStorage;
    new ((Token *)(char *)&Storage.Tok) Token(Tokens[I]);
  }
}

TokenSequenceStorage *TokenSequenceStorage::Create(const ASTContext &Ctx,
                                                   ArrayRef<Token> Tokens) {
  // TODO(dhollman) figure out whether this should be allocated with new or in
  // the ASTContext
  void *Result =
      Ctx.Allocate(totalSizeToAlloc<TokenInfoStorage>(Tokens.size()));
  return new (Result) TokenSequenceStorage(Tokens);
}

ArrayRef<TokenInfoStorage> TokenSequenceStorage::getTokens() const {
  return {getTrailingObjects<TokenInfoStorage>(), NumTokens};
}

} // end namespace clang
