// RUN: maki %s -fplugin-arg-maki---no-system-macros -fplugin-arg-maki---no-builtin-macros -fplugin-arg-maki---no-invalid-macros | jq 'sort_by(.Kind, .DefinitionLocation, .InvocationLocation)' | FileCheck %s --color

#define ZERO 0
typedef struct foo {
#define ONE 1
} foo;

typedef union bar {
#define TWO 2
// COM: This #include'd definition of EIGHT is not at the global scope
#include "eight.h"
} bar;

int baz =
#define THREE 3
    0;

int main(void) {
#define FOUR 4
    return 0;
}
#define FIVE 5

struct A {
    int a;
    int b;
// Declared inside struct. Direction translation to variable or enum will break
// program.
#define C 10
};

// COM: This separate definition of EIGHT is at the global scope
#include "eight.h"

// CHECK: [
// CHECK:   {
// CHECK:     "Kind": "Definition",
// CHECK:     "Name": "THREE",
// CHECK:     "IsObjectLike": true,
// CHECK:     "IsDefinitionLocationValid": true,
// CHECK:     "Body": "3",
// CHECK:     "IsDefinedAtGlobalScope": false,
// CHECK:     "DefinitionLocation": "{{.*}}/Tests/define_at_non_global_scope.c:15:9",
// CHECK:     "EndDefinitionLocation": "{{.*}}/Tests/define_at_non_global_scope.c:15:16"
// CHECK:   },
// CHECK:   {
// CHECK:     "Kind": "Definition",
// CHECK:     "Name": "FOUR",
// CHECK:     "IsObjectLike": true,
// CHECK:     "IsDefinitionLocationValid": true,
// CHECK:     "Body": "4",
// CHECK:     "IsDefinedAtGlobalScope": false,
// CHECK:     "DefinitionLocation": "{{.*}}/Tests/define_at_non_global_scope.c:19:9",
// CHECK:     "EndDefinitionLocation": "{{.*}}/Tests/define_at_non_global_scope.c:19:15"
// CHECK:   },
// CHECK:   {
// CHECK:     "Kind": "Definition",
// CHECK:     "Name": "FIVE",
// CHECK:     "IsObjectLike": true,
// CHECK:     "IsDefinitionLocationValid": true,
// CHECK:     "Body": "5",
// CHECK:     "IsDefinedAtGlobalScope": true,
// CHECK:     "DefinitionLocation": "{{.*}}/Tests/define_at_non_global_scope.c:22:9",
// CHECK:     "EndDefinitionLocation": "{{.*}}/Tests/define_at_non_global_scope.c:22:15"
// CHECK:   },
// CHECK:   {
// CHECK:     "Kind": "Definition",
// CHECK:     "Name": "C",
// CHECK:     "IsObjectLike": true,
// CHECK:     "IsDefinitionLocationValid": true,
// CHECK:     "Body": "10",
// CHECK:     "IsDefinedAtGlobalScope": false,
// CHECK:     "DefinitionLocation": "{{.*}}/Tests/define_at_non_global_scope.c:29:9",
// CHECK:     "EndDefinitionLocation": "{{.*}}/Tests/define_at_non_global_scope.c:29:13"
// CHECK:   },
// CHECK:   {
// CHECK:     "Kind": "Definition",
// CHECK:     "Name": "ZERO",
// CHECK:     "IsObjectLike": true,
// CHECK:     "IsDefinitionLocationValid": true,
// CHECK:     "Body": "0",
// CHECK:     "IsDefinedAtGlobalScope": true,
// CHECK:     "DefinitionLocation": "{{.*}}/Tests/define_at_non_global_scope.c:3:9",
// CHECK:     "EndDefinitionLocation": "{{.*}}/Tests/define_at_non_global_scope.c:3:15"
// CHECK:   },
// CHECK:   {
// CHECK:     "Kind": "Definition",
// CHECK:     "Name": "ONE",
// CHECK:     "IsObjectLike": true,
// CHECK:     "IsDefinitionLocationValid": true,
// CHECK:     "Body": "1",
// CHECK:     "IsDefinedAtGlobalScope": false,
// CHECK:     "DefinitionLocation": "{{.*}}/Tests/define_at_non_global_scope.c:5:9",
// CHECK:     "EndDefinitionLocation": "{{.*}}/Tests/define_at_non_global_scope.c:5:14"
// CHECK:   },
// CHECK:   {
// CHECK:     "Kind": "Definition",
// CHECK:     "Name": "TWO",
// CHECK:     "IsObjectLike": true,
// CHECK:     "IsDefinitionLocationValid": true,
// CHECK:     "Body": "2",
// CHECK:     "IsDefinedAtGlobalScope": false,
// CHECK:     "DefinitionLocation": "{{.*}}/Tests/define_at_non_global_scope.c:9:9",
// CHECK:     "EndDefinitionLocation": "{{.*}}/Tests/define_at_non_global_scope.c:9:14"
// CHECK:   },
// CHECK:   {
// CHECK:     "Kind": "Definition",
// CHECK:     "Name": "EIGHT",
// CHECK:     "IsObjectLike": true,
// CHECK:     "IsDefinitionLocationValid": true,
// CHECK:     "Body": "8",
// CHECK:     "IsDefinedAtGlobalScope": false,
// CHECK:     "DefinitionLocation": "{{.*}}/Tests/eight.h:2:9",
// CHECK:     "EndDefinitionLocation": "{{.*}}/Tests/eight.h:2:16"
// CHECK:   },
// CHECK:   {
// CHECK:     "Kind": "Definition",
// CHECK:     "Name": "EIGHT",
// CHECK:     "IsObjectLike": true,
// CHECK:     "IsDefinitionLocationValid": true,
// CHECK:     "Body": "8",
// CHECK:     "IsDefinedAtGlobalScope": true,
// CHECK:     "DefinitionLocation": "{{.*}}/Tests/eight.h:2:9",
// CHECK:     "EndDefinitionLocation": "{{.*}}/Tests/eight.h:2:16"
// CHECK:   },
// CHECK:   {
// CHECK:     "Kind": "Include",
// CHECK:     "IsValid": false,
// CHECK:     "IncludeName": "{{.*}}/Tests/eight.h"
// CHECK:   },
// CHECK:   {
// CHECK:     "Kind": "Include",
// CHECK:     "IsValid": true,
// CHECK:     "IncludeName": "{{.*}}/Tests/eight.h"
// CHECK:   }
// CHECK: ]