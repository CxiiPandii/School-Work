#include "val.h"
using namespace std;

// ===================== Helper Functions =====================

// Numeric coercion used by numeric operators and numeric relational operators.
// - Allows: VNUM directly, VSTRING if it is a valid numeric literal.
// - Disallows: VBOOL, VERR.
static bool ToNumeric(const Value& v, double& out)
{
    if (v.IsErr()) return false;

    if (v.IsNum())
    {
        out = v.GetNum();
        return true;
    }

    // Booleans are NOT allowed as numeric operands in BPL
    if (v.IsBool())
        return false;

    if (v.IsString())
    {
        const string& s = v.GetString();
        try {
            size_t idx = 0;
            double val = stod(s, &idx);
            if (idx != s.length()) return false;   // must consume entire string
            out = val;
            return true;
        }
        catch (...) {
            return false;
        }
    }

    return false;
}

// String coercion used by string-based operators (Catenate, SEQ, SGT, SLE, Repeat-left).
// - Allows: VSTRING (as-is), VNUM (formatted).
// - Disallows: VBOOL, VERR.
//
// For numbers, we mimic your RA7 behavior:
//   - If integer-valued, print as plain int ("4", "25")
//   - Else, print with one decimal ("9.5")
static bool ToStringForStrOps(const Value& v, string& out)
{
    if (v.IsErr() || v.IsBool())
        return false;

    if (v.IsString())
    {
        out = v.GetString();
        return true;
    }
    else if (v.IsNum())
    {
        double n = v.GetNum();
        if (floor(n) == n)
        {
            out = to_string(static_cast<int>(n));
        }
        else
        {
            ostringstream ss;
            ss << fixed << setprecision(1) << n;
            out = ss.str();
        }
        return true;
    }

    return false;
}

// Truthiness helper for logic ops (&&, ||)
// - Numbers: 0 -> false, others -> true
// - Strings: "" and "0" -> false, others -> true
// - Bool: use stored bool
// - Error: can't convert
static bool ToBool(const Value& v, bool& out)
{
    if (v.IsErr()) return false;

    if (v.IsBool())
    {
        out = v.GetBool();
        return true;
    }

    if (v.IsNum())
    {
        out = (v.GetNum() != 0.0);
        return true;
    }

    if (v.IsString())
    {
        const string& s = v.GetString();
        if (s.empty() || s == "0")
            out = false;
        else
            out = true;
        return true;
    }

    return false;
}

// ===================== Arithmetic Operators =====================

// +
Value Value::operator+(const Value& op) const
{
    if (this->IsErr() || op.IsErr())
        return Value();   // ERROR

    // Booleans not allowed in numeric + in BPL
    if (this->IsBool() || op.IsBool())
        return Value();

    double left, right;
    if (!ToNumeric(*this, left) || !ToNumeric(op, right))
        return Value();   // ERROR (e.g., non-numeric string)

    return Value(left + right);
}

// -
Value Value::operator-(const Value& op) const
{
    if (this->IsErr() || op.IsErr())
        return Value();   // ERROR

    if (this->IsBool() || op.IsBool())
        return Value();

    double left, right;
    if (!ToNumeric(*this, left) || !ToNumeric(op, right))
        return Value();

    return Value(left - right);
}

// *
Value Value::operator*(const Value& op) const
{
    if (this->IsErr() || op.IsErr())
        return Value();   

    if (this->IsBool() || op.IsBool())
        return Value();   

    double left, right;
    if (!ToNumeric(*this, left) || !ToNumeric(op, right))
        return Value();  

    return Value(left * right);
}

// /
Value Value::operator/(const Value& op) const
{
    if (this->IsErr() || op.IsErr())
        return Value();   // ERROR

    if (this->IsBool() || op.IsBool())
        return Value();

    double left, right;
    if (!ToNumeric(*this, left) || !ToNumeric(op, right))
        return Value();

    if (right == 0.0)
        return Value();   // Division by zero -> ERROR (interpreter will print runtime msg)

    return Value(left / right);
}

// %
Value Value::operator%(const Value& op) const
{
    if (this->IsErr() || op.IsErr())
        return Value();   // ERROR

    if (this->IsBool() || op.IsBool())
        return Value();

    double leftD, rightD;
    if (!ToNumeric(*this, leftD) || !ToNumeric(op, rightD))
        return Value();

    int left = static_cast<int>(leftD);
    int right = static_cast<int>(rightD);

    if (right == 0)
        return Value();   // Remainder by zero -> ERROR

    int res = left % right;
    return Value(static_cast<double>(res));
}

