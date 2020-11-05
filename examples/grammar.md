#Language Grammar

expression
    - LP expression RP
    - L3 expression L3
    - (NL|SC) expression (NL|SC)
    - IDENTIFIER argument*

argument
    - expression
    - data

data
    - INT
    - FLOAT
    - STRING
    - IDENTIFIER
    - LIST
    - CHAR

list
    - LB data* RB (possibly only allowing the same kind of data throughout)

Tokens needed: LP, RP, LB, RB, L3, R3, SC, NL, INT, FLOAT, STRING, IDENTIFIER, LIST, CHAR

* IDENTIFIER is used for both variables and operators
