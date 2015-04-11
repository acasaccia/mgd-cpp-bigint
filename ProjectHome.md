Design a class (or a class library) to handle unlimited integer operations (integer larger)
Provide the class standard overloaded arithmetic operators.

Follow the rules "do as ints do".

Write a test for `BigInt` operations:

Example:
```
{
    BigInt x = 569; // ctor with an integer
    BigInt y; // default ctor
    y = pow(x, 10); // 569*569*...*569 ten times (a big number!)
    BigInt z = x; //copy ctor
    z = x; // operator=
    z += y; // operator+, operator+=, -, -=, *, *=
    z %= y; // operator%, operator/ operator%= 
    z %=  5; // same operators of above... it is better to provide overloads for int or just convert int to BigInt?
    BigInt w("348734834853836786386736"); // yeah, ctor that takes a string!
    w++; // postincrement, preincrement
    if(w <= y) // yeeeah, comparison! <, <=, >, >=, ==, !=
        z &= x; // bitwise and, or, xor...
    std:: cout << y; // obviously streams operators...
    x = -y; // yeah, signed/unsigned, unary operator -
    x <<= 5; // yeah, shift operators!
    w = pow(w,y); // ok, this will crack your ram, but you have to implement pow for both base and exponent BigInt
}
```

Suggestions and hints:
  * choose the right drawback for: time efficiency, space efficiency, digit access
  * reuse code: do not write the same stuff more than once! (how will you implement operator!= if you have operator== ?)
  * document the code. provide a clear class interface
  * write an extensive test suite (I've developed my solution using gtest, the google testing framework, and developing in TDD philosophy)
  * enjoy it!