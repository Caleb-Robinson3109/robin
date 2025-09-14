<div style="display: flex;">

<div style="flex: 1;">

# Grammer

Program -\> Function <span class="done">Main</span>

Fucntion -\> FuncDef FuncBody Function | e

FuncDef -\> ident -\> Param Type

Param -\> Type ident -\> Param | e

Type -\> <span class="done"> int </span> | <span class="done"> char
</span>| <span class="done"> string </span>| <span class="done">
bool</span> | <span class="done"> float</span>

FuncBody -\> <span class="done">Scope</span>

Scope -\> <span class="done">ScopeType { ScopeBody }</span>

ScopeType -\> <span class="done">'Pure'</span> |
<span class="done">'IO'</span> | <span class="done">'State'</span> |
'Loop' | <span class="done">e</span>

ScopeBody -\> Code

Code -\> <span class="done">Statement Code'</span>| Loop Code'|
Conditional Code'| <span class="done">Scope Code'</span>

Code' -\> <span class="done"> Code </span> | <span class="done"> e
</span>

Statement -\> <span class="done"> IO </span> | <span class="done">
Return </span> | <span class="done"> Decloration </span>

IO -\> Print | Input | <span class="done"> Output </span>

Print -\> print String ;

Input -\> input ident Value ;

Output -\> <span class="change"> output <span class="diff"> String
(Value) ( output ( String ) ;)</span> ; </span>

Return -\> <span class="done"> return <span class="diff"> Value (int)
</span> ; </span>

Value -\> <span class="done"> String </span> | <span class="done"> Char
</span>| <span class="done"> Bool</span> | <span class="done">
Expression</span>

String -\> <span class="done"> string </span>| <span class="done"> idnet
</span>| StringConcat | Cast

Int -\> <span class="done"> int </span>| <span class="done"> ident
</span>

Char -\> <span class="done"> char </span>| <span class="done"> ident
</span>

Bool -\> <span class="done"> bool </span>| <span class="done"> ident
</span>

Float -\> <span class="done"> float</span> | <span class="done"> ident
</span>

Main -\> <span class="done">MainDef FuncBody</span>

MainDef -\> <span class="change">main '-\>' 'int' (int main ( ))
</span>| int main ( int argc , string argv )

Decloration -\> <span class="done"> Mut </span>| <span class="done"> Let
</span>

Mut -\> <span class="done"> mut Type ident = <span class="diff"> Value
(int)</span> ;</span>

Let -\> <span class="done"> Type ident = Value ;</span>

Expression -\> <span class="done">Term Expression'</span>

Expression' -\> <span class="done"> Operator Term Expression' | e
</span>

Term -\> <span class="done"> Factor</span> | <span class="done">(
Expression ) </span>

Factor -\> Number

Number -\> <span class="done">Int </span>|
<span class="done">Float</span>

Operator -\> <span class="done">+ </span>| <span class="done">- </span>|
<span class="done">\*</span> | <span class="done">/</span> |
<span class="done">%</span>

Proposition -\> Condition

Condition -\> Unary Condition'

Condition' -\> BooleanOperator Unary Condition' | e

Unary -\> \! Unary | Primary

Primary -\> Bool | ( Condition )

LogicalOperator -\> || | && | ^^ | -\> | == | \!=

Branch -\> BranchIf BranchElif BranchElse

Conditional -\> If Elif Else

BranchIF -\> if ( Proposition ) { Code }

BranchElif -\> elif ( Proposition ) { Code } BranchElif | e

BranchElse -\> else { Code } | e

If -\> if ( Proposition ) { Value }

Elif -\> elif (Proposition) {Value} Elif | e

Else -\> else { Value }

</div>

<div style="flex: 1;">

# Regex

int = ^-?\\d+$

float = ^-?\\d+\\.\\d+$

char = ^'\[a-zA-Z0-9\_\]'$

bool = \\b(true|false)\\b

string = ^\\"(\[a-zA-Z0-9\_\]|\\\\\[nt\\"\\\\\])\*\\"$

ident = ^\[a-zA-Z\_\]\[a-zA-Z0-9\_\]\*$

</div>

</div>

-----

<div style="display: flex;">

<div style="flex: 1;">

//TODO: check that there is no indirect recurrison

Green - completed

Red - change syntax

Yellow - change single token

Blue - must implement into code generator

</div>

<div style="flex: 1;">

\-c compile compiler

\-d debug build

\-i \<filename\> intermeident .cpp filename

\-o \<filename\> output filename

\-a print ast

\-t print tokens

\-r remove the intermeident .cpp file

\-e exacute the final binary

</div>

</div>
