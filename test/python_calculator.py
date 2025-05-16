

NUMBER, PLUS, MINUS, STAR, SLASH, CARET, LPAREN, RPAREN, EOF = (
    'NUMBER', 'PLUS', 'MINUS', 'STAR', 'SLASH', 'CARET', 'LPAREN', 'RPAREN', 'EOF'
)

class Token:
    def __init__(self, type_, value=None):
        self.type = type_
        self.value = value

    def __repr__(self):
        return f'Token({self.type}, {self.value})'
    
class Lexer:
    def __init__(self, text):
        self.text = text
        self.pos = 0
        self.current_char = self.text[self.pos] if self.text else None

    def advance(self):
        self.pos += 1
        self.current_char = self.text[self.pos] if self.pos < len(self.text) else None

    def skip_whitespace(self):
        while self.current_char and self.current_char.isspace():
            self.advance()

    def number(self):
        result = ''
        while self.current_char and (self.current_char.isdigit() or self.current_char == '.'):
            result += self.current_char
            self.advance()
        return Token(NUMBER, float(result))

    def get_next_token(self):
        self.skip_whitespace()
        if not self.current_char:
            return Token(EOF)

        if self.current_char.isdigit() or self.current_char == '.':
            return self.number()
        if self.current_char == '+':
            self.advance()
            return Token(PLUS)
        if self.current_char == '-':
            self.advance()
            return Token(MINUS)
        if self.current_char == '*':
            self.advance()
            return Token(STAR)
        if self.current_char == '/':
            self.advance()
            return Token(SLASH)
        if self.current_char == '^':
            self.advance()
            return Token(CARET)
        if self.current_char == '(':
            self.advance()
            return Token(LPAREN)
        if self.current_char == ')':
            self.advance()
            return Token(RPAREN)

        raise Exception(f"Unknown character: {self.current_char}")

class Parser:
    def __init__(self, lexer):
        self.lexer = lexer
        self.current_token = self.lexer.get_next_token()

    def eat(self, token_type):
        if self.current_token.type == token_type:
            self.current_token = self.lexer.get_next_token()
        else:
            raise Exception(f"Expected token {token_type}, got {self.current_token.type}")

    def parse(self):
        return self.expr()

    def expr(self):
        result = self.term()
        while self.current_token.type in (PLUS, MINUS):
            if self.current_token.type == PLUS:
                self.eat(PLUS)
                result += self.term()
            elif self.current_token.type == MINUS:
                self.eat(MINUS)
                result -= self.term()
        return result

    def term(self):
        result = self.factor()
        while self.current_token.type in (STAR, SLASH):
            if self.current_token.type == STAR:
                self.eat(STAR)
                result *= self.factor()
            elif self.current_token.type == SLASH:
                self.eat(SLASH)
                result /= self.factor()
        return result

    def factor(self):
        result = self.base()
        if self.current_token.type == CARET:
            self.eat(CARET)
            result = result ** self.factor()  # Right-associative
        return result

    def base(self):
        if self.current_token.type == NUMBER:
            value = self.current_token.value
            self.eat(NUMBER)
            return value
        elif self.current_token.type == LPAREN:
            self.eat(LPAREN)
            result = self.expr()
            self.eat(RPAREN)
            return result
        else:
            raise Exception("Unexpected token in base()")

def evaluate_expression(expr_string):
    lexer = Lexer(expr_string)
    parser = Parser(lexer)
    return parser.parse()


print(evaluate_expression("3 + 4 * (2 - 1) ^ 2"))  # Output: 7.0
print(evaluate_expression("2^3^2"))               # Output: 512.0 (right-associative)
print(evaluate_expression("(1 + 2) * (3 + 4)"))   # Output: 21.0
print(evaluate_expression("(1 + 2()"))   # Output: 21.0
