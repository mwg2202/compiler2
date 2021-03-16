#Language Grammar

expression
    - (LP|L3) item* (RP|R3)

item
    - expression
    - INT
    - FLOAT
    - quote
    - STRING
    - CHAR
    - nil
    - IDENTIFIER

Tokens needed: LP, RP, LB, RB, L3, R3, SC, NL, INT, FLOAT, STRING, IDENTIFIER, CHAR

* IDENTIFIER is used for both variables and operators


