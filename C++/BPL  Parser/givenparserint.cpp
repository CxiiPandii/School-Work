/* Implementation of Recursive-Descent Interpreter
 * for the Basic Perl-Like Language (BPL)
 * parserInterp.cpp
 * Programming Assignment 3
 * Fall 2025
*/

#include "parserInt.h"
#include <map>
#include <string>
#include <cstdlib>

using namespace std;

map<string, bool>    defVar;        
map<string, ValType> SymTable;      
map<string, Value>   TempsResults;  

namespace Parser 
{
    bool    pushed_back = false;
    LexItem pushed_token;

    static LexItem GetNextToken(istream& in, int& line) 
    {
        if (pushed_back) {
            pushed_back = false;
            return pushed_token;
        }
        return getNextToken(in, line);
    }

    static void PushBackToken(LexItem & t) 
    {
        if (pushed_back) {
            abort();
        }
        pushed_back = true;
        pushed_token = t;	
    }
}

static int error_count = 0;

int ErrCount()
{
    return error_count;
}

void ParseError(int line, string msg)
{
    ++error_count;
    cout << error_count << ". Line " << line << ": " << msg << endl;
}

// Helper: generic run-time error catcher
static bool CheckRuntime(const Value& v, int line, const string& msg)
{
    if (v.IsErr()) {
        ParseError(line, msg);
        return false;
    }
    return true;
}

// Program ::= StmtList
bool Prog(istream& in, int& line)
{
    bool f1;
    LexItem tok = Parser::GetNextToken(in, line);
    
    if (tok.GetToken() == DONE && tok.GetLinenum() <= 1) {
        ParseError(line, "Empty File");
        return true;
    }
    Parser::PushBackToken(tok);

        f1 = StmtList(in, line); 
            
    if (!f1) 
    {
        ParseError(line, "Missing Program");
        return false;
    }
    else 
    {
        cout << endl << endl;
        cout << "DONE" << endl;
        return true;
    }
	
}


// StmtList ::= Stmt; { Stmt; }
bool StmtList(istream& in, int& line)
{
    bool status;
    LexItem tok;
    
    status = Stmt(in, line);
    while (status)
    {
        tok = Parser::GetNextToken(in, line);
        if (tok == DONE)
        {
            Parser::PushBackToken(tok);
            return true;
        }
        else if (tok == RBRACES)
        {
            Parser::PushBackToken(tok);
            return true;
        }
        
        if (tok != SEMICOL)
        {
            line--;
            ParseError(line, "Missing semicolon at end of Statement");
            return false;
        }
        
        status = Stmt(in, line);
    }
            
    tok = Parser::GetNextToken(in, line);
    
    if (tok == ELSE)
    {
        ParseError(line, "Illegal If Statement Else-Clause");
        return false;
    }
    else if (tok == RBRACES)
    {
        Parser::PushBackToken(tok);
        return true;
    }
    else if (tok == DONE && !status)
    {
        ParseError(line, "Syntactic error in Program Body");
        return false;
    }
    else
    {
        ParseError(line, "Syntactic error in Program Body");
        return false;
    }
}


// Stmt ::= AssignStmt | PrintLnStmt | IfStmt  
bool Stmt(istream& in, int& line)
{
    bool status = false;
    LexItem t = Parser::GetNextToken(in, line);
    
    switch (t.GetToken()) {
    case IDENT: 
        Parser::PushBackToken(t);
        status = AssignStmt(in, line);
        if (!status)
        {
            ParseError(line, "Incorrect Assignment Statement");
            return status;
        }
        break;

    case PRINTLN:
        status = PrintLnStmt(in, line);
        if (!status)
        {
            ParseError(line, "Incorrect PrintLn Statement");
            return status;
        }
        break;

    case IF:
        status = IfStmt(in, line);
        if (!status)
        {
            ParseError(line, "Incorrect If-Statement");
            return status;
        }
        break;

    case ELSE:
        Parser::PushBackToken(t);
        return false;

    case DONE:
        return true;

    default:
        Parser::PushBackToken(t);
        return true;
    }
    return status;
}


// PrintLnStmt:= PRINTLN (ExprList) 
bool PrintLnStmt(istream& in, int& line)
{
    LexItem t = Parser::GetNextToken(in, line);
    if (t != LPAREN) 
    {
        ParseError(line, "Missing Left Parenthesis of PrintLn Statement");
        return false;
    }
    
    bool ex = ExprList(in, line);
    cout << endl;
    if (!ex) 
    {
        ParseError(line, "Missing expression list after PrintLn");
        return false;
    }
    
    t = Parser::GetNextToken(in, line);
    if (t != RPAREN) 
    {
        ParseError(line, "Missing Right Parenthesis of PrintLn Statement");
        return false;
    }
    
    return true;
}

