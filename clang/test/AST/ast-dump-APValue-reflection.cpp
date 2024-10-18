// Test without serialization:
// RUN: %clang_cc1 -triple x86_64-unknown-unknown -Wno-unused-value -std=c++26 \
// RUN:            -freflection -freflection-new-syntax \
// RUN:            -ast-dump %s -ast-dump-filter Test \
// RUN: | FileCheck --strict-whitespace --match-full-lines %s

void Test() {
  constexpr auto reflint = ^^int;
  // CHECK:  | `-VarDecl 0xd355e00 <col:3, col:23> col:18 v 'const meta::info' constexpr cinit
  // CHECK-NEXT:  |   |-value: Reflection <todo>
  // CHECK-NEXT:  |   `-CXXReflectExpr 0xd357800 <col:22, col:23> 'meta::info'

  constexpr auto refltokens = ^^{ += 5 };
  // CHECK:  | `-VarDecl 0xd355e00 <col:3, col:23> col:18 v 'const meta::info' constexpr cinit
  // CHECK-NEXT:  |   |-value: Reflection <todo>
  // CHECK-NEXT:  |   `-CXXReflectExpr 0xd357800 <col:22, col:23> 'meta::info'
}