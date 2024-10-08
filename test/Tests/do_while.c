// RUN: maki %s -fplugin-arg-maki---no-system-macros -fplugin-arg-maki---no-builtin-macros -fplugin-arg-maki---no-invalid-macros | jq 'sort_by(.Kind, .DefinitionLocation, .InvocationLocation)' | FileCheck %s --color
#define SKIP_SPACES(p, limit)  \
    do {                       \
        char *lim = (limit);   \
        while (p < lim) {      \
            if (*p++ != ' ') { \
                p--;           \
                break;         \
            }                  \
        }                      \
    } while (0)
int main(int argc, char const *argv[]) {
    char *goal = "FSE 23'";
    SKIP_SPACES(goal, (goal + 4));
    return 0;
}

// CHECK: [
// CHECK:   {
// CHECK:     "Kind": "Definition",
// CHECK:     "Name": "SKIP_SPACES",
// CHECK:     "IsObjectLike": false,
// CHECK:     "IsDefinitionLocationValid": true,
// CHECK:     "Body": "do { char * lim = ( limit ) ; while ( p < lim ) { if ( * p ++ != ' ' ) { p -- ; break ; } } } while ( 0 )",
// CHECK:     "IsDefinedAtGlobalScope": true,
// CHECK:     "DefinitionLocation": "{{.*}}/Tests/do_while.c:2:9",
// CHECK:     "EndDefinitionLocation": "{{.*}}/Tests/do_while.c:11:16"
// CHECK:   },
// CHECK:   {
// CHECK:     "Kind": "Invocation",
// CHECK:     "Name": "SKIP_SPACES",
// CHECK:     "DefinitionLocation": "{{.*}}/Tests/do_while.c:2:9",
// CHECK:     "InvocationLocation": "{{.*}}/Tests/do_while.c:14:5",
// CHECK:     "ASTKind": "Stmt",
// CHECK:     "TypeSignature": "void SKIP_SPACES(char * p, char * limit)",
// CHECK:     "InvocationDepth": 0,
// CHECK:     "NumASTRoots": 1,
// CHECK:     "NumArguments": 2,
// CHECK:     "HasStringification": false,
// CHECK:     "HasTokenPasting": false,
// CHECK:     "HasAlignedArguments": true,
// CHECK:     "HasSameNameAsOtherDeclaration": false,
// CHECK:     "IsExpansionControlFlowStmt": true,
// CHECK:     "DoesBodyReferenceMacroDefinedAfterMacro": false,
// CHECK:     "DoesBodyReferenceDeclDeclaredAfterMacro": true,
// CHECK:     "DoesBodyContainDeclRefExpr": true,
// CHECK:     "DoesSubexpressionExpandedFromBodyHaveLocalType": false,
// CHECK:     "DoesSubexpressionExpandedFromBodyHaveTypeDefinedAfterMacro": false,
// CHECK:     "DoesAnyArgumentHaveSideEffects": false,
// CHECK:     "DoesAnyArgumentContainDeclRefExpr": true,
// CHECK:     "IsHygienic": true,
// CHECK:     "IsICERepresentableByInt16": false,
// CHECK:     "IsICERepresentableByInt32": false,
// CHECK:     "IsDefinitionLocationValid": true,
// CHECK:     "IsInvocationLocationValid": true,
// CHECK:     "IsObjectLike": false,
// CHECK:     "IsInvokedInMacroArgument": false,
// CHECK:     "IsNamePresentInCPPConditional": false,
// CHECK:     "IsExpansionICE": false,
// CHECK:     "IsExpansionTypeNull": false,
// CHECK:     "IsExpansionTypeAnonymous": false,
// CHECK:     "IsExpansionTypeLocalType": false,
// CHECK:     "IsExpansionTypeDefinedAfterMacro": false,
// CHECK:     "IsExpansionTypeVoid": false,
// CHECK:     "IsExpansionTypeFunctionType": false,
// CHECK:     "IsAnyArgumentTypeNull": false,
// CHECK:     "IsAnyArgumentTypeAnonymous": false,
// CHECK:     "IsAnyArgumentTypeLocalType": false,
// CHECK:     "IsAnyArgumentTypeDefinedAfterMacro": false,
// CHECK:     "IsAnyArgumentTypeVoid": false,
// CHECK:     "IsAnyArgumentTypeFunctionType": false,
// CHECK:     "IsInvokedWhereModifiableValueRequired": false,
// CHECK:     "IsInvokedWhereAddressableValueRequired": false,
// CHECK:     "IsInvokedWhereICERequired": false,
// CHECK:     "IsInvokedWhereConstantExpressionRequired": false,
// CHECK:     "IsAnyArgumentExpandedWhereModifiableValueRequired": true,
// CHECK:     "IsAnyArgumentExpandedWhereAddressableValueRequired": false,
// CHECK:     "IsAnyArgumentConditionallyEvaluated": false,
// CHECK:     "IsAnyArgumentNeverExpanded": false,
// CHECK:     "IsAnyArgumentNotAnExpression": false
// CHECK:   }
// CHECK: ]