// SkipBlock: assumes next token is '{', skips entire block without executing StmtList
bool SkipBlock(istream& in, int& line)
{
    LexItem t = Parser::GetNextToken(in, line);

    if (t != LBRACES)
    {
        ParseError(line, "Missing left brace in skipped block");
        return false;
    }

    int depth = 1;

    while (depth > 0)
    {
        t = Parser::GetNextToken(in, line);

        if (t == LBRACES)
            depth++;
        else if (t == RBRACES)
            depth--;
        else if (t == DONE)
        {
            ParseError(line, "Missing right brace in skipped block");
            return false;
        }
    }

    return true;
}


// IfStmt:= IF (Expr) '{' StmtList '}' [ else '{' StmtList '}' ] 
bool IfStmt(istream& in, int& line)
{
    LexItem t = Parser::GetNextToken(in, line);
    if (t != LPAREN)
    {
        ParseError(line, "Missing Left Parenthesis of If condition");
        return false;
    }

    Value cond;
    if (!Expr(in, line, cond))
    {
        ParseError(line, "Missing if statement Logic Expression");
        return false;
    }

    // Convert to boolean
    bool condValue = false;
    if (cond.IsBool())
        condValue = cond.GetBool();
    else if (cond.IsNum())
        condValue = (cond.GetNum() != 0);
    else if (cond.IsString())
        condValue = (!cond.GetString().empty() && cond.GetString() != "0");
    else
    {
        ParseError(line, "Run-Time Error-Illegal Mixed Type Operands");
        return false;
    }

    t = Parser::GetNextToken(in, line);
    if (t != RPAREN)
    {
        ParseError(line, "Missing Right Parenthesis of If condition");
        return false;
    }

    t = Parser::GetNextToken(in, line);
    if (t != LBRACES)
    {
        Parser::PushBackToken(t);
        ParseError(line, "Missing left brace for If Statement Clause");
        return false;
    }

    if (condValue)
    {
        // Execute the IF block
        if (!StmtList(in, line))
        {
            ParseError(line, "Missing Statement for If Statement Clause");
            return false;
        }

        t = Parser::GetNextToken(in, line);
        if (t != RBRACES)
        {
            ParseError(line, "Missing right brace for If Statement Clause");
            return false;
        }
    }
    else
    {
        Parser::PushBackToken(t);   
        if (!SkipBlock(in, line))
            return false;
    }

    t = Parser::GetNextToken(in, line);

    if (t == ELSE)
    {
        t = Parser::GetNextToken(in, line);
        if (t != LBRACES)
        {
            Parser::PushBackToken(t);
            ParseError(line, "Missing left brace for Else-Clause");
            return false;
        }

        if (!condValue)
        {
            if (!StmtList(in, line))
            {
                ParseError(line, "Missing Statement for Else-Clause");
                return false;
            }

            t = Parser::GetNextToken(in, line);
            if (t != RBRACES)
            {
                ParseError(line, "Missing right brace for an Else-Clause");
                return false;
            }
        }
        else
        {
            Parser::PushBackToken(t); 
            if (!SkipBlock(in, line))
                return false;
        }
    }
    else
    {
        Parser::PushBackToken(t); 
    }

    return true;
}//end of IfStmt


// Var ::= IDENT
bool Var(istream& in, int& line, LexItem & idtok)
{
    string identstr;
    LexItem tok = Parser::GetNextToken(in, line);

    if (tok == IDENT) 
    {
        identstr = tok.GetLexeme();
        idtok    = tok; 

        defVar[identstr] = true;
        return true;
    }
    else if (tok.GetToken() == ERR) 
    {
        ParseError(line, "Unrecognized Input Pattern");
        cout << "(" << tok.GetLexeme() << ")" << endl;
        return false;
    }

    return false;
}

