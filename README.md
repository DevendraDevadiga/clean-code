# CaseStudy.md First Question
1) Functions can be made as library functions so that other programs can use.
2) if first line has only 3 Values, remaining has 4 values as expected, function will not parse remaining values.
3) Always expects specific format data, example last value should be 0xXX, if last param is decimal, code fails.
4) Code is fixed to parse 4 arguments. In future if needs changes in input text (like another input) then main code need to change.
5) Code is known range i.e 0xFF, so unit8 can be used instead of int and wasting another extra 3 bytes
6) Oveflow of integers/float not handled => not striclty
