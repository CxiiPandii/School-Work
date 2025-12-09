In this programming assignment, we built an Interpreter for a Basic Perl-Like programming language, called BPL. The grammar rules of the language and its tokens were given in Programming Assignments 1 and 2. We are required to modify the parser we have implemented for the BPL language to implement an interpreter for it.  The specifications of the grammar rules are described in EBNF notations as follows.

1.Prog ::= StmtList \n
2.StmtList ::= Stmt; { Stmt; } \n
3.Stmt ::= IfStmt | AssignStmt | PrintLnStmt
4.PrintLnStmt ::= PRINTLN (ExprList)
5.IfStmt ::= IF (Expr) ‘{‘ StmtList ‘}’ [ ELSE ‘{‘ StmtList ‘}’ ]
6.Var ::= IDENT
7.ExprList ::= Expr { , Expr }
8.AssignStmt ::= Var AssigOp Expr
9.Expr ::= OrExpr
10.AssigOp ::= ( = | += | -= | .= )
11.OrExpr ::= AndExpr { || AndExpr }
12.AndExpr ::= RelExpr { && RelExpr }
13.RelExpr ::= AddExpr [ ( @le | @gt | @eq | < | >= | == ) AddExpr ]
14.AddExpr :: MultExpr { ( + | - | . ) MultExpr }
15.MultExpr ::= UnaryExpr { ( * | / | % | .x. ) UnaryExpr }
16.UnaryExpr ::= [( - | + | ! )] ExponExpr
17.ExponExpr ::= PrimaryExpr { ** PrimaryExpr }
18.PrimaryExpr ::= IDENT | ICONST | FCONST | SCONST | (Expr)

We were also given a table of associativity guideline:
Table of Associativity and Precedence Levels of Operators
Precedence    ||    Operator         ||          Description              ||           Associativity
1.                  **                      Exponentiation                       Right-to-Left
2.              Unary +, -, !         Unary plus and minus, and NOT              Right-to-Left
3.              *, /, %, .x.           Multiplication, Division,                 Left-to-Right
                                  Remainder, and string repetition                                
4.               +, -, .              Addition, Subtraction, and                 Left-to-Right
                                          Concatenation
5.              <, >=, ==,          Relational operators for numeric             Left-to-Right
              @le, @gt,@eq                and string types
6.                 &&                      Logical AND                           Left-to-Right
7.                 ||                      Logical OR                            Left-to-Right
8.            =, +=, -=, .=            Assignment operators                      Right-to-Left

1. The BPL language has two data types: Numeric and string. The data type is dynamically bound
to a variable name in an assignment statement.
2. A variable has to be defined in an assignment statement before it is been used.
3. The associativity and precedence rules of operators in the language are as shown in the table
of operators’ precedence levels.
4. An IfStmt evaluates a logical expression (Expr) as a condition. If the logical condition value
is true, then the StmtList in the If-clause are executed, otherwise they are not. An else clause
for an IfSmt is optional. Therefore, If an Else-clause is defined, the StmtList in the Else-clause
are executed when the logical condition value is false. Howevef, the BPL language does not
include a Boolean type, instead it uses the following simple rules:
  •   If the value is a number, 0 means false; all other numbers mean true.
  • Otherwise, if the value is a string, the empty string ('') and the string '0' mean false; all
    other strings mean true.
  • If the variable doesn’t have a value yet, it’s an undefined variable error.
5. A PrinteLnStmt evaluates the list of expressions (ExprList), and prints their values in order
from left to right followed by a newline.
6. The ASSOP operator (=) and all the combined assignment operators (+=, -=, .=) assign a value
to a variable according to the right-hand side expression. It evaluates the Expr on the right-
hand side and saves its value in a memory location associated with the left-hand side variable
(Var). The type of the variable is bound dynamically to the type of the right-hand side
expression. However, the assignment of a Boolean value to a variable is illegal.
7. The binary operations for numeric operators are the addition, subtraction, multiplication,
division, remainder (modulus), and exponentiation. These are performed upon two numeric
operands. Except of the exponentiation operator, if any of the operands is a string, it will be
automatically converted to a numeric value. For the remainder operator, a numeric operand is
converted to an integer value in order to perform the operation.
8. The string concatenation operator is performed upon two string operands. If one of the
operands is not a string, that operand is automatically converted to a string.
9. The string repetition operator must have the first operand as a string, while the second operand
must be of a numeric type of an integer value.
10. Similarly, numeric relational and equality operators (==, <, and >=) operate upon two numeric
type operands. While, string relational and equality operators (@eq, @le, @gt) operate upon
two string type operands. The evaluation of a relational or an equality expression, produces
either a true or false value. If one of the operands does not match the type of the operator, that
operand is automatically converted to the type of the operator. For all relational and equality
operators, no cascading is allowed.
11. Logic binary operators (&&, ||) are applied on two operands, which their Boolean values are
determined based on the following rules:
  • If the value is a number, 0 means false; all other numbers mean true.
  • Otherwise, if the value is a string, the empty string ('') and the string '0' mean false; all
    other strings mean true.
  • If the variable doesn’t have a value yet, it’s an undefined variable error.
12. The unary sign operators (+ or -) are applied upon unary numeric operand only. While the
unary not operator (!) is applied upon a Boolean operand, according to the rules given
previously.
Interpreter Requirements:
Implement an interpreter for the language based on the recursive-descent parser developed in
Programming Assignment 2. You need to complete the implementations of the Value class
member functions. You need to modify the parser functions to include the required actions of the
interpreter for evaluating expressions, determining the type of expression values, executing the
statements, and checking run-time errors. You may use the parser you wrote for Programming
Assignment 2. Otherwise you may use the provided implementations for the parser when it is
posted. Rename the “parser.cpp” file as “parserInterp.cpp” to reflect the applied changes on the
current parser implementation for building an interpreter. The interpreter should provide the
following:
  • It performs syntax analysis of the input source code statement by statement, then executes
    the statement if there is no syntactic or semantic error.