// AssignStmt := Var AssignOp Expr
bool AssignStmt(istream& in, int& line)
{
    LexItem idtok;
    if (!Var(in, line, idtok)) 
    {
        ParseError(line, "Missing Left-Hand Side Variable in Assignment statement");
        return false;
    }

    string varName = idtok.GetLexeme();

    LexItem op = Parser::GetNextToken(in, line);
    if (!(op == ASSOP || op == CADDA || op == CSUBA || op == CCATA))
    {
        ParseError(line, "Missing Assignment Operator");
        return false;
    }

    Value rhs;
    if (!Expr(in, line, rhs))
    {
        ParseError(line, "Missing Expression in Assignment Statement");
        return false;
    }

    // Boolean assignment is illegal
    if (rhs.IsBool())
    {
        ParseError(line, "Run-Time Error-Illegal Assignment Operation");
        return false;
    }

    Value result;

    if (op == ASSOP)
    {
        result = rhs;
    }
    else 
    {
        if (TempsResults.find(varName) == TempsResults.end()) 
        {
            ParseError(line, "Run-Time Error-Illegal Assignment Operation");
            return false;
        }

        Value lhs = TempsResults[varName];

        if (op == CADDA)      result = lhs + rhs;
        else if (op == CSUBA) result = lhs - rhs;
        else if (op == CCATA) result = lhs.Catenate(rhs);

        if (!CheckRuntime(result, line, "Run-Time Error-Illegal Mixed Type Operands"))
            return false;
    }

    TempsResults[varName] = result;
    SymTable[varName]     = result.GetType();
    defVar[varName]       = true;

    return true;
}


// ExprList:= Expr {,Expr}
bool ExprList(istream& in, int& line) 
{
    bool  status = false;
    Value val;

    status = Expr(in, line, val);
    if (!status) 
    {
        ParseError(line, "Missing Expression");
        return false;
    }

    cout << val;

    LexItem tok = Parser::GetNextToken(in, line);

    if (tok == COMMA) 
    {
        if (!ExprList(in, line))
            return false;
    }
    else if (tok.GetToken() == ERR) 
    {
        ParseError(line, "Unrecognized Input Pattern");
        cout << "(" << tok.GetLexeme() << ")" << endl;
        return false;
    }
    else 
    {
        Parser::PushBackToken(tok);
        return true;
    }
    return true;
}


// Expr ::= OrExpr
bool Expr(istream& in, int& line, Value & retVal) 
{
    return OrExpr(in, line, retVal);
}

// OrExpr ::= AndExpr { || AndExpr }
bool OrExpr(istream& in, int& line, Value & retVal) 
{
    LexItem tok;
    Value lhs, rhs;

    if (!AndExpr(in, line, lhs))
        return false;

    tok = Parser::GetNextToken(in, line);
    if (tok.GetToken() == ERR) 
    {
        ParseError(line, "Unrecognized Input Pattern");
        cout << "(" << tok.GetLexeme() << ")" << endl;
        return false;
    }

    while (tok == OR) 
    {
        if (!AndExpr(in, line, rhs)) 
        {
            ParseError(line, "Missing operand after OR operator");
            return false;
        }

        Value res = lhs || rhs;
        if (!CheckRuntime(res, line, "Run-Time Error-Illegal Mixed Type Operands"))
            return false;

        lhs = res;

        tok = Parser::GetNextToken(in, line);
        if (tok.GetToken() == ERR) 
        {
            ParseError(line, "Unrecognized Input Pattern");
            cout << "(" << tok.GetLexeme() << ")" << endl;
            return false;
        }
    }

    Parser::PushBackToken(tok);
    retVal = lhs;
    return true;
}


// AndExpr ::= RelExpr { && RelExpr }
bool AndExpr(istream& in, int& line, Value & retVal) 
{
    LexItem tok;
    Value lhs, rhs;

    if (!RelExpr(in, line, lhs))
        return false;

    tok = Parser::GetNextToken(in, line);
    if (tok.GetToken() == ERR) 
    {
        ParseError(line, "Unrecognized Input Pattern");
        cout << "(" << tok.GetLexeme() << ")" << endl;
        return false;
    }

    while (tok == AND) 
    {
        if (!RelExpr(in, line, rhs)) 
        {
            ParseError(line, "Missing operand after AND operator");
            return false;
        }

        Value res = lhs && rhs;
        if (!CheckRuntime(res, line, "Run-Time Error-Illegal Mixed Type Operands"))
            return false;

        lhs = res;

        tok = Parser::GetNextToken(in, line);
        if (tok.GetToken() == ERR) {
            ParseError(line, "Unrecognized Input Pattern");
            cout << "(" << tok.GetLexeme() << ")" << endl;
            return false;
        }
    }

    Parser::PushBackToken(tok);
    retVal = lhs;
    return true;
}


