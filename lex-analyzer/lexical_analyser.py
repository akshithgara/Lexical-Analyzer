HEXA_DECIMAL = ['A','B','C','D','E','F']
PY_KEYWORDS = ['WHILE','ELSE','IF','END']

numLines = input()
def lex_helper_analyser(s):
    i = 0
    state = 1
    while i < len(s):
        c = s[i]
        if state == 1:
            if c == '+' or c == '-':
                state = 2
            elif c.isdigit():
                state = 3
            elif c in HEXA_DECIMAL:
                state = 7
            elif c == '(':
                state = 11
            else:
                state = -1
        elif state == 2:
            if c == '.':
                state = 4
            elif c.isdigit():
                state = 3
            else:
                state = -1
        elif state == 3:
            if c == '.':
                state = 4
            elif c.isdigit():
                state = 3
            elif c in HEXA_DECIMAL:
                state = 7
            elif c == 'H':
                state = 8
            else:
                state = -1
        elif state == 4:
            if c.isdigit():
                state = 5
            else:
                state = -1
        elif state == 5:
            if c.isdigit():
                state = 5
            elif c == 'E':
                state = 6
            else:
                state = -1
        elif state == 6:
            if c.isdigit():
                state = 6
            elif c == '-':
                state = 6
            else:
                state = -1
        elif state == 7:
            if c == 'H':
                state = 8
            elif c.isdigit():
                state = 7
            elif c in HEXA_DECIMAL:
                state = 7
            else:
                state = -1
        i += 1
    if s in PY_KEYWORDS:
        state = 9
    if state == 3:
        return 'Integer.'
    elif state == 5:
        return 'Decimal.'
    elif state == 6:
        return 'Scientific.'
    elif state == 8:
        return 'Hexadecimal.'
    elif state == 9:
        return 'Keyword.'
    else:
        return 'INVALID!'

def identifier_analyser(s):
    i = 0
    state = 1
    while i < len(s):
        c = s[i]
        if state == 1:
            if c.isalpha():
                state = 2
            else:
                state = -1
        elif state == 2:
            if c.isdigit():
                state = 2
            elif c == '_':
                state = 2
            elif c.isalpha():
                state = 2
            else:
                state = -1
        i += 1
    if state == 2:
        return 'Identifier.'
    else:
        return 'INVALID!'

def phone_analyser(s):
    i = 0
    state = 1
    while i < len(s):
        c = s[i]
        if state == 1:
            if c == '(':
                state = 2
            if c.isdigit():
                state = 6

        elif state == 2:
            if c.isdigit():
                state = 2
            elif c == ')':
                if i == 4:
                    state = 3
                else:
                    state = 6
            else:
                state = -1

        elif state == 6:
            if c.isdigit():
                state = 6
            elif c == '.' or c == '-':
                if i == 3:
                    state = 7
                else:
                    state = 6
            else:
                state = -1

        elif state == 3:
            if c.isdigit():
                state = 3
            elif c == '-':
                if i == 8:
                    state = 4
                else:
                    state = 3
            else:
                state = -1

        elif state == 7:
            if c.isdigit():
                state = 7
            elif c == '.' or c == '-':
                if i == 7:
                    state = 8
                else:
                    state = 7
            else:
                state = -1

        elif state == 4:
            if c.isdigit():
                if i == 12:
                    state = 5
                else:
                    state = 4
            else:
                state = -1

        elif state == 8:
            if c.isdigit():
                if i == 11:
                    state = 9
                else:
                    state = 8
            else:
                state = -1
        elif state == 5:
            if i > 12:
                state = -1
        elif state == 9:
            if i > 11:
                state = -1
        i += 1
    if state == 5 or state == 9:
        return 'Phone.'
    else:
        return 'INVALID!'

def lexical_analyser(s):
    finalOut = ''
    finalOut = lex_helper_analyser(s)
    if finalOut == 'INVALID!' :
        finalOut = identifier_analyser(s)
        if finalOut == 'INVALID!':
            finalOut = phone_analyser(s)

    return finalOut


print(numLines)
for i in range(int(numLines)):
    inp = input()
    print(str(i+1)+':',lexical_analyser(inp))