// Exponentiation: this ** oper
// Spec: exponentiation does NOT auto-convert strings; only pure numeric operands.
Value Value::Expon(const Value& oper) const
{
    if (this->IsErr() || oper.IsErr())
        return Value();

    if (!this->IsNum() || !oper.IsNum())
        return Value();   // strings/bools are illegal here

    double base = this->GetNum();
    double exp  = oper.GetNum();

    return Value(pow(base, exp));
}

// ===================== Numeric Relational / Equality =====================

// <
Value Value::operator<(const Value& op) const
{
    if (this->IsErr() || op.IsErr())
        return Value();  

    if (this->IsBool() || op.IsBool())
        return Value();  

    double left, right;
    if (!ToNumeric(*this, left) || !ToNumeric(op, right))
        return Value(); 

    return Value(left < right);
}

// ==
Value Value::operator==(const Value& op) const
{
    if (this->IsErr() || op.IsErr())
        return Value();   // ERROR

    if (this->IsBool() || op.IsBool())
        return Value();   // numeric equality does not allow bools

    double left, right;
    if (!ToNumeric(*this, left) || !ToNumeric(op, right))
        return Value();

    return Value(left == right);
}

// >=
Value Value::operator>=(const Value& op) const
{
    if (this->IsErr() || op.IsErr())
        return Value();   // ERROR

    if (this->IsBool() || op.IsBool())
        return Value();

    double left, right;
    if (!ToNumeric(*this, left) || !ToNumeric(op, right))
        return Value();

    return Value(left >= right);
}



// Catenate: this . oper
Value Value::Catenate(const Value& oper) const
{
    if (this->IsErr() || oper.IsErr())
        return Value();

    if (this->IsBool() || oper.IsBool())
        return Value();

    string left, right;

    if (!ToStringForStrOps(*this, left))
        return Value();

    if (!ToStringForStrOps(oper, right))
        return Value();

    return Value(left + right);
}

Value Value::Repeat(const Value& oper) const
{
    if (this->IsErr() || oper.IsErr())
        return Value(); 
        
    if (!oper.IsNum())
        return Value();   

    string base;

    if (this->IsString()) 
        base = this->GetString();
    else if (this->IsNum()) {
        double num = this->GetNum();
        ostringstream out;
        out << fixed << setprecision((floor(num)==num)?0:1) << num;
        base = out.str();
    }
    else
        return Value();   

    
    double timesDouble = oper.GetNum();
    int times = (int)timesDouble;

    if (times < 0)
        return Value();  

    string result;
    result.reserve(base.size() * times);

    for (int i = 0; i < times; ++i)
        result += base;

    return Value(result);
}

// SEQ: this @eq oper
Value Value::SEQ(const Value& oper) const
{
    if (this->IsErr() || oper.IsErr())
        return Value();  

    if (this->IsBool() || oper.IsBool())
        return Value();  

    string left, right;

    if (!ToStringForStrOps(*this, left))
        return Value();

    if (!ToStringForStrOps(oper, right))
        return Value();

    return Value(left == right);
}

// SGT: this @gt oper   (string greater-than)
Value Value::SGT(const Value& oper) const
{
    if (this->IsErr() || oper.IsErr())
        return Value();

    if (this->IsBool() || oper.IsBool())
        return Value();

    string left, right;

    if (!ToStringForStrOps(*this, left))
        return Value();

    if (!ToStringForStrOps(oper, right))
        return Value();

    return Value(left > right);
}

// SLE: this @le oper   (string less-than-or-equal)
Value Value::SLE(const Value& oper) const
{
    if (this->IsErr() || oper.IsErr())
        return Value();

    if (this->IsBool() || oper.IsBool())
        return Value();

    string left, right;

    if (!ToStringForStrOps(*this, left))
        return Value();

    if (!ToStringForStrOps(oper, right))
        return Value();

    return Value(left <= right);
}



// &&
Value Value::operator&&(const Value& op) const
{
    if (this->IsErr() || op.IsErr())
        return Value();   // ERROR

    bool leftB, rightB;
    if (!ToBool(*this, leftB) || !ToBool(op, rightB))
        return Value();   // ERROR

    return Value(leftB && rightB);
}

// ||
Value Value::operator||(const Value& op) const
{
    if (this->IsErr() || op.IsErr())
        return Value();   // ERROR

    bool leftB, rightB;
    if (!ToBool(*this, leftB) || !ToBool(op, rightB))
        return Value();   // ERROR

    return Value(leftB || rightB);
}

// !
Value Value::operator!() const
{
    if (this->IsErr())
        return Value();   


    if (this->IsBool())
        return Value(!this->GetBool());

    return Value(false);
}