// RelExpr ::= AddExpr [ ( @le | @gt | @eq | < | >= | == ) AddExpr ]
bool RelExpr(istream& in, int& line, Value & retVal) 
{
    LexItem tok;
    Value lhs, rhs;

    if (!AddExpr(in, line, lhs))
        return false;

    tok = Parser::GetNextToken(in, line);
    if (tok.GetToken() == ERR) {
        ParseError(line, "Unrecognized Input Pattern");
        cout << "(" << tok.GetLexeme() << ")" << endl;
        return false;
    }

    if (tok == NGTE || tok == NLT || tok == NEQ || 
        tok == SLTE || tok == SGT || tok == SEQ)
    {
        if (!AddExpr(in, line, rhs)) {
            ParseError(line, "Missing operand after a relational operator");
            return false;
        }

        Value res;

        // numeric relational: >=, <, ==
        if (tok == NGTE) 
            res = lhs >= rhs;
        else if (tok == NLT) 
            res = lhs < rhs;
        else if (tok == NEQ) 
            res = lhs == rhs;
        // string relational: @le, @gt, @eq
        else if (tok == SLTE) 
            res = lhs.SLE(rhs);
        else if (tok == SGT) 
            res = lhs.SGT(rhs);
        else if (tok == SEQ) 
            res = lhs.SEQ(rhs);

        if (!CheckRuntime(res, line, "Run-Time Error-Illegal Mixed Type Operands"))
            return false;

        retVal = res;
        return true;
    }

    Parser::PushBackToken(tok);
    retVal = lhs;
    return true;
}


// AddExpr :: MultExpr { ( + | - | . ) MultExpr }
bool AddExpr(istream& in, int& line, Value & retVal) 
{
    bool t1 = MultExpr(in, line, retVal);
    LexItem tok;

    if (!t1)
        return false;

    tok = Parser::GetNextToken(in, line);
    if (tok.GetToken() == ERR) 
    {
        ParseError(line, "Unrecognized Input Pattern");
        cout << "(" << tok.GetLexeme() << ")" << endl;
        return false;
    }

    while (tok == PLUS || tok == MINUS || tok == CAT) 
    {
        Value rhs;

        if (!MultExpr(in, line, rhs)) 
        {
            ParseError(line, "Missing operand after operator");
            return false;
        }

        Value res;

        if (tok == PLUS)
            res = retVal + rhs;
        else if (tok == MINUS)
            res = retVal - rhs;
        else
            res = retVal.Catenate(rhs);

        if (!CheckRuntime(res, line, "Run-Time Error-Illegal Mixed Type Operands"))
            return false;

        retVal = res;

        tok = Parser::GetNextToken(in, line);
        if (tok.GetToken() == ERR) 
        {
            ParseError(line, "Unrecognized Input Pattern");
            cout << "(" << tok.GetLexeme() << ")" << endl;
            return false;
        }
    }

    Parser::PushBackToken(tok);
    return true;
}


// MultExpr ::= UnaryExpr { ( * | / | % | .x.) UnaryExpr }
bool MultExpr(istream& in, int& line, Value & retVal) 
{
    bool t1 = UnaryExpr(in, line, retVal);
    LexItem tok;

    if (!t1)
        return false;

    tok = Parser::GetNextToken(in, line);
    if (tok.GetToken() == ERR) 
    {
        ParseError(line, "Unrecognized Input Pattern");
        cout << "(" << tok.GetLexeme() << ")" << endl;
        return false;
    }

    while (tok == MULT || tok == DIV || tok == REM || tok == SREPEAT)
    {
        Value rhs;

        if (!UnaryExpr(in, line, rhs))
        {
            ParseError(line, "Missing operand after operator");
            return false;
        }

        Value res;

        if (tok == MULT)
            res = retVal * rhs;
        else if (tok == DIV)
            res = retVal / rhs;
        else if (tok == REM)
            res = retVal % rhs;
        else if (tok == SREPEAT)
            res = retVal.Repeat(rhs);

        if (tok == SREPEAT)
        {
            if (res.IsErr())
            {
                ParseError(line, "Illegal operand type for the string repetition operation.");
                return false;
            }
        }
        else
        {
            if (!CheckRuntime(res, line, "Run-Time Error-Illegal Mixed Type Operands"))
                return false;
        }
        

        retVal = res;

        tok = Parser::GetNextToken(in, line);
        if (tok.GetToken() == ERR)
        {
            ParseError(line, "Unrecognized Input Pattern");
            cout << "(" << tok.GetLexeme() << ")" << endl;
            return false;
        }
    }

    
    Parser::PushBackToken(tok);
    return true;
}



// UnaryExpr ::= [ ( - | + | ! ) ] ExponExpr 
bool UnaryExpr(istream& in, int& line, Value & retVal)
{
    LexItem t = Parser::GetNextToken(in, line);
    bool status;
    int sign = 0;  // -1 => unary -, 1 => unary +, 2 => !

    if (t == MINUS)
        sign = -1;
    else if (t == PLUS)
        sign = 1;
    else if (t == NOT)
        sign = 2;
    else
        Parser::PushBackToken(t);

    status = ExponExpr(in, line, 0, retVal);
    if (!status) 
    {
        ParseError(line, "Missing operand for an operator");
        return false;
    }

    if (sign == -1) {
        if (!retVal.IsNum()) 
        {
            ParseError(line, "Run-Time Error-Illegal Mixed Type Operands");
            return false;
        }
        retVal = Value(-retVal.GetNum());
    }
    else if (sign == 1) 
    {
        if (!retVal.IsNum()) 
        {
            ParseError(line, "Run-Time Error-Illegal Mixed Type Operands");
            return false;
        }
    }
    else if (sign == 2) 
    {
        Value res = !retVal;
        if (!CheckRuntime(res, line, "Run-Time Error-Illegal Mixed Type Operands"))
            return false;
        retVal = res;
    }

    return true;
}


// ExponExpr ::= PrimaryExpr { ** ExponExpr }   (right-assoc)
bool ExponExpr(istream& in, int& line, int, Value & retVal)
{
    if (!PrimaryExpr(in, line, 0, retVal))
        return false;

    LexItem tok = Parser::GetNextToken(in, line);
    if (tok == EXPONENT) 
    {
        Value right;

        if (!ExponExpr(in, line, 0, right)) 
        {
            ParseError(line, "Missing exponent operand after exponentiation");
            return false;
        }

        Value res = retVal.Expon(right);
        if (!CheckRuntime(res, line, "Run-Time Error-Illegal Mixed Type Operands"))
            return false;

        retVal = res;

        tok = Parser::GetNextToken(in, line);
        if (tok.GetToken() == ERR) 
        {
            ParseError(line, "Unrecognized Input Pattern");
            cout << "(" << tok.GetLexeme() << ")" << endl;
            return false;
        }
    }
    else if (tok.GetToken() == ERR) 
    {
        ParseError(line, "Unrecognized Input Pattern");
        cout << "(" << tok.GetLexeme() << ")" << endl;
        return false;
    }

    Parser::PushBackToken(tok);
    return true;
}


// PrimaryExpr ::= IDENT | ICONST | FCONST | SCONST | (Expr)
bool PrimaryExpr(istream& in, int& line, int, Value & retVal) 
{
    LexItem tok = Parser::GetNextToken(in, line);

    if (tok == IDENT) 
    {
        string lexeme = tok.GetLexeme();

        auto it = TempsResults.find(lexeme);
        if (it == TempsResults.end()) 
        {
            ParseError(line, "Using Undefined Variable: " + lexeme);
            return false;
        }

        retVal = it->second;
        return true;
    }
    else if (tok == ICONST) 
    {
        double v = stod(tok.GetLexeme());
        retVal = Value(v);
        return true;
    }
    else if (tok == FCONST)
    {
        double v = stod(tok.GetLexeme());
        retVal = Value(v);
        return true;
    }
    else if (tok == SCONST)
    {
        string s = tok.GetLexeme();
        
        if (s.size() >= 2 && s.front() == '\'' && s.back() == '\'')
            s = s.substr(1, s.size() - 2);
        retVal = Value(s);
        return true;
    }

    else if (tok == LPAREN) 
    {
        if (!Expr(in, line, retVal)) 
        {
            ParseError(line, "Missing expression after Left Parenthesis");
            return false;
        }
        if (Parser::GetNextToken(in, line) == RPAREN)
            return true;

        ParseError(line, "Missing right Parenthesis after expression");
        return false;
    }
    else if (tok.GetToken() == ERR) 
    {
        ParseError(line, "Unrecognized Input Pattern");
        cout << "(" << tok.GetLexeme() << ")" << endl;
        return false;
    }

    return false;
}



